// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm).
//   Names cross-checked against YRpp (every address reconfirmed against the user's binary in the .cpp below).
//
// CopyProtection — two more interprocess copy-protection entry points. In retail
// both were reduced to a bare `ret` (each is the single byte `c3`): empty,
// no-op bodies that neutralise the launcher message pump and the protection
// shutdown. Conventions follow the YRpp declarations.
#pragma once

namespace CopyProtection
{
    // MSG* is opaque here; the retail body never dereferences it.
    struct MSG;

    void DispatchLauncherMessage(MSG* pMsg);
    // YRpp types the return as LSTATUS (long), but the retail body is a bare
    // `ret` that never touches EAX, so modelling it as void reproduces the
    // exact byte (and avoids fabricating a return value that retail omits).
    void __stdcall ShutDown();
}
