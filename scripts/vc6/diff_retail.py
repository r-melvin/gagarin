#!/usr/bin/env python3
# diff_retail.py — per-instruction match check for one function, the P3 inner loop.
#
# Compares a function compiled by the period VC6 toolchain (an i386 COFF .obj,
# disassembled with objdump) against the retail gamemd.exe bytes (via the local
# Ghidra CLI, or directly from the pinned PE when GAMEMD_BINARY is set).
# Differences confined to a relocation slot (an absolute memory
# displacement or a call/jmp rel32 that the linker would fix up) are normalised,
# exactly as reccmp does — the match unit is the instruction stream, not the raw
# relocated bytes.
#
# Usage:
#   diff_retail.py --obj match/economy/storage_class.obj \
#                  --sym '?GetTotalValue@StorageClass@@QBEHXZ' \
#                  --addr 0x6C9600 --len 0x4f
#
# Exit 0 iff every instruction matches (modulo relocations).
import argparse, collections, itertools, json, os, re, struct, subprocess, sys, tempfile
from retail_image import configured_span
import raw_match
from verify_vtable import VerifyError, defined_symbol, parse_coff

GHIDRA = os.environ.get("GHIDRA", os.path.expanduser("~/.cargo/bin/ghidra"))


def ghidra_bytes(addr, length):
    """Read a contiguous pinned-PE span when configured, else Ghidra memory.

    Do not use `ghidra disasm` here: it may return a function's flowed blocks
    without the contiguous bytes between them, notably after calls. Linear
    decoding of the complete byte span below preserves the real address gaps.
    """
    try:
        direct = configured_span(addr, length)
    except (OSError, ValueError) as exc:
        raise SystemExit(f"diff_retail: {exc}") from exc
    if direct is not None:
        return direct
    result = subprocess.run([GHIDRA, "memory", "read", hex(addr), str(length)],
                            capture_output=True, text=True)
    if result.returncode:
        raise SystemExit(f"diff_retail: Ghidra memory read failed at {addr:#x}: "
                         f"{result.stderr.strip() or result.stdout.strip()}")
    try:
        records = json.loads(result.stdout)
    except ValueError as e:
        raise SystemExit(f"diff_retail: invalid Ghidra memory-read response at "
                         f"{addr:#x}: {e}")
    if not isinstance(records, list) or not records:
        raise SystemExit(f"diff_retail: Ghidra returned no bytes at {addr:#x}")

    data = bytearray()
    expected = addr
    for record in records:
        try:
            start = int(record["address"], 16)
            size = int(record["size"])
            chunk = bytes.fromhex(record["hex"])
        except (KeyError, TypeError, ValueError) as e:
            raise SystemExit(f"diff_retail: malformed Ghidra memory span at "
                             f"{addr:#x}: {e}")
        if start != expected:
            raise SystemExit(f"diff_retail: Ghidra memory read is not contiguous "
                             f"at {expected:#x} (next span starts {start:#x})")
        if len(chunk) != size:
            raise SystemExit(f"diff_retail: Ghidra span at {start:#x} reports "
                             f"{size} bytes but returned {len(chunk)}")
        data.extend(chunk)
        expected += size
    if len(data) != length:
        raise SystemExit(f"diff_retail: requested {length} bytes at {addr:#x}, "
                         f"Ghidra returned {len(data)}")
    return bytes(data)


