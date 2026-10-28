// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Small ILocomotion overrides of TunnelLocomotionClass read off retail gamemd.exe
//   v1.001 (ILocomotion vtable 0x7F5A24). Functions are in ascending retail address order.

#include <new.h>
#include "tunnel_locomotion_w3_methods.h"
#include "../_layout/foot_class.h"
#include "loco_foot.h"
#include "../_layout/cell.h"

// FUNCTION: GAMEMD 0x728A60
// Moving, and not in state 1.
bool __stdcall TunnelLocomotionClass::IsMovingNow()
{
    if (IsMoving() && State != 1) {
        return true;
    }
    return false;
}

// GLOBAL: GAMEMD 0xB0F910 -- the unset coordinate the constructor copies into DestCoord.
extern LocoCoord DAT_00B0F910;

// FUNCTION: GAMEMD 0x728A00
TunnelLocomotionClass::TunnelLocomotionClass()
    : State(0), DestCoord(DAT_00B0F910), Timer_28(0), unknown_34(0), unknown_38(0)
{
}

// FUNCTION: GAMEMD 0x72A150
HRESULT __stdcall TunnelLocomotionClass::Load(IStream* pStm)
{
    HRESULT hr = LocomotionClass::Load(pStm);
    if (hr >= 0) {
        new (this) TunnelLocomotionClass(0);
    }
    return hr;
}

// The map's cell lookup and the cell test used by CanEnterCell.
struct TunnelCellView
{
    // FUNCTION: GAMEMD 0x486FF0 (decl; reloc)
    bool FUN_00486FF0();
};
struct TunnelMapView
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) -- MapClass::GetCellAt
    TunnelCellView* FUN_005657A0(const CellStruct* cell);
};
// GLOBAL: GAMEMD 0x87F7E8 -- the map object.
extern TunnelMapView TunnelMap_0087F7E8;
// GLOBAL: GAMEMD 0xA8ED6B -- when set, every cell is enterable.
extern bool DAT_00A8ED6B;

// FUNCTION: GAMEMD 0x728A90
// The target cell while moving, else where the linked unit is now.
LocoCoord __stdcall TunnelLocomotionClass::Destination()
{
    LocoCoord coord;
    if (IsMoving()) {
        coord.X = DestCoord.X;
        coord.Y = DestCoord.Y;
        coord.Z = DestCoord.Z;
        return coord;
    }
    coord = reinterpret_cast<LocoFootView_0055A730*>(LinkedTo)->Location;
    return coord;
}

// FUNCTION: GAMEMD 0x72A090
// Enterable unless the cell test fails; the result code is 7 in that case.
int __stdcall TunnelLocomotionClass::CanEnterCell(int cell)
{
    if (!DAT_00A8ED6B) {
        CellStruct c;
        c.X = reinterpret_cast<CellStruct*>(&cell)->X;
        c.Y = reinterpret_cast<CellStruct*>(&cell)->Y;
        if (!TunnelMap_0087F7E8.FUN_005657A0(&c)->FUN_00486FF0()) {
            return 7;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x72A020
int __stdcall TunnelLocomotionClass::ZGradient()
{
    if (State == 3 || State == 2 || State == 7 || State == 6 || State == 5) {
        return 2;
    }
    return LocomotionClass::ZGradient();
}

// FUNCTION: GAMEMD 0x72A060
bool __stdcall TunnelLocomotionClass::IsToHaveShadow()
{
    if (State == 0 || State == 1 || State == 7 || State == 2 || State == 6) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x72A1A0
int __stdcall TunnelLocomotionClass::InWhichLayer()
{
    return State != 4 ? 2 : 0;
}

// FUNCTION: GAMEMD 0x72A1C0
int __stdcall TunnelLocomotionClass::CanFire()
{
    int result = LocomotionClass::CanFire();
    if (!result && State) {
        result = 7;
    }
    return result;
}

// FUNCTION: GAMEMD 0x72A0E0
// Turn the linked unit's body toward the given facing.
void __stdcall TunnelLocomotionClass::DoTurn(unsigned long dir)
{
    DirStruct d = *reinterpret_cast<DirStruct*>(&dir);
    LinkedTo->PrimaryFacing.SetDesired(d);
}
