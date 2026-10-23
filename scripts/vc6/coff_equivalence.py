#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original diagnostic linker tooling; no retail bytes.
"""Conservative COMDAT equivalence for explicit aliases of matched addresses.

This models only already-bound, collocated function names in the M1 probe.
It neither discovers native aliases nor proves whole-image identity.
"""
import hashlib
import struct
from verify_vtable import parse_coff, defined_symbol, VerifyError


def fingerprint(path, name, extent, address, bindings, cache):
    if extent <= 0:
        raise VerifyError('invalid function extent')
    if path not in cache:
        cache[path] = parse_coff(path)
    data, sections, symbols, auxiliary = cache[path]
    symbol = defined_symbol(sections, symbols, name)
    secno = symbol['section']
    sec = sections[secno]
    flags = struct.unpack_from('<I', data, 20 + 40 * (secno - 1) + 36)[0]
    if symbol['storage_class'] != 2 or symbol['value'] != 0 or flags & 0x20001000 != 0x20001000 or flags & 0x800:
        raise VerifyError('not an external code COMDAT entry')
    selections = [auxiliary[i + 1][14] for i, s in symbols.items()
                  if s['section'] == secno and s['storage_class'] == 3 and s['aux_count']
                  and s['name'] == sec['name'] and s['value'] == 0 and i + 1 in auxiliary]
    if len(selections) != 1 or selections[0] not in (1, 2):
        raise VerifyError('unsupported COMDAT selection')
    for other in symbols.values():
        if other['section'] == secno and other['storage_class'] == 2 and other['name'] != name:
            if other['value'] != 0 or bindings.get(other['name'], (None,))[0] != address:
                raise VerifyError('another external label has no identical address binding')
    raw = bytearray(data[sec['raw_ptr']:sec['raw_ptr'] + sec['raw_size']])
    if len(raw) < extent or len(raw) > extent + 15 or any(b not in (0x90, 0xCC) for b in raw[extent:]):
        raise VerifyError('section exceeds the complete function and alignment padding')
    relocations, occupied = [], set()
    for offset, index, kind in sorted(sec['relocs']):
        if kind not in (6, 0x14) or offset + 4 > extent or occupied.intersection(range(offset, offset + 4)):
            raise VerifyError('unsupported, overlapping or out-of-function relocation')
        occupied.update(range(offset, offset + 4))
        target = symbols[index]
        if target['storage_class'] == 105:
            raise VerifyError('weak relocation target requires actual linker selection')
        bound = bindings.get(target['name'])
        if bound is not None:
            value = bound[0]
        elif target['section'] == secno and target['storage_class'] in (2, 3) and 0 <= target['value'] < extent:
            value = address + target['value']
        else:
            raise VerifyError('unbound relocation target: ' + target['name'])
        addend = int.from_bytes(raw[offset:offset + 4], 'little', signed=kind == 0x14)
        relocations.append((offset, kind, (value + addend) & 0xFFFFFFFF))
        raw[offset:offset + 4] = bytes(4)
    return bytes(raw), tuple(relocations)


def plan_folds(providers, defined_in, bindings):
    """Return object renames and evidence for explicit same-address aliases.

    Every candidate and provider definition must agree, since LINK can select
    any COMDAT. Ambiguity fails closed and leaves the existing plan unchanged.
    providers maps an address to (matched symbol, full validated byte extent).
    """
    renames, accepted, rejected, cache = {}, [], [], {}
    provider_names = {sym for sym, _ in providers.values()}
    for alias, (address, source) in sorted(bindings.items()):
        if source != 'symbol_bindings' or address not in providers or alias in provider_names or alias not in defined_in:
            continue
        provider, extent = providers[address]
        if provider not in defined_in:
            continue
        # Weak externals already resolve through LINK; only strong code is folded.
        paths = []
        competing_definition = False
        for path in defined_in[alias]:
            if path not in cache:
                cache[path] = parse_coff(path)
            _, sections, symbols, _ = cache[path]
            competing_definition |= any(s['name'] == alias and
                (s['storage_class'] == 105 or (s['storage_class'] == 2 and s['section'] == 0 and s['value'] > 0))
                for s in symbols.values())
            if any(s['name'] == alias and s['storage_class'] == 2 and s['section'] in sections
                   for s in symbols.values()):
                paths.append(path)
        if not paths:
            continue
        try:
            if competing_definition:
                raise VerifyError('candidate also has a weak or common definition')
            proof = fingerprint(defined_in[provider][0], provider, extent, address, bindings, cache)
            for path in defined_in[provider]:
                if fingerprint(path, provider, extent, address, bindings, cache) != proof:
                    raise VerifyError('provider definitions differ')
            for path in paths:
                if fingerprint(path, alias, extent, address, bindings, cache) != proof:
                    raise VerifyError('code or relocation targets differ')
        except (VerifyError, KeyError, IndexError, struct.error) as error:
            rejected.append({'symbol': alias, 'provider': provider, 'address': hex(address), 'reason': str(error)})
            continue
        for path in paths:
            renames.setdefault(path, {})[alias] = '__collocated_' + hashlib.sha256(alias.encode()).hexdigest()
        accepted.append({'symbol': alias, 'provider': provider, 'address': hex(address),
                         'extent': extent, 'definitions': [str(p) for p in paths],
                         'normalized_sha256': hashlib.sha256(proof[0]).hexdigest(),
                         'relocations': proof[1]})
    return renames, accepted, rejected
