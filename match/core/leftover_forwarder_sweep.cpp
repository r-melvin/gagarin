// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Three one-line forwarding members that hand their single argument first to a
// virtual on the subobject embedded at +0x50 and then to a non-virtual helper
// on themselves. Ordered ascending by retail address.

#include "leftover_forwarder_sweep.h"

// FUNCTION: GAMEMD 0x004B4F20
GG_SUBCALL_BODY(004B4F20, Slot3)

// FUNCTION: GAMEMD 0x004B4F40
GG_SUBCALL_BODY(004B4F40, Slot4)

// FUNCTION: GAMEMD 0x004B4F60
GG_SUBCALL_BODY(004B4F60, Slot5)
