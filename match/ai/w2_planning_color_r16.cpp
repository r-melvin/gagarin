// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Colour blends packed
//   into the display's native pixel format (PlanMgr.cpp address range).
//
// Address index: 0x63CF10 0x63CFC0 0x63D070

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/color_struct.h"
#include "../_layout/house_class.h"
#include "../renderer/pixel_pack_methods.h"

// The packing as the two marker-colour functions below expand it: the green term is
// combined first, then blue, then red (the shared PackPixel orders the terms R, G, B).
inline unsigned int PackPixelGBR(const ColorStruct& color)
{
    unsigned char red = color.R >> gg_b_translucent_pixel_format.loss0;
    unsigned char green = color.G >> gg_b_translucent_pixel_format.loss1;
    unsigned char blue = color.B >> gg_b_translucent_pixel_format.loss2;
    return (green << gg_b_translucent_pixel_format.pos1) | (blue << gg_b_translucent_pixel_format.pos2) | (red << gg_b_translucent_pixel_format.pos0);
}

// Only the owning house of a techno is read here.
struct TechnoOwner_0063CF10
{
    char _pad000[0x21C];    // +0x0000
    HouseClass* Owner;      // +0x021C
};
GG_STATIC_ASSERT(offsetof(TechnoOwner_0063CF10, Owner) == 0x21C);

// GLOBAL: GAMEMD 0xA83D4C -- the player's house.
extern HouseClass* DAT_00A83D4C;
// GLOBAL: GAMEMD 0xA8022C -- HouseClass::Array.Items.
extern HouseClass** DAT_00A8022C;
// GLOBAL: GAMEMD 0xA83CD9 -- the colour a planning marker is drawn in normally.
extern ColorStruct DAT_00A83CD9;
// GLOBAL: GAMEMD 0xA80220 -- white, the colour of a selected or current-node member.
extern ColorStruct DAT_00A80220;

// FUNCTION: GAMEMD 0x63CF10
// The owner's colour blended 80 toward the normal marker colour, packed to the native format.
unsigned int __fastcall FUN_0063CF10(TechnoOwner_0063CF10* techno)
{
    int index = techno->Owner->ArrayIndex;
    if (techno->Owner->IsControlledByCurrentPlayer() && DAT_00A83D4C) {
        index = DAT_00A83D4C->ArrayIndex;
    }
    ColorStruct color = DAT_00A8022C[index]->Color;
    color.FUN_006612C0(0x50, DAT_00A83CD9);
    return PackPixelGBR(color);
}

// FUNCTION: GAMEMD 0x63CFC0
// The owner's colour blended 100 toward white, packed to the native format.
unsigned int __fastcall FUN_0063CFC0(TechnoOwner_0063CF10* techno)
{
    int index = techno->Owner->ArrayIndex;
    if (techno->Owner->IsControlledByCurrentPlayer() && DAT_00A83D4C) {
        index = DAT_00A83D4C->ArrayIndex;
    }
    ColorStruct color = DAT_00A8022C[index]->Color;
    color.FUN_006612C0(100, DAT_00A80220);
    return PackPixelGBR(color);
}

// FUNCTION: GAMEMD 0x63D070
// Blend a colour toward a target by `ratio` and pack the result into the native pixel format.
unsigned int __fastcall FUN_0063D070(const ColorStruct* color, const ColorStruct* target, int ratio)
{
    ColorStruct blended = *color;
    blended.FUN_006612C0(ratio, *target);
    return PackPixel(blended);
}
