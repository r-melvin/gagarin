// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//
// The global vector of every TemporalClass (retail 0x00B0EC60, TemporalClass::Array).
// Defined here under /Ob2 so the run-time initialiser (constructor plus atexit
// registration, 0x71A3D0) fuses into one function and the exit stub 0x71A410 follows it.
#include "../core/vector_class_operations.h"

class TemporalClass;

// GLOBAL: GAMEMD 0x00B0EC60
// SYNTHETIC: GAMEMD 0x0071A410 -- exit-time destructor stub of DAT_00B0EC60
// SYNTHETIC: GAMEMD 0x0071A3D0 -- initialiser of DAT_00B0EC60
DynamicVectorClass<TemporalClass*> DAT_00B0EC60;
