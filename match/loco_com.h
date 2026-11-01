// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only)
//   The _com_ptr_t instantiations the locomotion leaves share. Retail has one
//   out-of-line copy of each comip.h member the leaves call: _QueryInterface
//   0x45AEA0 (IPersist from an ILocomotion pointer), _Release 0x4B4D50
//   (IPersist) and 0x4B4D60 (IPersistStream). Only Teleport's rows file scores
//   them (fn rows); every other rows file binds them.
//
// Shared by every leaf (module header, not foundation-owned).
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_LOCO_COM_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_LOCO_COM_H

#include <comdef.h>
#include "loco_interfaces.h"

// ILocomotionPtr / IPersistPtr / IPersistStreamPtr: the piggybacked locomotor
// and the persistence interfaces queried in PiggybackCLSID / Save.
_COM_SMARTPTR_TYPEDEF(ILocomotion, IID_ILocomotion);
_COM_SMARTPTR_TYPEDEF(IPersist, __uuidof(IPersist));
_COM_SMARTPTR_TYPEDEF(IPersistStream, __uuidof(IPersistStream));

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_LOCO_COM_H
