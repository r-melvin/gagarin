// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 through
//   the local Ghidra CLI at 0x54E4D0: the timer's StartTime at [EBX] and
//   TimeLeft at [EBX+0x8] (the inlined count-down at 0x54E4D8..0x54E4F4), the
//   rewrite at 0x54E507..0x54E50C storing frame / an uninitialised stack
//   dword / 0x1E; the node vector's Items at [EBX+0x10] and Count at
//   [EBX+0x1C]; the node's Item at [node+0] and Target at [node+4]; the
//   aircraft's Ammo at [ESI+0x2FC] (= 1), its PrimaryFacing at ESI+0x388
//   (receiver of FacingClass::Current @0x4C93D0, whose DirStruct comes back
//   through a hidden pointer read as one dword); the three virtuals
//   [EDX+0x1BC] (GetCell, no args), [EDX+0x3C8] (SetTarget, one pushed
//   pointer) and [EAX+0x1E8] (QueueMission, two pushed dwords 1, 0); the
//   neighbour lookup CALL 0x481810 with the 3-bit direction pushed.
//   0xA8ED84 is the frame counter. Names cross-checked against YRpp
//   (every
//   offset reconfirmed above). Ammo @0x2FC and PrimaryFacing @0x388 agree
//   with match/_layout/techno_class.h (not included: this TU needs the
//   pointer-to-member vtable idiom on a locally complete type).
#ifndef GG_MATCH_COMBAT_KAMIKAZE_UPDATE_METHODS_H
#define GG_MATCH_COMBAT_KAMIKAZE_UPDATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

class AbstractClass;

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
#include "../core/frame_counter.h"

// A frame-clocked countdown (YRpp CDTimerClass). The clock slot at +0x04 is
// never written by the constructor, which is exactly what retail shows: the
// temporary's middle dword is copied out of an uninitialised stack slot.
struct CDTimer_0054E4D0
{
    int StartTime;    // +0x00
    int unknown_04;   // +0x04
    int TimeLeft;     // +0x08

    explicit CDTimer_0054E4D0(int duration)
    {
        StartTime = CurrentFrame;
        TimeLeft = duration;
    }

    // What retail inlined at 0x54E4D8: frames left, zero once elapsed. The
    // two members are bound to locals first and the three outcomes are early
    // returns; the single-local `left -= passed` phrasing used elsewhere
    // compiles to the same instructions with EAX/ECX/EDX rotated.
    int GetTimeLeft() const
    {
        int start = this->StartTime;
        int left = this->TimeLeft;
        if (start == -1) {
            return left;
        }
        int passed = CurrentFrame - start;
        if (passed < left) {
            return left - passed;
        }
        return 0;
    }
};
GG_STATIC_ASSERT(offsetof(CDTimer_0054E4D0, TimeLeft) == 0x08);
GG_STATIC_ASSERT(sizeof(CDTimer_0054E4D0) == 0x0C);

// A binary-angle direction. The user-declared constructor is what makes VC6
// return it through a hidden pointer (a POD of this size would come back in
// EAX); retail reads the whole dword off that pointer.
struct Dir_0054E4D0
{
    unsigned int Raw;   // +0x00
    Dir_0054E4D0() {}
};
GG_STATIC_ASSERT(sizeof(Dir_0054E4D0) == 4);

// FacingClass (0x18) — opaque here; only Current() is called.
struct Facing_0054E4D0
{
    char opaque[0x18];

    // FUNCTION: GAMEMD 0x4C93D0 (decl; reloc) — FacingClass::Current.
    Dir_0054E4D0 Current();
};
GG_STATIC_ASSERT(sizeof(Facing_0054E4D0) == 0x18);

// CellClass — opaque; only the neighbour lookup is called.
struct Cell_0054E4D0
{
    // FUNCTION: GAMEMD 0x481810 (decl; reloc) — CellClass::GetNeighbourCell.
    Cell_0054E4D0* GetNeighbourCell(int facing);
};

// Declaration order matters — see match/_rt/gg_vslot.h.
struct UnitVtbl_0054E4D0;

// The kamikaze aircraft (an AircraftClass): Ammo @0x2FC, PrimaryFacing @0x388.
struct Unit_0054E4D0
{
    UnitVtbl_0054E4D0* Vtbl;          // +0x0000
    char               _pad004[0x2FC - 0x004];
    int                Ammo;          // +0x02FC
    char               _pad300[0x388 - 0x300];
    Facing_0054E4D0    PrimaryFacing; // +0x0388
};
GG_STATIC_ASSERT(offsetof(Unit_0054E4D0, Ammo) == 0x2FC);
GG_STATIC_ASSERT(offsetof(Unit_0054E4D0, PrimaryFacing) == 0x388);

typedef Cell_0054E4D0* (Unit_0054E4D0::*Fn1BC_0054E4D0)();
typedef int  (Unit_0054E4D0::*Fn1E8_0054E4D0)(int mission, int immediate);
typedef bool (Unit_0054E4D0::*Fn3C8_0054E4D0)(AbstractClass* target);

struct UnitVtbl_0054E4D0
{
    char            _pad000[0x1BC];              // +0x0000
    Fn1BC_0054E4D0  GetCell;                     // +0x01BC
    char            _pad1C0[0x1E8 - 0x1C0];
    Fn1E8_0054E4D0  QueueMission;                // +0x01E8
    char            _pad1EC[0x3C8 - 0x1EC];
    Fn3C8_0054E4D0  SetTarget;                   // +0x03C8
};
GG_STATIC_ASSERT(offsetof(UnitVtbl_0054E4D0, GetCell) == 0x1BC);
GG_STATIC_ASSERT(offsetof(UnitVtbl_0054E4D0, QueueMission) == 0x1E8);
GG_STATIC_ASSERT(offsetof(UnitVtbl_0054E4D0, SetTarget) == 0x3C8);

// Per-aircraft node: Item at +0, Target at +4 (null = fly straight ahead).
struct KamikazeControl_0054E4D0
{
    Unit_0054E4D0*  Item;      // +0x00
    AbstractClass*  Target;    // +0x04
};
GG_STATIC_ASSERT(offsetof(KamikazeControl_0054E4D0, Target) == 0x04);

// Kamikaze — the suicide-run manager: UpdateTimer then the node vector
// (vptr @0x0C, Items @0x10, Count @0x1C).
struct Kamikaze
{
    CDTimer_0054E4D0            UpdateTimer;    // +0x0000
    void*                       NodesVptr;      // +0x000C
    KamikazeControl_0054E4D0**  NodesItems;     // +0x0010
    char                        _pad014[0x1C - 0x14];
    int                         NodesCount;     // +0x001C

    // FUNCTION: GAMEMD 0x54E4D0
    void Update();
};
GG_STATIC_ASSERT(offsetof(Kamikaze, UpdateTimer) == 0x00);
GG_STATIC_ASSERT(offsetof(Kamikaze, NodesItems) == 0x10);
GG_STATIC_ASSERT(offsetof(Kamikaze, NodesCount) == 0x1C);

#endif  // GG_MATCH_COMBAT_KAMIKAZE_UPDATE_METHODS_H
