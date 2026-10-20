// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every offset, slot, constant and call target below is read numerically off
//   the user's retail gamemd.exe v1.001 via the local Ghidra CLI at the five
//   addresses named. None is bound by YRpp or the seed map.
#ifndef GG_MATCH_CORE_SMALL_MISC38_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC38_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);

extern char VT_007E3584;   // VTABLE: GAMEMD 0x7E3584 — this class
extern char VT_007E35A8;   // VTABLE: GAMEMD 0x7E35A8 — the base

// ---------------------------------------------------------------------------
// 0x41C3F0 — snap an all-zero triple to a default.
//
// Three doubles at +0x00, +0x08 and +0x10 are each compared against the
// constant at 0x7E2800, which `ghidra memory read 0x7E2800 8` shows is eight
// zero bytes, i.e. 0.0. Only when all three are zero is the first one set, and
// the value written is the two dwords 0x00000000 / 0x40590000 - the double
// 100.0.
// ---------------------------------------------------------------------------
struct Triple_0041C3F0
{
    double X;   // +0x0000
    double Y;   // +0x0008
    double Z;   // +0x0010
};
GG_STATIC_ASSERT(offsetof(Triple_0041C3F0, Z) == 0x10);

// FUNCTION: GAMEMD 0x41C3F0
void __fastcall FUN_0041C3F0(Triple_0041C3F0* self);

// ---------------------------------------------------------------------------
// 0x426750 — install a delegate and prime it.
// ---------------------------------------------------------------------------
struct Delegate_00426750
{
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();
    virtual void vt_010();
    virtual void vt_014();
    virtual bool vt_018();          // +0x0018
    virtual void vt_01C(int flag);  // +0x001C
    virtual void vt_020();
    virtual void vt_024();
    virtual void vt_028();
    virtual void vt_02C();
    virtual void vt_030();
    virtual void vt_034();          // +0x0034  reached by the 0x426790 teardown
};

// The teardown at 0x426790 reaches two more slots on the delegate and one on
// the sub-object at +0xE0C.
struct SubObject_00426790
{
    virtual void* vt_000(char flags);   // +0x0000  deleting destructor
};

// CLASS IDENTITY (whole-image RTTI sweep, docs/rtti_sweep.md; renamed from
// the raw `Obj_` placeholder). AnimFile's own vtable is 0x7E3584.
//   0x426750 -> AnimFile slot 1 (byte-off 0x4).
//   0x426790 -> AnimFile slot 2 (byte-off 0x8).
// No other table in the image holds them, so the slot is declared on
// AnimFile rather than inherited. The METHOD name is still unknown; only the
// class is proven, so the `FUN_<addr>` member name stays a placeholder.
struct AnimFile_00426750
{
    char*             Vtable;      // +0x0000
    char              _pad004[0x84 - 0x04];
    Delegate_00426750* Delegate;   // +0x0084
    char              Retired;     // +0x0088
    char              Primed;      // +0x0089
    char              _pad08A[0xE0C - 0x8A];
    SubObject_00426790* Sub;       // +0x0E0C
    void*             Buffer;      // +0x0E10

    // FUNCTION: GAMEMD 0x4267F0 — declared as a member so the tail position
    // stays a `CALL`.
    bool FUN_004267F0();

    // FUNCTION: GAMEMD 0x426750
    bool FUN_00426750(Delegate_00426750* delegate);
    // FUNCTION: GAMEMD 0x4266D0 — the destructor: the 0x426790 teardown with
    // this class's vtable installed first and the base's last.
    void FUN_004266D0();
    // FUNCTION: GAMEMD 0x426790
    void FUN_00426790();
};
GG_STATIC_ASSERT(offsetof(AnimFile_00426750, Retired) == 0x88);
GG_STATIC_ASSERT(offsetof(AnimFile_00426750, Sub) == 0xE0C);
GG_STATIC_ASSERT(offsetof(AnimFile_00426750, Buffer) == 0xE10);
GG_STATIC_ASSERT(offsetof(AnimFile_00426750, Delegate) == 0x84);
GG_STATIC_ASSERT(offsetof(AnimFile_00426750, Primed) == 0x89);

// ---------------------------------------------------------------------------
// 0x43A670 — release every slot of the vector at +0x08, then reset the
// sub-object at +0x04.
// ---------------------------------------------------------------------------
struct Item_0043A670
{
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();
    virtual void vt_010();
    virtual void vt_014();
    virtual void vt_018();
    virtual void vt_01C();
    virtual void vt_020(int flag);   // +0x0020
};

struct Sub_0043A670
{
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();           // +0x000C
};

struct Obj_0043A670
{
    char            _pad000[0x4];
    Sub_0043A670    Sub;      // +0x0004  (its vptr, reached as `LEA ECX,[EDI+4]`)
    Item_0043A670** Items;    // +0x0008
    char            _pad00C[0x14 - 0x0C];
    int             Count;    // +0x0014
    char            _pad018[0x1C - 0x18];
    int             field_1C; // +0x001C
    int             field_20; // +0x0020

