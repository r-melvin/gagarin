// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below. The window
//   between the loading-progress code and the dialog code holds LightConvertClass (the
//   palette-light object, 0x1B4 bytes) ahead of LinkClass at 0x5565F0, so it gets its own
//   file rather than link_class_methods.cpp.
//
//   Address index: 0x556520.

#include "_layout/light_convert_class.h"

// FUNCTION: GAMEMD 0x490400 (decl; reloc) -- the ConvertClass destructor body, which this
// class runs after reinstalling its own vtable. The base class has no canonical header here.
void __fastcall FUN_00490400(LightConvertClass* self);

// The scalar deleting form of the destructor (??_G); the destructor body is inlined into it.
// FUNCTION: GAMEMD 0x556520
LightConvertClass::~LightConvertClass()
{
    FUN_00490400(this);
}
