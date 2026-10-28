// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Small functions read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. Their owning classes are only partly named, so placeholder
//   names are kept for the receivers.
//   Address index: 0x6D5F30, 0x6D6A90, 0x74D430, 0x74E8A0, 0x74F620, 0x75E440, 0x769D60.

#include "vector_class.h"
#include "vector_class_operations.h"

// ---------------------------------------------------------------------------
// 0x6D5F30: forwards one fixed call through the object held in a global.
struct SlotTarget_006D5F30
{
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2(void* a, int b, void* c, int d, int e);
};
// GLOBAL: GAMEMD 0x887314
extern SlotTarget_006D5F30* DAT_00887314;
// GLOBAL: GAMEMD 0x8872FC
extern int DAT_008872FC;
// GLOBAL: GAMEMD 0x886FA0
extern char DAT_00886FA0[];

// FUNCTION: GAMEMD 0x6D5F30
// Calls slot 2 of the global object with a fixed argument set.
void FUN_006D5F30()
{
    DAT_00887314->vf_2(DAT_00886FA0, DAT_008872FC, DAT_00886FA0, 0, 1);
}

// ---------------------------------------------------------------------------
// 0x6D6A90: map cell lookup then a cell query for the same coordinate.
struct Point_006D6A90
{
    int unknown_0;
    int unknown_4;
};
struct CellView_006D6A90
{
    // FUNCTION: GAMEMD 0x47B3A0 (decl; reloc)
    __int64 FUN_0047B3A0(Point_006D6A90* where);
};
struct MapView_006D6A90
{
    // FUNCTION: GAMEMD 0x565730 (decl; reloc)
    CellView_006D6A90* FUN_00565730(Point_006D6A90* where);
};
// GLOBAL: GAMEMD 0x87F7E8
extern MapView_006D6A90 DAT_0087F7E8;

// FUNCTION: GAMEMD 0x6D6A90
__int64 __stdcall FUN_006D6A90(Point_006D6A90* where)
{
    CellView_006D6A90* cell = DAT_0087F7E8.FUN_00565730(where);
    Point_006D6A90 copy = *where;
    return cell->FUN_0047B3A0(&copy);
}

// ---------------------------------------------------------------------------
// 0x74D430: runs the per-monster routine over the vein-monster registry, last to first.
struct Monster_0074D430
{
    // FUNCTION: GAMEMD 0x74D490 (decl; reloc)
    void FUN_0074D490();
};
// GLOBAL: GAMEMD 0xB1D294
extern Monster_0074D430** DAT_00B1D294;
// GLOBAL: GAMEMD 0xB1D2A0
extern int DAT_00B1D2A0;

// FUNCTION: GAMEMD 0x74D430
void FUN_0074D430()
{
    for (int i = DAT_00B1D2A0 - 1; i >= 0; i--) {
        DAT_00B1D294[i]->FUN_0074D490();
    }
}

// ---------------------------------------------------------------------------
// 0x74E8A0: releases one vein monster's growth blocks.
struct GrowthStack_0074E8A0
{
    int Top;        // +0x00
    int unknown_4;  // +0x04
    int* Data;      // +0x08
};
struct Vein_0074E8A0
{
    char unknown_00[0xAC];
    int unknown_AC;                 // +0xAC
    GrowthStack_0074E8A0* Cells;    // +0xB0
    void* Growth;                   // +0xB4
    char unknown_B8[0xC4 - 0xB8];
    void* Flags;                    // +0xC4
};
void __cdecl FUN_007C8B3D(void* block);

// FUNCTION: GAMEMD 0x74E8A0
void __fastcall FUN_0074E8A0(Vein_0074E8A0* v)
{
    GrowthStack_0074E8A0* stack = v->Cells;
    if (stack) {
        for (int i = 0; i <= stack->Top; i++) {
            stack->Data[i] = 0;
        }
        stack->Top = 0;
        GrowthStack_0074E8A0* cells = v->Cells;
        if (cells) {
            FUN_007C8B3D(cells->Data);
            FUN_007C8B3D(cells);
        }
        v->Cells = 0;
    }
    if (v->Growth) {
        FUN_007C8B3D(v->Growth);
        v->Growth = 0;
    }
    if (v->Flags) {
        FUN_007C8B3D(v->Flags);
        v->Flags = 0;
    }
    v->unknown_AC = 0;
}

// ---------------------------------------------------------------------------
// 0x75E440: drops an entry from the list at +0x104, clearing the current pointer if it is that entry.
struct Holder_0075E440
{
    char unknown_00[0x104];
    DynamicVectorClass<void*> List;     // +0x104
    char unknown_11C[0x140 - 0x11C];
    void* Current;                      // +0x140

    void FUN_0075E440(void* item, int unused);
};

// FUNCTION: GAMEMD 0x75E440
void Holder_0075E440::FUN_0075E440(void* item, int unused)
{
    if (item == Current) {
        Current = 0;
    }
    void* key = item;
    List.RemoveItem(key);
}

// ---------------------------------------------------------------------------
// 0x769D60: whether the first index is below the other object's.
struct Bound_00769D60
{
    int unknown_0;
    int unknown_4;
    unsigned int Limit;  // +0x08
};
struct Cursor_00769D60
{
    int unknown_0;
    Bound_00769D60* Bound;  // +0x04
    unsigned int Index;     // +0x08
};

// FUNCTION: GAMEMD 0x769D60
bool __fastcall FUN_00769D60(Cursor_00769D60* c)
{
    return c->Index < c->Bound->Limit;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x74F620
// Zeroes every slot of a vein growth stack and resets its top.
void __fastcall FUN_0074F620(GrowthStack_0074E8A0* stack)
{
    for (int i = 0; i <= stack->Top; i++) {
        stack->Data[i] = 0;
    }
    stack->Top = 0;
}
