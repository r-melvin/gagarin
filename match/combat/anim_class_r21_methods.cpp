// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below
//   (AnimClass slots read from the RTTI table at 0x7E3354).
//
//   Address index: 0x425150, 0x425410, 0x4255B0, 0x4260F0, 0x4261D0, 0x426270, 0x426300

#include "../_layout/anim_class.h"
#include "../_layout/anim_type_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/obj_004a1d30.h"

// The display/map instance at 0x87F7E8, as these bodies call it (ECX = instance).
struct MapView_00425530
{
    // FUNCTION: GAMEMD 0x565730 (decl; reloc) -- the cell under a coordinate.
    CellClass* FUN_00565730(CoordStruct* coord);
    // FUNCTION: GAMEMD 0x578080 (decl; reloc) -- the ground height at a coordinate.
    int FUN_00578080(CoordStruct* coord);
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) -- the cell at a cell coordinate.
    CellClass* FUN_005657A0(CellStruct* cell);
    // FUNCTION: GAMEMD 0x4A9770 (decl; reloc) -- DisplayClass::Remove.
    void FUN_004A9770(ObjectClass* object);
};
// GLOBAL: GAMEMD 0x87F7E8
extern MapView_00425530 DAT_0087F7E8;
// GLOBAL: GAMEMD 0x89A1C0
extern int DAT_0089A1C0;
// An overlay type record, as far as this body reads it.
struct OverlayView_004260F0
{
    char _pad000[0x2A8];
    bool unknown_2A8;   // +0x2A8
};
GG_STATIC_ASSERT(offsetof(OverlayView_004260F0, unknown_2A8) == 0x2A8);
// GLOBAL: GAMEMD 0xA83D84 -- overlay type records by index
extern OverlayView_004260F0** DAT_00A83D84;
// GLOBAL: GAMEMD 0xA8E9AC / 0xA8E9B8 -- AnimClass::Array Items / Count.
extern AnimClass** DAT_00A8E9AC;
extern int DAT_00A8E9B8;
// A tiberium type, as far as this body reads it.
struct TiberiumView_004261D0
{
    char _pad000[0xC0];
    int unknown_C0;     // +0xC0 index of the colour scheme
};
GG_STATIC_ASSERT(offsetof(TiberiumView_004261D0, unknown_C0) == 0xC0);
// A colour scheme record, as far as this body reads it.
struct SchemeView_004261D0
{
    char _pad000[0x30C];
    void* unknown_30C;  // +0x30C the light converter
};
GG_STATIC_ASSERT(offsetof(SchemeView_004261D0, unknown_30C) == 0x30C);
// GLOBAL: GAMEMD 0xB0F4EC -- tiberium types by index
extern TiberiumView_004261D0** DAT_00B0F4EC;
// GLOBAL: GAMEMD 0xB054D4 -- colour scheme records
extern SchemeView_004261D0** DAT_00B054D4;
// GLOBAL: GAMEMD 0x89A1B4
extern int DAT_0089A1B4;
// FUNCTION: GAMEMD 0x4810A0 (decl; reloc) -- which sub-cell spot a coordinate falls in.
int __fastcall FUN_004810A0(CoordStruct* coord);
// FUNCTION: GAMEMD 0x7509E0 (decl; reloc) -- play a sound index at a coordinate (index in ECX, coordinate in EDX).
void* __fastcall FUN_007509E0(int index, const CoordStruct& where, AudioController* controller);

// FUNCTION: GAMEMD 0x425150
// Slot 10 of AnimClass: when a tracked object goes away, drop the references
// this animation holds to it (owner object, type, attached bullet, house).
void AnimClass::vf_10(void* target, bool removed)
{
    ObjectClass::vf_10(target, removed);
    if (OwnerObject == target && target != 0) {
        DAT_0087F7E8.FUN_004A9770(this);
        static_cast<ObjectClass*>(OwnerObject)->vf_24(this);
        OwnerObject = 0;
        UnableToContinue = 1;
        vf_73(0);
    }
    if (Type == target)
        Type = 0;
    if (AttachedBullet == target) {
        AttachedBullet = 0;
        vf_62();
    }
    if (Owner == target) {
        AttachedBullet = 0;
        vf_62();
    }
}

// FUNCTION: GAMEMD 0x425410
// Slot 13 of AnimClass: feed the synchronisation checksum with the owner's
// identity, the tint and adjust values, timing, and the state flags.
void AnimClass::vf_13(Obj_004A1D30* crc)
{
    ObjectClass::vf_13(crc);
    if (OwnerObject) {
        IRTTITypeInfo* info = reinterpret_cast<IRTTITypeInfo*>(static_cast<char*>(OwnerObject) + 4);
        crc->FUN_004A1D50(info->vf_rtti_4());
    }
    crc->FUN_004A1D50(unknown_D0);
    crc->FUN_004A1D50(TintColor);
    crc->FUN_004A1D50(ZAdjust);
    crc->FUN_004A1D50(YSortAdjust);
    crc->FUN_004A1D50(LoopDelay);
    crc->FUN_004A1D90(Accum);
    crc->FUN_004A1D50(AnimFlags);
    crc->FUN_004A1CA0(HasExtras);
    crc->FUN_004A1D50(RemainingIterations);
    crc->FUN_004A1CA0(UseCellLightConvert);
    crc->FUN_004A1CA0(DeleteOnMapCleanup);
    crc->FUN_004A1CA0(UnableToContinue);
    crc->FUN_004A1CA0(SkipProcessOnce);
    crc->FUN_004A1CA0(PowerOff);
}

