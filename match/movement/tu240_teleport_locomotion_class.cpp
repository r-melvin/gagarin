// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit TU240 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x717df0-0x71a1bf,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//
// TeleportLocomotionClass (locomotion module leaf), retail .text
// 0x717E20..0x71A15F. Layout, tables and evidence are in
// _layout/teleport_locomotion_class.h; the shared spine is movement/loco_base.h.
// Rows outside this partition are declared and bound by address only: the
// unit's other initialisers 0x717E60..0x717FE0, vf_11 0x718090, Destination
// 0x7180A0, GetClassID 0x719C60, InWhichLayer 0x719E20, EndPiggyback 0x719EE0,
// AddRef 0x71A0E0, Release 0x71A0F0 and the adjustor thunks.

#include <new.h>
#include "../_layout/teleport_locomotion_class.h"
#include "../core/header_tuning_globals.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new (CRT), called by the new-expressions.
// LIBRARY: GAMEMD 0x7C5F00 -- _ftol (CRT), the double-to-int conversions.
// GLOBAL: GAMEMD 0x7E1718 -- the shared double 1.0 the compiler's literal binds to.
// LIBRARY: GAMEMD 0x7C8B3D -- operator delete (CRT), called by the deleting destructor.
// LIBRARY: GAMEMD 0x7DC720 -- _com_issue_error (comsupp), the _com_ptr_t failure path.
// LIBRARY: OLE32!OleLoadFromStream / OleSaveToStream, IAT 0x7E15F8 / IAT 0x7E15F4.
// GLOBAL: GAMEMD 0x820270 -- IID_IPersistStream (uuid.lib), read by the IPersistStreamPtr.
// GLOBAL: GAMEMD 0x818858 -- IID_IPersist (uuid.lib), read by the IPersistPtr.
// VTABLE: GAMEMD 0x7EAEC0 -- LocomotionClass (IPersistStream side), stored by the inline base constructor in Load.
// VTABLE: GAMEMD 0x7EADF4 -- LocomotionClass (ILocomotion side).

// FUNCTION: GAMEMD 0x55A6F0 (decl; reloc) -- ~LocomotionClass, chained by the deleting destructor.

// ---- run-time initialised copies of the shared tuning globals -------------

// GLOBAL: GAMEMD 0xB0EBE0
extern double DAT_00B0EBE0;
// GLOBAL: GAMEMD 0x7F4FC8
const double DAT_007F4FC8 = 60.0;

// GLOBAL: GAMEMD 0xB0EC30
extern double DAT_00B0EC30;

// GLOBAL: GAMEMD 0xB0EC18
extern double DAT_00B0EC18;

// GLOBAL: GAMEMD 0xB0EC20
extern TuningCoordInit DAT_00B0EC20;

// The cell, as this class uses it.
struct TeleportCellView
{
    virtual void vf_000();
    virtual void vf_004();
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_010();
    virtual void vf_014();
    virtual void vf_018();
    virtual void vf_01C();
    virtual void vf_020();
    virtual void vf_024();
    virtual void vf_028();
    virtual void vf_02C();
    virtual void vf_030();
    virtual void vf_034();
    virtual void vf_038();
    virtual void vf_03C();
    virtual void vf_040();
    virtual void vf_044();
    virtual LocoCoord vf_048();   // +0x048

    // FUNCTION: GAMEMD 0x47C520 (decl; reloc) -- __thiscall, the building on the cell.
    TeleportFootView* FUN_0047C520();
    // FUNCTION: GAMEMD 0x481180 (decl; reloc) -- __thiscall, RET 0x14; a
    // coordinate on this cell for an arriving object.
    LocoCoord FUN_00481180(const LocoCoord& coord, bool a, bool b, int c);
    // FUNCTION: GAMEMD 0x481A00 (decl; reloc) -- __thiscall, RET 4.
    void FUN_00481A00(TeleportFootView* object);
    // FUNCTION: GAMEMD 0x481670 (decl; reloc) -- __thiscall, RET 0x10.
    void FUN_00481670(const LocoCoord* coord, int a, int b, char c);
    // FUNCTION: GAMEMD 0x4865D0 (decl; reloc) -- __thiscall, bool.
    bool FUN_004865D0();
    // FUNCTION: GAMEMD 0x483610 (decl; reloc) -- __thiscall, (+0x140 >> 8) & 1.
    bool FUN_00483610();

