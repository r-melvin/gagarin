// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes read from retail gamemd.exe v1.001 at 0x535AA0 and 0x535B30.
//   Placement workaround, not evidence of an original file boundary: retail 0x533D20 calls the INIClass constructor
//   at 0x535AA0, VC6 expands it when both share Init.cpp, and no ordinary source shape keeps the call. The cause is
//   unknown; the binary's file windows place these constructors with their callers. Both are the out-of-line copies:
//   the list and index constructors are expanded inside them, and the CCINIClass copy expands the INIClass constructor.
#include "_layout/ini_class.h"
#include "_layout/generic_list_inline.h"
#include "ccini_class_methods.h"

// TUSPLIT: GAMEMD 0x533D20 same-file 3.1% separate 100.0%
// FUNCTION: GAMEMD 0x535AA0
// The INIClass construction.
INIClass::INIClass() : unknown_04(0), unknown_08(0), SectionIndex(SectionIndexClass::InlineIndex()), unknown_3C(0)
{
}

// FUNCTION: GAMEMD 0x535B30
// The CCINIClass construction: the base, then the digest flag.
CCINIClass::CCINIClass() : DigestValid(false)
{
}
