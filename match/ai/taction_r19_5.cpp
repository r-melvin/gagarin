// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//   Address index: 0x6E3E50.

#include "taction_class_methods.h"
#include "../_layout/team_type_class.h"
#include "../_layout/tag_type_class.h"
#include "../_layout/trigger_type_class.h"
#include "../_layout/obj_004a1d30.h"

// FUNCTION: GAMEMD 0x6E3E50
// Synchronisation checksum: the referenced objects' ids and the action parameter.
void TActionClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    if (unknown_28)
        crc->FUN_004A1D50(unknown_28->vf_rtti_4());
    crc->FUN_004A1D50(unknown_2C);
    if (unknown_30)
        crc->FUN_004A1D50(unknown_30->vf_rtti_4());
    if (unknown_4C)
        crc->FUN_004A1D50(unknown_4C->vf_rtti_4());
    if (unknown_50)
        crc->FUN_004A1D50(unknown_50->vf_rtti_4());
    crc->FUN_004A1D50(unknown_90);
}
