// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail vtable 0x7F1008 is the ScriptTypeClass primary table (RTTI names
// .?AVScriptTypeClass@@). The constructor 0x6916B0, the INI reader 0x6918A0
// and writer 0x6917F0 and slot 12 (0x691F80, returns 0x234) pin this layout.
#ifndef GG_MATCH_LAYOUT_SCRIPT_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_SCRIPT_TYPE_CLASS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_type_class.h"
#include "../core/vector_class.h"

struct Obj_004A1D30;
class ScriptTypeClass;

// One script line: an action and its argument (8 bytes; the reader stores the
// two words at +0xA4 + 8*n and +0xA8 + 8*n). Placeholder member names.
struct ScriptActionNode
{
    // FUNCTION: GAMEMD 0x723CA0 (decl; reloc) -- parses a line from text.
    void FUN_00723CA0(const char* text);
    // FUNCTION: GAMEMD 0x723CE0 (decl; reloc) -- formats the line as text.
    void FUN_00723CE0(char* buffer) const;

    int Action;     // +0x00
    int Argument;   // +0x04
};
GG_STATIC_ASSERT(offsetof(ScriptActionNode, Argument) == 4);
GG_STATIC_ASSERT(sizeof(ScriptActionNode) == 8);

// GLOBAL: GAMEMD 0x8B41C8
extern DynamicVectorClass<ScriptTypeClass*> ScriptTypes;

// VTABLE: GAMEMD 0x7F1008  ScriptTypeClass
// VTABLE: GAMEMD 0x7F0FEC  ScriptTypeClass::(+0x04)
// VTABLE: GAMEMD 0x7F0FE4  ScriptTypeClass::(+0x08)
// VTABLE: GAMEMD 0x7F0FDC  ScriptTypeClass::(+0x0C)
class ScriptTypeClass : public AbstractTypeClass
{
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x691D50
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x691D90
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x691DE0
    virtual ~ScriptTypeClass();                                           // 8   0x691FA0 (scalar deleting)
    virtual void vf_10(void* target, bool removed);                       // 10  0x691E30
    virtual int vf_11();                                                  // 11  0x691F70
    virtual int vf_12();                                                  // 12  0x691F80
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x691E00
    virtual int vf_16();                                                  // 16  0x691F90
    virtual bool vf_25(CCINIClass* ini);                                  // 25  0x6918A0
    virtual bool vf_26(CCINIClass* ini);                                  // 26  0x6917F0

    // FUNCTION: GAMEMD 0x6916B0 (declaration; constructor)
    ScriptTypeClass(const char* id);
    // The stream loader's in-place construction: only the four tables.
    ScriptTypeClass(const AbstractNoInit& noInit) : AbstractTypeClass(noInit) {}

    // FUNCTION: GAMEMD 0x691B40
    static ScriptTypeClass* FUN_00691B40(const char* name);
    // FUNCTION: GAMEMD 0x691BB0
    static ScriptTypeClass* FUN_00691BB0(const char* name);

    int              ArrayIndex;          // +0x98  (vf_16 returns it)
    int              IsGlobal;            // +0x9C  constructor clears it
    int              ActionsCount;        // +0xA0
    ScriptActionNode ScriptActions[50];   // +0xA4
};
GG_STATIC_ASSERT(offsetof(ScriptTypeClass, ArrayIndex)    == 0x98);
GG_STATIC_ASSERT(offsetof(ScriptTypeClass, IsGlobal)      == 0x9C);
GG_STATIC_ASSERT(offsetof(ScriptTypeClass, ActionsCount)  == 0xA0);
GG_STATIC_ASSERT(offsetof(ScriptTypeClass, ScriptActions) == 0xA4);
GG_STATIC_ASSERT(sizeof(ScriptTypeClass)                  == 0x234);

#endif
