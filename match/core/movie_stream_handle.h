// Provenance: own-binary-via-Ghidra
// Movie-stream player handle shared by the decoder/loader/task routines at
// 0x7BD470..0x7C4260. Layout is recovered from the field accesses in those
// bodies; unnamed spans are unknown_XX gaps.
#ifndef GG_MOVIE_STREAM_HANDLE_H
#define GG_MOVIE_STREAM_HANDLE_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct MovieHandle_007BD470;

// Frame ring node: retail walks it through +0x0C and flags it at +0x14.
struct MovieLoadBuffer_007BD470;

// Decoded frame ring node; 0x7BD690 clears eleven dwords before the
// block table area that follows it.
struct MovieFrame_007BD470
{
    unsigned char* unknown_0; // 0x0
    MovieLoadBuffer_007BD470* unknown_4; // 0x4
    unsigned char* unknown_8; // 0x8
    MovieFrame_007BD470* unknown_C; // 0xc
    MovieFrame_007BD470* unknown_10; // 0x10
    int unknown_14; // 0x14
    int unknown_18; // 0x18
    int unknown_1C; // 0x1c
    unsigned char unknown_20[0x4];
    int unknown_24; // 0x24
    int unknown_28; // 0x28
};
GG_STATIC_ASSERT(offsetof(MovieFrame_007BD470, unknown_4) == 0x4);
GG_STATIC_ASSERT(offsetof(MovieFrame_007BD470, unknown_8) == 0x8);
GG_STATIC_ASSERT(offsetof(MovieFrame_007BD470, unknown_C) == 0xc);
GG_STATIC_ASSERT(offsetof(MovieFrame_007BD470, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(MovieFrame_007BD470, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(MovieFrame_007BD470, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(MovieFrame_007BD470, unknown_1C) == 0x1c);
GG_STATIC_ASSERT(offsetof(MovieFrame_007BD470, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(MovieFrame_007BD470, unknown_28) == 0x28);

// Loader buffer ring node; its data area follows the 0x18-byte node
// (0x7BD690 clears six dwords and points Data just past them).
struct MovieLoadBuffer_007BD470
{
    unsigned char* unknown_0; // 0x0
    MovieLoadBuffer_007BD470* unknown_4; // 0x4
    MovieLoadBuffer_007BD470* unknown_8; // 0x8
    unsigned char unknown_C[0xc];
};
GG_STATIC_ASSERT(offsetof(MovieLoadBuffer_007BD470, unknown_4) == 0x4);
GG_STATIC_ASSERT(offsetof(MovieLoadBuffer_007BD470, unknown_8) == 0x8);

typedef int (__cdecl *MovieIoFn_007BD470)(MovieHandle_007BD470* h, int op, void* buf, int size);
typedef void* (__cdecl *MovieMemFn_007BD470)(MovieHandle_007BD470* h, int op, void* p, int size);
typedef int (__cdecl *MoviePaletteFn_007BD470)(MovieHandle_007BD470* h, int op, int frame, int arg);
typedef int (__cdecl *MovieFrameFn_007BD470)(int op, int frame);
typedef int (__cdecl *MovieAudioFn_007BD470)(MovieHandle_007BD470* h, int op, void* buf, int size);

typedef int (*MovieStepFn_007BD470)(MovieHandle_007BD470* h);
typedef int (__cdecl *MovieTimerFn_007BD470)(MovieHandle_007BD470* h);
typedef void (__cdecl *MovieDrawFn_007BD470)(unsigned short* blockTable, unsigned short* pointers,
                                    unsigned short* dest, int blocksWide, int blocksHigh, int pitch);

#pragma pack(push, 1)
// Stream header as stored in the file (byte packed: unknown_26 sits at +0x26).
struct MovieHeader_007BD470
{
    unsigned short unknown_0; // 0x0
    unsigned short unknown_2; // 0x2
    unsigned short unknown_4; // 0x4
    unsigned short unknown_6; // 0x6
    unsigned short unknown_8; // 0x8
    unsigned char unknown_A; // 0xa
    unsigned char unknown_B; // 0xb
    unsigned char unknown_C; // 0xc
    unsigned char unknown_D; // 0xd
    unsigned char unknown_E[0x2];
    unsigned short unknown_10; // 0x10
    unsigned short unknown_12; // 0x12
    unsigned short unknown_14; // 0x14
    unsigned short unknown_16; // 0x16
    unsigned short unknown_18; // 0x18
    unsigned char unknown_1A; // 0x1a
    unsigned char unknown_1B; // 0x1b
    unsigned short unknown_1C; // 0x1c
    unsigned char unknown_1E; // 0x1e
    unsigned char unknown_1F; // 0x1f
    unsigned char unknown_20; // 0x20
    unsigned char unknown_21[0x1];
    unsigned int unknown_22; // 0x22
    int unknown_26; // 0x26
};
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_0) == 0x0);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_2) == 0x2);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_4) == 0x4);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_6) == 0x6);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_8) == 0x8);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_A) == 0xa);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_B) == 0xb);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_C) == 0xc);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_D) == 0xd);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_12) == 0x12);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_16) == 0x16);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_1A) == 0x1a);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_1B) == 0x1b);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_1C) == 0x1c);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_1E) == 0x1e);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_1F) == 0x1f);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_22) == 0x22);
GG_STATIC_ASSERT(offsetof(MovieHeader_007BD470, unknown_26) == 0x26);
#pragma pack(pop)

