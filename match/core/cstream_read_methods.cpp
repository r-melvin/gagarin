// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2
//
// CStreamClass (layout and tables in _layout/cstream_class.h): the
// constructor, the IUnknown bodies and the block-decompressing Read in slot 3.
// Each block on the underlying stream is an 8-byte header (compressed size,
// decompressed size) followed by the compressed bytes, which are expanded into
// the output buffer through the fastcall decompressor at 0x55C0E0. Defining
// the constructor makes VC6 emit both tables here, and with them the
// ILinkStream-side (+4) IUnknown adjustor thunks.

#include "../_layout/cstream_class.h"

// GLOBAL: GAMEMD 0xABCD3C - live COM-object counter.
extern int DAT_00ABCD3C;

// FUNCTION placeholder: retail 0x55C0E0, fastcall block decompressor.
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

// SYNTHETIC: GAMEMD 0x4A3220 -- compiler-generated ILinkStream QI adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x4A3230 -- compiler-generated ILinkStream AddRef adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x4A3240 -- compiler-generated ILinkStream Release adjustor thunk (this -= 0x4).
