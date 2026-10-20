// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x43E7B0: the discovered byte `[ESI+0x83]`, the
//   spied-by bitfield `[ESI+0x210]`, Owner `[ESI+0x21C]`, Type `[ESI+0x520]`
//   and the factory `[ESI+0x524]`; on the house type `[ECX+0xB8]`
//   (ArrayIndex, the shift count); on the building type `[EAX+0xCCE]`
//   (Naval) and `[EAX+0xEB8]`; the vtable slots `[EAX+0x1B8]` (one out
//   pointer), `[EAX+0x458]` (cell reference, position, flags), `[EDX+0x84]`
//   (GetTechnoType) and `[EDX+0x98]` (the name string); the helpers
//   0x4F9A50 (IsAlliedWith), 0x50B730, 0x500510, 0x4CA160 and the
//   fourteen-argument text draw 0x4AED70 on the globals 0x887314 and
//   0x87F6C4; and CurrentPlayer at 0xA83D4C. Names cross-checked against
//   YRpp BuildingClass.h / HouseClass.h (consult-only; NO LICENSE).
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_INFO_TIP_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_INFO_TIP_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// A screen position. The two-argument constructor is what loads both members
// before storing either, in retail's Y-then-X order.
struct Point_0043E7B0
{
    int X;   // +0x0000
    int Y;   // +0x0004

    Point_0043E7B0(int x, int y) { X = x; Y = y; }
    Point_0043E7B0() {}
};
GG_STATIC_ASSERT(sizeof(Point_0043E7B0) == 8);

struct HouseType_0043E7B0
{
    char _pad000[0xB8];   // +0x0000
    int  ArrayIndex;      // +0x00B8
};
GG_STATIC_ASSERT(offsetof(HouseType_0043E7B0, ArrayIndex) == 0xB8);

struct Object_0043E7B0;

struct House_0043E7B0
{
    char                _pad000[0x34];   // +0x0000
    HouseType_0043E7B0* Type;            // +0x0034

    // FUNCTION: GAMEMD 0x4F9A50 (decl; reloc) — HouseClass::IsAlliedWith.
    bool IsAlliedWith(House_0043E7B0* other);
    // FUNCTION: GAMEMD 0x50B730 (decl; reloc) — does this house build its
    // units through a shared factory.
    bool FUN_0050B730();
    // FUNCTION: GAMEMD 0x500510 (decl; reloc) — the factory currently
    // producing for this house.
    Object_0043E7B0* FUN_00500510(int kind, char naval, int flag);
};
GG_STATIC_ASSERT(offsetof(House_0043E7B0, Type) == 0x34);
// GLOBAL: GAMEMD 0xA83D4C — the house of the player at this computer.
extern House_0043E7B0* DAT_00A83D4C;

struct BuildingType_0043E7B0
{
    char _pad000[0xCCE];              // +0x0000
    char Naval;                       // +0x0CCE
    char _padCCF[0xEB8 - 0xCCF];      // +0x0CCF
    int  At_EB8;                      // +0x0EB8
};
GG_STATIC_ASSERT(offsetof(BuildingType_0043E7B0, Naval)  == 0xCCE);
GG_STATIC_ASSERT(offsetof(BuildingType_0043E7B0, At_EB8) == 0xEB8);

// FUNCTION: GAMEMD 0x4CA160 (decl; reloc) — the object a factory is
// currently building, __fastcall.
Object_0043E7B0* __fastcall FUN_004CA160(Object_0043E7B0* factory);

struct TypeVtbl_0043E7B0;

struct Type_0043E7B0
{
    TypeVtbl_0043E7B0* Vptr;   // +0x0000
};
typedef const wchar_t* (Type_0043E7B0::*Fn98_0043E7B0)();
struct TypeVtbl_0043E7B0
{
    char           _pad000[0x98];   // +0x0000
    Fn98_0043E7B0  GetUIName;       // +0x0098
};
GG_STATIC_ASSERT(offsetof(TypeVtbl_0043E7B0, GetUIName) == 0x98);

