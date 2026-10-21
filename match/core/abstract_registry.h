// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Shared vector-shaped regions used by several AbstractClass-derived objects.
// TriggerTypeClass construction (0x726C80) also appends to 0xB0F658/0xB0F670.
// TagClass construction (0x6E4DE0) and TriggerClass construction (0x725FA0)
// append to 0xB0F670/0xB0F708. TagClass::Destroy (0x6E5230), TriggerClass::Destroy
// (0x726720), DiskLaser pointer expiry (0x4A7900) and ObjectClass::UnInit
// (0x5F65F0) append to 0xB0F698. Original owning class/names are unconfirmed.
#ifndef GG_MATCH_CORE_ABSTRACT_REGISTRY_H
#define GG_MATCH_CORE_ABSTRACT_REGISTRY_H
#include "../_layout/vector_class.h"
// GLOBAL: GAMEMD 0xB0F658
extern DynamicVectorClassLayout DAT_00B0F658;
// GLOBAL: GAMEMD 0xB0F670
extern DynamicVectorClassLayout DAT_00B0F670;
// GLOBAL: GAMEMD 0xB0F698
extern DynamicVectorClassLayout DAT_00B0F698;
// GLOBAL: GAMEMD 0xB0F708
extern DynamicVectorClassLayout DAT_00B0F708;
#endif
