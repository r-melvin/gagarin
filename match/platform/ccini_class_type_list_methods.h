// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The TypeList<int> corner of the CCINIClass enumerated reader/writer run,
//   found by sweeping 0x475B67..0x476340 as raw bytes: six bodies behind pad
//   runs that end on a four-byte boundary, of which the Ghidra function list
//   knows only two.
//
//   The element container is read numerically off the user's retail
//   gamemd.exe v1.001. Its Items pointer sits at +0x04 and its Count at
//   +0x10 (the 0x475B70 writer's registry proves the twelve-byte gap), the
//   allocation flag is the byte at +0x0D that the inlined destructor tests
//   before calling the C library free at 0x7C8B3D, and the by-value
//   parameters occupy 0x1C bytes rather than 0x18, which is the trailing
//   dword YRpp's TypeList<T> carries as `unknown_18` (the
//   member name only, no text copied). The two vtable constants the
//   constructors seat are 0x7E4DB8 (the vector base) and 0x7E4DD8 (the
//   dynamic vector, which TypeList shares because it adds no virtuals).
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_TYPE_LIST_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_TYPE_LIST_METHODS_H

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../_rt/gg_static_assert.h"

// STRING: GAMEMD 0x889F64  ""
extern const char STR_00889F64[];
// STRING: GAMEMD 0x817F6C  "%d"
extern const char STR_00817F6C[];
// STRING: GAMEMD 0x817F70  ","
extern const char STR_00817F70[];

struct TypeListInt;

// The two vtables the list seats. The values are relocations, so what has to
// be right is that a store happens and which of the two symbols it names, not
// the address itself.
// VTABLE: GAMEMD 0x7E4DB8 — the vector base.
extern void* DAT_007E4DB8[];
// VTABLE: GAMEMD 0x7E4DD8 — the dynamic vector, which the list shares.
extern void* DAT_007E4DD8[];

// The out-of-line halves of the vector's own lifetime, all three taking the
// object in ECX, which is why they are spelled as methods of a stand-in
// rather than as free functions: cl 6.0 rejects __thiscall on a pointer or a
// free function outright.
struct VectorCallShim_int
{
    // FUNCTION: GAMEMD 0x477BE0 (decl; reloc) — VectorClass(capacity, pMem).
    void Construct(int capacity, int* pMem);
    // FUNCTION: GAMEMD 0x477B60 (decl; reloc) — VectorClass(const VectorClass&).
    void CopyConstruct(const TypeListInt* other);
    // FUNCTION: GAMEMD 0x478720 (decl; reloc) — VectorClass::operator=.
    void Assign(const TypeListInt* other);

    // Slot 2 of the vector vtable, the only virtual the readers call
    // (`MOV EDX,[obj]; CALL [EDX+8]`). Reaching it through a stand-in with a
    // vtable of its own is what keeps the call indirect: the list itself
    // carries its vtable as a plain member so that every seat below can be
    // written where retail writes it.
    virtual ~VectorCallShim_int();
    virtual bool Equals(const VectorCallShim_int* other);
    virtual bool SetCapacity(int capacity, int* pMem);
};

// TypeList<int>, the list the readers build and the writers walk.
struct TypeListInt
{
    void*   _vtable;            // +0x0000
    int*    Items;              // +0x0004
    int     Capacity;           // +0x0008
    bool    IsInitialized;      // +0x000C
    bool    IsAllocated;        // +0x000D
    int     Count;              // +0x0010
    int     CapacityIncrement;  // +0x0014
    int     unknown_18;         // +0x0018

    // The list's own lifetime, all of it inline because retail expands every
    // one of these at the call site.
    //
    // The capacity constructor: the vector base is built out of line at
    // 0x477BE0 and the dynamic tail seated after it.
    TypeListInt(int capacity, int* pMem) throw()
    {
        ((VectorCallShim_int*)this)->Construct(capacity, pMem);
        CapacityIncrement = 10;
        Count = 0;
        _vtable = DAT_007E4DD8;
    }

    // The copy constructor as retail builds a return value out of a list
    // that arrived by value: the vector base is default-built inline and
    // then assigned out of line at 0x478720, and only afterwards does the
    // dynamic tail follow.
    TypeListInt(const TypeListInt& other) throw()
    {
        Items = 0;
        Capacity = 0;
        IsInitialized = true;
        IsAllocated = false;
        _vtable = DAT_007E4DB8;

        ((VectorCallShim_int*)this)->Assign(&other);

        Count = other.Count;
        CapacityIncrement = other.CapacityIncrement;
        _vtable = DAT_007E4DD8;
    }

    // The other copy: the vector base is copy-built out of line at 0x477B60
    // instead. Retail uses this form for a list it built itself and the form
    // above for one that arrived by value, so the two are separate
    // constructors here; the second argument only selects between them.
    TypeListInt(const TypeListInt& other, int) throw()
    {
        ((VectorCallShim_int*)this)->CopyConstruct(&other);
        Count = other.Count;
        CapacityIncrement = other.CapacityIncrement;
        _vtable = DAT_007E4DD8;
    }

