// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bodies disassembled from retail gamemd.exe v1.001 at the addresses below.
//
// BuildingClass members, ordered ascending by retail address.
// Address index: 0x43EE50, 0x451F60, 0x4528A0.

#include "../_layout/building_class.h"
#include "../_layout/anim_class.h"
#include "../_layout/anim_type_class.h"
#include "../_layout/cell_class.h"
#include "../core/abstract_class_distance3d_methods.h"

// FUNCTION: GAMEMD 0x4528A0
// PARTIAL: 78.7% -- instruction multiset identical; retail reads both centre
// coordinates through one shared 12-byte stack slot (frame 0xC), this compiles
// two (frame 0x14). Named locals, scoped blocks, const refs and a reused local
// all keep two slots.
// True when the target's centre lies within the type's psychic detection radius
// (in cells) of this building's centre.
bool BuildingClass::FUN_004528A0(AbstractClass* target)
{
    CoordStruct here = vf_18();
    CoordStruct there = target->vf_18();
    int dx = here.X - there.X;
    int dy = here.Y - there.Y;
    int dz = here.Z - there.Z;
    int distance = (int)FUN_004CAC40((double)dx * dx + (double)dy * dy + (double)dz * dz);
    return distance <= Type->PsychicDetectionRadius * 256;
}

// GLOBAL: GAMEMD 0x7F4890 -- 32-entry table of animation frames per facing step.
extern int DAT_007F4890[32];

// FUNCTION: GAMEMD 0x43EE50
// When the building is in its active state and has its Anims[9] animation,
// show the frame for the current primary facing (32 steps) and zero the
// animation's step. Returns the frame, or 0 when nothing was done.
int BuildingClass::FUN_0043EE50()
{
    int frame = 0;
    if (vf_255() && Anims[9]) {
        DirStruct facing = PrimaryFacing.FUN_004C93D0();
        unsigned int whole = *(unsigned int*)&facing;
        frame = DAT_007F4890[((whole >> 10) + 1 >> 1) & 0x1F];
        AnimClass* anim = Anims[9];
        if (anim) {
            anim->Value = frame;
            anim->Step = 0;
        }
    }
    return frame;
}

// FUNCTION: GAMEMD 0x451F60
// For each live animation: hand cell-drawn types the given lighting and tint,
// then set the translucency (15 becomes 16 while the building reports mission
// type 5) on every animation.
void BuildingClass::FUN_00451F60(void* lightConvert, int tint)
{
    for (int i = 0; i < 0x15; i++) {
        AnimClass* anim = Anims[i];
        if (anim) {
            if (anim->Type && anim->Type->ShouldUseCellDrawer) {
                anim->LightConvert = lightConvert;
                anim->TintColor = tint;
            }
            int level = Translucency;
            if (level == 0xF && vf_26(0, 0) == 5)
                level = 0x10;
            for (int j = 0; j < 0x15; j++) {
                if (Anims[j])
                    Anims[j]->TranslucencyLevel = level;
            }
        }
    }
}
