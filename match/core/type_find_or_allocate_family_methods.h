// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Every constant below (the two reserved-name strings, the 0x24 ID offset,
//   the per-instance allocation size, and the Items/Count addresses of each
//   global array) was read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI (representative 0x512680). The
//   AbstractTypeClass spine is the repo's own oracle-confirmed layout.
//
// A family of `<T>TypeClass::FindOrAllocate(const char* id)`
// lookup-or-create factories: 131 bytes each, __fastcall (the id arrives in
// ECX), one shared `return 0` tail reached from three places.
//
// This is the same shape as the already-matched WeaponTypeClass::FindOrAllocate
// at 0x772FA0 (match/combat/weapon_type_class.cpp); that body is lifted here
// unchanged and parameterised. The per-instance variation is exactly four
// things: the global DynamicVectorClass holding the type array, the class's
// sizeof (the `PUSH imm32` before operator new), the constructor address, and
// nothing else — the "<none>"/"none" literals, the ID offset 0x24, the
// _strcmpi target 0x7C8D20 and operator new 0x7C8E17 are shared by these instantiations.
#ifndef GG_MATCH_CORE_TYPE_FIND_OR_ALLOCATE_FAMILY_METHODS_H
#define GG_MATCH_CORE_TYPE_FIND_OR_ALLOCATE_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/abstract_type_class.h"

// CRT case-insensitive compare (_strcmpi @ GAMEMD 0x7C8D20). Declared only, so
// every call site is a reloc; the CRT itself is outside the match target.
int __cdecl gg_strcmpi(const char* a, const char* b);

// Declares one instantiation of the family.
//   NAME — the struct name (address-anchored)
//   SIZE — sizeof the concrete type, i.e. retail's `PUSH imm32` operator-new
//          argument, confirmed byte-for-byte from the disassembly
#define GG_TYPE_FIND_OR_ALLOCATE_DECL(NAME, SIZE)                             \
    struct NAME : AbstractTypeClass                                           \
    {                                                                         \
        static NAME* __fastcall FindOrAllocate(const char* id);               \
        /* The type's own `(const char*)` constructor, __thiscall, returning  \
           `this` in EAX. Declared without a body so the call is a reloc; it  \
           is not supplied by this family. */                                       \
        NAME* Construct(const char* id);                                      \
        char unknown_98[(SIZE) - 0x98];   /* remaining Rules fields (P2) */   \
    };                                                                        \
    GG_STATIC_ASSERT(offsetof(NAME, ID) == 0x24);                             \
    GG_STATIC_ASSERT(sizeof(NAME) == (SIZE));                                 \
    struct NAME##Vector                                                       \
    {                                                                         \
        void*  vtable;        /* +0x00 */                                     \
        NAME** Items;         /* +0x04 */                                     \
        int    Capacity;      /* +0x08 */                                     \
        int    IsAllocated;   /* +0x0C */                                     \
        int    Count;         /* +0x10 */                                     \
    };                                                                        \
    GG_STATIC_ASSERT(offsetof(NAME##Vector, Items) == 0x04);                  \
    GG_STATIC_ASSERT(offsetof(NAME##Vector, Count) == 0x10);                  \
    extern NAME##Vector NAME##_Array

// The shared body: reject the two reserved names, scan the global array for a
// case-insensitive ID hit, otherwise hand-roll `new NAME(id)` as raw
// operator new + null guard + construct (no /GX exception-cleanup frame).
#define GG_TYPE_FIND_OR_ALLOCATE_BODY(NAME)                                   \
    NAME* __fastcall NAME::FindOrAllocate(const char* id)                     \
    {                                                                         \
        if (gg_strcmpi("<none>", id) != 0 && gg_strcmpi("none", id) != 0)     \
        {                                                                     \
            for (int i = 0; i < NAME##_Array.Count; ++i)                      \
            {                                                                 \
                if (gg_strcmpi(NAME##_Array.Items[i]->ID, id) == 0)           \
                    return NAME##_Array.Items[i];                             \
            }                                                                 \
            NAME* p = (NAME*)::operator new(sizeof(NAME));                    \
            if (p)                                                            \
                return p->Construct(id);                                      \
        }                                                                     \
        return 0;                                                             \
    }

// One declaration per retail instantiation, ascending by address.
GG_TYPE_FIND_OR_ALLOCATE_DECL(TypeClass_00512680, 0x1B0);
GG_TYPE_FIND_OR_ALLOCATE_DECL(TypeClass_00524CB0, 0xED0);
GG_TYPE_FIND_OR_ALLOCATE_DECL(TypeClass_005FEC70, 0x2BC);
GG_TYPE_FIND_OR_ALLOCATE_DECL(TypeClass_006B5910, 0x2A4);
GG_TYPE_FIND_OR_ALLOCATE_DECL(TypeClass_006CEEF0, 0x100);
GG_TYPE_FIND_OR_ALLOCATE_DECL(TypeClass_006E85F0, 0xD4);
GG_TYPE_FIND_OR_ALLOCATE_DECL(TypeClass_006F1920, 0xF8);
GG_TYPE_FIND_OR_ALLOCATE_DECL(TypeClass_007480D0, 0xE78);
GG_TYPE_FIND_OR_ALLOCATE_DECL(TypeClass_0074B960, 0x308);

#endif  // GG_MATCH_CORE_TYPE_FIND_OR_ALLOCATE_FAMILY_METHODS_H