struct MovieConfig_007BD470
{
    MovieIoFn_007BD470 unknown_0; // 0x0
    MovieMemFn_007BD470 unknown_4; // 0x4
    MoviePaletteFn_007BD470 unknown_8; // 0x8
    MovieFrameFn_007BD470 unknown_C; // 0xc
    int unknown_10; // 0x10
    MovieTimerFn_007BD470 unknown_14; // 0x14
    MovieAudioFn_007BD470 unknown_18; // 0x18
    unsigned char* unknown_1C; // 0x1c
    int unknown_20; // 0x20
    int unknown_24; // 0x24
    int unknown_28; // 0x28
    int unknown_2C; // 0x2c
    int unknown_30; // 0x30
    int unknown_34; // 0x34
    int unknown_38; // 0x38
    unsigned char unknown_3C[0x4];
    int unknown_40; // 0x40
    int unknown_44; // 0x44
    int unknown_48; // 0x48
    int unknown_4C; // 0x4c
    unsigned char unknown_50[0x4];
    unsigned char* unknown_54; // 0x54
    int unknown_58; // 0x58
    int unknown_5C; // 0x5c
    unsigned char unknown_60[0x10];
    int unknown_70; // 0x70
    int unknown_74; // 0x74
    int unknown_78; // 0x78
    unsigned char unknown_7C[0xc];
};
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_0) == 0x0);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_4) == 0x4);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_8) == 0x8);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_C) == 0xc);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_1C) == 0x1c);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_2C) == 0x2c);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_4C) == 0x4c);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_54) == 0x54);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_58) == 0x58);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_5C) == 0x5c);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_70) == 0x70);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_74) == 0x74);
GG_STATIC_ASSERT(offsetof(MovieConfig_007BD470, unknown_78) == 0x78);

