// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Third translation unit of the FlyLocomotionClass cluster: the two
//   __thiscall members that drive the touchdown spin and the landing switch.
//   See fly_locomotion_com_methods.h for how the class was named from its own
//   runtime type information. Both entry points came out of a raw-byte sweep
//   of 0x4CC100-0x4D0600 for NOP runs ending on a four-byte boundary; the
//   Ghidra function list gives 0x4CFA70 a length of 0x1D0, which is the
//   distance to the *next listed* address and covers two further bodies.
//
// Offsets confirmed numerically against the user's retail gamemd.exe v1.001.
// These are object-relative, because both bodies receive the object's own
// `this` in ECX:
//   +0x04 the locomotor vptr   `MOV ECX,[ESI+0x4]` / `LEA EAX,[ESI+0x4]` in
//                              0x4CE5A0, which calls its own slot +0x60
//                              through the interface pointer four in
//   +0x0C LinkedTo             `MOV ECX,[ESI+0xC]` in both
//   +0x38 FlightLevel         `MOV DWORD PTR [ESI+0x38],0x0` in 0x4CFA70
//   +0x50 IsTakingOff, +0x51 IsLanding, +0x52 the third flag - the three
//                              byte stores at 0x4CFADF
//   +0x53 IsSpinning           `MOV AL,[ESI+0x53]` in 0x4CE5A0
//   +0x54 SpinRate             `MOV ECX,[ESI+0x54]` in 0x4CE5A0
// LinkedTo's members: +0x6C a signed count, +0x9C a coordinate, +0x388 the
// facing slot, +0x6C4 the type. Its vtable slots: +0x2C the type
// discriminant, +0x1BC, +0x184, +0x484.
#ifndef GG_MATCH_MOVEMENT_FLY_LOCOMOTION_SPIN_METHODS_H
#define GG_MATCH_MOVEMENT_FLY_LOCOMOTION_SPIN_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// A map coordinate, copied whole out of LinkedTo +0x9C.
struct Coord_004CE5A0
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
};
GG_STATIC_ASSERT(sizeof(Coord_004CE5A0) == 12);

// The cell the coordinate resolves to; only one method is reached.
struct Cell_00486920
{
    // FUNCTION: GAMEMD 0x486920 (decl; reloc)
    void Touch();
};

struct MapClass_00565730
{
    // FUNCTION: GAMEMD 0x565730 (decl; reloc)
    Cell_00486920* GetCellAt(Coord_004CE5A0* coord);
};

// GLOBAL: GAMEMD 0x87F7E8 — the map.
extern MapClass_00565730 Map_0087F7E8;

// The value the facing slot's reader hands back: a full dword is read out of
// it, so it is modelled as an int-wide quantity.
struct DirValue_004C93D0
{
    int Value;   // +0x00
};

// The value the facing slot's writer takes: retail stores only sixteen bits
// into the temporary it passes, so the written member is a short.
struct Facing_004C9300
{
    short Raw;         // +0x00
    short Unknown02;   // +0x02
};
GG_STATIC_ASSERT(sizeof(Facing_004C9300) == 4);

struct FacingSlot_004C93D0
{
    // FUNCTION: GAMEMD 0x4C93D0 (decl; reloc)
    DirValue_004C93D0* Current(DirValue_004C93D0* out);
    // FUNCTION: GAMEMD 0x4C9300 (decl; reloc)
    void Assign(Facing_004C9300* value);
};

// LinkedTo's type object; only the gate byte at +0xE0D is read.
struct FootType_004CFA70
{
    char _pad000[0xE0D];   // +0x0000
    char At_E0D;           // +0x0E0D
};
GG_STATIC_ASSERT(offsetof(FootType_004CFA70, At_E0D) == 0xE0D);

// The locomotor's client object. Declaration order matters - see gg_vslot.h.
struct FootVtbl_004CFA70;

struct Foot_004CFA70
{
    FootVtbl_004CFA70* Vtbl;              // +0x0000
    char _pad004[0x6C - 0x4];             // +0x0004
    int  Remaining;                       // +0x006C
    char _pad070[0x9C - 0x70];            // +0x0070
    Coord_004CE5A0 Location;              // +0x009C
    char _pad0A8[0x388 - 0xA8];           // +0x00A8
    FacingSlot_004C93D0 Facing;           // +0x0388
    char _pad389[0x6C4 - 0x389];          // +0x0389
    FootType_004CFA70* Type;              // +0x06C4
};
GG_STATIC_ASSERT(offsetof(Foot_004CFA70, Remaining) == 0x6C &&
                 offsetof(Foot_004CFA70, Location) == 0x9C &&
                 offsetof(Foot_004CFA70, Facing) == 0x388 &&
                 offsetof(Foot_004CFA70, Type) == 0x6C4);

