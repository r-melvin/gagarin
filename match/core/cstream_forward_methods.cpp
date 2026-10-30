// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Existing native-backed CStreamClass bodies consolidated without expression changes.
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /Ob2
#include "../_layout/cstream_class.h"
#include "lz_pipe.h"

// GLOBAL: GAMEMD 0xABCD3C - live COM-object counter.
extern int DAT_00ABCD3C;
int FUN_0055c0e0(void const* src, unsigned src_len, void* dst,
                 unsigned* dst_len, void* work);

// FUNCTION: GAMEMD 0x4A2820
CStreamClass::CStreamClass()
    : RefCount(0), Reading(false), Writing(false), Remaining(0),
      OutBuffer(new char[0x10000]), InBuffer(new char[0x10000]),
      unknown_20(new char[0x10000])
{
    Header.CompressedSize = 0xFFFF;
}

// FUNCTION: GAMEMD 0x4A2930
ULONG __stdcall CStreamClass::AddRef()
{
    ++DAT_00ABCD3C;
    return InterlockedIncrement(&RefCount);
}

// FUNCTION: GAMEMD 0x4A2950
ULONG __stdcall CStreamClass::Release()
{
    --DAT_00ABCD3C;
    LONG count = InterlockedDecrement(&RefCount);
    if (count == 0)
        delete this;
    return count;
}

// FUNCTION: GAMEMD 0x4A2990
HRESULT __stdcall CStreamClass::QueryInterface(REFIID riid, void** ppv)
{
    if (ppv == 0)
        return E_POINTER;
    *ppv = 0;
    if (riid == IID_IUnknown)
        *ppv = static_cast<IStream*>(this);
    if (riid == IID_IStream)
        *ppv = static_cast<IStream*>(this);
    if (riid == IID_ILinkStream)
        *ppv = static_cast<ILinkStream*>(this);
    if (*ppv == 0)
        return E_NOINTERFACE;
    AddRef();
    return S_OK;
}

// FUNCTION: GAMEMD 0x4A2B60
HRESULT __stdcall CStreamClass::Read(void* pv, ULONG cb, ULONG* read)
{
    long left = cb;
    if (pv == 0)
    {
        return 0x80004003;   // E_POINTER
    }
    if (left < 0)
    {
        return 0x80070057;   // E_INVALIDARG
    }
    if (Stream == 0)
    {
        return 0x80004005;   // E_FAIL
    }
    if (Writing)
    {
        return 0x80004005;
    }
    Reading = true;
    if (read != 0)
    {
        *read = 0;
    }
    while (left > 0)
    {
        if (Remaining > 0)
        {
            int n = left;
            if (left >= Remaining)
            {
                n = Remaining;
            }
            memmove(pv, OutBuffer + Header.UncompressedSize - Remaining, n);
            pv = (char*)pv + n;
            left -= n;
            Remaining -= n;
        }
        if (left == 0)
        {
            break;
        }
        ULONG got = 0;
        long hr = Stream->Read(&Header, sizeof(Header), &got);
        if (hr < 0)
        {
            return hr;
        }
        if (got != sizeof(Header))
        {
            return 0x80004005;
        }
        hr = Stream->Read(InBuffer, Header.CompressedSize, &got);
        if (hr < 0)
        {
            return hr;
        }
        if (got != (ULONG)Header.CompressedSize)
        {
            return 0x80004005;
        }
        unsigned out_len = 0x10000;
        FUN_0055c0e0(InBuffer, Header.CompressedSize, OutBuffer, &out_len, 0);
        Remaining = Header.UncompressedSize;
    }
    if (read != 0)
    {
        *read = cb;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4A2E00
HRESULT __stdcall CStreamClass::Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER* plibNewPosition)
{
    if (Reading || Writing)
        return E_FAIL;
    return Stream->Seek(dlibMove, dwOrigin, plibNewPosition);
}

// FUNCTION: GAMEMD 0x4A2E50
HRESULT __stdcall CStreamClass::SetSize(ULARGE_INTEGER libNewSize)
{
    if (Reading || Writing)
        return E_FAIL;
    return Stream->SetSize(libNewSize);
}

// FUNCTION: GAMEMD 0x4A2EA0
HRESULT __stdcall CStreamClass::CopyTo(IStream* pstm, ULARGE_INTEGER cb, ULARGE_INTEGER* pcbRead,
                                       ULARGE_INTEGER* pcbWritten)
{
    return Stream->CopyTo(pstm, cb, pcbRead, pcbWritten);
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

// FUNCTION: GAMEMD 0x4A2F40
HRESULT __stdcall CStreamClass::LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
{
    return Stream->LockRegion(libOffset, cb, dwLockType);
}

// FUNCTION: GAMEMD 0x4A2F80
HRESULT __stdcall CStreamClass::UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
{
    return Stream->UnlockRegion(libOffset, cb, dwLockType);
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

// FUNCTION: GAMEMD 0x4A3020
// Compresses `count` bytes into the staging buffer and writes them to the wrapped
// stream as one block: the 8-byte header first, then the compressed bytes.
HRESULT CStreamClass::FUN_004A3020(char* buffer, int count)
{
    unsigned int compressed = count;
    lzo1x_1_compress((unsigned char*)buffer, count, (unsigned char*)InBuffer, &compressed, unknown_20);
    Header.UncompressedSize = 0x10000;
    ULONG written = 0;
    Header.CompressedSize = compressed;
    HRESULT hr = Stream->Write(&Header, 8, &written);
    if (hr >= 0) {
        if (written != 8)
            return E_FAIL;
        hr = Stream->Write(InBuffer, compressed, &written);
        if (hr >= 0)
            hr = written != compressed ? E_FAIL : S_OK;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x4A30E0
HRESULT CStreamClass::FUN_004A30E0()
{
    if (Writing && Remaining > 0) {
        if ((IStream*)Stream == 0)
            return E_FAIL;
        return FUN_004A3020(OutBuffer, Remaining);
    }
    return S_OK;
}

// SYNTHETIC: GAMEMD 0x4A3220 -- compiler-generated ILinkStream QI adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x4A3230 -- compiler-generated ILinkStream AddRef adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x4A3240 -- compiler-generated ILinkStream Release adjustor thunk (this -= 0x4).
