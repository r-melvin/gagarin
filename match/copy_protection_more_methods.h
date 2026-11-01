// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm).
//   Names cross-checked against YRpp (every address reconfirmed against the user's binary in the .cpp below).
//
// CopyProtection — two more interprocess copy-protection entry points. In retail
// the first byte of each was overwritten with a bare `ret` (`c3`), which turns the
// launcher message pump and the protection shutdown into no-ops; the original
// bodies follow the patch and are recovered in the .cpp. Conventions follow the
// YRpp declarations.
#pragma once

namespace CopyProtection
{
    // Win32 MSG layout; defined in the .cpp.
    struct MSG;

    void DispatchLauncherMessage(MSG* pMsg);
    // YRpp types the return as LSTATUS (long), but the recovered body leaves EAX
    // as the last call left it and nothing uses it; void matches retail.
    void __stdcall ShutDown();
}
