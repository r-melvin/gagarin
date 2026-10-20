// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x54E3B0: the aircraft's `[ESI+0x6C4]` (Type) and
//   the type's `[EAX+0xD68]` (MissileSpawn), the crash slot `[EDX+0x3DC]`
//   with one pushed 0, the 8-byte node from `PUSH 8; CALL 0x7C8E17`, the
//   PrimaryFacing at +0x388 handed to 0x4C93D0 (hidden-pointer DirStruct),
//   the GetCell slot `[EDX+0x1BC]` and CellClass::GetNeighbourCell 0x481810
//   with the 3-bit direction, the target's GetCoords slot `[EAX+0x48]` whose
//   X / Y are divided by 256 into a CellStruct for MapClass::GetCellAt
//   0x5657A0 on the map object 0x87F7E8, `[ESI+0x6CA]` (a flag byte set to
//   1) and `[ESI+0x2FC]` (Ammo = 1), and the node vector at +0x0C
//   (Capacity +0x14, IsAllocated +0x19, Count +0x1C, CapacityIncrement
//   +0x20, Resize slot +0x08). Names cross-checked against YRpp Kamikaze.h /
//   TechnoClass.h / TechnoTypeClass.h (consult-only; NO LICENSE), and the
//   sibling match/combat/kamikaze_update_methods.h / kamikaze_load_methods.h.
#ifndef GG_MATCH_COMBAT_KAMIKAZE_TRACKER_ADD_METHODS_H
#define GG_MATCH_COMBAT_KAMIKAZE_TRACKER_ADD_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// CellStruct — the user-declared constructor gives the by-value helper the
// hidden-pointer convention retail shows (words in the parameter slot, dword
// copy into the frame temp whose address is pushed).
struct Cell_0054E3B0
{
    short X;   // +0x0000
    short Y;   // +0x0002
    Cell_0054E3B0() {}
};
GG_STATIC_ASSERT(sizeof(Cell_0054E3B0) == 0x4);

struct Coord_0054E3B0
{
    int X;   // +0x0000
    int Y;   // +0x0004
    int Z;   // +0x0008
};
GG_STATIC_ASSERT(sizeof(Coord_0054E3B0) == 0xC);

inline Cell_0054E3B0 CoordToCell_0054E3B0(const Coord_0054E3B0* c)
{
    Cell_0054E3B0 r;
    r.X = (short)(c->X / 256);
    r.Y = (short)(c->Y / 256);
    return r;
}

// A binary-angle direction returned through a hidden pointer.
struct Dir_0054E3B0
{
    unsigned int Raw;   // +0x0000
    Dir_0054E3B0() {}
};
GG_STATIC_ASSERT(sizeof(Dir_0054E3B0) == 4);

// FacingClass (0x18) — only Current() is called.
struct Facing_0054E3B0
{
    char opaque[0x18];
    // FUNCTION: GAMEMD 0x4C93D0 (decl; reloc) — FacingClass::Current.
    Dir_0054E3B0 Current();
};
GG_STATIC_ASSERT(sizeof(Facing_0054E3B0) == 0x18);

// CellClass — only the neighbour lookup is called.
struct CellClass_0054E3B0
{
    // FUNCTION: GAMEMD 0x481810 (decl; reloc) — CellClass::GetNeighbourCell.
    CellClass_0054E3B0* GetNeighbourCell(int facing);
};

struct Map_0054E3B0
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCellAt.
    CellClass_0054E3B0* GetCellAt(const Cell_0054E3B0& cell);
};
// GLOBAL: GAMEMD 0x87F7E8 — the map instance.
extern Map_0054E3B0 MapInstance_0054E3B0;

// TechnoTypeClass — only MissileSpawn.
struct TechnoType_0054E3B0
{
    char _pad000[0xD68];   // +0x0000
    char MissileSpawn;     // +0x0D68
};
GG_STATIC_ASSERT(offsetof(TechnoType_0054E3B0, MissileSpawn) == 0xD68);

struct AbstractVtbl_0054E3B0;
struct Abstract_0054E3B0
{
    AbstractVtbl_0054E3B0* Vptr;   // +0x0000
};
typedef Coord_0054E3B0* (Abstract_0054E3B0::*Fn48_0054E3B0)(Coord_0054E3B0* out);
struct AbstractVtbl_0054E3B0
{
    char            _pad000[0x48];   // +0x0000
    Fn48_0054E3B0   GetCoords;       // +0x0048
};
GG_STATIC_ASSERT(offsetof(AbstractVtbl_0054E3B0, GetCoords) == 0x48);

struct TechnoVtbl_0054E3B0;

