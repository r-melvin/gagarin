// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x431B80: [ESI+0x24], [ESI+0x25], [ESI+0x27],
//   [ESI+0x28], [ESI+0x29], [ESI+0x30], [ESI+0x34]. Class name from YRpp
//  ; the sibling methods Close/SetFileName/Open
//   are already committed in match/platform/ccfile_class_ops_methods.cpp.
//
// BufferIOFileClass::~BufferIOFileClass @0x431B80 — release the IO buffer and
// reset the buffering state.
#ifndef GG_MATCH_PLATFORM_BUFFER_IO_FILE_CLASS_DTOR_METHODS_H
#define GG_MATCH_PLATFORM_BUFFER_IO_FILE_CLASS_DTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The deallocator retail hands the buffer to: __cdecl, one pointer argument,
// `ADD ESP,4` after the call. Declared without a body.
extern "C" void __cdecl FUN_007C8B3D(void* block);

// The base-class destructor at 0x65CA00, reached as `MOV ECX,ESI; CALL`. It is
// invoked through an explicit cast rather than by modelling the inheritance:
// the base layout is not needed here, only the call, and a real base would drag
// in its vtable arrangement for no gain. Called last, where retail has it.
struct RawFileClassBase
{
    void FUN_0065CA00();   // GAMEMD 0x65CA00
};

// ---------------------------------------------------------------------------
// BufferIOFileClass — only the fields this destructor touches are modelled.
// The vtable store at 0x431B89 (`MOV [ESI],0x7E3A2C`) is what makes the class
// virtual here.
// ---------------------------------------------------------------------------
// VTABLE: GAMEMD 0x7E3A2C  BufferIOFileClass
class BufferIOFileClass
{
public:
    virtual ~BufferIOFileClass();

    // FUNCTION: GAMEMD 0x431D90 — the same reset without the vtable install or
    // the base-destructor call: a close rather than a destruction.
    void FUN_00431D90();

    char           _pad04[0x24 - 0x04];   // +0x0004  (RawFileClass spine, P2)
    unsigned char  IsAllocated;           // +0x0024
    unsigned char  unknown_25;                // +0x0025
    unsigned char  _unknown_26;           // +0x0026  (not touched here)
    unsigned char  unknown_27;            // +0x0027
    unsigned char  unknown_28;              // +0x0028
    unsigned char  unknown_29;             // +0x0029
    char           _pad2A[0x30 - 0x2A];   // +0x002A
    void*          Buffer;                // +0x0030
    int            BufferSize;            // +0x0034
};
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, IsAllocated) == 0x24);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_25) == 0x25);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_27) == 0x27);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_29) == 0x29);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, Buffer) == 0x30);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, BufferSize) == 0x34);

#endif  // GG_MATCH_PLATFORM_BUFFER_IO_FILE_CLASS_DTOR_METHODS_H
