// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm).
//   Names cross-checked against YRpp (every address reconfirmed against the user's binary in the .cpp below).
//
// CopyProtection — interprocess copy-protection helpers. In retail the first three
// bytes of IsLauncherRunning, NotifyLauncher and CheckProtectedData were overwritten
// with `mov al,1 / ret`, so each returns true at once; the original bodies follow
// the patch and are recovered in the .cpp (see distribution_patches.json). Declared
// __stdcall to match the original YRpp JMP_STD convention; with no arguments the
// emitted body is convention-invariant.
#pragma once

namespace CopyProtection
{
    bool __stdcall IsLauncherRunning();
    bool __stdcall NotifyLauncher();
    bool __stdcall CheckProtectedData();
}
