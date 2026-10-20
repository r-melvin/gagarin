// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Seventh translation unit of the FlyLocomotionClass cluster: the
//   __thiscall member at 0x4CF950 that puts the flyer into its take-off
//   state. Its entry point came out of the raw-byte sweep of
//   0x4CC100-0x4D0600, not out of the Ghidra function list; the body ends at
//   0x4CFA69 and 0x4CFA70 is the already-matched landing switch in
//   fly_locomotion_spin_methods.cpp.
//
// Offsets confirmed numerically against the user's retail gamemd.exe v1.001.
// These are object-relative, because the body receives the object's own
// `this` in ECX:
//   +0x0C LinkedTo      `MOV ECX,[ESI+0xC]`, eleven times
//   +0x38 Speed         `MOV [ESI+0x38],EAX`            at 0x4CF9F8
//   +0x50 IsTakingOff   `MOV BYTE PTR [ESI+0x50],0x1`   at 0x4CF9A8
//   +0x51 IsLanding     `MOV [ESI+0x51],AL`             at 0x4CF9A5
// The client's members: +0x9C its location, +0x388 and +0x3A0 the two facing
// slots. Its vtable slots: +0x84 the type object, +0x1C8 the remaining
// travel, +0x1D4 / +0x1D8 / +0x37C / +0x380 the four gates, and +0x2F4 the
// cell it is standing on - which returns a four-byte class through a hidden
// pointer (`LEA EDX,[ESP+4]; PUSH EDX; CALL [EAX+0x2F4]`, then `MOV CX,[EAX]`
// off the returned pointer), so the type is a class of size four, not a
// register-width scalar.
#ifndef GG_MATCH_MOVEMENT_FLY_LOCOMOTION_TAKEOFF_METHODS_H
#define GG_MATCH_MOVEMENT_FLY_LOCOMOTION_TAKEOFF_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// A cell address: two 16-bit components, compared word by word against the
// engine's unset cell.
struct Cell_004CF950
{
    short X;   // +0x00
    short Y;   // +0x02
    Cell_004CF950() {}
};
GG_STATIC_ASSERT(sizeof(Cell_004CF950) == 4);

// GLOBAL: GAMEMD 0x8B3C58 — the engine's unset cell.
extern const Cell_004CF950 UnsetCell_008B3C58;

// Retail calls the cell slot once and reads both components off the returned
// hidden pointer; writing the two comparisons as two call expressions calls
// it twice. A whole-cell comparison is what folds them back into one call.
inline int operator==(const Cell_004CF950& a, const Cell_004CF950& b)
{
    return a.X == b.X && a.Y == b.Y;
}

// A world coordinate: three ints, copied whole out of the client's +0x9C.
struct Coord_004CF950
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
};
GG_STATIC_ASSERT(sizeof(Coord_004CF950) == 12);

// The value a facing slot's reader hands back through a hidden pointer.
struct Dir_004CF950
{
    unsigned int Raw;   // +0x00
    Dir_004CF950() {}
};
GG_STATIC_ASSERT(sizeof(Dir_004CF950) == 4);

struct FacingSlot_004CF950
{
    // FUNCTION: GAMEMD 0x4C9470 (decl; reloc) — the desired direction.
    Dir_004CF950* Desired(Dir_004CF950* out);
    // FUNCTION: GAMEMD 0x4C9300 (decl; reloc) — set the direction.
    void Assign(Dir_004CF950* value);
};

// The client's type object; only the take-off sound index is read.
struct FootType_004CF950;
struct FootTypeVtbl_004CF950;

struct FootType_004CF950
{
    FootTypeVtbl_004CF950* Vtbl;        // +0x0000
    char _pad004[0x52C - 0x4];          // +0x0004
    int  TakeOffSound;                  // +0x052C
};
GG_STATIC_ASSERT(offsetof(FootType_004CF950, TakeOffSound) == 0x52C);

typedef int (FootType_004CF950::*FnTypeInt_004CF950)();

struct FootTypeVtbl_004CF950
{
    char               _pad000[0xBC];   // +0x0000
    FnTypeInt_004CF950 At_BC;           // +0x00BC
};
GG_STATIC_ASSERT(offsetof(FootTypeVtbl_004CF950, At_BC) == 0xBC);

// The locomotor's client object. Declaration order matters - see gg_vslot.h.
struct FootVtbl_004CF950;

