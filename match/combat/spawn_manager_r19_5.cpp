// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 (Ghidra disasm at each
//   address below). Implemented on the canonical SpawnManagerClass.
//
// reccmp annotations (ascending by retail address):
//   FUNCTION: GAMEMD 0x6B6FA0  SpawnManagerClass::SpawnManagerClass(NoInit)

#include "../_layout/spawn_manager_class.h"
#include "../core/vector_class_operations.h"

// FUNCTION: GAMEMD 0x6B6FA0
// NoInit constructor (save-game load path): base NoInit constructor, an empty
// growable node vector (step 10), both timers started at the current frame
// with no time left, and the four COM vtable pointers.
SpawnManagerClass::SpawnManagerClass(const AbstractNoInit& noInit)
    : AbstractClass(noInit), SpawnedNodes(0, 0), SpawnTimer(0), UpdateTimer(0)
{
}

// SYNTHETIC: GAMEMD 0x6B8140 -- SpawnManagerClass scalar deleting destructor, emitted by the compiler from the
// virtual destructor where this TU seats the vtable.
