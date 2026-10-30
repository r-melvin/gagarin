// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Load-time (no-init)
//   constructors that run the base no-init chain and reseat the vtables.
//
// Address index: 0x65A7E0

#include "../FUNCTION.H"

// FUNCTION: GAMEMD 0x65A7E0
// RadioClass no-init constructor: base chain, then the link vector's vtable only.
RadioClass::RadioClass(const AbstractNoInit& noInit)
    : MissionClass(noInit), RadioLinks(noInit)
{
}
