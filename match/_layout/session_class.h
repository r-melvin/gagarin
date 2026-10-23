// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Shared Session receiver extracted from its existing Resume declaration.
// GameMode0: 0x69BAB0; word table307A: 0x69BBF0/0x69BC20;
// InGameFrameActive30D8: 0x69BAB0. Untouched ranges remain opaque.
#ifndef GG_MATCH_LAYOUT_SESSION_CLASS_H
#define GG_MATCH_LAYOUT_SESSION_CLASS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/vector_class.h"
#include "ipx_address_class.h"

class MultiplayerGameMode;
struct NetPlayerClass;
class CCINIClass;

// Embedded records: native69844B/698464/69847D; stride0x7C.
// No original type name is attested; numeric placeholder retained.
struct SessionProfile_00697F10
{
    int unknown_00, unknown_04, unknown_08, unknown_0C, unknown_10;
    bool unknown_14, unknown_15, unknown_16, unknown_17, unknown_18;
    char unknown_19[3];
    int unknown_1C[8][3]; // nativeusesindices1..7; slot0 remains unobserved
    // Declaration: GAMEMD 0x697F10 -- ECX receiver, fourargs, RET10hex.
    void FUN_00697F10(CCINIClass* ini, const char* section, int fallback, int firstFallback);
};


struct SessionClass
{
    int  GameMode;              // +0x0000
    MultiplayerGameMode* unknown_04; // 0x69B910, virtual slots27/28
    char unknown_08[0x64 - 8];
    int unknown_64[8]; // globalA8B29C, 0x69B9D6..0x69BAA0
    int unknown_84[8]; // 0x69BA5E..0x69BA74, eight DWORDs
    char unknown_A4[0x144 - 0xA4];
    unsigned long unknown_144; // native 0x697B41 stores the mixed DWORD
    char unknown_148[0x15C - 0x148];
    int unknown_15C; // globalA8B394, 0x69B98E
    int unknown_160;
    char unknown_164[0x174 - 0x164];
    int unknown_174;
    int unknown_178;
    int unknown_17C;
    int unknown_180;
    int unknown_184;
    int unknown_188;
    SessionProfile_00697F10 unknown_18C;
    SessionProfile_00697F10 unknown_208;
    SessionProfile_00697F10 unknown_284;
    char unknown_300[0x283C - 0x300];
    // GlobalA8DA74 = SessionA8B238 +283C; native69B60C/69B618.
    DynamicVectorClass<NetPlayerClass*> unknown_283C;
    char unknown_2854[4];
    NetPlayerClass* unknown_2858[8]; // native69C290/69C362
    char unknown_2878[0x2968 - 0x2878];
    unsigned char unknown_2968; // native697DD2 byte store
    char unknown_2969[0x2994 - 0x2969];
    IPXAddressClass unknown_2994[8]; // native69C362/69C40A: stride0xC
    char unknown_29F4[0x2E28 - 0x29F4];
    char unknown_2E28[8][0x24]; // zero288bytes69BDBA; string record stride0x24
    char unknown_2F48[0x2FF8 - 0x2F48];
    int unknown_2FF8[8]; // native69C095, scale4
    unsigned char unknown_3018;
    char unknown_3019[3];
    int unknown_301C;
    // UTF16 storage region before3074; logical string capacity unconfirmed.
    wchar_t unknown_3020[0x54 / 2]; // 0x697EAB passes its address to_wcsicmp
    int unknown_3074; // 0x697E8E, -1 sentinel
    char unknown_3078[2];
    unsigned short unknown_307A[8]; // 0x69BBF0: LEA [ECX+EDX*2+0x307A], limit7
    char unknown_308A[2];
    int unknown_308C; // native697DD9
    unsigned char unknown_3090; // native697D84
    char unknown_3091[3];
    int unknown_3094; // native697DE9
    char unknown_3098[4];
    int unknown_309C; // native697DDF
    char unknown_30A0[0x30D8 - 0x30A0];
    char InGameFrameActive;     // +0x30D8

