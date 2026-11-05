// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit TU053 of retail gamemd.exe v1.001 (code range 0x48a4f0-0x48bb00, between
//   CD.CPP and Connect.CPP); its source-file name is not attested by the binary, so the file keeps a
//   placeholder name. Functions are in ascending retail address order.

#include <string.h>
#include "conn_types.h"
#include "_layout/facing_class.h"
#include "_layout/rules_class.h"
#include "_layout/warhead_type_class.h"
#include "_layout/anim_type_class.h"
#include "_layout/cell_class.h"
#include "_layout/map_0087f7e8.h"
#include "scenario_class.h"
#include "shadow_block_list_methods.h"
#include "fps_counter_methods.h"

// STRING: GAMEMD 0x81D1F0
// STRING: GAMEMD 0x81D214
// STRING: GAMEMD 0x81D238

// GLOBAL: GAMEMD 0x8871E0 -- RulesClass::Instance.
extern RulesClass* Rules;
// GLOBAL: GAMEMD 0xA8B230 -- ScenarioClass::Instance.
extern ScenarioClass* DAT_00A8B230;
// GLOBAL: GAMEMD 0x89E870 -- the height of one map level.
extern int DAT_0089E870;

// FUNCTION: GAMEMD 0x48A4F0
const AnimTypeClass* __fastcall FUN_0048A4F0(int health, WarheadTypeClass* warhead, int selected,
                                       const CoordStruct* where)
{
    if (health == 0 || warhead == 0) {
        return 0;
    }
    if (selected == 2 && warhead->Conventional) {
        if (!(DAT_0087F7E8.FUN_00565730(where)->Flags & 0x100)
            && where->Z < DAT_0087F7E8.FUN_00578080(where) + DAT_0089E870 * 2) {
            int count = Rules->list_0BC0.Count;
            if (count == 0) {
                return 0;
            }
            int top = count * 35 - 1;
            if (health < top) {
                top = health;
            }
            return Rules->list_0BC0.Items[top / 35];
        }
    }
    if (warhead == Rules->LightningWarhead) {
        return Rules->WeatherConBoltExplosion;
    }
    int count = warhead->AnimList.Count;
    if (count == 0) {
        return 0;
    }
    if (warhead->EMEffect) {
        return warhead->AnimList.Items[DAT_00A8B230->unknown_0218.RandomRanged(0, count - 1)];
    }
    if (health >= count * 25 - 1) {
        health = count * 25 - 1;
    }
    return warhead->AnimList.Items[health / 25];
}

// GLOBAL: GAMEMD 0xA8EB78 -- the detail setting (0, 1 or 2).
extern int DAT_00A8EB78;
// GLOBAL: GAMEMD 0xABCD44 -- the current frame rate.
extern unsigned int DAT_00ABCD44;

// FUNCTION: GAMEMD 0x48A620
void __fastcall FUN_0048A620(int health, WarheadTypeClass* warhead, CoordStruct where, char c,
                             unsigned int mask)
{
    if ((DAT_00A8EB78 && DAT_00ABCD44 >= Detail::GetMinFrameRate()) || (mask & 0xF)) {
        if (c || (warhead && warhead->Bright)) {
            float size = warhead->CombatLightSize;
            int intensity;
            if (size > 0.0f) {
                if (size > 1.0f) {
                    size = 1.0f;
                }
                intensity = (int)(size * 63.0f);
            } else {
                intensity = (health << 6) >> 8;
                if (intensity >= 0x3F) {
                    intensity = 0x3F;
                } else if (intensity <= 0x15) {
                    intensity = 0x15;
                }
            }
            SpotLightClass* light = new SpotLightClass(where, intensity);
            light->unknown_14 |= mask;
        }
    }
}

// FUNCTION: GAMEMD 0x48A9D0 (decl; reloc) -- sign flag in CL, a value in EDX, then two ints, a double and
// the result pointer (RET 0x14).
bool __fastcall FUN_0048A9D0(bool flag, int dx, int a, int b, double g, double* out);

// FUNCTION: GAMEMD 0x48AB20
bool __fastcall FUN_0048AB20(int dx, int a, int b, double g, DirStruct* out)
{
    if (FUN_0048A9D0(0, dx, a, b, g, &g)) {
        if (g < 0.0) {
            g += 6.283185307179586;
        }
        g = (g - 1.5707963267948966) * -10430.060040584269;
        DirStruct dir;
        dir.Raw = (unsigned short)(int)g;
        *out = dir;
        return true;
    }
    return false;
}

// VTABLE: GAMEMD 0x7E519C  CommBufferClass (1 slot)

