// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Ordinary LayerClass bodies, ordered by pinned retail address.
// This is a project class home; original TU filename is not established.
#include "../_layout/layer_class.h"
#include "../_layout/object_class.h"
#include "layer_class_load_methods.h"
#include "layer_class_save_methods.h"
#include "map_class_add_object_methods.h"

// ObjectClass::GetYSort dispatched through the element's PRIMARY vtable slot at
// byte offset 0xB8 (no args, returns the int sort key):
//   MOV ECX,obj; MOV reg,[obj]; CALL [reg+0xB8]
typedef int (* GetYSortFunc)(void* self);
#define GET_YSORT(obj) ((*(GetYSortFunc*)(*(char**)(obj) + 0xb8))(obj))


// FUNCTION: GAMEMD 0x40CC00
void LayerClass::vf_8()
{
    Clear();
}

// FUNCTION: GAMEMD 0x40CC10
void LayerClass::vf_9()
{
}

// FUNCTION: GAMEMD 0x5519B0
//
// Add an object to this draw layer, either at its sorted position or appended
// at the end. The plain append is DynamicVectorClass::AddItem inlined (body in
// the header).
//
// Both answers are re-normalised on the way out: the sorted insert's full-width
// result becomes `NEG EAX; SBB EAX,EAX; NEG EAX`, and the inlined append's AL
// is squeezed through `XOR EDX,EDX; TEST AL,AL; SETNZ DL; MOV AL,DL` on each of
// its two tails. The second only appears with an explicit `!= 0` on the bool;
// a bare `return AddItem(object)`, or binding it to a bool local first, drops
// the four-instruction tail (60.4%), and a `?:` over the two calls re-shapes the
// whole function (58.5% / 13.2%).
bool LayerClass::AddObject(ObjectClass* object, bool sorted)
{
    if (sorted) {
        return SortedAdd(object) != 0;
    }
    return AddItem(object) != 0;
}

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

// FUNCTION: GAMEMD 0x551A90
// Insert an object into the layer ahead of the first element that
// ObjectClass::FUN_005F6220 ranks after it, growing the vector first if full.
int LayerClass::SortedAdd(ObjectClass* pObject)
{
    if (Count >= Capacity) {
        if ((!IsAllocated && Capacity != 0) || CapacityIncrement <= 0
            || !SetCapacity(Capacity + CapacityIncrement, 0)) {
            return 0;
        }
    }
    int i;
    for (i = 0; i < Count; i++) {
        if (Items[i]->FUN_005F6220(pObject)) {
            break;
        }
    }
    for (int j = Count - 1; j >= i; j--) {
        Items[j + 1] = Items[j];
    }
    Items[i] = pObject;
    Count = Count + 1;
    return 1;
}

// FUNCTION: GAMEMD 0x551B20  LayerClass::Save (__thiscall, ret 0x4)
// DisplayClass::Save (0x4AE720) calls it on each layer of the array at
// 0x8A0360, 0x18 bytes apart. A save over the layer's object list: write the
// element count, then each element pointer, bailing on the first failing
// HRESULT. The count is taken
// into a local before the first write and the loop bound reads that local, not
// the member — the Write call could have changed the object underneath.
Gg_HRESULT LayerClass::Save(IStream* pStm)
{
    if (pStm == 0)
        return GG_E_POINTER;

    int count = Count;

    Gg_HRESULT hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;

    for (int i = 0; i < count; i++) {
        hr = pStm->Write(&Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }

    return GG_S_OK;
}

// FUNCTION: GAMEMD 0x551B90
//
// LayerClass::Load, the counterpart of LayerClass::Save (0x551B20); its callers
// DisplayClass::Load (0x4AE6F0) and 0x67E730 pass each layer in ECX. Load the
// layer's pointer vector from a stream: the element count, then each saved
// pointer appended through AddItem, then every element queued with the
// swizzle manager so the saved pointers are remapped to the reloaded
// objects. A null stream is E_POINTER; a failed read returns its HRESULT.
//
// The count lands in the dead `pStm` parameter slot (pStm lives in EDI after
// the null check) and each element in the one frame local; both reads are
// early returns on a negative HRESULT.
HRESULT LayerClass::Load(IStream* pStm)
{
    if (pStm == 0) {
        return 0x80004003;
    }

    int count = 0;
    HRESULT hr = pStm->Read(&count, 4, 0);
    if (hr < 0) {
        return hr;
    }

    for (int i = 0; i < count; i++) {
        ObjectClass* item;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0) {
            return hr;
        }
        this->AddItem(item);
    }

    for (int j = 0; j < count; j++) {
        DAT_00B0C110.SwizzleManagerClass::vf_4(&this->Items[j]);
    }

    return 0;
}
