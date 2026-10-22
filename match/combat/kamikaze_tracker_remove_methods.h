// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x54E590: the node vector's items at `[EDI+0x10]`
//   and count at `[EDI+0x1C]` (a DynamicVectorClass at +0x0C); each node's
//   aircraft at `[EAX]` and cell at `[EAX+0x4]`, both compared against the
//   argument; the argument's slot `CALL [EAX+0x48]` (GetCoords, one out
//   pointer, returned in EAX) and the signed divide by 256 (`CDQ; AND
//   EDX,0xFF; ADD; SAR 8`) into two words at the parameter's home slot; the
//   map singleton as the immediate `MOV ECX,0x87F7E8` feeding CALL 0x5657A0
//   (GetCellAt) with a 4-byte temporary at [ESP+0xC]; the aircraft's slots
//   `CALL [EDX+0x3C8]` (SetTarget, one pushed pointer) and `CALL
//   [EDX+0x1E8]` (QueueMission, pushed 1 and 0); and the CRT free at
//   0x7C8B3D (cdecl, `ADD ESP,4`). Names cross-checked against YRpp
//   Kamikaze::Remove / KamikazeControl
//   and the sibling match/combat/kamikaze_class_methods.h (Nodes
//   @0x0C), re-derived here under this TU's own tags.
#ifndef GG_MATCH_COMBAT_KAMIKAZE_TRACKER_REMOVE_METHODS_H
#define GG_MATCH_COMBAT_KAMIKAZE_TRACKER_REMOVE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Cell_0054E590
{
    short X;   // +0x00
    short Y;   // +0x02
};
GG_STATIC_ASSERT(sizeof(Cell_0054E590) == 4);

struct Coord_0054E590
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
};
GG_STATIC_ASSERT(sizeof(Coord_0054E590) == 0xC);

struct CellClass_0054E590;

struct Map_0054E590
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCellAt.
    CellClass_0054E590* GetCellAt(const Cell_0054E590& cell);
};
// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance (an object, not a pointer).
extern Map_0054E590 DAT_0087F7E8;

// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) — game memory free (cdecl).
void __cdecl GameDelete_0054E590(void* block);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct AbstractVtbl_0054E590;
struct Abstract_0054E590
{
    AbstractVtbl_0054E590* Vtbl;   // +0x00
};
typedef Coord_0054E590* (Abstract_0054E590::*FnCoords_0054E590)(Coord_0054E590* out);
struct AbstractVtbl_0054E590
{
    char              _pad000[0x48];   // +0x0000
    FnCoords_0054E590 GetCoords;       // +0x0048
};
GG_STATIC_ASSERT(offsetof(AbstractVtbl_0054E590, GetCoords) == 0x48);

struct TechnoVtbl_0054E590;
struct Techno_0054E590
{
    TechnoVtbl_0054E590* Vtbl;   // +0x00
};
typedef void (Techno_0054E590::*FnMission_0054E590)(int mission, int arg);
typedef void (Techno_0054E590::*FnTarget_0054E590)(CellClass_0054E590* target);
struct TechnoVtbl_0054E590
{
    char               _pad000[0x1E8];            // +0x0000
    FnMission_0054E590 QueueMission;              // +0x01E8
    char               _pad1EC[0x3C8 - 0x1EC];    // +0x01EC
    FnTarget_0054E590  SetTarget;                 // +0x03C8
};
GG_STATIC_ASSERT(offsetof(TechnoVtbl_0054E590, QueueMission) == 0x1E8);
GG_STATIC_ASSERT(offsetof(TechnoVtbl_0054E590, SetTarget) == 0x3C8);

// KamikazeControl — one suicide aircraft and the cell it dives at.
struct Node_0054E590
{
    Techno_0054E590*    Item;   // +0x00
    CellClass_0054E590* Cell;   // +0x04
};
GG_STATIC_ASSERT(sizeof(Node_0054E590) == 8);

// DynamicVectorClass<KamikazeControl*> — only the members Remove touches.
struct NodeVector_0054E590
{
    void*           Vtbl;      // +0x00
    Node_0054E590** Items;     // +0x04
    int             Capacity;  // +0x08
    char            _pad0C[0x10 - 0x0C];
    int             Count;     // +0x10
    int             CapacityIncrement;   // +0x14
};
GG_STATIC_ASSERT(offsetof(NodeVector_0054E590, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(NodeVector_0054E590, Count) == 0x10);

struct Kamikaze_0054E590
{
    char                _pad000[0x0C];   // +0x0000  the update timer
    NodeVector_0054E590 Nodes;           // +0x000C

    // FUNCTION: GAMEMD 0x54E590
    void Remove(Abstract_0054E590* object);
};
GG_STATIC_ASSERT(offsetof(Kamikaze_0054E590, Nodes) == 0x0C);
GG_STATIC_ASSERT(offsetof(Kamikaze_0054E590, Nodes.Items) == 0x10);
GG_STATIC_ASSERT(offsetof(Kamikaze_0054E590, Nodes.Count) == 0x1C);

#endif  // GG_MATCH_COMBAT_KAMIKAZE_TRACKER_REMOVE_METHODS_H
