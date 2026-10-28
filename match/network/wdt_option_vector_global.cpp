// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//
// File-scope vector of reference-counted World Domination Tour options
// (rc_ptr<GameOption>, RTTI vtables 0x7F6FD4 / 0x7F6FF4). Defined here under /Ob2 so
// the run-time initialiser (constructor plus atexit registration) fuses into one function
// and the exit stub 0x7660B0 sits 0x40 after it.
#include "world_domination_tour.h"
#include "../core/vector_class_operations.h"

typedef rc_ptr<WorldDominationTour::GameOption> OptionPtr;

// GLOBAL: GAMEMD 0x00B72760
// SYNTHETIC: GAMEMD 0x007660B0 -- exit-time destructor stub of DAT_00B72760
DynamicVectorClass<OptionPtr> DAT_00B72760;
