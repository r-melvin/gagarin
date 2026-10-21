// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail 0x43AD00 field stores and allocation branch were confirmed from
//   entry-origin instructions; 0x7C8E17 is the called library allocator.

#include "../_layout/memory_buffer.h"

extern "C" void* __cdecl FUN_007C8E17(unsigned int size); // LIBRARY: GAMEMD 0x7C8E17

// FUNCTION: GAMEMD 0x43AD00
MemoryBuffer::MemoryBuffer(void* pBuffer, int size) throw()
{
    Buffer = pBuffer;
    Size = size;
    Allocated = 0;
    if (pBuffer == 0 && size > 0) {
        Buffer = FUN_007C8E17(size);
        Allocated = 1;
    }
}

extern "C" void __cdecl FUN_007C8B3D(void* block); // LIBRARY: GAMEMD 0x7C8B3D

// FUNCTION: GAMEMD 0x43ADC0
MemoryBuffer::MemoryBuffer(int size) throw()
{
    Buffer = 0;
    Size = size;
    Allocated = 0;
    if (size > 0) {
        Buffer = FUN_007C8E17(size);
        Allocated = 1;
    }
}

// FUNCTION: GAMEMD 0x43AE50
void MemoryBuffer::Clear() throw()
{
    if (Allocated) {
        FUN_007C8B3D(Buffer);
    }
    Buffer = 0;
    Size = 0;
    Allocated = 0;
}