def raw_x86_insns(data, base_addr, *, allow_data=False):
    """Decode every byte of a contiguous retail span as 32-bit x86.

    objdump receives an isolated raw binary at the retail's true address. Its
    listing is linear, so a CALL does not make later contiguous instructions
    disappear as they can from Ghidra's function-flow disassembly.
    """
    if not data:
        raise SystemExit("diff_retail: refusing to decode an empty retail span")
    path = None
    try:
        with tempfile.NamedTemporaryFile(prefix="gagarin-retail-", suffix=".bin",
                                         dir="/tmp", delete=False) as f:
            f.write(data)
            path = f.name
        result = subprocess.run(
            ["objdump", "-D", "-z", "-b", "binary", "-m", "i386", "-M", "intel",
             f"--adjust-vma={base_addr:#x}", path],
            capture_output=True, text=True)
        if result.returncode:
            raise SystemExit("diff_retail: objdump could not decode retail span: "
                             f"{result.stderr.strip() or result.stdout.strip()}")

        insns = []
        for line in result.stdout.splitlines():
            # A long x86 instruction can be wrapped onto a bytes-only line.
            continuation = re.match(
                r"^\s*([0-9a-fA-F]+):\s+((?:[0-9a-fA-F]{2}\s*)+)$", line)
            if continuation:
                if not insns:
                    raise SystemExit("diff_retail: objdump returned instruction "
                                     "continuation without an instruction")
                address = int(continuation.group(1), 16)
                off, bts, mnem, ops = insns[-1]
                if address != base_addr + off + len(bts) // 2:
                    raise SystemExit("diff_retail: non-contiguous objdump byte "
                                     f"continuation at {address:#x}")
                insns[-1] = (off, bts + re.sub(r"\s+", "", continuation.group(2)).lower(),
                             mnem, ops)
                continue

            match = re.match(
                r"^\s*([0-9a-fA-F]+):\s+((?:[0-9a-fA-F]{2}\s+)+)"
                r"(\S+)(?:\s+(.*))?$", line)
            if not match:
                continue
            address = int(match.group(1), 16)
            byte_string = re.sub(r"\s+", "", match.group(2)).lower()
            mnemonic = match.group(3).lower()
            operands = (match.group(4) or "").strip().lower()
            if mnemonic == ".byte" and not allow_data:
                raise SystemExit(f"diff_retail: objdump could not decode byte at "
                                 f"{address:#x}; check the explicit span")
            # Match objdump_insns: objdump renders string prefixes as a
            # separate mnemonic token ("rep movs ..."), while Ghidra's
            # mnemonic aliases normalize forms such as "movsd.rep".
            if mnemonic in ("rep", "repz", "repnz", "repe", "repne", "lock") and operands:
                parts = operands.split(None, 1)
                mnemonic += " " + parts[0]
                operands = parts[1] if len(parts) > 1 else ""
            insns.append((address - base_addr, byte_string, mnemonic, operands))

        if not insns:
            raise SystemExit(f"diff_retail: objdump decoded no instructions at "
                             f"{base_addr:#x}")
        expected = base_addr
        for off, byte_string, _, _ in insns:
            address = base_addr + off
            if address != expected:
                raise SystemExit(f"diff_retail: objdump skipped bytes at "
                                 f"{expected:#x} before {address:#x}")
            expected += len(byte_string) // 2
        if expected != base_addr + len(data):
            raise SystemExit(f"diff_retail: decoded span ends at {expected:#x}, "
                             f"not {base_addr + len(data):#x}; check --len")
        decoded = bytes.fromhex("".join(byte_string for _, byte_string, _, _ in insns))
        if decoded != data:
            raise SystemExit("diff_retail: decoded instruction bytes do not "
                             "reconstruct the requested retail span")
        return insns
    finally:
        if path and os.path.exists(path):
            os.unlink(path)


def explicit_length(text):
    """Return a validated positive length; Ghidra's size estimate is unsafe."""
    if text == "auto":
        raise SystemExit("diff_retail: warning: --len auto is refused because "
                         "Ghidra's function size can omit contiguous blocks; "
                         "pass the full validated retail span with --len")
    try:
        length = int(text, 16)
    except ValueError:
        raise SystemExit(f"diff_retail: invalid --len {text!r}; use a hex span")
    if length <= 0:
        raise SystemExit("diff_retail: --len must be a positive byte span")
    return length