// FUNCTION: GAMEMD 0x48B0E0
CommBufferClass::CommBufferClass(int sendSlots, int receiveSlots, int maxlen, int extraLength)
{
    unknown_04 = sendSlots;
    unknown_08 = receiveSlots;
    unknown_0C = maxlen;
    unknown_10 = extraLength;
    unknown_24 = (CommSendEntry*)new char[sendSlots * sizeof(CommSendEntry)];
    unknown_34 = (CommReceiveEntry*)new char[receiveSlots * sizeof(CommReceiveEntry)];
    unknown_30 = new int[sendSlots];
    unknown_40 = new int[receiveSlots];
    for (int i = 0; i < unknown_04; i++) {
        unknown_24[i].unknown_14 = new char[maxlen];
        if (unknown_10 > 0) {
            unknown_24[i].unknown_1C = new char[unknown_10];
        } else {
            unknown_24[i].unknown_1C = 0;
        }
    }
    for (int j = 0; j < unknown_08; j++) {
        unknown_34[j].unknown_0C = new char[maxlen];
        if (unknown_10 > 0) {
            unknown_34[j].unknown_14 = new char[unknown_10];
        } else {
            unknown_34[j].unknown_14 = 0;
        }
    }
    Init();
}

// FUNCTION: GAMEMD 0x48B1F0
CommBufferClass::~CommBufferClass()
{
    for (int i = 0; i < unknown_04; i++) {
        delete[] unknown_24[i].unknown_14;
        if (unknown_24[i].unknown_1C) {
            delete[] (char*)unknown_24[i].unknown_1C;
        }
    }
    for (int j = 0; j < unknown_08; j++) {
        delete[] unknown_34[j].unknown_0C;
        if (unknown_34[j].unknown_14) {
            delete[] (char*)unknown_34[j].unknown_14;
        }
    }
    delete[] unknown_24;
    delete[] unknown_34;
    delete[] unknown_30;
    delete[] unknown_40;
}

// FUNCTION: GAMEMD 0x48B2A0
void CommBufferClass::Init()
{
    unknown_2C = 0;
    unknown_3C = 0;
    unknown_14 = 0;
    unknown_18 = 0;
    unknown_1C = 0;
    unknown_20 = 0;
    unknown_28 = 0;
    unknown_38 = 0;
    for (int i = 0; i < unknown_04; i++) {
        unknown_24[i].Flags &= ~1;
        unknown_24[i].Flags &= ~2;
        unknown_24[i].Flags &= ~4;
        unknown_24[i].unknown_04 = 0;
        unknown_24[i].unknown_08 = 0;
        unknown_24[i].unknown_0C = 0;
        unknown_24[i].unknown_10 = 0;
        unknown_24[i].unknown_18 = 0;
        unknown_24[i].unknown_20 = 0;
        unknown_30[i] = 0;
    }
    for (int j = 0; j < unknown_08; j++) {
        unknown_34[j].Flags &= ~1;
        unknown_34[j].Flags &= ~2;
        unknown_34[j].Flags &= ~4;
        unknown_34[j].unknown_04 = 0;
        unknown_34[j].unknown_08 = 0;
        unknown_34[j].unknown_10 = 0;
        unknown_40[j] = 0;
    }
    unknown_44 = 0;
    unknown_48 = 0;
    unknown_4C = 0;
    unknown_54 = 0;
}

// FUNCTION: GAMEMD 0x48B410
int CommBufferClass::FUN_0048B410(void* a1, int a2, void* a3, int a4, unsigned short a5)
{
    if (unknown_28 == unknown_04 || a2 > unknown_0C) {
        if (unknown_28 == unknown_04) {
            FUN_004068E0("Queue_Send - No room in send queue\n");
        } else {
            FUN_004068E0("buflen > MaxPacketSize by %d bytes\n", unknown_0C - a2);
        }
        return 0;
    }
    int index = -1;
    for (int i = 0; i < unknown_04; i++) {
        if (!(unknown_24[i].Flags & 1)) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return 0;
    }
    unknown_24[index].Flags |= 1;
    unknown_24[index].Flags &= ~2;
    unknown_24[index].Flags &= ~4;
    unknown_24[index].unknown_04 = 0;
    unknown_24[index].unknown_08 = 0;
    unknown_24[index].unknown_0C = 0;
    unknown_24[index].unknown_10 = a2;
    unknown_24[index].unknown_20 = a5;
    memcpy(unknown_24[index].unknown_14, a1, a2);
    if (a3 && a4 > 0 && a4 <= unknown_10) {
        memcpy(unknown_24[index].unknown_1C, a3, a4);
        unknown_24[index].unknown_18 = a4;
    } else {
        unknown_24[index].unknown_18 = 0;
    }
    unknown_30[unknown_28] = index;
    unknown_28++;
    unknown_2C++;
    return 1;
}

