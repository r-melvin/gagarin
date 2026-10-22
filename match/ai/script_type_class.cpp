// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x691970 / 0x691C00 (Ghidra
//   disasm). Structure cross-checked against YRpp
//   (each offset,
//   slot and call target reconfirmed against the user's binary).
//
// Translation unit: ScriptTypeClass INI-array management.
//   FUNCTION: GAMEMD 0x691970   ScriptTypeClass::LoadFromINIList (static __fastcall)
//   FUNCTION: GAMEMD 0x691C00   ScriptTypeClass::FindOrAllocate  (static __fastcall)
//   GLOBAL:   GAMEMD 0x8B41C8   ScriptTypeClass::Array (DynamicVectorClass<...*>)
//   STRING:   GAMEMD 0x83E728   "ScriptTypes"
//   STRING:   GAMEMD 0x817474   "<none>"
//   STRING:   GAMEMD 0x817694   "none"
//
// Match status (reccmp diff_retail.py + raw_match.py vs retail,
// reloc-normalised):
//   0x691970 LoadFromINIList  100.0%  (136/136 instructions, 0 real diff)
//   0x691C00 FindOrAllocate   100.0%  (99/99 instructions, 0 real diff)
//
// MATCHED. Both share the same inlined DynamicVectorClass::AddItem /
// FindItemIndex / ctor, and both carried the same lone residual in the
// AddItem grow path's virtual SetCapacity call (0x691CD7..CE6): retail keeps
// the new capacity in EDX and loads the call target into the freed EAX
// *before* the argument pushes, where our build kept it in EAX and deferred
// the `[Array]` vtable load past the pushes (`add eax,edx; push 0; push eax;
// mov eax,[Array]` against retail's `add edx,eax; mov eax,[Array]; push 0;
// push edx`). That was filed as a toolchain register-allocation difference
// across three attempts (operand order, local hoists, argument naming). It is
// not one: it is the shape of the inlined helper. As a *member* of the vector
// the body scores 98.5% / 96.0%; as a free inline function taking the array as
// its first pointer parameter — AddItem_ScriptTypeArray below — the identical
// body scores 100% on both functions. The lever was found at 0x41D300
// (match/core/registered_object_ctor_methods.cpp) and transferred here
// unchanged; 0x6CB3A0 is the third site.

#include "script_type_class.h"

// The four ScriptTypeClass vtable addresses written by the inlined constructor
// (retail 0x7F1008 / 0x7F0FEC / 0x7F0FE4 / 0x7F0FDC).  Reloc-normalised, so any
// distinct symbols suffice; the full vtables are P2.
extern char g_ScriptType_vt0;
extern char g_ScriptType_vt1;
extern char g_ScriptType_vt2;
extern char g_ScriptType_vt3;

// The append written as a free inline helper taking the array as a pointer
// parameter rather than as a member of the vector. See the MATCHED note below.
static inline bool AddItem_ScriptTypeArray(ScriptTypeVector* self,
                                           ScriptTypeClass* item)
{
    if (self->Count >= self->Capacity) {
        if (!self->IsAllocated && self->Capacity != 0) {
            return false;
        }
        if (self->CapacityIncrement <= 0) {
            return false;
        }
        if (!self->SetCapacity(self->CapacityIncrement + self->Capacity, 0)) {
            return false;
        }
    }
    int idx = self->Count++;
    self->Items[idx] = item;
    return true;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x691970  ScriptTypeClass::LoadFromINIList (static __fastcall)
//
// For every key in [ScriptTypes], read its value (a script id), find-or-allocate
// the matching ScriptTypeClass (constructor + Array.AddItem inlined), load it,
// and stamp IsGlobal.
// ---------------------------------------------------------------------------
void ScriptTypeClass::LoadFromINIList(CCINIClass* pINI, int isGlobal)
{
    char buffer[0x18];

    int count = pINI->GetKeyCount("ScriptTypes");
    for (int n = 0; n < count; ++n) {
        const char* key = pINI->GetKeyName("ScriptTypes", n);
        if (pINI->ReadString("ScriptTypes", key, "", buffer, 0x18) > 0) {
            ScriptTypeClass* pItem;

            if (Strcmpi("<none>", buffer) && Strcmpi("none", buffer)) {
                int i = 0;
                while (i < ScriptTypeArray.Count) {
                    if (Strcmpi(ScriptTypeArray.Items[i]->ID, buffer) == 0) {
                        pItem = ScriptTypeArray.Items[i];
                        goto have_item;
                    }
                    ++i;
                }

                pItem = (ScriptTypeClass*)OpNew(0x234);
                if (pItem) {
                    pItem->AbsCtor(buffer);
                    pItem->IsGlobal = 0;
                    pItem->ActionsCount = 0;
                    pItem->vt0 = &g_ScriptType_vt0;
                    pItem->vt1 = &g_ScriptType_vt1;
                    pItem->vt2 = &g_ScriptType_vt2;
                    pItem->vt3 = &g_ScriptType_vt3;

                    AddItem_ScriptTypeArray(&ScriptTypeArray, pItem);
                    pItem->ArrayIndex = ScriptTypeArray.FindItemIndex(pItem);
                    goto have_item;
                }
            }

            pItem = 0;
have_item:
            ((IScriptType*)pItem)->LoadFromINI(pINI);
            pItem->IsGlobal = isGlobal;
        }
    }
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x691C00  ScriptTypeClass::FindOrAllocate (static __fastcall)
//
// Look up a ScriptTypeClass by id; allocate + register one if absent.  "<none>"
// and "none" both resolve to null.
// ---------------------------------------------------------------------------
ScriptTypeClass* ScriptTypeClass::FindOrAllocate(const char* pID)
{
    if (Strcmpi("<none>", pID) && Strcmpi("none", pID)) {
        int i = 0;
        while (i < ScriptTypeArray.Count) {
            if (Strcmpi(ScriptTypeArray.Items[i]->ID, pID) == 0) {
                return ScriptTypeArray.Items[i];
            }
            ++i;
        }

        ScriptTypeClass* pItem = (ScriptTypeClass*)OpNew(0x234);
        if (pItem) {
            pItem->AbsCtor(pID);
            pItem->IsGlobal = 0;
            pItem->ActionsCount = 0;
            pItem->vt0 = &g_ScriptType_vt0;
            pItem->vt1 = &g_ScriptType_vt1;
            pItem->vt2 = &g_ScriptType_vt2;
            pItem->vt3 = &g_ScriptType_vt3;

            AddItem_ScriptTypeArray(&ScriptTypeArray, pItem);
            pItem->ArrayIndex = ScriptTypeArray.FindItemIndex(pItem);

            return pItem;
        }
    }

    return 0;
}
