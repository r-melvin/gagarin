// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//
// The light-source list global at 0xABCA10: a DynamicVectorClass<LightSourceClass*>
// (vtable 0x7ECF7C). Retail puts its fused constructor + atexit initialiser at
// 0x554640 and the exit-time destructor stub at 0x554680; both come out of this
// one definition.
#include "vector_class_operations.h"

class LightSourceClass;

// GLOBAL: GAMEMD 0xABCA10
// SYNTHETIC: GAMEMD 0x00554640 -- initialiser of DAT_00ABCA10 (fused ctor + atexit)
// SYNTHETIC: GAMEMD 0x00554680 -- exit-time destructor stub of DAT_00ABCA10
DynamicVectorClass<LightSourceClass*> DAT_00ABCA10;
