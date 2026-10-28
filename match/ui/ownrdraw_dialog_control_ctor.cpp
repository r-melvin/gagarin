// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: 0x624110 stores the SimpleDialogControl vtable (0x7EF738, RTTI
//   .?AVSimpleDialogControl@OwnerDraw@@) and zeroes the word at +0x04 and the byte at +0x08.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2

namespace OwnerDraw {
class DialogControl
{
public:
    virtual ~DialogControl();
};

class SimpleDialogControl : public DialogControl
{
public:
    // FUNCTION: GAMEMD 0x624110
    SimpleDialogControl();
    int  unknown_04;   // +0x04
    bool unknown_08;   // +0x08
};
}

// FUNCTION: GAMEMD 0x624110
OwnerDraw::SimpleDialogControl::SimpleDialogControl()
    : unknown_04(0), unknown_08(false)
{
}
