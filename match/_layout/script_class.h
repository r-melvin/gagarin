// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail vtable 0x7F0F78 is the ScriptClass primary table (RTTI names
// .?AVScriptClass@@). The constructor 0x6913C0 and slot 12 (0x691ED0,
// returns 0x30) pin this layout.
#ifndef GG_MATCH_LAYOUT_SCRIPT_CLASS_H
#define GG_MATCH_LAYOUT_SCRIPT_CLASS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "script_type_class.h"

class ScriptClass;

// GLOBAL: GAMEMD 0x8872B0
extern DynamicVectorClass<ScriptClass*> DAT_008872B0;

// VTABLE: GAMEMD 0x7F0F78  ScriptClass
// VTABLE: GAMEMD 0x7F0F5C  ScriptClass::(+0x04)
// VTABLE: GAMEMD 0x7F0F54  ScriptClass::(+0x08)
// VTABLE: GAMEMD 0x7F0F4C  ScriptClass::(+0x0C)
class ScriptClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x6915F0
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x691630
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x691690
    virtual ~ScriptClass();                                               // 8   0x691EE0 (scalar deleting)
    virtual int vf_11();                                                  // 11  0x691EC0
    virtual int vf_12();                                                  // 12  0x691ED0
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x6914E0

    // FUNCTION: GAMEMD 0x6913C0 (declaration; constructor)
    ScriptClass(ScriptTypeClass* type);
    // The stream loader's in-place construction: only the four tables.
    ScriptClass(const AbstractNoInit& noInit) : AbstractClass(noInit) {}

    ScriptTypeClass* Type;            // +0x24
    int              unknown_28;      // +0x28  constructor clears it
    int              CurrentMission;  // +0x2C  constructor sets -1
};
GG_STATIC_ASSERT(offsetof(ScriptClass, Type)           == 0x24);
GG_STATIC_ASSERT(offsetof(ScriptClass, unknown_28)     == 0x28);
GG_STATIC_ASSERT(offsetof(ScriptClass, CurrentMission) == 0x2C);
GG_STATIC_ASSERT(sizeof(ScriptClass)                   == 0x30);

#endif