def objdump_insns(obj, sym):
    """Decode one COFF symbol's own section bytes and return local relocations.

    Parsing `objdump -d` is unsafe for VC6 `/Gy` objects: each function has a
    separate COMDAT section named `.text`, and objdump can print another
    section's `$L` switch labels at matching offsets in this one. Such a label
    can split an instruction and corrupt this function's score. Slice the
    symbol's actual section bytes from COFF and linearly decode them instead;
    the section identity also keeps its relocation table unambiguous.
    """
    try:
        data, sections, symbols, _ = parse_coff(obj)
        function = defined_symbol(sections, symbols, sym)
    except (OSError, ValueError, VerifyError) as exc:
        raise SystemExit(f"diff_retail: cannot read COFF symbol {sym} in {obj}: {exc}") from exc
    section = sections[function["section"]]
    if section["uninitialized"]:
        raise SystemExit(f"diff_retail: symbol {sym} is in uninitialized COFF data")
    start = function["value"]
    end = section["raw_size"]
    if start < 0 or start >= end:
        raise SystemExit(f"diff_retail: symbol {sym} has no initialized section bytes")
    raw_start = section["raw_ptr"] + start
    raw_end = section["raw_ptr"] + end
    if raw_end > len(data):
        raise SystemExit(f"diff_retail: truncated COFF bytes for symbol {sym}")
    code = data[raw_start:raw_end]
    try:
        object_code, relocs = raw_match.obj_func_bytes(obj, sym, len(code))
    except (OSError, ValueError, struct.error, IndexError) as exc:
        raise SystemExit(f"diff_retail: invalid COFF relocations for {sym} in {obj}: {exc}") from exc
    if object_code != code:
        raise SystemExit(f"diff_retail: COFF symbol slice disagrees for {sym} in {obj}")
    try:
        insns = raw_x86_insns(code, 0, allow_data=True)
    except SystemExit as exc:
        raise SystemExit(f"diff_retail: cannot decode COFF symbol {sym}: {exc}") from exc
    # A symbol may start inside a shared section; return offsets relative to
    # that symbol, matching the instruction stream's zero-based offsets.
    return insns, relocs


# Ghidra and objdump disagree on a few mnemonic spellings for the same opcode.
# Fold them so the multiset comparison does not report spelling as a difference.
_MNEMONIC_ALIASES = {
    "jz": "je", "jnz": "jne", "jnc": "jae", "jc": "jb",
    "jna": "jbe", "jnae": "jb", "jnb": "jae", "jnbe": "ja",
    "jng": "jle", "jnge": "jl", "jnl": "jge", "jnle": "jg",
    "jp": "jpe", "jnp": "jpo",
    "setz": "sete", "setnz": "setne", "setnc": "setae", "setc": "setb",
    "cmpsd.repe": "repz cmps", "movsd.rep": "rep movs",
    "stosd.rep": "rep stos", "scasb.repne": "repnz scas",
    "movsb.rep": "rep movs", "cmpsb.repe": "repz cmps",
}


def canon_mnemonic(m):
    m = m.lower()
    # objdump prints the string ops as two tokens ("rep movs"); Ghidra as one.
    for prefix in ("rep ", "repz ", "repnz "):
        if m.startswith(prefix):
            return prefix.strip() + " " + m[len(prefix):].split()[0]
    return _MNEMONIC_ALIASES.get(m, m)


# x86 register tokens, longest-first so `eax` wins over `ax` and `ah`/`al`.
REG_RE = re.compile(
    r"\b(e(?:ax|bx|cx|dx|si|di|bp|sp)|ax|bx|cx|dx|si|di|bp|sp"
    r"|[abcd][lh]|st\(\d\)|mm\d|xmm\d+)\b")


def regs(ops):
    """Ordered list of register tokens in an operand string, case-normalised.

    Ghidra prints `EDI,EDI` and objdump prints `edi,edi`; both reduce to the
    same token list, so this compares register *roles* rather than spelling."""
    return REG_RE.findall(ops.lower())


def compiled_reloc_targets(obj, sym):
    """{reloc offset: target offset} for DIR32 relocations in sym's section that
    point back into the same section, both relative to the symbol start.

    These are the switch jump-table slots (and the `jmp`/`movzx` operands that
    address a table): the linker would fix them up, so their stored value says
    nothing and the symbol they name is what has to be compared."""
    try:
        data, sections, symbols, _ = parse_coff(obj)
        function = defined_symbol(sections, symbols, sym)
    except (OSError, ValueError, VerifyError) as exc:
        raise SystemExit(f"diff_retail: cannot read COFF symbol {sym} in {obj}: {exc}") from exc
    section = sections[function["section"]]
    start = function["value"]
    out = {}
    for rva, index, kind in section["relocs"]:
        target = symbols.get(index)
        if (kind == 0x0006 and rva >= start and target
                and target["section"] == function["section"]):
            addend, = struct.unpack_from("<I", data, section["raw_ptr"] + rva)
            out[rva - start] = target["value"] + addend - start
    return out


