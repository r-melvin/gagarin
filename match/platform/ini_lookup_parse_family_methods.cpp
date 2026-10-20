// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Five INI lookup-and-parse forwarders. Each reads one entry into a 0x80-byte
// stack buffer through the shared string reader, hands the text to its own
// parser and returns the parsed value, or returns the caller's fallback when
// the entry is absent. Ordered ascending by retail address.

#include "ini_lookup_parse_family_methods.h"

// FUNCTION: GAMEMD 0x0067B500
GG_INI_LOOKUP_PARSE_BODY(0067B500)

// FUNCTION: GAMEMD 0x0067BAC0
GG_INI_LOOKUP_PARSE_BODY(0067BAC0)

// FUNCTION: GAMEMD 0x0067BCE0
GG_INI_LOOKUP_PARSE_BODY(0067BCE0)

// FUNCTION: GAMEMD 0x0067BD30
GG_INI_LOOKUP_PARSE_BODY(0067BD30)

// FUNCTION: GAMEMD 0x0067BD80
GG_INI_LOOKUP_PARSE_BODY(0067BD80)
