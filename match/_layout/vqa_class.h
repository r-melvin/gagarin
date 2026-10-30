// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | structural-reference-only
//   VQAClass, the Westwood VQA playback object (C++ part of the playback library 5.0), and its embedded
//   configuration block, read off the user's retail gamemd.exe v1.001 (constructor 0x759260 and the
//   members at 0x759510..0x75A350). The class is named by the retail string "VQAClass::Advance_Frame()";
//   field names are placeholders except where the binary names the role.
#ifndef GG_LAYOUT_VQA_CLASS_H
#define GG_LAYOUT_VQA_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/movie_stream_handle.h"
#include "../platform/ccfile_class.h"

struct StreamSampleView;
struct VQAOwner_006C9C60;
class VQAClass;

typedef int (__cdecl *VQAIoFn)(MovieHandle_007BD470* h, int op, unsigned int* buf, int size);
typedef void* (__cdecl *VQAAllocFn)(int unused, int op, unsigned int* p, size_t n);
typedef int (__cdecl *VQAPaletteFn)(MovieHandle_007BD470* h, int op, unsigned short* buf, unsigned int size);
typedef unsigned (__cdecl *VQAAudioFn)(StreamSampleView* sample);
typedef int (__cdecl *VQATimerFn)(int a, int b);

// The configuration block the object hands the playback engine; reset from the default block at
// 0x84E738 by 0x7BE640. Object offset 0x178.
struct VQAConfigBlock
{
    VQAIoFn Io; // 0x0
    VQAAllocFn Alloc; // 0x4
    VQAPaletteFn Palette; // 0x8
    int unknown_0C; // 0xc
    VQAAudioFn Audio; // 0x10
    int unknown_14; // 0x14
    VQATimerFn Timer; // 0x18
    char* unknown_1C; // 0x1c
    int unknown_20; // 0x20
    int unknown_24; // 0x24
    int unknown_28; // 0x28
    int unknown_2C; // 0x2c
    int unknown_30; // 0x30
    int unknown_34; // 0x34
    int unknown_38; // 0x38
    int unknown_3C; // 0x3c
    unsigned int Flags40; // 0x40
    unsigned int Flags44; // 0x44
    int unknown_48; // 0x48
    int unknown_4C; // 0x4c
    int unknown_50; // 0x50
    int unknown_54; // 0x54
    int unknown_58; // 0x58
    int unknown_5C; // 0x5c
    int unknown_60; // 0x60
    int unknown_64; // 0x64
    int unknown_68; // 0x68
    VQAClass* Self; // 0x6c
    int unknown_70; // 0x70
    int unknown_74; // 0x74
    int unknown_78; // 0x78
    int unknown_7C; // 0x7c
    int unknown_80; // 0x80
    int unknown_84; // 0x84
    void FUN_007BE640();
};
GG_STATIC_ASSERT(sizeof(VQAConfigBlock) == 0x88);
GG_STATIC_ASSERT(offsetof(VQAConfigBlock, Audio) == 0x10);
GG_STATIC_ASSERT(offsetof(VQAConfigBlock, Timer) == 0x18);
GG_STATIC_ASSERT(offsetof(VQAConfigBlock, unknown_1C) == 0x1c);
GG_STATIC_ASSERT(offsetof(VQAConfigBlock, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(VQAConfigBlock, Flags40) == 0x40);
GG_STATIC_ASSERT(offsetof(VQAConfigBlock, Flags44) == 0x44);
GG_STATIC_ASSERT(offsetof(VQAConfigBlock, unknown_5C) == 0x5c);
GG_STATIC_ASSERT(offsetof(VQAConfigBlock, Self) == 0x6c);
GG_STATIC_ASSERT(offsetof(VQAConfigBlock, unknown_84) == 0x84);

class VQAClass
{
public:
    VQAClass(const char* name, unsigned int mode, int (__cdecl *h540)(), void (__cdecl *h544)(),
             void (__cdecl *cb548)(), int a6, int a7);
    ~VQAClass();
    int FUN_00759540(unsigned int count);
    bool FUN_00759940(int frame, bool flag);
    bool Advance_Frame(bool* failed);
    int FUN_00759FB0(int op, unsigned int* buf, int size);
    int FUN_0075A120(int op, unsigned int* buf, int size);

    VQAOwner_006C9C60* Owner; // 0x0
    CCFileClass File; // 0x4
    bool FileOpen; // 0x70
    char Name[0x107]; // 0x71
    VQAConfigBlock Config; // 0x178
    MovieHandle_007BD470* Handle; // 0x200
    unsigned char Palette[0x300]; // 0x204
    int Position; // 0x504
    int FrameCount; // 0x508
    int unknown_50C; // 0x50c
    int unknown_510; // 0x510
    bool Active; // 0x514
    int unknown_518; // 0x518
    int unknown_51C; // 0x51c
    int unknown_520; // 0x520
    int unknown_524; // 0x524
    bool PaletteDirty; // 0x528
    unsigned int Mode; // 0x52c
    unsigned int DataSize; // 0x530
    unsigned int DataLoaded; // 0x534
    unsigned int DataCursor; // 0x538
    unsigned char* Data; // 0x53c
    int (__cdecl *Handler540)(); // 0x540
    void (__cdecl *Handler544)(); // 0x544
    void (__cdecl *Callback548)(); // 0x548
    int Pending; // 0x54c
    bool Sleeping; // 0x550
    bool PauseLogged; // 0x551
};
GG_STATIC_ASSERT(offsetof(VQAClass, File) == 0x4);
GG_STATIC_ASSERT(offsetof(VQAClass, FileOpen) == 0x70);
GG_STATIC_ASSERT(offsetof(VQAClass, Name) == 0x71);
GG_STATIC_ASSERT(offsetof(VQAClass, Config) == 0x178);
GG_STATIC_ASSERT(offsetof(VQAClass, Handle) == 0x200);
GG_STATIC_ASSERT(offsetof(VQAClass, Palette) == 0x204);
GG_STATIC_ASSERT(offsetof(VQAClass, Position) == 0x504);
GG_STATIC_ASSERT(offsetof(VQAClass, FrameCount) == 0x508);
GG_STATIC_ASSERT(offsetof(VQAClass, unknown_510) == 0x510);
GG_STATIC_ASSERT(offsetof(VQAClass, Active) == 0x514);
GG_STATIC_ASSERT(offsetof(VQAClass, unknown_524) == 0x524);
GG_STATIC_ASSERT(offsetof(VQAClass, PaletteDirty) == 0x528);
GG_STATIC_ASSERT(offsetof(VQAClass, Mode) == 0x52c);
GG_STATIC_ASSERT(offsetof(VQAClass, DataSize) == 0x530);
GG_STATIC_ASSERT(offsetof(VQAClass, DataLoaded) == 0x534);
GG_STATIC_ASSERT(offsetof(VQAClass, DataCursor) == 0x538);
GG_STATIC_ASSERT(offsetof(VQAClass, Data) == 0x53c);
GG_STATIC_ASSERT(offsetof(VQAClass, Handler540) == 0x540);
GG_STATIC_ASSERT(offsetof(VQAClass, Handler544) == 0x544);
GG_STATIC_ASSERT(offsetof(VQAClass, Callback548) == 0x548);
GG_STATIC_ASSERT(offsetof(VQAClass, Pending) == 0x54c);
GG_STATIC_ASSERT(offsetof(VQAClass, Sleeping) == 0x550);
GG_STATIC_ASSERT(offsetof(VQAClass, PauseLogged) == 0x551);

#endif