_TABLE_OPERAND = {
    # `jmp dword ptr [reg*4+table]` reads a switch's dword jump table;
    # `movzx reg,byte ptr [reg+table]` (or `mov r8,...` after an `xor`) reads its
    # byte index table.
    "jmp": (re.compile(r"dword ptr \[\w+\*4\+0x([0-9a-f]+)\]"), "dword"),
    "movzx": (re.compile(r"byte ptr \[\w+\+0x([0-9a-f]+)\]"), "byte"),
    "mov": (re.compile(r"^[abcd]l,byte ptr \[\w+\+0x([0-9a-f]+)\]"), "byte"),
}


def table_refs(insns, resolve):
    """{table offset: 'dword'|'byte'} for the tables the code references.

    `resolve(insn)` returns the table offset an instruction addresses, or None.
    Tables sit after all the code, so the scan stops at the first table start:
    everything beyond it is table data that happens to decode as instructions."""
    found = {}
    for insn in insns:
        if insn[0] >= min(found, default=insn[0] + 1):
            break
        kind = _TABLE_OPERAND.get(insn[2])
        offset = resolve(insn) if kind else None
        if offset is not None:
            found[offset] = kind[1]
    return found


def retail_table_resolver(addr, length):
    def resolve(insn):
        m = _TABLE_OPERAND[insn[2]][0].search(insn[3])
        target = int(m.group(1), 16) - addr if m else -1
        return target if 0 <= target < length else None
    return resolve


