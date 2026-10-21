// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Shared prefix of the project's IStream COM binding. Retail 0x55AA60 and
// 0x4728E0 call Write through vtable +0x10 with stack this and three arguments.
// This describes the interface prefix, not a concrete stream object's size.
#ifndef GG_RT_ISTREAM_H
#define GG_RT_ISTREAM_H
#include <stddef.h>
#include "gg_static_assert.h"
struct Gg_REFIID;

struct Gg_IStream
{
    // vptr implicit at +0x00.
    virtual long __stdcall QueryInterface(Gg_REFIID* iid, void** ppv) = 0;       // 0x00
    virtual unsigned long   __stdcall AddRef() = 0;                                         // 0x04
    virtual unsigned long   __stdcall Release() = 0;                                        // 0x08
    virtual long __stdcall Read(void* pv, unsigned long cb, unsigned long* pcbRead) = 0;         // 0x0C
    virtual long __stdcall Write(const void* pv, unsigned long cb, unsigned long* pcbWrite) = 0; // 0x10
};

// Layout model for the observed indirect call; targets depend on the stream.
typedef long (__stdcall *Gg_IStreamWriteCall)(Gg_IStream*, const void*,
                                           unsigned long, unsigned long*);
struct Gg_IStreamSlotPrefix
{
    void* unknown_00[4];
    Gg_IStreamWriteCall Write;
};
GG_STATIC_ASSERT(sizeof(Gg_IStreamWriteCall) == 4);
GG_STATIC_ASSERT(offsetof(Gg_IStreamSlotPrefix, Write) == 0x10);
#endif
