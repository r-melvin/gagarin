// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The ScriptClass / ScriptTypeClass block of retail .text (0x6911E0..0x69202A):
// three of the unit's run-time initialisers, both constructors and
// destructors, the two name lookups and the primary-table slots, in retail
// address order. The classes are declared in _layout/script_class.h and
// _layout/script_type_class.h.
// LIBRARY: GAMEMD 0x7C8EF4 -- sprintf; GAMEMD 0x7C8D20 -- _strcmpi;
// GAMEMD 0x7C8B3D -- operator delete.
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy
//   /Ob2: the constructors and destructors expand the registry vector bodies.

#include <new.h>
#include <stdio.h>
#include <string.h>
#include "../_layout/script_class.h"
#include "../_layout/obj_004a1d30.h"
#include "../core/vector_class_operations.h"
#include "../movement/locomotion_load_support.h"
#include "../core/header_tuning_globals.h"
#include "../platform/ccini_class_methods.h"

// FUNCTION: GAMEMD 0x727CF0 (decl; reloc) -- trims a buffer in place.
void FUN_00727CF0(char* buffer);

// GLOBAL: GAMEMD 0x889F64 -- the shared empty default string.
extern const char DAT_00889F64[];

// GLOBAL: GAMEMD 0xA8ECA0 -- the registry the slot-10 walk indexes.
extern DynamicVectorClass<AbstractClass*> DAT_00A8ECA0;

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0xB055C8
extern double DAT_00B055C8;
// GLOBAL: GAMEMD 0x7F0F38
const double DAT_007F0F38 = 60.0;

// SYNTHETIC: GAMEMD 0x6911E0
// GLOBAL: GAMEMD 0xB05618
double DAT_00B05618 = DAT_00B055C8 / DAT_007F0F38;
// SYNTHETIC: GAMEMD 0x691200
// GLOBAL: GAMEMD 0xB05600
double DAT_00B05600 = 1.0 / DAT_00B05618;
// SYNTHETIC: GAMEMD 0x691380
// GLOBAL: GAMEMD 0xB05608
TuningCoordInit DAT_00B05608(128, 128, 0);

// ---- ScriptClass -------------------------------------------------------------------------------------------------

// FUNCTION: GAMEMD 0x6913C0
ScriptClass::ScriptClass(ScriptTypeClass* type)
    : Type(type), unknown_28(0), CurrentMission(-1)
{
    DAT_008872B0.AddItem(this);
}

// FUNCTION: GAMEMD 0x691460
ScriptClass::~ScriptClass()
{
    AnnounceExpiredPointer(1);
    DAT_008872B0.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x6914E0
void ScriptClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    crc->FUN_004A1D50(CurrentMission);
}

// FUNCTION: GAMEMD 0x691630
HRESULT __stdcall ScriptClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) ScriptClass(AbstractNoInit());
    DAT_00B0C110.FUN_006CF240((void**)&Type);
    return 0;
}

// ---- ScriptTypeClass ---------------------------------------------------------------------------------------------

// FUNCTION: GAMEMD 0x6916B0
ScriptTypeClass::ScriptTypeClass(const char* id)
    : AbstractTypeClass(id), IsGlobal(0), ActionsCount(0)
{
    ScriptTypes.AddItem(this);
    ArrayIndex = ScriptTypes.FindItemIndex(this);
}

// FUNCTION: GAMEMD 0x691770
ScriptTypeClass::~ScriptTypeClass()
{
    AnnounceExpiredPointer(1);
    ScriptTypes.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x6917F0
bool ScriptTypeClass::vf_26(CCINIClass* ini)
{
    if (AbstractTypeClass::vf_26(ini)) {
        for (int i = 0; i < 50; i++) {
            char key[0x10];
            char value[0x80];
            sprintf(key, "%d", i);
            FUN_00727CF0(key);
            if (i < ActionsCount) {
                ScriptActions[i].FUN_00723CE0(value);
                ini->WriteString(ID, key, value);
            } else {
                ini->Clear(ID, key);
            }
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x6918A0
bool ScriptTypeClass::vf_25(CCINIClass* ini)
{
    ini->Reset();
    if (AbstractTypeClass::vf_25(ini)) {
        ActionsCount = 0;
        for (int i = 0; i < 50; i++) {
            char key[0x10];
            char value[0x80];
            ScriptActionNode node;
            sprintf(key, "%d", i);
            FUN_00727CF0(key);
            if (ini->FUN_00528A10(ID, key, DAT_00889F64, value, 0x80) > 0) {
                node.FUN_00723CA0(value);
                if (ActionsCount < 50) {
                    ScriptActions[ActionsCount] = node;
                    ActionsCount++;
                }
            }
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x691B40
ScriptTypeClass* ScriptTypeClass::FUN_00691B40(const char* name)
{
    if (name) {
        for (int i = 0; i < ScriptTypes.Count; i++) {
            if (!_strcmpi(name, ScriptTypes.Items[i]->ID)
                || !_strcmpi(name, ScriptTypes.Items[i]->Name)) {
                return ScriptTypes.Items[i];
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x691BB0
ScriptTypeClass* ScriptTypeClass::FUN_00691BB0(const char* name)
{
    if (name) {
        for (int i = 0; i < ScriptTypes.Count; i++) {
            if (!_strcmpi(name, ScriptTypes.Items[i]->Name)) {
                return ScriptTypes.Items[i];
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x691D90
HRESULT __stdcall ScriptTypeClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) ScriptTypeClass(AbstractNoInit());
    return 0;
}

// FUNCTION: GAMEMD 0x691E00
void ScriptTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1D50(ActionsCount);
}

// FUNCTION: GAMEMD 0x691E30
// Action 0x12 lines hold an index into the 0xA8ECA0 registry; when an object
// of kind 0x23 leaves it, later indices shift down and its own index clears.
void ScriptTypeClass::vf_10(void* target, bool removed)
{
    AbstractClass* object = static_cast<AbstractClass*>(target);
    if (object && object->vf_11() == 0x23) {
        int index = -1;
        for (int i = 0; i < ActionsCount; i++) {
            if (ScriptActions[i].Action == 0x12) {
                if (index == -1) {
                    index = DAT_00A8ECA0.FindItemIndex(object);
                    if (index == -1) {
                        return;
                    }
                }
                if (ScriptActions[i].Argument > index) {
                    ScriptActions[i].Argument--;
                } else if (ScriptActions[i].Argument == index) {
                    ScriptActions[i].Argument = 0;
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x691EC0
int ScriptClass::vf_11()
{
    return 0x1A;
}

// FUNCTION: GAMEMD 0x691ED0
int ScriptClass::vf_12()
{
    return sizeof(ScriptClass);
}

// SYNTHETIC: GAMEMD 0x691EE0
// ScriptClass scalar deleting destructor (primary slot 8).

// FUNCTION: GAMEMD 0x691F70
int ScriptTypeClass::vf_11()
{
    return 0x1B;
}

// FUNCTION: GAMEMD 0x691F80
int ScriptTypeClass::vf_12()
{
    return sizeof(ScriptTypeClass);
}

// FUNCTION: GAMEMD 0x691F90
int ScriptTypeClass::vf_16()
{
    return ArrayIndex;
}

// SYNTHETIC: GAMEMD 0x691FA0
// ScriptTypeClass scalar deleting destructor (primary slot 8).
