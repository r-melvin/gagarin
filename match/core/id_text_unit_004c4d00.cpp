// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The unit at retail 0x4C4D00..0x4C4FFF (between Egos.CPP and the EMPulse
// unit): three of its run-time initialisers and the "%d,%s" formatter
// 0x4C4F90, in retail address order.

#include <stdio.h>
#include "../_layout/abstract_type_class.h"
#include "../_layout/obj_004a1d30.h"
#include "header_tuning_globals.h"

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0x8A3798
extern double DAT_008A3798;
// GLOBAL: GAMEMD 0x7E8718
const double DAT_007E8718 = 60.0;

// SYNTHETIC: GAMEMD 0x4C4D30
// GLOBAL: GAMEMD 0x8A3808
double DAT_008A3808 = DAT_008A3798 / DAT_007E8718;
// SYNTHETIC: GAMEMD 0x4C4D50
// GLOBAL: GAMEMD 0x8A37F0
double DAT_008A37F0 = 1.0 / DAT_008A3808;
// SYNTHETIC: GAMEMD 0x4C4ED0
// GLOBAL: GAMEMD 0x8A37F8
TuningCoordInit DAT_008A37F8(128, 128, 0);

// GLOBAL: GAMEMD 0x8A37A0 -- the static text buffer 0x4C4F90 returns.
extern char DAT_008A37A0[];
// STRING: GAMEMD 0x82085C
// "%d,%s"

// A number paired with a type: 0x4C4F90 prints "<number>,<type ID>". Called from 0x6E8510.
struct Obj_004C4F90
{
    int                unknown_00;   // +0x00
    AbstractTypeClass* unknown_04;   // +0x04

    // FUNCTION: GAMEMD 0x4C4F90
    char* FUN_004C4F90() const;
    // FUNCTION: GAMEMD 0x4C4FC0
    void FUN_004C4FC0(Obj_004A1D30* crc) const;
};
GG_STATIC_ASSERT(offsetof(Obj_004C4F90, unknown_04) == 4);

// FUNCTION: GAMEMD 0x4C4F90
char* Obj_004C4F90::FUN_004C4F90() const
{
    sprintf(DAT_008A37A0, "%d,%s", unknown_00, unknown_04->ID.Data);
    return DAT_008A37A0;
}

// FUNCTION: GAMEMD 0x4C4FC0
// Feeds the number, then the type's class kind and unique ID, into the CRC.
void Obj_004C4F90::FUN_004C4FC0(Obj_004A1D30* crc) const
{
    crc->FUN_004A1D50(unknown_00);
    if (unknown_04) {
        crc->FUN_004A1D50(unknown_04->vf_11());
        crc->FUN_004A1D50(unknown_04->vf_rtti_4());
    }
}
