// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Two WarheadTypeClass array helpers emitted in the block at 0x40F2D0. The
// class is fixed by the constructor 0x75CEC0 (it installs the WarheadTypeClass
// tables 0x7F6B30 / 0x7F6B14 / 0x7F6B0C / 0x7F6B04), the 0x1D0 allocation and
// the array at 0x8874C0. The ID compared is AbstractTypeClass::ID (+0x24).
#include "type_class_findoralloc_methods.h"

// The array's inline FindItemIndex, written against the layout view.
static inline int WarheadIndexOf(WarheadTypeClass* item)
{
    for (int i = 0; i < WarheadTypeClassArray.Count; i++) {
        if (((WarheadTypeClass**)WarheadTypeClassArray.Items)[i] == item)
            return i;
    }
    return -1;
}

// FUNCTION: GAMEMD 0x40F510
// Returns the index of the warhead named `id`, creating it if absent; -1 for
// the "no type" literals.
int WarheadTypeClass::FUN_0040F510(const char* id)
{
    if (_stricmp(id, "<none>") == 0 || _stricmp(id, "none") == 0)
        return -1;

    for (int i = 0; i < WarheadTypeClassArray.Count; i++) {
        if (_stricmp(id, ((WarheadTypeClass**)WarheadTypeClassArray.Items)[i]->ID) == 0)
            return i;
    }

    return WarheadIndexOf(new WarheadTypeClass(id));
}

// FUNCTION: GAMEMD 0x40F5C0
const char* WarheadTypeClass::FUN_0040F5C0(int index)
{
    if (index == -1 || (unsigned)index >= (unsigned)WarheadTypeClassArray.Count)
        return 0;
    return ((WarheadTypeClass**)WarheadTypeClassArray.Items)[index]->ID;
}

// Retail 0x75DED5..0x75E065 reads these fields and passes Locomotor
// as a 16-byte span; 0x75E027..0x75E04F iterates eleven doubles.
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Wall) == 0x144);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->Wall) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Wood) == 0x147);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->Wood) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Tiberium) == 0x148);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->Tiberium) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, unknown_bool_149) == 0x149);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->unknown_bool_149) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Sparky) == 0x14A);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->Sparky) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Sonic) == 0x14B);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->Sonic) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Fire) == 0x14C);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->Fire) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Conventional) == 0x14D);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->Conventional) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Rocker) == 0x14E);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->Rocker) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, DirectRocker) == 0x14F);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->DirectRocker) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Bright) == 0x150);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->Bright) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, CLDisableRed) == 0x151);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->CLDisableRed) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, CLDisableGreen) == 0x152);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->CLDisableGreen) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, CLDisableBlue) == 0x153);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->CLDisableBlue) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Deform) == 0x98);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->Deform) == 8);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, DeformTreshold) == 0x100);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->DeformTreshold) == 4);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, ProneDamage) == 0xF8);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->ProneDamage) == 8);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Veinhole) == 0x17B);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->Veinhole) == 1);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, ShakeXlo) == 0x17C);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->ShakeXlo) == 4);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, ShakeXhi) == 0x180);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->ShakeXhi) == 4);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, ShakeYlo) == 0x184);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->ShakeYlo) == 4);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, ShakeYhi) == 0x188);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->ShakeYhi) == 4);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Locomotor) == 0x15C);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->Locomotor) == 16);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Verses) == 0xA0);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->Verses) == 88);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, InfDeath) == 0x120);
GG_STATIC_ASSERT(sizeof(((WarheadTypeClass*)0)->InfDeath) == 4);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, AnimList) + offsetof(RawBlock1C, Count) == 0x114);
GG_STATIC_ASSERT(sizeof(((RawBlock1C*)0)->Count) == 4);

// FUNCTION: GAMEMD 0x75DEC0
void WarheadTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1CA0(Wall);
    crc->FUN_004A1CA0(Wood);
    crc->FUN_004A1CA0(Tiberium);
    crc->FUN_004A1CA0(unknown_bool_149);
    crc->FUN_004A1CA0(Sparky);
    crc->FUN_004A1CA0(Sonic);
    crc->FUN_004A1CA0(Fire);
    crc->FUN_004A1CA0(Conventional);
    crc->FUN_004A1CA0(Rocker);
    crc->FUN_004A1CA0(DirectRocker);
    crc->FUN_004A1CA0(Bright);
    crc->FUN_004A1CA0(CLDisableRed);
    crc->FUN_004A1CA0(CLDisableGreen);
    crc->FUN_004A1CA0(CLDisableBlue);
    crc->FUN_004A1D90(Deform);
    crc->FUN_004A1D50(DeformTreshold);
    crc->FUN_004A1D90(ProneDamage);
    crc->FUN_004A1CA0(Veinhole);
    crc->FUN_004A1D50(ShakeXlo);
    crc->FUN_004A1D50(ShakeXhi);
    crc->FUN_004A1D50(ShakeYlo);
    crc->FUN_004A1D50(ShakeYhi);
    crc->FUN_004A1DE0(&Locomotor, 0x10);
    for (int i = 0; i < 0xB; i++)
        crc->FUN_004A1D90(Verses[i]);
    crc->FUN_004A1D50(AnimList.Count);
    crc->FUN_004A1D50(InfDeath);
}
