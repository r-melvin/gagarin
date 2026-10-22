// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x5587F0  LoadOptionsClass::LoadDialog      (__thiscall)
//   FUNCTION: GAMEMD 0x559EB0  LoadOptionsClass::DeleteMission   (__thiscall, slot 3; ECX unused)
//   FUNCTION: GAMEMD 0x558DD0  LoadOptionsClass::ProcessDialog   (referenced; tail-jmp)

#include "load_options_class_methods.h"

// The Win32 file-delete import. Retail calls it indirectly through the IAT
// (`call dword ptr [__imp__DeleteFileA@4]`); declaring it dllimport makes our
// cl emit the identical `ff 15` form (reloc-normalised by the differ).
extern "C" __declspec(dllimport) int __stdcall DeleteFileA(const char* lpFileName);

// FUNCTION: GAMEMD 0x5587F0  (__thiscall)
// Open the savegame browser in Load mode: set Mode=Load, clear the Save
// Description, then tail-call the shared dialog worker (0x558DD0), whose bool
// result becomes ours.
bool LoadOptionsClass::LoadDialog()
{
    this->Mode = LOM_Load;
    this->Description = 0;
    return this->ProcessDialog();
}

// FUNCTION: GAMEMD 0x559EB0  (__thiscall, vtable slot 3; ECX unused)
// Delete one savegame file; report success only when DeleteFileA returns
// exactly 1 (TRUE).
bool LoadOptionsClass::DeleteMission(const char* pFilename)
{
    // Bind the comparison to a bool local so cl emits the lean `cmp eax,1;
    // sete al` tail (retail's exact form) instead of the branchless
    // dec/neg/sbb/inc equality idiom it picks when `== 1` is returned inline.
    bool succeeded = (DeleteFileA(pFilename) == 1);
    return succeeded;
}