// The kamikaze aircraft: Ammo @0x2FC, PrimaryFacing @0x388, Type @0x6C4,
// the flag byte @0x6CA.
struct Techno_0054E3B0
{
    TechnoVtbl_0054E3B0*  Vptr;                    // +0x0000
    char                  _pad004[0x2F8];          // +0x0004
    int                   Ammo;                    // +0x02FC
    char                  _pad300[0x88];           // +0x0300
    Facing_0054E3B0       PrimaryFacing;           // +0x0388
    char                  _pad3A0[0x6C4 - 0x3A0];  // +0x03A0
    TechnoType_0054E3B0*  Type;                    // +0x06C4
    char                  _pad6C8[2];              // +0x06C8
    unsigned char         At_6CA;                  // +0x06CA

    // The cell one step ahead along the aircraft's facing. Defined in the
    // class body so the inline expansion keeps its own callee-saved save;
    // its use of EDI is what puts retail's PUSH/POP EDI around that branch.
    CellClass_0054E3B0* CellAhead();
};
GG_STATIC_ASSERT(offsetof(Techno_0054E3B0, Ammo)          == 0x2FC);
GG_STATIC_ASSERT(offsetof(Techno_0054E3B0, PrimaryFacing) == 0x388);
GG_STATIC_ASSERT(offsetof(Techno_0054E3B0, Type)          == 0x6C4);
GG_STATIC_ASSERT(offsetof(Techno_0054E3B0, At_6CA)        == 0x6CA);

typedef CellClass_0054E3B0* (Techno_0054E3B0::*Fn1BC_0054E3B0)();
typedef void (Techno_0054E3B0::*Fn3DC_0054E3B0)(int arg);
struct TechnoVtbl_0054E3B0
{
    char             _pad000[0x1BC];            // +0x0000
    Fn1BC_0054E3B0   GetCell;                   // +0x01BC
    char             _pad1C0[0x3DC - 0x1C0];    // +0x01C0
    Fn3DC_0054E3B0   Crash;                     // +0x03DC
};
GG_STATIC_ASSERT(offsetof(TechnoVtbl_0054E3B0, GetCell) == 0x1BC);
GG_STATIC_ASSERT(offsetof(TechnoVtbl_0054E3B0, Crash)   == 0x3DC);

inline CellClass_0054E3B0* Techno_0054E3B0::CellAhead()
{
    int facing = ((PrimaryFacing.Current().Raw >> 12) + 1 >> 1) & 7;
    CellClass_0054E3B0* cell = (this->*Vptr->GetCell)();
    return cell->GetNeighbourCell(facing);
}

// KamikazeControl — the 8-byte node: aircraft and target cell.
struct Node_0054E3B0
{
    Techno_0054E3B0*     Item;   // +0x0000
    CellClass_0054E3B0*  Cell;   // +0x0004
};
GG_STATIC_ASSERT(sizeof(Node_0054E3B0) == 8);

// DynamicVectorClass<KamikazeControl*>: slot +0x08 is Resize(newCapacity,
// array), the allocation flag is the byte at +0x0D.
struct NodeVector_0054E3B0
{
    virtual void vt_000();
    virtual void vt_004();
    virtual bool Resize(int newCapacity, void* array);   // +0x0008

    Node_0054E3B0** Items;              // +0x0004
    int   Capacity;                     // +0x0008
    char  _pad0C[0x1];
    char  IsAllocated;                  // +0x000D
    char  _pad0E[0x10 - 0x0E];
    int   Count;                        // +0x0010
    int   CapacityIncrement;            // +0x0014

    // DynamicVectorClass::AddItem, expanded inline by VC6 at the call site.
    // Same phrasing as match/map/cell_class_tag_methods.h (0x485250).
    bool AddItem(Node_0054E3B0* item)
    {
        int cap = Capacity;
        if (Count < cap
            || ((IsAllocated || cap == 0)
                && CapacityIncrement > 0
                && Resize(cap + CapacityIncrement, 0))) {
            int index = Count++;
            Items[index] = item;
            return true;
        }
        return false;
    }
};
GG_STATIC_ASSERT(offsetof(NodeVector_0054E3B0, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(NodeVector_0054E3B0, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(NodeVector_0054E3B0, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(NodeVector_0054E3B0, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(NodeVector_0054E3B0, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(NodeVector_0054E3B0) == 0x18);

// Kamikaze tracker — the node vector lives at +0x0C.
struct Kamikaze_0054E3B0
{
    char                 _pad000[0xC];   // +0x0000
    NodeVector_0054E3B0  Nodes;          // +0x000C

    // FUNCTION: GAMEMD 0x54E3B0 — Kamikaze::Add.
    void Add(Techno_0054E3B0* item, Abstract_0054E3B0* target);
};
GG_STATIC_ASSERT(offsetof(Kamikaze_0054E3B0, Nodes) == 0xC);

#endif  // GG_MATCH_COMBAT_KAMIKAZE_TRACKER_ADD_METHODS_H