struct Foot_004CF950
{
    FootVtbl_004CF950*  Vtbl;               // +0x0000
    char                _pad004[0x9C - 0x4];
    Coord_004CF950      Location;           // +0x009C
    char                _pad0A8[0x388 - 0xA8];
    FacingSlot_004CF950 PrimaryFacing;      // +0x0388
    char                _pad389[0x3A0 - 0x389];
    FacingSlot_004CF950 SecondaryFacing;    // +0x03A0
};
GG_STATIC_ASSERT(offsetof(Foot_004CF950, Location) == 0x9C &&
                 offsetof(Foot_004CF950, PrimaryFacing) == 0x388 &&
                 offsetof(Foot_004CF950, SecondaryFacing) == 0x3A0);

typedef char (Foot_004CF950::*FnChar_004CF950)();
typedef int (Foot_004CF950::*FnInt_004CF950)();
typedef FootType_004CF950* (Foot_004CF950::*FnType_004CF950)();
typedef Cell_004CF950 (Foot_004CF950::*FnCell_004CF950)();

struct FootVtbl_004CF950
{
    char            _pad000[0x84];            // +0x0000
    FnType_004CF950 At_84;                    // +0x0084
    char            _pad088[0x1C8 - 0x88];    // +0x0088
    FnInt_004CF950  At_1C8;                   // +0x01C8
    char            _pad1CC[0x1D4 - 0x1CC];   // +0x01CC
    FnChar_004CF950 At_1D4;                   // +0x01D4
    FnChar_004CF950 At_1D8;                   // +0x01D8
    char            _pad1DC[0x2F4 - 0x1DC];   // +0x01DC
    FnCell_004CF950 At_2F4;                   // +0x02F4
    char            _pad2F8[0x37C - 0x2F8];   // +0x02F8
    FnChar_004CF950 At_37C;                   // +0x037C
    FnChar_004CF950 At_380;                   // +0x0380
};
GG_STATIC_ASSERT(offsetof(FootVtbl_004CF950, At_84) == 0x84 &&
                 offsetof(FootVtbl_004CF950, At_1C8) == 0x1C8 &&
                 offsetof(FootVtbl_004CF950, At_1D4) == 0x1D4 &&
                 offsetof(FootVtbl_004CF950, At_1D8) == 0x1D8 &&
                 offsetof(FootVtbl_004CF950, At_2F4) == 0x2F4 &&
                 offsetof(FootVtbl_004CF950, At_37C) == 0x37C &&
                 offsetof(FootVtbl_004CF950, At_380) == 0x380);

// The global list the client is handed to when it is standing on no cell.
struct Registry_00887888
{
    // FUNCTION: GAMEMD 0x4134A0 (decl; reloc)
    void Add(Foot_004CF950* item);
};
// GLOBAL: GAMEMD 0x887888 — that list.
extern Registry_00887888 Registry_00887888_Instance;

// VocClass::PlayAt — static, __fastcall: ECX = sound index, EDX = coordinate,
// the third argument (0 here) pushed.
// FUNCTION: GAMEMD 0x7509E0 (decl; reloc)
int __fastcall VocClass_PlayAt_004CF950(int index, Coord_004CF950* coords,
                                        int controller);

// FlyLocomotionClass through its own `this`.
struct FlyLocoTakeOff
{
    void*            _vtable_persist;       // +0x0000
    void*            _vtable_locomotor;     // +0x0004
    char             _pad008[0x4];          // +0x0008
    Foot_004CF950*   LinkedTo;              // +0x000C
    char             _pad010[0x38 - 0x10];  // +0x0010
    int              Speed;                 // +0x0038
    char             _pad03C[0x50 - 0x3C];  // +0x003C
    char             IsTakingOff;           // +0x0050
    char             IsLanding;             // +0x0051

    // FUNCTION: GAMEMD 0x4CF950
    void BeginTakeOff();
};
GG_STATIC_ASSERT(offsetof(FlyLocoTakeOff, LinkedTo) == 0x0C &&
                 offsetof(FlyLocoTakeOff, Speed) == 0x38 &&
                 offsetof(FlyLocoTakeOff, IsTakingOff) == 0x50 &&
                 offsetof(FlyLocoTakeOff, IsLanding) == 0x51);

#endif  // GG_MATCH_MOVEMENT_FLY_LOCOMOTION_TAKEOFF_METHODS_H
