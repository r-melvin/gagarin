// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Inline body of CCINIClass::CCINIClass(): the base construction, then the digest flag at +0x40 cleared (the vptr
// 0x7E1AF4 is seated by the compiler). Retail's out-of-line copy is 0x535B30, with the base construction expanded
// inside it; ini_class_ctor_535aa0.cpp defines that copy and does not include this header.
#ifndef GG_MATCH_CCINI_CLASS_DEFAULT_CTOR_H
#define GG_MATCH_CCINI_CLASS_DEFAULT_CTOR_H
#include "ccini_class_methods.h"
inline CCINIClass::CCINIClass() : DigestValid(false) {}
#endif