    char              unknown_004[0x24 - 0x04];
    TeleportCell      unknown_024;         // +0x024 its own index (`ADD EDX,0x24` @0x007185B2)
    char              unknown_028[0x44 - 0x28];
    int               unknown_044;         // +0x044 a house index (@0x007182CA)
    char              unknown_048[0xE4 - 0x48];
    TeleportFootView* unknown_0E4;         // +0x0E4 the first object (@0x007182B5)
    TeleportFootView* unknown_0E8;         // +0x0E8 the first object on a bridge (@0x0071829E)
    int               unknown_0EC;         // +0x0EC @0x00718856
    char              unknown_0F0[0x140 - 0xF0];
    unsigned int      unknown_140;         // +0x140 flags (@0x00718284)
};
GG_STATIC_ASSERT(offsetof(TeleportCellView, unknown_024) == 0x024);
GG_STATIC_ASSERT(offsetof(TeleportCellView, unknown_044) == 0x044);
GG_STATIC_ASSERT(offsetof(TeleportCellView, unknown_0E4) == 0x0E4);
GG_STATIC_ASSERT(offsetof(TeleportCellView, unknown_0E8) == 0x0E8);
GG_STATIC_ASSERT(offsetof(TeleportCellView, unknown_140) == 0x140);

// The map at 0x87F7E8, as this class uses it.
struct TeleportMapView
{
    // FUNCTION: GAMEMD 0x565730 (decl; reloc) -- the cell under a coordinate.
    TeleportCellView* FUN_00565730(const LocoCoord& coord);
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) -- the cell at an index.
    TeleportCellView* FUN_005657A0(const TeleportCell* cell);
    // FUNCTION: GAMEMD 0x56D230 (decl; reloc) -- __thiscall, RET 0xC.
    int FUN_0056D230(const TeleportCell* cell, int speed, bool flag);
    // FUNCTION: GAMEMD 0x56DC20 (decl; reloc) -- __thiscall, a nearby free cell.
    TeleportCell FUN_0056DC20(const TeleportCell* where, int a, int zone, int speed, int bridge,
                              int b, int c, int d, int e, int f, int g,
                              const TeleportCell* avoid, int h, int i);
    // FUNCTION: GAMEMD 0x578080 (decl; reloc) -- __thiscall, the height at a coordinate.
    int FUN_00578080(const LocoCoord* coord);
    // FUNCTION: GAMEMD 0x578460 (decl; reloc) -- __thiscall, RET 8, bool.
    bool FUN_00578460(const TeleportCell& cell, int a);
};
// GLOBAL: GAMEMD 0x87F7E8
extern TeleportMapView DAT_0087F7E8;

// A house, as 0x718260 reads it.
struct TeleportHouseView
{
    char unknown_000[0x2A9];
    char unknown_2A9;                      // +0x2A9 @0x007184E0

    // FUNCTION: GAMEMD 0x50E1B0 (decl; reloc) -- __thiscall, RET 4, bool.
    bool FUN_0050E1B0(TeleportTypeView* type);
};
GG_STATIC_ASSERT(offsetof(TeleportHouseView, unknown_2A9) == 0x2A9);
// GLOBAL: GAMEMD 0xA83D84 -- the items of the house array.
extern TeleportHouseView** DAT_00A83D84;

// GLOBAL: GAMEMD 0x8871E0
#include "../_layout/rules_class.h"
extern RulesClass* DAT_008871E0;
// GLOBAL: GAMEMD 0xB0EC2C -- a height step, set by the unit's initialiser 0x717F60.
extern int DAT_00B0EC2C;
// GLOBAL: GAMEMD 0xB0EC38 -- a height step, set by the unit's initialiser 0x717EC0.
extern int DAT_00B0EC38;
// GLOBAL: GAMEMD 0xB0EBD8 -- the unit's "no cell" value, zeroed by its initialiser 0x717F90.
extern TeleportCell DAT_00B0EBD8;

// The 0x1C8-byte object Process allocates and constructs with 0x421EA0
// (type, coordinate, then five scalars; RET 0x1C).
struct TeleportAnimView
{
    // FUNCTION: GAMEMD 0x421EA0 (decl; reloc)
    TeleportAnimView(void* type, const LocoCoord& where, int a, int b, int c, int d, char e);
    char opaque[0x1C8];
};
GG_STATIC_ASSERT(sizeof(TeleportAnimView) == 0x1C8);

// An entry of the array at 0xA8ED44 (count at 0xA8ED50), as Process walks it.
struct TeleportListedView
{
    char              unknown_000[0x10C];
    TeleportFootView* unknown_10C;         // +0x10C @0x007193E4

    // FUNCTION: GAMEMD 0x468430 (decl; reloc) -- __thiscall.
    void FUN_00468430();
};
GG_STATIC_ASSERT(offsetof(TeleportListedView, unknown_10C) == 0x10C);
// GLOBAL: GAMEMD 0xA8ED44
extern TeleportListedView** DAT_00A8ED44;
// GLOBAL: GAMEMD 0xA8ED50
extern int DAT_00A8ED50;

