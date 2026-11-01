// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6BA140.

#include "pcx_get_surface_methods.h"

// PCX::GetSurface (0x6BA140) has no body here: the plain lookup scored 67.2%
// and the retail double null test of the hit node's payload address cannot be
// written without a dead test. The declaration lives in the header.
