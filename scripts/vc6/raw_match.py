#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original
# raw_match.py — gold-standard byte-level match check for one function.
#
# Compares a compiled function's raw bytes (sliced straight from the i386-COFF
# .obj by symbol) against retail gamemd.exe bytes (GAMEMD_BINARY selects a
# SHA-pinned PE read; otherwise Ghidra supplies memory bytes), and
# normalises only supported four-byte COFF relocation fields (absolute addresses
# and relative calls/jumps that the linker fixes up).
#
# This is more robust than scripts/vc6/diff_retail.py for functions whose
# disassembly objdump prints out of address order (e.g. /Gy switch-case `$L`
# blocks + embedded jump tables): it works on the contiguous byte image, so the
# ordering never matters. Use it to confirm switch-heavy / table-driven matches.
#
# Relocations are read from the .obj's own COFF relocation table, NOT guessed
# from the size of a differing run. The earlier version treated any differing run
# of <=4 bytes as a relocation slot, which blessed register renames, swapped
# instruction pairs and different SETcc forms as matches: it reported 100.0% for
# functions diff_retail.py scored as low as 59.5%. Because verify_tus.py accepts
# either oracle, that also meant a regression producing short differing runs
# would not have been caught. Same defect, and same fix, as the zero-window
# heuristic removed from diff_retail.py.
#
# Usage:
#   raw_match.py --obj build-vc6/packet_class.obj \
#                --sym '?HostToNet@FieldClass@@QAEXXZ' --addr 0x4CB8B0 --len 0x5A
#
# Exit 0 iff every byte difference lies in a relocation slot.
import argparse, json, os, re, struct, subprocess, sys
from retail_image import configured_span
from verify_vtable import parse_coff, defined_symbol, VerifyError

GHIDRA = os.path.expanduser("~/.cargo/bin/ghidra")
HARD_LITERAL_FAILURE = 3
HARD_RELOCATION_FAILURE = 4  # address-labelled DAT_ target mismatch

# Address-labelled data symbols are either plain C names, leading-underscore C
# names, or MSVC data symbols beginning with `?DAT_...@@`. Anchor at the symbol
# start so a method/class/template name that merely contains `DAT_XXXXXXXX`
# cannot be mistaken for a global address claim.
DAT_ADDRESS_RE = re.compile(r"^(?:\?)?_?DAT_([0-9A-Fa-f]{8})(?:@@|$)")


class AddressLabelRelocationError(Exception):
    """An address-labelled DAT_ relocation does not point at its named VA."""


class FloatLiteralCheckError(Exception):
    """A defined MSVC float constant cannot be proven equal to retail."""


def raw_span_matches_modulo_relocations(retail_function, object_function, relocs):
    """Match raw bytes using the same per-byte relocation mask as raw_match.

    `diff_retail.py` uses instruction text for its normal diagnostic, so it
    calls this before applying the literal-pool check to a prospective 100%
    result. Short or otherwise non-exact spans are left to their existing
    partial-match path.
    """
    if len(retail_function) != len(object_function):
        return False
    diffs = [i for i, (retail_byte, object_byte) in enumerate(
        zip(retail_function, object_function)) if retail_byte != object_byte]
    if not diffs:
        return True
    covered = set()
    for offset in relocs:
        covered.update(range(offset, offset + 4))
    return all(offset in covered for offset in diffs)


def verify_float_literals_for_raw_exact_span(obj, sym, function_addr,
                                             retail_function):
    """Verify local literals only when the complete raw span is relocation-exact.

    Returns False for objects without named float constants or for spans with
    any non-relocation byte differences. Returns True after checking an
    eligible span; raises FloatLiteralCheckError for unverifiable/mismatched
    named local literals.
    """
    try:
        with open(obj, "rb") as stream:
            object_bytes = stream.read()
    except OSError as exc:
        raise FloatLiteralCheckError(f"cannot read COFF object for literal audit: {exc}") from exc
    if b"__real@4@" not in object_bytes and b"__real@8@" not in object_bytes:
        return False
    try:
        object_function, relocs = obj_func_bytes(obj, sym, len(retail_function))
    except ValueError as exc:
        if "requested span" in str(exc) and "exceeds COFF section size" in str(exc):
            return False
        raise FloatLiteralCheckError(f"cannot read raw span for literal audit: {exc}") from exc
    except (OSError, struct.error) as exc:
        raise FloatLiteralCheckError(f"cannot read raw span for literal audit: {exc}") from exc
    if object_function is None or not raw_span_matches_modulo_relocations(
            retail_function, object_function, relocs):
        return False
    verify_float_literal_relocations(obj, sym, function_addr, retail_function)
    return True


