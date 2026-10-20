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
import argparse, collections, json, os, re, subprocess, sys

GHIDRA = os.environ.get("GHIDRA", os.path.expanduser("~/.cargo/bin/ghidra"))


def ghidra_func_size(addr):
    """Byte length of the function starting at `addr`, from Ghidra.

    Guessing this from the instruction shape has produced three separate false
    readings in this tree: a length that stops short of the last instruction
    reports a partial match for an exact one, and a length that overruns counts
    the *next* function's opening instruction as a mismatch. Ghidra already
    knows the answer, so ask it."""
    out = subprocess.run([GHIDRA, "function", "get", hex(addr), "--json"],
                         capture_output=True, text=True).stdout
    try:
        recs = json.loads(out)
    except ValueError:
        raise SystemExit(f"diff_retail: no Ghidra function record at {addr:#x}; "
                         f"pass --len explicitly")
    for r in recs:
        if int(r["entry_point"], 16) == addr and r.get("size"):
            return int(r["size"])
    raise SystemExit(f"diff_retail: {addr:#x} is not a function entry point in "
                     f"Ghidra; pass --len explicitly")


def ghidra_insns(addr, length):
    # Pull enough instructions to cover `length` bytes, then trim to it.
    #
    # This count used to be a flat 256, which silently truncated the RETAIL
    # side of the comparison for any function longer than that. A body of 371
    # instructions was scored against the first 256 of retail, so its
    # percentage was computed against a truncated target and was meaningless.
    # Two bytes is the shortest x86 instruction we care about here, so
    # length//2 is a safe upper bound on the instruction count, with a floor
    # for very short functions.
    out = subprocess.run([GHIDRA, "disasm", hex(addr), "-n", str(max(256, length // 2 + 16))],
                         capture_output=True, text=True).stdout
    data = json.loads(out)
    insns, consumed = [], 0
    for d in data:
        nbytes = len(d["bytes"]) // 2
        if consumed >= length:
            break
        insns.append((consumed, d["bytes"].lower(), d["mnemonic"].lower(),
                      ",".join(d["operands"])))
        consumed += nbytes
    return insns


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
                    help="function byte length, or 'auto' (default) to read it "
                         "from Ghidra's function record")
    a = ap.parse_args()
    addr = int(a.addr, 16)
    length = ghidra_func_size(addr) if a.len == "auto" else int(a.len, 16)

    retail = ghidra_insns(addr, length)
    comp, relocs = objdump_insns(a.obj, a.sym)
    # Trim trailing alignment padding from the compiled side. VC6 pads with
    # both the one-byte `nop` and the multi-byte `lea reg,[reg+0x0]` form.
    while comp and (comp[-1][2] == "nop"
                    or (comp[-1][2] == "lea" and "+0x0]" in comp[-1][3]
                        and regs(comp[-1][3])[:1] == regs(comp[-1][3])[1:2])):
        comp.pop()

    # A /Gy switch emits its jump and index tables immediately after the code,
    # inside the same COMDAT, and objdump happily disassembles that data as
    # instructions. Ghidra's function record stops at the last `ret`, so the
    # retail side never contains them and every table byte would otherwise be
    # scored as a mismatch. Drop the compiled tail past the function length --
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
