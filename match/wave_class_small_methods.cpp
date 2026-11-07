// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x75F610 and 0x75F7D0.
//
// WaveClass slot 10 (pointer expiry) and slot 6 (Save).
// Address index: 0x75F610 vf_10, 0x75F7D0 Save.

#include <objidl.h>
#include "_layout/wave_class.h"
#include "logicview_87f778.h"
#include "_layout/map_0087f7e8.h"
#include "scenario_class_methods.h"
#include "_layout/cell_class.h"
#include "vector_class_operations.h"
#include "_layout/scenario_ptr_00a8b230.h"

// GLOBAL: GAMEMD 0x87F778
extern LogicView_87F778 DAT_0087F778;
// GLOBAL: GAMEMD 0xA8E9A0
extern bool DAT_00A8E9A0;
// GLOBAL: GAMEMD 0xA8E7AC
extern int DAT_00A8E7AC;

// FUNCTION: GAMEMD 0x75F610
void WaveClass::vf_10(void* target, bool removed)
{
    ObjectClass::vf_10(target, removed);
    if (unknown_1D4 == target)
        unknown_1D4 = 0;
    if (unknown_AC == target)
        unknown_AC = 0;
}

// FUNCTION: GAMEMD 0x75F7D0
HRESULT __stdcall WaveClass::Save(IStream* pStm, BOOL fClearDirty)
{
    AbstractClass::Save(pStm, fClearDirty);
    int count = unknown_1F0.Count;
    HRESULT hr = pStm->Write(&count, 4, 0);
    if (hr >= 0) {
        for (int i = 0; i < count; i++) {
            hr = pStm->Write(&unknown_1F0.Items[i], 4, 0);
            if (hr < 0)
                break;
        }
    }
    return hr;
}

// FUNCTION: GAMEMD 0x75F880
// Returns a constant. Vtable slot 12 of WaveClass (RTTI).
int WaveClass::vf_12()
{
    return 0x240;
}

// FUNCTION: GAMEMD 0x75F890
// Returns a constant. Vtable slot 30 of WaveClass (RTTI).
int WaveClass::vf_30()
{
    return 3;
}

// FUNCTION: GAMEMD 0x75F8A0
// Returns zero. Vtable slot 34 of WaveClass (RTTI).
ObjectTypeClass* WaveClass::vf_34()
{
    return 0;
}

// FUNCTION: GAMEMD 0x75F8B0
bool WaveClass::vf_54(const CoordStruct& coord, int a2)
{
    if (!DAT_00A8E9A0 || !InLimbo || IsOnMap) {
        return false;
    }
    if (DAT_00A8E7AC == 0 && vf_107(DAT_0087F7E8.FUN_00565730(&coord), -1, coord.Z, 0, true) != 0) {
        return false;
    }
    InLimbo = false;
    NeedsRedraw = false;
    vf_109(coord);
    if (!vf_73(1)) {
        return false;
    }
    if (IsAlive) {
        if (vf_30() != -1) {
            DAT_0087F7E8.FUN_004A9720(this);
        }
        DAT_0087F778.FUN_0055BAA0(this, false);
    }
    return true;
}

// FUNCTION: GAMEMD 0x75F980
bool WaveClass::vf_53()
{
    if (!DAT_00A8E9A0 || InLimbo)
        return false;
    vf_55(1);
    vf_73(0);
    DAT_0087F7E8.FUN_004A9770(this);
    DAT_0087F778.FUN_0055BAE0(this);
    vf_71();
    InLimbo = true;
    NeedsRedraw = false;
    return true;
}

// FUNCTION: GAMEMD 0x75F9F0
void WaveClass::vf_69(Point2D* point, RectangleStruct* clip)
{
    if ((DAT_00A8B230->unknown_0000 & 0x1000) && DAT_0087F7E8.IsLocationFogged(&unknown_B4)
        && DAT_0087F7E8.IsLocationFogged(&unknown_C0)) {
        return;
    }
    switch (unknown_B0) {
    case 0:
        FUN_0075FA90(point, clip);
        break;
    case 3:
        FUN_007602E0(point, clip);
        break;
    case 1:
    case 2:
        FUN_007609E0(point, clip);
        break;
    }
}

// FUNCTION: GAMEMD 0x760F50
void WaveClass::vf_23()
{
    switch (unknown_B0) {
    case 3:
        FUN_00762AF0();
        if (--unknown_130 < 0) {
            vf_62();
            return;
        }
        ObjectClass::vf_23();
        return;
    case 0: {
        FUN_00762AF0();
        for (int i = 0; i < unknown_1F0.Count; i++) {
            CoordStruct tmp;
            FUN_0075F330(unknown_1F0.Items[i]->GetCellCoords(&tmp));
        }
        if (--unknown_130 < 0) {
            vf_62();
            return;
        }
        ObjectClass::vf_23();
        return;
    }
    case 1:
    case 2:
        unknown_1D0 -= 6;
        if (unknown_1D0 < 32) {
            vf_62();
        }
        return;
    }
}

// FUNCTION: GAMEMD 0x7631F0
// Returns a constant. Vtable slot 11 of WaveClass (RTTI).
int WaveClass::vf_11()
{
    return 0x2B;
}
