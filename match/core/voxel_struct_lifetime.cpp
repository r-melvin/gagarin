// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native 0x5F61A0 deletes the model at +0 and animation at +4, clearing each
// field after its delete. Their nonvirtual destructor targets are native
// 0x755D10 and 0x5BD5A0, respectively.
#include "../_layout/components.h"

// FUNCTION: GAMEMD 0x5F61A0
VoxelStruct::~VoxelStruct()
{
    delete unknown_00;
    unknown_00 = 0;
    delete HVAData;
    HVAData = 0;
}
