// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x4A2E50, 0x4A2EE0, 0x4A2F10, 0x4A2FC0, 0x4A2FF0.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2
//
// CStreamClass IStream methods that forward unchanged to the wrapped stream
// (the smart-pointer dereference raises E_POINTER when it is null).
// Address index: 0x4A2E50 SetSize, 0x4A2EE0 Commit, 0x4A2F10 Revert, 0x4A2FC0 Stat, 0x4A2FF0 Clone.

#include "../_layout/cstream_class.h"

// FUNCTION: GAMEMD 0x4A2E50
HRESULT __stdcall CStreamClass::SetSize(ULARGE_INTEGER libNewSize)
{
    if (Reading || Writing)
        return E_FAIL;
    return Stream->SetSize(libNewSize);
}

// FUNCTION: GAMEMD 0x4A2EE0
HRESULT __stdcall CStreamClass::Commit(DWORD grfCommitFlags)
{
    return Stream->Commit(grfCommitFlags);
}

// FUNCTION: GAMEMD 0x4A2F10
HRESULT __stdcall CStreamClass::Revert()
{
    return Stream->Revert();
}

// FUNCTION: GAMEMD 0x4A2FC0
HRESULT __stdcall CStreamClass::Stat(STATSTG* pstatstg, DWORD grfStatFlag)
{
    return Stream->Stat(pstatstg, grfStatFlag);
}

// FUNCTION: GAMEMD 0x4A2FF0
HRESULT __stdcall CStreamClass::Clone(IStream** ppstm)
{
    return Stream->Clone(ppstm);
}
