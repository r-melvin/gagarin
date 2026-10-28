// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   SuperClass members read off retail gamemd.exe v1.001, round 16. The object is seen through
//   SuperView_r16, which carries only the members these bodies touch. Address index: 0x6CB2E0.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/vector_class_operations.h"

// The animation a super weapon plays, as far as its "got invalid" byte.
struct SuperAnimView_r16
{
    char unknown_00[0x195];
    unsigned char GotInvalid;   // +0x195
};
GG_STATIC_ASSERT(offsetof(SuperAnimView_r16, GotInvalid) == 0x195);

class SuperView_r16;

// GLOBAL: GAMEMD 0xB0F5B8 -- a list of super weapons (vptr +0x00, Items +0x04, Count +0x10).
extern DynamicVectorClass<SuperView_r16*> DAT_00B0F5B8_r16;

class SuperView_r16
{
public:
    void FUN_006CB2E0();

    char unknown_00[0x68];
    SuperAnimView_r16* Animation;        // +0x68
    unsigned char AnimationGotInvalid;   // +0x6C
};
GG_STATIC_ASSERT(offsetof(SuperView_r16, Animation) == 0x68);
GG_STATIC_ASSERT(offsetof(SuperView_r16, AnimationGotInvalid) == 0x6C);

// FUNCTION: GAMEMD 0x6CB2E0
// Let go of the animation and take the super weapon off the list, once per reason it was on it.
void SuperView_r16::FUN_006CB2E0()
{
    if (Animation) {
        Animation->GotInvalid = 0;
        Animation = 0;
        DAT_00B0F5B8_r16.RemoveItem(this);
    }
    if (AnimationGotInvalid) {
        DAT_00B0F5B8_r16.RemoveItem(this);
        AnimationGotInvalid = 0;
    }
}
