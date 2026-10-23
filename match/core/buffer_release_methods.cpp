// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// The buffer-release template, ordered ascending by retail address.

#include "buffer_release_methods.h"

// FUNCTION: GAMEMD 0x40BE50
void FUN_0040BE50(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    obj->unknown_10 = 0;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x40BFA0
void FUN_0040BFA0(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x40C820
void FUN_0040C820(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    obj->unknown_10 = 0;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x40C970
void FUN_0040C970(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x40CC70
void FUN_0040CC70(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    obj->unknown_10 = 0;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x40CDC0
void FUN_0040CDC0(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x40D540
void FUN_0040D540(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    obj->unknown_10 = 0;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x40D690
void FUN_0040D690(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x40E7F0
void FUN_0040E7F0(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    obj->unknown_10 = 0;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x40E940
void FUN_0040E940(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x40EEC0
void FUN_0040EEC0(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    obj->unknown_10 = 0;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x40F010
void FUN_0040F010(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x40FBB0
void FUN_0040FBB0(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    obj->unknown_10 = 0;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x40FD00
void FUN_0040FD00(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x42D540
void FUN_0042D540(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    obj->unknown_10 = 0;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x42D5A0
void FUN_0042D5A0(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    obj->unknown_10 = 0;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x42D6F0
void FUN_0042D6F0(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x42D9A0
void FUN_0042D9A0(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x42F3A0
void FUN_0042F3A0(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    obj->unknown_10 = 0;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x42F420
void FUN_0042F420(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    obj->unknown_10 = 0;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x42F7C0
void FUN_0042F7C0(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x42FAB0
void FUN_0042FAB0(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// FUNCTION: GAMEMD 0x43AC20
void FUN_0043AC20(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

