// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Each accessed 24-byte region lies in the pinned PE's loader-zero tail.
// These definitions bind storage only; runtime initialization and original
// source ownership remain unknown.
#include "abstract_registry.h"
GG_STATIC_ASSERT(sizeof(DynamicVectorClassLayout) == 0x18);
// GLOBAL: GAMEMD 0xB0F670
DynamicVectorClassLayout DAT_00B0F670;
// GLOBAL: GAMEMD 0xB0F698
DynamicVectorClassLayout DAT_00B0F698;
// GLOBAL: GAMEMD 0xB0F708
DynamicVectorClassLayout DAT_00B0F708;
