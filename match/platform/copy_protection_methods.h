// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm).
//   Names cross-checked against YRpp (every address reconfirmed against the user's binary in the .cpp below).
//
// CopyProtection — interprocess copy-protection helpers. In retail IsLauncherRunning
// and CheckProtectedData are constant `return true;` stubs (3-byte `mov al,1 / ret`).
// NotifyLauncher (0x49F620) is the launcher handshake whose first three bytes
// (`sub esp,0x1c`) were overwritten with the same `mov al,1 / ret`, so it returns
// true at once; the rest of the original body follows it (see the .cpp). Declared
// __stdcall to match the original YRpp JMP_STD convention; with no arguments the
// emitted body is convention-invariant.
#pragma once

namespace CopyProtection
{
    bool __stdcall IsLauncherRunning();
    bool __stdcall NotifyLauncher();
    bool __stdcall CheckProtectedData();
}
