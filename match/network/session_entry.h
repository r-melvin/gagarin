// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Retail vector RTTI identifies entries at0xA8B8C8 as class MultiMission.
// 0x69ACD0 copies 44 UTF-16 units at +0; 0x69AD20 copies 0x104 bytes
// at +0x58; 0x69AD80 copies 0x20 bytes at +0x15C. Each terminates
// the last element. Constructor0x69A980 seats TypeList<DiskID> at188
// and DynamicVectorClass<Wstring> at1A4. Caller5E865D allocates1BC.
// TypeList tail+18 is storage, not a new field meaning or initialization claim.
// Constructor0x69A980 uses the two canonical vector members and owning strings.
#ifndef GG_MATCH_NETWORK_SESSION_ENTRY_H
#define GG_MATCH_NETWORK_SESSION_ENTRY_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/disk_id.h"
#include "../core/type_list.h"
#include "../core/string_class.h"
class INIClass;
class MultiMission
{
public:
    wchar_t unknown_000[0x2C];
    char unknown_058[0x104];
    char unknown_15C[0x20];
    bool unknown_17C;
    char unknown_17D[3];
    int unknown_180;
    int unknown_184;
    TypeList<DiskID> unknown_188;
    DynamicVectorClass<Wstring> unknown_1A4;
    // Declaration: GAMEMD 0x69A3B0 -- INI receiver and section, RET8.
    MultiMission(INIClass* ini, const char* section);
    // Declaration: GAMEMD 0x69A980
    MultiMission(const char* filename, const wchar_t* description,
                 const char* digest, bool flag, const char* modeList,
                 int value180, int value184);
    // Declaration at 0x69AC30
    bool FUN_0069AC30(int value);
    // Declaration at 0x69ACD0
    void FUN_0069ACD0(const wchar_t* source);
    // Declaration at 0x69AD20
    void FUN_0069AD20(const char* source);
    // Declaration at 0x69AD80
    void FUN_0069AD80(const char* source);
    // Declaration at 0x69ADF0
    bool FUN_0069ADF0();
    // Declaration at 0x69AE10 (declaration)
    bool FUN_0069AE10(Wstring* mode);
};
GG_STATIC_ASSERT(offsetof(MultiMission, unknown_000) == 0);
GG_STATIC_ASSERT(sizeof(((MultiMission*)0)->unknown_000) == 0x58);
GG_STATIC_ASSERT(offsetof(MultiMission, unknown_058) == 0x58);
GG_STATIC_ASSERT(sizeof(((MultiMission*)0)->unknown_058) == 0x104);
GG_STATIC_ASSERT(offsetof(MultiMission, unknown_15C) == 0x15C);
GG_STATIC_ASSERT(sizeof(((MultiMission*)0)->unknown_15C) == 0x20);
GG_STATIC_ASSERT(offsetof(MultiMission, unknown_17C) == 0x17C);
GG_STATIC_ASSERT(sizeof(((MultiMission*)0)->unknown_17C) == 1);
typedef TypeList<DiskID> MultiMissionDiskList;
GG_STATIC_ASSERT(sizeof(MultiMissionDiskList) == 0x1C);
GG_STATIC_ASSERT(offsetof(MultiMission, unknown_180) == 0x180);
GG_STATIC_ASSERT(offsetof(MultiMission, unknown_184) == 0x184);
GG_STATIC_ASSERT(offsetof(MultiMission, unknown_188) == 0x188);
GG_STATIC_ASSERT(offsetof(MultiMission, unknown_188) + offsetof(MultiMissionDiskList, Items) == 0x18C);
GG_STATIC_ASSERT(offsetof(MultiMission, unknown_188) + offsetof(MultiMissionDiskList, Count) == 0x198);
GG_STATIC_ASSERT(offsetof(MultiMission, unknown_1A4) == 0x1A4);
typedef DynamicVectorClass<Wstring> MultiMissionModeList;
GG_STATIC_ASSERT(offsetof(MultiMission, unknown_1A4) + offsetof(MultiMissionModeList, Items) == 0x1A8);
GG_STATIC_ASSERT(offsetof(MultiMission, unknown_1A4) + offsetof(MultiMissionModeList, Count) == 0x1B4);
GG_STATIC_ASSERT(sizeof(((MultiMissionModeList*)0)->Count) == 4);
GG_STATIC_ASSERT(sizeof(MultiMission) == 0x1BC);
GG_STATIC_ASSERT(sizeof(((MultiMission*)0)->unknown_180) == 4);
GG_STATIC_ASSERT(sizeof(((MultiMission*)0)->unknown_184) == 4);
GG_STATIC_ASSERT(sizeof(((MultiMissionDiskList*)0)->Count) == 4);
#endif
