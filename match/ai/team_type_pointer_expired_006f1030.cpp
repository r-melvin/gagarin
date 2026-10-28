// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail 0x6F1030, read instruction by instruction from gamemd.exe v1.001: a TeamType-sized
// object forgets a pointer it holds in four fields and forwards the notice to the object still
// stored at +0xE0 (virtual slot 10).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Forward_006F1030 {
    virtual void vf_000();
    virtual void vf_001();
    virtual void vf_002();
    virtual void vf_003();
    virtual void vf_004();
    virtual void vf_005();
    virtual void vf_006();
    virtual void vf_007();
    virtual void vf_008();
    virtual void vf_009();
    virtual void vf_010(void* target, int arg);
};

struct TeamTypeView_006F1030 {
    unsigned char unknown_00[0xC4];
    void* unknown_C4;   // +0x00C4
    unsigned char unknown_C8[8];
    void* unknown_D0;   // +0x00D0
    unsigned char unknown_D4[0xC];
    Forward_006F1030* unknown_E0;   // +0x00E0
    void* unknown_E4;   // +0x00E4

    // FUNCTION: GAMEMD 0x6F1030
    void FUN_006F1030(void* target, int arg);
};
GG_STATIC_ASSERT(offsetof(TeamTypeView_006F1030, unknown_C4) == 0xC4);
GG_STATIC_ASSERT(offsetof(TeamTypeView_006F1030, unknown_D0) == 0xD0);
GG_STATIC_ASSERT(offsetof(TeamTypeView_006F1030, unknown_E0) == 0xE0);
GG_STATIC_ASSERT(offsetof(TeamTypeView_006F1030, unknown_E4) == 0xE4);

// FUNCTION: GAMEMD 0x6F1030
// Clears every field that holds the pointer, then forwards the notice to the object at +0xE0.
void TeamTypeView_006F1030::FUN_006F1030(void* target, int arg)
{
    if (unknown_D0 == target) {
        unknown_D0 = 0;
    }
    if (unknown_C4 == target) {
        unknown_C4 = 0;
    }
    if (unknown_E4 == target) {
        unknown_E4 = 0;
    }
    if (unknown_E0 == target) {
        unknown_E0 = 0;
    }
    if (unknown_E0 != 0) {
        unknown_E0->vf_010(target, arg);
    }
}