def verify_address_label_relocations(obj, sym, function_addr, retail_function):
    """Verify address-labelled DAT_ targets in an otherwise exact raw span.

    Relocation normalization intentionally ignores fixup bytes. For a symbol
    whose own spelling records its retail VA (DAT_XXXXXXXX), prove that the
    relocated operand still names that VA, including the COFF addend. This is
    deliberately narrow: it neither resolves arbitrary functions nor turns a
    partial body into a hard failure.
    """
    try:
        coff, sections, symbols, _ = parse_coff(obj)
    except (OSError, VerifyError, ValueError, struct.error) as exc:
        raise AddressLabelRelocationError(f"cannot parse COFF for DAT_ target audit: {exc}") from exc

    function = None
    for item in symbols.values():
        if item["name"] == sym and item["section"] in sections:
            if function is not None and (function["section"], function["value"]) != (item["section"], item["value"]):
                raise AddressLabelRelocationError(f"ambiguous COFF definitions for {sym}")
            function = item
    if function is None:
        raise AddressLabelRelocationError(f"defined COFF function not found for DAT_ audit: {sym}")

    code = sections[function["section"]]
    if code["uninitialized"]:
        raise AddressLabelRelocationError(f"function {sym} is in uninitialized COFF storage")
    start = function["value"]
    end = start + len(retail_function)
    if end > code["raw_size"] or code["raw_ptr"] + end > len(coff):
        raise AddressLabelRelocationError(f"function {sym} DAT_ audit span exceeds its COFF section")

    for rva, symbol_index, kind in code["relocs"]:
        if rva < start or rva >= end:
            continue
        target = symbols.get(symbol_index)
        if target is None:
            raise AddressLabelRelocationError(
                f"relocation at {rva:#x} refers to non-primary COFF symbol index {symbol_index}")
        match = DAT_ADDRESS_RE.match(target["name"])
        if match is None:
            continue
        if kind not in (0x0006, 0x0014):
            raise AddressLabelRelocationError(
                f"unsupported relocation type {kind:#x} for address-labelled {target['name']}")
        if rva + 4 > end:
            raise AddressLabelRelocationError(
                f"relocation for {target['name']} crosses the requested function span")

        relative = rva - start
        if kind == 0x0006:  # IMAGE_REL_I386_DIR32: S + A
            addend = struct.unpack_from("<I", coff, code["raw_ptr"] + rva)[0]
            observed = struct.unpack_from("<I", retail_function, relative)[0]
        else:  # IMAGE_REL_I386_REL32: S + A - P - 4
            addend = struct.unpack_from("<i", coff, code["raw_ptr"] + rva)[0]
            displacement = struct.unpack_from("<i", retail_function, relative)[0]
            observed = (function_addr + relative + 4 + displacement) & 0xFFFFFFFF
        expected = (int(match.group(1), 16) + addend) & 0xFFFFFFFF
        if observed != expected:
            raise AddressLabelRelocationError(
                f"+{relative:#x}: {target['name']} with COFF addend {addend:+#x} "
                f"resolves to {expected:#010x}, retail operand targets {observed:#010x}")


