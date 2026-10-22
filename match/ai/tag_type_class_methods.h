// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x6E5E70), cross-checked against
//   YRpp TagTypeClass.h (consult-only; reconfirmed numerically here).
//
//   TagTypeClass derives the committed AbstractTypeClass layout spine. The only
//   members FindByNameOrID touches are ID (+0x24) and Name (+0x64) — both from
//   AbstractTypeClass — and the static lookup array TagTypes.
#ifndef GG_MATCH_AI_TAG_TYPE_CLASS_METHODS_H
#define GG_MATCH_AI_TAG_TYPE_CLASS_METHODS_H

// Share the full recovered TagTypeClass with the flag and INI methods so all
// three headers can be included together without redefining the class.
#include "tag_type_class_flag_methods.h"

#endif  // GG_MATCH_AI_TAG_TYPE_CLASS_METHODS_H
