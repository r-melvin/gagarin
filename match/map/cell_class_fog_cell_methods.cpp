// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x486A70.

#include "cell_class_fog_cell_methods.h"

// The retail MapClass singleton lives at this fixed address.
#define MapInstance (reinterpret_cast<MapClass_00486A70*>(0x87F7E8))

// FUNCTION: GAMEMD 0x486A70  CellClass::FogCell (__thiscall)
//
// Freeze what this cell currently shows into a fog snapshot. Only when the
// scenario's 0x1000 flag is set: the same diagonal stripe CleanFog walks
// (i = 1,3,..,15 with the coord stepping (+1,+1)) is visited, and for every
// cell whose Level sits in [i-2, i] and that is not already fogged a fresh
// fogged-object vector is built, every occupier of that cell is asked to
// record itself into it, the fog bit is set, and the vector is kept only if
// anything landed in it.
//
// MATCHED 100% (123/123 instructions; 358/375 bytes, 5 relocation slots).
//
// The lever was the allocation's *name*, not the register allocator. The
// earlier spelling re-assigned the allocation to its own variable
// (`FogVec* fogged = (FogVec*)op_new(0x18); fogged = fogged ? fogged->Construct()
// : 0;`), which makes cl home the raw `operator new` result in `fogged`'s
// callee-saved register immediately (`MOV ESI,EAX` ahead of `ADD ESP,4`) and
// run the seven constructor stores through that register. Retail keeps the
// result in EAX across the null test and all seven stores and only copies it
// into the vector register at the join (`MOV EDI,EAX; JMP` / `XOR EDI,EDI`) —
// the ordinary `T* p = new T;` shape, where the constructed value is a fresh
// name. Binding the raw allocation to its own `void* raw` and naming the
// constructed pointer separately reproduces it, and the ESI/EDI exchange that
// ran through the rest of the body (the 0x400000 literal, the occupier cursor
// and the vector) fell into line by itself: 68.3% to 100% on that one edit.
//
// Four spellings of the same split all reach 100% and are interchangeable:
// the `void* raw` ternary used here; a free `FogConstruct(p)` taking the
// vector as a parameter; an if/else that calls `p->Construct()` for effect and
// then assigns `fogged = p`; and an inline `FogNew()` helper holding the whole
// allocate-and-construct pair. Only the self-assigning control stays at 68.3%.
//
// The tail-merge diagnostic from the eleventh batch does NOT apply here: there
// is a single return, retail's four callee-saved pushes are already sunk below
// the scenario-flag test, and our prologue reproduced their order and offsets
// exactly even at 68.3%. The register exchange was downstream of the naming.
// Previously tried without effect: `if (p) p = p->Construct();` in place of the
// ternary (0%), a `FogVecBase` temporary struct-assigned inside Construct
// (adds 12 frame bytes, 0%), and the vector pointer declared at the top of the
// stripe body (68.3%, byte-identical residual).
void CellClass::FogCell()
{
    if (DAT_00A8B230->unknown_0000 & 0x1000)
    {
        CellStruct coords = this->MapCoords;
        int i = 1;
        do
        {
            CellClass* cell = MapInstance->GetCellAt(coords);
            int level = cell->Level;
            if (level >= i - 2 && level <= i && (cell->Flags & 0x400000) == 0)
            {
                void* raw = FogOperatorNew(sizeof(FogVec_00486A70));
                FogVec_00486A70* fogged =
                    raw ? ((FogVec_00486A70*)raw)->Construct() : 0;
                (fogged->*fogged->Vptr->At_08)(1, 0);
                fogged->CapacityIncrement = 1;

                cell->Flags |= 0x400000;

                for (Obj_00486A70* obj = (Obj_00486A70*)cell->FirstObject; obj != 0;
                     obj = obj->NextObject)
                {
                    int rtti = obj->RTTI.Vptr->WhatAmI(&obj->RTTI);
                    if (rtti == 6)
                    {
                        CellStruct where;
                        (obj->*obj->Vptr->GetMapCoords)(&where);
                        if (obj->CheckFog())
                        {
                            bool flag;
                            if (!(obj->*obj->Vptr->At_80)())
                            {
                                flag = true;
                                if (obj->Unknown_6ED == 0xF) {
                                    flag = false;
                                }
                            }
                            else
                            {
                                flag = false;
                            }
                            obj->FUN_00457AA0(fogged, cell, flag);
                        }
                    }
                    else if (rtti == 1 || rtti == 2 || rtti == 0xF)
                    {
                        (obj->*obj->Vptr->At_150)();
                    }
                }

                if (fogged->Count > 0) {
                    cell->FoggedObjects = (DynamicVectorClass<FoggedObjectClass*>*)fogged;
                } else if (fogged != 0) {
                    (fogged->*fogged->Vptr->At_00)(1);
                }
            }
            ++coords.X;
            ++coords.Y;
            i += 2;
        } while (i <= 15);
    }
}
