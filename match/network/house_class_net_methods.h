// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x749060-0x74919A), cross-checked
//   against YRpp (reconfirmed
//   numerically here).
//
// UnitTrackerClass — the per-house unit census used by the network layer.
// HouseClass embeds one of these; the "HouseClass-net" serialization methods
// (Init / ToNetworkFormat / ToPCFormat) are its members. The
// tracker is a flat array of 0x200 per-type counters, a live total, and a flag
// recording whether the counters are currently byte-swapped for the wire.
#ifndef GG_MATCH_NETWORK_HOUSE_CLASS_NET_METHODS_H
#define GG_MATCH_NETWORK_HOUSE_CLASS_NET_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ws2_32 import thunks: byte-order conversion (host<->network). Declared (no
// body) so cl emits a normalised call/reloc. The disasm pushes the raw dword
// and stores the dword result back, so the 32-bit signature is exact.
extern "C" unsigned long __stdcall htonl(unsigned long hostlong);   // GAMEMD thunk 0x7C8962
extern "C" unsigned long __stdcall ntohl(unsigned long netlong);    // GAMEMD thunk 0x7C896E

#include "../_layout/unit_tracker_class.h"

#endif
