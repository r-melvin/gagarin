// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor ".?AVCStreamClass@@" (0x81FC30); class hierarchy
//   descriptor attributes 5 (multiple inheritance), base array:
//     CStreamClass          (5 bases)  +0x00
//     IStream          (AU) (2 bases)  +0x00 -> ISequentialStream -> IUnknown
//     ILinkStream      (AU) (1 base)   +0x04 -> IUnknown
//   Tables: 0x7E5DAC (COL offset 0; 14 IStream slots + the scalar deleting
//   destructor 0x4A3110 in slot 14) and 0x7E5D94 (COL offset 4; the three
//   IUnknown adjustor thunks 0x4A3220 / 0x4A3230 / 0x4A3240, then 0x4A2A20 /
//   0x4A2AB0).
//   Layout from the constructor 0x4A2820 (stores +0x08..+0x24, three 0x10000
//   operator new blocks, sizeof 0x2C from the class factory 0x6BEE40) and from
//   Read 0x4A2B60 (+0x08 stream, +0x10/+0x11 direction flags, +0x14 bytes left,
//   +0x18 / +0x1C buffers, +0x24 block header). AddRef / Release 0x4A2930 /
//   0x4A2950 interlock +0x0C.
//
// CStreamClass: an IStream that compresses / decompresses blocks over another
// IStream.
#ifndef GG_MATCH_LAYOUT_CSTREAM_CLASS_H
#define GG_MATCH_LAYOUT_CSTREAM_CLASS_H

#include <stddef.h>
#include <comdef.h>
#include "../_rt/gg_static_assert.h"
#include "i_link_stream.h"

// GLOBAL: GAMEMD 0x7E9530 - the ILinkStream interface id.
extern "C" const IID IID_ILinkStream;

// The 8-byte header in front of every block on the underlying stream.
struct CStreamBlockHeader
{
    int CompressedSize;     // +0x0
    int UncompressedSize;   // +0x4
};
GG_STATIC_ASSERT(sizeof(CStreamBlockHeader) == 8);

// Tables 0x7E5DAC (IStream side) and 0x7E5D94 (ILinkStream side, +0x04); not
// claimed while Write..Clone, the ILinkStream slots and the destructor are unmatched.
class CStreamClass : public IStream, public ILinkStream
{
public:
    // FUNCTION: GAMEMD 0x4A2820 (declaration)
    CStreamClass();

    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);   // 0  0x4A2990
    virtual ULONG __stdcall AddRef();                                     // 1  0x4A2930
    virtual ULONG __stdcall Release();                                    // 2  0x4A2950
    virtual HRESULT __stdcall Read(void* pv, ULONG cb, ULONG* pcbRead);   // 3  0x4A2B60
    virtual HRESULT __stdcall Write(const void* pv, ULONG cb, ULONG* pcbWritten);    // 4  0x4A2CD0
    virtual HRESULT __stdcall Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin,
                                   ULARGE_INTEGER* plibNewPosition);      // 5  0x4A2E00
    virtual HRESULT __stdcall SetSize(ULARGE_INTEGER libNewSize);        // 6  0x4A2E50
    virtual HRESULT __stdcall CopyTo(IStream* pstm, ULARGE_INTEGER cb, ULARGE_INTEGER* pcbRead,
                                     ULARGE_INTEGER* pcbWritten);         // 7  0x4A2EA0
    virtual HRESULT __stdcall Commit(DWORD grfCommitFlags);              // 8  0x4A2EE0
    virtual HRESULT __stdcall Revert();                                   // 9  0x4A2F10
    virtual HRESULT __stdcall LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb,
                                         DWORD dwLockType);               // 10 0x4A2F40
    virtual HRESULT __stdcall UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb,
                                           DWORD dwLockType);             // 11 0x4A2F80
    virtual HRESULT __stdcall Stat(STATSTG* pstatstg, DWORD grfStatFlag); // 12 0x4A2FC0
    virtual HRESULT __stdcall Clone(IStream** ppstm);                    // 13 0x4A2FF0
    virtual void vf_3();                                                  // ILinkStream 3  0x4A2A20
    virtual void vf_4();                                                  // ILinkStream 4  0x4A2AB0
    // Slot 14: the scalar deleting destructor 0x4A3110 carries this body inline.
    virtual ~CStreamClass();

    IStreamPtr         Stream;       // +0x08 ctor @0x4A282A (=0)
    long               RefCount;     // +0x0C ctor @0x4A282D; AddRef / Release interlock it
    bool               Reading;      // +0x10 ctor @0x4A2830
    bool               Writing;      // +0x11 ctor @0x4A2833
    char               unknown_12[2];
    int                Remaining;    // +0x14 ctor @0x4A2836
    char*              OutBuffer;    // +0x18 ctor @0x4A2843 (0x10000 bytes)
    char*              InBuffer;     // +0x1C ctor @0x4A2850 (0x10000 bytes)
    char*              unknown_20;   // +0x20 ctor @0x4A285B (0x10000 bytes)
    CStreamBlockHeader Header;       // +0x24 ctor stores 0xFFFF in the first dword @0x4A286B
};
GG_STATIC_ASSERT((size_t)&reinterpret_cast<const char&>(((CStreamClass*)0)->Stream) == 0x08);
GG_STATIC_ASSERT(offsetof(CStreamClass, RefCount)   == 0x0C);
GG_STATIC_ASSERT(offsetof(CStreamClass, Reading)    == 0x10);
GG_STATIC_ASSERT(offsetof(CStreamClass, Writing)    == 0x11);
GG_STATIC_ASSERT(offsetof(CStreamClass, Remaining)  == 0x14);
GG_STATIC_ASSERT(offsetof(CStreamClass, OutBuffer)  == 0x18);
GG_STATIC_ASSERT(offsetof(CStreamClass, InBuffer)   == 0x1C);
GG_STATIC_ASSERT(offsetof(CStreamClass, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(CStreamClass, Header)     == 0x24);
GG_STATIC_ASSERT(sizeof(CStreamClass)               == 0x2C);

#endif  // GG_MATCH_LAYOUT_CSTREAM_CLASS_H
