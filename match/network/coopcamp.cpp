// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Op /Ob2
// Measured /Op retains the native divide-by-60 instruction; /Ob2 emits the
// three dynamic initializers directly. All existing owner rows remain exact.
//   Original translation unit coopcamp.cpp. The name is the source-file string at 0x81f370
//   in retail gamemd.exe v1.001, passed by the assert at 0x49dc91 inside this object's
//   code range (0x49b180-0x49f0df). Functions are in ascending retail address order.
//
// List<INIClass::INISection*> constructor. Retail 0x49E8E0 seats both
// sentinel nodes (0x7E1B0C), the GenericList table (0x7E1B04), links the head
// to the tail, then seats the derived table 0x7E1AFC (RTTI names it
// List<INIClass::INISection*>). Ten callers construct INIClass objects.
//
//   Provenance note: own-binary-via-Ghidra. Direct retail RTTI confirms the non-const
// char* specialization and its zero-offset dynamic base. All entry-origin
// spans and both seven-slot address points are verified against the pinned PE.
// The DynamicVectorClass deleting-dtor full span requires /GX disabled; other
// methods are tested independently. Vtable weak defaults are conditional, not
// final-link proof. The separate const-char* family is not described here.
//
//   Provenance note: own-binary-via-Ghidra. Direct retail RTTI names the two types
// and confirms DynamicVectorClass<DynamicVectorClass<char*>*> derives from
// VectorClass<DynamicVectorClass<char*>*> at offset zero. Entry-origin spans
// and both seven-slot address points were checked against the pinned PE.
// The dynamic deleting-dtor full span needs /GX disabled; the remaining
// tested bodies are exact with /GX as well. Vtable weak defaults are conditional
// slot evidence, not final-link proof. The capacity constructors replace
// address-bound PodElem4 stand-ins; no complete pointee-layout or original-TU
// claim is made.

#include <math.h>
#pragma intrinsic(pow)
#include "../_layout/ini_class.h"

// VTABLE: GAMEMD 0x7E1AFC -- List<INIClass::INISection*>.
// The canonical declaration is shared with its typed table definition.

// Bodies owned elsewhere (0x40E320, 0x52ACE0); repeated inline here so /Ob2
// expands them into the derived constructor as retail does.
inline GenericNode::GenericNode()
{
    NextNode = 0;
    PrevNode = 0;
    Vtable = &GG_VTABLE_GENERIC_NODE_SLOTS;
}

inline GenericList::GenericList()
{
    Vtable = &GG_VTABLE_GENERIC_LIST_SLOTS;
    FirstNode.Link(&LastNode);
}

#include "../core/trivial_tu057_methods.h"

#include "../core/vector_class_operations.h"

template class DynamicVectorClass<char*>;

// VTABLE: GAMEMD 0x007E5BC4 -- DynamicVectorClass<char*>.
// VTABLE: GAMEMD 0x007E5C24 -- VectorClass<char*>.
typedef VectorClass<char*> GgCharPtrVector;
typedef DynamicVectorClass<char*> GgCharPtrDynamicVector;
GG_STATIC_ASSERT(sizeof(char*) == 4);
GG_STATIC_ASSERT(sizeof(GgCharPtrVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgCharPtrVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCharPtrVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCharPtrVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCharPtrVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgCharPtrVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgCharPtrDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, CapacityIncrement) == 0x14);

#include "../core/vector_class_operations.h"

template class DynamicVectorClass<DynamicVectorClass<char*>*>;

// VTABLE: GAMEMD 0x007E5BE4 -- DynamicVectorClass<DynamicVectorClass<char*>*>.
// VTABLE: GAMEMD 0x007E5C04 -- VectorClass<DynamicVectorClass<char*>*>.
typedef VectorClass<DynamicVectorClass<char*>*> GgNestedCharVector;
typedef DynamicVectorClass<DynamicVectorClass<char*>*> GgNestedCharDynamicVector;
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<char*>*) == 4);
GG_STATIC_ASSERT(sizeof(GgNestedCharVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgNestedCharVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgNestedCharVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgNestedCharVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgNestedCharVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgNestedCharVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgNestedCharDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, CapacityIncrement) == 0x14);

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Declaration: GAMEMD 0x4CAC40 -- engine table helper; stacked double, ST0 result.
double __cdecl FUN_004CAC40(double value);

// GLOBAL: GAMEMD 0x89F660
extern int DAT_0089F660;
// GLOBAL: GAMEMD 0x89F664
extern int DAT_0089F664;
// GLOBAL: GAMEMD 0x89F668
extern int DAT_0089F668;

// SYNTHETIC: GAMEMD 0x49B180
// Compiler-generated dynamic initializer for the native double storage.
// GLOBAL: GAMEMD 0x89F5A0
double DAT_0089F5A0 = FUN_004CAC40(2.0 * pow(256.0, 2.0));

// SYNTHETIC: GAMEMD 0x49B1B0
// GLOBAL: GAMEMD 0x89F670
double DAT_0089F670 = DAT_0089F5A0 / 60.0;

// SYNTHETIC: GAMEMD 0x49B1D0
// GLOBAL: GAMEMD 0x89F658
double DAT_0089F658 = 1.0 / DAT_0089F670;

