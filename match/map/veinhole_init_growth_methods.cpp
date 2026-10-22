// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x74DE90.

#include "veinhole_init_growth_methods.h"
#include <string.h>

// The retail MapClass singleton lives at this fixed address.
#define MapInstance (reinterpret_cast<Map_0074DE90*>(0x87F7E8))

// FUNCTION: GAMEMD 0x74DE90  VeinholeMonsterClass::InitVeinGrowthData (__fastcall)
//
// (Re)build the vein-growth bookkeeping. When `rebuild` is set every monster's
// existing growth data is released and freshly allocated: an 8-byte record per
// map cell, an index stack sized to the same cell count, and a per-cell flag
// byte array cleared to zero. The shared growth buffer is (re)allocated and
// cleared, every map object's 0x8000 flag is dropped, each monster re-seeds or
// re-spreads its veins depending on whether it has been initialised, and a
// second pass retires vein overlay 0x7E from every cell that the new buffer no
// longer marks.
//
// PARTIAL (5.9% as scored by the offset-aligned differ; the instruction stream
// is otherwise retail's): the whole residual is one shared-zero register.
// Retail materialises `XOR EBX,EBX` at the top of the rebuild arm and then uses
// EBX for six `CMP reg,EBX` guards and four zero stores (`MOV [ECX+EAX*4-4],EBX`
// in both fill loops, `MOV [ESI],EBX`, `MOV [EAX],EBX`); cl 12.00.8804 emits
// `TEST reg,reg` and immediate zero stores instead. That single extra
// instruction shifts every following byte by two, so the aligned score collapses
// even though only 11 of 187 instructions actually differ — every other
// instruction, operand and block order is exact, including the array-new counter
// preamble (`DEC ESI; MOV [ESP+0x14],ESI` with no ctor loop), both inline
// memsets and the `JL` that jumps past the buffer reload straight onto the
// shared `TEST EAX,EAX`. Variants tried: the zero threaded through the Construct
// and Clear helpers as an `int` parameter (cl folds it back to an immediate,
// identical output), `if (p) p = p->Construct();` vs the ternary, and the
// `new Pair[n]` count read through a local vs the global. This is the recorded
// shared-zero-register class from the fourth batch (0x72ADE0), here in the
// direction where retail forms the register and cl does not.
//
// A later pass tried the allocation-naming lever that took CellClass::FogCell
// from 68.3% to 100%, binding the raw allocation to its own name instead of
// re-assigning the constructed pointer to itself. It changes nothing here:
// still 5.9%, same single missing shared zero. That lever governs which
// register holds a constructed pointer; this residual is a materialisation
// retail performs and cl does not, so the two do not meet.
void InitVeinGrowthData(bool rebuild)
{
    unsigned int size = FUN_0042B1F0();

    if (rebuild) {
        int i;
        for (i = DAT_00B1D2A0 - 1; i >= 0; i--) {
            FUN_0074E8A0(DAT_00B1D294[i]);
        }
        if (DAT_00B1D2F0 != 0) {
            VeinFree(DAT_00B1D2F0);
            DAT_00B1D2F0 = 0;
        }
        for (i = DAT_00B1D2A0 - 1; i >= 0; i--) {
            DAT_00B1D294[i]->Growth = new Pair_0074DE90[DAT_008871E0->CellCount];

            Stack_0074DE90* stack =
                (Stack_0074DE90*)VeinOperatorNew(sizeof(Stack_0074DE90));
            stack = stack ? stack->Construct() : 0;
            DAT_00B1D294[i]->Cells = stack;

            DAT_00B1D294[i]->GrowthFlags = (char*)VeinOperatorNew(size);
            memset(DAT_00B1D294[i]->GrowthFlags, 0, size);

            DAT_00B1D294[i]->Cells->Clear();
        }
    }

    if (DAT_00B1D2F0 == 0) {
        DAT_00B1D2F0 = (char*)VeinOperatorNew(size);
    }

    MapInstance->FUN_00578350();
    for (Obj_0074DE90* o = MapInstance->FUN_00578290(); o != 0;
         o = MapInstance->FUN_00578290()) {
        o->Flags &= 0xFFFF7FFF;
    }

    memset(DAT_00B1D2F0, 0, size);

    for (int j = DAT_00B1D2A0 - 1; j >= 0; j--) {
        Veinhole_0074DE90* monster = DAT_00B1D294[j];
        if (monster->Initialised) {
            FUN_0074E6B0(monster);
        } else {
            FUN_0074E1C0(monster);
        }
    }

    MapInstance->FUN_00578350();
    for (Obj_0074DE90* p = MapInstance->FUN_00578290(); p != 0;
         p = MapInstance->FUN_00578290()) {
        if (p->OverlayTypeIndex == 0x7E
            && DAT_00B1D2F0[FUN_0042B1C0(&p->MapCoords)] == 0) {
            p->OverlayTypeIndex = -1;
        }
        p->Flags &= 0xFFFF7FFF;
    }
}
