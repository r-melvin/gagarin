// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// The four argument forwarders, ordered ascending by retail address.

#include "stdcall_forward_sweep.h"


// FUNCTION: GAMEMD 0x6AC5D0
void Sidebar_006D1800::FUN_006AC5D0(void* arg)
{
    FUN_006568A0(arg);
}

// FUNCTION: GAMEMD 0x6AC5E0
void Sidebar_006D1800::FUN_006AC5E0(void* arg)
{
    FUN_00656AC0(arg);
}

// FUNCTION: GAMEMD 0x6D1800
// TabClass's slot 33 forwards to SidebarClass's slot 33 with `this` left in ECX.
void Tab_006D1800::vf_33(void* arg)
{
    Sidebar_006D1800::vf_33(arg);
}