struct MovieDrawState_007BD470
{
    MovieFrame_007BD470* unknown_0; // 0x0
    int unknown_4; // 0x4
    unsigned char* unknown_8; // 0x8
    int unknown_C; // 0xc
    int unknown_10; // 0x10
    int unknown_14; // 0x14
    int unknown_18; // 0x18
    int unknown_1C; // 0x1c
    int unknown_20; // 0x20
    unsigned char unknown_24[0x300]; // 0x24
    unsigned char unknown_324[0x200];
    int unknown_524; // 0x524
    int unknown_528; // 0x528
    int unknown_52C; // 0x52c
    int unknown_530; // 0x530
    unsigned char unknown_534[0x4];
    int unknown_538; // 0x538
};
GG_STATIC_ASSERT(offsetof(MovieDrawState_007BD470, unknown_0) == 0x0);
GG_STATIC_ASSERT(offsetof(MovieDrawState_007BD470, unknown_4) == 0x4);
GG_STATIC_ASSERT(offsetof(MovieDrawState_007BD470, unknown_8) == 0x8);
GG_STATIC_ASSERT(offsetof(MovieDrawState_007BD470, unknown_C) == 0xc);
GG_STATIC_ASSERT(offsetof(MovieDrawState_007BD470, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(MovieDrawState_007BD470, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(MovieDrawState_007BD470, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(MovieDrawState_007BD470, unknown_1C) == 0x1c);
GG_STATIC_ASSERT(offsetof(MovieDrawState_007BD470, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(MovieDrawState_007BD470, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(MovieDrawState_007BD470, unknown_524) == 0x524);
GG_STATIC_ASSERT(offsetof(MovieDrawState_007BD470, unknown_528) == 0x528);
GG_STATIC_ASSERT(offsetof(MovieDrawState_007BD470, unknown_52C) == 0x52c);
GG_STATIC_ASSERT(offsetof(MovieDrawState_007BD470, unknown_530) == 0x530);
GG_STATIC_ASSERT(offsetof(MovieDrawState_007BD470, unknown_538) == 0x538);

struct MovieHandle_007BD470
{
    unsigned short unknown_0; // 0x0
    unsigned short unknown_2; // 0x2
    unsigned short unknown_4; // 0x4
    unsigned char unknown_6[0x2];
    unsigned char* unknown_8; // 0x8
    short unknown_C; // 0xc
    short unknown_E; // 0xe
    int unknown_10; // 0x10
    int unknown_14; // 0x14
    int unknown_18; // 0x18
    int unknown_1C; // 0x1c
    int unknown_20; // 0x20
    int unknown_24; // 0x24
    int unknown_28; // 0x28
    int unknown_2C; // 0x2c
    int unknown_30; // 0x30
    unsigned char unknown_34[0x4];
    int unknown_38; // 0x38
    unsigned short unknown_3C; // 0x3c
    unsigned char unknown_3E; // 0x3e
    unsigned char unknown_3F; // 0x3f
    MovieConfig_007BD470 unknown_40; // 0x40
    char unknown_C8[0x20]; // 0xc8
    MovieHeader_007BD470 unknown_E8; // 0xe8
    unsigned char unknown_112[0xa];
    int unknown_11C; // 0x11c
    int unknown_120; // 0x120
    unsigned char unknown_124[0x4];
    int unknown_128; // 0x128
    int unknown_12C; // 0x12c
    unsigned char unknown_130[0x8];
    int unknown_138; // 0x138
    int unknown_13C; // 0x13c
    int unknown_140; // 0x140
    int unknown_144; // 0x144
    unsigned char unknown_148[0x8];
    int unknown_150; // 0x150
    int unknown_154; // 0x154
    unsigned char* unknown_158; // 0x158
    int unknown_15C; // 0x15c
    int unknown_160; // 0x160
    MovieLoadBuffer_007BD470* unknown_164; // 0x164
    MovieLoadBuffer_007BD470* unknown_168; // 0x168
    MovieLoadBuffer_007BD470* unknown_16C; // 0x16c
    MovieFrame_007BD470* unknown_170; // 0x170
    int unknown_174; // 0x174
    int unknown_178; // 0x178
    unsigned char unknown_17C[0x4];
    int unknown_180; // 0x180
    int unknown_184; // 0x184
    unsigned char unknown_188[0x18];
    MovieDrawState_007BD470 unknown_1A0; // 0x1a0
    MovieFrame_007BD470* unknown_6DC; // 0x6dc
    unsigned char unknown_6E0[0x4];
    MovieFrame_007BD470* unknown_6E4; // 0x6e4
    unsigned char* unknown_6E8; // 0x6e8
    MovieLoadBuffer_007BD470* unknown_6EC; // 0x6ec
    unsigned char* unknown_6F0; // 0x6f0
    unsigned char* unknown_6F4; // 0x6f4
    int unknown_6F8; // 0x6f8
    int unknown_6FC; // 0x6fc
    int unknown_700; // 0x700
    int unknown_704; // 0x704
    int unknown_708; // 0x708
    int unknown_70C; // 0x70c
    int unknown_710; // 0x710
    unsigned short unknown_714; // 0x714
    unsigned short unknown_716; // 0x716
    unsigned char unknown_718[0x4];
    void* unknown_71C; // 0x71c
    unsigned char unknown_720[0x2c];
    unsigned short unknown_74C; // 0x74c
    unsigned short unknown_74E; // 0x74e
    unsigned char unknown_750[0x4];
    void* unknown_754; // 0x754
    unsigned short unknown_758; // 0x758
    unsigned char unknown_75A[0x6];
    void* unknown_760; // 0x760
    unsigned int* unknown_764; // 0x764
    int unknown_768; // 0x768
    int unknown_76C; // 0x76c
    int unknown_770; // 0x770
    int unknown_774; // 0x774
    int unknown_778; // 0x778
    MovieStepFn_007BD470 unknown_77C; // 0x77c
    MovieStepFn_007BD470 unknown_780; // 0x780
    MovieDrawFn_007BD470 unknown_784; // 0x784
    MovieDrawFn_007BD470 unknown_788; // 0x788
    unsigned char* unknown_78C; // 0x78c
    unsigned int unknown_790; // 0x790
    unsigned char* unknown_794; // 0x794
    unsigned short* unknown_798; // 0x798
    unsigned int unknown_79C; // 0x79c
    int unknown_7A0; // 0x7a0
    int unknown_7A4; // 0x7a4
    unsigned char* unknown_7A8; // 0x7a8
    int unknown_7AC; // 0x7ac
    int unknown_7B0; // 0x7b0
    unsigned int unknown_7B4; // 0x7b4
    unsigned char* unknown_7B8; // 0x7b8
    int unknown_7BC; // 0x7bc
    int unknown_7C0; // 0x7c0
    int unknown_7C4; // 0x7c4
    unsigned char unknown_7C8[0x4];
    unsigned int unknown_7CC; // 0x7cc
    int unknown_7D0[3]; // 0x7d0
};
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_0) == 0x0);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_2) == 0x2);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_4) == 0x4);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_8) == 0x8);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_C) == 0xc);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_E) == 0xe);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_1C) == 0x1c);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_2C) == 0x2c);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_3C) == 0x3c);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_3E) == 0x3e);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_3F) == 0x3f);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_C8) == 0xc8);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_E8) == 0xe8);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_11C) == 0x11c);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_120) == 0x120);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_128) == 0x128);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_12C) == 0x12c);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_138) == 0x138);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_13C) == 0x13c);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_140) == 0x140);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_144) == 0x144);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_150) == 0x150);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_154) == 0x154);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_158) == 0x158);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_15C) == 0x15c);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_160) == 0x160);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_164) == 0x164);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_168) == 0x168);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_16C) == 0x16c);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_170) == 0x170);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_174) == 0x174);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_178) == 0x178);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_180) == 0x180);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_184) == 0x184);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_1A0) == 0x1a0);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_6DC) == 0x6dc);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_6E4) == 0x6e4);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_6E8) == 0x6e8);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_6EC) == 0x6ec);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_6F0) == 0x6f0);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_6F4) == 0x6f4);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_6F8) == 0x6f8);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_6FC) == 0x6fc);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_700) == 0x700);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_704) == 0x704);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_708) == 0x708);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_70C) == 0x70c);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_710) == 0x710);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_714) == 0x714);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_716) == 0x716);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_71C) == 0x71c);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_74C) == 0x74c);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_74E) == 0x74e);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_754) == 0x754);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_758) == 0x758);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_760) == 0x760);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_764) == 0x764);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_768) == 0x768);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_76C) == 0x76c);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_770) == 0x770);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_774) == 0x774);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_778) == 0x778);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_77C) == 0x77c);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_780) == 0x780);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_784) == 0x784);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_788) == 0x788);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_78C) == 0x78c);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_790) == 0x790);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_794) == 0x794);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_798) == 0x798);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_79C) == 0x79c);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_7A0) == 0x7a0);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_7A4) == 0x7a4);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_7A8) == 0x7a8);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_7AC) == 0x7ac);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_7B0) == 0x7b0);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_7B4) == 0x7b4);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_7B8) == 0x7b8);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_7BC) == 0x7bc);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_7C0) == 0x7c0);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_7C4) == 0x7c4);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_7CC) == 0x7cc);
GG_STATIC_ASSERT(offsetof(MovieHandle_007BD470, unknown_7D0) == 0x7d0);
// 0x7C2590 allocates and clears exactly 0x7DC bytes for a handle.
GG_STATIC_ASSERT(sizeof(MovieHandle_007BD470) == 0x7dc);

#endif
