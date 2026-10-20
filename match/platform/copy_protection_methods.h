// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm).
//   Names cross-checked against YRpp CopyProtection.h (consult-only, no LICENSE;
//   every address reconfirmed against the user's binary in the .cpp below).
//
// CopyProtection — interprocess copy-protection helpers. In retail these three
// entry points were reduced to constant `return true;` stubs (each is the
// 3-byte `mov al,1 / ret`), neutralising the launcher handshake. Declared
// __stdcall to match the original YRpp JMP_STD convention; with no arguments the
// emitted body is convention-invariant.
#pragma once

namespace CopyProtection
{
    bool __stdcall IsLauncherRunning();
    bool __stdcall NotifyLauncher();
    bool __stdcall CheckProtectedData();
}
