#!/usr/bin/env python3
# diff_retail.py — per-instruction match check for one function, the P3 inner loop.
#
# Compares a function compiled by the period VC6 toolchain (an i386 COFF .obj,
# disassembled with objdump) against the retail gamemd.exe bytes (via the local
# Ghidra CLI). Differences confined to a relocation slot (an absolute memory
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
import argparse, collections, json, os, re, subprocess, sys, tempfile

GHIDRA = os.environ.get("GHIDRA", os.path.expanduser("~/.cargo/bin/ghidra"))


def ghidra_bytes(addr, length):
    """Read exactly one contiguous retail span from Ghidra memory.

    Do not use `ghidra disasm` here: it may return a function's flowed blocks
    without the contiguous bytes between them, notably after calls. Linear
    decoding of the complete byte span below preserves the real address gaps.
    """
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


def raw_x86_insns(data, base_addr):
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
            ["objdump", "-D", "-b", "binary", "-m", "i386", "-M", "intel",
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
            if mnemonic == ".byte":
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
    """Instructions and relocation offsets for one symbol.

    `-r` on its own prints relocation blocks keyed by section *name*, and with
    /Gy every function lands in its own COMDAT that is still called `.text` —
    so a name-keyed lookup silently merges the relocations of every function in
    the object and can bless a differing run in one function using another
    function's relocation. `-dr` interleaves each relocation directly under the
    instruction it applies to, inside the right section, which removes the
    ambiguity entirely."""
    out = subprocess.run(["objdump", "-d", "-r", "-M", "intel", obj],
                         capture_output=True, text=True).stdout
    lines = out.splitlines()
    insns, relocs, inblk = [], set(), False
    for ln in lines:
        m = re.match(r"^[0-9a-f]+ <(.+?)>:$", ln)
        if m:
            name = m.group(1)
            if name == sym:
                inblk = True
            elif inblk and (name.startswith("$") or name.startswith(".")
                            or name.startswith(sym + "+")):
                pass  # intra-function local label (e.g. a /Gy switch-case $L264)
            else:
                inblk = False
            continue
        if not inblk:
            continue
        # A relocation line carries a type mnemonic where an instruction line
        # would carry hex bytes.
        rel = re.match(r"^\s*([0-9a-f]+):\s+([A-Za-z][A-Za-z0-9_]*)\s", ln)
        if rel and not re.match(r"^\s*[0-9a-f]+:\s+(?:[0-9a-f]{2} )", ln):
            relocs.add(int(rel.group(1), 16))
            continue
        # objdump wraps a long instruction's bytes onto continuation lines that
        # carry only "<off>: <hex bytes>" with no mnemonic — append those to the
        # previous instruction so its byte length is complete.
        cont = re.match(r"^\s*[0-9a-f]+:\s+((?:[0-9a-f]{2}\s*)+)$", ln)
        if cont and insns:
            off0, bts0, mnem0, ops0 = insns[-1]
            insns[-1] = (off0, bts0 + cont.group(1).replace(" ", "").lower(),
                         mnem0, ops0)
            continue
        m = re.match(r"^\s*([0-9a-f]+):\s+((?:[0-9a-f]{2} )+)\s*(\S+)\s*(.*)$", ln)
        if not m:
            # Do NOT end the block on a blank line: with /Gy, a function's
            # switch-case bodies are emitted as separate `$Lxxx` blocks after a
            # blank line. Only a different real-function label (handled above)
            # ends the block. Trailing alignment/data is bounded by --len + the
            # trailing-nop trim in main().
            continue
        off = int(m.group(1), 16)
        bts = m.group(2).replace(" ", "").lower()
        mnem = m.group(3).lower()
        ops = m.group(4).strip().lower()
        # objdump prints a string-op prefix as its own token ("rep stos dword
        # ptr ..."), so the mnemonic captured above would be just "rep" and the
        # real opcode would be hiding at the front of the operands. Pull it back
        # into the mnemonic; Ghidra spells the same instruction "stosd.rep",
        # which _MNEMONIC_ALIASES folds to the objdump form.
        if mnem in ("rep", "repz", "repnz", "repe", "repne", "lock") and ops:
            parts = ops.split(None, 1)
            mnem = mnem + " " + parts[0]
            ops = parts[1] if len(parts) > 1 else ""
        insns.append((off, bts, mnem, ops))
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
    ap.add_argument("--addr", required=True)
    ap.add_argument("--len", default="auto",
                    help="full validated retail byte span (hex); the legacy "
                         "'auto' default is refused because Ghidra size may omit blocks")
    a = ap.parse_args()
    addr = int(a.addr, 16)
    length = explicit_length(a.len)

    retail = raw_x86_insns(ghidra_bytes(addr, length), addr)
    comp, relocs = objdump_insns(a.obj, a.sym)
    # Trim trailing alignment padding from the compiled side. VC6 pads with
    # both the one-byte `nop` and the multi-byte `lea reg,[reg+0x0]` form.
    while comp and (comp[-1][2] == "nop"
                    or (comp[-1][2] == "lea" and "+0x0]" in comp[-1][3]
                        and regs(comp[-1][3])[:1] == regs(comp[-1][3])[1:2])):
        comp.pop()

    # A /Gy switch emits its jump and index tables immediately after the code,
    # inside the same COMDAT, and objdump happily disassembles that data as
    # instructions. The caller supplies the validated function span, so the
    # retail side includes exactly those bytes. Drop the compiled tail past
    # that span --
    # but only when the last instruction still inside the length is a terminator
    # (`ret` or an unconditional `jmp`), so a function that genuinely runs longer
    # than retail's still fails on the extra instructions rather than being
    # silently truncated. The dropped byte count is printed either way.
    inside = [c for c in comp if c[0] < length]
    if len(inside) < len(comp) and inside and inside[-1][2] in ("ret", "jmp"):
        dropped = sum(len(c[1]) // 2 for c in comp[len(inside):])
        print(f"note: dropped {dropped} bytes past the function end "
              f"(switch tables / alignment data)\n")
        comp = inside

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

    pct = 100.0 * total / n if n else 0.0
    print(f"match: {pct:.1f}%")
    sys.exit(0 if mismatch == 0 and len(retail) == len(comp) else 1)


if __name__ == "__main__":
    main()
