// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | behaviour-confirmed-name
// Retail 0x6E5AE0 initializes 0xB0E780 with DynamicVectorClass<TagTypeClass*>
// table 0x7F4558, empty storage, flags 1/0, count 0 and growth 10, then
// registers 0x6E5B20 through atexit at 0x7C978A. Full initializer span 61 bytes.
// Ob2 fuses the initializer and registration helpers as in retail; no GX.
#include "../_layout/tag_type_class.h"
#include "../core/vector_class_operations.h"
typedef DynamicVectorClass<TagTypeClass*> TagTypeRegistry;
GG_STATIC_ASSERT(offsetof(TagTypeRegistry, Items) == 4);
GG_STATIC_ASSERT(offsetof(TagTypeRegistry, Capacity) == 8);
GG_STATIC_ASSERT(offsetof(TagTypeRegistry, IsInitialized) == 0xC);
GG_STATIC_ASSERT(offsetof(TagTypeRegistry, IsAllocated) == 0xD);
GG_STATIC_ASSERT(offsetof(TagTypeRegistry, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(TagTypeRegistry, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(TagTypeRegistry) == 0x18);
// GLOBAL: GAMEMD 0xB0E780
DynamicVectorClass<TagTypeClass*> TagTypes;

// LIBRARY: GAMEMD 0x7C978A -- CRT atexit registration.
// SYNTHETIC: GAMEMD 0x6E5AE0
// Compiler-generated initializer (_$E4), complete 61-byte match.
// SYNTHETIC: GAMEMD 0x6E5B20
// Compiler-generated cleanup (_$E2): the implicit DynamicVectorClass
// destructor inlining ~VectorClass. A namespace-scope object gets no guard.
