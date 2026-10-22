// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Accessed 24-byte registry prefix at 0x8B4178. Storage lies in the pinned
// PE loader-zero tail; later runtime initialization is not established here.
#include "../_layout/trigger_type_class.h"
GG_STATIC_ASSERT(sizeof(DynamicVectorClassLayout) == 0x18);
// GLOBAL: GAMEMD 0x8B4178
DynamicVectorClassLayout TriggerTypeClass::Array;
