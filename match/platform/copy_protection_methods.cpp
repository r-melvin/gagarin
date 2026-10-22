// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// Each retail body is the identical 3-byte sequence  b0 01 c3
//   MOV AL, 0x1 ; RET            == return true;
// confirmed by disasm at all three addresses below.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x49F5C0  CopyProtection::IsLauncherRunning   (__stdcall)
//   FUNCTION: GAMEMD 0x49F620  CopyProtection::NotifyLauncher      (__stdcall)
//   FUNCTION: GAMEMD 0x49F7A0  CopyProtection::CheckProtectedData  (__stdcall)

#include "copy_protection_methods.h"

namespace CopyProtection
{

// FUNCTION: GAMEMD 0x49F5C0  (__stdcall)
bool __stdcall IsLauncherRunning()
{
    return true;
}

// FUNCTION: GAMEMD 0x49F620  (__stdcall)
bool __stdcall NotifyLauncher()
{
    return true;
}

// FUNCTION: GAMEMD 0x49F7A0  (__stdcall)
bool __stdcall CheckProtectedData()
{
    return true;
}

}
