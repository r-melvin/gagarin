// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Scenario.CPP. The name is the source-file string at 0x83d838
//   in retail gamemd.exe v1.001, passed by the assert at 0x6835e1 inside this object's
//   code range (0x683070-0x68cb2f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   0x68BD80). Names cross-checked against YRpp (every offset/address reconfirmed against the user's binary).
//
//   GLOBAL:   GAMEMD 0x87F7E8   MapClass::Instance
//   GLOBAL:   GAMEMD 0x00B05458 undefined-waypoint sentinel cell
//
//   Every displacement, constant, table bound and callee below was read off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. None of the owning classes is bound by RTTI or
//   a binary string here, so all keep placeholder names. The two imports are
//   named by the PE import table (GetAsyncKeyState 0x7E13E0, SendMessageA
//   0x7E14A4).
//
// Small leaves (64 bytes or less) between 0x500000 and 0x6B0000 that other
// translation units already declared as callees but nothing defined.

#include "../_layout/mp_score_runner.h"
#include "scenario_class_methods.h"
#include "../_layout/obj_004a1d30.h"
#include "vtable_seating_ctor_family_methods.h"
#include "vector_class_operations.h"
#include "../_layout/ini_class.h"
#include "../_layout/cd_callback.h"
#include "../_layout/global_0081c1d0.h"
#include "../platform/ccini_class_methods.h"
#include "../platform/ccfile_class.h"
#include "../map/class_sweep_00581f50.h"
#include "frame_counter.h"
#include "../audio/theme_class_methods.h"
#include "../ui/tooltip_manager_shared.h"
#include "../combat/evade_class_do_methods.h"
#include "spin_wait_methods.h"
#include "../network/transport/conn_types.h"
#include "../audio/vox_class_methods.h"
#include "campaign_class.h"
#include "../_layout/house_type_class.h"
#include "../_layout/house_class.h"
#include "rules_class.h"
#include "../_layout/building_class.h"
#include "../_layout/audio_0048d080.h"
#include "../platform/input_manager_class_methods.h"
#include "../network/win_modem_class.h"
#include "../_layout/swizzle_manager_class.h"
#include "../_layout/tactical.h"
#include "../_layout/aircraft_tracker_class.h"
#include "../_layout/layer_class.h"
#include "../_layout/tag_type_class.h"
#include "../combat/kamikaze_class_methods.h"
#include "../combat/particles/system_class.h"
#include "small_misc35_methods.h"
#include "../_layout/tag_class.h"
#include "../_layout/trigger_type_class.h"
#include "../_layout/tiberium_class.h"
#include "../_layout/anim_class.h"
#include "../_layout/unit_class.h"
#include "../_layout/unit_type_class.h"
#include "../_layout/infantry_type_class.h"
#include "leftover_trivial_leaf_sweep.h"
#include "trivial_tu207_methods.h"
#include "../ui/game_options_class_methods.h"

#include "../_layout/load_progress_mgr.h"
#include "../_layout/dialog_005d3490.h"
#include "../network/transport/winsock_interface_class.h"
#include "../ui/message_list_class_methods.h"
#include "../_layout/map_seed_class.h"
extern char DAT_00ABDFD8[]; // GLOBAL: GAMEMD 0xABDFD8


// Each operand below is read from entry0x684620 primary assembly.
struct PaletteClass;
LoadProgressMgr* __fastcall FUN_00552A40(); // FUNCTION: GAMEMD 0x552A40 (decl)
void __fastcall FUN_00552AA0(); // FUNCTION: GAMEMD 0x552AA0 (decl; RET, no incoming args read)
void __fastcall FUN_004A3C30(PaletteClass* palette, int duration, void (__fastcall* callback)()); // FUNCTION: GAMEMD 0x4A3C30 (decl)
int __fastcall FUN_0072B380(); // FUNCTION: GAMEMD 0x72B380 (decl)
int __cdecl sprintf(char* out, const char* format, ...); // LIBRARY: GAMEMD 0x7C8EF4
int __cdecl swprintf(wchar_t* out, const wchar_t* format, ...); // LIBRARY: GAMEMD 0x7CA564
bool __fastcall FUN_00686730(const char* filename); // FUNCTION: GAMEMD 0x686730 (decl)
void __fastcall FUN_00686890(bool flag); // FUNCTION: GAMEMD 0x686890 (decl)
void __fastcall FUN_00684C30(); // FUNCTION: GAMEMD 0x684C30 (decl)
extern int DAT_00B779C4; // GLOBAL: GAMEMD 0xB779C4
extern int DAT_00B779D4; // GLOBAL: GAMEMD 0xB779D4
extern unsigned short Ports_00A8E2B2[]; // GLOBAL: GAMEMD 0xA8E2B2
extern bool DAT_00A8B8C1; // GLOBAL: GAMEMD 0xA8B8C1
extern bool DAT_00A8B8C2; // GLOBAL: GAMEMD 0xA8B8C2
extern XYWHStruct DAT_00886FA0; // GLOBAL: GAMEMD 0x886FA0
extern MessageListClass ScenarioMessageList_00A8BC60; // GLOBAL: GAMEMD 0xA8BC60
extern PaletteClass DAT_00885780; // GLOBAL: GAMEMD 0x885780
extern const char STR_0083DA88[]; // STRING: GAMEMD 0x83DA88
extern const char STR_0083DA70[]; // STRING: GAMEMD 0x83DA70
extern const char STR_0083DA58[]; // STRING: GAMEMD 0x83DA58
extern const char STR_0083DA4C[]; // STRING: GAMEMD 0x83DA4C
extern const char STR_0083DA40[]; // STRING: GAMEMD 0x83DA40
extern const char STR_0083DA30[]; // STRING: GAMEMD 0x83DA30
extern const char STR_0083DA08[]; // STRING: GAMEMD 0x83DA08
extern const char STR_0083D9FC[]; // STRING: GAMEMD 0x83D9FC
extern const char STR_0083D9DC[]; // STRING: GAMEMD 0x83D9DC
extern const char STR_0083D9B4[]; // STRING: GAMEMD 0x83D9B4
extern const char STR_00825FB0[]; // STRING: GAMEMD 0x825FB0
extern const char STR_00831AF0[]; // STRING: GAMEMD 0x831AF0
GG_STATIC_ASSERT(offsetof(Point2D, X) == 0);
GG_STATIC_ASSERT(offsetof(Point2D, Y) == 4);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, SideIndex) == 0xBC);


#include "../network/multiplayer_game_mode.h"
#include "../network/transport/ipx_interface_class.h"
#include "../network/transport/connman_class.h"
#include "../platform/copy_protection_methods.h"
#include "trivial_tu223_methods.h"
extern MultiplayerGameMode* DAT_00A8B23C; // GLOBAL: GAMEMD 0xA8B23C
extern unsigned char DAT_00A8D5F8; // GLOBAL: GAMEMD 0xA8D5F8
extern int DAT_00A8D57C; // GLOBAL: GAMEMD 0xA8D57C
extern int DAT_00A8D588; // GLOBAL: GAMEMD 0xA8D588
extern unsigned short DAT_00A8D610; // GLOBAL: GAMEMD 0xA8D610
extern int DAT_00A8B570; // GLOBAL: GAMEMD 0xA8B570
extern unsigned int DAT_00A8DA90[8]; // GLOBAL: GAMEMD 0xA8DA90
extern unsigned int DAT_00A8B2BC[8]; // GLOBAL: GAMEMD 0xA8B2BC
extern unsigned int DAT_00A8B29C[8]; // GLOBAL: GAMEMD 0xA8B29C
extern unsigned int DAT_00A8B27C[8]; // GLOBAL: GAMEMD 0xA8B27C
extern const wchar_t DAT_00887734[]; // GLOBAL: GAMEMD 0x887734
extern const char STR_0083DB0C[]; // STRING: GAMEMD 0x83DB0C
void __fastcall FUN_00648350(); // FUNCTION: GAMEMD 0x648350 (decl)
void __fastcall FUN_0055CF10(); // FUNCTION: GAMEMD 0x55CF10 (decl)
void __fastcall FUN_0052FEC0(void*, unsigned char); // FUNCTION: GAMEMD 0x52FEC0 (decl)
void __fastcall FUN_004C3E30(); // FUNCTION: GAMEMD 0x4C3E30 (decl)
bool __fastcall FUN_005DB680(); // FUNCTION: GAMEMD 0x5DB680 (decl)
int __fastcall FUN_005ADD10(ScenarioClass* scenario); // FUNCTION: GAMEMD 0x5ADD10 (decl)
int __fastcall FUN_005ADE20(ScenarioClass* scenario, const char* filename); // FUNCTION: GAMEMD 0x5ADE20 (decl)

extern const char STR_0083DB24[]; // STRING: GAMEMD 0x83DB24
extern const char STR_00829F14[]; // STRING: GAMEMD 0x829F14
extern const char STR_00829F1C[]; // STRING: GAMEMD 0x829F1C
extern const char STR_008262F0[]; // STRING: GAMEMD 0x8262F0

extern int DAT_00A8E7AC; // GLOBAL: GAMEMD 0x00A8E7AC
extern DynamicVectorClass<BuildingClass*> DAT_00A8EB40; // GLOBAL: GAMEMD 0x00A8EB40
extern int HouseClass_ArrayCount; // GLOBAL: GAMEMD 0x00A80238
extern TiberiumClass** TiberiumArrayItems; // GLOBAL: GAMEMD 0x00B0F4EC
extern ParticleCoord DAT_00B05488; // GLOBAL: GAMEMD 0x00B05488
extern const char STR_0083DA90[]; // STRING: GAMEMD 0x0083DA90 (decl)
int __fastcall FUN_00644630(const char* id); // GAMEMD 0x644630; ECX=id, no stack args
void __fastcall FUN_0075F020(); // GAMEMD 0x75F020
HouseClass* __fastcall FUN_00502D30(int index); // GAMEMD 0x502D30
extern DynamicVectorClass<UnitTypeClass*> DAT_00A83CE0; // GLOBAL: GAMEMD 0x00A83CE0
extern DynamicVectorClass<InfantryTypeClass*> DAT_00A8E348; // GLOBAL: GAMEMD 0x00A8E348
extern char DAT_00A8B258; // GLOBAL: GAMEMD 0x00A8B258
extern int DAT_00A8B270; // GLOBAL: GAMEMD 0x00A8B270
extern const char STR_0083DDA8[]; // STRING: GAMEMD 0x0083DDA8
extern const char STR_0083DD94[]; // STRING: GAMEMD 0x0083DD94
extern const char STR_0083DD70[]; // STRING: GAMEMD 0x0083DD70
extern const char STR_0083DD50[]; // STRING: GAMEMD 0x0083DD50
extern const char STR_00830990[]; // STRING: GAMEMD 0x00830990
int __fastcall FUN_00688ED0(ObjectClass* object, const CellStruct* cell, int distance); // GAMEMD 0x688ED0
TechnoClass* __fastcall FUN_0040DD70(ObjectClass* object); // GAMEMD 0x40DD70; checked type filter
void __fastcall FUN_007500B0(int value); // GAMEMD 0x7500B0
double __cdecl FUN_004CAC40(double value); // GAMEMD 0x4CAC40
extern unsigned char DAT_00A8ED5D; // GLOBAL: GAMEMD 0x00A8ED5D
extern char DAT_00A83E48[]; // GLOBAL: GAMEMD 0x00A83E48
extern int DAT_00A8B254; // GLOBAL: GAMEMD 0x00A8B254
extern Obj_0069ACC0** DAT_00A8B8CC; // GLOBAL: GAMEMD 0x00A8B8CC
extern char** DAT_00ABF394; // GLOBAL: GAMEMD 0x00ABF394
extern int DAT_00A8DAB4; // GLOBAL: GAMEMD 0x00A8DAB4
extern GameOptionsClass DAT_00A8EB60; // GLOBAL: GAMEMD 0x00A8EB60
void __fastcall FUN_004790B0(int value); // GAMEMD 0x4790B0
int __fastcall FUN_004790A0(int value); // GAMEMD 0x4790A0
void __cdecl FUN_004B6C30(); // GAMEMD 0x4B6C30; external ABI-only declaration
void __fastcall FUN_005BF260(int movie, int unused, int a, int b, int c); // GAMEMD 0x5BF260
bool __fastcall FUN_00684620(const char* filename); // GAMEMD 0x684620
void __fastcall FUN_004F4780(bool value, void* surface, int unused); // GAMEMD 0x4F4780
void __fastcall FUN_0072DEF0(); // GAMEMD 0x72DEF0
void __fastcall FUN_007781A0(); // GAMEMD 0x7781A0
void __fastcall FUN_0078ABF0(char flag, const wchar_t* text); // GAMEMD 0x78ABF0
extern const char STR_0083D8C4[]; // STRING: GAMEMD 0x0083D8C4
extern const char STR_0083D8B0[]; // STRING: GAMEMD 0x0083D8B0
extern const char STR_0083D890[]; // STRING: GAMEMD 0x0083D890
extern const char STR_0083D888[]; // STRING: GAMEMD 0x0083D888
extern const char STR_0083D8A8[]; // STRING: GAMEMD 0x0083D8A8
extern const char STR_0082BF9C[]; // STRING: GAMEMD 0x0082BF9C
extern const char STR_008241C0[]; // STRING: GAMEMD 0x008241C0
extern const char STR_0082C1BC[]; // STRING: GAMEMD 0x0082C1BC
extern Tactical* TacticalInstance; // GLOBAL: GAMEMD 0x00887324
extern ParticleSystemClass* DAT_00A8ED78; // GLOBAL: GAMEMD 0x00A8ED78
extern AircraftTrackerClass AircraftTracker; // GLOBAL: GAMEMD 0x00887888
extern Kamikaze DAT_00ABC5F8; // GLOBAL: GAMEMD 0x00ABC5F8
extern Obj_00439110 DAT_0087F5D8; // GLOBAL: GAMEMD 0x0087F5D8
extern HouseClass* CurrentPlayer; // GLOBAL: GAMEMD 0x00A83D4C
extern DynamicVectorClass<AbstractTypeClass*> DAT_00A8E968; // GLOBAL: GAMEMD 0x00A8E968
class IsometricTileTypeClass;
extern DynamicVectorClass<IsometricTileTypeClass*> DAT_00A8ED28; // GLOBAL: GAMEMD 0x00A8ED28
extern DynamicVectorClass<ObjectClass*> DAT_00A8E360; // GLOBAL: GAMEMD 0x00A8E360
class TagClass;
extern DynamicVectorClass<TagClass*> DAT_008B41A8; // GLOBAL: GAMEMD 0x008B41A8
extern DynamicVectorClass<TagClass*> DAT_008B40C8; // GLOBAL: GAMEMD 0x008B40C8
extern DynamicVectorClass<ObjectClass*> DAT_00A8ECB8; // GLOBAL: GAMEMD 0x00A8ECB8
extern DynamicVectorClass<void*> DAT_0087F838; // GLOBAL: GAMEMD 0x0087F838
extern int DAT_0083D834; // GLOBAL: GAMEMD 0x0083D834
extern bool DAT_00829AE4; // GLOBAL: GAMEMD 0x00829AE4
extern int DAT_0087F8D4; // GLOBAL: GAMEMD 0x0087F8D4
extern int DAT_0087F8D8; // GLOBAL: GAMEMD 0x0087F8D8
extern int DAT_0087F8DC; // GLOBAL: GAMEMD 0x0087F8DC
extern int DAT_0087F8E0; // GLOBAL: GAMEMD 0x0087F8E0
extern const char STR_0083DAF8[]; // STRING: GAMEMD 0x0083DAF8 (decl)
extern const char STR_0083DAE8[]; // STRING: GAMEMD 0x0083DAE8 (decl)
extern const char STR_0083DAD0[]; // STRING: GAMEMD 0x0083DAD0 (decl)
extern const char STR_0083DAB0[]; // STRING: GAMEMD 0x0083DAB0 (decl)
extern const char STR_0083DA9C[]; // STRING: GAMEMD 0x0083DA9C (decl)
void __fastcall FUN_0053A090(); // GAMEMD 0x53A090
void __fastcall FUN_00534450(); // GAMEMD 0x534450
void __fastcall FUN_006E5570(); // GAMEMD 0x6E5570
void __fastcall FUN_005549A0(); // GAMEMD 0x5549A0
void __fastcall FUN_00539760(); // GAMEMD 0x539760
void __fastcall FUN_004C5470(); // GAMEMD 0x4C5470
void __fastcall FUN_0074D760(); // GAMEMD 0x74D760
void __fastcall FUN_00722390(); // GAMEMD 0x722390
void __fastcall FUN_00722E50(); // GAMEMD 0x722E50
void __fastcall FUN_006370B0(); // GAMEMD 0x6370B0
void __fastcall FUN_0052CB90(); // GAMEMD 0x52CB90

