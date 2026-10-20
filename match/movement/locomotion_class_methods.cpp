// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp LocomotionClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x55A950  LocomotionClass::AddRef      (__stdcall)
//   FUNCTION: GAMEMD 0x55A970  LocomotionClass::Release     (__stdcall)
//   FUNCTION: GAMEMD 0x55AB40  LocomotionClass::GetSizeMax  (__stdcall)

#include "locomotion_class_methods.h"

// Win32 import: indirect IAT call (FF15) — matches CALL dword ptr [0x7E11CC].
extern "C" __declspec(dllimport) LONG __stdcall InterlockedIncrement(LONG volatile* Addend);
extern "C" __declspec(dllimport) LONG __stdcall InterlockedDecrement(LONG volatile* Addend);

// Global locomotor instance counter at 0x00ABCD3C.
extern int LocomotionClass_Count;

// FUNCTION: GAMEMD 0x55A950  (__stdcall)
// Mirror of Release below: bump the global locomotor census, then the object's
// own interlocked refcount (IAT call CALL dword ptr [0x7E11C8]).
ULONG __stdcall LocomotionClass::AddRef()
{
    ++LocomotionClass_Count;
    return InterlockedIncrement(&this->RefCount);
}

// FUNCTION: GAMEMD 0x55A970  (__stdcall)
ULONG __stdcall LocomotionClass::Release()
{
    --LocomotionClass_Count;
    LONG count = InterlockedDecrement(&this->RefCount);
    if (count == 0 && this != 0)
        delete this;            // virtual deleting dtor: CALL [vtbl+0x20] (flag 1)
    return count;
}

// FUNCTION: GAMEMD 0x55AB40  (__stdcall)
HRESULT __stdcall LocomotionClass::GetSizeMax(Gg_ULARGE_INTEGER* pcbSize)
{
    if (pcbSize == 0)
        return (HRESULT)0x80004003;   // E_POINTER

    int size = this->Size();          // CALL [vtbl+0x24]
    pcbSize->QuadPart = (unsigned long)(size + 4);
    return 0;                         // S_OK
}