    // FUNCTION: GAMEMD 0x43A6B0
    void FUN_0043A6B0(int first, int second);
};
GG_STATIC_ASSERT(offsetof(Obj_0043A670, Count) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_0043A670, field_20) == 0x20);
GG_STATIC_ASSERT(offsetof(Obj_0043A670, Sub) == 0x04);
GG_STATIC_ASSERT(offsetof(Obj_0043A670, Items) == 0x08);
GG_STATIC_ASSERT(offsetof(Obj_0043A670, Count) == 0x14);

// FUNCTION: GAMEMD 0x43A670
void __fastcall FUN_0043A670(Obj_0043A670* self);

// FUNCTION: GAMEMD 0x43A6B0 — the same release, then two stack arguments
// stored at +0x1C and +0x20. `RET 8` with the object in ECX makes it a
// __thiscall member rather than the sibling's __fastcall free function.


// ---------------------------------------------------------------------------
// 0x452630 — a three-gate predicate ending in a member call.
// ---------------------------------------------------------------------------
struct Settings_00452630
{
    char _pad000[0x157A];
    char Enabled;   // +0x157A
};
GG_STATIC_ASSERT(offsetof(Settings_00452630, Enabled) == 0x157A);

// CLASS IDENTITY (whole-image RTTI sweep, docs/rtti_sweep.md; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). BuildingClass's own vtable is 0x7E3EBC.
//   0x452630 -> BuildingClass slot 37 (byte-off 0x94).
// That table is the only table in the image that holds it, so the slot is
// declared on BuildingClass and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct BuildingClass_00452630
{
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();
    virtual void vt_010();
    virtual void vt_014();
    virtual void vt_018();
    virtual void vt_01C();
    virtual void vt_020();
    virtual void vt_024();
    virtual void vt_028();
    virtual void vt_02C();
    virtual void vt_030();
    virtual void vt_034();
    virtual void vt_038();
    virtual void vt_03C();
    virtual void vt_040();
    virtual void vt_044();
    virtual void vt_048();
    virtual void vt_04C();
    virtual void vt_050();
    virtual void vt_054();
    virtual void vt_058();
    virtual void vt_05C();
    virtual void vt_060();
    virtual void vt_064();
    virtual void vt_068();
    virtual void vt_06C();
    virtual void vt_070();
    virtual void vt_074();
    virtual void vt_078();
    virtual void vt_07C();
    virtual bool vt_080();          // +0x0080

    char               _pad004[0x6C - 0x04];
    void*              Subject;    // +0x006C
    char               _pad070[0x520 - 0x70];
    Settings_00452630* Settings;   // +0x0520

    // FUNCTION: GAMEMD 0x701140 — declared as a member so the tail position
    // stays a `CALL`.
    bool FUN_00701140();

    // FUNCTION: GAMEMD 0x452630
    bool FUN_00452630();
};
GG_STATIC_ASSERT(offsetof(BuildingClass_00452630, Subject) == 0x6C);
GG_STATIC_ASSERT(offsetof(BuildingClass_00452630, Settings) == 0x520);

// ---------------------------------------------------------------------------
// 0x4739F0 — a constructor: base, then the member at +0x58, then three fields
// and this class's vtable, then one more initialiser that takes the argument.
// ---------------------------------------------------------------------------
extern char VT_007E16B0;   // VTABLE: GAMEMD 0x7E16B0

// FUNCTION: GAMEMD 0x47AA30 — the base constructor.
void __fastcall FUN_0047AA30(void* self);
// The +0x58 member's constructor takes both arguments on the stack (retail
// pushes two zeroes), so it is a __thiscall member rather than a __fastcall
// free function - the free form would put the second argument in EDX.
struct Member_004739F0
{
    char _pad000[0x64 - 0x58];

    // FUNCTION: GAMEMD 0x43AD00
    void FUN_0043AD00(int a, int b);
};

// FUNCTION: GAMEMD 0x7B5440 — maps the argument, __fastcall (retail leaves it
// in ECX from `MOV ECX,[ESP+8]` and pushes nothing).
int __fastcall FUN_007B5440(int value);

struct Obj_004739F0
{
    char* Vtable;   // +0x0000
    char  _pad004[0x58 - 0x04];
    Member_004739F0 Member;      // +0x0058
    int   Reset64;  // +0x0064
    int   Reset68;  // +0x0068

    // FUNCTION: GAMEMD 0x47AE10
    void FUN_0047AE10(int value);

    // FUNCTION: GAMEMD 0x4739F0
    Obj_004739F0* FUN_004739F0(int value);
    // FUNCTION: GAMEMD 0x473A30
    Obj_004739F0* FUN_00473A30(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_004739F0, Reset64) == 0x64);
GG_STATIC_ASSERT(offsetof(Obj_004739F0, Reset68) == 0x68);

#endif  // GG_MATCH_CORE_SMALL_MISC38_METHODS_H
