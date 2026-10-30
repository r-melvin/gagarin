// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm at 0x7514D0).
//   Names cross-checked against YRpp (every offset
//   reconfirmed numerically from the disassembly below).
//
// VocClass::FindIndex — case-insensitive lookup of a sound name within the
// global VocClass::Array, returning its index or -1.
//
// Disasm-derived facts (0x7514D0):
//   * Array : DynamicVectorClass<VocClass*> @ 0x00B1D378.
//       items base  -> [0x00B1D37C]  (vector +0x04)
//       active count-> [0x00B1D388]  (vector +0x10)
//   * each Array[i] is a VocClass*; its +0x00 dword is an AudioEvent pointer.
//     If non-null, a __thiscall getter (retail 0x00405170) yields the name;
//     otherwise the literal "Invalid Voc" (0x00846574) is used.
//   * names compared with _stricmp (retail 0x007C8D20, cdecl(pName, name)).
#ifndef GG_MATCH_AUDIO_VOC_CLASS_METHODS_H
#define GG_MATCH_AUDIO_VOC_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/voc_class.h"

// VocClass, its descriptor and the VocClass::Array global are defined in match/_layout/voc_class.h.

#endif  // GG_MATCH_AUDIO_VOC_CLASS_METHODS_H