// FUNCTION: GAMEMD 0x49B350
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_0049B350()
{
    DAT_0089F668 = 0;
    DAT_0089F660 = 0x80;
    DAT_0089F664 = 0x80;
}

// FUNCTION: GAMEMD 0x49B420
// Tail-calls a method on a global object.
void FUN_0049B420(int a1, int a2)
{
    FUN_0049E510(DAT_0089F518, a2);
}


struct Arg1_0049D0C0;
struct Arg1_0049D0F0;
struct Arg2_0049D0C0;
struct Arg2_0049D0F0;
struct Obj_0049D0C0;
struct Obj_0049D0F0;

struct Arg1_0049D0C0
{
    int unknown_00;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Arg1_0049D0C0, unknown_00) == 0x0);

struct Arg1_0049D0F0
{
    int unknown_00;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Arg1_0049D0F0, unknown_00) == 0x0);

struct Arg2_0049D0C0
{
    int unknown_00;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Arg2_0049D0C0, unknown_00) == 0x0);

struct Arg2_0049D0F0
{
    int unknown_00;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Arg2_0049D0F0, unknown_00) == 0x0);

struct Obj_0049D0C0
{
    char unknown_00[0x14];
    int unknown_14;   // +0x0014
    int unknown_18;   // +0x0018
    char unknown_1C[0x50];
    unsigned char unknown_6C;   // +0x006C
    // FUNCTION: GAMEMD 0x49D0C0
    unsigned char FUN_0049D0C0(Arg1_0049D0C0* a1, Arg2_0049D0C0* a2);
};
GG_STATIC_ASSERT(offsetof(Obj_0049D0C0, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_0049D0C0, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(Obj_0049D0C0, unknown_6C) == 0x6C);

struct Obj_0049D0F0
{
    char unknown_00[0x30];
    int unknown_30;   // +0x0030
    int unknown_34;   // +0x0034
    char unknown_38[0x34];
    unsigned char unknown_6C;   // +0x006C
    // FUNCTION: GAMEMD 0x49D0F0
    unsigned char FUN_0049D0F0(Arg1_0049D0F0* a1, Arg2_0049D0F0* a2);
};
GG_STATIC_ASSERT(offsetof(Obj_0049D0F0, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(Obj_0049D0F0, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(Obj_0049D0F0, unknown_6C) == 0x6C);

// FUNCTION: GAMEMD 0x49D0C0
// Branching.
unsigned char Obj_0049D0C0::FUN_0049D0C0(Arg1_0049D0C0* a1, Arg2_0049D0C0* a2)
{
    if (unknown_6C != 0)
    {
        a1->unknown_00 = unknown_14;
        a2->unknown_00 = unknown_18;
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x49D0F0
// Branching.
unsigned char Obj_0049D0F0::FUN_0049D0F0(Arg1_0049D0F0* a1, Arg2_0049D0F0* a2)
{
    if (unknown_6C != 0)
    {
        a1->unknown_00 = unknown_30;
        a2->unknown_00 = unknown_34;
        return 1;
    }
    return 0;
}

// TEMPLATE: GAMEMD 0x49E8E0
// ??0?$List@PAUINISection@INIClass@@@@QAE@XZ
// VC6 cannot instantiate a constructor alone; only its visible body is emitted.
template class List<INIClass::INISection*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049E950
// FUNCTION: GAMEMD 0x0049E980
// FUNCTION: GAMEMD 0x0049E9A0
// FUNCTION: GAMEMD 0x0049EA30
// FUNCTION: GAMEMD 0x0049EA70
// FUNCTION: GAMEMD 0x0049EB20
// FUNCTION: GAMEMD 0x0049EE10
// FUNCTION: GAMEMD 0x0049EE60
// FUNCTION: GAMEMD 0x0049EF10
// FUNCTION: GAMEMD 0x0049EF40
// FUNCTION: GAMEMD 0x0049EF80
// FUNCTION: GAMEMD 0x0049EFA0
template class VectorClass<char*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049E9B0
// FUNCTION: GAMEMD 0x0049E9E0
// FUNCTION: GAMEMD 0x0049EA00
struct Obj_0049EA10 {
    int unknown_00;
    int unknown_04;
    int unknown_08;
    unsigned char unknown_0C;
    int unknown_10;
    Obj_0049EA10();
};
GG_STATIC_ASSERT(offsetof(Obj_0049EA10, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(Obj_0049EA10, unknown_10) == 0x10);
// FUNCTION: GAMEMD 0x0049EA10
Obj_0049EA10::Obj_0049EA10()
    : unknown_00(0), unknown_04(0), unknown_08(0), unknown_0C(0), unknown_10(0)
{
}

// FUNCTION: GAMEMD 0x0049EB50
// FUNCTION: GAMEMD 0x0049EB90
// FUNCTION: GAMEMD 0x0049EC40
// FUNCTION: GAMEMD 0x0049EC70
// FUNCTION: GAMEMD 0x0049ECB0
// FUNCTION: GAMEMD 0x0049ECD0
// FUNCTION: GAMEMD 0x0049ED30
// FUNCTION: GAMEMD 0x0049EDE0
// FUNCTION: GAMEMD 0x0049EFF0
// FUNCTION: GAMEMD 0x0049F040
// FUNCTION: GAMEMD 0x0049F090
template class VectorClass<DynamicVectorClass<char*>*>;
