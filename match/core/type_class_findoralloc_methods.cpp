// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x428B80 / 0x644890 /
//   0x71E2A0 / 0x75E3B0.
//
// Four instantiations of one lookup-or-create template, the callees the
// RulesClass INI list-parsers invoke per key. Each rejects the two "no type"
// literals, scans the type array by ID, and otherwise allocates and constructs.
// Written out four times rather than macro-generated so each carries its own
// addresses and asserts.
//
// Two constructs are load-bearing and both cost the entire match if missed:
//
//  * The constructors are declared `throw()`. `new T(id)` with a
//    potentially-throwing constructor makes VC6 emit an SEH frame
//    (`PUSH -1; PUSH 0; MOV EAX,FS:[0]`) so operator delete can run on unwind;
//    retail has no such frame. Without `throw()`: 3.8%.
//
//  * The array element is *recomputed* at both uses rather than bound to a
//    local. Binding it costs a third callee-saved register (retail saves ESI
//    and EDI only) and shifts every push: 14.5%. Retail reloads the Items base
//    inside the loop and again on the found path, which is what the repeated
//    subscript produces.

#include "type_class_findoralloc_methods.h"

// FUNCTION: GAMEMD 0x428B80  AnimTypeClass::FindOrAllocate (__fastcall)
AnimTypeClass* __fastcall AnimTypeClass::FindOrAllocate(const char* id)
{
    if (_stricmp("<none>", id) == 0)
        return 0;

    if (_stricmp("none", id) == 0)
        return 0;

    for (int i = 0; i < AnimTypeClassArray.Count; i++) {
        if (_stricmp(((AnimTypeClass**)AnimTypeClassArray.Items)[i]->ID, id) == 0)
            return ((AnimTypeClass**)AnimTypeClassArray.Items)[i];
    }

    return new AnimTypeClass(id);
}

// FUNCTION: GAMEMD 0x71E2A0  TerrainTypeClass::FindOrAllocate (__fastcall)
TerrainTypeClass* __fastcall TerrainTypeClass::FindOrAllocate(const char* id)
{
    if (_stricmp("<none>", id) == 0)
        return 0;

    if (_stricmp("none", id) == 0)
        return 0;

    for (int i = 0; i < TerrainTypeClassArray.Count; i++) {
        if (_stricmp(((TerrainTypeClass**)TerrainTypeClassArray.Items)[i]->ID, id) == 0)
            return ((TerrainTypeClass**)TerrainTypeClassArray.Items)[i];
    }

    return new TerrainTypeClass(id);
}

// FUNCTION: GAMEMD 0x75E3B0  WarheadTypeClass::FindOrAllocate (__fastcall)
WarheadTypeClass* __fastcall WarheadTypeClass::FindOrAllocate(const char* id)
{
    if (_stricmp("<none>", id) == 0)
        return 0;

    if (_stricmp("none", id) == 0)
        return 0;

    for (int i = 0; i < WarheadTypeClassArray.Count; i++) {
        if (_stricmp(((WarheadTypeClass**)WarheadTypeClassArray.Items)[i]->ID, id) == 0)
            return ((WarheadTypeClass**)WarheadTypeClassArray.Items)[i];
    }

    return new WarheadTypeClass(id);
}

