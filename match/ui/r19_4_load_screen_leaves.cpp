// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Load-screen helpers over
//   the same receiver as match/ui/load_screen_side_caption_methods.cpp; the receiver here is a
//   separate placeholder view of the members touched.
//
// Address index: 0x642B60

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "load_screen_side_caption_methods.h"
#include "../_layout/session_class.h"
#include "../network/transport/conn_types.h"

// STRING: GAMEMD 0x836ECC  "LightGrey"
extern const char STR_00836ECC[];

struct LoadScreenView_00642B60
{
    char _pad000[0x80];
    int  PlayerSide;       // +0x0080

    void* PickCaptionGadget();
};
GG_STATIC_ASSERT(offsetof(LoadScreenView_00642B60, PlayerSide) == 0x80);

// FUNCTION: GAMEMD 0x642B60
// Find the load-screen caption gadget: the neutral one for a spectating local player in a
// network game, otherwise the one for the player's side.
void* LoadScreenView_00642B60::PickCaptionGadget()
{
    if ((Session_00A8B238.GameMode == 3 || Session_00A8B238.GameMode == 4) &&
        Players_00A8DA78[0]->unknown_6B == -1) {
        return FindGadgetByCaption_0068CA50(STR_00836ECC, 1);
    }
    if (PlayerSide == 0) {
        return FindGadgetByCaption_0068CA50(STR_00836EC0, 1);
    }
    return FindGadgetByCaption_0068CA50(STR_00836EB4, 1);
}
