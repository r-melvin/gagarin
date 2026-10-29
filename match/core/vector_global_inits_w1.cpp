// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Initialiser and exit-time stub addresses and the vtable stored by each were read off the
//   user's retail gamemd.exe v1.001 with the local Ghidra CLI.
//
// File-scope DynamicVectorClass<T> objects whose run-time initialiser (fused constructor
// plus atexit) and exit-time destructor stub need the vector operations expanded inline.
// The class translation units that own these objects are built without /Ob2, so the
// objects are defined here.
#include "vector_class_operations.h"

class EBolt;
class CaptureManagerClass;

// GLOBAL: GAMEMD 0x008A0E88
// SYNTHETIC: GAMEMD 0x004C1D90 -- run-time initialiser of DAT_008A0E88
// SYNTHETIC: GAMEMD 0x004C1DD0 -- exit-time destructor stub of DAT_008A0E88
DynamicVectorClass<EBolt*> DAT_008A0E88;

// GLOBAL: GAMEMD 0x0089E0F0
// SYNTHETIC: GAMEMD 0x00471750 -- run-time initialiser of DAT_0089E0F0
// SYNTHETIC: GAMEMD 0x00471790 -- exit-time destructor stub of DAT_0089E0F0
DynamicVectorClass<CaptureManagerClass*> DAT_0089E0F0;

class ConvertClass;

#include "../_layout/staticvectorholder_0089ecf8.h"

// SYNTHETIC: GAMEMD 0x0048E6A0 -- run-time initialiser of DAT_0089ECF8
// SYNTHETIC: GAMEMD 0x0048E6E0 -- exit-time destructor stub of DAT_0089ECF8, guard byte 0x0089ED10 bit 0
DynamicVectorClass<ConvertClass*> StaticVectorHolder_0089ECF8::DAT_0089ECF8;
