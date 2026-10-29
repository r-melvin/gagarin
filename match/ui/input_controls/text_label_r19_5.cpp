// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the address below.
//   Address index: 0x72A440. Layout and evidence: ui_gadget.h.
#include "controls_views.h"

// FUNCTION: GAMEMD 0x72A440
// A one-cell gadget at (x, y) carrying the text; no width cap (-1), shown, not typing.
TextLabelClass::TextLabelClass(const wchar_t* text, int x, int y, int scheme, int unused)
    : GadgetClass(x, y, 1, 1, 0, 0), unknown_24(0), unknown_28(0), unknown_2C(unused), Text(text),
      SchemeIndex(scheme), MaxWidth(-1), unknown_3C(0), IsHidden(0), IsTyping(0), CharsShown(0),
      unknown_48(0)
{
}
