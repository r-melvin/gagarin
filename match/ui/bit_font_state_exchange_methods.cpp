// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; complete entry instructions at 0x433CE0/0x434100.
#include "bit_font_state_exchange_methods.h"
// FUNCTION: GAMEMD 0x433CE0
unsigned char BitFontStateView::SwapFlag(unsigned char value)
{
    unsigned char previous = Flag;
    Flag = value;
    return previous;
}
// FUNCTION: GAMEMD 0x434100
int BitFontStateView::SwapTabWidth(int value)
{
    int previous = TabWidth;
    TabWidth = value;
    return previous;
}
