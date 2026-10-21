// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail 0x725FA0/0x726630 access the 24-byte prefix at 0xA8EAE8.
// Its storage lies in the PE loader-zero tail; runtime initialization is unknown.
#include "../_layout/trigger_class.h"
GG_STATIC_ASSERT(sizeof(DynamicVectorClassLayout) == 0x18);
// GLOBAL: GAMEMD 0xA8EAE8
DynamicVectorClassLayout TriggerClass::Array;
