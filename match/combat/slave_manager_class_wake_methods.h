// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and slots read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x6B1020: `[ESI+0x24]` (Owner, read
//   afresh before each use), `[ESI+0x5C]` (State), `[ESI+0x60]`
//   (LastScanFrame), the owner's `[ECX+0x21C]` (HouseClass* Owner) with
//   `[EAX+0x1EC]` (IsHumanPlayer, byte), the owner slots `[EDX+0x1BC]`
//   (GetCell, no arguments) with `[EAX+0xEC]` compared to 5 on the cell it
//   returns, and `[ESI+0x338]` called with (out-buffer, int, 0) and its
//   result dereferenced as one dword (a CellStruct); the rules pointer
//   `[0x8871E0]` with `[EAX+0x1790]` and `[EAX+0x1780]`, the frame counter
//   `[0xA8ED84]` and the word pair `[0xB0B5B8]` / `[0xB0B5BA]` (a CellStruct,
//   bytes 00 00 00 00). Owner@0x21C and IsHumanPlayer@0x1EC agree with
//   match/_layout/techno_class.h and match/economy/house_class_lookup_methods.h;
//   State/LastScanFrame with match/combat/slave_manager_class_methods.h (none
//   edited; re-derived here so the TU stands alone). Slot 0x1BC is getCell;
//   slot 0x338 (0x70F8F0 in the leaf
//   vftable at 0x7F4960) is not named by YRpp and stays a
//   placeholder. YRpp names the function (SlaveManagerClass::ShouldWakeUpNow)
//   and RulesClass::Instance.
#ifndef GG_MATCH_COMBAT_SLAVE_MANAGER_CLASS_WAKE_METHODS_H
#define GG_MATCH_COMBAT_SLAVE_MANAGER_CLASS_WAKE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
#include "../core/frame_counter.h"

// CellStruct — a packed map cell coordinate. The user-declared constructor
// makes VC6 return it through a hidden pointer, which is how the slot-0x338
// result comes back (out-buffer pushed, its address returned in EAX).
#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 0x4);

// GLOBAL: GAMEMD 0xB0B5B8 — the "no cell" sentinel the found cell is compared to.
extern CellStruct DAT_00B0B5B8;

// HouseClass — only IsHumanPlayer @0x1EC is read.
struct House_006B1020
{
    char _pad000[0x1EC];   // +0x0000
    bool IsHumanPlayer;    // +0x01EC
};
GG_STATIC_ASSERT(offsetof(House_006B1020, IsHumanPlayer) == 0x1EC);

// CellClass — only the int at +0xEC (the land type; 5 == ore) is read.
struct Cell_006B1020
{
    char _pad000[0xEC];    // +0x0000
    int  At_EC;            // +0x00EC
};
GG_STATIC_ASSERT(offsetof(Cell_006B1020, At_EC) == 0xEC);

// RulesClass — the two slave-miner tunables read here.
struct Rules_006B1020
{
    char _pad0000[0x1780];         // +0x0000
    int  At_1780;                  // +0x1780  a lepton range, divided by 256
    char _pad1784[0x1790 - 0x1784];// +0x1784
    int  At_1790;                  // +0x1790  frames between scans
};
GG_STATIC_ASSERT(offsetof(Rules_006B1020, At_1780) == 0x1780);
GG_STATIC_ASSERT(offsetof(Rules_006B1020, At_1790) == 0x1790);
// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
extern Rules_006B1020* RulesInstance;

// Declaration order matters — see match/_rt/gg_vslot.h.
struct TechnoVtbl_006B1020;

// TechnoClass — the slave miner that owns the manager.
struct Techno_006B1020
{
    TechnoVtbl_006B1020* Vtbl;      // +0x0000
    char                 _pad004[0x21C - 0x4];   // +0x0004
    House_006B1020*      Owner;     // +0x021C
};
GG_STATIC_ASSERT(offsetof(Techno_006B1020, Owner) == 0x21C);

typedef Cell_006B1020* (Techno_006B1020::*Fn1BC_006B1020)();
typedef CellStruct (Techno_006B1020::*Fn338_006B1020)(int range, int flag);

struct TechnoVtbl_006B1020
{
    char _pad000[0x1BC];               // +0x0000
    Fn1BC_006B1020 At_1BC;             // +0x01BC  GetCell
    char _pad1C0[0x338 - 0x1C0];       // +0x01C0
    Fn338_006B1020 At_338;             // +0x0338  nearby-cell search
};
GG_STATIC_ASSERT(offsetof(TechnoVtbl_006B1020, At_1BC) == 0x1BC);
GG_STATIC_ASSERT(offsetof(TechnoVtbl_006B1020, At_338) == 0x338);

class SlaveManagerView_006B1020
{
public:
    char               _base[0x24];          // +0x0000  AbstractClass
    Techno_006B1020*   Owner;                // +0x0024
    char               _pad028[0x5C - 0x28]; // +0x0028
    int                State;                // +0x005C  SlaveManagerStatus
    int                LastScanFrame;        // +0x0060

    // FUNCTION: GAMEMD 0x6B1020
    bool ShouldWakeUpNow();
};
GG_STATIC_ASSERT(offsetof(SlaveManagerView_006B1020, Owner)         == 0x24);
GG_STATIC_ASSERT(offsetof(SlaveManagerView_006B1020, State)         == 0x5C);
GG_STATIC_ASSERT(offsetof(SlaveManagerView_006B1020, LastScanFrame) == 0x60);

#endif  // GG_MATCH_COMBAT_SLAVE_MANAGER_CLASS_WAKE_METHODS_H
