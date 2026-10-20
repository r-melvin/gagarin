// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Shape and constants read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x55A9B0: `RET 0xC` with nothing in
//   ECX and the out-pointer at [ESP+0xC] make this a COM __stdcall with the
//   object as the first stacked argument; the four 16-byte compares are
//   `MOV ECX,4; REPE CMPSD` against the immediates 0x7F7C90, 0x7F7C80,
//   0x7ED358 and 0x7F7C70, whose bytes (`ghidra memory read`) are
//   00000000-0000-0000-C000-000000000046 (IID_IUnknown),
//   00000109-...-46 (IID_IPersistStream), 90320f07-4198-d111-b709-00a024ddafd1
//   (the engine's own locomotor interface) and 0000010c-...-46 (IID_IPersist).
//   IUnknown and the locomotor interface answer with the object plus four
//   (`LEA ECX,[EDX+4]` under a null test), IPersistStream and IPersist with the
//   object itself, so the IPersistStream vptr sits at +0 and the locomotor
//   vptr at +4. The final AddRef goes through the +0 vptr's slot 1 with the
//   object pushed (`MOV EAX,[EDX]; PUSH EDX; CALL [EAX+4]`). The HRESULTs are
//   0x80004003 (E_POINTER) and 0x80004002 (E_NOINTERFACE). YRpp names the
//   function (LocomotionClass::QueryInterface, static) - name-only, consult-only.
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_QUERY_INTERFACE_METHODS_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_QUERY_INTERFACE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

typedef long HRESULT;

struct Guid_0055A9B0 { char Bytes[16]; };
GG_STATIC_ASSERT(sizeof(Guid_0055A9B0) == 16);

// GLOBAL: GAMEMD 0x7F7C90 — IID_IUnknown.
extern const Guid_0055A9B0 IID_IUnknown_007F7C90;
// GLOBAL: GAMEMD 0x7F7C80 — IID_IPersistStream.
extern const Guid_0055A9B0 IID_IPersistStream_007F7C80;
// GLOBAL: GAMEMD 0x7ED358 — the locomotor interface id.
extern const Guid_0055A9B0 IID_ILocomotion_007ED358;
// GLOBAL: GAMEMD 0x7F7C70 — IID_IPersist.
extern const Guid_0055A9B0 IID_IPersist_007F7C70;

// The two COM bases. Only slot order matters: the IUnknown triple heads both,
// and the locomotor's own methods are never dispatched here.
struct IPersistStream_0055A9B0
{
    virtual HRESULT       __stdcall QueryInterface(const Guid_0055A9B0* riid, void** ppv) = 0; // +0x00
    virtual unsigned long __stdcall AddRef() = 0;                                              // +0x04
    virtual unsigned long __stdcall Release() = 0;                                             // +0x08
};

struct ILocomotion_0055A9B0
{
    virtual HRESULT       __stdcall QueryInterface(const Guid_0055A9B0* riid, void** ppv) = 0; // +0x00
    virtual unsigned long __stdcall AddRef() = 0;                                              // +0x04
    virtual unsigned long __stdcall Release() = 0;                                             // +0x08
};

// LocomotionClass: the IPersistStream vptr at +0, the locomotor vptr at +4.
struct Loco_0055A9B0 : public IPersistStream_0055A9B0, public ILocomotion_0055A9B0
{
};
GG_STATIC_ASSERT(sizeof(Loco_0055A9B0) == 0x8);

// FUNCTION: GAMEMD 0x55A9B0 — YRpp: LocomotionClass::QueryInterface. COM
// __stdcall: the locomotor arrives as the first stacked argument.
HRESULT __stdcall FUN_0055A9B0(Loco_0055A9B0* self, const Guid_0055A9B0* riid,
                               void** ppv);

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_QUERY_INTERFACE_METHODS_H
