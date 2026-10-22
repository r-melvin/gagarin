// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// Both retail bodies are the identical single byte  c3  (RET), an empty no-op
// function — confirmed by disasm at both addresses below.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x49F740  CopyProtection::DispatchLauncherMessage (__fastcall)
//   FUNCTION: GAMEMD 0x49F8B0  CopyProtection::ShutDown                (__stdcall)

#include "copy_protection_more_methods.h"

namespace CopyProtection
{

// FUNCTION: GAMEMD 0x49F740  (__fastcall)
void DispatchLauncherMessage(MSG*)
{
}

// FUNCTION: GAMEMD 0x49F8B0  (__stdcall)
//   Retail leaves EAX untouched (bare `ret`); the empty body emits exactly that.
void __stdcall ShutDown()
{
}

}
