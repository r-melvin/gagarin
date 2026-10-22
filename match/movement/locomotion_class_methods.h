// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// SaveView_0055AA60 is an address-local partial view of the IPersistStream +
// ILocomotion prefix used by the saved-function candidate. It is not a claim
// about a complete object's identity or size. The modeled IUnknown and
// IPersistStream members use the __stdcall ABI: the `this` pointer is
// pushed on the stack as the implicit first parameter (NOT in ECX), exactly as
// the disassembly shows ([ESP+0xc] / [ESP+8]).
//
// The partial view records the primary COM vtable shape used by the saved
// method candidate:
//   * Release's guarded `delete this` -> CALL [vtbl+0x20]  (deleting dtor, slot 8)
//   * GetSizeMax's Size()             -> CALL [vtbl+0x24]  (slot 9)
// The first 8 slots are QueryInterface, AddRef, Release, GetClassID, IsDirty,
// Load, Save, GetSizeMax (all __stdcall); slot 8 is the destructor; slot 9 is
// the __thiscall int Size(). RefCount sits at +0x14 (InterlockedDecrement'd).
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_METHODS_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

typedef long  HRESULT;
typedef long  LONG;
typedef unsigned long ULONG;

struct Gg_REFIID;        // opaque; only used as a parameter token below
struct Gg_IStream;

// pcbSize output for GetSizeMax: the Win32 ULARGE_INTEGER union. Retail stores
// LowPart (eax) then an immediate-0 HighPart, i.e. a single 64-bit QuadPart
// assignment of a zero-extended 32-bit value.
struct Gg_ULARGE_INTEGER
{
    union
    {
        struct
        {
            unsigned long LowPart;   // +0x0
            unsigned long HighPart;  // +0x4
        };
        unsigned __int64 QuadPart;   // +0x0
    };
};

struct SaveView_0055AA60
{
    // vptr is implicit at +0x00 (single primary COM vtable).
    char gap_04[0x10];       // +0x04
    LONG RefCount;           // +0x14

    // --- vtable slots 0..9, in COM order ---
    virtual HRESULT __stdcall QueryInterface(Gg_REFIID* iid, void** ppv) = 0;  // 0
    virtual ULONG   __stdcall AddRef();                                        // 1
    virtual ULONG   __stdcall Release();                                       // 2
    virtual HRESULT __stdcall GetClassID(void* pClassID) = 0;                  // 3
    virtual HRESULT __stdcall IsDirty() = 0;                                   // 4
    virtual HRESULT __stdcall Load(Gg_IStream* pStm) = 0;                      // 5
    virtual HRESULT __stdcall Save(Gg_IStream* pStm, LONG fClear) = 0;         // 6
    virtual HRESULT __stdcall GetSizeMax(Gg_ULARGE_INTEGER* pcbSize);          // 7
    virtual ~SaveView_0055AA60();                                               // 8
    virtual int Size() = 0;                                                    // 9 (__thiscall)
};

GG_STATIC_ASSERT(offsetof(SaveView_0055AA60, RefCount) == 0x14);

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_METHODS_H
