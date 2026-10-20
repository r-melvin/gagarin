#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; reads the developer-supplied pinned PE only.
"""Optional bridge-independent retail spans, selected by GAMEMD_BINARY."""
import json
import os
import struct
from pathlib import Path

from verify_vtable import DEFAULT_TOTALS, VerifyError, load_pe


def configured_span(address, length):
    """Return None for legacy bridge mode; an explicit bad image must fail."""
    binary = os.environ.get("GAMEMD_BINARY")
    if not binary:
        return None
    if length <= 0:
        raise ValueError("retail span length must be positive")
    expected = json.loads(Path(DEFAULT_TOTALS).read_text())["_meta"]["sha256"]
    try:
        data, _, sections = load_pe(binary, expected)
    except (VerifyError, struct.error) as exc:
        raise ValueError(str(exc)) from exc
    found = []
    for _, start, virtual_size, raw_pointer, raw_size in sections:
        if start <= address and address + length <= start + min(virtual_size, raw_size):
            offset = raw_pointer + address - start
            found.append(data[offset:offset + length])
    if len(found) != 1:
        raise ValueError(f"retail span {address:#x}+{length:#x} needs one file-backed PE section; found {len(found)}")
    return found[0]
