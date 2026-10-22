// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and global addresses read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x55B880. The two globals it touches, 0x008B40CC
//   (Items) and 0x008B40D8 (Count), sit at +0x04 and +0x10 of a
//   DynamicVectorClass, which pins the vector object to 0x008B40C8. Name
//   cross-checked against YRpp (`LogicClass::PointerGotInvalid`).
#ifndef GG_MATCH_CORE_LOGIC_CLASS_POINTER_METHODS_H
#define GG_MATCH_CORE_LOGIC_CLASS_POINTER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"

struct AbstractClass;

// The only AbstractType this list holds (`CMP EAX,0x2C`).
#define ABS_LOGIC_MEMBER 0x2C

// WhatAmI() — virtual at primary-vtable slot +0x2C, zero-argument, so the
// tree's __fastcall-fn-pointer idiom is the right tool here.
typedef int (__fastcall* WhatAmIFunc)(AbstractClass*);
#define LOGIC_WHAT_AM_I(o) ((*(WhatAmIFunc*)(*(char**)(o) + 0x2c))(o))

// GLOBAL: GAMEMD 0x008B40C8 — the logic list.
extern DynamicVectorClassLayout LogicArray;

struct LogicClass
{
    void PointerGotInvalid(AbstractClass* invalid, bool removed);   // GAMEMD 0x55B880
};

#endif  // GG_MATCH_CORE_LOGIC_CLASS_POINTER_METHODS_H