typedef int (Foot_004CFA70::*FnInt_004CFA70)();
typedef void* (Foot_004CFA70::*FnPtr_004CFA70)();
typedef void (Foot_004CFA70::*FnPair_004CFA70)(int, int);

struct FootVtbl_004CFA70
{
    char _pad000[0x2C];                   // +0x0000
    FnInt_004CFA70 At_2C;                 // +0x002C
    char _pad030[0x184 - 0x30];           // +0x0030
    FnInt_004CFA70 At_184;                // +0x0184
    char _pad188[0x1BC - 0x188];          // +0x0188
    FnPtr_004CFA70 At_1BC;                // +0x01BC
    char _pad1C0[0x484 - 0x1C0];          // +0x01C0
    FnPair_004CFA70 At_484;               // +0x0484
};
GG_STATIC_ASSERT(offsetof(FootVtbl_004CFA70, At_2C) == 0x2C &&
                 offsetof(FootVtbl_004CFA70, At_184) == 0x184 &&
                 offsetof(FootVtbl_004CFA70, At_1BC) == 0x1BC &&
                 offsetof(FootVtbl_004CFA70, At_484) == 0x484);

// The locomotor interface, reached through the object's own +0x04 vptr. Only
// the slot at +0x60 is dispatched here; the rest hold slot order.
struct ILoco_004CE5A0
{
    virtual void __stdcall Slot00() = 0;
    virtual void __stdcall Slot04() = 0;
    virtual void __stdcall Slot08() = 0;
    virtual void __stdcall Slot0C() = 0;
    virtual void __stdcall Slot10() = 0;
    virtual void __stdcall Slot14() = 0;
    virtual void __stdcall Slot18() = 0;
    virtual void __stdcall Slot1C() = 0;
    virtual void __stdcall Slot20() = 0;
    virtual void __stdcall Slot24() = 0;
    virtual void __stdcall Slot28() = 0;
    virtual void __stdcall Slot2C() = 0;
    virtual void __stdcall Slot30() = 0;
    virtual void __stdcall Slot34() = 0;
    virtual void __stdcall Slot38() = 0;
    virtual void __stdcall Slot3C() = 0;
    virtual void __stdcall Slot40() = 0;
    virtual void __stdcall Slot44() = 0;
    virtual void __stdcall Slot48() = 0;
    virtual void __stdcall Slot4C() = 0;
    virtual void __stdcall Slot50() = 0;
    virtual void __stdcall Slot54() = 0;
    virtual void __stdcall Slot58() = 0;
    virtual void __stdcall Slot5C() = 0;
    // +0x60 — the shared locomotor move step; true once it has arrived.
    virtual char __stdcall MoveStep() = 0;
};

// FlyLocomotionClass through its own `this`.
struct FlyLocoSpin
{
    void* PersistVptr;         // +0x0000
    void* LocomotorVptr;       // +0x0004
    char  _pad008[0x4];        // +0x0008
    Foot_004CFA70* LinkedTo;   // +0x000C
    char  _pad010[0x28];       // +0x0010
    int   FlightLevel;        // +0x0038
    char  _pad03C[0x14];       // +0x003C
    char  IsTakingOff;         // +0x0050
    char  IsLanding;           // +0x0051
    char  Unknown52;           // +0x0052
    char  IsSpinning;          // +0x0053
    int   SpinRate;            // +0x0054

    // FUNCTION: GAMEMD 0x4CE5A0
    void ProcessSpin();
    // FUNCTION: GAMEMD 0x4CFA70
    void BeginLanding();
};
GG_STATIC_ASSERT(offsetof(FlyLocoSpin, LocomotorVptr) == 0x04 &&
                 offsetof(FlyLocoSpin, LinkedTo) == 0x0C &&
                 offsetof(FlyLocoSpin, FlightLevel) == 0x38 &&
                 offsetof(FlyLocoSpin, IsTakingOff) == 0x50 &&
                 offsetof(FlyLocoSpin, IsLanding) == 0x51 &&
                 offsetof(FlyLocoSpin, Unknown52) == 0x52 &&
                 offsetof(FlyLocoSpin, IsSpinning) == 0x53 &&
                 offsetof(FlyLocoSpin, SpinRate) == 0x54);

// FUNCTION: GAMEMD 0x705D60 (decl; reloc) — the client's own landing gate.
struct FootGate_00705D60
{
    char IsCarryingSomething();
};
// FUNCTION: GAMEMD 0x47C520 (decl; reloc)
struct CellFinder_0047C520
{
    void* ToCell();
};
// FUNCTION: GAMEMD 0x65AD50 (decl; reloc)
struct FootOccupier_0065AD50
{
    char IsOccupied(void* cell);
};

#endif  // GG_MATCH_MOVEMENT_FLY_LOCOMOTION_SPIN_METHODS_H