// GLOBAL: GAMEMD 0x00B0C110
extern SwizzleManagerClass DAT_00B0C110;
extern const char STR_0083DDF8[]; // STRING: GAMEMD 0x0083DDF8 (decl)
extern const char STR_0083DD20[]; // STRING: GAMEMD 0x0083DD20 (decl)
extern const char STR_0083DCD4[]; // STRING: GAMEMD 0x0083DCD4 (decl)
extern const char STR_0083DC9C[]; // STRING: GAMEMD 0x0083DC9C (decl)
extern int DAT_00A8B274; // GLOBAL: GAMEMD 0x00A8B274
extern int DAT_0087F90C; // GLOBAL: GAMEMD 0x0087F90C
extern int DAT_0087F910; // GLOBAL: GAMEMD 0x0087F910
extern int DAT_0087F914; // GLOBAL: GAMEMD 0x0087F914
extern int DAT_0087F918; // GLOBAL: GAMEMD 0x0087F918

// GLOBAL: GAMEMD 0x00B72D20
extern WinModemClass* WinModem_00B72D20;
// GLOBAL: GAMEMD 0x00A8022C
extern HouseClass** HouseClass_ArrayItems;
// GLOBAL: GAMEMD 0x00A8E2AC
extern int DAT_00A8E2AC;
// GLOBAL: GAMEMD 0x00A8E258
extern wchar_t DAT_00A8E258[21];
extern const char STR_0083D984[]; // STRING: GAMEMD 0x0083D984 (decl)
extern const char STR_0083D94C[]; // STRING: GAMEMD 0x0083D94C (decl)
void __fastcall FUN_005DA750(int id, int value); // FUNCTION: GAMEMD 0x5DA750 (decl; ECX id, EDX=1 at 0x684596)

// GLOBAL: GAMEMD 0x008B41E4
extern BuildingClass** DAT_008B41E4;
// GLOBAL: GAMEMD 0x008B41F0
extern int DAT_008B41F0;

#include "scenario_class_start_points_methods.h"

#include "trivial_tu201_methods.h"

#include "../ui/input_controls/mouse_ww_mouse_class.h"
#include "../platform/input_manager_class_methods.h"

#include <windows.h>
#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);
extern "C" int __cdecl strcmp(const char*, const char*);

// LIBRARY: GAMEMD 0x7c91d0
// _strncpy
extern "C" char* __cdecl strncpy(char*, const char*, unsigned int);
// FUNCTION: GAMEMD 0x6e57f0 (decl; reloc)
// @FUN_006E57F0@4
extern "C" void __fastcall FUN_006E57F0(unsigned int);
// FUNCTION: GAMEMD 0x6e5820 (decl; reloc)
// @FUN_006E5820@4
extern "C" void __fastcall FUN_006E5820(unsigned int);

// GLOBAL: GAMEMD 0x00886FB8
extern int DAT_00886FB8;
// GLOBAL: GAMEMD 0x00886FBC
extern int DAT_00886FBC;
// GLOBAL: GAMEMD 0x00A8EB84
extern int DAT_00A8EB84;
// GLOBAL: GAMEMD 0x00A8EB88
extern int DAT_00A8EB88;
// GLOBAL: GAMEMD 0x00A8EB8C
extern int DAT_00A8EB8C;
// GLOBAL: GAMEMD 0x00A8EB90
extern int DAT_00A8EB90;
// FUNCTION: GAMEMD 0x4068e0 (decl; reloc)
// _FUN_004068E0
extern "C" int __cdecl FUN_004068E0(const char*, ...);
// FUNCTION: GAMEMD 0x560bf0 (decl; reloc)
// @FUN_00560BF0@8
extern "C" void __fastcall FUN_00560BF0(int, int);

// GLOBAL: GAMEMD 0x00A8B230
extern ScenarioClass* ScenarioInstance;
// GLOBAL: GAMEMD 0x00A8ED9C
extern unsigned char DAT_00A8ED9C;
// GLOBAL: GAMEMD 0x00B07784
extern int DAT_00B07784;

// GLOBAL: GAMEMD 0x00B054CC
extern unsigned char DAT_00B054CC;
// FUNCTION: GAMEMD 0x406f40 (decl; reloc)
// _FUN_00406F40
extern "C" void __cdecl FUN_00406F40();

// GLOBAL: GAMEMD 0x00A8B238
extern int DAT_00A8B238;
// FUNCTION: GAMEMD 0x406f00 (decl; reloc)
// _FUN_00406F00
extern "C" void __cdecl FUN_00406F00();

extern "C" int __cdecl atoi(const char*);
extern "C" char* __cdecl strtok(char*, const char*);
extern "C" char* __cdecl strcpy(char*, const char*);
// GLOBAL: GAMEMD 0x007F0E48
extern const char* DAT_007F0E48;

// GLOBAL: GAMEMD 0x007F0E60
extern const char* DAT_007F0E60;
// GLOBAL: GAMEMD 0x00B054BC
extern int DAT_00B054BC;

// FUNCTION: GAMEMD 0x763610 (decl; reloc)
// @FUN_00763610@4
extern "C" const char* __fastcall FUN_00763610(int index);

void __fastcall FUN_00465450(); // GAMEMD 0x00465450
void __fastcall FUN_007236D0(); // GAMEMD 0x007236D0
void __fastcall FUN_0053AB50(); // GAMEMD 0x0053AB50
void __fastcall FUN_004261D0(); // GAMEMD 0x004261D0
void __fastcall FUN_00734210(); // GAMEMD 0x00734210
void __fastcall FUN_00660C50(); // GAMEMD 0x00660C50
void __fastcall FUN_0074D450(int value); // GAMEMD 0x0074D450
void __fastcall FUN_0071DCA0(int value); // GAMEMD 0x0071DCA0
void __fastcall FUN_006B5490(int value); // GAMEMD 0x006B5490
void __fastcall FUN_00734270(ObjectClass* value); // GAMEMD 0x734270
// GLOBAL: GAMEMD 0x00B0EA80
extern CDTimerClass DAT_00B0EA80;
// GLOBAL: GAMEMD 0x00B73550
extern HWND DAT_00B73550;

// Inline countdown expansion at 0x68517E; no separate entry is claimed.
inline int FUN_00685120_TimeLeft(const CDTimerClass& timer)
{
    int left = timer.TimeLeft;
    if (timer.StartTime != -1) {
        int elapsed = CurrentFrame - timer.StartTime;
        left = elapsed < left ? left - elapsed : 0;
    }
    return left;
}

void __fastcall FUN_0072DDB0(); // GAMEMD 0x0072DDB0
void __fastcall FUN_005BF450(); // GAMEMD 0x005BF450
void __fastcall FUN_00406E80(); // GAMEMD 0x00406E80
void __fastcall FUN_00750FA0(); // GAMEMD 0x00750FA0
void __fastcall FUN_00752CA0(); // GAMEMD 0x00752CA0
void __fastcall FUN_0048D080(); // GAMEMD 0x0048D080
void __fastcall FUN_007529A0(bool enabled); // GAMEMD 0x7529A0
bool __fastcall FUN_00683AB0(const char* filename, bool flag, int value); // GAMEMD 0x683AB0
// GLOBAL: GAMEMD 0x00A8ED5C
extern bool DAT_00A8ED5C;
// GLOBAL: GAMEMD 0x00A8E378
extern bool DAT_00A8E378;
// GLOBAL: GAMEMD 0x00887368
extern ToolTipManager* DAT_00887368;
// GLOBAL: GAMEMD 0x00A83D10
extern ThemeClass DAT_00A83D10;
// GLOBAL: GAMEMD 0x008A38E0
extern EvadeClass DAT_008A38E0;
// GLOBAL: GAMEMD 0x00A8EB80
extern bool DAT_00A8EB80;

void __fastcall FUN_00407070(void* value); // GAMEMD 0x407070
void __fastcall FUN_00407150(Queue_004070B0* value, int flags); // GAMEMD 0x407150
bool __fastcall FUN_007529E0(); // GAMEMD 0x7529E0
// GLOBAL: GAMEMD 0x0087E758
extern Queue_004070B0* DAT_0087E758;
// GLOBAL: GAMEMD 0x0088730C
extern MouseSurfaceView* DAT_0088730C;
// GLOBAL: GAMEMD 0x00A8E9A0
extern unsigned char DAT_00A8E9A0;
// GLOBAL: GAMEMD 0x0083DB34
extern const char STR_0083DB34[];

// GLOBAL: GAMEMD 0x00A83C9C
extern HouseTypeClass** DAT_00A83C9C;

// FUNCTION: GAMEMD 0x4E6150 (decl; reloc)
// @FUN_004E6150@16
extern "C" void __fastcall FUN_004E6150(int*, char*, char*, int);
// FUNCTION: GAMEMD 0x5CAF70 (decl; reloc)
// ?FUN_005CAF70@@YIIPAI@Z
unsigned int __fastcall FUN_005CAF70(unsigned int* high);
// GLOBAL: GAMEMD 0x007F0E50
extern const double DAT_007F0E50;
// GLOBAL: GAMEMD 0x007E51F8
extern const double DAT_007E51F8;
// GLOBAL: GAMEMD 0x007EF918
extern const double DAT_007EF918;
// GLOBAL: GAMEMD 0x007F0E58
extern const double DAT_007F0E58;

// STRING: GAMEMD 0x0083DDD4
// "Scenario Save: ElapsedTimer = %ld\n"
extern const char STR_0083DDD4[];

// GLOBAL: GAMEMD 0x00A8ED84
extern int DAT_00A8ED84;
// FUNCTION: GAMEMD 0x686B20 (decl; reloc)
// ?FUN_00686B20@@YI_NPAVCCINIClass@@_N@Z
bool __fastcall FUN_00686B20(CCINIClass* ini, bool flag);
// STRING: GAMEMD 0x0083DB6C
// "Read_Scenario_INI - Filename is %s\n"
extern const char STR_0083DB6C[];
// STRING: GAMEMD 0x0083DB50
// "Scenario ini load failed!\n"
extern const char STR_0083DB50[];

// LIBRARY: GAMEMD 0x7CA489
// _wcscpy
extern "C" wchar_t* __cdecl wcscpy(wchar_t*, const wchar_t*);
// FUNCTION: GAMEMD 0x734E60 (decl; reloc)
// ?FUN_00734E60@@YIPB_WPBDH0H@Z
const wchar_t* __fastcall FUN_00734E60(const char* id, int zero, const char* file, int line);
// STRING: GAMEMD 0x0083D838
// "D:\\ra2mdpost\\Scenario.CPP"
extern const char STR_0083D838[];

// GLOBAL: GAMEMD 0x00A8ED6B
extern bool DAT_00A8ED6B;
// GLOBAL: GAMEMD 0x00ABE154
extern SeatNull_006406E0* DAT_00ABE154;

void __fastcall FUN_00501160(CCINIClass* ini); // GAMEMD 0x00501160
void __fastcall FUN_0071CB90(CCINIClass* ini); // GAMEMD 0x0071CB90
void __fastcall FUN_007436E0(CCINIClass* ini); // GAMEMD 0x007436E0
void __fastcall FUN_0051FEF0(CCINIClass* ini); // GAMEMD 0x0051FEF0
void __fastcall FUN_0041AF80(CCINIClass* ini); // GAMEMD 0x0041AF80
void __fastcall FUN_0044FE60(CCINIClass* ini); // GAMEMD 0x0044FE60
void __fastcall FUN_005FD6A0(CCINIClass* ini); // GAMEMD 0x005FD6A0
void __fastcall FUN_006B4DD0(CCINIClass* ini); // GAMEMD 0x006B4DD0
void __fastcall FUN_00728280(CCINIClass* ini); // GAMEMD 0x00728280
void __fastcall FUN_00727880(CCINIClass* ini); // GAMEMD 0x00727880
void __fastcall FUN_006E5FE0(CCINIClass* ini); // GAMEMD 0x006E5FE0
void __fastcall FUN_00691B30(CCINIClass* ini, int flag); // GAMEMD 0x00691B30
void __fastcall FUN_006E8340(CCINIClass* ini, int flag); // GAMEMD 0x006E8340
void __fastcall FUN_006F1AB0(CCINIClass* ini, int flag); // GAMEMD 0x006F1AB0
void __fastcall FUN_0041F490(CCINIClass* ini, int flag); // GAMEMD 0x0041F490

// A two-short cell value copied as one dword.
struct Cell_0050DEF0
{
    short X;
    short Y;

    Cell_0050DEF0() {}
    bool operator==(const Cell_0050DEF0& other) const
    {
        return X == other.X && Y == other.Y;
    }
};
GG_STATIC_ASSERT(sizeof(Cell_0050DEF0) == 4);

// GLOBAL: GAMEMD 0x008B40F8
extern "C" int DAT_008B40F8;
// GLOBAL: GAMEMD 0x00A8EF98
extern "C" Cell_0050DEF0 DAT_00A8EF98;
// GLOBAL: GAMEMD 0x00A9FAB0
extern "C" int DAT_00A9FAB0;
// GLOBAL: GAMEMD 0x00AA0444
extern "C" int DAT_00AA0444;
// GLOBAL: GAMEMD 0x00AA0168 (256 key-state words)
extern "C" short DAT_00AA0168[256];
// GLOBAL: GAMEMD 0x00B45B68
extern "C" int DAT_00B45B68;
// GLOBAL: GAMEMD 0x008B4130
extern "C" int DAT_008B4130;

// ---------------------------------------------------------------------------

struct Team_005095D0
{
    char Pad_00[0x24];
    int unknown_24;
    char Pad_28[4];
    void* unknown_2C;
};
GG_STATIC_ASSERT(offsetof(Team_005095D0, unknown_2C) == 0x2C);

// GLOBAL: GAMEMD 0x008B40EC
extern "C" Team_005095D0** DAT_008B40EC;

struct Obj_005095D0
{
    int FUN_005095D0(int kind);
};


struct Obj_0050DA10
{
    char Pad_00[0x5490];
    Cell_0050DEF0 unknown_5490;
    Cell_0050DEF0 unknown_5494;
    char Pad_5498[0x54F0 - 0x5498];
    Cell_0050DEF0 unknown_54F0;
    Cell_0050DEF0 unknown_54F4;
    Cell_0050DEF0 unknown_54F8;
    int unknown_54FC;
    char Pad_5500[0x577C - 0x5500];
    int unknown_577C;

    void FUN_0050DA10();
    void FUN_0050DA50();
    int FUN_0050DA80() const;
    Cell_0050DEF0 FUN_0050DEF0() const;
    void FUN_0050DFF0();
};
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_5490) == 0x5490);
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_54F0) == 0x54F0);
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_54FC) == 0x54FC);
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_577C) == 0x577C);

struct Obj_0053ECB0
{
    unsigned char unknown_0[10];

    Obj_0053ECB0();
};

struct Triple_0053EDA0
{
    short unknown_0;
    short unknown_2;
    short unknown_4;
};
GG_STATIC_ASSERT(sizeof(Triple_0053EDA0) == 6);

struct Obj_0053EDA0
{
    int unknown_0;
    Triple_0053EDA0 unknown_4;

    void FUN_0053EDA0(int* first, Triple_0053EDA0* rest) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0053EDA0, unknown_4) == 4);

struct Obj_005402B0
{
    void FUN_005402B0(int value);
};

struct Obj_00542FC0
{
    char Pad_00[0x48];
    Obj_005402B0* unknown_48;

