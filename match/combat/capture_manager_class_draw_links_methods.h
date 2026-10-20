// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x472160: `[EDI+0x28]` / `[EDI+0x34]` (ControlNodes
//   Items / Count) and `[EDI+0x48]` (Owner) -- the same three the sibling
//   match/combat/capture_manager_class_draw_methods.h already asserts --
//   `[EAX+0x00]` (node Unit), the count-down timer at node `+0x8` / `+0x10`
//   (`CMP EAX,-1`, `SUB ESI,EAX` against `[0xA8ED84]`), `[ECX+0x83]`
//   (IsSelected on both the owner and the node unit), `LEA EDX,[ECX+0x9C]`
//   with three dword loads (the unit's CoordStruct), `[EAX+0x3DC]` off the
//   type returned by slot `[EDX+0x84]`, `[ECX+0x21C]` plus `0x56F9` (a
//   three-byte colour read word-then-byte) and the owner slot `[ESI+0xB0]`,
//   which returns a CoordStruct through a hidden pointer. YRpp
//   (consult-only, no LICENSE) names CaptureManagerClass::DrawLinks.
#ifndef GG_MATCH_COMBAT_CAPTURE_MANAGER_CLASS_DRAW_LINKS_METHODS_H
#define GG_MATCH_COMBAT_CAPTURE_MANAGER_CLASS_DRAW_LINKS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Coord_00472160 { int X; int Y; int Z; };
GG_STATIC_ASSERT(sizeof(Coord_00472160) == 0xC);

struct Color_00472160 { unsigned char R; unsigned char G; unsigned char B; };
GG_STATIC_ASSERT(sizeof(Color_00472160) == 3);

// GLOBAL: GAMEMD 0xA8ED84 -- Unsorted::CurrentFrame.
extern int CurrentFrame_00472160;

// CDTimerClass -- frame count-down timer (sizeof 0xC); the inlined GetTimeLeft
// read is 0x47219B..0x4721B5.
struct CDTimer_00472160
{
    int StartTime;      // +0x00
    int unknown_04;     // +0x04
    int TimeLeft;       // +0x08

    int GetTimeLeft() const
    {
        int left = TimeLeft;
        if (StartTime != -1) {
            int elapsed = CurrentFrame_00472160 - StartTime;
            if (elapsed < left) {
                left = left - elapsed;
            } else {
                left = 0;
            }
        }
        return left;
    }
};
GG_STATIC_ASSERT(offsetof(CDTimer_00472160, TimeLeft) == 0x8);
GG_STATIC_ASSERT(sizeof(CDTimer_00472160)             == 0xC);

struct UnitVtbl_00472160;

// The unit the link points at.
struct Unit_00472160
{
    UnitVtbl_00472160* Vptr;                  // +0x0000
    char               _pad0004[0x83 - 4];    // +0x0004
    bool               IsSelected;            // +0x0083
    char               _pad0084[0x9C - 0x84]; // +0x0084
    Coord_00472160     Location;              // +0x009C
};
GG_STATIC_ASSERT(offsetof(Unit_00472160, IsSelected) == 0x83);
GG_STATIC_ASSERT(offsetof(Unit_00472160, Location)   == 0x9C);

struct Type_00472160
{
    char _pad0000[0x3DC];     // +0x0000
    int  unknown_3DC;         // +0x03DC  added to the link's Z
};
GG_STATIC_ASSERT(offsetof(Type_00472160, unknown_3DC) == 0x3DC);

typedef Type_00472160* (Unit_00472160::*Fn84_00472160)();

struct UnitVtbl_00472160
{
    char _pad000[0x84];          // +0x0000
    Fn84_00472160 GetType;       // +0x0084
};
GG_STATIC_ASSERT(offsetof(UnitVtbl_00472160, GetType) == 0x84);

struct ControlNode_00472160
{
    Unit_00472160*   Unit;          // +0x0000
    char             _pad0004[4];   // +0x0004  OriginalOwner
    CDTimer_00472160 Timer;         // +0x0008
};
GG_STATIC_ASSERT(offsetof(ControlNode_00472160, Timer) == 0x8);

struct House_00472160
{
    char            _pad0000[0x56F9];    // +0x0000
    Color_00472160  LinkColor;           // +0x56F9
};
GG_STATIC_ASSERT(offsetof(House_00472160, LinkColor) == 0x56F9);

struct OwnerVtbl_00472160;

struct Owner_00472160
{
    OwnerVtbl_00472160* Vptr;                    // +0x0000
    char                _pad0004[0x83 - 4];      // +0x0004
    bool                IsSelected;              // +0x0083
    char                _pad0084[0x21C - 0x84];  // +0x0084
    House_00472160*     Owner;                   // +0x021C

    // FUNCTION: GAMEMD 0x704E40 (decl; reloc) -- the line/link renderer.
    void FUN_00704E40(Coord_00472160 to);
};
GG_STATIC_ASSERT(offsetof(Owner_00472160, IsSelected) == 0x83);
GG_STATIC_ASSERT(offsetof(Owner_00472160, Owner)      == 0x21C);

typedef Coord_00472160 (Owner_00472160::*FnB0_00472160)(
    int index, Coord_00472160 offset, Coord_00472160 from, Color_00472160 color);

struct OwnerVtbl_00472160
{
    char _pad000[0xB0];          // +0x0000
    FnB0_00472160 At_B0;         // +0x00B0
};
GG_STATIC_ASSERT(offsetof(OwnerVtbl_00472160, At_B0) == 0xB0);

struct CaptureManager_00472160
{
    char                    _pad0000[0x28];          // +0x0000
    ControlNode_00472160**  ControlNodes_Items;      // +0x0028
    char                    _pad002C[0x34 - 0x2C];   // +0x002C
    int                     ControlNodes_Count;      // +0x0034
    char                    _pad0038[0x48 - 0x38];   // +0x0038
    Owner_00472160*         Owner;                   // +0x0048

    // FUNCTION: GAMEMD 0x472160 -- CaptureManagerClass::DrawLinks.
    void DrawLinks();
};
GG_STATIC_ASSERT(offsetof(CaptureManager_00472160, ControlNodes_Items) == 0x28);
GG_STATIC_ASSERT(offsetof(CaptureManager_00472160, ControlNodes_Count) == 0x34);
GG_STATIC_ASSERT(offsetof(CaptureManager_00472160, Owner)              == 0x48);

#endif  // GG_MATCH_COMBAT_CAPTURE_MANAGER_CLASS_DRAW_LINKS_METHODS_H