// FUNCTION: GAMEMD 0x48B570
int CommBufferClass::FUN_0048B570(void* a1, int* a2, int a3, void* a4, int* a5, unsigned short* a6)
{
    if (unknown_28 == 0 || !(unknown_24[unknown_30[a3]].Flags & 1)) {
        return 0;
    }
    if (a1) {
        memcpy(a1, unknown_24[unknown_30[a3]].unknown_14, unknown_24[unknown_30[a3]].unknown_10);
        *a2 = unknown_24[unknown_30[a3]].unknown_10;
    }
    if (a4 && a5) {
        memcpy(a4, unknown_24[unknown_30[a3]].unknown_1C, unknown_24[unknown_30[a3]].unknown_18);
        *a5 = unknown_24[unknown_30[a3]].unknown_18;
    }
    if (a6) {
        *a6 = unknown_24[unknown_30[a3]].unknown_20;
    }
    unknown_24[unknown_30[a3]].Flags &= ~1;
    unknown_24[unknown_30[a3]].Flags &= ~2;
    unknown_24[unknown_30[a3]].Flags &= ~4;
    unknown_24[unknown_30[a3]].unknown_04 = 0;
    unknown_24[unknown_30[a3]].unknown_08 = 0;
    unknown_24[unknown_30[a3]].unknown_0C = 0;
    unknown_24[unknown_30[a3]].unknown_10 = 0;
    unknown_24[unknown_30[a3]].unknown_18 = 0;
    unknown_24[unknown_30[a3]].unknown_20 = 0;
    for (int i = a3; i < unknown_28 - 1; i++) {
        unknown_30[i] = unknown_30[i + 1];
    }
    unknown_30[unknown_28 - 1] = 0;
    unknown_28--;
    return 1;
}

// FUNCTION: GAMEMD 0x48B750
int CommBufferClass::FUN_0048B750(void* a1, int a2, void* a3, int a4)
{
    if (unknown_38 == unknown_08 || a2 > unknown_0C) {
        return 0;
    }
    int index = -1;
    for (int i = 0; i < unknown_08; i++) {
        if (!(unknown_34[i].Flags & 1)) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        FUN_004068E0("Can't queue incoming packet - Unable to find free slot in array.\n");
        return 0;
    }
    unknown_34[index].Flags |= 1;
    unknown_34[index].Flags &= ~2;
    unknown_34[index].Flags &= ~4;
    unknown_34[index].unknown_04 = ConnTimer.GetValue();
    unknown_34[index].unknown_08 = a2;
    memcpy(unknown_34[index].unknown_0C, a1, a2);
    if (a3 && a4 > 0 && a4 <= unknown_10) {
        memcpy(unknown_34[index].unknown_14, a3, a4);
        unknown_34[index].unknown_10 = a4;
    } else {
        unknown_34[index].unknown_10 = 0;
    }
    unknown_40[unknown_38] = index;
    unknown_38++;
    unknown_3C++;
    return 1;
}

// FUNCTION: GAMEMD 0x48B890
int CommBufferClass::FUN_0048B890(void* a1, int* a2, int a3, void* a4, int* a5)
{
    if (unknown_38 == 0 || !(unknown_34[unknown_40[a3]].Flags & 1)) {
        return 0;
    }
    if (a1) {
        memcpy(a1, unknown_34[unknown_40[a3]].unknown_0C, unknown_34[unknown_40[a3]].unknown_08);
        *a2 = unknown_34[unknown_40[a3]].unknown_08;
    }
    if (a4 && a5) {
        memcpy(a4, unknown_34[unknown_40[a3]].unknown_14, unknown_34[unknown_40[a3]].unknown_10);
        *a5 = unknown_34[unknown_40[a3]].unknown_10;
    }
    unknown_34[unknown_40[a3]].Flags &= ~1;
    unknown_34[unknown_40[a3]].Flags &= ~2;
    unknown_34[unknown_40[a3]].Flags &= ~4;
    unknown_34[unknown_40[a3]].unknown_08 = 0;
    unknown_34[unknown_40[a3]].unknown_10 = 0;
    for (int i = a3; i < unknown_38 - 1; i++) {
        unknown_40[i] = unknown_40[i + 1];
    }
    unknown_40[unknown_38 - 1] = 0;
    unknown_38--;
    return 1;
}
