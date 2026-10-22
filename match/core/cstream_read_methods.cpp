// Provenance: own-binary-via-Ghidra
//
// CStreamClass (COM stream wrapper, vtable 0x7E5DAC): the block-decompressing
// Read in slot 3. Each block on the underlying stream is an 8-byte header
// (compressed size, decompressed size) followed by the compressed bytes,
// which are expanded into the output buffer through the fastcall
// decompressor at 0x55C0E0.

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

typedef unsigned long ULONG;

extern void __stdcall _com_issue_error(long hr);   // retail 0x7DC720, not matched

// FUNCTION placeholder: retail 0x55C0E0, fastcall block decompressor.
int FUN_0055c0e0(void const* src, unsigned src_len, void* dst,
                 unsigned* dst_len, void* work);

struct IStreamView
{
    virtual long __stdcall QueryInterface(void const* iid, void** out) = 0;
    virtual ULONG __stdcall AddRef() = 0;
    virtual ULONG __stdcall Release() = 0;
    virtual long __stdcall Read(void* pv, ULONG cb, ULONG* read) = 0;
};

// _com_ptr_t<IStream>::operator-> shape.
struct IStreamViewPtr
{
    IStreamView* m_pInterface;
    IStreamView* operator->() const
    {
        if (m_pInterface == 0)
        {
            _com_issue_error(0x80004003);   // E_POINTER
        }
        return m_pInterface;
    }
};

struct CStreamBlockHeader
{
    int CompressedSize;     // +0x0
    int UncompressedSize;   // +0x4
};

class CStreamClass
{
public:
    long __stdcall Read(void* pv, long cb, ULONG* read);

    void*              vftable;      // +0x00
    int                unknown_04;   // +0x04
    IStreamViewPtr     Stream;       // +0x08
    int                unknown_0C;   // +0x0C
    bool               Reading;      // +0x10
    bool               Writing;      // +0x11
    char               unknown_12[2];
    int                Remaining;    // +0x14
    char*              OutBuffer;    // +0x18
    char*              InBuffer;     // +0x1C
    int                unknown_20;   // +0x20
    CStreamBlockHeader Header;       // +0x24
};
GG_STATIC_ASSERT(offsetof(CStreamClass, Stream) == 0x08);
GG_STATIC_ASSERT(offsetof(CStreamClass, Reading) == 0x10);
GG_STATIC_ASSERT(offsetof(CStreamClass, Writing) == 0x11);
GG_STATIC_ASSERT(offsetof(CStreamClass, Remaining) == 0x14);
GG_STATIC_ASSERT(offsetof(CStreamClass, OutBuffer) == 0x18);
GG_STATIC_ASSERT(offsetof(CStreamClass, InBuffer) == 0x1C);
GG_STATIC_ASSERT(offsetof(CStreamClass, Header) == 0x24);

// FUNCTION: GAMEMD 0x4A2B60
long __stdcall CStreamClass::Read(void* pv, long cb, ULONG* read)
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
    if (Stream.m_pInterface == 0)
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
