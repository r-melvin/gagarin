// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Three destructors of a class holding a polymorphic member object at +0x08:
// seat the host vtable, seat the member's vtable, destroy the member through
// its base destructor, then destroy the host base. The member's own destructor
// is inlined, which is why both vtables are seated here. Every byte outside the
// two vtable constants is identical across the three, so the body is written
// once as a macro and expanded per instantiation. Ordered ascending by retail
// address.

#include "relay_host_member_dtor_sweep.h"

// FUNCTION: GAMEMD 0x00766030
GG_RELAY_HOST_DTOR_BODY(007F6FC4)

// FUNCTION: GAMEMD 0x00767BF0
GG_RELAY_HOST_DTOR_BODY(007F70DC)

// FUNCTION: GAMEMD 0x0076F650
GG_RELAY_HOST_DTOR_BODY(007F7314)