// FUNCTION: GAMEMD 0x7509E0 (decl; reloc) -- __fastcall (a sound, where, one int).
void FUN_007509E0(int sound, const LocoCoord& where, int a);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- the square root of a double.
double __cdecl FUN_004CAC40(double value);

// Coordinate difference, read through the two references.
inline LocoCoord operator-(const LocoCoord& a, const LocoCoord& b)
{
    LocoCoord d;
    d.X = a.X - b.X;
    d.Y = a.Y - b.Y;
    d.Z = a.Z - b.Z;
    return d;
}

// The length of a coordinate, truncated to leptons.
inline int TeleportLength(const LocoCoord& c)
{
    return (int)FUN_004CAC40((double)c.X * c.X + (double)c.Y * c.Y + (double)c.Z * c.Z);
}

// True for a foot object (null is not one).
inline bool TeleportIsFoot(TeleportFootView* object)
{
    if (object == 0)
        return false;
    return object->Flags.IsFoot;
}




// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x718000
TeleportLocomotionClass::TeleportLocomotionClass()
    : DestCoord(DAT_00B0EBF8), unknown_28(DAT_00B0EBF8), Moving(0), unknown_35(0),
      unknown_36(0), unknown_38(0), Piggybackee(0)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x718080
bool __stdcall TeleportLocomotionClass::IsMoving()
{
    if (Moving == true)
        return true;
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x718100
void __stdcall TeleportLocomotionClass::MoveTo(LocoCoord to)
{
    if (Foot()->vf_37C() || Foot()->vf_380() || Foot()->vf_1D4() || Foot()->vf_1D8()) {
        Foot()->unknown_5A4 = 0;
        return;
    }
    LocoCoord target = to;
    if (Foot()->unknown_1F8 && Foot()->WhatAmI() == 0xF) {
        TeleportCellView* cell = DAT_0087F7E8.FUN_00565730(target);
        cell->FUN_00481670(&DAT_00B0EBF8, 1, 1, 0);
    }
    FUN_00718B70(&target);
    if (!TeleportSameCoord(unknown_28, DAT_00B0EBF8)) {
        Moving = 1;
        DestCoord = unknown_28;
    } else {
        Foot()->vf_480(0, 1);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x718230
void __stdcall TeleportLocomotionClass::StopMoving()
{
    DestCoord = DAT_00B0EBF8;
    Moving = 0;
    unknown_36 = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x718260
// PARTIAL 4.9% (aligned 57.0%). Retail keeps the house index in EBX and 0 in EDI
// from the loop on, and tests bit 8 with `TEST CH,1`; cl zeroes EBX up front and
// hoists 0x100 into EBP, which shifts every later register and the frame (0x20
// vs 0x28). Tried: plain transcription (48.2% aligned), the two-return foot test
// (kept), cell flag accessors (49.0%).
// The cell lookup `cellHere->FUN_00483610` below is not called: retail loads the
// function's address (`MOV EAX,0x483610; TEST EAX,EAX; SETNZ`), so the flag is
// always true; the source keeps that shape.
bool TeleportLocomotionClass::FUN_00718260(LocoCoord coord, bool flag)
{
    if (!flag) {
        TeleportFootView* object = (DAT_0087F7E8.FUN_00565730(coord)->unknown_140 & 0x100)
            ? DAT_0087F7E8.FUN_00565730(coord)->unknown_0E8
            : DAT_0087F7E8.FUN_00565730(coord)->unknown_0E4;
        int house = DAT_0087F7E8.FUN_00565730(coord)->unknown_044;
        flag = false;
        for (; object; object = object->unknown_030) {
            if (!object->vf_160() && object->WhatAmI() == 0xF && Foot()->WhatAmI() == 0xF) {
                if (TeleportSameCoord(coord, object->vf_048())) {
                    int damage = object->vf_084()->unknown_0A0;
                    object->vf_16C(&damage, 0, DAT_008871E0->C4Warhead, 0, 1, 0, 0);
                }
            } else if (!object->vf_160() && TeleportIsFoot(object)) {
                int damage = object->vf_084()->unknown_0A0;
                object->vf_16C(&damage, 0, DAT_008871E0->C4Warhead, 0, 1, 0, 0);
            } else if (object->vf_160()) {
                int damage = Foot()->vf_084()->unknown_0A0;
                Foot()->vf_16C(&damage, 0, DAT_008871E0->C4Warhead, 0, 1, 0, 0);
            } else if (!TeleportIsFoot(object)) {
                flag = true;
            }
        }
        if ((DAT_0087F7E8.FUN_00565730(coord)->unknown_140 & 0x100)
            && !(DAT_0087F7E8.FUN_00565730(coord)->unknown_140 & 0x200))
            flag = true;
        TeleportCell here = TeleportCellOf(Foot()->vf_048());
        TeleportCellView* cellHere = DAT_0087F7E8.FUN_005657A0(&here);
        bool onBridge = cellHere->FUN_00483610;
        if ((house != -1 && !DAT_00A83D84[house]->unknown_2A9 && !onBridge) || flag) {
            int speed = Foot()->vf_084()->unknown_5B4;
            if (speed == 9)
                speed = 0;
            else if (speed == 2)
                speed = 0;
            else if (speed == 3)
                speed = 5;
            TeleportCell none;
            none.X = 0;
            none.Y = 0;
            TeleportCell dest = TeleportCellOf(coord);
            TeleportCell found = DAT_0087F7E8.FUN_0056DC20(&dest, 1,
                DAT_0087F7E8.FUN_0056D230(&cellHere->unknown_024, speed, onBridge), speed,
                (DAT_0087F7E8.FUN_005657A0(&dest)->unknown_140 >> 8) & 1,
                1, 1, 0, 0, 0, 1, &none, 0, 0);
            LocoCoord centre = DAT_0087F7E8.FUN_00565730(coord)->vf_048();
            int dx = coord.X - centre.X;
            int dy = coord.Y - centre.Y;
            int dz = coord.Z - centre.Z;
            LocoCoord target = DAT_0087F7E8.FUN_005657A0(&found)->vf_048();
            Foot()->unknown_288.X = target.X + dx;
            Foot()->unknown_288.Y = target.Y + dy;
            Foot()->unknown_288.Z = target.Z + dz;
            return false;
        }
    } else {
        if (!TeleportSameCoord(unknown_28, DAT_00B0EBF8)) {
            Foot()->vf_0F4(&unknown_28);
        } else {
            LocoCoord at = Foot()->Location;
            Foot()->vf_0F4(&at);
        }
        unknown_28 = Foot()->unknown_288;
        unknown_28.Z = DAT_0087F7E8.FUN_00578080(&unknown_28);
        if ((DAT_0087F7E8.FUN_00565730(unknown_28)->unknown_140 & 0x100) && !Foot()->unknown_08C) {
            Foot()->unknown_08C = 1;
            unknown_28.Z += DAT_00B0EC2C;
        } else {
            Foot()->unknown_08C = 0;
        }
        Foot()->vf_0F0(&unknown_28);
    }
    if (!TeleportSameCoord(unknown_28, DAT_00B0EBF8)) {
        Foot()->vf_0F0(&unknown_28);
    } else {
        LocoCoord at = Foot()->Location;
        Foot()->vf_0F0(&at);
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7187A0
// PARTIAL 26.4% (aligned 77.1%). Retail shares one 4-byte slot for every cell
// temporary and the damage value (frame 8 vs 0x14) and hoists 0x100 into EDI.
// Tried: plain transcription (kept), a constructor-less cell (no change), one
// reused cell local (25.7%).
void TeleportLocomotionClass::FUN_007187A0(LocoCoord coord)
{
    for (TeleportFootView* object = DAT_0087F7E8.FUN_00565730(coord)->unknown_0E4; object;
         object = object->unknown_030) {
        if (object->vf_160()) {
            int damage = Foot()->vf_084()->unknown_0A0;
            Foot()->vf_16C(&damage, 0, DAT_008871E0->C4Warhead, 0, 1, 0, 0);
        }
    }
    bool blocked = false;
    if (Foot()->vf_084()->unknown_CCE
        && ((DAT_0087F7E8.FUN_00565730(coord)->unknown_140 & 0x100)
            || DAT_0087F7E8.FUN_00565730(coord)->unknown_0EC == 1))
        blocked = true;
    bool special = false;
    if (Foot()->vf_084()->unknown_67C == 3) {
        special = true;
        if (Foot()->vf_084()->unknown_410
            && !Foot()->unknown_21C->FUN_0050E1B0(Foot()->vf_084()))
            special = false;
    }
    TeleportCell cell = TeleportCellOf(coord);
    if (DAT_0087F7E8.FUN_005657A0(&cell)->unknown_0EC == 2 && !special
        && !Foot()->vf_084()->unknown_CCE && Foot()->WhatAmI() != 0xF
        && !(DAT_0087F7E8.FUN_00565730(coord)->unknown_140 & 0x100)
        && DAT_0087F7E8.FUN_00565730(coord)->unknown_0EC != 1) {
        Foot()->unknown_3CD = 1;
        Foot()->vf_3A0();
        if (Foot()->unknown_2D8) {
            Foot()->unknown_2D8->FUN_006B0AE0(Foot()->unknown_428, Foot()->unknown_42C);
            delete Foot()->unknown_2D8;
            Foot()->unknown_2D8 = 0;
        }
        if (Foot()->unknown_428)
            Foot()->vf_0E0(Foot()->unknown_428);
        else if (Foot()->unknown_42C)
            Foot()->vf_0E4(Foot()->unknown_42C);
        return;
    }
    TeleportCell here = TeleportCellOf(coord);
    if (Foot()->vf_1AC(DAT_0087F7E8.FUN_005657A0(&here), -1, -1, 0, 1) == 7 || blocked) {
        TeleportCell at = TeleportCellOf(coord);
        if (DAT_0087F7E8.FUN_005657A0(&at)->FUN_004865D0() && Foot()->WhatAmI() != 0xF) {
            Foot()->unknown_3CD = 1;
            Foot()->vf_3A0();
            if (Foot()->unknown_2D8) {
                Foot()->unknown_2D8->FUN_006B0AE0(Foot()->unknown_428, Foot()->unknown_42C);
                delete Foot()->unknown_2D8;
                Foot()->unknown_2D8 = 0;
            }
        } else {
            int damage = Foot()->vf_084()->unknown_0A0;
            Foot()->vf_16C(&damage, 0, DAT_008871E0->C4Warhead, 0, 1, 0, 0);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x718B70
// PARTIAL 8.3% (aligned 59.7%). The frame is 0x4C in retail vs 0x5C here and the
// `*to` empty case is placed at the end of the function; register naming
// differs from there. Tried: if/else for the height flag (7.6%), the && form
// (kept), a constructor-less cell (no change).
bool TeleportLocomotionClass::FUN_00718B70(const LocoCoord* to)
{
    if (!TeleportSameCoord(unknown_28, DAT_00B0EBF8)) {
        Foot()->vf_0F4(&unknown_28);
    } else {
        LocoCoord at = Foot()->Location;
        Foot()->vf_0F4(&at);
    }
    LocoCoord target = *to;
    if (TeleportSameCoord(*to, DAT_00B0EBF8)) {
        unknown_28 = *to;
    } else {
        bool high = (DAT_0087F7E8.FUN_00565730(target)->unknown_140 & 0x100)
            && Foot()->Location.Z > DAT_0087F7E8.FUN_00578080(&target) + DAT_00B0EC38 * 3;
        if (Foot()->WhatAmI() == 0xF) {
            bool onTarget = false;
            if (Foot()->vf_200())
                Foot()->vf_1EC();
            if (Foot()->vf_184() == 8 || Foot()->vf_184() == 9 || Foot()->vf_184() == 7
                || Foot()->vf_184() == 0x19) {
                TeleportFootView* object = Foot()->unknown_5A4;
                if (object && object->WhatAmI() == 1
                    && TeleportSameCell(object->vf_1B8(), TeleportCellOf(*to)))
                    onTarget = true;
                object = Foot()->unknown_5A4;
                if (object && object->WhatAmI() == 2
                    && TeleportSameCell(object->vf_1B8(), TeleportCellOf(*to)))
                    onTarget = true;
                object = Foot()->unknown_5A4;
                if (object && object->WhatAmI() == 6
                    && DAT_0087F7E8.FUN_00565730(*to)->FUN_0047C520() == object)
                    onTarget = true;
            }
            LocoCoord old = unknown_28;
            unknown_28 = DAT_0087F7E8.FUN_00565730(target)->FUN_00481180(target, onTarget, high, 0);
            TeleportCell cell = TeleportCellOf(unknown_28);
            if (Foot()->vf_1AC(DAT_0087F7E8.FUN_005657A0(&cell), -1, -1, 0, 1))
                unknown_28 = DAT_00B0EBF8;
            DAT_0087F7E8.FUN_00565730(old)->vf_048();
            if (TeleportSameCoord(unknown_28, DAT_00B0EBF8)) {
                TeleportFootView* object = Foot()->unknown_5A4;
                if (object && object->Flags.unknown_14_1) {
                    int speed = Foot()->vf_084()->unknown_5B4;
                    TeleportCell objectCell = TeleportCellOf(object->vf_04C(0));
                    TeleportCellView* footCell = DAT_0087F7E8.FUN_00565730(Foot()->vf_04C(0));
                    bool flag = Foot()->vf_0BC(0);
                    TeleportCell none;
                    none.X = 0;
                    none.Y = 0;
                    TeleportCell found = DAT_0087F7E8.FUN_0056DC20(&objectCell,
                        Foot()->vf_084()->unknown_67C,
                        DAT_0087F7E8.FUN_0056D230(&footCell->unknown_024, speed, flag), speed,
                        (DAT_0087F7E8.FUN_005657A0(&objectCell)->unknown_140 >> 8) & 1,
                        1, 1, 0, 1, 0, 1, &none, 0, 0);
                    if (!TeleportSameCell(found, DAT_00B0EBD8)) {
                        unknown_28 = DAT_0087F7E8.FUN_005657A0(&found)->FUN_00481180(
                            DAT_0087F7E8.FUN_005657A0(&found)->vf_048(), onTarget, high, 0);
                    }
                }
            }
        } else if (Foot()->unknown_27C) {
            Foot()->vf_0F0(&unknown_28);
        } else {
            int speed = Foot()->vf_084()->unknown_5B4;
            TeleportCell cell = TeleportCellOf(*to);
            if (!TeleportSameCell(cell, DAT_00B0EBD8)
                && Foot()->vf_1AC(DAT_0087F7E8.FUN_005657A0(&cell), -1, -1, 0, 1)) {
                int zone = DAT_0087F7E8.FUN_0056D230(&cell, speed, high);
                TeleportCell none;
                none.X = 0;
                none.Y = 0;
                cell = DAT_0087F7E8.FUN_0056DC20(&cell, Foot()->vf_084()->unknown_67C, zone, speed,
                                                 high, 1, 1, 0, 0, 0, 1, &none, 0, 0);
            }
            if (!TeleportSameCell(cell, DAT_00B0EBD8)) {
                Foot()->vf_0F4(&unknown_28);
                TeleportCell at = TeleportCellOf(DAT_0087F7E8.FUN_005657A0(&cell)->vf_048());
                unknown_28.X = at.X * 256 + 128;
                unknown_28.Y = at.Y * 256 + 128;
                unknown_28.Z = 0;
                unknown_28.Z = DAT_0087F7E8.FUN_00578080(&unknown_28);
                Foot()->vf_0F0(&unknown_28);
            }
        }
    }
    if (!TeleportSameCoord(unknown_28, DAT_00B0EBF8)) {
        Foot()->vf_0F0(&unknown_28);
        return true;
    }
    LocoCoord at = Foot()->Location;
    Foot()->vf_0F0(&at);
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7192C0
void __stdcall TeleportLocomotionClass::DoTurn(unsigned long dir)
{
    Foot()->PrimaryFacing.SetDesired(TeleportDir(dir));
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7192F0
// PARTIAL 6.5% (aligned 79.9%). Retail's frame is 0x20 vs 0x34 here (it shares
// the coordinate temporaries); the code is otherwise in retail's block order.
// Tried: the unknown_27C test first (75.5% aligned) and inverted (kept); only
// two attempts so far.
bool __stdcall TeleportLocomotionClass::Process()
{
    int distance = 0;
    if (Foot()->unknown_271 && unknown_38 == 0 && Foot()->unknown_280 == 0) {
        vf_10();
        return false;
    }
    if (unknown_38 == 0 && Foot()->unknown_280) {
        unknown_38 = Foot()->unknown_280;
        return false;
    }
    if (!Foot()->unknown_27C) {
        if (unknown_38 <= 0) {
            if (!IsMoving())
                return false;
            if (TeleportSameCoord(Foot()->Location, unknown_28)
                || TeleportSameCoord(unknown_28, DAT_00B0EBF8)) {
                Foot()->vf_480(0, 1);
                StopMoving();
                return false;
            }
            Foot()->FUN_0070D4A0();
            for (int i = DAT_00A8ED50 - 1; i >= 0; i--) {
                TeleportListedView* entry = DAT_00A8ED44[i];
                if (entry->unknown_10C == Foot())
                    entry->FUN_00468430();
            }
            new TeleportAnimView(DAT_008871E0->WarpOut, Foot()->Coord_09C(), 0, 1, 0x600, 0, 0);
            distance = TeleportLength(Foot()->vf_048() - unknown_28);
            unknown_3C = TeleportTimer(0);
            if (DAT_008871E0->ChronoTrigger)
                unknown_3C = TeleportTimer(distance / DAT_008871E0->ChronoDistanceFactor);
            unknown_3C = (unknown_3C.GetTimeLeft() > DAT_008871E0->ChronoMinimumDelay)
                ? unknown_3C : TeleportTimer(DAT_008871E0->ChronoMinimumDelay);
            if (distance < DAT_008871E0->ChronoRangeMinimum)
                unknown_3C = TeleportTimer(DAT_008871E0->ChronoMinimumDelay);
            Foot()->unknown_271 = 1;
            if (Foot()->WhatAmI() == 1 && Foot()->unknown_6C4->unknown_E0E) {
                unknown_3C = TeleportTimer(0);
                Foot()->unknown_271 = 0;
            }
            if (Foot()->unknown_694)
                Foot()->unknown_694->unknown_69C->FUN_0062A4A0();
            Foot()->vf_124(0);
            int sound = Foot()->vf_084()->unknown_578;
            if (sound != -1 || (sound = DAT_008871E0->ChronoOutSound) != -1)
                FUN_007509E0(sound, Foot()->Coord_09C(), 0);
            Foot()->vf_1B4(&unknown_28);
            TeleportCell cell = TeleportCellOf(unknown_28);
            TeleportCellView* there = DAT_0087F7E8.FUN_005657A0(&cell);
            Foot()->vf_1B4(&unknown_28);
            if (there->unknown_140 & 0x100)
                Foot()->unknown_08C = 1;
            else
                Foot()->unknown_08C = 0;
            Foot()->vf_1CC(0);
            Foot()->vf_124(1);
            sound = Foot()->vf_084()->unknown_574;
            if (sound != -1 || (sound = DAT_008871E0->ChronoInSound) != -1)
                FUN_007509E0(sound, Foot()->Coord_09C(), 0);
            Foot()->vf_18C(2);
            StopMoving();
            there->FUN_00481A00(Foot());
            Foot()->vf_480(0, 1);
            new TeleportAnimView(DAT_008871E0->WarpOut, Foot()->Coord_09C(), 0, 1, 0x600, 0, 0);
            Foot()->unknown_280 = 0;
            return false;
    }
    } else {
        if (unknown_38 == 0) {
            Foot()->unknown_270 = 1;
            unknown_3C = TeleportTimer(60);
            unknown_38++;
            return false;
        }
    }
    switch (unknown_38) {
    case 1:
        vf_10();
        return false;
    case 2: {
        new TeleportAnimView(DAT_008871E0->WarpOut, Foot()->Coord_09C(), 0, 1, 0x600, 0, 0);
        Foot()->vf_124(0);
        int sound = Foot()->vf_084()->unknown_578;
        if (sound != -1 || (sound = DAT_008871E0->ChronoOutSound) != -1)
            FUN_007509E0(sound, Foot()->Coord_09C(), 0);
        Foot()->unknown_271 = 1;
        Foot()->unknown_27C = 0;
        Foot()->unknown_270 = 0;
        Foot()->unknown_08C = 0;
        bool placed = FUN_00718260(Foot()->unknown_288, false);
        unknown_38++;
        if (placed)
            unknown_38++;
        return false;
    }
    case 3:
        if (FUN_00718260(Foot()->unknown_288, false))
            unknown_38++;
        Foot()->unknown_284 = DAT_008871E0->ChronoDelay;
        return false;
    case 4:
        FUN_00718260(Foot()->unknown_288, true);
        Foot()->vf_1B4(&unknown_28);
        Foot()->vf_1CC(0);
        Foot()->vf_124(1);
        unknown_38++;
        return false;
    case 5: {
        Foot()->vf_1B4(&unknown_28);
        Foot()->vf_1CC(0);
        Foot()->vf_124(1);
        int sound = Foot()->vf_084()->unknown_574;
        if (sound != -1 || (sound = DAT_008871E0->ChronoInSound) != -1)
            FUN_007509E0(sound, Foot()->Coord_09C(), 0);
        if (!DAT_0087F7E8.FUN_00578460(Foot()->vf_1B8(), 1))
            Foot()->unknown_3D5 = 0;
        if (Foot()->unknown_280 == 0)
            FUN_007187A0(unknown_28);
        if (Foot()->unknown_090) {
            Foot()->vf_18C(2);
            StopMoving();
            Foot()->unknown_428 = 0;
            Foot()->unknown_42C = 0;
            Foot()->FUN_0070C610(0);
            Foot()->vf_480(0, 1);
            unknown_3C = TeleportTimer(Foot()->unknown_284);
            new TeleportAnimView(DAT_008871E0->WarpOut, Foot()->Coord_09C(), 0, 1, 0x600, 0, 0);
            unknown_38++;
        }
        return false;
    }
    case 6:
        vf_10();
        return false;
    case 7:
        Foot()->unknown_271 = 0;
        Foot()->FUN_0070C610(0);
        Foot()->vf_480(0, 1);
        Moving = false;
        Foot()->unknown_280 = 0;
        unknown_38 = 0;
        break;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x719BF0
// PARTIAL 80.6% (mnemonic multiset identical). Retail keeps TimeLeft in EAX and
// the elapsed frames in ECX; cl swaps the two. Tried four forms of the timer
// read (early return, local start, the rocket form, a conversion operator).
void __stdcall TeleportLocomotionClass::vf_10()
{
    if (unknown_3C.GetTimeLeft() == 0) {
        Foot()->unknown_271 = 0;
        if (Foot()->unknown_2B4 == 0) {
            Foot()->FUN_0070F770();
            if (!Foot()->FUN_00709480())
                Foot()->vf_484(0, 1);
        }
        if (unknown_38 > 0)
            unknown_38++;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x719CA0
HRESULT __stdcall TeleportLocomotionClass::Load(IStream* pStm)
{
    HRESULT hr = LocomotionClass::Load(pStm);
    if (hr >= 0) {
        new (this) TeleportLocomotionClass(0);
        bool hasPiggyback;
        pStm->Read(&hasPiggyback, 1, 0);
        if (hasPiggyback)
            hr = OleLoadFromStream(pStm, IID_ILocomotion, (void**)&Piggybackee);
    }
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x719D40
HRESULT __stdcall TeleportLocomotionClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = LocomotionClass::Save(pStm, fClearDirty);
    if (hr >= 0) {
        bool hasPiggyback;
        if (Piggybackee != 0) {
            hasPiggyback = true;
            pStm->Write(&hasPiggyback, 1, 0);
            IPersistStreamPtr persist(Piggybackee);
            return OleSaveToStream(persist, pStm);
        }
        hasPiggyback = false;
        pStm->Write(&hasPiggyback, 1, 0);
    }
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x719E30
HRESULT __stdcall TeleportLocomotionClass::QueryInterface(REFIID riid, void** ppv)
{
    HRESULT hr = LocomotionClass::QueryInterface(riid, ppv);
    if (hr == E_NOINTERFACE) {
        if (riid == IID_IPiggyback)
            *ppv = static_cast<IPiggyback*>(this);
        if (*ppv == 0)
            return E_NOINTERFACE;
        AddRef();
        hr = S_OK;
    }
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x719E90
HRESULT __stdcall TeleportLocomotionClass::BeginPiggyback(ILocomotion* loco)
{
    if (!loco)
        return E_POINTER;
    if (Piggybackee == 0) {
        Piggybackee = loco;
        return S_OK;
    }
    return E_FAIL;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x719F30
bool __stdcall TeleportLocomotionClass::IsOkToEnd()
{
    if (!IsMoving() && Piggybackee != 0 && !unknown_35 && !Foot()->unknown_27C
        && unknown_38 == 0 && !Foot()->unknown_6AD)
        return true;
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x719F80
HRESULT __stdcall TeleportLocomotionClass::PiggybackCLSID(CLSID* out)
{
    if (!out)
        return E_POINTER;
    if (Piggybackee) {
        IPersistPtr persist(Piggybackee);
        if (persist == 0)
            return E_FAIL;
        return persist->GetClassID(out);
    }
    IPersistPtr persist(static_cast<LocomotionClass*>(this));
    if (persist == 0)
        return E_FAIL;
    return persist->GetClassID(out);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71A090
// PARTIAL 84.0% (multiset identical). Retail loads the copied Z before the
// LinkedTo pointer; cl loads LinkedTo first. Tried: a named local (kept), an
// assignment to a declared local, passing the returned value by reference
// (8.0%, no local copy).
void __stdcall TeleportLocomotionClass::MarkAllOccupationBits(int mark)
{
    if (mark == 0) {
        LocoCoord head;
        head = HeadToCoord();
        Foot()->vf_0F4(&head);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71A100
bool __stdcall TeleportLocomotionClass::IsPiggybacking()
{
    return Piggybackee != 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71A120
int TeleportLocomotionClass::Size()
{
    return sizeof(*this);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71A130
// The scalar deleting destructor (synthetic): the inline destructor releases
// Piggybackee and chains ~LocomotionClass 0x55A6F0.

// SYNTHETIC: GAMEMD 0x71A160 -- compiler-generated ILocomotion QI adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x71A170 -- compiler-generated ILocomotion AddRef adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x71A180 -- compiler-generated ILocomotion Release adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x71A190 -- compiler-generated IPiggyback QI adjustor thunk (this -= 0x18).
// SYNTHETIC: GAMEMD 0x71A1A0 -- compiler-generated IPiggyback AddRef adjustor thunk (this -= 0x18).
// SYNTHETIC: GAMEMD 0x71A1B0 -- compiler-generated IPiggyback Release adjustor thunk (this -= 0x18).