def verify_relocation_targets_for_raw_exact_span(obj, sym, function_addr,
                                                  retail_function):
    """Audit address-labelled relocations before accepting an exact diff.

    For a complete span, the caller uses this before accepting a raw or
    instruction-level exact result. Address-labelled operands are checked even
    if unrelated bytes make the body partial. A short COFF section checks only
    complete DAT_ relocation fields in its emitted prefix. Float-pool checking
    remains limited to a byte-exact complete span.
    """
    try:
        object_function, reloc_offsets = obj_func_bytes(obj, sym, len(retail_function))
    except ValueError as exc:
        # A short emitted COMDAT is a known partial-match shape. Do not turn
        # it into a hard failure just because the requested whole retail span
        # cannot be sliced. Still inspect every address-labelled relocation
        # present in the emitted prefix: those operands are independently
        # checkable, and instruction-diff fallback must not bless a swapped
        # DAT_ target there.
        if "exceeds COFF section size" in str(exc):
            try:
                coff, sections, symbols, _ = parse_coff(obj)
                function = defined_symbol(sections, symbols, sym)
                section = sections[function["section"]]
                available = max(0, min(len(retail_function),
                                       section["raw_size"] - function["value"]))
                # If truncation leaves only part of a relocation field, its
                # retail target is unknowable. Exclude that incomplete field
                # from the prefix audit instead of turning a short partial
                # into a hard failure.
                limit = function["value"] + available
                for rva, _, _ in section["relocs"]:
                    if function["value"] <= rva < limit and rva + 4 > limit:
                        available = min(available, rva - function["value"])
                        limit = function["value"] + available
                verify_address_label_relocations(
                    obj, sym, function_addr, retail_function[:available])
            except (OSError, ValueError, StopIteration, struct.error, VerifyError) as nested:
                raise AddressLabelRelocationError(
                    f"cannot audit address-labelled targets in short candidate {sym}: {nested}") from nested
            return False
        raise AddressLabelRelocationError(
            f"cannot read candidate function span for relocation audit: {exc}") from exc
    except (OSError, struct.error, VerifyError) as exc:
        raise AddressLabelRelocationError(
            f"cannot read candidate function span for relocation audit: {exc}") from exc
    if object_function is None:
        raise AddressLabelRelocationError(f"candidate function {sym} has no defined COFF body")
    if len(object_function) != len(retail_function):
        raise AddressLabelRelocationError(
            f"candidate function span has {len(object_function)} bytes, "
            f"retail request has {len(retail_function)}")
    # Address-labelled globals are semantic operands even when some unrelated
    # byte keeps the whole body partial. Check them before the ordinary byte
    # difference return so diff_retail's instruction fallback cannot bless a
    # normalized but wrongly targeted DAT_ relocation.
    verify_address_label_relocations(obj, sym, function_addr, retail_function)
    covered = set()
    for offset in reloc_offsets:
        covered.update(range(offset, offset + 4))
    if any(a != b and i not in covered
           for i, (a, b) in enumerate(zip(retail_function, object_function))):
        return False
    verify_float_literals_for_raw_exact_span(obj, sym, function_addr, retail_function)
    return True

def verify_float_literal_relocations(obj, sym, function_addr, retail_function):
    """Compare referenced defined __real@4@/__real@8@ values with retail.

    This deliberately checks only named, defined MSVC float-constant symbols.
    The retail target address comes from the actual relocated operand in the
    pinned PE when GAMEMD_BINARY is set (otherwise from the established Ghidra
    memory-read fallback). Other relocation classes and unresolved constants
    remain outside this narrow check.
    """
    # Most objects have no floating constants. Avoid a second COFF parse in
    # that common case; the defined MSVC constant names live in the COFF string
    # table and are longer than the eight-byte inline-name field.
    try:
        with open(obj, "rb") as stream:
            object_bytes = stream.read()
    except OSError as exc:
        raise FloatLiteralCheckError(f"cannot read COFF object for literal audit: {exc}") from exc
    if b"__real@4@" not in object_bytes and b"__real@8@" not in object_bytes:
        return
    try:
        coff, sections, symbols, _ = parse_coff(obj)
    except (OSError, VerifyError, ValueError, struct.error) as exc:
        raise FloatLiteralCheckError(f"cannot parse COFF literal targets: {exc}") from exc

    # Locate the requested function's definition, matching obj_func_bytes' rule
    # that skips undefined declarations with the same decorated name.
    function = None
    for item in symbols.values():
        if item["name"] == sym and item["section"] in sections:
            if function is not None and (function["section"], function["value"]) != (item["section"], item["value"]):
                raise FloatLiteralCheckError(f"ambiguous COFF definitions for {sym}")
            function = item
    if function is None:
        raise FloatLiteralCheckError(f"defined COFF function not found for literal audit: {sym}")

    code = sections[function["section"]]
    if code["uninitialized"]:
        raise FloatLiteralCheckError(f"function {sym} is in uninitialized COFF storage")
    start = function["value"]
    end = start + len(retail_function)
    for rva, symbol_index, kind in code["relocs"]:
        if rva < start or rva >= end:
            continue
        target = symbols.get(symbol_index)
        if target is None:
            continue
        name = target["name"]
        if not (name.startswith("__real@4@") or name.startswith("__real@8@")):
            continue
        width = 4 if name.startswith("__real@4@") else 8
        # Only a real definition in initialized COFF data is a local literal
        # whose value this object can establish. Undefined/weak references are
        # not claimed as verified by this check.
        if target["section"] not in sections:
            continue
        const_section = sections[target["section"]]
        if const_section["uninitialized"]:
            raise FloatLiteralCheckError(f"{name} is defined in uninitialized COFF storage")
        if kind not in (0x0006, 0x0014):
            raise FloatLiteralCheckError(f"unsupported relocation type {kind:#x} for {name}")
        if rva + 4 > end:
            raise FloatLiteralCheckError(f"relocation for {name} crosses the requested function span")
        rel_off = rva - start
        obj_field = const_section["raw_ptr"] + target["value"]
        if kind == 0x0006:  # IMAGE_REL_I386_DIR32, S + A
            addend = struct.unpack_from("<I", coff, code["raw_ptr"] + rva)[0]
            retail_target = struct.unpack_from("<I", retail_function, rel_off)[0]
        else:  # IMAGE_REL_I386_REL32, S + A - P - 4
            addend = struct.unpack_from("<i", coff, code["raw_ptr"] + rva)[0]
            displacement = struct.unpack_from("<i", retail_function, rel_off)[0]
            retail_target = (function_addr + rel_off + 4 + displacement) & 0xFFFFFFFF
        literal_offset = target["value"]
        if literal_offset < 0 or literal_offset + width > const_section["raw_size"]:
            raise FloatLiteralCheckError(
                f"{name} literal at symbol offset {literal_offset:#x} exceeds its COFF section")
        # The relocation may intentionally point inside an 8-byte pool entry,
        # for example at its upper DWORD. Compare the complete named constant
        # from its symbol base, adjusting the retail operand by the relocation
        # addend to recover that base address.
        retail_literal = (retail_target - addend) & 0xFFFFFFFF
        expected = coff[obj_field:obj_field + width]
        try:
            observed = retail_bytes(retail_literal, width)
        except (OSError, ValueError, KeyError, IndexError, TypeError, struct.error) as exc:
            raise FloatLiteralCheckError(
                f"cannot read retail literal {retail_literal:#x} for {name}: {exc}") from exc
        if len(observed) != width:
            raise FloatLiteralCheckError(
                f"short retail literal read at {retail_literal:#x} for {name}: "
                f"wanted {width} bytes, received {len(observed)}")
        if expected != observed:
            raise FloatLiteralCheckError(
                f"{name} resolves to retail {retail_literal:#x}, but COFF literal "
                f"{expected.hex()} != retail bytes {observed.hex()}")


