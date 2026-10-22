// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Shared Session receiver extracted from its existing Resume declaration.
// GameMode0: 0x69BAB0; word table307A: 0x69BBF0/0x69BC20;
// InGameFrameActive30D8: 0x69BAB0. Untouched ranges remain opaque.
#ifndef GG_MATCH_LAYOUT_SESSION_CLASS_H
#define GG_MATCH_LAYOUT_SESSION_CLASS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct SessionClass
{
    int  GameMode;              // +0x0000
    char unknown_04[0x307A - 4];
    unsigned short unknown_307A[8]; // 0x69BBF0: LEA [ECX+EDX*2+0x307A], limit7
    char unknown_308A[0x30D8 - 0x308A];
    char InGameFrameActive;     // +0x30D8

    // Declaration: GAMEMD 0x69BAB0 (decl; reloc)
    void Resume();
    void FUN_0069BBF0(int index);
    unsigned short FUN_0069BC20(int id);
    // Declaration: GAMEMD 0x697E70 (decl; reloc) -- AL result, stack pointer, RET4.
    bool FUN_00697E70(void* house);
    // Declaration: GAMEMD 0x69AE90 (decl; reloc) -- progress argument, RET4.
    void FUN_0069AE90(int delay);
    // Declaration: GAMEMD 0x69BC60 (decl; reloc) -- slot index argument, EAX result, RET4.
    int FUN_0069BC60(int index);
};
GG_STATIC_ASSERT(offsetof(SessionClass, GameMode) == 0);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_307A) == 0x307A);
GG_STATIC_ASSERT(sizeof(((SessionClass*)0)->unknown_307A) == 0x10);
GG_STATIC_ASSERT(offsetof(SessionClass, InGameFrameActive) == 0x30D8);

// GLOBAL: GAMEMD 0xA8B238
extern SessionClass Session_00A8B238;

#endif // GG_MATCH_LAYOUT_SESSION_CLASS_H
