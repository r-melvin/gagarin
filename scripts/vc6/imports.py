#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads the pinned PE ($GAMEMD_BINARY) at build time only.
"""Imports from the import libraries (milestone M3, step 4).

Retail's import address table lists the imported functions grouped by DLL. Referencing the library
symbol of each slot (`__imp_<decorated name>`) in slot order makes LINK pull the import library
members, so the import address table, lookup tables, hint/name strings and descriptors come from
the libraries instead of the pinned image (link_m1.py --hybrid --library-imports, experimental).

Status. All 371 imports resolve to library symbols with the hints retail has, and the linked tables
have retail's sizes (IAT 0x608, descriptors 0x12C, lookup tables 0x608, names 0x184C) and retail's
descriptor order once the libraries are named in that order. The order of the functions inside each
DLL's address table is the order LINK 6 pulls the library members in, which neither /INCLUDE order nor
the thunk-or-__imp_ reference form changes, and it differs from retail's (17 of 371 slots agree). The
image therefore does not reach section identity with this flag; the default hybrid image keeps the
pinned import tables.
"""

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import tail_layout  # noqa: E402

IMAGE_BASE = 0x400000


def import_symbols(retail, libdir, extra=(), thunks=()):
    """(['__imp_...' in IAT slot order], [(slot VA, dll, name) with no library symbol]).

    thunks: names of the import thunks retail has; a slot with a thunk is referenced by the thunk's
    name, as the code that calls it does, the others by their `__imp_` symbol."""
    slots = tail_layout.import_slots(retail.pe, IMAGE_BASE, retail.sections)
    names = tail_layout.decorated_names(Path(libdir), extra)
    out, missing = [], []
    for va in sorted(slots):
        dll, key = slots[va]
        decorated = names.get((dll, key))
        if decorated is None and isinstance(key, str) and key.startswith("_"):
            decorated = key   # a DLL that exports decorated names (binkw32): retail's name is the symbol
        if decorated is None:
            missing.append((va, dll, key))
        else:
            out.append(decorated if decorated in thunks else "__imp_" + decorated)
    return out, missing