// A coordinate taken by value (retail copies the animation's location on the stack here).
static inline CoordStruct PlacedAt(const CoordStruct& where)
{
    return where;
}

// FUNCTION: GAMEMD 0x4260F0
// Whether an animation may sit on a cell: reject cells whose occupation bits
// (0xE0) are set, water/impassable land types, and bridge-deck heights that do
// not line up with the animation's own height.
bool AnimClass::FUN_004260F0(CellStruct* cell)
{
    CellClass* target = DAT_0087F7E8.FUN_005657A0(cell);
    if ((target->Flags & 0x100) != 0 && PlacedAt(Location).Z - target->Level * DAT_0089A1C0 > DAT_0089A1C0 * 2) {
        if ((target->AltOccupationBits & 0xE0) != 0)
            return false;
    } else {
        if (target->LandType == 3 || target->LandType == 10 || target->LandType == 4)
            return false;
        if (target->OverlayTypeIndex != -1 && DAT_00A83D84[target->OverlayTypeIndex]->unknown_2A8)
            return false;
        if ((target->OccupationBits & 0xE0) != 0)
            return false;
        if (target->Level * DAT_0089A1C0 - PlacedAt(Location).Z > DAT_0089A1C0 * 2)
            return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x4261D0
// Re-point every animated-tiberium animation at the light converter of the
// colour scheme belonging to the tiberium in the cell it sits on.
void __cdecl FUN_004261D0()
{
    for (int i = 0; i < DAT_00A8E9B8; i++) {
        AnimClass* anim = DAT_00A8E9AC[i];
        if (anim->Type->IsAnimatedTiberium) {
            CoordStruct where = anim->Location;
            int tiberium = DAT_0087F7E8.FUN_00565730(&where)->GetContainedTiberiumIndex();
            if (tiberium != -1 && DAT_00B0F4EC[tiberium] != 0)
                anim->LightConvert = DAT_00B054D4[DAT_00B0F4EC[tiberium]->unknown_C0]->unknown_30C;
        }
    }
}

// FUNCTION: GAMEMD 0x426270
// Slot 60 of AnimClass: mark the sub-cell spot under a coordinate as occupied
// (the upper bit set when the point is at or below the ground height, the
// lower otherwise) and record the owner index.
void AnimClass::vf_60(CoordStruct* coord)
{
    int spot = FUN_004810A0(coord);
    CellClass* cell = DAT_0087F7E8.FUN_00565730(coord);
    if (DAT_0087F7E8.FUN_00578080(coord) + DAT_0089A1B4 <= coord->Z
        && (cell->Flags & 0x100) != 0) {
        cell->AltOccupationBits |= (unsigned char)(1 << spot);
        cell->AltInfantryOwnerIndex = vf_14();
    } else {
        cell->OccupationBits |= (unsigned char)(1 << spot);
        cell->InfantryOwnerIndex = vf_14();
    }
}

// FUNCTION: GAMEMD 0x426300
// Slot 61 of AnimClass: the reverse of slot 60; once no spot bits (0x1C) remain
// the owner index is reset to -1.
void AnimClass::vf_61(CoordStruct* coord)
{
    int spot = FUN_004810A0(coord);
    CellClass* cell = DAT_0087F7E8.FUN_00565730(coord);
    int ground = DAT_0087F7E8.FUN_00578080(coord);
    int top = DAT_0089A1B4 + ground;
    if (top <= coord->Z) {
        cell->AltOccupationBits &= ~(unsigned char)(1 << spot);
        if ((cell->AltOccupationBits & 0x1C) == 0)
            cell->AltInfantryOwnerIndex = -1;
    } else {
        cell->OccupationBits &= ~(unsigned char)(1 << spot);
        if ((cell->OccupationBits & 0x1C) == 0)
            cell->InfantryOwnerIndex = -1;
    }
}

// FUNCTION: GAMEMD 0x4255B0
// Slot 62 of AnimClass: detach from the owner object, end the start sound, and
// (unless inert) play the type's stop sound at the current coordinate.
void AnimClass::vf_62()
{
    if (OwnerObject)
        static_cast<ObjectClass*>(OwnerObject)->vf_24(this);
    FUN_00424B50(0);
    StartSoundAudioController.FUN_00406060();
    if (!IsInert && Type && Type->StopSound != -1) {
        FUN_007509E0(Type->StopSound, vf_18(), &StopSoundAudioController);
    }
    ObjectClass::vf_62();
}
