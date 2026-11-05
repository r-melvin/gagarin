// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Inline body of INIClass::INIClass() as CCINIClass's constructor expands it at 0x5D5C07: +0x04/+0x08 zeroed, the
// list (0x49E8E0) and index (0x49EA10) constructors called, +0x3C zeroed. Retail's out-of-line copy at 0x535AA0 has
// both constructors expanded inside it; ini_class_ctor_535aa0.cpp defines that copy and does not include this header.
#ifndef GG_MATCH_LAYOUT_INI_CLASS_DEFAULT_CTOR_H
#define GG_MATCH_LAYOUT_INI_CLASS_DEFAULT_CTOR_H
#include "ini_class.h"
inline INIClass::INIClass() : unknown_04(0), unknown_08(0), unknown_3C(0) {}
#endif