struct ObjVtbl_0043E7B0;

struct Object_0043E7B0
{
    ObjVtbl_0043E7B0* Vptr;   // +0x0000
};
typedef Type_0043E7B0* (Object_0043E7B0::*Fn84_0043E7B0)();
struct ObjVtbl_0043E7B0
{
    char           _pad000[0x84];   // +0x0000
    Fn84_0043E7B0  GetTechnoType;   // +0x0084
};
GG_STATIC_ASSERT(offsetof(ObjVtbl_0043E7B0, GetTechnoType) == 0x84);

// The drawing surface and the clipping rectangle the tip is drawn into.
struct Surface_0043E7B0;
struct Rect_0043E7B0;
// GLOBAL: GAMEMD 0x887314 — the surface.
extern Surface_0043E7B0* DAT_00887314;
// GLOBAL: GAMEMD 0x87F6C4 — the clipping rectangle.
extern Rect_0043E7B0* DAT_0087F6C4;

// FUNCTION: GAMEMD 0x4AED70 (decl; reloc) — draw a UI string, __fastcall:
// the surface in ECX, the rectangle in EDX and fourteen stack arguments.
void __fastcall FUN_004AED70(Surface_0043E7B0* surface, Rect_0043E7B0* rect,
                             const wchar_t* text, int a3, Point_0043E7B0* pos,
                             unsigned int flags, int a6, int a7, int a8, int a9,
                             int a10, int a11, int a12, int a13, int a14, int a15);

struct Vtbl_0043E7B0;

struct Building_0043E7B0
{
    Vtbl_0043E7B0*        Vptr;                 // +0x0000
    char                  _pad004[0x7F];        // +0x0004
    char                  IsDiscovered;         // +0x0083
    char                  _pad084[0x210 - 0x84];// +0x0084
    unsigned int          SpiedBy;              // +0x0210
    char                  _pad214[8];           // +0x0214
    House_0043E7B0*       Owner;                // +0x021C
    char                  _pad220[0x300];       // +0x0220
    BuildingType_0043E7B0* Type;                // +0x0520
    Object_0043E7B0*      Factory;              // +0x0524

    // FUNCTION: GAMEMD 0x43E7B0 — BuildingClass::DrawInfoTipAndSpiedSelection.
    void DrawInfoTipAndSpiedSelection(Point_0043E7B0* pos, unsigned int flags);
};
GG_STATIC_ASSERT(offsetof(Building_0043E7B0, IsDiscovered) == 0x83);
GG_STATIC_ASSERT(offsetof(Building_0043E7B0, SpiedBy)      == 0x210);
GG_STATIC_ASSERT(offsetof(Building_0043E7B0, Owner)        == 0x21C);
GG_STATIC_ASSERT(offsetof(Building_0043E7B0, Type)         == 0x520);
GG_STATIC_ASSERT(offsetof(Building_0043E7B0, Factory)      == 0x524);

typedef void (Building_0043E7B0::*Fn1B8_0043E7B0)(Point_0043E7B0* out);
typedef void (Building_0043E7B0::*Fn458_0043E7B0)(const Point_0043E7B0& tip,
                                                  Point_0043E7B0* pos,
                                                  unsigned int flags);
struct Vtbl_0043E7B0
{
    char            _pad000[0x1B8];          // +0x0000
    Fn1B8_0043E7B0  At_1B8;                  // +0x01B8
    char            _pad1BC[0x458 - 0x1BC];  // +0x01BC
    Fn458_0043E7B0  At_458;                  // +0x0458
};
GG_STATIC_ASSERT(offsetof(Vtbl_0043E7B0, At_1B8) == 0x1B8);
GG_STATIC_ASSERT(offsetof(Vtbl_0043E7B0, At_458) == 0x458);

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_INFO_TIP_METHODS_H
