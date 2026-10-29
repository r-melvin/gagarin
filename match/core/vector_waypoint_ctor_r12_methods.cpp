// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   VectorClass<WaypointClass> constructor taking a capacity and optional storage, read off retail
//   gamemd.exe v1.001 (vtable 0x7F6EF4). The other members of the instantiation are in
//   vector_dtor_element_slot_methods.cpp.
//   Address index: 0x764760.

#include "vector_class_operations.h"
#include "../_layout/waypoint_class.h"

// FUNCTION: GAMEMD 0x764760
// VectorClass<WaypointClass>::VectorClass(int, WaypointClass*)
template class VectorClass<WaypointClass>;
