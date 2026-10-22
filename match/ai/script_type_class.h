// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/convention derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x691970 / 0x691C00), cross-
//   checked against YRpp ScriptTypeClass.h / AbstractTypeClass.h / ArrayClasses.h
//   (consult-only, no LICENSE; every offset/slot reconfirmed below).
//
// ScriptTypeClass — an AI script template loaded from the [ScriptTypes] INI
// section.  Only the members the two matched static methods touch are modelled;
// the full AbstractTypeClass-derived layout (and the real COM/Abstract vtable
// hierarchy) is P2.  The four primary/secondary vptrs (+0..+0xC), the ID string
// (+0x24), and ArrayIndex/IsGlobal/ActionsCount (+0x98/+0x9C/+0xA0) are pinned
// numerically from the disassembly and asserted.
#ifndef GG_MATCH_AI_SCRIPT_TYPE_CLASS_H
#define GG_MATCH_AI_SCRIPT_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class CCINIClass;

// ---------------------------------------------------------------------------
// External (reloc-normalised) callees we are NOT matching.
// ---------------------------------------------------------------------------
// CRT _strcmpi (case-insensitive compare).  __cdecl, returns 0 on equal.
int  __cdecl Strcmpi(const char* a, const char* b);                // GAMEMD 0x7C8D20
// operator new(size_t).  __cdecl.
void* __cdecl OpNew(unsigned int size);                            // GAMEMD 0x7C8E17

// ---------------------------------------------------------------------------
// CCINIClass — only the three __thiscall readers used here are declared
// (body-less, so cl emits reloc-normalised direct calls).
// ---------------------------------------------------------------------------
class CCINIClass
{
public:
    int         GetKeyCount(const char* section);                       // GAMEMD 0x526960
    const char* GetKeyName(const char* section, int index);             // GAMEMD 0x526CC0
    int         ReadString(const char* section, const char* key,
                           const char* def, char* buffer, int size);    // GAMEMD 0x528A10
};

// ---------------------------------------------------------------------------
// IScriptType — dispatch-only view onto a ScriptTypeClass primary vtable.
// LoadFromINI sits at primary-vtable byte offset 0x64 (slot 25): confirmed by
// `MOV EAX,[ESI]; CALL [EAX+0x64]` in LoadFromINIList.  The 25 leading slots are
// the merged IPersistStream + AbstractClass + AbstractTypeClass virtuals (P2);
// here they are placeholders only so the one call lands on offset 0x64.
// ---------------------------------------------------------------------------
struct IScriptType
{
    virtual void _s00(); virtual void _s01(); virtual void _s02(); virtual void _s03();
    virtual void _s04(); virtual void _s05(); virtual void _s06(); virtual void _s07();
    virtual void _s08(); virtual void _s09(); virtual void _s10(); virtual void _s11();
    virtual void _s12(); virtual void _s13(); virtual void _s14(); virtual void _s15();
    virtual void _s16(); virtual void _s17(); virtual void _s18(); virtual void _s19();
    virtual void _s20(); virtual void _s21(); virtual void _s22(); virtual void _s23();
    virtual void _s24();
    virtual void LoadFromINI(CCINIClass* pINI);   // slot 25 -> offset 0x64
};

// ---------------------------------------------------------------------------
// ScriptTypeClass (sizeof = 0x234).  Flat data view: four vptrs, the ID string,
// ArrayIndex/IsGlobal/ActionsCount.  The AbstractTypeClass base ctor (0x410800)
// is declared as a body-less member so cl emits a __thiscall call to it.
// ---------------------------------------------------------------------------
struct ScriptTypeClass
{
    void* vt0;                 // +0x00  primary vtable (IPersistStream+...)
    void* vt1;                 // +0x04  IRTTITypeInfo
    void* vt2;                 // +0x08  INoticeSink
    void* vt3;                 // +0x0C  INoticeSource
    char  _pad10[0x24 - 0x10]; // +0x10  AbstractClass members (P2)
    char  ID[0x18];            // +0x24
    char  _pad3C[0x98 - 0x3C]; // +0x3C  rest of AbstractTypeClass (P2)
    int   ArrayIndex;          // +0x98
    int   IsGlobal;            // +0x9C  (loaded/stored as a dword in retail)
    int   ActionsCount;        // +0xA0
    char  _padActions[0x234 - 0xA4]; // +0xA4  ScriptActionNode[50] (P2)