    void FUN_00542FC0(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_00542FC0, unknown_48) == 0x48);

struct Entry_005657A0
{
    char Pad_00[0x24];
    Cell_0050DEF0 unknown_24;
};

// GLOBAL: GAMEMD 0x00ABDC50
extern "C" Entry_005657A0 DAT_00ABDC50;

struct Obj_005657A0
{
    char Pad_00[0x13C];
    Entry_005657A0** unknown_13C;

    Entry_005657A0* FUN_005657A0(const Cell_0050DEF0& cell) const;
};
GG_STATIC_ASSERT(offsetof(Obj_005657A0, unknown_13C) == 0x13C);

struct Obj_005B3700
{
    int unknown_0;
    char unknown_4;
    char unknown_5;
    char unknown_6;
    char unknown_7;
    char unknown_8;
    char unknown_9;
    char Pad_0A[6];
    double unknown_10;
    double unknown_18;

    Obj_005B3700();
};
GG_STATIC_ASSERT(offsetof(Obj_005B3700, unknown_10) == 0x10);

struct Slot_005B3A00
{
    char Bytes[0x20];
};

// GLOBAL: GAMEMD 0x00A8E3A8 (32-byte records)
extern "C" Slot_005B3A00 DAT_00A8E3A8[];

struct Obj_005B3A00
{
    char Pad_00[0xAC];
    int unknown_AC;
};
GG_STATIC_ASSERT(offsetof(Obj_005B3A00, unknown_AC) == 0xAC);

struct Iface_005BF500
{
    virtual void vf_0() = 0;
    virtual void vf_1() = 0;
    virtual void vf_2() = 0;
    virtual void vf_3(int value) = 0;
};

// GLOBAL: GAMEMD 0x00B45B5C
extern "C" Iface_005BF500** DAT_00B45B5C;

struct Vector_005C6120
{
    virtual void vf_0() = 0;
    virtual void vf_1() = 0;
    virtual void vf_2() = 0;
    virtual void vf_3() = 0;

    void** unknown_4;
    int Pad_08;
    int Pad_0C;
    int unknown_10;

    void FUN_005C6120();
};

struct Obj_005F9710
{
    char unknown_0;
    char unknown_1;
};

struct Quad_00645C30
{
    int unknown_0;
    int unknown_4;
    int unknown_8;
    int unknown_C;

    Quad_00645C30(int a, int b, int c, int d);
};

struct Record_00656580
{
    char Bytes[0x18];
};

struct Key_00656580
{
    char Pad_00[0xEF0];
    int unknown_EF0;
};
GG_STATIC_ASSERT(offsetof(Key_00656580, unknown_EF0) == 0xEF0);

struct Obj_00656580
{
    Record_00656580 unknown_0[1];

    Record_00656580* FUN_00656580(const Key_00656580* key);
};


struct Obj_0065AD30
{
    char Pad_00[0xE4];
    int* unknown_E4;

    int FUN_0065AD30(int index) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0065AD30, unknown_E4) == 0xE4);

struct Pair_0065C890
{
    int unknown_0;
    int unknown_4;

    Pair_0065C890(int a, int b);
};

struct Obj_0068BCB0
{
    char Pad_00[0x214];
    int unknown_214;
};
GG_STATIC_ASSERT(offsetof(Obj_0068BCB0, unknown_214) == 0x214);

struct Obj_0068C030
{
    char Pad_00[0x1180];
    int unknown_1180[16];

    int FUN_0068C030(int index) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0068C030, unknown_1180) == 0x1180);

struct Owner_006915D0
{
    char Pad_00[0xA0];
    unsigned int unknown_A0;
};
GG_STATIC_ASSERT(offsetof(Owner_006915D0, unknown_A0) == 0xA0);

struct Cursor_006915D0
{
    char Pad_00[0x24];
    Owner_006915D0* unknown_24;
    char Pad_28[4];
    unsigned int unknown_2C;
};
GG_STATIC_ASSERT(offsetof(Cursor_006915D0, unknown_2C) == 0x2C);

#pragma pack(push, 1)
struct Obj_00696F10
{
    char Pad_00[0x4B];
    int unknown_4B;
    int unknown_4F;
    int unknown_53;
    int unknown_57;
    int unknown_5B;
    int unknown_5F;
    int unknown_63;
    int unknown_67;

    int FUN_00696F10() const;
    int FUN_00696F20() const;
    int FUN_00696F50() const;
    int FUN_00696F70() const;
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_4B) == 0x4B);
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_67) == 0x67);