    // Append, expanding by the increment when the array is full. The
    // expansion is the vector's slot-2 virtual, reached through the stand-in.
    bool AddItem(int item) throw()
    {
        if (Count >= Capacity) {
            if (!IsAllocated && Capacity != 0) {
                return false;
            }

            if (CapacityIncrement <= 0) {
                return false;
            }

            if (!((VectorCallShim_int*)this)->SetCapacity(
                    Capacity + CapacityIncrement, 0)) {
                return false;
            }
        }

        int index = Count++;

        Items[index] = item;
        return true;
    }

    // The release the 0x475C70 writer inlines over its by-value parameter.
    // Retail tests the pointer first and the allocation flag second, and
    // seats no vtable, so the store the vector's own release would make is
    // dead here. The no-throw specification kept /GX, the tree's earlier flag
    // set, from
    // wrapping the parameter's release in an unwind funclet retail has no
    // trace of.
    ~TypeListInt() throw()
    {
        _vtable = DAT_007E4DB8;

        if (Items != 0 && IsAllocated) {
            free(Items);
            Items = 0;
        }

        IsAllocated = false;
        Capacity = 0;
    }
};
GG_STATIC_ASSERT(offsetof(TypeListInt, Items) == 0x04 &&
                 offsetof(TypeListInt, IsAllocated) == 0x0D &&
                 offsetof(TypeListInt, Count) == 0x10 &&
                 sizeof(TypeListInt) == 0x1C);

// An object type record. Only the inline ID text at +0x24 is read, by
// `LEA EDI,[EAX+0x24]` in the 0x476240 writer.
struct ObjectType_00476240
{
    char _pad000[0x24];     // +0x0000
    char ID[4];             // +0x0024
};
GG_STATIC_ASSERT(offsetof(ObjectType_00476240, ID) == 0x24);

// The packed identity a type list element carries: the low three bytes are
// the registry index and the top byte the abstract-type tag, which the
// 0x476240 writer sign-extends out with `SAR ECX,0x18`. The tag byte is
// zeroed on construction and the index store is folded away, which is why
// retail has a byte store of zero and no dword store of zero.
struct AbstractType_006E6AB0;   // opaque; handled by pointer only

struct TypeId_00476240
{
    int     ID;     // +0x0000
    char    RTTI;   // +0x0004

    // FUNCTION: GAMEMD 0x6E6AB0 (decl; reloc) — build an identity from a
    // record. Returns the object in EAX like every MSVC constructor, which
    // is where the 0x476020 reader reads both fields back from.
    TypeId_00476240(AbstractType_006E6AB0* type);

    TypeId_00476240()
    {
        RTTI = 0;
    }

};
// FUNCTION: GAMEMD 0x6E7330 (decl; reloc) — packed identity -> record. The
// identity arrives in ECX.
ObjectType_00476240* FUN_006E7330(TypeId_00476240* id);

// The two registries the 0x476020 reader looks a name up in, in order.
// GLOBAL: GAMEMD 0xA8E34C — the first registry's item array.
extern AbstractType_006E6AB0** DAT_00A8E34C;
// GLOBAL: GAMEMD 0xA83CE4 — the second registry's item array.
extern AbstractType_006E6AB0** DAT_00A83CE4;

// FUNCTION: GAMEMD 0x523C90 (decl; reloc) — first registry: name -> index.
int FUN_00523C90(const char* name);
// FUNCTION: GAMEMD 0x747370 (decl; reloc) — second registry: name -> index.
int FUN_00747370(const char* name);

// LIBRARY: GAMEMD 0x7C9CC2 (decl; reloc) — the CRT token splitter.
extern "C" char* __cdecl FUN_007C9CC2(char* text, const char* delimiters);
// LIBRARY: GAMEMD 0x7C9BFD (decl; reloc) — the CRT decimal parser.
extern "C" int __cdecl FUN_007C9BFD(const char* text);
// FUNCTION: GAMEMD 0x751590 (decl; reloc) — armour index -> armour name.
const char* FUN_00751590(int index);

GG_STATIC_ASSERT(offsetof(TypeId_00476240, RTTI) == 0x04 &&
                 sizeof(TypeId_00476240) == 0x08);

class CCINI_00475C70
{
public:
    // FUNCTION: GAMEMD 0x528660 (decl; reloc) — INIClass::WriteString.
    bool WriteString(const char* section, const char* key, const char* value);

    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) — INIClass::ReadString.
    int  ReadString(const char* section, const char* key, const char* defaultValue,
                    char* buffer, unsigned int size);

    // FUNCTION: GAMEMD 0x475C70
    bool WriteArmorList(const char* section, const char* key, TypeListInt list);
    // FUNCTION: GAMEMD 0x475D70
    TypeListInt ReadIntegerList(const char* section, const char* key,
                                TypeListInt defaultValue);
    // FUNCTION: GAMEMD 0x476020
    TypeListInt ReadTypeIdList(const char* section, const char* key,
                               TypeListInt defaultValue);
    // FUNCTION: GAMEMD 0x475F30
    bool WriteIntegerList(const char* section, const char* key,
                          const TypeListInt* list);
    // FUNCTION: GAMEMD 0x476240
    bool WriteTypeIdList(const char* section, const char* key,
                         const TypeListInt* list);
};

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_TYPE_LIST_METHODS_H
