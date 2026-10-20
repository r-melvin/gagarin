// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   One class template, thirteen explicit instantiations, ordered ascending by
//   retail address: seven halvings (0xA8 bytes each) and six doublings (0x9C
//   bytes each). Each `template struct HashTable<Node_AAAAAAAA>;` makes the
//   compiler generate `?Shrink@?$HashTable@UNode_AAAAAAAA@@@@QAEXXZ` and
//   `?Grow@...`, one of which is the retail function at the annotated address;
//   the other is the direction that table never had instantiated in retail and
//   carries no address.
//
//   The bodies are in the header. Only the node type -- which is to say the
//   chain-link displacement -- and the direction differ between them.
//
//   KNOWN LIMITATION -- staging ground, not a destination: MSVC6 emits each
//   template instantiation as a COMDAT into the translation unit that
//   instantiated it, so these instantiations belong to many different original
//   Westwood translation units. One sweep file is right for matching bytes now
//   and wrong for retail's eventual link order.

#include "hash_table_rehash_sweep.h"

// FUNCTION: GAMEMD 0x005EEF60
// Halves the table, chain link at +0x08.
template struct HashTable<Node_005EEF60>;

// Layout asserted on the first instantiation; every instantiation in this
// family has the same table layout, because the node type only ever appears
// behind a pointer. The assert has to follow an explicit instantiation: VC6
// fails to re-parse the template body when offsetof is what first instantiates
// it, and it will not take a template-id as offsetof's first argument either,
// hence the typedef.
typedef HashTable<Node_005EEF60> GgHashTableRep;
GG_STATIC_ASSERT(offsetof(GgHashTableRep, Buckets)     == 0x00);
GG_STATIC_ASSERT(offsetof(GgHashTableRep, BucketCount) == 0x08);
GG_STATIC_ASSERT(offsetof(GgHashTableRep, BitWidth)    == 0x0C);
GG_STATIC_ASSERT(offsetof(GgHashTableRep, IsFixed)     == 0x14);
GG_STATIC_ASSERT(offsetof(GgHashTableRep, Hash)        == 0x18);
GG_STATIC_ASSERT(offsetof(GgHashTableRep, MinBuckets)  == 0x30);

// FUNCTION: GAMEMD 0x005EF010
// Doubles the table, chain link at +0x08.
template struct HashTable<Node_005EF010>;

// FUNCTION: GAMEMD 0x00624BE0
// Doubles the table, chain link at +0x08.
template struct HashTable<Node_00624BE0>;

// FUNCTION: GAMEMD 0x006252F0
// Doubles the table, chain link at +0x0C.
template struct HashTable<Node_006252F0>;

// FUNCTION: GAMEMD 0x00625780
// Halves the table, chain link at +0x08.
template struct HashTable<Node_00625780>;

// FUNCTION: GAMEMD 0x006258E0
// Halves the table, chain link at +0x0C.
template struct HashTable<Node_006258E0>;

// FUNCTION: GAMEMD 0x007ADF70
// Halves the table, chain link at +0x70.
template struct HashTable<Node_007ADF70>;

// FUNCTION: GAMEMD 0x007AE020
// Doubles the table, chain link at +0x70.
template struct HashTable<Node_007AE020>;

// FUNCTION: GAMEMD 0x007AE0E0
// Doubles the table, chain link at +0x48.
template struct HashTable<Node_007AE0E0>;

// FUNCTION: GAMEMD 0x007AE460
// Halves the table, chain link at +0x08.
template struct HashTable<Node_007AE460>;

// FUNCTION: GAMEMD 0x007AE510
// Doubles the table, chain link at +0x08.
template struct HashTable<Node_007AE510>;

// FUNCTION: GAMEMD 0x007AE830
// Halves the table, chain link at +0x08.
template struct HashTable<Node_007AE830>;

// FUNCTION: GAMEMD 0x007AEF50
// Halves the table, chain link at +0x48.
template struct HashTable<Node_007AEF50>;