struct Obj_0069B540
{
    char Pad_00[0x24];
    int unknown_24;
    char Pad_28[0x4C - 0x28];
    int unknown_4C[8];
    int unknown_6C[8];
};
GG_STATIC_ASSERT(offsetof(Obj_0069B540, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(Obj_0069B540, unknown_6C) == 0x6C);

struct Obj_0069BBE0
{
    char Pad_00[0x30D8];
    char unknown_30D8;
};
GG_STATIC_ASSERT(offsetof(Obj_0069BBE0, unknown_30D8) == 0x30D8);

struct Type_006A46D0
{
    char Pad_00[0x24];
    char unknown_24[1];
};

// GLOBAL: GAMEMD 0x008B4124
extern "C" Type_006A46D0** DAT_008B4124;

#include "../renderer/color_scheme_find_methods.h"
#include "../renderer/convert_class_create_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F0E38
extern const double DAT_007F0E38;
// GLOBAL: GAMEMD 0xB05460
extern double DAT_00B05460;
// GLOBAL: GAMEMD 0xB054A8
extern double DAT_00B054A8;
// GLOBAL: GAMEMD 0xB054B0
extern int DAT_00B054B0;
// GLOBAL: GAMEMD 0xB054B4
extern int DAT_00B054B4;
// GLOBAL: GAMEMD 0xB054B8
extern int DAT_00B054B8;
// GLOBAL: GAMEMD 0xB054C0
extern double DAT_00B054C0;

// FUNCTION: GAMEMD 0x6830A0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_006830A0()
{
    DAT_00B054C0 = DAT_00B05460 / DAT_007F0E38;
}

// FUNCTION: GAMEMD 0x6830C0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_006830C0()
{
    DAT_00B054A8 = DAT_007E1718 / DAT_00B054C0;
}

// FUNCTION: GAMEMD 0x683240
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_00683240()
{
    DAT_00B054B8 = 0;
    DAT_00B054B0 = 0x80;
    DAT_00B054B4 = 0x80;
}

// FUNCTION: GAMEMD 0x6832B0
// Empty function.
void __cdecl FUN_006832B0()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6832C0
ScenarioClass::ScenarioClass()
    : unknown_0218(0), Timer_11E8(0), unknown_1218(0), unknown_1224(0),
      unknown_1230(0), unknown_123C(0), unknown_1248(0), unknown_34C0(0)
{
    FUN_00683610();
    unknown_3598 = false;
    unknown_34BD = false;
    FUN_006B8AE0();
    unknown_1254 = 1;
    unknown_34CC = -1;
    unknown_0004[0] = 0;
    unknown_0004[0x104] = 0;
    for (int i = 0; i < 702; ++i) Waypoints[i] = WaypointUndefined;
    wcscpy(unknown_1360, EmptyName_00887734);
    wcscpy(unknown_13DA, EmptyName_00887734);
    strcpy(unknown_125C, STR_00889F64);
    strcpy(unknown_1C50, STR_00889F64);
    strcpy(unknown_13BA, STR_00889F64);
    wcscpy(unknown_1450, EmptyName_00887734);
    for (i = 0; i < 50; ++i) {
        unknown_1C88[i].unknown_00[0] = 0;
        FUN_00689670(i, 0);
    }
    for (i = 0; i < 100; ++i) {
        unknown_248A[i].unknown_00[0] = 0;
        FUN_00689910(i, 0);
    }
    memset(&unknown_348E, 0, 16);
}

// FUNCTION: GAMEMD 0x683560
ScenarioClass::ScenarioClass(const AbstractNoInit& noInit)
    : unknown_0218(0), unknown_0614(noInit), unknown_11F8(noInit)
{
    // The incoming one-word argument is unused in retail; the existing tag
    // expresses the observed selective preservation, not a recovered type name.
    if (unknown_11F8.unknown_00[0])
        unknown_11F4 = FUN_00734E60(unknown_11F8.unknown_00, 0, STR_0083D838, 0x158);
    else
        unknown_11F4 = EmptyName_00887734;
}


// Declaration: GAMEMD 0x6886B0
void __fastcall FUN_006886B0(bool value);
// Declaration: GAMEMD 0x68C050
void __fastcall FUN_0068C050();
extern bool DAT_00A8B261; // GLOBAL: GAMEMD 0xA8B261
extern int DAT_00A8B54C; // GLOBAL: GAMEMD 0xA8B54C
extern unsigned int DAT_00A8D108; // GLOBAL: GAMEMD 0xA8D108
extern unsigned int DAT_00A8D10C; // GLOBAL: GAMEMD 0xA8D10C
extern const char STR_00817318[]; // STRING: GAMEMD 0x817318

// FUNCTION: GAMEMD 0x683AB0
bool __fastcall FUN_00683AB0(const char* filename, bool flag, int index)
{
    if ((!filename || strlen(filename) == 0) && index != -1) {
        if (DAT_00A8ED5D == 1) filename = DAT_00A83E48;
        else filename = CampaignArray.Items[index]->Scenario;
    }
    ScenarioInstance->unknown_34CC = index;
    FUN_004068E0(STR_0083D8C4, filename);
    FUN_004068E0(STR_0083D8B0, PlayerCount_00A8DA84);
    strcpy(ScenarioInstance->unknown_125C, filename);
    _strupr(ScenarioInstance->unknown_125C);
    FUN_004790B0(-1);
    if (Session_00A8B238.GameMode == 0) {
        if (ScenarioInstance->unknown_34CC != -1)
            FUN_004790B0(CampaignArray.Items[ScenarioInstance->unknown_34CC]->idxCD);
    } else if (DAT_00A8B254 != -1) {
        Obj_0069ACC0* entry = DAT_00A8B8CC[DAT_00A8B254];
        if (!entry->FUN_0069AC30(FUN_004790A0(60))) FUN_004790B0(entry->FUN_0069ACC0());
    }
    ++DAT_00A8DAB4;
    if (CD().FUN_004790E0(g_FileSearchMode)) {
        --DAT_00A8DAB4;
        WWMouseClassInstance->vf_3();
        {
            CCINIClass ini;
            CCFileClass file(filename);
            if (ini.ReadCCFile(&file, true, false)) {
                int movie = ini.FUN_004757D0(STR_0082BF9C, STR_008241C0, -1);
                if (movie == -1) movie = ini.FUN_004757D0(STR_0082BF9C, STR_0083D8A8, -1);
                if (movie != -1) {
                    DAT_00A83D10.Stop(false);
                    FUN_005BF260(movie, -1, 1, 1, 1);
                }
            }
        }
        FUN_004068E0(STR_0083D890, filename);
        DAT_00A83D10.FUN_00720BB0(DAT_00A83D10.FindIndex(STR_0082C1BC));
        if (!FUN_00684620(filename)) {
            WWMouseClassInstance->vf_4();
            if (Session_00A8B238.GameMode == 4) FUN_0078ABF0(0, EmptyName_00887734);
            return false;
        }
        char movie[28];
        if (ScenarioInstance->unknown_1438 != -1)
            wsprintfA(movie, STR_0083D888, DAT_00ABF394[ScenarioInstance->unknown_1438]);
        if (ScenarioInstance->unknown_34D0 > 0) FUN_004B6C30();
        if (flag) FUN_005BF260(ScenarioInstance->unknown_1444, -1, 1, 1, 1);
        if (DAT_00886FB8 != DAT_00A8EB84 || DAT_00886FBC != DAT_00A8EB88) {
            FUN_004068E0(STR_0083D868, DAT_00A8EB84, DAT_00A8EB88);
            FUN_00560BF0(DAT_00A8EB84, DAT_00A8EB88);
        }
        FUN_0072DEF0();
        DAT_00A8EB60.FUN_005FB160();
        DAT_0088730C->vf_06(0);
        FUN_004F4780(true, DAT_0088730C, 0);
        ScenarioInstance->unknown_0614.Resume();
        if (ScenarioInstance->unknown_1C70 == -1) DAT_00A83D10.Stop(true);
        else DAT_00A83D10.QueueSong(ScenarioInstance->unknown_1C70);
        FUN_007781A0();
        DAT_00A8ED5C = true;
        DAT_00A8E378 = true;
        if (Session_00A8B238.GameMode == 4) FUN_0078ABF0(0, EmptyName_00887734);
        return true;
    }
    if (Session_00A8B238.GameMode == 4) FUN_0078ABF0(0, EmptyName_00887734);
    return false;
}

// FUNCTION: GAMEMD 0x684060
void __fastcall FUN_00684060(int duration)
{
    if (duration) {
        ScenarioInstance->unknown_0620 = ScenarioElapsedTimer(duration * 60);
        if (ScenarioInstance->unknown_0630) return;
        ScenarioInstance->unknown_0630 = 1;
    }
    if (!ScenarioInstance->unknown_062C) {
        FUN_00406F00();
        if (DAT_00A8B238 == 0 || DAT_00A8B238 == 5) {
            ScenarioInstance->unknown_0614.Pause();
        }
        DAT_00B054CC = ScenarioInstance->unknown_35A2;
        if (!DAT_00B054CC) {
            MapInstance.FUN_006938C0();
            if (!WWMouseClassInstance->GetHideCount()) WWMouseClassInstance->vf_3();
            ScenarioInstance->unknown_35A2 = 1;
            DAT_00A8ED9C = 1;
            DAT_0087F770->DoSomething();
            DAT_00B07784 = 0;
        }
    }
    ++ScenarioInstance->unknown_062C;
}

// FUNCTION: GAMEMD 0x684180
void __cdecl FUN_00684180()
{
    if (ScenarioInstance->unknown_062C) {
        --ScenarioInstance->unknown_062C;
        if (ScenarioInstance->unknown_062C == 0) {
            if (!DAT_00B054CC) {
                if (ScenarioInstance->unknown_35A2 == 1) {
                    while (WWMouseClassInstance->GetHideCount()) {
                        WWMouseClassInstance->vf_4();
                    }
                }
                ScenarioInstance->unknown_35A2 = 0;
                DAT_00A8ED9C = 0;
                DAT_0087F770->DoSomething();
                DAT_00B07784 = 0;
            }
            ScenarioInstance->unknown_0614.Resume();
            FUN_00406F40();
        }
    }
}

// FUNCTION: GAMEMD 0x684240
void __cdecl FUN_00684240()
{
    MapInstance.FUN_006938C0();
    if (!WWMouseClassInstance->GetHideCount()) WWMouseClassInstance->vf_3();
    ScenarioInstance->unknown_35A2 = 1;
    DAT_00A8ED9C = 1;
    DAT_0087F770->DoSomething();
    DAT_00B07784 = 0;
}

// FUNCTION: GAMEMD 0x684290
void __cdecl FUN_00684290()
{
    if (ScenarioInstance->unknown_35A2 == 1 && WWMouseClassInstance->GetHideCount()) {
        do { WWMouseClassInstance->vf_4(); }
        while (WWMouseClassInstance->GetHideCount());
    }
    ScenarioInstance->unknown_35A2 = 0;
    DAT_00A8ED9C = 0;
    DAT_0087F770->DoSomething();
    DAT_00B07784 = 0;
}

// FUNCTION: GAMEMD 0x6842f0
void __fastcall FUN_006842F0(bool enabled)
{
    if (enabled) {
        if (DAT_00886FB8 != DAT_00A8EB84 || DAT_00886FBC != DAT_00A8EB88) {
            FUN_004068E0(STR_0083D868, DAT_00A8EB84, DAT_00A8EB88);
            FUN_00560BF0(DAT_00A8EB84, DAT_00A8EB88);
        }
    } else if (DAT_00886FB8 != DAT_00A8EB8C && DAT_00886FBC != DAT_00A8EB90) {
        FUN_004068E0(STR_0083D924);
        FUN_00560BF0(DAT_00A8EB8C, DAT_00A8EB90);
    }
}

// FUNCTION: GAMEMD 0x684370
bool __fastcall FUN_00684370()
{
    if (Session_00A8B238.GameMode == 0 || Session_00A8B238.GameMode == 5)
        return true;
    ScenarioElapsedTimer timeout;
    ScenarioElapsedTimer update(300);
    timeout = ScenarioElapsedTimer(3600);
    double previous = DAT_00AC4F58.FUN_006433D0();
    for (;;) {
        DAT_0087F770->FUN_0054F000();
        FUN_0048D080();
        if (Session_00A8B238.GameMode == 1 && WinModem_00B72D20 &&
            !(WinModem_00B72D20->Get_Modem_Status() & 0x80)) {
            FUN_004068E0(STR_0083D984);
            return false;
        }
        if (timeout.GetTimeLeft() <= 0) {
            int source = 1;
            for (int index = 1; index < PlayerCount_00A8DA84; ++index, ++source) {
                if (DAT_00AC4F58.FUN_00643E90(source) < 0.999) {
                    const char* first = NarrowName_007350C0(Players_00A8DA78[index]->Name);
                    const char* second = NarrowName_007350C0(Players_00A8DA78[index]->Name);
                    FUN_004068E0(STR_0083D94C, first, second);
                    int id = Players_00A8DA78[index]->unknown_6F;
                    FUN_005DA750(id, 1);
                    if (Session_00A8B238.FUN_00697E70(HouseClass_ArrayItems[id])) {
                        DAT_00A8E2AC = -1;
                        memset(DAT_00A8E258, 0, 42);
                    }
                    --index;
                }
            }
            return false;
        }
        double current = DAT_00AC4F58.FUN_006433D0();
        if (current >= 0.9995) {
            Session_00A8B238.FUN_0069AE90(ScenarioInstance->unknown_34BD ? 200 : 100);
            return true;
        }
        if (current != previous) {
            timeout = ScenarioElapsedTimer(7200);
            previous = current;
        }
        if (update.GetTimeLeft() <= 0) {
            update = ScenarioElapsedTimer(60);
            Session_00A8B238.FUN_0069AE90(ScenarioInstance->unknown_34BD ? 200 : 100);
        }
    }
}

// FUNCTION: GAMEMD 0x684620
bool __fastcall FUN_00684620(const char* filename)
{
    char scenario[260];
    strcpy(scenario, filename);
    CurrentFrame = 0;
    ScenarioInstance->unknown_3598 = true;
    ++DAT_00A8E7AC;
    ScenarioInstance->unknown_34BD = _stricmp(scenario + strlen(scenario) - 4, STR_0083DA88) == 0;
    FUN_004068E0(ScenarioInstance->unknown_34BD ? STR_0083DA70 : STR_0083DA58);
    LoadProgressMgr* manager = 0;
    if (!DAT_00A8ED6B) {
        int players = 1;
        if (Session_00A8B238.GameMode != 0 && Session_00A8B238.GameMode != 5)
            players = PlayerCount_00A8DA84;
        DAT_00AC4F58.FUN_00642A60(100.0, players, 0);
        wchar_t caption[132];
        const wchar_t* captionText = 0;
        if (Session_00A8B238.GameMode == 4 && DAT_00B779C4) {
            swprintf(caption, FUN_00734E60(STR_0083DA4C, 0, STR_0083D838, 0x4AF), DAT_00B779D4);
            captionText = caption;
        }
        manager = FUN_00552A40();
        manager->FUN_00552B10();
        DAT_00AC4F58.FUN_00643E80(manager);
        int side = 0;
        if (Session_00A8B238.GameMode == 0) {
            if (ScenarioInstance->unknown_34CC != -1)
                side = CampaignArray.Items[ScenarioInstance->unknown_34CC]->idxCD;
        } else {
            int country = Players_00A8DA78[0]->unknown_4B;
            if (country == -3) country = 0;
            side = DAT_00A83C9C[country]->SideIndex;
        }
        ScenarioInstance->unknown_34B8 = side;
        DAT_00AC4F58.FUN_00642B10(side);
        FUN_00552A40()->FUN_00552CC0();
        if (Session_00A8B238.GameMode == 0)
            DAT_00AC4F58.FUN_00642C20(STR_0083DA40, 0, FUN_0072B380());
        else
            DAT_00AC4F58.FUN_00642C20(STR_0083DA30, 0, 0);
        Point2D position;
        Point2D* point = manager->FUN_00552BE0(&position);
        bool multiplayer = Session_00A8B238.GameMode != 0;
        DAT_00AC4F58.FUN_00642C80(point->X, point->Y, captionText, multiplayer, multiplayer);
        DAT_00AC4F58.FUN_00642DF0(manager->FUN_00552C90());
        if (Interface_00887628 && Session_00A8B238.GameMode == 4 && PlayerCount_00A8DA84 > 1) {
            FUN_004068E0(STR_0083DA08);
            Interface_00887628->ClearBroadcastAddresses();
            // Literal bytes at0x82E108, followed by sixteen zero bytes.
            char dotted[32] = "xxx.xxx.xxx.xxx";
            for (int i = 1; i < PlayerCount_00A8DA84; ++i) {
                unsigned char network[4], node[6];
                Players_00A8DA78[i]->Address.GetAddress(network, node);
                sprintf(dotted, STR_0083D9FC, node[0], node[1], node[2], node[3]);
                FUN_004068E0(STR_0083D9DC, dotted);
                Interface_00887628->AddBroadcastAddress(dotted, Ports_00A8E2B2[i]);
            }
        }
    }
    bool read;
    if (ScenarioInstance->unknown_34BD) {
        // Binary0x58B740 ->0x595740 ->0x595680 establishes MapSeedClass at+0;
        // this cast asserts only that known prefix, not the full global layout.
        read = reinterpret_cast<MapSeedClass*>(DAT_00ABDFD8)->FUN_00597A10(scenario);
        if (read) {
            reinterpret_cast<MapSeedClass*>(DAT_00ABDFD8)->FUN_00598960(0, 0);
            FUN_00686890(true);
        }
        strcpy(ScenarioInstance->unknown_125C, scenario);
    } else read = FUN_00686730(scenario);
    if (!RulesInstance->unknown_14AE) MapInstance.FUN_00577F30(0);
    if (!read) {
        FUN_004068E0(STR_0083D9B4, scenario);
        FUN_004A3C30(&DAT_00885780, 7, FUN_0048D080);
        Dialog_005D3490 dialog;
        dialog.FUN_005D3490(FUN_00734E60(STR_00831AF0, 0, STR_0083D838, 0x50D),
            FUN_00734E60(STR_00825FB0, 0, STR_0083D838, 0x50D), 0, 0, 0);
        --DAT_00A8E7AC;
        ScenarioInstance->unknown_3598 = false;
        if (manager) {
            DAT_00AC4F58.FUN_00643E80(0);
            FUN_00552AA0();
        }
        return false;
    }
    // Reuse existing MessageListClass view for global0xA8BC60.
    ScenarioMessageList_00A8BC60.Init(DAT_00886FA0.X + 3, DAT_00886FA0.Y, 6, 0x62, 0xE,
        -1, -1, false, 0x14, 0x62, DAT_00886FA0.Width - 6);
    FUN_00684C30();
    if (Session_00A8B238.GameMode == 3 || Session_00A8B238.GameMode == 4) {
        Session_00A8B238.FUN_0069AE90(99);
        if (Session_00A8B238.GameMode == 4 && Flag_00A8DBA0)
            IdMap_00B052D0.FUN_00664610(15000, 1);
    }
    Session_00A8B238.FUN_0069AE90(ScenarioInstance->unknown_34BD ? 200 : 100);
    DAT_00A8B8C1 = false;
    DAT_00A8B8C2 = false;
    bool ready = FUN_00684370();
    if (Session_00A8B238.GameMode == 4) Session_00A8B238.FUN_0069B170();
    --DAT_00A8E7AC;
    if (!DAT_00A8ED6B && ready) {
        FUN_0048D080();
        while (DAT_00AC4F58.FUN_006433D0() < 1.0)
            for (int i = 0; i < PlayerCount_00A8DA84; ++i)
                DAT_00AC4F58.FUN_00643C50(i, 100.0, -1, -1);
    }
    ScenarioInstance->unknown_3598 = false;
    DAT_00AC4F58.FUN_00642AD0();
    if (manager) {
        DAT_00AC4F58.FUN_00643E80(0);
        manager->FUN_00554370();
    }
    for (int i = HouseClass_ArrayCount - 1; i >= 0; --i)
        HouseClass_ArrayItems[i]->FUN_0050D610();
    return true;
}

// FUNCTION: GAMEMD 0x684C30
void __fastcall FUN_00684C30()
{
    ++DAT_00A8E7AC;
    for (int i = 0; i < DAT_00A8EB40.Count; ++i) DAT_00A8EB40.Items[i]->vf_312();
    MapInstance.FUN_004F42F0(2);
    if (!DAT_00A8ED6B) {
        MapInstance.FUN_006D04F0(1);
        if (Session_00A8B238.GameMode == 0) {
            CellStruct cell = ScenarioInstance->Waypoints[DAT_008A38E0.CarryOverGlobals[0] ?
                ScenarioInstance->unknown_0210 : ScenarioInstance->unknown_020C];
            ScenarioInstance->unknown_349A = cell;
            ScenarioInstance->unknown_3496 = ScenarioInstance->unknown_349A;
            ScenarioInstance->unknown_3492 = ScenarioInstance->unknown_3496;
            ScenarioInstance->unknown_348E = ScenarioInstance->unknown_3492;
            CoordStruct coord;
            coord.X = cell.X * 256 + 128;
            coord.Y = cell.Y * 256 + 128;
            coord.Z = 0;
            coord.Z = MapInstance.FUN_00578080(&coord);
            MapInstance.FUN_00653F70(&coord);
        }
    }
    for (i = 0; i < TagTypes.Count; ++i) {
        TagTypeClass* type = TagTypes.Items[i];
        if (type->GetFlags() & 4) DAT_008B41A8.AddItem(TagClass::GetInstance(type));
        if (type->GetFlags() & 0x10) DAT_008B40C8.AddItem(TagClass::GetInstance(type));
        if (type->GetFlags() & 8) {
            TagClass* tag = TagClass::GetInstance(type);
            HouseClass* house = FUN_00502D30(tag->Type->FirstTrigger->House->ArrayIndex2);
            if (house) {
                // Native 0x684E67 selects this vector at House+0x38.
                reinterpret_cast<DynamicVectorClass<TagClass*>*>(&house->RelatedTags)->AddItem(tag);
            }
        }
    }
    --DAT_00A8E7AC;
    for (i = 0; i < TagTypes.Count; ++i) {
        TagTypeClass* type = TagTypes.Items[i];
        if (type->HasAllowWinAction())
            ++FUN_00502D30(type->FirstTrigger->House->ArrayIndex)->AllowWinBlocks;
    }
    if (ScenarioInstance->unknown_34B2) {
        for (i = 0; i < HouseClass_ArrayCount; ++i) {
            HouseClass* house = HouseClass_ArrayItems[i];
            if (house) {
                // Retail 0x684F2A/0x684F45 dispatches through IHouse at +0x24.
                int remaining = static_cast<IHouse*>(house)->vf_06();
                TiberiumClass* type = TiberiumArrayItems[0];
                while (remaining > type->Value && static_cast<IHouse*>(house)->vf_07() > 0) {
                    house->GiveTiberium(1.0f, 0);
                    remaining -= type->Value;
                }
            }
        }
    }
    MapInstance.FUN_004ADCD0(1, 0);
    FUN_0075F020();
    MapInstance.IteratorBegin_578350();
    CellClass* cell;
    while ((cell = MapInstance.IteratorNext_578290()) != 0) cell->FUN_0047D2B0(-1);
    MapInstance.FUN_0056D6E0();
    MapInstance.FUN_0056C510();
    MapInstance.FUN_00581F50();
    MapInstance.FUN_00586BF0();
    if (!DAT_00A8ED78) {
        ParticleCoord coord(0xA80, 0xA80, 0);
        int index = FUN_00644630(STR_0083DA90);
        DAT_00A8ED78 = new ParticleSystemClass(
            ((ParticleSystemTypeClass**)DAT_00A83D68.Items)[index], coord, 0, 0, DAT_00B05488, 0);
    }
    if (RulesInstance->unknown_1870) {
        MapInstance.IteratorBegin_578350();
        while ((cell = MapInstance.IteratorNext_578290()) != 0) {
            if (cell->FUN_00485020() &&
                ScenarioInstance->unknown_0218.RandomRanged(0, RulesInstance->unknown_186C - 1) == 0)
                new AnimClass(RulesInstance->unknown_1870, cell->vf_18(), 0, 1, 0x600, 0, false);
        }
    }
    FUN_0055AF40(RulesInstance->unknown_000);
    FUN_0055AF50(RulesInstance->unknown_008);
}

// FUNCTION: GAMEMD 0x685120
void __fastcall FUN_00685120()
{
    FUN_00465450();
    FUN_007236D0();
    FUN_0074D450(ScenarioInstance->unknown_1258);
    FUN_0071DCA0(ScenarioInstance->unknown_1258);
    FUN_006B5490(ScenarioInstance->unknown_1258);
    MapInstance.FUN_00655B20();
    if (DAT_00B0EA80.StartTime != -1) {
        DAT_00B0EA80.TimeLeft = FUN_00685120_TimeLeft(DAT_00B0EA80);
    }
    DAT_00B0EA80.StartTime = CurrentFrame;
    DAT_0087E8B8.FUN_0042AC00(&DAT_0087F8D4);
    FUN_0053AB50();
    FUN_004261D0();
    MapInstance.FUN_004F42F0(2);
    InvalidateRect(DAT_00B73550, 0, false);
    FUN_00734210();
    FUN_00734270(0);
    FUN_00660C50();
}

// FUNCTION: GAMEMD 0x6851F0
void __fastcall FUN_006851F0()
{
    ScenarioInstance->unknown_0214 = 1000000;
    ScenarioInstance->unknown_0218.unknown_00 = true;
    DAT_0083D834 = 0x4000;
    FUN_00407150(DAT_0087E758, 0x4000);
    FUN_00750FA0();
    CurrentPlayer = 0;
    ScenarioInstance->FUN_00683610();
    FUN_0053A090();
    for (int i = DAT_00A8E968.Count - 1; i >= 0; --i) {
        if (DAT_00A8E968.Items[i]->vf_rtti_3() == 0x12) DAT_00A8E968.Delete(i);
    }
    FUN_00534450();
    for (i = 0; i < DAT_00A8ED28.Count; ++i) {
        // The native type registry stores each tile object's offset-zero
        // AbstractTypeClass pointer; 0x685253/0x685256 confirms its +4 RTTI side.
        DAT_00A8E968.AddItem(reinterpret_cast<AbstractTypeClass*>(DAT_00A8ED28.Items[i]));
    }
    MapInstance.FUN_00565B00();
    DAT_0087F838.Clear();
    FUN_006E5570();
    for (i = 0; i < 50; ++i) {
        if (ScenarioInstance->unknown_1C88[i].unknown_28) {
            ScenarioInstance->unknown_1C88[i].unknown_28 = 0;
            ScenarioInstance->unknown_34AA = true;
            FUN_006E57F0(i);
        }
    }
    delete TacticalInstance;
    TacticalInstance = new Tactical;
    TacticalInstance->FUN_006DA980();
    DAT_00829AE4 = false;
    while (DAT_00A8E360.Count) {
        if (DAT_00A8E360.Items[0]->vf_11() == 8) DAT_00A8E360.Items[0]->Release();
        else delete DAT_00A8E360.Items[0];
    }
    DAT_00829AE4 = true;
    while (TagTypes.Count) delete TagTypes.Items[0];
    DAT_008B41A8.Clear();
    DAT_008B40C8.Clear();
    ScenarioInstance->unknown_35A4 = 3600;
    ScenarioInstance->unknown_35A8 = ScenarioInstance->unknown_35A4;
    ScenarioInstance->unknown_35AC = ScenarioInstance->unknown_35A4;
    ScenarioInstance->unknown_35B0 = 0;
    ScenarioInstance->unknown_35CF = 0;
    ScenarioInstance->unknown_35EE = 0;
    ScenarioInstance->unknown_360D = 0;
    FUN_005549A0();
    FUN_00539760();
    FUN_004C5470();
    FUN_0074D760();
    FUN_00722390();
    FUN_00722E50();
    DAT_0087F5D8.FUN_00439110();
    DAT_00ABC5F8.Clear();
    AircraftTracker.Clear();
    FUN_006370B0();
    DAT_0087F8D4 = 0;
    DAT_0087F8D8 = 0;
    DAT_0087F8DC = 0;
    DAT_0087F8E0 = 0;
    FUN_004068E0(STR_0083DAF8);
    MapInstance.FUN_005BDF50();
    FUN_004068E0(STR_0083DAE8);
    DAT_0087F778.Clear();
    FUN_004068E0(STR_0083DAD0);
    DAT_00A8ECB8.Clear();
    FUN_004068E0(STR_0083DAB0);
    for (i = 0; i < 702; ++i) ScenarioInstance->Waypoints[i] = WaypointUndefined;
    FUN_004068E0(STR_0083DA9C);
    FUN_0052CB90();
    if (DAT_00A8ED78) {
        DAT_00A8ED78->FUN_0062E650();
        delete DAT_00A8ED78;
        DAT_00A8ED78 = 0;
    }
    ScenarioInstance->unknown_0218.unknown_00 = false;
    FUN_00734210();
    FUN_00734270(0);
    FUN_00660C50();
    ScenarioInstance->unknown_0214 = 1000000;
}

// FUNCTION: GAMEMD 0x685670
void __fastcall FUN_00685670()
{
    if (Session_00A8B238.GameMode != 0 && Session_00A8B238.GameMode != 5 && !(DAT_00A8D5F8 & 2)) {
        FUN_00648350();
        FUN_0055CF10();
    }
    DAT_00A8ED5C = false;
    DAT_00A8E378 = false;
    ScenarioInstance->unknown_0614.Pause();
    FUN_005BF450();
    WWMouseClassInstance->DrawCachedOnto(DAT_0088730C, false);
    WWMouseClassInstance->vf_5();
    MapInstance.FUN_005BDA80(0, 0);
    WWMouseClassInstance->vf_3();
    FUN_00407070(DAT_0087E758);
    FUN_004070B0(DAT_0087E758);
    int deadline = ConnTimer.GetValue() + 300;
    while (FUN_007529E0()) {
        if (deadline <= ConnTimer.GetValue()) break;
        FUN_0048D080();
    }
    FUN_007529A0(true);
    FUN_00752CA0();
    FUN_00406E80();
    FUN_00750FA0();
    FUN_00407150(DAT_0087E758, 0x4000);
    if (DAT_00886FB8 != DAT_00A8EB8C && DAT_00886FBC != DAT_00A8EB90) {
        FUN_004068E0(STR_0083D924);
        FUN_00560BF0(DAT_00A8EB8C, DAT_00A8EB90);
    }
    if (Session_00A8B238.GameMode != 0) {
        bool resume = false;
        if (!(DAT_00A8D5F8 & 2)) {
            ++DAT_00A8D57C;
            if (Session_00A8B238.GameMode == 4)
                FUN_0078ABF0(true, FUN_00734E60(STR_0083DB0C, 0, STR_0083D838, 0x7E8));
            if (DAT_00A8B23C && (Session_00A8B238.GameMode == 3 || Session_00A8B238.GameMode == 4) && DAT_00A8B23C->vf_2())
                FUN_0052FEC0(0, 1);
            else {
                DAT_00A8D610 = 0;
                Obj_005C9700 score;
                score.FUN_005C9720();
            }
            if (DAT_00A8B23C) resume = DAT_00A8B23C->vf_42();
            ++DAT_00A8D588;
            if (DAT_00A8D588 > 3) DAT_00A8D588 = 3;
            if (resume) {
                DAT_00A8B23C->vf_43();
                FUN_0078ABF0(false, DAT_00887734);
            }
        }
        if (!resume) {
            DAT_00A8D610 = 0;
            if (DAT_00A8B23C) DAT_00A8B23C->vf_41(1);
            DAT_00A8E9A0 = false;
            FUN_0078ABF0(false, DAT_00887734);
            return;
        }
    }
    FUN_005BF260(ScenarioInstance->unknown_143C, -1, 1, 1, 1);
    if (!(DAT_00A8D5F8 & 2)) {
        DAT_0087F770->DoSomething();
        if (!ScenarioInstance->unknown_34AE) {
            Obj_006C8E70 score;
            score.FUN_006C8E70()->FUN_006C8E80();
        }
        if (ScenarioInstance->unknown_1448 != -1)
            FUN_005BF260(ScenarioInstance->unknown_1448, -1, 1, 1, 1);
        if (ScenarioInstance->unknown_144C != -1)
            FUN_005BF260(ScenarioInstance->unknown_144C, -1, 1, 1, 1);
        if (!CopyProtection::CheckProtectedData() || ScenarioInstance->unknown_34AF) {
            DAT_00A8E9A0 = false;
            WWMouseClassInstance->vf_4();
            return;
        }
        if (ScenarioInstance->unknown_34AC) {
            if (ScenarioInstance->unknown_34CC != -1)
                FUN_005BF260(CampaignArray.Items[ScenarioInstance->unknown_34CC]->FinalMovie, -1, 1, 1, 1);
            FUN_004C3E30();
            DAT_00A8E9A0 = false;
            WWMouseClassInstance->vf_4();
            return;
        }
        if (!(DAT_00A8B23C && (Session_00A8B238.GameMode == 3 || Session_00A8B238.GameMode == 4) && DAT_00A8B23C->vf_2())) {
            if (!ScenarioInstance->unknown_34B0) {
                WWMouseClassInstance->vf_4();
                FUN_005ADD10(ScenarioInstance);
                WWMouseClassInstance->vf_3();
            } else {
                if (ScenarioInstance->unknown_1C88[1].unknown_28)
                    FUN_005ADE20(ScenarioInstance, ScenarioInstance->unknown_0004 + 0x104);
                else
                    FUN_005ADE20(ScenarioInstance, ScenarioInstance->unknown_0004);
            }
        }
        DAT_0087F770->DoSomething();
    }
    WWMouseClassInstance->vf_4();
    DAT_008A38E0.FUN_004C6180();
    ++ScenarioInstance->unknown_1254;
    if (DAT_00A8B23C && (Session_00A8B238.GameMode == 3 || Session_00A8B238.GameMode == 4) && DAT_00A8B23C->vf_2()) {
        if (Session_00A8B238.GameMode == 3) {
            Interface_00887628->vf_1();
            delete Interface_00887628;
            Interface_00887628 = 0;
            Interface_00887628 = new IPXInterfaceClass;
        }
        Interface_00887628->StartupWinsock();
        int saved = DAT_00A8B274;
        char settings[4][32];
        memcpy(settings[0], DAT_00A8DA90, 32);
        memcpy(settings[1], DAT_00A8B2BC, 32);
        memcpy(settings[2], DAT_00A8B29C, 32);
        memcpy(settings[3], DAT_00A8B27C, 32);
        if (!FUN_005DB680()) {
            delete Interface_00887628;
            Interface_00887628 = 0;
            DAT_00A8E9A0 = false;
            return;
        }
        DAT_00A8B274 = saved;
        memcpy(DAT_00A8B27C, settings[3], 32);
        memcpy(DAT_00A8B29C, settings[2], 32);
        memcpy(DAT_00A8B2BC, settings[1], 32);
        memcpy(DAT_00A8DA90, settings[0], 32);
        DAT_0087F770->DoSomething();
    }
    DAT_00A8E9A0 = CopyProtection::CheckProtectedData();
    if (!DAT_00A8E9A0) {
        WWMouseClassInstance->vf_4();
        return;
    }
    while (!FUN_00683AB0(ScenarioInstance->unknown_125C, true, ScenarioInstance->unknown_34CC)) {}
    if (DAT_00A8B23C && (Session_00A8B238.GameMode == 3 || Session_00A8B238.GameMode == 4) && DAT_00A8B23C->vf_2()) {
        Session_00A8B238.FUN_00697B70();
        if (Session_00A8B238.GameMode == 3) {
            unsigned long delay;
            if (Manager_00A8E9C0.FUN_005424C0() + 2 < 15) delay = 15;
            else delay = Manager_00A8E9C0.FUN_005424C0() + 2;
            Manager_00A8E9C0.SetTiming(delay, -1, 600, true);
            if (Manager_00A8E9C0.FUN_005424C0() + 2 < 60) delay = 60;
            else delay = Manager_00A8E9C0.FUN_005424C0() + 2;
            Manager_00A8E9C0.vf_14(delay, -1, 600);
        } else if (Session_00A8B238.GameMode == 4 && !DAT_00A8B570) {
            unsigned long delay;
            if (Manager_00A8E9C0.FUN_005424C0() + 2 < 60) delay = 60;
            else delay = Manager_00A8E9C0.FUN_005424C0() + 2;
            Manager_00A8E9C0.SetTiming(delay, -1, 600, true);
        }
    }
    DAT_008A38E0.Do();
    if (DAT_00887368) DAT_00887368->SetState(DAT_00A8EB80);
    MapInstance.FUN_004F4480();
    FUN_004A3C30(&DAT_00885780, 7, FUN_0048D080);
}

// FUNCTION: GAMEMD 0x685DC0
void __fastcall FUN_00685DC0()
{
    if (Session_00A8B238.GameMode != 0 && Session_00A8B238.GameMode != 5 && !(DAT_00A8D5F8 & 2)) {
        FUN_00648350();
        FUN_0055CF10();
    }
    DAT_00A8ED5C = false;
    DAT_00A8E378 = false;
    ScenarioInstance->unknown_0614.Pause();
    FUN_005BF450();
    WWMouseClassInstance->DrawCachedOnto(DAT_0088730C, false);
    WWMouseClassInstance->vf_5();
    MapInstance.FUN_005BDA80(0, 0);
    WWMouseClassInstance->vf_3();
    if (DAT_00886FB8 != DAT_00A8EB8C && DAT_00886FBC != DAT_00A8EB90) {
        FUN_004068E0(STR_0083D924);
        FUN_00560BF0(DAT_00A8EB8C, DAT_00A8EB90);
    }
    FUN_00407070(DAT_0087E758);
    FUN_004070B0(DAT_0087E758);
    int deadline = ConnTimer.GetValue() + 300;
    while (FUN_007529E0()) {
        if (deadline <= ConnTimer.GetValue()) break;
        FUN_0048D080();
    }
    FUN_007529A0(true);
    FUN_00752CA0();
    FUN_00406E80();
    FUN_00750FA0();
    FUN_00407150(DAT_0087E758, 0x4000);
    bool resume = false;
    if (Session_00A8B238.GameMode != 0) {
        if (!(DAT_00A8D5F8 & 2)) {
            ++DAT_00A8D57C;
            if (Session_00A8B238.GameMode == 4)
                FUN_0078ABF0(true, FUN_00734E60(STR_0083DB0C, 0, STR_0083D838, 0x9BC));
            if (DAT_00A8B23C && (Session_00A8B238.GameMode == 3 || Session_00A8B238.GameMode == 4) && DAT_00A8B23C->vf_2())
                FUN_0052FEC0(0, 1);
            else {
                DAT_00A8D610 = 0;
                Obj_005C9700 score;
                score.FUN_005C9720();
            }
            if (DAT_00A8B23C) resume = DAT_00A8B23C->vf_42();
            ++DAT_00A8D588;
            if (DAT_00A8D588 > 3) DAT_00A8D588 = 3;
            if (resume) {
                DAT_00A8B23C->vf_43();
                FUN_0078ABF0(false, DAT_00887734);
            }
        }
        if (!resume) {
            DAT_00A8D610 = 0;
            if (DAT_00A8B23C) DAT_00A8B23C->vf_41(0);
            DAT_00A8E9A0 = false;
            FUN_0078ABF0(false, DAT_00887734);
            return;
        }
    }
    FUN_005BF260(ScenarioInstance->unknown_1440, -1, 1, 1, 1);
    FUN_0052FEC0(0, 1);
    bool proceed = resume;
    if (Session_00A8B238.GameMode == 0 && !(DAT_00A8D5F8 & 2)) {
        Dialog_005D3490 dialog;
        if (dialog.FUN_005D3490(
            FUN_00734E60(STR_0083DB24, 0, STR_0083D838, 0x9FF),
            FUN_00734E60(STR_00829F14, 0, STR_0083D838, 0x9FF),
            FUN_00734E60(STR_00829F1C, 0, STR_0083D838, 0x9FF), 0, 0) == 0)
            proceed = true;
    }
    if (!proceed) {
        DAT_00A8E9A0 = false;
        return;
    }
    if (Session_00A8B238.GameMode == 4)
        FUN_0078ABF0(true, FUN_00734E60(STR_008262F0, 0, STR_0083D838, 0xA06));
    if (DAT_00A8B23C && (Session_00A8B238.GameMode == 3 || Session_00A8B238.GameMode == 4) && DAT_00A8B23C->vf_2()) {
        if (Session_00A8B238.GameMode == 3) {
            Interface_00887628->vf_1();
            delete Interface_00887628;
            Interface_00887628 = 0;
            Interface_00887628 = new IPXInterfaceClass;
        }
        Interface_00887628->StartupWinsock();
        int saved = DAT_00A8B274;
        char settings[4][32];
        memcpy(settings[0], DAT_00A8DA90, 32);
        memcpy(settings[1], DAT_00A8B2BC, 32);
        memcpy(settings[2], DAT_00A8B29C, 32);
        memcpy(settings[3], DAT_00A8B27C, 32);
        if (!FUN_005DB680()) {
            delete Interface_00887628;
            Interface_00887628 = 0;
            DAT_00A8E9A0 = false;
            goto cleanupNotice;
        }
        DAT_00A8B274 = saved;
        memcpy(DAT_00A8B27C, settings[3], 32);
        memcpy(DAT_00A8B29C, settings[2], 32);
        memcpy(DAT_00A8B2BC, settings[1], 32);
        memcpy(DAT_00A8DA90, settings[0], 32);
        DAT_0087F770->DoSomething();
    }
    FUN_00683AB0(ScenarioInstance->unknown_125C, true, ScenarioInstance->unknown_34CC);
    if (DAT_00A8B23C && (Session_00A8B238.GameMode == 3 || Session_00A8B238.GameMode == 4) && DAT_00A8B23C->vf_2()) {
        Session_00A8B238.FUN_00697B70();
        if (Session_00A8B238.GameMode == 3) {
            unsigned long delay;
            if (Manager_00A8E9C0.FUN_005424C0() + 2 < 15) delay = 15;
            else delay = Manager_00A8E9C0.FUN_005424C0() + 2;
            Manager_00A8E9C0.SetTiming(delay, -1, 600, true);
            if (Manager_00A8E9C0.FUN_005424C0() + 2 < 60) delay = 60;
            else delay = Manager_00A8E9C0.FUN_005424C0() + 2;
            Manager_00A8E9C0.vf_14(delay, -1, 600);
        } else if (Session_00A8B238.GameMode == 4 && !DAT_00A8B570) {
            unsigned long delay;
            if (Manager_00A8E9C0.FUN_005424C0() + 2 < 60) delay = 60;
            else delay = Manager_00A8E9C0.FUN_005424C0() + 2;
            Manager_00A8E9C0.SetTiming(delay, -1, 600, true);
        }
    }
    DAT_008A38E0.Do();
    if (DAT_00887368) DAT_00887368->SetState(DAT_00A8EB80);
    MapInstance.FUN_004F4480();
cleanupNotice:
    if (Session_00A8B238.GameMode == 4) FUN_0078ABF0(false, DAT_00887734);
}


// FUNCTION: GAMEMD 0x6863E0
void __fastcall FUN_006863E0()
{
    FUN_0072DDB0();
    if (DAT_00886FB8 != DAT_00A8EB8C && DAT_00886FBC != DAT_00A8EB90) {
        FUN_004068E0(STR_0083D924);
        FUN_00560BF0(DAT_00A8EB8C, DAT_00A8EB90);
    }
    DAT_00A8ED5C = false;
    DAT_00A8E378 = false;
    if (DAT_00887368) DAT_00887368->SetState(false);
    ScenarioInstance->unknown_0614.Pause();
    FUN_005BF450();
    ScenarioElapsedTimer timer;
    timer = ScenarioElapsedTimer(60);
    DAT_00A83D10.Stop(true);
    FUN_00406E80();
    FUN_00750FA0();
    FUN_007529A0(true);
    FUN_00752CA0();
    MapInstance.FUN_005BDA80(0, 0);
    DAT_0087F770->DoSomething();
    FUN_00683AB0(ScenarioInstance->unknown_125C, false, ScenarioInstance->unknown_34CC);
    DAT_008A38E0.Do();
    while (timer.GetTimeLeft() > 0) FUN_0048D080();
    DAT_0087F770->DoSomething();
    if (DAT_00887368) DAT_00887368->SetState(DAT_00A8EB80);
    MapInstance.FUN_004F4480();
}

// FUNCTION: GAMEMD 0x686570
void __fastcall FUN_00686570()
{
    DAT_00A8ED5C = false;
    DAT_00A8E378 = false;
    ScenarioInstance->unknown_0614.Pause();
    ScenarioInstance->unknown_1254 = 1;
    FUN_005BF450();
    DAT_0087F770->DoSomething();
    WWMouseClassInstance->DrawCachedOnto(DAT_0088730C, false);
    WWMouseClassInstance->vf_5();
    MapInstance.FUN_005BDA80(0, 0);
    DAT_00A83D10.Stop(true);
    FUN_00407070(DAT_0087E758);
    VoxClass::Play(STR_0083DB34, 2, -1);
    FUN_004070B0(DAT_0087E758);
    int deadline = ConnTimer.GetValue() + 300;
    while (FUN_007529E0()) {
        if (deadline <= ConnTimer.GetValue()) break;
        FUN_0048D080();
    }
    FUN_007529A0(true);
    FUN_00752CA0();
    FUN_00406E80();
    FUN_00750FA0();
    FUN_00407150(DAT_0087E758, 0x4000);
    if (DAT_00886FB8 != DAT_00A8EB8C && DAT_00886FBC != DAT_00A8EB90) {
        FUN_004068E0(STR_0083D924);
        FUN_00560BF0(DAT_00A8EB8C, DAT_00A8EB90);
    }
    DAT_00A8E9A0 = 0;
}

// FUNCTION: GAMEMD 0x686700
void ScenarioClass::FUN_00686700(const char* text)
{
    if (text) {
        strncpy(unknown_125C, text, 260);
        unknown_125C[259] = 0;
    }
}

// FUNCTION: GAMEMD 0x686730
bool __fastcall FUN_00686730(const char* filename)
{
    if (!CD().FUN_004790E0(g_FileSearchMode)) return false;
    DAT_00A8ED84 = 0;
    CCINIClass ini;
    CCFileClass file(filename);
    FUN_004068E0(STR_0083DB6C, filename);
    if (!ini.ReadCCFile(&file, true, false)) {
        FUN_004068E0(STR_0083DB50);
        return false;
    }
    strcpy(ScenarioInstance->unknown_125C, filename);
    return FUN_00686B20(&ini, false);
}

// FUNCTION: GAMEMD 0x686890
void __fastcall FUN_00686890(bool value)
{
    if (PlayerCount_00A8DA84 + DAT_00A8B274 < RulesInstance->unknown_14D0 && !DAT_00A8ED6B) {
        for (int index = 0; index < HouseClass_ArrayCount; ++index) {
            HouseClass* house = HouseClass_ArrayItems[index];
            if (!house->IsHumanPlayer && !house->Type->MultiplayPassive && DAT_00A8B274 < 1)
                house->FUN_004FB920();
        }
    }
    FUN_0048D080();
    if (!DAT_00A8ED6B) {
        int saved = DAT_00A8E7AC;
        DAT_00A8E7AC = 0;
        if (DAT_00A8B23C) {
            DAT_00A8B23C->vf_33(value);
            DAT_00A8B23C->FUN_005D6D80();
        } else {
            FUN_006886B0(value);
        }
        DAT_00A8E7AC = saved;
    }
    Session_00A8B238.FUN_0069AE90(93);
    FUN_0048D080();
    if (DAT_00A8B261) {
        int count = RulesInstance->unknown_1470;
        if (count <= DAT_00A8B54C) count = DAT_00A8B54C;
        if (RulesInstance->unknown_1474 <= count) count = RulesInstance->unknown_1474;
        for (; count > 0; --count) MapInstance.FUN_0056BD40();
    }
    FUN_0048D080();
    MapInstance.FUN_004AC4F0();
    HouseClass* neutral = HouseClass::FindByCountryIndex(HouseTypeClass::FindIndexOfName(STR_00817318));
    for (int index = 0; index < HouseClass_ArrayCount; ++index) {
        HouseClass_ArrayItems[index]->Base.unknown_74 = HouseClass_ArrayItems[index];
        HouseClass* house = HouseClass_ArrayItems[index];
        if (!house->IsHumanPlayer && !house->Type->MultiplayPassive) {
            house->Unknown_Timer_5640 = CDTimerClass(RulesInstance->unknown_1178[house->AIDifficulty]);
            // 0x686A33..3C dereferences the known-live House then uses its
            // IHouse subobject at +0x24; reference conversion preserves that ABI.
            int money = static_cast<IHouse&>(*HouseClass_ArrayItems[index]).vf_06();
            house = HouseClass_ArrayItems[index];
            house->FUN_004F9950((int)(money * (RulesInstance->unknown_1308[house->AIDifficulty] * 0.01)));
        }
        if (HouseClass_ArrayItems[index]->Type->MultiplayPassive)
            HouseClass_ArrayItems[index]->Type->WallOwner = false;
        else
            HouseClass_ArrayItems[index]->Type->WallOwner = true;
        if (HouseClass_ArrayItems[index] != neutral) {
            HouseClass_ArrayItems[index]->FUN_004F9B70(neutral, false);
            neutral->FUN_004F9B70(HouseClass_ArrayItems[index], false);
        }
    }
    if (DAT_00A8B23C) {
        DAT_00A8B23C->vf_34();
        DAT_00A8B23C->vf_35();
    }
    FUN_0068C050();
    DAT_00A8D108 = 0x01010101;
    DAT_00A8D10C = 0x01010101;
}

// FUNCTION: GAMEMD 0x687CE0
void __fastcall FUN_00687CE0(const char* filename, bool flag)
{
    CCINIClass ini;
    if (DAT_00A8ED6B && CCFileClass(filename).Exists(false)) {
        CCFileClass input(filename);
        ini.ReadCCFile(&input, true, false);
    }
    ScenarioInstance->FUN_0068AD70(&ini, flag);
    if (flag) {
        if (DAT_00ABE154 && DAT_00ABE154->unknown_00) {
            DAT_00ABE154->FUN_006418B0(&ini);
        } else {
            SeatNull_006406E0 manager;
            manager.FUN_00641140();
            manager.FUN_006418B0(&ini);
        }
    } else FUN_00501160(&ini);
    MapInstance.FUN_004AD7E0(&ini);
    FUN_0071CB90(&ini);
    FUN_007436E0(&ini);
    FUN_0051FEF0(&ini);
    FUN_0041AF80(&ini);
    FUN_0044FE60(&ini);
    FUN_005FD6A0(&ini);
    FUN_006B4DD0(&ini);
    FUN_00728280(&ini);
    if (!flag || DAT_00A8ED6B) {
        FUN_00691B30(&ini, 0);
        FUN_006E8340(&ini, 0);
        FUN_006F1AB0(&ini, 0);
        FUN_0041F490(&ini, 0);
    }
    FUN_00727880(&ini);
    FUN_006E5FE0(&ini);
    RawFileClass output(filename);
    ini.WriteCCFile(&output, true);
}

// FUNCTION: GAMEMD 0x688380
DynamicVectorClass<Cell> __fastcall FUN_00688380(bool)
{
    DynamicVectorClass<Cell> points(0, 0);
    int defined = 0;
    for (int i = 0; i < 8; ++i) {
        if (i >= 702 || i < 0 ||
            (ScenarioInstance->Waypoints[i].X == WaypointUndefined.X &&
             ScenarioInstance->Waypoints[i].Y == WaypointUndefined.Y)) break;
        ++defined;
    }
    int spectators = 0;
    for (i = 0; i < PlayerCount_00A8DA84; ++i)
        if (Players_00A8DA78[i]->unknown_6B == -1) ++spectators;
    int count = PlayerCount_00A8DA84 - spectators + DAT_00A8B274;
    if (defined > count) count = defined;
    for (i = 0; i < count; ++i) {
        if (i < 702 && i >= 0 &&
            (ScenarioInstance->Waypoints[i].X != WaypointUndefined.X ||
             ScenarioInstance->Waypoints[i].Y != WaypointUndefined.Y)) {
            points.AddItem(Cell(ScenarioInstance->Waypoints[i].X,
                                ScenarioInstance->Waypoints[i].Y));
            CellStruct point = ScenarioInstance->Waypoints[i];
            FUN_004068E0(STR_0083DD20, point.X, point.Y);
        }
    }
    if (count > points.Count) {
        FUN_004068E0(STR_0083DCD4);
        while (points.Count < count) {
            int y = ScenarioInstance->unknown_0218.RandomRanged(0, DAT_0087F918 - 10);
            int x = ScenarioInstance->unknown_0218.RandomRanged(10, DAT_0087F914 - 10);
            Cell start(x + DAT_0087F90C, y + DAT_0087F910 + 10);
            Cell closeTo(0, 0);
            Cell point = MapInstance.FUN_0056DC20(start, 1, -1, 0, false, 8, 8,
                                                false, false, false, true,
                                                closeTo, false, false);
            if (point.X != WaypointUndefined.X || point.Y != WaypointUndefined.Y) {
                points.AddItem(point);
                FUN_004068E0(STR_0083DC9C, point.X, point.Y);
            }
        }
    }
    return points;
}

// FUNCTION: GAMEMD 0x6886B0
void __fastcall FUN_006886B0(bool value)
{
    DynamicVectorClass<TechnoClass*> created(0, 0);
    int number = DAT_00A8B270;
    if (DAT_00A8B258) --number;
    // Retail 0x688709..0x68871D passes the whole Randomizer by value.
    FUN_004068E0(STR_0083DDA8, number, ScenarioInstance->unknown_0218);
    FUN_004068E0(STR_0083DD94, ScenarioInstance->unknown_0214);
    int cost = 0;
    int types = 0;
    for (int i = 0; i < DAT_00A83CE0.Count; ++i) {
        UnitTypeClass* type = DAT_00A83CE0.Items[i];
        if (type->AllowedToStartInMultiplayer && RulesInstance->unknown_B20.FindItemIndex(type) < 0) {
            cost += type->vf_43();
            ++types;
        }
    }
    for (i = 0; i < DAT_00A8E348.Count; ++i) {
        InfantryTypeClass* type = DAT_00A8E348.Items[i];
        if (type->AllowedToStartInMultiplayer) {
            cost += type->vf_43();
            ++types;
        }
    }
    int budget = cost / types * number;
    DynamicVectorClass<Cell> starts = FUN_00688380(value);
    bool used[16] = { false };
    int assigned = 0;
    for (i = 0; i < HouseClass_ArrayCount; ++i) {
        HouseClass* house = HouseClass_ArrayItems[i];
        if (house->Type->MultiplayPassive) continue;
        FUN_004068E0(STR_0083DD70, i, house->Type->ID);
        DynamicVectorClass<UnitTypeClass*> units(0, 0);
        DynamicVectorClass<InfantryTypeClass*> infantry(0, 0);
        unsigned int owner = 1 << house->Type->ArrayIndex;
        for (int j = 0; j < DAT_00A83CE0.Count; ++j) {
            UnitTypeClass* type = DAT_00A83CE0.Items[j];
            if (type->AllowedToStartInMultiplayer && type->TechLevel <= house->TechLevel &&
                (type->OwnerFlags & owner) && RulesInstance->unknown_B20.FindItemIndex(type) < 0)
                units.AddItem(type);
        }
        for (j = 0; j < DAT_00A8E348.Count; ++j) {
            InfantryTypeClass* type = DAT_00A8E348.Items[j];
            if (type->AllowedToStartInMultiplayer && type->TechLevel <= house->TechLevel &&
                (type->OwnerFlags & owner)) infantry.AddItem(type);
        }
        Cell start;
        if (assigned == 0) {
            int index = ScenarioInstance->unknown_0218.RandomRanged(0, starts.Count - 1);
            used[index] = true;
            assigned = 1;
            start = starts.Items[index];
        } else {
            int distances[26] = { 0 };
            for (j = 0; j < starts.Count; ++j) {
                if (!used[j]) {
                    for (int k = 0; k < starts.Count; ++k) {
                        if (used[k]) {
                            double dy = (short)(starts.Items[j].Y - starts.Items[k].Y);
                            double dx = (short)(starts.Items[j].X - starts.Items[k].X);
                            distances[j] += (short)FUN_004CAC40(dy * dy + dx * dx);
                        }
                    }
                }
            }
            int index = 0;
            int farthest = 0;
            for (j = 0; j < starts.Count; ++j) {
                if (distances[j] > farthest || farthest == 0) {
                    farthest = distances[j];
                    index = j;
                }
            }
            ++assigned;
            used[index] = true;
            start = starts.Items[index];
        }
        house->FUN_0050E000(start);
        if (DAT_00A8B258) {
            ObjectClass* unit = new UnitClass(house->FUN_00505310(RulesInstance->unknown_B20), house);
            CoordStruct coord = { start.X * 256 + 128, start.Y * 256 + 128, 0 };
            if (!unit->vf_54(coord, 0) && !FUN_00688ED0(unit, &start, 1)) {
                delete unit;
            } else if (unit) {
                house->OurFlagCarrier = 0;
                house->OurFlagCoords = WaypointUndefined;
                if (ScenarioInstance->unknown_0000 & 0x10) house->FUN_004FC060(unit, true);
            }
        }
        created.Clear();
        int spent = 0;
        while (spent < budget) {
            TechnoTypeClass* type = 0;
            if (spent < budget * 2 / 3 && units.Count > 0)
                type = units.Items[ScenarioInstance->unknown_0218.RandomRanged(0, units.Count - 1)];
            else if (infantry.Count > 0)
                type = infantry.Items[ScenarioInstance->unknown_0218.RandomRanged(0, infantry.Count - 1)];
            // Slot35 returns the offset-zero ObjectClass of the constructed object.
            ObjectClass* object = static_cast<ObjectClass*>(type->vf_35(house));
            TechnoClass* techno = FUN_0040DD70(object);
            if (!FUN_00688ED0(object, &start, 4)) {
                delete object;
            } else {
                FUN_004068E0(STR_0083DD50, house->Type->ID, type->ID);
                spent += type->vf_43();
                created.AddItem(techno);
                if (ScenarioInstance->unknown_0000 & 0x200) FUN_007500B0(1);
                techno->vf_124(house->FUN_0050B730() ? 5 : 11);
            }
        }
    }
    FUN_004068E0(STR_00830990, ScenarioInstance->unknown_0218.RandomRanged(0, 0xFFFF));
}

// FUNCTION: GAMEMD 0x688ED0
int __fastcall FUN_00688ED0(ObjectClass* object, const CellStruct* cell, int distance)
{
    if (MapInstance.FUN_00578460(cell, 1)) {
        Point2D offset(0, 0);
        ObjectClass* occupied = MapInstance.FUN_005657A0(cell)->FindTechnoNearestTo(&offset, false, 0);
        if (!occupied || (occupied->vf_11() == 15 && object->vf_11() == 15)) {
            CoordStruct height = { cell->X * 256 + 128, cell->Y * 256 + 128, 0 };
            int z = MapInstance.FUN_00578080(&height);
            CoordStruct where = { cell->X * 256 + 128, cell->Y * 256 + 128, z };
            if (object->vf_54(where, 0)) return 1;
        }
    }
    while (distance < 32) {
        int direction = ScenarioInstance->unknown_0218.RandomRanged(0, 7);
        for (int pass = 0; pass < 2; ++pass) {
            for (int attempt = 0; attempt < 8; ++attempt) {
                int x = cell->X;
                int y = cell->Y;
                int maxX = DAT_0087F90C - 1 + DAT_0087F914;
                int maxY = DAT_0087F910 - 1 + DAT_0087F918;
                switch (direction) {
                case 0: y -= distance; break;
                case 1: x += distance; y -= distance; break;
                case 2: x += distance; break;
                case 3: x += distance; y += distance; break;
                case 4: y += distance; break;
                case 5: x -= distance; y += distance; break;
                case 6: x -= distance; break;
                case 7: x -= distance; y -= distance; break;
                }
                if (x > maxX) x = maxX;
                if (x < DAT_0087F90C) x = DAT_0087F90C;
                if (y > maxY) y = maxY;
                if (y < DAT_0087F910) y = DAT_0087F910;
                CellStruct candidate = { (short)x, (short)y };
                if (pass > 0) {
                    int delta = ScenarioInstance->unknown_0218.RandomRanged(0, 1);
                    if (ScenarioInstance->unknown_0218.RandomRanged(0, 99) < 50) {
                        x = candidate.X + delta;
                        if (x > maxX) x = maxX;
                    } else {
                        x = candidate.X - delta;
                        if (x < DAT_0087F90C) x = DAT_0087F90C;
                    }
                    delta = ScenarioInstance->unknown_0218.RandomRanged(0, 1);
                    if (ScenarioInstance->unknown_0218.RandomRanged(0, 99) < 50) {
                        y = candidate.Y + delta;
                        if (y > maxY) y = maxY;
                    } else {
                        y = candidate.Y - delta;
                        if (y < DAT_0087F910) y = DAT_0087F910;
                    }
                    candidate.X = (short)x;
                    candidate.Y = (short)y;
                }
                bool same = candidate.X == cell->X && candidate.Y == cell->Y;
                if (MapInstance.FUN_00578460(&candidate, 1) && !same) {
                    Point2D offset(0, 0);
                    ObjectClass* occupied = MapInstance.FUN_005657A0(&candidate)->FindTechnoNearestTo(&offset, false, 0);
                    if (!occupied || (occupied->vf_11() == 15 && object->vf_11() == 15)) {
                        CoordStruct height;
                        height.FUN_0041C230(candidate.X * 256 + 128, candidate.Y * 256 + 128, 0);
                        int z = MapInstance.FUN_00578080(&height);
                        CoordStruct where;
                        where.FUN_0041C230(candidate.X * 256 + 128, candidate.Y * 256 + 128, z);
                        if (object->vf_54(where, 0)) return 1;
                    }
                }
                ++direction;
                if (direction > 7) direction = 0;
            }
        }
        ++distance;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x689310
void ScenarioClass::FUN_00689310(Gg_IStream* const stream)
{
    int count;
    FUN_004068E0(STR_0083DDD4, unknown_0614);
    bool paused = unknown_0614.unknown_00 == -1;
    if (!paused) unknown_0614.Pause();
    stream->Write(this, 0x3740, 0);
    count = unknown_34D4.Count;
    stream->Write(&count, 4, 0);
    for (int i = 0; i < count; ++i) stream->Write(&unknown_34D4.Items[i], 4, 0);
    count = unknown_34F0.Count;
    stream->Write(&count, 4, 0);
    for (i = 0; i < count; ++i) stream->Write(&unknown_34F0.Items[i], 4, 0);
    count = unknown_350C.Count;
    stream->Write(&count, 4, 0);
    for (i = 0; i < count; ++i) stream->Write(&unknown_350C.Items[i], 4, 0);
    if (!paused) unknown_0614.Resume();
}

// FUNCTION: GAMEMD 0x689470
void ScenarioClass::FUN_00689470(Gg_IStream* const stream)
{
    unknown_0614.Pause();
    stream->Read(this, 0x3740, 0);
    new(this) ScenarioClass(AbstractNoInit());
    new(&unknown_34D4) TypeList<TechnoTypeClass*>;
    int count;
    stream->Read(&count, 4, 0);
    for (int i = 0; i < count; ++i) {
        TechnoTypeClass* item;
        stream->Read(&item, 4, 0);
        unknown_34D4.AddItem(item);
    }
    new(&unknown_34F0) TypeList<int>;
    stream->Read(&count, 4, 0);
    for (i = 0; i < count; ++i) {
        int item;
        stream->Read(&item, 4, 0);
        unknown_34F0.AddItem(item);
    }
    new(&unknown_350C) TypeList<int>;
    stream->Read(&count, 4, 0);
    for (i = 0; i < count; ++i) {
        int item;
        stream->Read(&item, 4, 0);
        unknown_350C.AddItem(item);
    }
    for (i = 0; i < unknown_34D4.Count; ++i) {
        // Canonical vf_4 still spells its pointer-sized argument as int.
        // 0x6895E4..0x6895ED passes this exact element address on the stack.
        DAT_00B0C110.SwizzleManagerClass::vf_4((int)&unknown_34D4.Items[i]);
    }
    if (unknown_11F8.unknown_00[0])
        unknown_11F4 = FUN_00734E60(unknown_11F8.unknown_00, false, STR_0083D838, 0x19D0);
    else unknown_11F4 = EmptyName_00887734;
    unknown_0614.Resume();
    FUN_004068E0(STR_0083DDF8, unknown_0614);
}

// FUNCTION: GAMEMD 0x689670
unsigned char ScenarioClass::FUN_00689670(unsigned int index, unsigned char value)
{
    if (index < 50) {
        unsigned char previous = unknown_1C88[index].unknown_28;
        if (previous != value) {
            unknown_1C88[index].unknown_28 = value;
            unknown_34AA = true;
            FUN_006E57F0(index);
        }
        return previous;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6896C0
unsigned char ScenarioClass::FUN_006896C0(const char* text, unsigned char value)
{
    unsigned int index = -1;
    for (int i = 0; i < 50; ++i) {
        if (strcmp(text, unknown_1C88[i].unknown_00) == 0) { index = i; break; }
    }
    if (index != -1) {
        if (index < 50) {
            unsigned char previous = unknown_1C88[index].unknown_28;
            if (previous != value) {
                unknown_1C88[index].unknown_28 = value;
                unknown_34AA = true;
                FUN_006E57F0(index);
            }
            return previous;
        }
        return 0;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x689760
bool ScenarioClass::FUN_00689760(int index, unsigned char* value)
{
    if (index < 0 || index >= 50) return false;
    *value = unknown_1C88[index].unknown_28;
    return true;
}

// FUNCTION: GAMEMD 0x689790
bool ScenarioClass::FUN_00689790(const char* text, unsigned char* value)
{
    int index = -1;
    for (int i = 0; i < 50; ++i) {
        if (strcmp(text, unknown_1C88[i].unknown_00) == 0) { index = i; break; }
    }
    if (index != -1 && index >= 0 && index < 50) {
        *value = unknown_1C88[index].unknown_28;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x689820
int ScenarioClass::FUN_00689820(const char* text)
{
    for (int i = 0; i < 50; ++i) {
        if (strcmp(text, unknown_1C88[i].unknown_00) == 0) return i;
    }
    return -1;
}

// FUNCTION: GAMEMD 0x689880
bool ScenarioClass::FUN_00689880(INIClass* ini)
{
    int count = ini->GetKeyCount(STR_0083D824) < 50 ? ini->GetKeyCount(STR_0083D824) : 50;
    for (int i = 0; i < count; ++i) {
        const char* key = ini->GetKeyName(STR_0083D824, i);
        int index = atoi(key);
        ini->FUN_00528A10(STR_0083D824, key, 0, unknown_1C88[index].unknown_00, 40);
    }
    return true;
}

// FUNCTION: GAMEMD 0x689910
unsigned char ScenarioClass::FUN_00689910(unsigned int index, unsigned char value)
{
    if (index < 100) {
        unsigned char previous = unknown_248A[index].unknown_28;
        if (previous != value) {
            unknown_248A[index].unknown_28 = value;
            unknown_34AA = true;
            FUN_006E5820(index);
        }
        return previous;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x689960
unsigned char ScenarioClass::FUN_00689960(const char* text, unsigned char value)
{
    unsigned int index = -1;
    for (int i = 0; i < 100; ++i) {
        if (strcmp(text, unknown_248A[i].unknown_00) == 0) { index = i; break; }
    }
    if (index != -1) {
        if (index < 100) {
            unsigned char previous = unknown_248A[index].unknown_28;
            if (previous != value) {
                unknown_248A[index].unknown_28 = value;
                unknown_34AA = true;
                FUN_006E5820(index);
            }
            return previous;
        }
        return 0;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x689A00
bool ScenarioClass::FUN_00689A00(int index, unsigned char* value)
{
    if (index < 0 || index >= 100) return false;
    *value = unknown_248A[index].unknown_28;
    return true;
}

// FUNCTION: GAMEMD 0x689A30
bool ScenarioClass::FUN_00689A30(const char* text, unsigned char* value)
{
    int index = -1;
    for (int i = 0; i < 100; ++i) {
        if (strcmp(text, unknown_248A[i].unknown_00) == 0) { index = i; break; }
    }
    if (index != -1 && index >= 0 && index < 100) {
        *value = unknown_248A[index].unknown_28;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x689AC0
int ScenarioClass::FUN_00689AC0(const char* text)
{
    for (int i = 0; i < 100; ++i) {
        if (strcmp(text, unknown_248A[i].unknown_00) == 0) return i;
    }
    return -1;
}

// FUNCTION: GAMEMD 0x689B20
bool ScenarioClass::FUN_00689B20(INIClass* ini)
{
    for (int i = 0; i < 100; ++i) unknown_248A[i].unknown_00[0] = 0;
    int count = ini->GetKeyCount(STR_0083D824) < 100 ? ini->GetKeyCount(STR_0083D824) : 100;
    for (int entry = 0; entry < count; ++entry) {
        const char* key = ini->GetKeyName(STR_0083D824, entry);
        int index = atoi(key);
        char buffer[128];
        ini->FUN_00528A10(STR_0083D824, key, 0, buffer, 128);
        char* token = strtok(buffer, STR_00817F70);
        strcpy(unknown_248A[index].unknown_00, token);
        token = strtok(0, STR_00817F70);
        if (token) unknown_248A[index].unknown_28 = atoi(token) != 0;
    }
    return true;
}

// FUNCTION: GAMEMD 0x689C60
bool ScenarioClass::FUN_00689C60(INIClass* ini)
{
    ini->Clear(DAT_007F0E48, 0);
    for (int i = 0; i < 100; ++i) {
        if (unknown_248A[i].unknown_00[0]) {
            char key[12];
            char value[128];
            wsprintfA(key, STR_00817F6C, i);
            wsprintfA(value, STR_0083DE1C, unknown_248A[i].unknown_00,
                       unknown_248A[i].unknown_28 != 0);
            ini->WriteString(DAT_007F0E48, key, value);
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x689CF0
int ScenarioClass::FUN_00689CF0()
{
    int count = 0;
    for (int i = 0; i < 100; ++i) {
        if (unknown_248A[i].unknown_00[0]) ++count;
    }
    return count;
}

// FUNCTION: GAMEMD 0x689D10
int ScenarioClass::FUN_00689D10()
{
    for (int i = 0; i < 100; ++i) {
        if (!unknown_248A[i].unknown_00[0]) return i;
    }
    return -1;
}

// FUNCTION: GAMEMD 0x689D30
//
// Read the scenario header's start position, map size and starting-point
// counts, then the numbered waypoints that hold the multiplayer start
// cells. Every field keeps its current value as the INI default, and the
// waypoint table is cleared first so an absent entry reads back as zero.
//
// PARTIAL (94.0%, 94/100 by position; multiset identical; was 8.0%). Two
// levers took it from 8.0%: the clear loop assigns a constructed two-int cell
// (`*clear = Cell(0, 0)`) instead of storing two named zero locals, which is
// what gives retail's two separate zero registers filled in the prologue and
// the plain `TEST ECX,ECX` count test; and the waypoint loop is a counted `for`
// whose key uses `i + 1`, so the increment folds onto the key's `LEA`
// (`MOV EAX,EBX`). What is left is the order inside the loop tail: retail loads
// both halves of the returned cell, stores both, then re-reads the count and
// advances the cursor (`MOV ECX,[EAX]; MOV EAX,[EAX+4]; MOV [EDI],ECX;
// MOV [EDI+4],EAX; ... ADD EDI,8`), where cl stores the first half, advances
// the cursor and stores the second half at `[EDI-4]`. Tried: cursor advance
// before/after the index bump, an indexed `Waypoints[i]` target, a POD cell
// with an inline maker (same 94.0%), a named copy of the returned cell, a
// member-wise copy and a const reference to the returned cell (82.2%).
bool Scenario_00689D30::ReadStartPoints(CCINI_00689D30* ini)
{
    Cell_00689D30* slot = Waypoints;

    StartX = -1;
    StartY = -1;
    Width = -1;
    Height = -1;
    NumberStartingPoints = -1;

    Cell_00689D30* clear = slot;
    for (int n = 8; n != 0; n--) {
        *clear = Cell_00689D30(0, 0);
        clear++;
    }

    StartX = ini->ReadInteger(STR_0083DE68, STR_0083DE70, StartX);
    StartY = ini->ReadInteger(STR_0083DE68, STR_0083DE60, StartY);
    Width = ini->ReadInteger(STR_0083DE68, STR_0082BBE4, Width);
    Height = ini->ReadInteger(STR_0083DE68, STR_0081A7A8, Height);
    NumberStartingPoints =
        ini->ReadInteger(STR_0083DE68, STR_0083DE48, NumberStartingPoints);
    NumCoopHumanStartSpots =
        ini->ReadInteger(STR_0083DE68, STR_0083DE30, NumCoopHumanStartSpots);

    for (int i = 0; i < NumberStartingPoints; i++) {
        char key[12];
        gg_sprintf(key, STR_0083DE24, i + 1);
        *slot = ini->ReadWaypoint(STR_0083DE68, key, *slot);
        slot++;
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.

// FUNCTION: GAMEMD 0x68B8A0
int __fastcall FUN_0068B8A0(int value)
{
    int frequency = 0;
    int code;
    char flag;
    FUN_004E6150(&code, &flag, 0, 0);
    if (code > 5) value = int(value * DAT_007F0E50);
    unsigned int high;
    unsigned int low = FUN_005CAF70(&high);
    if (low || high) {
        frequency = int((double(high) * DAT_007E51F8 + double(low)) * DAT_007EF918);
    }
    return int(value * DAT_007F0E58 / frequency);
}

// FUNCTION: GAMEMD 0x0068BCB0
int FUN_0068BCB0(Obj_0068BCB0* self)
{
    return ++self->unknown_214;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x68B940
void ScenarioClass::FUN_0068B940(Obj_004A1D30* crc)
{
    crc->FUN_004A1DB0(unknown_13BA);
    crc->FUN_004A1D50(unknown_1434);
    crc->FUN_004A1D50(unknown_1438);
    crc->FUN_004A1D50(unknown_143C);
    crc->FUN_004A1D50(unknown_1440);
    crc->FUN_004A1D50(unknown_1444);
    crc->FUN_004A1D50(unknown_1448);
    crc->FUN_004A1D50(unknown_144C);
    crc->FUN_004A1D50(unknown_1C74);
    crc->FUN_004A1D50(unknown_1C84);
    crc->FUN_004A1D50(unknown_1C70);
    crc->FUN_004A1D90(unknown_1C78);
    crc->FUN_004A1CA0(unknown_34BC);
    crc->FUN_004A1CA0(unknown_34AD);
    crc->FUN_004A1D50(unknown_1C80 / 100);
    crc->FUN_004A1D50(unknown_34A0);
    crc->FUN_004A1CA0(unknown_34AC);
    crc->FUN_004A1D50(unknown_34CC);
    crc->FUN_004A1CA0(unknown_34AE);
    crc->FUN_004A1CA0(unknown_34AF);
    crc->FUN_004A1CA0(unknown_34B0);
    crc->FUN_004A1CA0(unknown_34B2);
    crc->FUN_004A1CA0(unknown_34B4);
    crc->FUN_004A1CA0(unknown_34B1);
    crc->FUN_004A1D50(unknown_1C84);
    crc->FUN_004A1D50(unknown_34D0);
    crc->FUN_004A1D50(Timer_11E8.GetTimeLeft());
    crc->FUN_004A1D50(unknown_1218.GetTimeLeft());
    crc->FUN_004A1D50(unknown_1224.GetTimeLeft());
    crc->FUN_004A1D50(unknown_1230.GetTimeLeft());
    crc->FUN_004A1D50(unknown_123C.GetTimeLeft());
    int elapsed = unknown_0614.unknown_08;
    if (unknown_0614.unknown_00 != -1)
        elapsed += unknown_0614.unknown_04.GetTime() - unknown_0614.unknown_00;
    crc->FUN_004A1D50(elapsed);
    crc->FUN_004A1D50(Difficulty);
    crc->FUN_004A1D50(unknown_0610);
    crc->FUN_004A1D50(unknown_1258);
    crc->FUN_004A1D50(unknown_3540);
    crc->FUN_004A1D50(unknown_3544);
    crc->FUN_004A1CA0(unknown_34A4);
    crc->FUN_004A1D50(unknown_3548);
    crc->FUN_004A1D50(unknown_354C);
    crc->FUN_004A1D50(unknown_3550);
    crc->FUN_004A1D50(unknown_3554);
    crc->FUN_004A1D50(unknown_3558);
    crc->FUN_004A1D50(unknown_355C);
    crc->FUN_004A1D50(unknown_3528);
    crc->FUN_004A1D50(unknown_352C);
    crc->FUN_004A1D50(unknown_3530);
}

// FUNCTION: GAMEMD 0x68BCC0  ScenarioClass::GetWaypointCoords (__thiscall, ret 0x8)
// Returns the 4-byte CellStruct by value, so retail's RET 0x8 covers the hidden
// return-buffer pointer plus the index. No bounds check — callers are expected
// to have asked IsDefinedWaypoint first.
CellStruct ScenarioClass::GetWaypointCoords(int idx)
{
    return Waypoints[idx];
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x68BCE0
CellClass* ScenarioClass::FUN_0068BCE0(int index)
{
    return MapInstance.FUN_005657A0(&Waypoints[index]);
}

// FUNCTION: GAMEMD 0x68BD00
CoordStruct ScenarioClass::FUN_0068BD00(int index)
{
    CellClass* cell = MapInstance.FUN_005657A0(&Waypoints[index]);
    CoordStruct result = cell->vf_18();
    if (cell->Flags & 0x500) result.Z += DAT_00B054BC;
    return result;
}

// FUNCTION: GAMEMD 0x68BD60
void ScenarioClass::FUN_0068BD60()
{
    for (int i = 0; i < 702; ++i) Waypoints[i] = WaypointUndefined;
}

// FUNCTION: GAMEMD 0x68BD80  (__thiscall)
// True iff waypoint `idx` is in range [0..701] and its stored cell differs from
// the sentinel "undefined" cell. The first mismatching coordinate short-circuits
// to true; an exact match (both X and Y equal the sentinel) is "not defined".
bool ScenarioClass::IsDefinedWaypoint(int idx)
{
    if (idx < 702 && idx >= 0 &&
        (Waypoints[idx].X != WaypointUndefined.X ||
         Waypoints[idx].Y != WaypointUndefined.Y))
    {
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.


// FUNCTION: GAMEMD 0x68BDC0
void ScenarioClass::FUN_0068BDC0(INIClass* ini)
{
    for (int i = 0; i < 702; ++i) {
        char key[20];
        wsprintfA(key, STR_00817F6C, i);
        int value = ini->FUN_005276D0(STR_0082DB0C, key, 0);
        if (!value) Waypoints[i] = WaypointUndefined;
        else {
            CellStruct cell;
            cell.X = value % 1000;
            cell.Y = value / 1000;
            Waypoints[i] = cell;
        }
        if (i < 702 && i >= 0 &&
            (Waypoints[i].X != WaypointUndefined.X || Waypoints[i].Y != WaypointUndefined.Y)) {
            MapInstance.FUN_005657A0(&Waypoints[i])->Flags |= 4;
        }
    }

}

// FUNCTION: GAMEMD 0x68BE90
void ScenarioClass::FUN_0068BE90(INIClass* ini)
{
    ini->Clear(DAT_007F0E60, 0);
    for (int i = 0; i < 702; ++i) {
        if (Waypoints[i].X != WaypointUndefined.X || Waypoints[i].Y != WaypointUndefined.Y) {
            char key[32];
            wsprintfA(key, STR_00817F6C, i);
            ini->WriteInteger(DAT_007F0E60, key, Waypoints[i].Y * 1000 + Waypoints[i].X, 0);
        }
    }

}

// FUNCTION: GAMEMD 0x68BF30
void ScenarioClass::FUN_0068BF30(int index)
{
    Waypoints[index] = WaypointUndefined;
}

// FUNCTION: GAMEMD 0x68BF50
void ScenarioClass::FUN_0068BF50(int index, CellStruct value)
{
    Waypoints[index] = value;
}

// FUNCTION: GAMEMD 0x68BF70
CellClass* ScenarioClass::FUN_0068BF70(int index)
{
    return MapInstance.FUN_005657A0(&Waypoints[index]);
}

// FUNCTION: GAMEMD 0x68BF90
const char* ScenarioClass::FUN_0068BF90()
{
    int i = 0;
    for (CellStruct* cell = Waypoints; i < 702; ++i, ++cell) {
        if (!(i < 702 && i >= 0 &&
            (cell->X != WaypointUndefined.X || cell->Y != WaypointUndefined.Y))) {
            return FUN_00763610(i);
        }
    }
    return STR_00889F64;
}

// FUNCTION: GAMEMD 0x68BFE0
int __fastcall FUN_0068BFE0()
{
    int result = 0;
    if (!DAT_00A8B238) {
        int index = ScenarioInstance->unknown_34CC;
        if (index != -1) result = CampaignArray.Items[index]->idxCD;
    } else {
        int index = Players_00A8DA78[0]->unknown_4B;
        if (index == -3) index = 0;
        result = DAT_00A83C9C[index]->SideIndex;
    }
    return result;
}

// FUNCTION: GAMEMD 0x0068C030
// Entry `index` of the sixteen at +0x1180, or -1 out of range.
int Obj_0068C030::FUN_0068C030(int index) const
{
    if (index >= 0 && index < 16) {
        return unknown_1180[index];
    }
    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x68c2b0
// VectorClass<Cell>::operator=
template<> VectorClass<Cell>& VectorClass<Cell>::operator=(const VectorClass<Cell>& other)
{
    if (this != &other) {
        Clear();
        Capacity = other.Capacity;
        if (Capacity) {
            Items = new Cell[Capacity];
            if (Items) {
                IsAllocated = true;
                for (int i = 0; i < Capacity; ++i) Items[i] = other.Items[i];
            }
        } else {
            Items = 0;
            IsAllocated = false;
        }
    }
    return *this;
}

// LIBRARY: GAMEMD 0x7D5408
// ?FUN_007D5408@@YAPADPBD@Z
char* __cdecl FUN_007D5408(const char* name);
// GLOBAL: GAMEMD 0x0083E1AC
// Byte table passed to 0x68C3B0; the observed prefix contains 0x01 bytes.
extern const unsigned char DAT_0083E1AC[];
// GLOBAL: GAMEMD 0x00887308
extern void* DAT_00887308;
// FUNCTION: GAMEMD 0x68C3B0 (decl; reloc)
// ?FUN_0068C3B0@@YIPAXPBXPAUPaletteClass@@1PAX2HHHHPBE@Z
void* __fastcall FUN_0068C3B0(const void* hsv, PaletteClass* pal1, PaletteClass* pal2,
                            void* palette, void* surface, int shade,
                            int a, int b, int c, const unsigned char* table);

struct ScenarioHSVRecord
{
    unsigned char unknown_00, unknown_01, unknown_02;
    ColorStruct_0072ADE0 FUN_00517440(); // GAMEMD 0x517440, aggregate return
};
GG_STATIC_ASSERT(offsetof(ScenarioHSVRecord, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(ScenarioHSVRecord, unknown_01) == 1);
GG_STATIC_ASSERT(offsetof(ScenarioHSVRecord, unknown_02) == 2);
GG_STATIC_ASSERT(sizeof(ScenarioHSVRecord) == 3);

// LIBRARY: GAMEMD 0x4CACB0
// _FUN_004CACB0
extern "C" double __cdecl FUN_004CACB0(double);
// LIBRARY: GAMEMD 0x4CAD00
// _FUN_004CAD00
extern "C" double __cdecl FUN_004CAD00(double);
// GLOBAL: GAMEMD 0x007F0E98
extern const double DAT_007F0E98;
// GLOBAL: GAMEMD 0x007F0E90
extern const double DAT_007F0E90;
// GLOBAL: GAMEMD 0x007F0E88
extern const double DAT_007F0E88;
// GLOBAL: GAMEMD 0x007F0E80
extern const double DAT_007F0E80;

// Allocation size and nine stack arguments observed at 0x68C4AD/0x68C4E2.
struct ScenarioConvert_00555DA0
{
    char unknown_000[0x1B4];
    ScenarioConvert_00555DA0* FUN_00555DA0(void* palette, PaletteClass* second,
        void* surface, int a, int b, int c, int zero,
        const unsigned char* table, int shade); // GAMEMD 0x555DA0
};
GG_STATIC_ASSERT(sizeof(ScenarioConvert_00555DA0) == 0x1B4);

// FUNCTION: GAMEMD 0x68C050
void __fastcall FUN_0068C050()
{
    void* selected = 0;
    if (DAT_008B41F0 > 0 && RulesInstance->unknown_D54 > 0 &&
        RulesInstance->unknown_D54 >= DAT_008B41F0) {
        DynamicVectorClass<int> choices(0, 0);
        for (int i = 0; i < RulesInstance->unknown_D54; ++i)
            choices.AddItem(i);
        for (i = 0; i < DAT_008B41F0; ++i) {
            int index = ScenarioInstance->unknown_0218.RandomRanged(0, choices.Count - 1);
            choices.Delete(index);
            if (index + 1 > RulesInstance->unknown_D10) {
                index -= RulesInstance->unknown_D10;
                if (index + 1 > RulesInstance->unknown_D2C) {
                    index -= RulesInstance->unknown_D2C;
                    if (index + 1 <= RulesInstance->unknown_D48)
                        selected = RulesInstance->unknown_D3C[index];
                } else selected = RulesInstance->unknown_D20[index];
            } else selected = RulesInstance->unknown_D04[index];
            if (selected) DAT_008B41E4[i]->SecretProduction = selected;
        }
    }
}

// FUNCTION: GAMEMD 0x68C3B0
void* __fastcall FUN_0068C3B0(const void* hsv, PaletteClass* pal1, PaletteClass* pal2,
    void* palette, void* surface, int shade, int a, int b, int c,
    const unsigned char* table)
{
    int hue = static_cast<const unsigned char*>(hsv)[0];
    int saturationByte = static_cast<const unsigned char*>(hsv)[1];
    int valueByte = static_cast<const unsigned char*>(hsv)[2];
    // Receiver is the complete 768-byte palette region; assignment copies it.
    static_cast<PaletteClass*>(palette)->FUN_006260D0(pal1);
    double saturation = saturationByte;
    double value = valueByte;
    for (int i = 0; i < 16; ++i) {
        double angle = i * DAT_007F0E98 + DAT_007F0E90;
        double other = i * DAT_007F0E88 + DAT_007F0E80;
        if (!i) angle = 0.19634954084936207;
        ScenarioHSVRecord color;
        color.unknown_01 = (unsigned char)(int)(FUN_004CACB0(other) * saturation);
        color.unknown_02 = (unsigned char)(int)(FUN_004CAD00(angle) * value);
        color.unknown_00 = hue;
        ColorStruct_0072ADE0 rgb = color.FUN_00517440();
        memcpy(static_cast<unsigned char*>(palette) + ((i + 16) % 256) * 3, &rgb, 3);
    }
    ScenarioConvert_00555DA0* result = static_cast<ScenarioConvert_00555DA0*>(FUN_007C8E17(sizeof(ScenarioConvert_00555DA0)));
    if (result) return result->FUN_00555DA0(palette, pal2, surface, a, b, c, 0, table, shade);
    return 0;
}

// FUNCTION: GAMEMD 0x68C500
ConvertClass* __fastcall FUN_0068C500(const ScenarioHSVRecord* hsv,
    const PaletteClass* source, ColorStruct_0072ADE0* second,
    void* surface, PaletteClass* destination)
{
    double saturation = hsv->unknown_01;
    int hue = hsv->unknown_00;
    double value = hsv->unknown_02;
    PaletteClass palette = *source;
    for (int i = 0; i < 16; ++i) {
        double angle = i * DAT_007F0E98 + DAT_007F0E90;
        double other = i * DAT_007F0E88 + DAT_007F0E80;
        if (!i) angle = 0.19634954084936207;
        ScenarioHSVRecord color;
        color.unknown_01 = (unsigned char)(int)(FUN_004CACB0(other) * saturation);
        color.unknown_02 = (unsigned char)(int)(FUN_004CAD00(angle) * value);
        color.unknown_00 = hue;
        ColorStruct_0072ADE0 rgb = color.FUN_00517440();
        memcpy(&palette.unknown_000[((i + 16) % 256) * 3], &rgb, 3);
    }
    if (destination) destination->FUN_006260D0(&palette);
    ConvertClass* result = (ConvertClass*)FUN_007C8E17(sizeof(ConvertClass));
    if (result) return result->FUN_0048E740((ColorStruct_0072ADE0*)palette.unknown_000, second, surface, 1, 0);
    return 0;
}

// FUNCTION: GAMEMD 0x68C710
ColorScheme::ColorScheme(const char* name, HSVClass* hsv, PaletteClass* pal1,
                         PaletteClass* pal2, int shade, bool flag) throw()
{
    Name = FUN_007D5408(name);
    memcpy(unknown_308, hsv, 3);
    unknown_30C = 0;
    unknown_310 = shade;
    unknown_314[0] = 16;
    unknown_314[1] = 15;
    unknown_314[2] = 25;
    unknown_314[3] = 24;
    unknown_314[4] = 22;
    unknown_314[5] = 16;
    unknown_314[6] = 19;
    unknown_314[7] = 16;
    unknown_314[8] = 16;
    unknown_314[9] = 21;
    unknown_30C = FUN_0068C3B0(unknown_308, pal1, pal2, unknown_004,
                               DAT_00887308, shade, 1000, 1000, 1000, DAT_0083E1AC);
    if (flag) {
        ColorSchemeArray.AddItem(this);
        unknown_000 = ColorSchemeArray.Count;
    }
}

// FUNCTION: GAMEMD 0x68C9C0  ColorScheme::FindByName (__fastcall, static)
// Return the index of the scheme matching this name and shade, creating it
// first if it does not exist. The create path does not return the new object —
// it falls back into the scan, which then finds it. Writing that as an outer
// `for (;;)` is what produces retail's two backward jumps to 0x68C9D3.
//
// The constructor is declared `throw()`: `new` with a throwing constructor
// makes VC6 emit an SEH frame that retail does not have (§4.6).
//
// Argument order to _stricmp is (name, candidate), read off the push order —
// the opposite of HouseTypeClass::FindIndexOfName's inner compare. Getting it
// backwards costs two instructions and 3.8%.
int ColorScheme::FindByName(const char* name, HSVClass* hsv,
                            PaletteClass* pal1, PaletteClass* pal2,
                            int shade)
{
    for (;;)
    {
        for (int i = 0; i < ColorSchemeArray.Count; i++)
        {
            if (_stricmp(name, ColorSchemeArray.Items[i]->Name) == 0
             && ColorSchemeArray.Items[i]->unknown_310 == shade)
            {
                return i;
            }
        }

        new ColorScheme(name, hsv, pal1, pal2, shade, true);
    }
}
