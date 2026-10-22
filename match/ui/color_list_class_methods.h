// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: the user's retail gamemd.exe v1.001 through the local Ghidra
//   CLI at 0x4887F0 / 0x488850 / 0x4888B0 / 0x488910. This address run carried
//   no name in any worklist; the owning class was recovered from the runtime
//   type information hanging off the vtable the destructor installs:
//     0x7E5054 - 4 -> 0x7FD1A8 (complete object locator)
//     0x7FD1A8 + 0xC -> 0x81D148 (type descriptor)
//     0x81D148 + 8 -> ".?AVColorListClass@@"
//   and the element vector's own vtable resolves the same way:
//     0x7E4DB8 - 4 -> 0x7FCDB0 -> 0x81C038 -> ".?AV?$VectorClass@H@@"
//   so Colors is a DynamicVectorClass<int>. Every offset below is read
//   numerically from the disassembly.
//
// ColorListClass -- a ListClass whose entries each carry a colour. The four
// bodies here are the destructor, the colour-carrying Add_Item, and the two
// Remove_Item overloads, each of which keeps the parallel colour vector in
// step with the base list.
//
// Layout, member by member from the disassembly:
//   +0x000  vptr            `MOV [EDI],0x7E5054` in the destructor
//   +0x034  List            `LEA ECX,[ESI+0x34]` + `CALL [EAX+0x10]` (ID) at
//                           0x4888BA -- the base ListClass's own text vector
//   +0x174  Colors          `LEA ESI,[EDI+0x174]`, then +0x4/+0x8/+0xD/+0x10/
//                           +0x14 exactly as the container pair lays out
//   +0x18C  Style           (not touched here; pinned by 0x488960)
//   +0x190  SelectColor     `MOV [EDI+0x190],EBX` in the destructor
#ifndef GG_MATCH_UI_COLOR_LIST_CLASS_METHODS_H
#define GG_MATCH_UI_COLOR_LIST_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/vector_class.h"

void* __cdecl operator new[](size_t);
void  __cdecl operator delete[](void*);

// VTABLE: GAMEMD 0x007E5054 — ColorListClass
extern char VT_007E5054[];

// ---------------------------------------------------------------------------
// VectorClass<int> / DynamicVectorClass<int> — the colour vector.
//
// Virtual slot order, as already pinned elsewhere in this tree:
//   0x00 ~VectorClass  0x04 operator==  0x08 Resize  0x0C Clear  0x10 ID
// The destructor's `CALL [EAX+0xC]` is therefore Clear(), and Add's
// `CALL [EDX+0x8]` with two pushed arguments is Resize(capacity, array).
// ---------------------------------------------------------------------------
class ColorVector
{
public:
    // VTABLE: GAMEMD 0x007E4DB8
    virtual ~ColorVector() { ColorVector::Clear(); }                 // 0x00
    virtual bool operator==(ColorVector const& other) const;         // 0x04
    virtual bool Resize(int capacity, int const* array);             // 0x08
    virtual void Clear()                                             // 0x0C
    {
        if (Vector && IsAllocated) {
            delete[] Vector;
            Vector = 0;
        }
        IsAllocated = false;
        Capacity = 0;
    }
    virtual int ID(int const& object) const;                         // 0x10

    int* Vector;       // +0x04
    int  Capacity;    // +0x08
    bool IsValid;      // +0x0C
    bool IsAllocated;  // +0x0D
};
GG_STATIC_ASSERT(offsetof(ColorVector, Vector)      == 0x04);
GG_STATIC_ASSERT(offsetof(ColorVector, Capacity)   == 0x08);
GG_STATIC_ASSERT(offsetof(ColorVector, IsValid)     == 0x0C);
GG_STATIC_ASSERT(offsetof(ColorVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(sizeof(ColorVector)                == 0x10);

class ColorDynVector : public ColorVector
{
public:
    int Count;  // +0x10
    int CapacityIncrement;   // +0x14

    // Both of these are expanded at their call sites in retail, never called.
    bool Add(int const& object)
    {
        if (Count >= Capacity) {
            if ((IsAllocated || !Capacity) && CapacityIncrement > 0) {
                if (!Resize(Capacity + CapacityIncrement, 0)) {
                    return false;
                }
            } else {
                return false;
            }
        }
        int index = Count;
        Count = index + 1;
        Vector[index] = object;
        return true;
    }

    bool Delete(int index)
    {
        if (index < Count) {
            Count--;
            for (int i = index; i < Count; i++) {
                Vector[i] = Vector[i + 1];
            }
        }
        return true;
    }
};
GG_STATIC_ASSERT(offsetof(ColorDynVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(ColorDynVector, CapacityIncrement)  == 0x14);
GG_STATIC_ASSERT(sizeof(ColorDynVector)                == 0x18);

// ---------------------------------------------------------------------------
// DynamicVectorClass<wchar_t const*> — the base ListClass's own entry vector
// (RTTI VectorClass<unsigned short const*> at 0x7ED1FC; VC6's wchar_t is
// unsigned short). Only FindItemIndex (slot 0x10) is reached from this TU.
// ---------------------------------------------------------------------------
typedef DynamicVectorClass<wchar_t const*> TextDynVector;
GG_STATIC_ASSERT(sizeof(TextDynVector) == 0x18);

// ---------------------------------------------------------------------------
// ColorListClass. The ListClass base is opaque padding apart from the two
// sub-objects this TU reaches; its four out-of-line entry points are declared
// only, so cl emits relocatable __thiscall calls.
// ---------------------------------------------------------------------------
class ColorListClass
{
public:
    void*          Vfptr;                   // +0x000
    char           _pad004[0x34 - 0x04];    // +0x004
    TextDynVector  List;                    // +0x034
    char           _pad04C[0x174 - 0x4C];   // +0x04C
    ColorDynVector Colors;                  // +0x174
    int            Style;                   // +0x18C
    int            SelectColor;             // +0x190

    // FUNCTION: GAMEMD 0x557600 (decl; reloc) — ListClass::~ListClass
    void ListClass_Dtor();
    // FUNCTION: GAMEMD 0x5576A0 (decl; reloc) — ListClass::Add_Item
    void ListClass_AddItem(wchar_t const* text);
    // FUNCTION: GAMEMD 0x557730 (decl; reloc) — ListClass::Remove_Item(index)
    void ListClass_RemoveItem(int index);
    // FUNCTION: GAMEMD 0x557800 (decl; reloc) — ListClass::Remove_Item(text)
    void ListClass_RemoveItem(wchar_t const* text);

    // FUNCTION: GAMEMD 0x4887F0
    void Dtor();
    // FUNCTION: GAMEMD 0x488850
    void AddItem(wchar_t const* text, int color);
    // FUNCTION: GAMEMD 0x4888B0
    void RemoveItem(wchar_t const* text);
    // FUNCTION: GAMEMD 0x488910
    void RemoveItem(int index);
};

GG_STATIC_ASSERT(offsetof(ColorListClass, List)        == 0x034);
GG_STATIC_ASSERT(offsetof(ColorListClass, Colors)      == 0x174);
GG_STATIC_ASSERT(offsetof(ColorListClass, Style)       == 0x18C);
GG_STATIC_ASSERT(offsetof(ColorListClass, SelectColor) == 0x190);

#endif  // GG_MATCH_UI_COLOR_LIST_CLASS_METHODS_H
