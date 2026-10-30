// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm). Bodies derived
//   directly from the disassembly at the listed addresses; signatures
//   cross-checked against YRpp (every
//   offset reconfirmed numerically below).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x551A30  LayerClass::Sort          (__thiscall)
//   FUNCTION: GAMEMD 0x55BAA0  LogicClass::AddObject     (__thiscall)
//   FUNCTION: GAMEMD 0x55BAE0  LogicClass::RemoveObject  (__thiscall)

#include "map_class_object_methods.h"

// ObjectClass::GetYSort dispatched through the element's PRIMARY vtable slot at
// byte offset 0xB8 (no args, returns the int sort key):
//   MOV ECX,obj; MOV reg,[obj]; CALL [reg+0xB8]
typedef int (* GetYSortFunc)(void* self);
#define GET_YSORT(obj) ((*(GetYSortFunc*)(*(char**)(obj) + 0xb8))(obj))

// FUNCTION: GAMEMD 0x551A30  (__thiscall)
// One ascending bubble-sort pass over the layer's object list, ordering by each
// element's GetYSort() key. `Items`/`Count` are re-read every iteration because
// the virtual GetYSort() calls may alias the vector.
void LayerClass::Sort()
{
    for (int i = 0; i < this->Count - 1; i++)
    {
        void* b = ((void**)this->Items)[i + 1];
        void* a = ((void**)this->Items)[i];
        int kb = GET_YSORT(b);
        int ka = GET_YSORT(a);
        if (kb < ka)
        {
            ((void**)this->Items)[i + 1] = a;
            ((void**)this->Items)[i] = b;
        }
    }
}

// FUNCTION: GAMEMD 0x55BAA0  (__thiscall)
// LogicClass's vtable 0x7E18FC holds this at slot 7, where LayerClass's table
// has LayerClass::AddObject (0x5519B0). If the object is already in logic,
// succeed immediately; otherwise add it to the layer and, on success, latch its
// in-logic flag.
bool LogicClass::AddObject(ObjectClass* pObject, bool sorted)
{
    if (pObject->IsInLogic)
    {
        return true;
    }
    if (this->LayerClass::AddObject(pObject, sorted))
    {
        pObject->IsInLogic = 1;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x55BAE0  (__thiscall)
// Remove pObject from the layer if it is flagged in-logic: find its slot, then
// shift the tail down one and drop Count. Clears pObject's in-logic flag last.
void LogicClass::RemoveObject(ObjectClass* pObject)
{
    if (pObject->IsInLogic)
    {
        int idx = FindItemIndex(pObject);
        if (idx != -1 && idx < this->Count)
        {
            this->Count = this->Count - 1;
            for (; idx < this->Count; idx++)
            {
                this->Items[idx] = this->Items[idx + 1];
            }
        }
        pObject->IsInLogic = 0;
    }
}