def compiled_table_resolver(targets):
    def resolve(insn):
        # The 32-bit table displacement is the last field of both encodings.
        return targets.get(insn[0] + len(insn[1]) // 2 - 4)
    return resolve


def trim_padding(insns):
    """Drop trailing alignment padding: `nop`, `lea reg,[reg+0x0]`, `mov reg,reg`."""
    def padding(insn):
        mnemonic, ops = insn[2], insn[3]
        return (mnemonic == "nop"
                or (mnemonic == "lea" and "+0x0]" in ops
                    and regs(ops)[:1] == regs(ops)[1:2])
                or (mnemonic == "mov" and re.fullmatch(r"(e[a-z]{2}),\1", ops)))
    while insns and padding(insns[-1]):
        insns.pop()
    return insns


def read_tables(starts, data, end, code, slot_target):
    """Entries of every table, in address order, as [(kind, [entry, ...])].

    `starts` is {table offset: kind}; a table runs to the next table or `end`.
    A dword table is the run of slots `slot_target(offset)` accepts, each mapped
    to the index in `code` of the instruction it lands on (-1 if none); a byte
    table is its bytes minus trailing 0x90/0xcc padding."""
    by_offset = {insn[0]: i for i, insn in enumerate(code)}
    order = sorted(starts)
    tables = []
    for n, start in enumerate(order):
        stop = order[n + 1] if n + 1 < len(order) else end
        if starts[start] == "byte":
            tables.append(("byte", list(data[start:stop].rstrip(b"\x90\xcc"))))
            continue
        entries = []
        for at in range(start, stop - 3, 4):
            target = slot_target(at)
            if target is None:
                break
            entries.append(by_offset.get(target, -1))
        tables.append(("dword", entries))
    return tables


def compare_tables(retail_tables, comp_tables):
    """(matching, mismatching) entry counts; a missing table or entry is a miss."""
    good = bad = 0
    for r, c in itertools.zip_longest(retail_tables, comp_tables):
        if r is None or c is None or r[0] != c[0]:
            bad += max([len(t[1]) for t in (r, c) if t] + [1])
            continue
        same = sum(x == y for x, y in zip(r[1], c[1]))
        good += same
        bad += max(len(r[1]), len(c[1])) - same
    return good, bad


def reloc_normalised_equal(rb, cb, insn_off, relocs):
    """True if compiled bytes cb match retail bytes rb once the relocation
    fields the linker would rewrite are masked out.

    Every differing byte must fall inside a four-byte window starting at a
    recorded relocation offset for this section. Byte-level test ONLY: a
    differing run of <=4 bytes also covers a modrm byte, so `xor edi,edi`
    (33ff) against `xor ebx,ebx` (33db) would pass on its own — a register
    rename, not a relocation. Callers MUST also require the operand register
    lists to agree (see `regs`)."""
    if len(rb) != len(cb):
        return False
    if rb == cb:
        return True
    r = bytes.fromhex(rb)
    c = bytes.fromhex(cb)
    diff = [i for i in range(len(r)) if r[i] != c[i]]
    if not diff:
        return True
    if not relocs:
        return False

    runs = []
    start = diff[0]
    prev = diff[0]
    for i in diff[1:]:
        if i != prev + 1:
            runs.append((start, prev))
            start = i
        prev = i
    runs.append((start, prev))

    for lo, hi in runs:
        alo = insn_off + lo
        ahi = insn_off + hi
        if not any(f <= alo and ahi < f + 4 for f in relocs):
            return False
    return True


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--obj", required=True)
    ap.add_argument("--sym", required=True)
    ap.add_argument("--skip", metavar="RETAIL,COMPILED", default="0,0",
                    help="leading instructions to drop from the retail / compiled stream "
                         "(a distribution patch over a function's prologue)")
    ap.add_argument("--dump-streams", metavar="JSON",
                    help="write the trimmed retail/compiled instruction streams "
                         "and COFF relocation offsets to JSON (residual_classify.py)")
    ap.add_argument("--addr", required=True)
    ap.add_argument("--len", default="auto",
                    help="full validated retail byte span (hex); the legacy "
                         "'auto' default is refused because Ghidra size may omit blocks")
    a = ap.parse_args()
    addr = int(a.addr, 16)
    length = explicit_length(a.len)

    retail_raw = ghidra_bytes(addr, length)
    retail = raw_x86_insns(retail_raw, addr, allow_data=True)
    comp, relocs = objdump_insns(a.obj, a.sym)
    # A /Gy switch emits its jump and index tables immediately after the code,
    # inside the same COMDAT, and objdump happily disassembles that data as
    # instructions. Find the tables from the code that reads them (`jmp
    # [reg*4+table]`, and `movzx`/`mov r8` of `[reg+table]`), stop decoding at the
    # first one on both sides, and compare the slots separately below. The
    # compiled side names its tables through relocations; retail holds addresses.
    comp_targets = compiled_reloc_targets(a.obj, a.sym)
    retail_tabs = table_refs(retail, retail_table_resolver(addr, length))
    comp_tabs = table_refs(comp, compiled_table_resolver(comp_targets))
    comp_data = bytes.fromhex("".join(c[1] for c in comp))
    if retail_tabs:
        retail = [r for r in retail if r[0] < min(retail_tabs)]
    if comp_tabs:
        comp = [c for c in comp if c[0] < min(comp_tabs)]
    # Table data may be undecodable, but code must not be.
    for r in retail:
        if r[2] == ".byte":
            raise SystemExit(f"diff_retail: objdump could not decode byte at "
                             f"{addr + r[0]:#x}; check the explicit span")

    # Trim trailing alignment padding from the compiled side. VC6 pads with
    # both the one-byte `nop` and the multi-byte `lea reg,[reg+0x0]` form.
    trim_padding(comp)
    if retail_tabs:
        trim_padding(retail)

    # Without a table, the compiled tail past the validated span may still be
    # switch data. Drop it --
    # but only when the last instruction still inside the length is a terminator
    # (`ret` or an unconditional `jmp`), so a function that genuinely runs longer
    # than retail's still fails on the extra instructions rather than being
    # silently truncated. The dropped byte count is printed either way.
    inside = [c for c in comp if c[0] < length]
    if (not comp_tabs and len(inside) < len(comp) and inside
            and inside[-1][2] in ("ret", "jmp")):
        dropped = sum(len(c[1]) // 2 for c in comp[len(inside):])
        print(f"note: dropped {dropped} bytes past the function end "
              f"(switch tables / alignment data)\n")
        comp = inside

    table_good = table_bad = 0
    if retail_tabs:
        def retail_slot(at):
            target = struct.unpack_from("<I", retail_raw, at)[0] - addr
            return target if 0 <= target < length else None
        table_good, table_bad = compare_tables(
            read_tables(retail_tabs, retail_raw, length, retail, retail_slot),
            read_tables(comp_tabs, comp_data, len(comp_data), comp, comp_targets.get))
        print(f"table: {table_good}/{table_good + table_bad} switch table entries match\n")
    elif comp_tabs:
        print("table: compiled switch table lies outside the retail span; not compared\n")

    skip_retail, skip_comp = (int(v) for v in a.skip.split(","))
    retail, comp = retail[skip_retail:], comp[skip_comp:]
    if a.dump_streams:
        with open(a.dump_streams, "w") as f:
            json.dump({"retail": retail, "comp": comp,
                       "relocs": sorted(relocs) if not isinstance(relocs, dict)
                       else sorted(relocs.keys())}, f)
    n = max(len(retail), len(comp))
    exact = reloc = mismatch = 0
    print(f"{'off':>5}  {'retail':<22} {'compiled':<22} verdict")
    for i in range(n):
        r = retail[i] if i < len(retail) else (None, "", "--", "")
        c = comp[i] if i < len(comp) else (None, "", "--", "")
        if r[1] == c[1]:
            v, _ = "EXACT", exact
            exact += 1
        elif (r[2] == c[2] and regs(r[3]) == regs(c[3])
              and reloc_normalised_equal(r[1], c[1],
                                         c[0] if c[0] is not None else 0,
                                         relocs)):
            v = "RELOC"
            reloc += 1
        else:
            v = "**DIFF**"
            mismatch += 1
        print(f"{(r[0] if r[0] is not None else 0):#06x}  "
              f"{r[2]+' '+r[3]:<22.22} {c[2]+' '+c[3]:<22.22} {v}")
    # Table slots only ever lower the score: matching slots add no credit, each
    # mismatching one counts as a differing unit.
    mismatch += table_bad
    n += table_bad
    total = exact + reloc
    print(f"\n{total}/{n} instructions match "
          f"({exact} exact, {reloc} reloc-normalised, {mismatch} diff)")

    # The positional score measures alignment, so a single inserted or moved
    # instruction near the top drags it down far below the real delta. The
    # mnemonic multiset does not care about position: when it comes out empty the
    # two streams contain exactly the same instructions and every remaining
    # difference is scheduling or register naming. Print it whenever the score is
    # imperfect, so a low number is never read as a wrong reading by mistake.
    if mismatch:
        rmn = collections.Counter(canon_mnemonic(i[2]) for i in retail)
        cmn = collections.Counter(canon_mnemonic(i[2]) for i in comp)
        only_r = {k: v for k, v in (rmn - cmn).items()}
        only_c = {k: v for k, v in (cmn - rmn).items()}
        if not only_r and not only_c:
            print(f"multiset: identical ({len(retail)} vs {len(comp)} "
                  f"instructions) — scheduling/register naming only")
        else:
            print(f"multiset: retail-only {only_r or '{}'}  "
                  f"compiled-only {only_c or '{}'}  "
                  f"({len(retail)} vs {len(comp)} instructions)")

    # Disassembly matching can normalize a relocation without checking the
    # value of a local MSVC float pool entry. Before a prospective exact result,
    # require the raw span itself to be exact modulo COFF relocation fields and
    # run the shared literal check. Partial or non-exact raw spans retain their
    # established diagnostic path.
    if mismatch == 0 and len(retail) == len(comp):
        try:
            raw_match.verify_relocation_targets_for_raw_exact_span(
                a.obj, a.sym, addr, retail_raw)
        except raw_match.AddressLabelRelocationError as exc:
            print(f"diff_retail: HARD DAT-RELOCATION FAILURE: {exc}")
            sys.exit(raw_match.HARD_RELOCATION_FAILURE)
        except raw_match.FloatLiteralCheckError as exc:
            print(f"diff_retail: HARD FLOAT-LITERAL FAILURE: {exc}")
            sys.exit(raw_match.HARD_LITERAL_FAILURE)

    pct = 100.0 * total / n if n else 0.0
    print(f"match: {pct:.1f}%")
    sys.exit(0 if mismatch == 0 and len(retail) == len(comp) else 1)


if __name__ == "__main__":
    main()
