// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp LocomotionClass.h / Interfaces.h (consult-only).
//
// LocomotionClass::Save (IPersistStream::Save, __stdcall). It serialises the
// locomotor to an IStream: first the 4-byte `this` pointer (a swizzle key the
// Load path remaps), then Size() raw bytes of the object, then — if the caller
// asked to clear the dirty flag — zeroes the byte at this+0x11.
//
// This TU reuses the primary COM vtable binding from locomotion_class_methods.h
// (Size() lives at vtable slot 9 == [vptr+0x24], a __thiscall). It additionally
// needs the IStream vtable shape so that IStream::Write resolves to the exact
// indexed thiscall the retail code performs: CALL [streamvptr+0x10].
//   IStream vtable: QueryInterface(0x0) AddRef(0x4) Release(0x8) Read(0xC)
//                   Write(0x10) ...   => Write is slot 4, byte offset 0x10.
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_SAVE_METHODS_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_SAVE_METHODS_H

#include "locomotion_class_methods.h"

// Minimal IStream COM binding: only the slots up to and including Write must be
// laid out, so Write lands at vtable byte offset 0x10 exactly as the disasm
// shows ([EAX+0x10] / [EBX+0x10]).
struct Gg_IStream
{
    // vptr implicit at +0x00.
    virtual HRESULT __stdcall QueryInterface(Gg_REFIID* iid, void** ppv) = 0;       // 0x00
    virtual ULONG   __stdcall AddRef() = 0;                                         // 0x04
    virtual ULONG   __stdcall Release() = 0;                                        // 0x08
    virtual HRESULT __stdcall Read(void* pv, ULONG cb, ULONG* pcbRead) = 0;         // 0x0C
    virtual HRESULT __stdcall Write(const void* pv, ULONG cb, ULONG* pcbWrite) = 0; // 0x10
};

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_SAVE_METHODS_H
