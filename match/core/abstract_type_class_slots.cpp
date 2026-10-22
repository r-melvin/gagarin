// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// AbstractTypeClass body for slot 13 of its primary table 0x7E2000
// (abstract_type_class.h); the name is a placeholder.
#include "../_layout/abstract_type_class.h"
#include "../_layout/obj_004a1d30.h"

// FUNCTION: GAMEMD 0x410BE0
// The base fields through AbstractClass's slot 13 (a direct call), then the
// ID, Name and the +0x3D text field into the checksum sink.
void AbstractTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    crc->FUN_004A1DB0(ID);
    crc->FUN_004A1DB0(Name);
    crc->FUN_004A1DB0(UINameLabel);
}
