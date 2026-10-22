// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Argument slots and callee bindings read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x434B90.
//
// The single-line text draw at 0x434B90.
//
// Naming: YRpp binds this address to a *non-static* `BitText::Print`,
// and that cannot be right — retail never reads ECX. The receiver of all four
// calls in the body is the first stack argument, and `RET 0x1C` accounts for
// seven stack arguments with nothing left over for a `this`. So this is a free
// __stdcall function, and it keeps its Ghidra placeholder name rather than a
// YRpp name that the bytes contradict.
//
// The first argument is what YRpp calls the font, passed by value there; it is
// a pointer here, since it is loaded into ECX as the receiver for 0x4348F0,
// 0x434110, 0x434500 and 0x434990.
#ifndef GG_MATCH_UI_BIT_TEXT_PRINT_METHODS_H
#define GG_MATCH_UI_BIT_TEXT_PRINT_METHODS_H

class Surface;

// BitFont — the four methods this draw path drives. All are direct (non-virtual)
// __thiscall calls at fixed addresses, so they are declared without bodies and
// the compiler emits reloc-normalised direct calls.
class BitFont
{
public:
    void FUN_004348F0(Surface* surface);                        // GAMEMD 0x4348F0
    void FUN_00434110(int value);                               // GAMEMD 0x434110
    int  FUN_00434500(const unsigned short* text, int a, int b,
                      int c, int d);                            // GAMEMD 0x434500
    void FUN_00434990(Surface* surface);                        // GAMEMD 0x434990
};

// FUNCTION: GAMEMD 0x434B90
int __stdcall FUN_00434B90(BitFont* font, Surface* surface, const unsigned short* text,
                           int arg4, int arg5, int arg6, int arg7);

#endif  // GG_MATCH_UI_BIT_TEXT_PRINT_METHODS_H
