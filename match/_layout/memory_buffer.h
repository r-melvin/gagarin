// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail 0x43AD00 writes the buffer pointer at +0, size at +4, and the
//   allocation flag at +8; each touched offset and the 0x0C-byte size are
//   pinned by static assertions below. CCFileClass::Close at 0x473CE0
//   constructs it at +0x58 before Position at +0x64, confirming this storage
//   boundary. MemoryBuffer and bool retain project naming/type choices; the
//   binary establishes an ownership byte, not its original C++ spelling.
#ifndef GG_MATCH_LAYOUT_MEMORY_BUFFER_H
#define GG_MATCH_LAYOUT_MEMORY_BUFFER_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class MemoryBuffer
{
public:
    // FUNCTION: GAMEMD 0x43AD00
    MemoryBuffer(void* pBuffer, int size) throw();
    // FUNCTION: GAMEMD 0x43ADC0
    MemoryBuffer(int size) throw();
    // FUNCTION: GAMEMD 0x43AE10 -- releases owned storage, then borrows the source.
    MemoryBuffer& operator=(const MemoryBuffer& other);
    // FUNCTION: GAMEMD 0x43AE50 -- explicit cleanup; destructor identity unproven.
    void Clear() throw();

    void* Buffer;        // +0x00
    int   Size;          // +0x04
    bool  Allocated;     // +0x08
private:
    char  unknown_09[3];  // +0x09
};
GG_STATIC_ASSERT(offsetof(MemoryBuffer, Buffer)    == 0x00);
GG_STATIC_ASSERT(offsetof(MemoryBuffer, Size)      == 0x04);
GG_STATIC_ASSERT(offsetof(MemoryBuffer, Allocated) == 0x08);
GG_STATIC_ASSERT(sizeof(MemoryBuffer)               == 0x0C);

#endif