    // Declaration: GAMEMD 0x69BAB0 (decl; reloc)
    void Resume();
    // Declaration: GAMEMD 0x697AD0 -- ECX Session, no stack arguments.
    void FUN_00697AD0();
    // Declaration: GAMEMD 0x699980 -- Session receiver at 0x697AD7.
    void FUN_00699980();
    // Declaration: GAMEMD 0x697B70 -- EAX result, ECX receiver, RET.
    int FUN_00697B70();
    // Declaration: GAMEMD 0x69B600 -- boolAL, one int argument, RET4.
    bool FUN_0069B600(int value);
    // Declaration: GAMEMD 0x69B670 -- EAX result, no stack arguments.
    int FUN_0069B670();
    int FUN_0069B690();
    // Declaration: GAMEMD 0x69B760 -- ECX Session, value and bool stackargs, RET8.
    void FUN_0069B760(int value, bool randomize);
    // Declaration: GAMEMD 0x69B7E0 -- ECX Session, two stackargs, RET8.
    void FUN_0069B7E0(int value, bool randomize);
    void FUN_0069B8C0();
    void FUN_0069B170(); // FUNCTION: GAMEMD 0x69B170 (decl; 0x684B53)
    void FUN_0069BBF0(int index);
    unsigned short FUN_0069BC20(int id);
    // Declaration: GAMEMD 0x697E70 (decl; reloc) -- AL result, stack pointer, RET4.
    bool FUN_00697E70(void* house);
    // Declaration: GAMEMD 0x69AE70 -- receiver-relative string at +0x6A8.
    bool FUN_0069AE70();
    // Declaration: GAMEMD 0x69AE90 (decl; reloc) -- progress argument, RET4.
    void FUN_0069AE90(int delay);
    // Declaration: GAMEMD 0x69BC60 (decl; reloc) -- slot index argument, EAX result, RET4.
    int FUN_0069BC60(int index);
    // Declaration: GAMEMD 0x69BD60 -- ECX receiver, noargs, RET.
    void FUN_0069BD60();
};
GG_STATIC_ASSERT(offsetof(SessionClass, GameMode) == 0);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_307A) == 0x307A);
GG_STATIC_ASSERT(sizeof(((SessionClass*)0)->unknown_307A) == 0x10);
GG_STATIC_ASSERT(offsetof(SessionClass, InGameFrameActive) == 0x30D8);

// GLOBAL: GAMEMD 0xA8B238
extern SessionClass Session_00A8B238;


GG_STATIC_ASSERT(offsetof(SessionClass, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_64) == 0x64);
GG_STATIC_ASSERT(sizeof(((SessionClass*)0)->unknown_64) == 0x20);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_84) == 0x84);
GG_STATIC_ASSERT(sizeof(((SessionClass*)0)->unknown_84) == 0x20);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_15C) == 0x15C);

GG_STATIC_ASSERT(offsetof(SessionClass, unknown_283C) == 0x283C);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<NetPlayerClass*>) == 0x18);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_283C)
    + offsetof(DynamicVectorClass<NetPlayerClass*>, Items) == 0x2840);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_283C)
    + offsetof(DynamicVectorClass<NetPlayerClass*>, Count) == 0x284C);
GG_STATIC_ASSERT(sizeof(wchar_t) == 2);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_3020) == 0x3020);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_3074) == 0x3074);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_2968) == 0x2968);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_308C) == 0x308C);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_3090) == 0x3090);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_3094) == 0x3094);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_309C) == 0x309C);
GG_STATIC_ASSERT(offsetof(SessionProfile_00697F10, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(SessionProfile_00697F10, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(SessionProfile_00697F10, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(SessionProfile_00697F10, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(SessionProfile_00697F10, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(SessionProfile_00697F10, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(SessionProfile_00697F10, unknown_15) == 0x15);
GG_STATIC_ASSERT(offsetof(SessionProfile_00697F10, unknown_16) == 0x16);
GG_STATIC_ASSERT(offsetof(SessionProfile_00697F10, unknown_17) == 0x17);
GG_STATIC_ASSERT(offsetof(SessionProfile_00697F10, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(SessionProfile_00697F10, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(sizeof(SessionProfile_00697F10) == 0x7C);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_18C) == 0x18C);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_208) == 0x208);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_284) == 0x284);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_174) == 0x174);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_178) == 0x178);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_184) == 0x184);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_188) == 0x188);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_160) == 0x160);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_17C) == 0x17C);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_180) == 0x180);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_2858) == 0x2858);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_2994) == 0x2994);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_2E28) == 0x2E28);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_2FF8) == 0x2FF8);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_3018) == 0x3018);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_301C) == 0x301C);
GG_STATIC_ASSERT(sizeof(((SessionClass*)0)->unknown_2E28) == 0x120);
// 0x69AE70 adds 0x6A8 to its receiver; string capacity remains unknown.
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_300) == 0x300);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_300) + 0x3A8 == 0x6A8);

GG_STATIC_ASSERT(offsetof(SessionClass, unknown_144) == 0x144);
GG_STATIC_ASSERT(sizeof(((SessionClass*)0)->unknown_144) == 4);

#endif // GG_MATCH_LAYOUT_SESSION_CLASS_H