def retail_bytes(addr, n):
    direct = configured_span(addr, n)
    if direct is not None:
        return direct
    r = subprocess.run([GHIDRA, "memory", "read", hex(addr), str(n)],
                       capture_output=True, text=True).stdout
    return bytes.fromhex(json.loads(r)[0]["hex"])


def obj_func_bytes(obj, sym, n):
    """Slice `n` bytes of `sym` out of the COFF .obj's section raw data.

    Returns (bytes, reloc_offsets) where reloc_offsets are relative to the start
    of the function. With /Gy each function is its own COMDAT section, so the
    section's relocation table belongs to this function alone."""
    if n <= 0:
        raise ValueError("requested function span must be positive")
    with open(obj, "rb") as stream:
        d = stream.read()
    nsec, = struct.unpack_from("<H", d, 2)
    sptr, nsym = struct.unpack_from("<II", d, 8)
    strtab = sptr + nsym * 18
    if strtab > len(d):
        raise ValueError("truncated COFF symbol table")
    primary_indices = set()
    index = 0
    while index < nsym:
        primary_indices.add(index)
        index += 1 + d[sptr + index * 18 + 17]
        if index > nsym:
            raise ValueError("COFF auxiliary records exceed symbol table")
    sec_raw, sec_size, sec_rel = {}, {}, {}
    for i in range(nsec):
        o = 20 + i * 40
        sec_raw[i + 1] = struct.unpack_from("<I", d, o + 20)[0]
        sec_size[i + 1] = struct.unpack_from("<I", d, o + 16)[0]
        # PointerToRelocations at +24, NumberOfRelocations at +32.
        sec_rel[i + 1] = (struct.unpack_from("<I", d, o + 24)[0],
                          struct.unpack_from("<H", d, o + 32)[0])
    want = sym.encode()
    i = 0
    while i < nsym:
        o = sptr + i * 18
        # Auxiliary records are not symbols, even if their payload resembles one.
        i += 1 + d[o + 17]
        name = d[o:o + 8]
        if name[:4] == b"\0\0\0\0":
            so = struct.unpack_from("<I", d, o + 4)[0]
            nm = d[strtab + so:d.find(b"\0", strtab + so)]
        else:
            nm = name.rstrip(b"\0")
        if nm == want:
            val = struct.unpack_from("<I", d, o + 8)[0]
            sec = struct.unpack_from("<h", d, o + 12)[0]
            # VC6 can put an undefined declaration before the same name's
            # defined COMDAT (notably template deleting destructors). Keep
            # searching; undefined/absolute/debug symbols have no section bytes.
            if sec <= 0:
                continue
            if sec not in sec_raw:
                raise ValueError(f"symbol {sym} refers to missing COFF section {sec}")
            base = sec_raw[sec]
            if val + n > sec_size[sec]:
                raise ValueError(f"symbol {sym}: requested span {n:#x} at "
                                 f"section offset {val:#x} exceeds COFF section "
                                 f"size {sec_size[sec]:#x}")
            if base + sec_size[sec] > len(d):
                raise ValueError(f"truncated raw data for COFF section {sec}")
            rptr, rcount = sec_rel[sec]
            if rptr + rcount * 10 > len(d):
                raise ValueError(f"truncated relocation table for COFF section {sec}")
            relocs = set()
            for k in range(rcount):
                ro = rptr + k * 10          # VirtualAddress, SymbolTableIndex, Type
                rva = struct.unpack_from("<I", d, ro)[0]
                if val <= rva < val + n:
                    kind = struct.unpack_from("<H", d, ro + 8)[0]
                    if kind not in (0x0006, 0x0014):  # I386 DIR32 / REL32
                        raise ValueError(f"unsupported COFF relocation type {kind:#x}")
                    target_index = struct.unpack_from("<I", d, ro + 4)[0]
                    if target_index not in primary_indices:
                        raise ValueError("COFF relocation target is not a primary symbol")
                    if rva + 4 > val + n:
                        raise ValueError("COFF relocation crosses requested function span")
                    relocs.add(rva - val)
            return d[base + val:base + val + n], relocs
    return None, set()