    // External AbstractTypeClass(const char*) base ctor.
    void AbsCtor(const char* id);                 // GAMEMD 0x410800

    // FUNCTION: GAMEMD 0x691970  ScriptTypeClass::LoadFromINIList (static __fastcall)
    static void __fastcall LoadFromINIList(CCINIClass* pINI, int isGlobal);

    // FUNCTION: GAMEMD 0x691C00  ScriptTypeClass::FindOrAllocate (static __fastcall)
    static ScriptTypeClass* __fastcall FindOrAllocate(const char* pID);
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(ScriptTypeClass, ID)           == 0x24);
GG_STATIC_ASSERT(offsetof(ScriptTypeClass, ArrayIndex)   == 0x98);
GG_STATIC_ASSERT(offsetof(ScriptTypeClass, IsGlobal)     == 0x9C);
GG_STATIC_ASSERT(offsetof(ScriptTypeClass, ActionsCount) == 0xA0);
GG_STATIC_ASSERT(sizeof(ScriptTypeClass)                 == 0x234);
#endif

// ---------------------------------------------------------------------------
// ScriptTypeClass::Array — DynamicVectorClass<ScriptTypeClass*> @ 0x8B41C8.
// Items(+4)/Capacity(+8)/IsInitialized(+0xC)/IsAllocated(+0xD)/Count(+0x10)/
// CapacityIncrement(+0x14) all confirmed from the 0x8B41Cx absolute accesses.
// SetCapacity is the virtual at vtable offset +8 (CALL [EAX+8]).
// ---------------------------------------------------------------------------
struct ScriptTypeVector
{
    virtual void _v0();
    virtual void _v1();
    virtual bool SetCapacity(int capacity, void* pMem);   // slot 2 -> offset 0x8

    ScriptTypeClass** Items;        // +0x04
    int               Capacity;     // +0x08
    unsigned char     IsInitialized;// +0x0C
    unsigned char     IsAllocated;  // +0x0D
    unsigned char     _pad0E[2];    // +0x0E
    int               Count;        // +0x10
    int               CapacityIncrement; // +0x14

    // The append is NOT a member: it is the free inline helper
    // AddItem_ScriptTypeArray in script_type_class.cpp. Written as a member of
    // this vector, cl 8804 accumulates the grow path's capacity sum into the
    // wrong register and defers the receiver's vtable load past the argument
    // pushes; the identical body as a free function taking the array as its
    // first pointer parameter matches retail exactly. See the .cpp.

    // Mirrors VectorClass::FindItemIndex — linear scan returning the slot index
    // of `item`, or -1. Inlined at the FindOrAllocate / LoadFromINIList tails.
    int FindItemIndex(ScriptTypeClass* item)
    {
        for (int i = 0; i < this->Count; ++i) {
            if (this->Items[i] == item) {
                return i;
            }
        }
        return -1;
    }
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(ScriptTypeVector, Items)             == 0x04);
GG_STATIC_ASSERT(offsetof(ScriptTypeVector, Capacity)          == 0x08);
GG_STATIC_ASSERT(offsetof(ScriptTypeVector, IsAllocated)       == 0x0D);
GG_STATIC_ASSERT(offsetof(ScriptTypeVector, Count)             == 0x10);
GG_STATIC_ASSERT(offsetof(ScriptTypeVector, CapacityIncrement) == 0x14);
#endif

extern ScriptTypeVector ScriptTypeArray;   // GLOBAL: GAMEMD 0x8B41C8

#endif  // GG_MATCH_AI_SCRIPT_TYPE_CLASS_H
