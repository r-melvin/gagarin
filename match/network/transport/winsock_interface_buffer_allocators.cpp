// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RTTI
//   The selected bodies and their referenced field offsets come from the
//   pinned retail gamemd.exe v1.001. The static pool arrays are address-scoped
//   layout fields, each 128 * 0x2A0 bytes; this TU does not claim constructor
//   initialization or ownership beyond the observed allocator accesses.
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
#include <new>
#include "winsock_interface_class.h"

// FUNCTION: GAMEMD 0x7B20E0 -- WinsockInterfaceClass::AllocOutBuffer.
WinsockInterfaceClass::WinsockBufferType* WinsockInterfaceClass::AllocOutBuffer(bool alternate)
{
    WinsockBufferType* buffer = 0;

    if (!alternate)
    {
        if (StaticOutBuffersInUse == 128)
        {
            buffer = (WinsockBufferType*)operator new(sizeof(WinsockBufferType));
            buffer->IsAllocated = 1;
            buffer->InUse = 1;
        }
        else
        {
            for (int i = 0; i < 128; i++)
            {
                int pos = StaticOutBufferPos++;
                if (StaticOutBufferPos > 127)
                    StaticOutBufferPos = 0;
                if (!StaticOutBuffers[pos].InUse)
                {
                    buffer = &StaticOutBuffers[pos];
                    buffer->InUse = 1;
                    StaticOutBuffersInUse++;
                    break;
                }
            }
        }
        if (buffer)
        {
            buffer->IsAlternate = 0;
            buffer->unknown_18 = 0;
        }
    }
    else
    {
        if (StaticAltOutBuffersInUse == 128)
        {
            buffer = (WinsockBufferType*)operator new(sizeof(WinsockBufferType));
            buffer->IsAllocated = 1;
            buffer->InUse = 1;
        }
        else
        {
            for (int i = 0; i < 128; i++)
            {
                int pos = StaticAltOutBufferPos++;
                if (StaticAltOutBufferPos > 127)
                    StaticAltOutBufferPos = 0;
                if (!StaticAltOutBuffers[pos].InUse)
                {
                    buffer = &StaticAltOutBuffers[pos];
                    buffer->InUse = 1;
                    StaticAltOutBuffersInUse++;
                    break;
                }
            }
        }
        if (buffer)
        {
            buffer->IsAlternate = 1;
            buffer->unknown_18 = 0;
        }
    }
    return buffer;
}

// FUNCTION: GAMEMD 0x7B2240 -- WinsockInterfaceClass::AllocInBuffer.
WinsockInterfaceClass::WinsockBufferType* WinsockInterfaceClass::AllocInBuffer()
{
    WinsockBufferType* buffer = 0;

    if (StaticInBuffersInUse == 128)
    {
        buffer = (WinsockBufferType*)operator new(sizeof(WinsockBufferType));
        buffer->IsAllocated = 1;
        buffer->InUse = 1;
    }
    else
    {
        for (int i = 0; i < 128; i++)
        {
            int pos = StaticInBufferPos++;
            if (StaticInBufferPos > 127)
                StaticInBufferPos = 0;
            if (!StaticInBuffers[pos].InUse)
            {
                buffer = &StaticInBuffers[pos];
                buffer->InUse = 1;
                StaticInBuffersInUse++;
                break;
            }
        }
    }
    if (buffer)
    {
        buffer->IsAlternate = 0;
        buffer->unknown_18 = 0;
    }
    return buffer;
}