def runs(diffs):
    out = []
    if not diffs:
        return out
    s = p = diffs[0]
    for x in diffs[1:]:
        if x == p + 1:
            p = x
        else:
            out.append((s, p)); s = p = x
    out.append((s, p))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--obj", required=True)
    ap.add_argument("--sym", required=True)
    ap.add_argument("--addr", required=True)
    ap.add_argument("--len", required=True)
    a = ap.parse_args()
    n = int(a.len, 16)
    try:
        ob, relocs = obj_func_bytes(a.obj, a.sym, n)
    except (OSError, ValueError, struct.error) as exc:
        print(f"raw_match: {exc}"); sys.exit(2)
    if ob is None:
        print(f"raw_match: symbol {a.sym} not found in {a.obj}"); sys.exit(2)
    try:
        rb = retail_bytes(int(a.addr, 16), n)
    except (OSError, ValueError, struct.error) as exc:
        print(f"raw_match: {exc}"); sys.exit(2)
    if len(rb) != n:
        print(f"raw_match: requested {n} retail bytes, received {len(rb)}"); sys.exit(2)
    diffs = [i for i in range(n) if rb[i] != ob[i]]
    rr = runs(diffs)

    # Cover byte-by-byte rather than run-by-run. `runs()` merges adjacent
    # differing bytes, so two neighbouring relocated dwords — a switch jump table
    # is a row of them — form one eight-byte run that fits inside no single
    # four-byte field. Testing coverage per byte gets those right while still
    # rejecting anything outside a recorded field.
    covered = set()
    for r in relocs:
        covered.update(range(r, r + 4))

    def is_reloc(lo, hi):
        return all(i in covered for i in range(lo, hi + 1))

    reloc = [r for r in rr if is_reloc(*r)]
    real = [r for r in rr if not is_reloc(*r)]
    for s, e in rr:
        tag = "reloc" if is_reloc(s, e) else "**REAL**"
        print(f"  {s:#06x}..{e:#06x} {tag}  retail={rb[s:e+1].hex()} obj={ob[s:e+1].hex()}")
    print(f"{n - len(diffs)}/{n} bytes identical; "
          f"{len(reloc)} reloc slot(s), {len(real)} real diff(s)")
    # A changed local float can hide entirely inside a normalized DIR32/REL32
    # field. Do this only for otherwise byte-exact functions so partial-match
    # diagnostics keep their historical behavior. Exit 3 is intentionally
    # distinct: verify_all.py and verify_tus.py must not accept diff_retail's
    # instruction-position fallback after this failure.
    if not real:
        try:
            verify_address_label_relocations(a.obj, a.sym, int(a.addr, 16), rb)
            verify_float_literal_relocations(a.obj, a.sym, int(a.addr, 16), rb)
        except AddressLabelRelocationError as exc:
            print(f"raw_match: HARD DAT-RELOCATION FAILURE: {exc}")
            sys.exit(HARD_RELOCATION_FAILURE)
        except FloatLiteralCheckError as exc:
            print(f"raw_match: HARD FLOAT-LITERAL FAILURE: {exc}")
            sys.exit(HARD_LITERAL_FAILURE)
    print("match: 100.0%" if not real else "match: <100% (real diffs)")
    sys.exit(0 if not real else 1)


if __name__ == "__main__":
    main()
