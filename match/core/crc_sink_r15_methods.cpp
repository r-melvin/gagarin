// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x4A1D90 in the user's retail gamemd.exe v1.001.
//
// Checksum sink (Obj_004A1D30) bodies. Address index: 0x4A1D90.
#include "../_layout/obj_004a1d30.h"

// FUNCTION: GAMEMD 0x4A1D90
// Adds the eight bytes of a double to the checksum.
void Obj_004A1D30::FUN_004A1D90(double value)
{
    double copy = value;
    FUN_004A1DE0(&copy, 8);
}
