// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit Queue.CPP. The name is the source-file string at 0x8374a0
//   in retail gamemd.exe v1.001, passed by the assert at 0x647990 inside this object's
//   code range (0x646a80-0x65267f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Leaf bodies that repeat at several addresses: the integer sort comparator
// (the same shape as IndexClass::Comparator, bound to other tables), release
// and replace of one global heap block, a 64 KiB global buffer clear, and
// three constant or global tests. Each address was verified separately.
//
// Six key/value-vector Grow instances, ordered ascending by retail address.
//
// Grow the vector by `extra` slots: allocate, copy the live elements across
// field by field, free the old block, and invalidate the cached lookup slot. A
// negative request and a failed allocation both report false without touching
// anything.
//
// The phrasing is the one already driven to 100% at 0x41C500 and is reproduced
// unchanged. The two details that matter are recorded there and hold here: the
// allocation is `new GrowPair[total]`, whose elided vector-constructor-iterator
// setup is retail's `DEC`/spill pair after the null check, and the copy is a
// whole-struct assignment through an explicit byte offset, which is what moves
// the pair as two dwords sharing one address computation and keeps the index a
// plain register. Count and Items are re-read every iteration rather than
// hoisted.

// VC6FLAGS: /nologo /c /O2 /Gr /GR /Ob2 /DNDEBUG /Gy
// /Ob2 expands proven global array constructors/destructors; __xc order is
// confirmed by ev_182d7497bcb677f15b6407900116870a45444b90af558c3036740f7b8ac401a4.
#include <string.h>
#include "../core/mathtbl_init_shapes.h"
#include <wchar.h>
#include <time.h>
#include <stdio.h>


extern int DAT_00A9FABC;
extern void* DAT_00ABF3F4;
extern int DAT_00B2FF78[0x4000];
extern int DAT_00B1D5E0[0x4000];
extern void* DAT_00B77F54;
extern void* DAT_00B77F60;

#include "../core/pair_vector_grow_sweep.h"

#include "../core/trivial_tu186_methods.h"
#include "../network/event_queue.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../platform/input_manager_class_methods.h"
#include "../platform/ccfile_class.h"
#include "../ui/input_controls/mouse_ww_mouse_class.h"
#include "../ui/input_controls/ui_display_chain.h"
#include "../network/null_modem_class_methods.h"
#include "../_layout/tactical.h"
#include "../_layout/rules_class.h"
#include "../ui/message_list_class_methods.h"
#include "../audio/voc_class_play_global_methods.h"
#include "../renderer/surface_class.h"
#include "../renderer/pixel_shift_view.h"
#include "../_layout/com_0048d080.h"
#include "../_layout/dialog_005d3490.h"
#include "../core/scenario_class_methods.h"
#include "../_layout/infantry_class.h"
#include "../_layout/unit_class.h"
#include "../_layout/aircraft_class.h"
#include "../_layout/building_class.h"
#include "../_layout/unit_type_class.h"
#include "../_layout/aircraft_type_class.h"
#include "../_layout/building_type_class_layout.h"
#include "../_layout/techno_class.h"
#include "../_layout/draw_layer_004a9770.h"
#include "../renderer/color_scheme_find_methods.h"
#include "../movement/loco_interfaces.h"
#include "../_layout/conn_stat.h"
#include "../_layout/version_class.h"
#include "../core/vector_class_operations.h"
#include "../_layout/cell.h"
#include "../_layout/astar_00746000.h"
#include "../_layout/obj_004a1d30.h"
#include "../_layout/obj_005bcc40.h"
#include <stdlib.h>
#include "../network/transport/winsock_interface_class.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7F0290
extern const double DAT_007F0290;
// GLOBAL: GAMEMD 0xAC6650
extern double DAT_00AC6650;
// GLOBAL: GAMEMD 0xB04878
extern unsigned char DAT_00B04878;
// GLOBAL: GAMEMD 0xB04884
extern int DAT_00B04884;
// GLOBAL: GAMEMD 0xB04888
extern int DAT_00B04888;
// GLOBAL: GAMEMD 0xB0488C
extern unsigned char DAT_00B0488C;
// GLOBAL: GAMEMD 0xB0488D
extern unsigned char DAT_00B0488D;

// GLOBAL: GAMEMD 0xA83D4C
extern HouseClass* DAT_00A83D4C;
// GLOBAL: GAMEMD 0xA802C8
extern EventQueue<128> DAT_00A802C8;
GG_STATIC_ASSERT(offsetof(EventQueue<128>, Count) == 0);
GG_STATIC_ASSERT(offsetof(EventQueue<128>, Head) == 8);
GG_STATIC_ASSERT(offsetof(EventQueue<128>, List) == 0xC);
GG_STATIC_ASSERT(offsetof(EventQueue<128>, Time) == 0x378C);
GG_STATIC_ASSERT(sizeof(EventQueue<128>) == 0x398C);
GG_STATIC_ASSERT(offsetof(HouseClass, IsGameOver) == 0x1F6);
GG_STATIC_ASSERT(offsetof(HouseClass, IsWinner) == 0x1F7);
GG_STATIC_ASSERT(offsetof(HouseClass, IsLoser) == 0x1F8);

template<> int EventQueue<128>::FUN_00652540();
// GLOBAL: GAMEMD 0x8B41F8
extern EventQueue<0x4000> DAT_008B41F8;
GG_STATIC_ASSERT(offsetof(EventQueue<0x4000>, Count) == 0);
GG_STATIC_ASSERT(offsetof(EventQueue<0x4000>, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(EventQueue<0x4000>, Head) == 8);
GG_STATIC_ASSERT(offsetof(EventQueue<0x4000>, List) == 0xC);
GG_STATIC_ASSERT(offsetof(EventQueue<0x4000>, Time) == 0x1BC00C);
GG_STATIC_ASSERT(sizeof(EventQueue<0x4000>) == 0x1CC00C);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ArrayIndex2) == 0xB8);
// GLOBAL: GAMEMD 0xA8D58C
extern CCFileClass DAT_00A8D58C;
// GLOBAL: GAMEMD 0xA8D5F8
#include "../core/game_state_flags.h"
// GLOBAL: GAMEMD 0xA8E9A0
extern unsigned char DAT_00A8E9A0;
// GLOBAL: GAMEMD 0xAC50F8
extern int DAT_00AC50F8;
// GLOBAL: GAMEMD 0xAC5200
extern int DAT_00AC5200;
// GLOBAL: GAMEMD 0xAC51FC
extern int DAT_00AC51FC;
// GLOBAL: GAMEMD 0xB04474
extern int DAT_00B04474[256];
// GLOBAL: GAMEMD 0xA8E30C
extern int DAT_00A8E30C;
// GLOBAL: GAMEMD 0xB04880
extern bool DAT_00B04880;
// GLOBAL: GAMEMD 0xA8B24C
extern int DAT_00A8B24C;
// GLOBAL: GAMEMD 0xA8B548
extern int DAT_00A8B548;
// GLOBAL: GAMEMD 0xA8B554
extern int DAT_00A8B554;
// GLOBAL: GAMEMD 0xA8B550
extern int DAT_00A8B550;
// GLOBAL: GAMEMD 0xA8B54C
extern int DAT_00A8B54C;
// Declaration: GAMEMD 0x8377A0 -- string reference
extern const char STR_008377A0[];
// Declaration: GAMEMD 0x837768 -- string reference
extern const char STR_00837768[];
// Declaration: GAMEMD 0x64B660 (decl; reloc) -- caller0x649D7D..0x649D8F.
int FUN_0064B660(char*, int, int, int, int, int*);

// GLOBAL: GAMEMD 0xA8E7A8
extern int DAT_00A8E7A8;
// GLOBAL: GAMEMD 0xB0487C
extern int DAT_00B0487C;
// Declaration: GAMEMD 0x8377DC -- string reference
extern const char STR_008377DC[];

// Declaration: GAMEMD 0x6475F0 (decl; reloc)
// FUN_006475F0
void FUN_006475F0();
// Declaration: GAMEMD 0x64C380 (decl; reloc)
// FUN_0064C380
int FUN_0064C380(int, int, ConnManClass*, const ScenarioTimer*, Obj_00646D00*);
// Declaration: GAMEMD 0x64D990 (decl; reloc)
// FUN_0064D990
void FUN_0064D990(int);
// Declaration: GAMEMD 0x64D9E0 (decl; reloc)
// FUN_0064D9E0
void FUN_0064D9E0();
// Declaration: GAMEMD 0x64DAB0 (decl; reloc)
// FUN_0064DAB0
void FUN_0064DAB0();
// Declaration: GAMEMD 0x64DEA0 (decl; reloc)
// FUN_0064DEA0
void FUN_0064DEA0(EventClass*);
// Declaration: GAMEMD 0x6516F0 (decl; reloc)
// FUN_006516F0
void FUN_006516F0(int, EventClass*);
// Declaration: GAMEMD 0x6BEC50 (decl; reloc)
// FUN_006BEC50
void FUN_006BEC50(int);
// Declaration: GAMEMD 0x6BEC60 (decl; reloc)
// FUN_006BEC60
void FUN_006BEC60();

// GLOBAL: GAMEMD 0xA8D812
extern char DAT_00A8D812[];
// GLOBAL: GAMEMD 0xA8DA40
extern int DAT_00A8DA40;
// GLOBAL: GAMEMD 0xA8EDA0
extern int DAT_00A8EDA0;
// GLOBAL: GAMEMD 0x887324
extern Tactical* DAT_00887324;

// Both DWORD reads and low-word updates of 0xAFA400 occur in this TU.
// 0x6483A3/0x6483C1, ev_d9f5845068d74c2f1868fc7566fdeb61616df207872797b1ee0d4ad87008ed9f.
struct QueueWord_00AFA400
{
    unsigned short unknown_00;
    unsigned short unknown_02;
};
GG_STATIC_ASSERT(offsetof(QueueWord_00AFA400, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(QueueWord_00AFA400, unknown_02) == 2);
GG_STATIC_ASSERT(sizeof(QueueWord_00AFA400) == 4);
// GLOBAL: GAMEMD 0xAFA400
extern QueueWord_00AFA400 DAT_00AFA400;

// Register/stack arguments verified at 0x6483B5/0x64847C/0x6484EE/0x648516.
// Declaration: GAMEMD 0x649CA0 (decl; reloc)
int FUN_00649CA0(ConnManClass*, char*, int, int, unsigned short);
// Declaration: GAMEMD 0x64A000 (decl; reloc)
void FUN_0064A000(ConnManClass*, unsigned short);
// Declaration: GAMEMD 0x64A0C0 (decl; reloc)
int FUN_0064A0C0(ConnManClass*, char*, int, unsigned, Obj_00646D00*, GameTimerClass*);
// Declaration: GAMEMD 0x64A630 (decl; reloc)
int FUN_0064A630(char*, int);
// Declaration: GAMEMD 0x48D080 (decl; reloc)
void FUN_0048D080();
// Declaration: GAMEMD 0x55DEE0 (decl; reloc) -- ECX=&key at 0x6485BC.
void FUN_0055DEE0(int*);
// Declaration: GAMEMD 0x8374F0 -- string reference
extern const char STR_008374F0[];
// Declaration: GAMEMD 0x837530 -- string reference
extern const char STR_00837530[];
// Declaration: GAMEMD 0x83754C -- string reference
extern const char STR_0083754C[];
// Declaration: GAMEMD 0x837560 -- string reference
extern const char STR_00837560[];
// Declaration: GAMEMD 0x837584 -- string reference
extern const char STR_00837584[];
// Declaration: GAMEMD 0x8375A8 -- string reference
extern const char STR_008375A8[];
// Declaration: GAMEMD 0x8375C0 -- string reference
extern const char STR_008375C0[];
// Declaration: GAMEMD 0x8375D4 -- string reference
extern const char STR_008375D4[];

// Prefix of the wire protocol, not a game-object class. Offsets at0x64A635,
// 0x64A66D,0x64A696,0x64A67F,0x64A650,0x64A75B.
// ev_192f2ed6febc139005c78f08d0f0d00636d5475885edb8a952b66f0ac5d380a3.
#pragma pack(push, 1)
struct QueueProtocol_0064A630
{
    int unknown_00;
    char unknown_04[20];
    unsigned char unknown_18;
    union
    {
        wchar_t Text[1]; // variable-length text begins here
        unsigned char Byte;
        struct { unsigned char unknown_00[4]; signed char unknown_04; } Command;
    } unknown_19;
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(QueueProtocol_0064A630, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(QueueProtocol_0064A630, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(QueueProtocol_0064A630, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(QueueProtocol_0064A630, unknown_19.Text) == 0x19);
GG_STATIC_ASSERT(offsetof(QueueProtocol_0064A630, unknown_19.Command.unknown_04) == 0x1D);
GG_STATIC_ASSERT(sizeof(QueueProtocol_0064A630) == 0x1E);
// GLOBAL: GAMEMD 0xA8BC60
extern MessageListClass DAT_00A8BC60;
// GLOBAL: GAMEMD 0xA8D110
extern unsigned char DAT_00A8D110;
// GLOBAL: GAMEMD 0xA8D111
extern unsigned char DAT_00A8D111;
// GLOBAL: GAMEMD 0xA8D112
extern wchar_t DAT_00A8D112[];
// GLOBAL: GAMEMD 0x7E27F8
extern const double DAT_007E27F8;
// Declaration: GAMEMD 0x735120 (decl; reloc)
const wchar_t* FUN_00735120(const char*);
// Declaration: GAMEMD 0x5F0180 (decl; reloc) -- 0x64A650/0x64A656.
void FUN_005F0180(int, int);
// Declaration: GAMEMD 0x752B70 (decl; reloc) -- byte argument in CL at0x64A75B.
void FUN_00752B70(unsigned char);

// Variable packed records selected by event types0x25/0x26. Read-only layout
// evidence: ev_7fcde2706a7271e3a0f269ff4645c9ecc899d1c26296b2cd0396b9a1b77ee26b.
#pragma pack(push, 1)
struct QueueFrameInfo_0064A0C0
{
    unsigned unknown_00;
    char unknown_04[4];
    unsigned short unknown_08;
    unsigned char unknown_0A;
    signed char unknown_0B;
    unsigned char unknown_0C;
};
struct QueuePacketTiming_0064A0C0
{
    signed char unknown_00;
    unsigned char unknown_01;
    unsigned unknown_02;
    char unknown_06[2];
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(QueueFrameInfo_0064A0C0, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(QueueFrameInfo_0064A0C0, unknown_08) == 8);
GG_STATIC_ASSERT(offsetof(QueueFrameInfo_0064A0C0, unknown_0A) == 10);
GG_STATIC_ASSERT(offsetof(QueueFrameInfo_0064A0C0, unknown_0B) == 11);
GG_STATIC_ASSERT(offsetof(QueueFrameInfo_0064A0C0, unknown_0C) == 12);
GG_STATIC_ASSERT(sizeof(QueueFrameInfo_0064A0C0) == 13);
GG_STATIC_ASSERT(offsetof(QueuePacketTiming_0064A0C0, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(QueuePacketTiming_0064A0C0, unknown_01) == 1);
GG_STATIC_ASSERT(offsetof(QueuePacketTiming_0064A0C0, unknown_02) == 2);
GG_STATIC_ASSERT(sizeof(QueuePacketTiming_0064A0C0) == 8);
// GLOBAL: GAMEMD 0xA8E2C4
extern unsigned DAT_00A8E2C4;
// GLOBAL: GAMEMD 0xA8E2CC
extern int DAT_00A8E2CC;
// GLOBAL: GAMEMD 0xA8E2D4
extern unsigned DAT_00A8E2D4;
// GLOBAL: GAMEMD 0xAC5210
extern unsigned DAT_00AC5210[7];
// Declaration: GAMEMD 0x652110 (decl; reloc) -- ECX=records,EDX=index0x64A18B.
void FUN_00652110(Obj_00646D00*, int);
// Declaration: GAMEMD 0x64BDD0 (decl; reloc) -- ECX=packet,EDX=length0x64A41D.
int FUN_0064BDD0(char*, unsigned);
// Declaration: GAMEMD 0x7350C0 (decl; reloc)
const char* FUN_007350C0(const wchar_t*);
// Declaration: GAMEMD 0x837998 -- string reference
extern const char STR_00837998[];
// Declaration: GAMEMD 0x837978 -- string reference
extern const char STR_00837978[];
// Declaration: GAMEMD 0x837948 -- string reference
extern const char STR_00837948[];
// Declaration: GAMEMD 0x837910 -- string reference
extern const char STR_00837910[];
// Declaration: GAMEMD 0x8378F8 -- string reference
extern const char STR_008378F8[];
// Declaration: GAMEMD 0x8378BC -- string reference
extern const char STR_008378BC[];
// Declaration: GAMEMD 0x837898 -- string reference
extern const char STR_00837898[];
// Declaration: GAMEMD 0x837888 -- string reference
extern const char STR_00837888[];
// Declaration: GAMEMD 0x8377F8 -- string reference
extern const char STR_008377F8[];
// Declaration: GAMEMD 0x837864 -- string reference
extern const char STR_00837864[];
// Declaration: GAMEMD 0x837828 -- string reference
extern const char STR_00837828[];

#include "command_packet_layouts.h"
#include "../_layout/session_class.h"

// GLOBAL: GAMEMD 0xB779C4
extern int DAT_00B779C4;
// GLOBAL: GAMEMD 0xA8BB40
extern int DAT_00A8BB40[8];
// GLOBAL: GAMEMD 0xA8BB60
extern int DAT_00A8BB60[8][8];
// Declaration: GAMEMD 0x64AD10 (decl; reloc) -- ECX=voter,EDX=target0x64AC6C..77.
void FUN_0064AD10(int, int);
// Declaration: GAMEMD 0x734E60 (decl; reloc) -- fixed args,calleeRET8.
const wchar_t* FUN_00734E60(const char*, int*, const char*, int);
// Declaration: GAMEMD 0x775B10 (decl; reloc)
HWND __cdecl FUN_00775B10();
// Declaration: GAMEMD 0x5E2820 (decl; reloc) -- ECX=index,EDX=text,stackHWND.
void FUN_005E2820(int, const wchar_t*, HWND);
// Declaration: GAMEMD 0x837A00 -- string reference
extern const char STR_00837A00[];
// Declaration: GAMEMD 0x8379E8 -- string reference
extern const char STR_008379E8[];
// Declaration: GAMEMD 0x8379D8 -- string reference
extern const char STR_008379D8[];
// Declaration: GAMEMD 0x8374A0 -- string reference
extern const char STR_008374A0[];
// Declaration: GAMEMD 0x8379B8 -- string reference
extern const char STR_008379B8[];
// Declaration: GAMEMD 0x837A4C -- string reference
extern const char STR_00837A4C[];
// Declaration: GAMEMD 0x837A30 -- string reference
extern const char STR_00837A30[];

// GLOBAL: GAMEMD 0x837320
extern const int DAT_00837320[8];
// GLOBAL: GAMEMD 0xAFA418
extern unsigned DAT_00AFA418;
// GLOBAL: GAMEMD 0xA8EAE4
extern ColorStruct DAT_00A8EAE4;
// GLOBAL: GAMEMD 0x887310
extern Surface* DAT_00887310;
// Declaration: GAMEMD 0x775690 (decl; reloc) -- ECX=control,EDX=RECT*0x64A7E5.
void FUN_00775690(HWND, RECT*);

// GLOBAL: GAMEMD 0x837300
extern const int DAT_00837300[8];
// GLOBAL: GAMEMD 0xB77780
extern int DAT_00B77780;
// GLOBAL: GAMEMD 0xB77CE0
extern int DAT_00B77CE0;
// GLOBAL: GAMEMD 0xB04890
extern int DAT_00B04890;
// GLOBAL: GAMEMD 0xB77930
extern char DAT_00B77930[];
// Declaration: GAMEMD 0x5D4ED0 (decl; reloc) -- dialog ECX0x64AE8E.
void FUN_005D4ED0(HWND);
// Declaration: GAMEMD 0x5D4E70 (decl; reloc) -- dialog ECX0x64B0EA.
void FUN_005D4E70(HWND);
// Declaration: GAMEMD 0x621E90 (decl; reloc)
void FUN_00621E90(HWND);
// Declaration: GAMEMD 0x6213A0 (decl; reloc) -- ownerdraw LPARAM0x64AE9D.
void FUN_006213A0(void*);

// GLOBAL: GAMEMD 0xB0489C
extern time_t DAT_00B0489C;
// GLOBAL: GAMEMD 0xA8022C
extern HouseClass** DAT_00A8022C;
// GLOBAL: GAMEMD 0xA80238
extern int DAT_00A80238;
// GLOBAL: GAMEMD 0xA8F900
extern unsigned char DAT_00A8F900;
// GLOBAL: GAMEMD 0xB0BD78
extern unsigned char DAT_00B0BD78;
// GLOBAL: GAMEMD 0xA8B8C1
extern unsigned char DAT_00A8B8C1;
// GLOBAL: GAMEMD 0xA8DAB4
extern int DAT_00A8DAB4;
GG_STATIC_ASSERT(offsetof(HouseClass, LostConnection) == 0x208);
GG_STATIC_ASSERT(offsetof(HouseClass, IsResigner) == 0x247);
GG_STATIC_ASSERT(offsetof(HouseClass, Defeated) == 0x1F5);
GG_STATIC_ASSERT(offsetof(HouseClass, IsHumanPlayer) == 0x1EC);
// Declaration: GAMEMD 0x5E2BE0 (decl; reloc) -- house in ECX0x64B2D2..DB.
int FUN_005E2BE0(HouseClass*);
// Declaration: GAMEMD 0x6C6F50 (decl; reloc) -- CL=0 at0x64B34B.
void FUN_006C6F50(unsigned char);
// Declaration: GAMEMD 0x5DA750 (decl; reloc) -- ECX=house,EDX=byteflag0x64B3F2.
void FUN_005DA750(int, unsigned char);
// Declaration: GAMEMD 0x5F0120 (decl; reloc) -- AL result0x64B49E.
bool FUN_005F0120();

// Dictionary stride0x280 at0x64B540, first five-byte TargetClass key then
// target bytes at+5. ev_02a7a345b4efa5a3b101e2830602a1c992f68d99c02885910fafccbfdb28ef26.
#pragma pack(push, 1)
struct QueueDictionary_0064B4D0
{
    TargetClass unknown_00[128];
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(QueueDictionary_0064B4D0, unknown_00) == 0);
GG_STATIC_ASSERT(sizeof(((QueueDictionary_0064B4D0*)0)->unknown_00[0]) == 5);
GG_STATIC_ASSERT(sizeof(QueueDictionary_0064B4D0) == 0x280);
// GLOBAL: GAMEMD 0xAC5230
extern QueueDictionary_0064B4D0 DAT_00AC5230[8];
// GLOBAL: GAMEMD 0xAFA338
extern unsigned DAT_00AFA338[8];
// GLOBAL: GAMEMD 0xAFA42C
extern int DAT_00AFA42C[8];
// Declaration: GAMEMD 0x837AA8 -- string reference
extern const char STR_00837AA8[];
// Declaration: GAMEMD 0x837A80 -- string reference
extern const char STR_00837A80[];
// Declaration: GAMEMD 0x837AD8 -- string reference
extern const char STR_00837AD8[];

// GLOBAL: GAMEMD 0xA8ED74
extern unsigned char DAT_00A8ED74;
// GLOBAL: GAMEMD 0x8208EC -- byte counts selected by the event type0x64B6E8.
extern const unsigned char DAT_008208EC[];
// Declaration: GAMEMD 0x5B3950 (decl; reloc) -- mission in ECX0x64B81A.
const char* FUN_005B3950(int);
// Declaration: GAMEMD 0x837CB0 -- string reference
extern const char STR_00837CB0[];
// Declaration: GAMEMD 0x837C7C -- string reference
extern const char STR_00837C7C[];
// Declaration: GAMEMD 0x837C64 -- string reference
extern const char STR_00837C64[];
// Declaration: GAMEMD 0x837C18 -- string reference
extern const char STR_00837C18[];
// Declaration: GAMEMD 0x837BCC -- string reference
extern const char STR_00837BCC[];
// Declaration: GAMEMD 0x837B18 -- string reference
extern const char STR_00837B18[];
// Declaration: GAMEMD 0x837B44 -- string reference
extern const char STR_00837B44[];
// Declaration: GAMEMD 0x837B84 -- string reference
extern const char STR_00837B84[];

// GLOBAL: GAMEMD 0xA83ED0
extern EventQueue<256> DAT_00A83ED0;
GG_STATIC_ASSERT(offsetof(EventQueue<256>, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(EventQueue<256>, List) == 0xC);
GG_STATIC_ASSERT(sizeof(EventQueue<256>) == 0x730C);

// Cached decoder target lists: 0x64BF77 index=player*8+slot, stride0x280;
// 0x64BF97/0x64C091 stores DWORD counts. ev_1439a780fc9c7432c7d2add662750777bf53347aa1e92a326a9dc724f49b53e2.
// GLOBAL: GAMEMD 0xAC50FC
extern int DAT_00AC50FC[8][8];
// GLOBAL: GAMEMD 0xAFA468
extern QueueDictionary_0064B4D0 DAT_00AFA468[8][8];
GG_STATIC_ASSERT(sizeof(DAT_00AC50FC) == 0x100);
GG_STATIC_ASSERT(sizeof(DAT_00AFA468) == 0xA000);
// Declaration: GAMEMD 0x837D30 -- string reference
extern const char STR_00837D30[];
// Declaration: GAMEMD 0x837D00 -- string reference
extern const char STR_00837D00[];
// Declaration: GAMEMD 0x837DCC -- string reference
extern const char STR_00837DCC[];
// Declaration: GAMEMD 0x837DA8 -- string reference
extern const char STR_00837DA8[];
// Declaration: GAMEMD 0x837D6C -- string reference
extern const char STR_00837D6C[];
// Declaration: GAMEMD 0x837CD4 -- string reference
extern const char STR_00837CD4[];

GG_STATIC_ASSERT(offsetof(ScenarioTimer, StartTime) == 0);
GG_STATIC_ASSERT(offsetof(ScenarioTimer, TimeLeft) == 8);
GG_STATIC_ASSERT(offsetof(HouseClass, IsGiverUpper) == 0x248);
GG_STATIC_ASSERT(offsetof(HouseClass, IsInPlayerControl) == 0x1ED);
GG_STATIC_ASSERT(offsetof(HouseClass, ArrayIndex) == 0x30);
GG_STATIC_ASSERT(offsetof(HouseClass, IQLevel2) == 0x24C);
GG_STATIC_ASSERT(offsetof(HouseClass, PlainName) == 0x15FF4);
GG_STATIC_ASSERT(offsetof(HouseClass, UIName) == 0x1602A);
// C380 caller/callee facts: ev_63cf4d98f24bc68d0f1f48aca48e2cbd846bef0ab1cb8fb5d4270aae350c865d.
// Timer accesses use CurrentFrame atA8ED84, matching canonical ScenarioTimer.
// Declaration: GAMEMD 0x64CDA0 (decl; reloc)
void FUN_0064CDA0(int, int);
// Declaration: GAMEMD 0x5E2BA0 (decl; reloc) -- ECX=departedHouse64C850.
int FUN_005E2BA0(HouseClass*);
// Declaration: GAMEMD 0x4FC980 (decl; reloc) -- ECX=departedHouse64C85B.
void FUN_004FC980(HouseClass*);
// Declaration: GAMEMD 0x5F0180 (decl; reloc)
void FUN_005F0180(int, int);
// GLOBAL: GAMEMD 0xA8B1DC
extern int DAT_00A8B1DC;
// GLOBAL: GAMEMD 0xA8B1F8
extern int DAT_00A8B1F8;
// GLOBAL: GAMEMD 0xA8E2D8
extern int DAT_00A8E2D8;
// GLOBAL: GAMEMD 0xA8E2DC
extern int DAT_00A8E2DC;
// GLOBAL: GAMEMD 0xA8E2E0
extern int DAT_00A8E2E0;
// GLOBAL: GAMEMD 0x8373A0
extern unsigned long DAT_008373A0;
// GLOBAL: GAMEMD 0x82091C
extern const char* DAT_0082091C[];
// Declaration: GAMEMD 0x837F78 -- string reference
extern const char STR_00837F78[];
// Declaration: GAMEMD 0x837F40 -- string reference
extern const char STR_00837F40[];
// Declaration: GAMEMD 0x837F24 -- string reference
extern const char STR_00837F24[];
// Declaration: GAMEMD 0x837EF8 -- string reference
extern const char STR_00837EF8[];
// Declaration: GAMEMD 0x837EE8 -- string reference
extern const char STR_00837EE8[];
// Declaration: GAMEMD 0x837ED8 -- string reference
extern const char STR_00837ED8[];
// Declaration: GAMEMD 0x837EC8 -- string reference
extern const char STR_00837EC8[];
// Declaration: GAMEMD 0x837EB8 -- string reference
extern const char STR_00837EB8[];
// Declaration: GAMEMD 0x837EAC -- string reference
extern const char STR_00837EAC[];
// Declaration: GAMEMD 0x837E98 -- string reference
extern const char STR_00837E98[];
// Declaration: GAMEMD 0x837E58 -- string reference
extern const char STR_00837E58[];
// Declaration: GAMEMD 0x837E20 -- string reference
extern const char STR_00837E20[];
// Declaration: GAMEMD 0x820E0C -- string reference
extern const char STR_00820E0C[];
// Declaration: GAMEMD 0x824FD8 -- string reference
extern const char STR_00824FD8[];
// Declaration: GAMEMD 0x837E74 -- string reference
extern const char STR_00837E74[];
// Declaration: GAMEMD 0x837E04 -- string reference
extern const char STR_00837E04[];
// Declaration: GAMEMD 0x837DE8 -- string reference
extern const char STR_00837DE8[];
// Declaration: GAMEMD 0x837DF8 -- string reference
extern const char STR_00837DF8[];

// GLOBAL: GAMEMD 0xA8B8B8
extern int DAT_00A8B8B8;
// GLOBAL: GAMEMD 0xA8B8BC
extern int DAT_00A8B8BC;
// GLOBAL: GAMEMD 0xB04874
extern int DAT_00B04874;
// GLOBAL: GAMEMD 0xA8B8C2
extern unsigned char DAT_00A8B8C2;
// Declaration: GAMEMD 0x837474 -- string reference
extern const char STR_00837474[];
// Declaration: GAMEMD 0x825FB0 -- string reference
extern const char STR_00825FB0[];
// Declaration: GAMEMD 0x5BC400 (decl; reloc)
void __cdecl FUN_005BC400();
// Declaration: GAMEMD 0x72DDB0 (decl; reloc)
void FUN_0072DDB0();
// Declaration: GAMEMD 0x6842F0 (decl; reloc) -- CL0 at65238A.
void FUN_006842F0(bool);
// GLOBAL: GAMEMD 0xA8DB7C
extern unsigned DAT_00A8DB7C[8];
// GLOBAL: GAMEMD 0xA8B558
extern int DAT_00A8B558;
// GLOBAL: GAMEMD 0xABCD44
extern unsigned FPSCounter_CurrentFrameRate;
// GLOBAL: GAMEMD 0x7F02A4
extern const float DAT_007F02A4;
// GLOBAL: GAMEMD 0xB052E0
extern int DAT_00B052E0;
// Declaration: GAMEMD 0x8391CC -- string reference
extern const char STR_008391CC[];
// Declaration: GAMEMD 0x8391A8 -- string reference
extern const char STR_008391A8[];
// These globals use the existing canonical opaque vector prefix; their full
// derived container/element identities are not inferred from this checksum.
// Primary DAB0 reads Items+4,Count+10,Techno Location9C and Facing388/3A0.
// GLOBAL: GAMEMD 0xA83DE8
extern DynamicVectorClassLayout DAT_00A83DE8;
// GLOBAL: GAMEMD 0x8B4108
extern DynamicVectorClassLayout DAT_008B4108;
// GLOBAL: GAMEMD 0xA8EB40
extern DynamicVectorClassLayout DAT_00A8EB40;
// GLOBAL: GAMEMD 0x87F778
extern DynamicVectorClassLayout DAT_0087F778;
// GLOBAL: GAMEMD 0xA8B230
extern ScenarioClass* DAT_00A8B230;
// Declaration: GAMEMD 0x650A90 (decl; reloc) -- ECX signed frame modulo25664DE70.
void FUN_00650A90(int);
GG_STATIC_ASSERT(offsetof(TechnoClass, PrimaryFacing) == 0x388);
GG_STATIC_ASSERT(offsetof(TechnoClass, SecondaryFacing) == 0x3A0);
GG_STATIC_ASSERT(offsetof(ObjectClass, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(HouseClass, MapIsClear) == 0x241);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_0218) == 0x218);
// GLOBAL: GAMEMD 0xA8E390
extern DynamicVectorClassLayout DAT_00A8E390;
// GLOBAL: GAMEMD 0xAFA26C
extern int DAT_00AFA26C;
// GLOBAL: GAMEMD 0xA83C9C
extern HouseTypeClass** DAT_00A83C9C;
// GLOBAL: GAMEMD 0x7E1710
extern const double DAT_007E1710;
// Declaration: GAMEMD 0x82BA08 -- string reference
extern const char STR_0082BA08[];
// Declaration: GAMEMD 0x817318 -- string reference
extern const char STR_00817318[];
// Declaration: GAMEMD 0x838EC0 -- string reference
extern const char STR_00838EC0[];
// Declaration: GAMEMD 0x40DCB0 (decl; reloc) -- enum name pointer consumed as bytes.
void* FUN_0040DCB0(int);
// LIBRARY: GAMEMD 0x7DC720 (decl; reloc)
extern void __stdcall _com_issue_error(long);
// Inlined log field operations. All destinations are the binary-proven log
// records above; these source helpers have no separately claimed retail entry.
static inline unsigned QueueLogTarget(AbstractClass* target, char* name)
{
    unsigned coordinate = 0;
    if (!target) {
        name[0] = 0;
        return 0;
    }
    if (target->Flags.IsTechno) coordinate = target->vf_16();
    else if (target->vf_11() == 11) {
        CellStruct cell = static_cast<CellClass*>(target)->MapCoords;
        coordinate = (unsigned(int(cell.Y)) << 16) | unsigned(int(cell.X));
    }
    name[23] = 0;
    strncpy(name, static_cast<const char*>(FUN_0040DCB0(target->vf_11())), 23);
    return coordinate;
}

static inline unsigned char QueueLogHeading(FacingClass* facing)
{
    DirStruct direction;
    unsigned bits;
    // Full returned representation, includingPadding: ev_6ce7a1b456c12a5926ab40c1239b11b47165549fa89da53c645c985400daa876.
    memcpy(&bits, facing->FUN_004C93D0(&direction), sizeof(bits));
    return static_cast<unsigned char>(((bits >> 7) + 1) >> 1);
}

static inline ILocomotion* QueueLogLocomotor(FootClass* foot)
{
    // Genuine COM interface boundary at Foot+674, checks at650Fxx; reload
    // after _com_issue_error matches the canonical smart-pointer operation.
    if (!foot->Locomotor) _com_issue_error(0x80004003);
    return static_cast<ILocomotion*>(foot->Locomotor);
}

static inline void QueueLogTechno(QueueTechnoLog_00650A90* out, TechnoClass* item,
                                 bool secondary)
{
    CoordStruct location = item->Location;
    out->unknown_00 = location.X / 10 + (location.Y / 10) * 65536U;
    out->unknown_64 = QueueLogHeading(&item->PrimaryFacing);
    if (secondary) out->unknown_65 = QueueLogHeading(&item->SecondaryFacing);
    out->unknown_66 = static_cast<unsigned char>(item->vf_97());
}

static inline void QueueLogObject(QueueObjectLog_00650A90* out, ObjectClass* item)
{
    CoordStruct location = item->Location;
    out->unknown_00 = location.X / 10 + (location.Y / 10) * 65536U;
    out->unknown_24 = static_cast<short>(item->vf_11());
    if (item->vf_11() == 43 || item->vf_11() == 19) {
        out->unknown_04 = -1;
        out->unknown_08[0] = 0;
    } else {
        out->unknown_04 = item->vf_34()->vf_16();
        out->unknown_08[23] = 0;
        strncpy(out->unknown_08, item->vf_34()->ID, 23);
    }
    HouseClass* owner = item->vf_15();
    out->unknown_20 = owner ? static_cast<unsigned char>(owner->ArrayIndex) : 255;
}

// Library binding: GAMEMD 0x7C8EF4 -- sprintf.
// Library binding: GAMEMD 0x7CA845 -- fopen.
// Library binding: GAMEMD 0x7CA7D8 -- fprintf.
// Library binding: GAMEMD 0x7CA75B -- fclose.
// Declaration: GAMEMD 0x74FDC0 (decl; reloc) -- existing recovered symbol spelling.
char* FUN_0074fdc0();
// GLOBAL: GAMEMD 0xA8ECE0
extern VersionClass DAT_00A8ECE0;
// Declaration: GAMEMD 0x777AC0 (decl; reloc) -- ECX output,EDXcapacity6517CB.
char* FUN_00777AC0(char*, unsigned);
// Declaration: GAMEMD 0x777B60 (decl; reloc) -- ECX output,EDXcapacity6517E1.
char* FUN_00777B60(char*, unsigned);
// Declaration: GAMEMD 0x777B30 (decl; reloc) -- ECX output,EDXcapacity6517F3.
char* FUN_00777B30(char*, unsigned);
// Declaration: GAMEMD 0x4E6150 (decl; reloc) -- shared native probe ABI.
extern "C" void __fastcall FUN_004E6150(int*, char*, char*, int);
// Declaration: GAMEMD 0x4E62B0 (decl; reloc) -- no args, CPU name pointer.
const char* FUN_004E62B0();
// GLOBAL: GAMEMD 0xABCD48
extern unsigned DAT_00ABCD48;
// GLOBAL: GAMEMD 0xABCD4C
extern unsigned DAT_00ABCD4C;
// GLOBAL: GAMEMD 0xA8B568
extern int DAT_00A8B568;
// GLOBAL: GAMEMD 0xA8DB9C
extern int DAT_00A8DB9C;
// GLOBAL: GAMEMD 0xA8EB60
extern int DAT_00A8EB60;
// GLOBAL: GAMEMD 0x81D988 -- byte string passed as fopen mode.
extern const char DAT_0081D988[];
// GLOBAL: GAMEMD 0x821F08 -- probe-result text passed as printf string.
extern const char DAT_00821F08[];
// GLOBAL: GAMEMD 0x821F04 -- probe-result text passed as printf string.
extern const char DAT_00821F04[];
// Declaration: GAMEMD 0x0081D850 -- string reference
extern const char STR_0081D850[];
// Declaration: GAMEMD 0x0081D864 -- string reference
extern const char STR_0081D864[];
// Declaration: GAMEMD 0x0081D870 -- string reference
extern const char STR_0081D870[];
// Declaration: GAMEMD 0x0081D88C -- string reference
extern const char STR_0081D88C[];
// Declaration: GAMEMD 0x0081D8A4 -- string reference
extern const char STR_0081D8A4[];
// Declaration: GAMEMD 0x0081D8B4 -- string reference
extern const char STR_0081D8B4[];
// Declaration: GAMEMD 0x0081D8C8 -- string reference
extern const char STR_0081D8C8[];
// Declaration: GAMEMD 0x0081D8F0 -- string reference
extern const char STR_0081D8F0[];
// Declaration: GAMEMD 0x0081D8FC -- string reference
extern const char STR_0081D8FC[];
// Declaration: GAMEMD 0x0081D918 -- string reference
extern const char STR_0081D918[];
// Declaration: GAMEMD 0x0081D930 -- string reference
extern const char STR_0081D930[];
// Declaration: GAMEMD 0x0081D948 -- string reference
extern const char STR_0081D948[];
// Declaration: GAMEMD 0x0081D95C -- string reference
extern const char STR_0081D95C[];
// Declaration: GAMEMD 0x0081D970 -- string reference
extern const char STR_0081D970[];
// Declaration: GAMEMD 0x00821EE4 -- string reference
extern const char STR_00821EE4[];
// Declaration: GAMEMD 0x00821F0C -- string reference
extern const char STR_00821F0C[];
// Declaration: GAMEMD 0x0083886C -- string reference
extern const char STR_0083886C[];
// Declaration: GAMEMD 0x00838880 -- string reference
extern const char STR_00838880[];
// Declaration: GAMEMD 0x00838894 -- string reference
extern const char STR_00838894[];
// Declaration: GAMEMD 0x008388A8 -- string reference
extern const char STR_008388A8[];
// Declaration: GAMEMD 0x008388BC -- string reference
extern const char STR_008388BC[];
// Declaration: GAMEMD 0x008388D0 -- string reference
extern const char STR_008388D0[];
// Declaration: GAMEMD 0x008388E4 -- string reference
extern const char STR_008388E4[];
// Declaration: GAMEMD 0x00838918 -- string reference
extern const char STR_00838918[];
// Declaration: GAMEMD 0x0083894C -- string reference
extern const char STR_0083894C[];
// Declaration: GAMEMD 0x00838AA0 -- string reference
extern const char STR_00838AA0[];
// Declaration: GAMEMD 0x00838AB0 -- string reference
extern const char STR_00838AB0[];
// Declaration: GAMEMD 0x00838AC4 -- string reference
extern const char STR_00838AC4[];
// Declaration: GAMEMD 0x00838DE0 -- string reference
extern const char STR_00838DE0[];
// Declaration: GAMEMD 0x00838DEC -- string reference
extern const char STR_00838DEC[];
// Declaration: GAMEMD 0x00838E04 -- string reference
extern const char STR_00838E04[];
// Declaration: GAMEMD 0x00838E18 -- string reference
extern const char STR_00838E18[];
// Declaration: GAMEMD 0x00838E30 -- string reference
extern const char STR_00838E30[];
// Declaration: GAMEMD 0x00838E40 -- string reference
extern const char STR_00838E40[];
// Declaration: GAMEMD 0x00838E4C -- string reference
extern const char STR_00838E4C[];
// Declaration: GAMEMD 0x00838E90 -- string reference
extern const char STR_00838E90[];
// Declaration: GAMEMD 0x00838EE8 -- string reference
extern const char STR_00838EE8[];
// Declaration: GAMEMD 0x00838EF8 -- string reference
extern const char STR_00838EF8[];
// Declaration: GAMEMD 0x00838F38 -- string reference
extern const char STR_00838F38[];
// Declaration: GAMEMD 0x00838F70 -- string reference
extern const char STR_00838F70[];
// Declaration: GAMEMD 0x00838FC0 -- string reference
extern const char STR_00838FC0[];
// Declaration: GAMEMD 0x00838FF8 -- string reference
extern const char STR_00838FF8[];
// Declaration: GAMEMD 0x00839074 -- string reference
extern const char STR_00839074[];
// Declaration: GAMEMD 0x008390A8 -- string reference
extern const char STR_008390A8[];
// Declaration: GAMEMD 0x00839100 -- string reference
extern const char STR_00839100[];
// Declaration: GAMEMD 0x00839138 -- string reference
extern const char STR_00839138[];
// Declaration: GAMEMD 0x00839168 -- string reference
extern const char STR_00839168[];
// Declaration: GAMEMD 0x0083917C -- string reference
extern const char STR_0083917C[];
// Declaration: GAMEMD 0x00839188 -- string reference
extern const char STR_00839188[];
// Declaration: GAMEMD 0x00839194 -- string reference
extern const char STR_00839194[];
// Declaration: GAMEMD 0x0084E865 -- string reference
extern const char STR_0084E865[];
static inline void QueueDumpObject(FILE* file, const Obj_00646CE0* log,
                                  const QueueObjectLog_00650A90* item, int index)
{
    fprintf(file, STR_00838AC4, index, item->unknown_00);
    if (item->unknown_24 == 43 || item->unknown_24 == 19)
        fprintf(file, STR_00838AA0, FUN_0040DCB0(item->unknown_24), 0);
    else
        fprintf(file, STR_00838AB0, FUN_0040DCB0(item->unknown_24), item->unknown_04, item->unknown_08);
    if (item->unknown_20 == -1) fprintf(file, STR_00838EE8);
    else fprintf(file, STR_0083894C, log->unknown_0C[item->unknown_20].unknown_00);
}

// Declaration: GAMEMD 0x838AD4 -- string reference
extern const char STR_00838AD4[];
// Declaration: GAMEMD 0x838A54 -- string reference
extern const char STR_00838A54[];
// SYNTHETIC: GAMEMD 0x00646AB0
// dynamic initializer for DAT_00AFA460
// GLOBAL: GAMEMD 0x00AFA460
double DAT_00AFA460 = DAT_00AC6650 / DAT_007F0290;

// SYNTHETIC: GAMEMD 0x00646AD0
// dynamic initializer for DAT_00AFA410
// GLOBAL: GAMEMD 0x00AFA410
double DAT_00AFA410 = 1.0 / DAT_00AFA460;

GG_STATIC_ASSERT(sizeof(DAT_00AFA460) == 8);
GG_STATIC_ASSERT(sizeof(DAT_00AFA410) == 8);

// SYNTHETIC: GAMEMD 0x00646C50
// GLOBAL: GAMEMD 0x00AFA420
MathTblCoord DAT_00AFA420;

// FUNCTION: GAMEMD 0x646C90
Obj_00646CE0::Obj_00646CE0()
{
    unknown_300 = 0;
    unknown_2EC = 0;
    for (int i = 0; i < 5; ++i)
    {
        unknown_318[i] = 0;
        unknown_304[i] = 0;
    }
    unknown_330 = 0;
    unknown_32C = 0;
    unknown_334 = 0;
    unknown_338 = 0x20000;
}

// FUNCTION: GAMEMD 0x646CE0
// Branching.
Obj_00646CE0::~Obj_00646CE0()
{
    if (unknown_334 != 0)
    {
        FUN_007C8B3D(unknown_334);
    }
}

// FUNCTION: GAMEMD 0x646D00
// Stores several members.
Obj_00646D00::Obj_00646D00()
{
    unknown_00 = -1;
    unknown_04 = 0;
    unknown_08 = 0;
    unknown_0C = 0;
    unknown_10 = 0;
    unknown_14 = 0;
}

// SYNTHETIC: GAMEMD 0x646D20
// _$E4
// GLOBAL: GAMEMD 0xAFA278
Obj_00646D00 DAT_00AFA278[7];

// FUNCTION: GAMEMD 0x646D50
// Branching.
void __cdecl FUN_00646D50()
{
    if (Session_00A8B238.GameMode == 4)
    {
        Manager_00A8E9C0.FUN_00543090();
    }
}

// FUNCTION: GAMEMD 0x646D70
void FUN_00646D70()
{
    if (Session_00A8B238.GameMode == 4) Manager_00A8E9C0.FUN_00543080();
}

// FUNCTION: GAMEMD 0x646DB0
// Empty function.
void __cdecl FUN_00646DB0()
{
}

// SYNTHETIC: GAMEMD 0x646DC0
// _$E7
// GLOBAL: GAMEMD 0xAFA358
Obj_00646D00 DAT_00AFA358[7];

// FUNCTION: GAMEMD 0x646DF0
void FUN_00646DF0(int index)
{
    DAT_00AFA358[index].unknown_14 = timeGetTime();
}

// SYNTHETIC: GAMEMD 0x646E10
// _$E12
// GLOBAL: GAMEMD 0xAC6660
Obj_00646CE0 DAT_00AC6660[256];

// SYNTHETIC: GAMEMD 0x646E60
// _$E10
// Compiler-generated reverse array destructor for DAT_00AC6660.

// FUNCTION: GAMEMD 0x646E90
bool FUN_00646E90(int mission, const TargetClass& target, TargetClass source,
                  const TargetClass& destination)
{
    // Canonical empty target semantics; its ID is initialized rather than
    // reproducing the retail compiler's incidental preserved register value.
    TargetClass follow = { 0, 0 };
    EventClass event(DAT_00A83D4C->ArrayIndex, source, (unsigned char)mission,
                     target, destination, follow);
    if (DAT_00A802C8.Count >= 128) return false;
    DAT_00A802C8.List[DAT_00A802C8.Head] = event;
    DAT_00A802C8.Time[DAT_00A802C8.Head] = timeGetTime();
    ++DAT_00A802C8.Count;
    DAT_00A802C8.Head = (DAT_00A802C8.Head + 1) & 127;
    return true;
}

// FUNCTION: GAMEMD 0x646F70
bool FUN_00646F70(int mission, const TargetClass& target, TargetClass source,
                  const TargetClass& destination, int speed, int maxSpeed)
{
    EventClass event(DAT_00A83D4C->ArrayIndex, source, (unsigned char)mission,
                     target, destination, speed, maxSpeed);
    if (DAT_00A802C8.Count >= 128) return false;
    DAT_00A802C8.List[DAT_00A802C8.Head] = event;
    DAT_00A802C8.Time[DAT_00A802C8.Head] = timeGetTime();
    ++DAT_00A802C8.Count;
    DAT_00A802C8.Head = (DAT_00A802C8.Head + 1) & 127;
    return true;
}

// FUNCTION: GAMEMD 0x647040
bool FUN_00647040()
{
    if (DAT_00A83D4C->IsWinner || DAT_00A83D4C->IsLoser || DAT_00A83D4C->IsGameOver) return false;
    EventClass event(DAT_00A83D4C->ArrayIndex, 0xc);
    if (DAT_00A802C8.Count >= 128) return false;
    DAT_00A802C8.List[DAT_00A802C8.Head] = event;
    DAT_00A802C8.Time[DAT_00A802C8.Head] = timeGetTime();
    ++DAT_00A802C8.Count;
    DAT_00A802C8.Head = (DAT_00A802C8.Head + 1) & 127;
    return true;
}

// FUNCTION: GAMEMD 0x6470F0
bool FUN_006470F0()
{
    if (DAT_00A83D4C->IsWinner || DAT_00A83D4C->IsLoser || DAT_00A83D4C->IsGameOver) return false;
    EventClass event(DAT_00A83D4C->ArrayIndex, 0x22);
    if (DAT_00A802C8.Count >= 128) return false;
    DAT_00A802C8.List[DAT_00A802C8.Head] = event;
    DAT_00A802C8.Time[DAT_00A802C8.Head] = timeGetTime();
    ++DAT_00A802C8.Count;
    DAT_00A802C8.Head = (DAT_00A802C8.Head + 1) & 127;
    return true;
}

// FUNCTION: GAMEMD 0x6471A0
bool FUN_006471A0()
{
    unsigned char type = 0x13;
    if (Session_00A8B238.GameMode == 4 && Flag_00A8DBA0 && PlayerCount_00A8DA84 > 2 && Session_00A8B238.FUN_00697E70(0)) type = 0x27;
    EventClass event(DAT_00A83D4C->ArrayIndex, type);
    if (DAT_00A802C8.Count >= 128) return false;
    DAT_00A802C8.List[DAT_00A802C8.Head] = event;
    DAT_00A802C8.Time[DAT_00A802C8.Head] = timeGetTime();
    ++DAT_00A802C8.Count;
    DAT_00A802C8.Head = (DAT_00A802C8.Head + 1) & 127;
    return true;
}

// FUNCTION: GAMEMD 0x647260
void FUN_00647260()
{
    if (!(DAT_00A8D5F8 & 2))
    {
        switch (Session_00A8B238.GameMode)
        {
        case 0:
        case 5:
            while (DAT_00A802C8.Count != 0)
            {
                EventClass& event = DAT_00A802C8.List[DAT_00A802C8.unknown_04];
                event.IsExecuted &= 0xFE;
                if (DAT_008B41F8.Count < 0x4000)
                {
                    DAT_008B41F8.List[DAT_008B41F8.Head] = event;
                    DAT_008B41F8.Time[DAT_008B41F8.Head] = timeGetTime();
                    DAT_008B41F8.Head = (DAT_008B41F8.Head + 1) & 0x3FFF;
                    ++DAT_008B41F8.Count;
                }
                DAT_00A802C8.FUN_00652540();
            }
            if (DAT_00A8D5F8 & 1) FUN_0064D9E0();
            if (FUN_0064C380(1, DAT_00A83D4C->Type->ArrayIndex2, 0, 0, 0)) FUN_0064D990(0);
            else DAT_00A8E9A0 = 0;
            return;
        case 1:
        case 2:
        case 3:
        case 4:
            FUN_006475F0();
        default:
            return;
        }
    }

    EventClass event;
    if (DAT_0087F770->FUN_0054F000())
    {
        if (DAT_0087F770->FUN_0054F050() == 0x1B || (DAT_00A8D5F8 & 4))
        {
            DAT_00A8E9A0 = 0;
            return;
        }
    }
    else if ((DAT_00A8D5F8 & 4) && CurrentFrame > 0 &&
             (WWMouseClassInstance->vf_11() != DAT_00AC50F8 || WWMouseClassInstance->vf_12() != DAT_00AC5200))
    {
        DAT_00A8E9A0 = 0;
        return;
    }
    DAT_00AC50F8 = WWMouseClassInstance->vf_11();
    DAT_00AC5200 = WWMouseClassInstance->vf_12();
    FUN_0064DAB0();
    unsigned frame = CurrentFrame;
    DAT_00B04474[frame & 255] = DAT_00AC51FC;
    if (DAT_00A8E30C <= CurrentFrame)
    {
        if (DAT_00B04880) FUN_006516F0(CurrentFrame % 256, 0);
        else FUN_0064DEA0(0);
        FUN_006BEC60();
        FUN_006BEC50(0);
        frame = CurrentFrame;
    }
    if (frame == 0)
    {
        if (Session_00A8B238.GameMode != 0) return;
    }
    else if (Session_00A8B238.GameMode != 0 && Session_00A8B238.GameMode != 5 && DAT_00A8B24C == 2 &&
             frame != ((DAT_00A8B554 - 1 + frame) / DAT_00A8B554) * DAT_00A8B554) return;

    int count;
    if (DAT_00A8D58C.CCFileClass::ReadBytes(&count, 4) != 4)
    {
        DAT_00A8E9A0 = 0;
        return;
    }
    for (int i = 0; i < count; ++i)
    {
        if (DAT_00A8D58C.CCFileClass::ReadBytes(&event, sizeof(event)) != sizeof(event))
        {
            DAT_00A8E9A0 = 0;
            return;
        }
        event.IsExecuted &= 0xFE;
        if (DAT_008B41F8.Count < 0x4000)
        {
            DAT_008B41F8.List[DAT_008B41F8.Head] = event;
            DAT_008B41F8.Time[DAT_008B41F8.Head] = timeGetTime();
            DAT_008B41F8.Head = (DAT_008B41F8.Head + 1) & 0x3FFF;
            ++DAT_008B41F8.Count;
        }
    }
    int result;
    if (Session_00A8B238.GameMode == 0) result = FUN_0064C380(1, DAT_00A83D4C->Type->ArrayIndex2, 0, 0, 0);
    else result = FUN_0064C380(DAT_00A8B548, 0, 0, 0, 0);
    if (result) FUN_0064D990(0);
    else DAT_00A8E9A0 = 0;
}

// FUNCTION: GAMEMD 0x648350
void FUN_00648350()
{
    FUN_004068E0(STR_008375D4);
    ConnManClass* manager;
    char* data;
    int capacity;
    if (Session_00A8B238.GameMode >= 3 && Session_00A8B238.GameMode <= 4) {
        manager = &Manager_00A8E9C0;
        data = DAT_00A8D812;
        capacity = DAT_00A8DA40;
    } else {
        manager = &DAT_00A8EA70;
        data = DAT_00A8EA70.unknown_04;
        capacity = DAT_00A8EA70.unknown_08 - 14;
    }
    DAT_00AFA400.unknown_00 += FUN_00649CA0(manager, data, capacity,
        DAT_00A8B550, DAT_00AFA400.unknown_00);
    ScenarioElapsedTimer resend(15);
    ScenarioElapsedTimer timeout(600);
    GameTimerClass stamp;
    FUN_004068E0(STR_008375C0);
    for (;;) {
        DAT_0087F770->FUN_0054F000();
        if (!resend.GetTimeLeft()) {
            resend = ScenarioElapsedTimer(15);
            FUN_004068E0(STR_008375A8);
            FUN_0064A000(manager, DAT_00AFA400.unknown_00);
        }
        manager->Service();
        if (!timeout.GetTimeLeft()) {
            FUN_004068E0(STR_00837560);
            return;
        }
        for (int n = 1; n <= 64; ++n) {
            int length, id;
            if (!manager->vf_3(data, &length, &id)) break;
            DAT_0087F770->FUN_0054F000();
            if (Session_00A8B238.GameMode == 1 || Session_00A8B238.GameMode == 2) {
                switch (FUN_0064A630(data, 0)) {
                case 0: break;
                case 4:
                    manager->Service();
                    resend = ScenarioElapsedTimer(15);
                    timeout = ScenarioElapsedTimer(600);
                    break;
                default: return;
                }
            } else if (FUN_0064A0C0(manager, data, id, length, DAT_00AFA358, &stamp) == 3) {
                FUN_004068E0(STR_0083754C);
                return;
            }
            manager->Service();
        }
        FUN_0048D080();
        if (!DAT_00A8EDA0) {
            int key, x, y;
            Map_0087F7E8.GScreenClass::Input(&key, &x, &y);
            FUN_0055DEE0(&key);
            DAT_00887324->vf_23();
            Map_0087F7E8.GScreenClass::vf_15();
        }
        int player = -1;
        int oldest = CurrentFrame + 1000;
        for (int i = 0; i < manager->vf_4(); ++i) {
            if (DAT_00AFA358[i].unknown_00 < oldest) {
                oldest = DAT_00AFA358[i].unknown_00;
                player = i;
            }
        }
        if (CurrentFrame <= DAT_00A8B554 + oldest) {
            FUN_004068E0(STR_00837530, oldest);
            FUN_004068E0(STR_008374F0);
            FUN_0064A000(manager, DAT_00AFA400.unknown_00);
            FUN_0064A000(manager, DAT_00AFA400.unknown_00);
            FUN_0064A000(manager, DAT_00AFA400.unknown_00);
            FUN_0064A000(manager, DAT_00AFA400.unknown_00);
            return;
        }
        FUN_004068E0(STR_00837584, player, DAT_00AFA358[player].unknown_00);
    }
}

// FUNCTION: GAMEMD 0x649CA0
int FUN_00649CA0(ConnManClass* manager, char* data, int capacity,
                int ahead, unsigned short sent)
{
    int total = 0;
    int remaining = DAT_00A802C8.Count;
    if (remaining > 0x2000 - DAT_008B41F8.Count)
        remaining = 0x2000 - DAT_008B41F8.Count;
    int initialCount = DAT_00A802C8.Count;
    do {
        int needsAck = remaining != 0 && DAT_00A802C8.Count != 0 && DAT_00A8B54C != 1;
        // The wire buffer starts with the packed EventClass fields at +0/+2/+3,
        // +7/+B/+D (0x649CFF..0x649D5E); this is a serialization layout cast.
        EventClass* header = reinterpret_cast<EventClass*>(data);
        header->Type = 0x1C;
        int packed = 0;
        if (DAT_00A8B24C == 2)
            header->Frame = ((DAT_00A8B554 + (unsigned)CurrentFrame - 1 + ahead) /
                DAT_00A8B554) * DAT_00A8B554;
        else header->Frame = CurrentFrame + ahead;
        header->HouseIndex = DAT_00A83D4C->ArrayIndex;
        header->Data.Payload_19.unknown_07 = DAT_00AC51FC;
        header->Data.Payload_19.unknown_0B = sent;
        header->Data.Payload_19.unknown_0D = ahead;
        int length = DAT_00A8B24C ? 14 : sizeof(EventClass);
        if (DAT_00A8B24C == 0) {
            int n = 0;
            while (DAT_00A802C8.Count && n < remaining) {
                EventClass& event = DAT_00A802C8.List[DAT_00A802C8.unknown_04];
                int bytes = sizeof(EventClass);
                if (event.Type == 0x1F) bytes += event.Data.Payload_1F.unknown_0B;
                if (length + bytes > capacity) break;
                event.Frame = CurrentFrame + ahead;
                event.HouseIndex = DAT_00A83D4C->ArrayIndex;
                event.IsExecuted &= 0xFE;
                if (DAT_008B41F8.Count >= 0x4000) break;
                DAT_008B41F8.List[DAT_008B41F8.Head] = event;
                DAT_008B41F8.Time[DAT_008B41F8.Head] = timeGetTime();
                DAT_008B41F8.Head = (DAT_008B41F8.Head + 1) & 0x3FFF;
                ++DAT_008B41F8.Count;
                unsigned char type = event.Type;
                memcpy(data + length, &event, sizeof(EventClass));
                if (type == 0x1F) {
                    memcpy(data + length + sizeof(EventClass),
                        event.Data.Payload_1F.unknown_07, event.Data.Payload_1F.unknown_0B);
                    length += sizeof(EventClass) + event.Data.Payload_1F.unknown_0B;
                } else length += sizeof(EventClass);
                ++n;
                if (DAT_00A802C8.Count) {
                    DAT_00A802C8.unknown_04 = (DAT_00A802C8.unknown_04 + 1) & 127;
                    --DAT_00A802C8.Count;
                }
            }
            // Retail increments n at0x649F2F, not packed at ESP+24.
        } else if (DAT_00A8B24C > 0 && DAT_00A8B24C <= 2) {
            length = FUN_0064B660(data, capacity, ahead, length, remaining, &packed);
        } else length = 0;
        remaining -= packed;
        total += packed;
        if (packed) {
            FUN_004068E0(STR_008377A0, packed, CurrentFrame);
            needsAck = 1;
        }
        manager->vf_2(data, length, needsAck, -1);
        ++DAT_00B0487C;
        manager->Service();
        if (!DAT_00A802C8.Count || DAT_00A802C8.Count > initialCount || !remaining) {
            if (total) FUN_004068E0(STR_00837768, total, CurrentFrame);
            return total;
        }
    } while (true);
}

// FUNCTION: GAMEMD 0x64A000
void FUN_0064A000(ConnManClass* manager, unsigned short sent)
{
    EventClass event;
    memset(&event, 0, sizeof(event));
    event.Type = 0x19;
    if (DAT_00A8B24C == 2)
        event.Frame = ((DAT_00A8B554 + DAT_00A8B550 - 1 + (unsigned)CurrentFrame) /
            DAT_00A8B554) * DAT_00A8B554;
    else event.Frame = DAT_00A8B550 + CurrentFrame;
    event.HouseIndex = DAT_00A83D4C->ArrayIndex;
    event.Data.Payload_19.unknown_07 = DAT_00A8E7A8;
    event.Data.Payload_19.unknown_0D = DAT_00A8B550;
    event.Data.Payload_19.unknown_0B = sent;
    manager->vf_2(&event, 14, 0, -1);
    FUN_004068E0(STR_008377DC);
    ++DAT_00B0487C;
}

// FUNCTION: GAMEMD 0x64A0C0
int FUN_0064A0C0(ConnManClass* manager, char* data, int id, unsigned length,
                Obj_00646D00* records, GameTimerClass* stamp)
{
    int ready = 0;
    int index = manager->vf_6(id);
    // Both packet formats use the packed EventClass header; their variable
    // records begin at +7, with strides13 and8 (0x64A367/0x64A36A).
    EventClass* header = reinterpret_cast<EventClass*>(data);
    if (Flag_00A8DBA0 && (header->Type == 0x25 || header->Type == 0x26)) {
        int count = header->HouseIndex;
        if (header->Type == 0x26) FUN_004068E0(STR_00837998);
        else if (header->Type == 0x25) FUN_004068E0(STR_00837978);
        if (!count) FUN_004068E0(STR_00837948);
        unsigned maximum = 0;
        QueueFrameInfo_0064A0C0* frame = reinterpret_cast<QueueFrameInfo_0064A0C0*>(data + 7);
        QueuePacketTiming_0064A0C0* timing = reinterpret_cast<QueuePacketTiming_0064A0C0*>(data + 7);
        for (int n = 0; n < count; ++n, ++frame, ++timing) {
            if (header->Type == 0x25) {
                index = manager->vf_6(frame->unknown_0B);
                if (index != -1) {
                    Obj_00646D00& record = records[index];
                    int newest = frame->unknown_00 - frame->unknown_0A;
                    if (record.unknown_00 < newest) {
                        record.unknown_00 = newest;
                        FUN_00652110(records, index);
                        if (Manager_00A8E9C0.FUN_00540FC0(frame->unknown_0B))
                            FUN_004068E0(STR_00837910,
                                FUN_007350C0(Manager_00A8E9C0.FUN_00540FC0(frame->unknown_0B)),
                                frame->unknown_0B, record.unknown_00);
                        if (record.unknown_04 < frame->unknown_08) {
                            record.unknown_04 = frame->unknown_08;
                            FUN_004068E0(STR_008378F8, record.unknown_04);
                        }
                    } else if (Manager_00A8E9C0.FUN_00540FC0(frame->unknown_0B)) {
                        FUN_004068E0(STR_008378BC,
                            FUN_007350C0(Manager_00A8E9C0.FUN_00540FC0(frame->unknown_0B)),
                            frame->unknown_0B, record.unknown_00);
                    }
                    if (!(frame->unknown_0C & 1))
                        record.unknown_0C = stamp->Clock.GetTime() - stamp->StartTime;
                }
            } else if (timing->unknown_00 == DAT_00A83D4C->ArrayIndex) {
                DAT_00A8E2D4 = timing->unknown_02;
                FUN_004068E0(STR_00837898, (DAT_00A8E2D4 * 1000U) / 60);
            } else {
                index = manager->vf_6(timing->unknown_00);
                if (index != -1) {
                    unsigned value = timing->unknown_02;
                    records[index].unknown_10 = value;
                    DAT_00AC5210[index] = value;
                    if (maximum <= value) maximum = value;
                    if (timing->unknown_01 && Session_00A8B238.FUN_00697E70(0) &&
                            DAT_00A8E2CC != timing->unknown_00) {
                        EventClass event(DAT_00A83D4C->ArrayIndex, 0x28, int(timing->unknown_00));
                        if (DAT_00A802C8.Count < 128) {
                            DAT_00A802C8.List[DAT_00A802C8.Head] = event;
                            DAT_00A802C8.Time[DAT_00A802C8.Head] = timeGetTime();
                            DAT_00A802C8.Head = (DAT_00A802C8.Head + 1) & 127;
                            ++DAT_00A802C8.Count;
                        }
                    }
                }
            }
        }
        if (count && maximum) DAT_00A8E2C4 = maximum;
        return ready;
    }
    Obj_00646D00& record = records[index];
    if (record.unknown_00 < int(header->Frame - header->Data.Payload_19.unknown_0D)) {
        if (record.unknown_00 == -1) {
            ready = 1;
            FUN_004068E0(STR_00837888);
        }
        record.unknown_00 = header->Frame - header->Data.Payload_19.unknown_0D;
        FUN_00652110(records, index);
    }
    if (record.unknown_04 < header->Data.Payload_19.unknown_0B)
        record.unknown_04 = header->Data.Payload_19.unknown_0B;
    if (header->Type == 0x19) {
        if (Session_00A8B238.GameMode == 4 || Session_00A8B238.GameMode == 3)
            FUN_004068E0(STR_008377F8, Manager_00A8E9C0.FUN_00540FC0(id),
                header->Frame - header->Data.Payload_19.unknown_0D);
        if (header->Data.Payload_19.unknown_07 != DAT_00A8E7A8) return 2;
        record.unknown_0C = stamp->Clock.GetTime() - stamp->StartTime;
        return ready;
    }
    int count;
    if (DAT_00A8B24C == 0) {
        count = 0;
        int offset = 0;
        while (length >= sizeof(EventClass)) {
            EventClass* event = reinterpret_cast<EventClass*>(data + offset);
            if (event->Type != 0x19) {
                event->IsExecuted &= 0xFE;
                if (event->Type == 0x1F) {
                    event->Data.Payload_1F.unknown_07 = new char[event->Data.Payload_1F.unknown_0B];
                    // Retail's 0x64A46F source is the packet's +111, independent
                    // of the current event offset. Preserve that wire behavior.
                    memcpy(event->Data.Payload_1F.unknown_07, data + sizeof(EventClass),
                        event->Data.Payload_1F.unknown_0B);
                    offset += event->Data.Payload_1F.unknown_0B;
                    length -= event->Data.Payload_1F.unknown_0B;
                }
                if (DAT_008B41F8.Count >= 0x4000) {
                    if (event->Type == 0x1F) FUN_007C8B3D(event->Data.Payload_1F.unknown_07);
                    count = -1;
                    break;
                }
                DAT_008B41F8.List[DAT_008B41F8.Head] = *event;
                DAT_008B41F8.Time[DAT_008B41F8.Head] = timeGetTime();
                DAT_008B41F8.Head = (DAT_008B41F8.Head + 1) & 0x3FFF;
                ++DAT_008B41F8.Count;
                ++count;
            }
            offset += sizeof(EventClass);
            length -= sizeof(EventClass);
        }
    } else count = FUN_0064BDD0(data, length);
    if (count == -1) {
        FUN_004068E0(STR_00837864);
        return 3;
    }
    if (header->Type == 0x1C && count > 0) --count;
    FUN_004068E0(STR_00837828, CurrentFrame, count);
    record.unknown_08 += unsigned(count) & 0xFFFF;
    return ready;
}

// FUNCTION: GAMEMD 0x64A630
int FUN_0064A630(char* data, int flag)
{
    // The protocol starts with a 32-bit kind. Ordinary events share the buffer
    // but use EventClass's byte type, house+2 and Frame+3 instead.
    QueueProtocol_0064A630* packet = reinterpret_cast<QueueProtocol_0064A630*>(data);
    int kind = packet->unknown_00;
    if (kind == 0x66 || (!flag && (kind == 0x69 || kind == 0x6A))) {
        FUN_005F0180(packet->unknown_19.Command.unknown_04, 0);
        return 5;
    }
    if (kind == 0x68) {
        const wchar_t* name = FUN_00735120(packet->unknown_04);
        wchar_t* text = packet->unknown_19.Text;
        if (!DAT_00A8BC60.FUN_005D3FC0(name, packet->unknown_18, text,
                int(Rules->MessageDelay * DAT_007E27F8))) {
            name = FUN_00735120(packet->unknown_04);
            DAT_00A8BC60.FUN_005D3BA0(name, packet->unknown_18, text,
                packet->unknown_18, 0x4046, int(Rules->MessageDelay * DAT_007E27F8), false);
            VocClass::PlayGlobal(Rules->IncomingMessage, 1.0f, 0x2000, 0);
        }
        if (wcslen(text)) wcscpy(DAT_00A8D112, text);
        Map_0087F7E8.GScreenClass::FlagToRedraw(2);
    } else if (kind == 0x78) {
        if ((DAT_00A8D110 && Session_00A8B238.GameMode == 3) || (DAT_00A8D111 && Session_00A8B238.GameMode == 4)) {
            FUN_00752B70(packet->unknown_19.Byte);
            return 4;
        }
    } else if (!(kind >= 100 && kind <= 0x6C) && !(kind >= 0x6E && kind <= 0x74) &&
               DAT_00A8B54C != 1) {
        EventClass* event = reinterpret_cast<EventClass*>(data);
        if (event->Type && event->Type < 0x2F)
            return event->HouseIndex == DAT_00A83D4C->ArrayIndex ? 6 : 0;
    }
    return 4;
}

// FUNCTION: GAMEMD 0x64A7B0
void FUN_0064A7B0(HWND dialog)
{
    for (int i = 0; i < PlayerCount_00A8DA84; ++i) {
        RECT rect;
        FUN_00775690(GetDlgItem(dialog, DAT_00837320[i]), &rect);
        RectangleStruct bounds = { rect.left, rect.top,
            rect.right - rect.left, rect.bottom - rect.top };
        int index;
        if (Session_00A8B238.GameMode == 1 || Session_00A8B238.GameMode == 2) index = 0;
        else index = Manager_00A8E9C0.IPXManagerClass::vf_6(Players_00A8DA78[i]->unknown_6F);
        unsigned delay = i ? DAT_00AFA418 - DAT_00AFA278[index].unknown_0C : 0;
        ColorStruct color(0, 200, 0);
        if (delay > 240) {
            color.R = 200;
            if (delay > 480) {
                color.G = 0;
                unsigned elapsed = (timeGetTime() * 60 -
                    unsigned(DAT_00AFA278[index].unknown_14) * 60) / 1000;
                if (elapsed < 420) {
                    color.R = 0;
                    color.B = 200;
                    delay = elapsed;
                }
            }
        }
        int percent = 100 - (delay * 100) / 1200;
        if (percent < 1) percent = 0;
        int width = bounds.Width * percent / 100;
        if (width < 6) width = 6;
        unsigned short pixel =
            ((color.R >> gg_b_translucent_pixel_format.loss0) << gg_b_translucent_pixel_format.pos0) |
            ((color.G >> gg_b_translucent_pixel_format.loss1) << gg_b_translucent_pixel_format.pos1) |
            ((color.B >> gg_b_translucent_pixel_format.loss2) << gg_b_translucent_pixel_format.pos2);
        unsigned background =
            ((DAT_00A8EAE4.R >> gg_b_translucent_pixel_format.loss0) << gg_b_translucent_pixel_format.pos0) |
            ((DAT_00A8EAE4.G >> gg_b_translucent_pixel_format.loss1) << gg_b_translucent_pixel_format.pos1) |
            ((DAT_00A8EAE4.B >> gg_b_translucent_pixel_format.loss2) << gg_b_translucent_pixel_format.pos2);
        RectangleStruct clip = DAT_00887310->GetRect();
        DAT_00887310->DrawRectEx(&clip, &bounds, background);
        RectangleStruct inner = { bounds.X + 2, bounds.Y + 2, width - 4, bounds.Height - 4 };
        clip = DAT_00887310->GetRect();
        DAT_00887310->FillRectEx(&clip, &inner, pixel);
    }
}

// FUNCTION: GAMEMD 0x64AAE0
void FUN_0064AAE0(HWND dialog, int player)
{
    if (player < 0 || player >= PlayerCount_00A8DA84) return;
    FUN_004068E0(STR_00837A00, player, Players_00A8DA78[player], Players_00A8DA78[0]->unknown_6F);
    HWND list = GetDlgItem(dialog, 0x651);
    if (!player || (Session_00A8B238.GameMode == 4 && DAT_00B779C4)) {
        if (!player)
            FUN_005E2820(-1, FUN_00734E60(STR_008379E8, 0, STR_008374A0, 0xD2F), list);
        else
            FUN_005E2820(-1, FUN_00734E60(STR_008379D8, 0, STR_008374A0, 0xD39), list);
        int count = SendMessageA(list, 0x18B, 0, 0);
        if (count > 50) {
            SendMessageA(list, 0x182, 0, 0);
            --count;
        }
        SendMessageA(list, 0x197, count - 1, 0);
        return;
    }
    QueuePacket_0064AAE0 packet;
    packet.unknown_00 = 0x1C;
    strncpy(packet.unknown_04, FUN_007350C0(Players_00A8DA78[0]->Name), 20);
    packet.unknown_33 = Players_00A8DA78[0]->unknown_6F;
    packet.unknown_2F = Players_00A8DA78[player]->unknown_6F;
    for (int i = 1; i < PlayerCount_00A8DA84; ++i) {
        FUN_004068E0(STR_008379B8, Players_00A8DA78[i]);
        Manager_00A8E9C0.FUN_005410F0(&packet, sizeof(packet), 1,
            &Players_00A8DA78[i]->Address, 0, 0);
    }
    FUN_0064AD10(Players_00A8DA78[0]->unknown_6F, Players_00A8DA78[player]->unknown_6F);
}

// FUNCTION: GAMEMD 0x64AD10
void FUN_0064AD10(int voter, int player)
{
    int count = DAT_00A8BB40[player];
    for (int i = 0; i < count; ++i)
        if (DAT_00A8BB60[player][i] == voter) return;
    DAT_00A8BB60[player][count] = voter;
    ++DAT_00A8BB40[player];
    if (Session_00A8B238.GameMode == 3 || Session_00A8B238.GameMode == 4) {
        const wchar_t* name = Manager_00A8E9C0.FUN_00540FC0(voter);
        if (!name) name = Players_00A8DA78[0]->Name;
        FUN_004068E0(STR_00837A4C, name, Manager_00A8E9C0.FUN_00540FC0(player));
        wchar_t text[256];
        swprintf(text, FUN_00734E60(STR_00837A30, 0, STR_008374A0, 0xD9D),
            name, Manager_00A8E9C0.FUN_00540FC0(player));
        HWND list = GetDlgItem(FUN_00775B10(), 0x651);
        FUN_005E2820(-1, text, list);
        int count = SendMessageA(list, 0x18B, 0, 0);
        if (count > 50) {
            SendMessageA(list, 0x182, 0, 0);
            --count;
        }
        SendMessageA(list, 0x197, count - 1, 0);
    }
}

// FUNCTION: GAMEMD 0x64AE30
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_0064AE30()
{
    DAT_00B04884 = 0;
    DAT_00B04888 = 0;
    DAT_00B0488C = 0;
    DAT_00B0488D = 0;
    DAT_00B04878 = 0;
}

// FUNCTION: GAMEMD 0x64AE50
LRESULT __stdcall FUN_0064AE50(HWND window, unsigned message, WPARAM wparam, LPARAM lparam)
{
    HWND dialog = window;
    // GetWindowLong+8 contains an int* (0x64AE5A/0x64B0AA).
    int* state = reinterpret_cast<int*>(GetWindowLongA(dialog, 8));
    switch (message) {
    case 2:
        FUN_005D4ED0(dialog);
        return 0;
    case 0xF:
        FUN_00621E90(dialog);
        FUN_0064A7B0(dialog);
        ValidateRect(dialog, 0);
        return 0;
    case 0x14: return 1;
    case 0x2B:
        FUN_006213A0(reinterpret_cast<void*>(lparam));
        return 1;
    case 0x111:
        switch (wparam & 0xFFFF) {
        case 2: *state = 2; return 0;
        case 0x640: FUN_0064AAE0(dialog, 0); return 0;
        case 0x641: FUN_0064AAE0(dialog, 2); return 0;
        case 0x642: FUN_0064AAE0(dialog, 1); return 0;
        case 0x643: FUN_0064AAE0(dialog, 3); return 0;
        case 0x644: FUN_0064AAE0(dialog, 4); return 0;
        case 0x645: FUN_0064AAE0(dialog, 5); return 0;
        case 0x646: FUN_0064AAE0(dialog, 6); return 0;
        case 0x647: FUN_0064AAE0(dialog, 7); return 0;
        }
        break;
    case 0x113:
        if (Session_00A8B238.GameMode == 4 && wparam == 1 && DAT_00AC1170) {
            if (DAT_00B77780 < 5) {
                DAT_00AC1170->Vtbl->At_18(DAT_00AC1170, DAT_00B77930, 1000, &window);
                ++DAT_00B77780;
            }
            ++DAT_00B04890;
            if (DAT_00B779C4) {
                if (!DAT_00B0488C && DAT_00B04890 > 5 && !DAT_00B77CE0) {
                    DAT_00B0488C = 1;
                    ++DAT_00B04884;
                } else if (!DAT_00B0488D && DAT_00B04890 > 10 && !DAT_00B77CE0) {
                    DAT_00B0488D = 1;
                    ++DAT_00B04888;
                }
                if (DAT_00B04884 > 5 || DAT_00B04888 > 2) {
                    DAT_00B04878 = 1;
                    *state = 2;
                    return 0;
                }
            }
            SetTimer(dialog, 1, 1000, 0);
            return 0;
        }
        break;
    case 0x132: case 0x133: case 0x134: case 0x135:
    case 0x136: case 0x137: case 0x138:
        return reinterpret_cast<LRESULT>(GetStockObject(4));
    case 0x497:
        FUN_005D4E70(dialog);
        for (int i = 0; i < 8; ++i) {
            EnableWindow(GetDlgItem(dialog, DAT_00837300[i]), false);
            EnableWindow(GetDlgItem(dialog, DAT_00837320[i]), false);
        }
        for (i = 0; i < 8; ++i) {
            HWND name = GetDlgItem(dialog, DAT_00837300[i]);
            HWND control = GetDlgItem(dialog, DAT_00837320[i]);
            if (i < PlayerCount_00A8DA84) {
                SendMessageA(name, 0x4B2, 0, reinterpret_cast<LPARAM>(Players_00A8DA78[i]));
                EnableWindow(name, true);
                EnableWindow(control, true);
            } else {
                DestroyWindow(name);
                DestroyWindow(control);
            }
        }
        if (Session_00A8B238.GameMode == 4) {
            DAT_00B77780 = 0;
            DAT_00B77CE0 = 0;
            DAT_00B0488C = 0;
            DAT_00B0488D = 0;
            DAT_00B04890 = 0;
            DAT_00B04878 = 0;
            SetTimer(dialog, 1, 1000, 0);
        }
        WWMouseClassInstance->vf_4();
        break;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x64B240
void FUN_0064B240(ConnManClass* manager, int index, Obj_00646D00* records, unsigned char flag)
{
    bool recent = time(0) - DAT_00B0489C < 60;
    DAT_00B0489C = time(0);
    int house = manager->vf_5(index);
    FUN_004068E0(STR_00837AA8, house, CurrentFrame);
    if (house == -1) {
        FUN_004068E0(STR_00837A80);
        return;
    }
    DAT_00A8022C[house]->LostConnection = 1;
    if (FUN_005E2BE0(DAT_00A8022C[house]) == 1 && Session_00A8B238.GameMode == 4 && !DAT_00A8F900) {
        Unsorted_RegisterGameEndTime();
        DAT_00B0BD78 = 1;
        if (!recent) DAT_00A8B8C1 = 1;
        for (int i = 0; i < DAT_00A80238; ++i) {
            HouseClass* player = DAT_00A8022C[i];
            if (player && !player->Defeated && player->IsHumanPlayer) player->LostConnection = 1;
        }
        FUN_006C6F50(0);
    }
    if (FUN_005E2BE0(DAT_00A8022C[house]) > 1 && !recent)
        DAT_00A8022C[house]->IsResigner = 1;
    for (int i = index; i < manager->vf_4() - 1; ++i) {
        records[i] = records[i + 1];
        DAT_00A8BB40[i] = DAT_00A8BB40[i + 1];
        memcpy(DAT_00A8BB60[i], DAT_00A8BB60[i + 1], sizeof(DAT_00A8BB60[i]));
    }
    FUN_005DA750(house, flag);
}

// FUNCTION: GAMEMD 0x64B410
int FUN_0064B410(ConnManClass* manager, Obj_00646D00* records)
{
    if (Session_00A8B238.GameMode == 1 || Session_00A8B238.GameMode == 2) {
        if (manager->vf_4()) {
            ++DAT_00A8DAB4;
            if (!FUN_005F0120()) {
                --DAT_00A8DAB4;
                return 0;
            }
            --DAT_00A8DAB4;
        }
    } else if (Session_00A8B238.GameMode == 3 || Session_00A8B238.GameMode == 4) {
        int oldest = 0x7FFFFFFF;
        int index = 0;
        for (int i = 0; i < manager->vf_4(); ++i) {
            if (records[i].unknown_00 < oldest) {
                oldest = records[i].unknown_00;
                index = i;
            }
        }
        FUN_0064B240(manager, index, records, 1);
        return 1;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x64B4D0
bool FUN_0064B4D0(unsigned char* count, int* length, char* prefix, const char* targets, bool apply)
{
    if (*count > 1) {
        for (int i = 0; i < 8; ++i) {
            if (DAT_00AFA338[i] == *count &&
                !memcmp(&DAT_00AC5230[i].unknown_00, prefix, sizeof(TargetClass)) &&
                !memcmp(&DAT_00AC5230[i].unknown_00[1], targets,
                    DAT_00AFA338[i] * sizeof(TargetClass) - sizeof(TargetClass))) {
                if (apply) {
                    *length -= *count * sizeof(TargetClass) - sizeof(TargetClass);
                    *count = 0;
                    prefix[6] = i;
                }
                return true;
            }
        }
    }
    if (apply && *count > 1) {
        int selected = -1;
        int oldest = -1;
        for (int i = 0; i < 8; ++i) {
            if (!DAT_00AFA42C[i]) { selected = i; break; }
            int elapsed = CurrentFrame - DAT_00AFA42C[i];
            if (elapsed > oldest) { selected = i; oldest = elapsed; }
        }
        if (selected == -1) selected = 0;
        FUN_004068E0(STR_00837AD8, *count, selected);
        DAT_00AFA42C[selected] = CurrentFrame;
        memcpy(&DAT_00AC5230[selected].unknown_00, prefix, sizeof(TargetClass));
        memcpy(&DAT_00AC5230[selected].unknown_00[1], targets,
            *count * sizeof(TargetClass) - sizeof(TargetClass));
        DAT_00AFA338[selected] = *count;
        prefix[6] = selected;
    }
    return false;
}

// FUNCTION: GAMEMD 0x64B660
int FUN_0064B660(char* data, int capacity, int ahead, int length, int limit, int* result)
{
    EventClass previous;
    memset(&previous, 0, sizeof(previous));
    int packed = 0;
    char* runCount = 0;
    unsigned char runLength = 0;
    bool append = false;
    bool forceNew = false;
    char* prefix = 0;
    char* targets = 0;
    if (DAT_00A8ED74) FUN_004068E0(STR_00837CB0, CurrentFrame);
    while (DAT_00A802C8.Count && packed < limit) {
        EventClass& event = DAT_00A802C8.List[DAT_00A802C8.unknown_04];
        unsigned payload = DAT_008208EC[event.Type];
        int needed = payload + 1;
        if (event.Type == 0x1F) needed += event.Data.Payload_1F.unknown_0B;
        if (previous.Type == 4) {
            if (event.Type == 4) {
                if (!forceNew && event.Data.MegaMission.Mission == previous.Data.MegaMission.Mission &&
                    event.Data.MegaMission.Target.RTTI == previous.Data.MegaMission.Target.RTTI &&
                    event.Data.MegaMission.Target.ID == previous.Data.MegaMission.Target.ID &&
                    event.Data.MegaMission.Destination.RTTI == previous.Data.MegaMission.Destination.RTTI &&
                    event.Data.MegaMission.Destination.ID == previous.Data.MegaMission.Destination.ID) {
                    if (DAT_00A8ED74) {
                        unsigned destination = event.Data.MegaMission.Destination.RTTI ?
                            (unsigned(event.Data.MegaMission.Destination.RTTI) << 24) |
                            (event.Data.MegaMission.Destination.ID & 0xFFFFFF) : ~0U;
                        unsigned target = event.Data.MegaMission.Target.RTTI ?
                            (unsigned(event.Data.MegaMission.Target.RTTI) << 24) |
                            (event.Data.MegaMission.Target.ID & 0xFFFFFF) : ~0U;
                        unsigned whom = event.Data.MegaMission.Whom.RTTI ?
                            (unsigned(event.Data.MegaMission.Whom.RTTI) << 24) |
                            (event.Data.MegaMission.Whom.ID & 0xFFFFFF) : ~0U;
                        FUN_004068E0(STR_00837C7C, whom,
                            FUN_005B3950(event.Data.MegaMission.Mission), target, destination);
                    }
                    payload = sizeof(TargetClass);
                    ++runLength;
                    needed = sizeof(TargetClass);
                    append = true;
                } else {
                    if (DAT_00A8ED74) FUN_004068E0(STR_00837C64);
                    FUN_004068E0(STR_00837C18, runLength);
                    FUN_0064B4D0(&runLength, &length, prefix, targets, true);
                    ++needed;
                    append = false;
                    *runCount = runLength;
                    runLength = 1;
                    runCount = data + length + 1;
                }
            } else {
                FUN_004068E0(STR_00837BCC, runLength);
                FUN_0064B4D0(&runLength, &length, prefix, targets, true);
                *runCount = runLength;
                runCount = 0;
                append = false;
                runLength = 0;
            }
        } else if (event.Type == 4) {
            if (DAT_00A8ED74) FUN_004068E0(STR_00837C64);
            ++needed;
            runLength = 1;
            append = false;
            runCount = data + length + 1;
        }
        forceNew = false;
        if (needed + length > capacity) {
            if (event.Type == 4 && append) {
                // Primary0x64BD5F decrements before dictionary lookup; the
                // decompiler's reordered expression would miscount a cache hit.
                --runLength;
                FUN_004068E0(STR_00837B18, runLength);
                FUN_0064B4D0(&runLength, &length, prefix, targets, true);
                *runCount = runLength;
            }
            break;
        }
        if (DAT_00A8B24C == 2)
            event.Frame = ((DAT_00A8B554 + (unsigned)CurrentFrame - 1 + ahead) /
                DAT_00A8B554) * DAT_00A8B554;
        else event.Frame = CurrentFrame + ahead;
        event.HouseIndex = DAT_00A83D4C->ArrayIndex;
        event.IsExecuted &= 0xFE;
        if (DAT_008B41F8.Count >= 0x4000) break;
        DAT_008B41F8.List[DAT_008B41F8.Head] = event;
        DAT_008B41F8.Time[DAT_008B41F8.Head] = DAT_00A802C8.Time[DAT_00A802C8.unknown_04];
        DAT_008B41F8.Head = (DAT_008B41F8.Head + 1) & 0x3FFF;
        ++DAT_008B41F8.Count;
        if (event.Type == 4) {
            *runCount = runLength;
            if (append) {
                memcpy(data + length, event.Data.DataBuffer, payload);
                length += payload;
                if (DAT_00A802C8.Count == 1 || packed == limit - 1) {
                    FUN_004068E0(STR_00837B44, runLength);
                    FUN_0064B4D0(&runLength, &length, prefix, targets, true);
                    *runCount = runLength;
                } else if (FUN_0064B4D0(&runLength, &length, prefix, targets, false)) {
                    FUN_004068E0(STR_00837B84, runLength);
                    forceNew = true;
                    *runCount = runLength;
                }
            } else {
                data[length] = 4;
                prefix = data + length + 2;
                memcpy(prefix, event.Data.DataBuffer, payload);
                targets = prefix + payload;
                length += 2 + payload;
            }
        } else if (event.Type == 0x1B) {
            data[length] = 0x1B;
            // Wire payload starts at EventClass+0xD for this type0x64BB81.
            memcpy(data + length + 1, event.Data.DataBuffer + 6, payload);
            length += 1 + payload;
        } else if (event.Type == 0x1F) {
            data[length] = 0x1F;
            memcpy(data + length + 1, &event.Data.Payload_1F.unknown_0B, payload);
            length += 1 + payload;
            memcpy(data + length, event.Data.Payload_1F.unknown_07, event.Data.Payload_1F.unknown_0B);
            length += event.Data.Payload_1F.unknown_0B;
        } else {
            data[length] = event.Type;
            memcpy(data + length + 1, event.Data.DataBuffer, payload);
            length += 1 + payload;
        }
        ++packed;
        previous = event;
        if (!DAT_00A802C8.Count) break;
        DAT_00A802C8.unknown_04 = (DAT_00A802C8.unknown_04 + 1) & 127;
        --DAT_00A802C8.Count;
    }
    *result = packed;
    return length;
}

// FUNCTION: GAMEMD 0x64BDD0
int FUN_0064BDD0(char* data, unsigned length)
{
    EventClass event;
    memset(&event, 0, sizeof(event));
    int player = reinterpret_cast<EventClass*>(data)->HouseIndex;
    int offset = 0;
    int added = 0;
    unsigned expected = 13;
    while (expected + 1 <= length) {
        event.Type = data[offset];
        if (event.Type == 0x19) {
            offset += 1 + expected;
            length -= 1 + expected;
            expected = 13;
            continue;
        }
        unsigned char count = 0;
        if (event.Type == 0x1C) {
            EventClass* header = reinterpret_cast<EventClass*>(data + offset);
            event.HouseIndex = header->HouseIndex;
            event.Frame = header->Frame;
            offset += 6;
            length -= 6;
        } else if (event.Type == 4) {
            count = data[offset + 1];
            ++offset;
            --length;
        }
        memset(event.Data.DataBuffer, 0, sizeof(event.Data.DataBuffer));
        unsigned payload = DAT_008208EC[event.Type];
        unsigned consumed = payload;
        if (event.Type == 4) {
            memcpy(event.Data.DataBuffer, data + offset + 1, payload);
            if (count == 0) {
                int slot = event.Data.MegaMission._gap_;
                offset += 1 + payload;
                length -= 1 + payload;
                consumed = 5;
                int units = 1;
                // Count entries are full DWORDs (0x64BF97/0x64C091); wire
                // iteration deliberately takes the low byte0x64C115.
                count = static_cast<unsigned char>(DAT_00AC50FC[player][slot]);
                event.Data.MegaMission.Whom = DAT_00AFA468[player][slot].unknown_00[0];
                if (!event.Frame || !event.Type) FUN_004068E0(STR_00837D30, CurrentFrame, slot, player);
                while (count) {
                    if (DAT_008B41F8.Count >= 0x4000) return -1;
                    DAT_008B41F8.List[DAT_008B41F8.Head] = event;
                    DAT_008B41F8.Time[DAT_008B41F8.Head] = timeGetTime();
                    DAT_008B41F8.Head = (DAT_008B41F8.Head + 1) & 0x3FFF;
                    ++DAT_008B41F8.Count;
                    ++added;
                    event.Data.MegaMission.Whom = DAT_00AFA468[player][slot].unknown_00[units];
                    --count;
                    ++units;
                    if (count == 1) {
                        consumed = ~0U;
                        FUN_004068E0(STR_00837D00, int(event.Data.MegaMission._gap_), units * 5);
                        break;
                    }
                }
            } else if (count > 1) {
                offset += 1 + payload;
                length -= 1 + payload;
                consumed = 5;
                FUN_004068E0(STR_00837DCC);
                int slot = event.Data.MegaMission._gap_;
                DAT_00AFA468[player][slot].unknown_00[0] = event.Data.MegaMission.Whom;
                int units = 1;
                DAT_00AC50FC[player][slot] = units;
                if (!event.Frame || !event.Type) FUN_004068E0(STR_00837DA8, CurrentFrame);
                // Additional wire targets are packed five-byte TargetClass
                // values, as copied at0x64C057/0x64C05E.
                const TargetClass* next = reinterpret_cast<const TargetClass*>(data + offset);
                while (count) {
                    if (DAT_008B41F8.Count >= 0x4000) return -1;
                    DAT_008B41F8.List[DAT_008B41F8.Head] = event;
                    DAT_008B41F8.Time[DAT_008B41F8.Head] = timeGetTime();
                    DAT_008B41F8.Head = (DAT_008B41F8.Head + 1) & 0x3FFF;
                    ++DAT_008B41F8.Count;
                    ++added;
                    event.Data.MegaMission.Whom = *next;
                    DAT_00AFA468[player][slot].unknown_00[units] = *next;
                    --count;
                    ++units;
                    DAT_00AC50FC[player][slot] = units;
                    if (count == 1) {
                        consumed = 4;
                        FUN_004068E0(STR_00837D6C, player, units, int(event.Data.MegaMission._gap_));
                        break;
                    }
                    offset += sizeof(TargetClass);
                    length -= sizeof(TargetClass);
                    ++next;
                }
            }
        } else if (event.Type == 0x1B) {
            memcpy(event.Data.DataBuffer + 6, data + offset + 1, payload);
        } else if (event.Type == 0x1F) {
            memcpy(&event.Data.Payload_1F.unknown_0B, data + offset + 1, payload);
            unsigned bytes = event.Data.Payload_1F.unknown_0B;
            event.Data.Payload_1F.unknown_07 = new char[bytes];
            memcpy(event.Data.Payload_1F.unknown_07, data + payload + offset + 1, bytes);
            offset += bytes;
            length -= bytes;
        } else memcpy(event.Data.DataBuffer, data + offset + 1, payload);
        if (!event.Frame || !event.Type) FUN_004068E0(STR_00837CD4, CurrentFrame);
        if (DAT_008B41F8.Count >= 0x4000) {
            if (event.Type == 0x1F) FUN_007C8B3D(event.Data.Payload_1F.unknown_07);
            return -1;
        }
        DAT_008B41F8.List[DAT_008B41F8.Head] = event;
        DAT_008B41F8.Time[DAT_008B41F8.Head] = timeGetTime();
        DAT_008B41F8.Head = (DAT_008B41F8.Head + 1) & 0x3FFF;
        ++DAT_008B41F8.Count;
        ++added;
        offset += 1 + consumed;
        length -= 1 + consumed;
        if (!length) return added;
        expected = DAT_008208EC[static_cast<unsigned char>(data[offset])];
        if (data[offset] == 4) ++expected;
    }
    return added;
}

// FUNCTION: GAMEMD 0x64C380
// Signed comparisons: JLE/JGE64C3D4/3D8,64C477/47B and the
// late-event signed branches; ev_63cf4d98f24bc68d0f1f48aca48e2cbd846bef0ab1cb8fb5d4270aae350c865d.
int FUN_0064C380(int, int, ConnManClass* manager, const ScenarioTimer* timer,
                Obj_00646D00* records)
{
    int houses = DAT_00A80238;
    int count = DAT_008B41F8.Count;
    int frame = DAT_00A8B1DC;
    for (int n = 0; n < count; ++n) {
        EventClass& event = DAT_008B41F8.List[(DAT_008B41F8.unknown_04 + n) & 0x3FFF];
        if (event.Type != 0x1C && DAT_00A8B1F8 < int(event.Frame) && int(event.Frame) < frame) {
            FUN_004068E0(STR_00837F78, event.Frame, frame);
            frame = DAT_00A8B1DC;
            event.Frame = frame;
        }
    }
    if (DAT_00A8E2D8 && DAT_00A8E2DC && DAT_00A8E2E0 != -1) {
        frame = DAT_00A8E2DC;
        for (n = 0; n < count; ++n) {
            EventClass& event = DAT_008B41F8.List[(DAT_008B41F8.unknown_04 + n) & 0x3FFF];
            if (event.Type == 0x13 && event.HouseIndex == DAT_00A8E2E0 &&
                DAT_00A8E2D8 < int(event.Frame) && int(event.Frame) < frame) {
                FUN_004068E0(STR_00837F40, event.Frame, frame);
                frame = DAT_00A8E2DC;
                event.Frame = frame;
            }
        }
        if (frame < CurrentFrame) {
            DAT_00A8E2D8 = 0;
            DAT_00A8E2DC = 0;
            DAT_00A8E2E0 = -1;
        }
    }
    for (int h = 0; h < houses; ++h) {
        HouseClass* house = DAT_00A8022C[h];
        if (!house || (!house->IsHumanPlayer && !house->IsInPlayerControl)) continue;
        for (n = 0; n < count; ++n) {
            EventClass& event = DAT_008B41F8.List[(DAT_008B41F8.unknown_04 + n) & 0x3FFF];
            if (event.HouseIndex != house->ArrayIndex || int(event.Frame) > CurrentFrame ||
                (event.IsExecuted & 1)) continue;
            if (int(event.Frame) < CurrentFrame && event.Type != 0x1C &&
                Session_00A8B238.GameMode != 0 && Session_00A8B238.GameMode != 5) {
                FUN_004068E0(STR_00837F24);
                FUN_004068E0(STR_00837EF8);
                FUN_004068E0(STR_00837EE8, DAT_0082091C[event.Type]);
                FUN_004068E0(STR_00837ED8, event.Frame);
                FUN_004068E0(STR_00837EC8, event.HouseIndex);
                FUN_004068E0(STR_00837EB8, DAT_00A8B550);
                FUN_004068E0(STR_00837EAC, CurrentFrame);
                FUN_004068E0(STR_00837E98, DAT_00A8B554);
                manager->vf_4();
                continue;
            }
            if (event.Type == 0x13) {
                HouseClass* departed = 0;
                for (int j = 0; j < houses; ++j) {
                    departed = DAT_00A8022C[j];
                    if (departed && departed->ArrayIndex == event.HouseIndex) {
                        departed->IsGiverUpper = 1;
                        break;
                    }
                }
                if (FUN_005E2BE0(departed) == 1) {
                    if (Session_00A8B238.GameMode == 4 && !DAT_00A8F900) {
                        DAT_00A8B8C1 = 1;
                        Unsorted_RegisterGameEndTime();
                        FUN_006C6F50(0);
                    }
                }
                if (Session_00A8B238.GameMode == 4 && !DAT_00A8F900 && DAT_00A83D4C &&
                    DAT_00A83D4C == departed) {
                    FUN_004068E0(STR_00837E58);
                    FUN_006C6F50(0);
                }
                if (!FUN_005E2BA0(departed)) FUN_004FC980(departed);
            }
            if (event.Type == 0x13 || event.Type == 0xC || event.Type == 0x22) {
                if (DAT_00A8ED74 && event.Type == 0x13)
                    FUN_004068E0(STR_00837E20, event.HouseIndex,
                        DAT_00A8022C[event.HouseIndex]->PlainName, event.Frame, CurrentFrame);
                if (event.HouseIndex == DAT_00A83D4C->ArrayIndex) {
                    DAT_008373A0 = timeGetTime() - DAT_008B41F8.Time[
                        (DAT_008B41F8.unknown_04 + n) & 0x3FFF];
                    event.FUN_004C6CB0();
                } else if (event.Type == 0x13) {
                    FUN_004068E0(STR_00820E0C, CurrentFrame);
                    if (Session_00A8B238.GameMode == 1 || Session_00A8B238.GameMode == 2) FUN_005F0180(h, 0);
                    else if ((Session_00A8B238.GameMode == 3 || Session_00A8B238.GameMode == 4) && manager) {
                        int index = manager->vf_6(h);
                        if (index != -1) {
                            while (index < manager->vf_4() - 1) {
                                records[index] = records[index + 1];
                                ++index;
                            }
                            FUN_005DA750(h, 0);
                        }
                    }
                    if ((DAT_00A8D5F8 & 2) && event.Type == 0x13) {
                        house->IsHumanPlayer = 0;
                        house->IQLevel2 = Rules->unknown_1434;
                        house->AllyAIHouses();
                        char name[21];
                        strncpy(name, STR_00824FD8, 20);
                        name[20] = 0;
                        memcpy(house->PlainName, name, sizeof(name));
                        wcsncpy(house->UIName,
                            FUN_00734E60(STR_00837E74, 0, STR_008374A0, 0x1628), 21);
                        house->UIName[20] = 0;
                        FUN_004068E0(STR_00837E04, STR_008374A0, 0x162A);
                        --DAT_00A8B54C;
                    }
                }
            } else if (event.Type != 0x1C) {
                DAT_008373A0 = timeGetTime() - DAT_008B41F8.Time[
                    (DAT_008B41F8.unknown_04 + n) & 0x3FFF];
                if (event.Type == 4) {
                    if (DAT_00A83ED0.Count < 256) {
                        DAT_00A83ED0.List[DAT_00A83ED0.Head] = event;
                        DAT_00A83ED0.Time[DAT_00A83ED0.Head] = timeGetTime();
                        DAT_00A83ED0.Head = (DAT_00A83ED0.Head + 1) & 255;
                        ++DAT_00A83ED0.Count;
                    }
                } else event.FUN_004C6CB0();
            } else if (!timer || timer->GetTimeLeft() == 0) {
                if (event.Frame == CurrentFrame &&
                    DAT_00B04474[(event.Frame - event.Data.Payload_19.unknown_0D) & 255] !=
                    event.Data.Payload_19.unknown_07) {
                    if (!DAT_00B04880) FUN_0064DEA0(&event);
                    else for (int k = 256; k; --k) FUN_006516F0(k & 255, &event);
                    ++DAT_00A8DAB4;
                    Dialog_005D3490 dialog;
                    dialog.FUN_005D3490(
                        FUN_00734E60(STR_00837DE8, 0, STR_008374A0, 0x165A),
                        FUN_00734E60(STR_00837DF8, 0, STR_008374A0, 0x165B), 0, 0, 0);
                    --DAT_00A8DAB4;
                    return 0;
                }
            }
            event.IsExecuted |= 1;
        }
        int start = 0;
        char mission = -1;
        TargetClass target;
        TargetClass destination;
        for (int j = 0; j < DAT_00A83ED0.Count; ++j) {
            EventClass& command = DAT_00A83ED0.List[(DAT_00A83ED0.unknown_04 + j) & 255];
            bool changed = false;
            if (mission != -1) {
                changed = command.Data.MegaMission.Mission != mission ||
                    command.Data.MegaMission.Target.RTTI != target.RTTI ||
                    command.Data.MegaMission.Target.ID != target.ID ||
                    command.Data.MegaMission.Destination.RTTI != destination.RTTI ||
                    command.Data.MegaMission.Destination.ID != destination.ID;
            }
            mission = command.Data.MegaMission.Mission;
            target = command.Data.MegaMission.Target;
            destination = command.Data.MegaMission.Destination;
            if (changed) {
                int amount = j - start;
                start = j;
                if (amount > 1) FUN_0064CDA0(j - amount, amount);
            } else if (j == DAT_00A83ED0.Count - 1 && j - start + 1 > 1)
                FUN_0064CDA0(start, j - start + 1);
        }
        while (DAT_00A83ED0.Count) {
            DAT_00A83ED0.List[DAT_00A83ED0.unknown_04].FUN_004C6CB0();
            if (!DAT_00A83ED0.Count) break;
            DAT_00A83ED0.unknown_04 = (DAT_00A83ED0.unknown_04 + 1) & 255;
            --DAT_00A83ED0.Count;
        }
    }
    return 1;
}

// FUNCTION: GAMEMD 0x64CD30
void FUN_0064CD30(int first, int count, int id, unsigned char type, const TargetClass* destination)
{
    int last = first + count;
    while (first <= last) {
        EventClass& event = DAT_00A83ED0.List[(DAT_00A83ED0.unknown_04 + first) & 255];
        if (event.Data.MegaMission.Whom.RTTI == type && event.Data.MegaMission.Whom.ID == id) break;
        ++first;
    }
    if (first > last) return;
    DAT_00A83ED0.List[(DAT_00A83ED0.unknown_04 + first) & 255].Data.MegaMission.Destination = *destination;
}

// Declaration: GAMEMD 0x5F6790 (decl; reloc) -- result pointer ECX, vector EDX.
CoordStruct* FUN_005F6790(CoordStruct* out, const DynamicVectorClass<ObjectClass*>* objects);
// Declaration: GAMEMD 0x5F6810 (decl; reloc) -- vector ECX, center EDX, result EAX.
ObjectClass* FUN_005F6810(const DynamicVectorClass<ObjectClass*>* objects, const CoordStruct* center);
// Declaration: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// LIBRARY: GAMEMD 0x7C8B48 (decl; reloc)
extern "C" void __cdecl FUN_007C8B48(void*, unsigned, unsigned,
                                   int (__cdecl*)(const void*, const void*));
// Declaration: GAMEMD 0x652630 (decl; reloc)
int __cdecl FUN_00652630(const void*, const void*);
// GLOBAL: GAMEMD 0xABDC50
extern CellClass InvalidCell;
// GLOBAL: GAMEMD 0xAC6640
extern CellStruct DAT_00AC6640;

static inline CellClass* QueueFormationCell(const CellStruct& cell)
{
    // Both declared return views refer to the same native CellClass at5657A0.
    return reinterpret_cast<CellClass*>(Map_0087F7E8.FUN_005657A0(&cell));
}
static inline int QueueFormationZone(const CellStruct& cell, int zone, bool bridge)
{
    return Map_0087F7E8.FUN_0056D230(cell, zone, bridge);
}
static inline bool QueueFormationUsable(const CellStruct& cell, bool level)
{
    return Map_0087F7E8.FUN_00578460(cell, level);
}
static inline void QueueFormationPath(const CellStruct& from, const CellStruct& to,
                                      ObjectClass* object, bool fromBridge,
                                      bool toBridge, int zone)
{
    // Exact existing six-argument AStar ABI at64D64B: two four-byte coordinate
    // pointers, Foot receiver, two one-byte flags in DWORD argument slots, int.
    DAT_0087E8B8.AttemptPath(&from, &to,
        static_cast<FootClass*>(object), fromBridge, toBridge, zone);
}

static void QueueAssignFormationTarget(int first, int end, ObjectClass* object,
                                       const CellStruct& cell)
{
    TargetClass destination;
    destination.FUN_006E6AB0(QueueFormationCell(cell));
    TargetClass whom;
    whom.FUN_006E6AB0(object);
    // The existing recovered helper preserves retail's inclusive end search.
    FUN_0064CD30(first, end - first, whom.ID, whom.RTTI, &destination);
}

// FUNCTION: GAMEMD 0x64CDA0
void FUN_0064CDA0(int first, int count)
{
    EventClass& initial = DAT_00A83ED0.List[(DAT_00A83ED0.unknown_04 + first) & 255];
    if (initial.Data.MegaMission.Destination.RTTI != 11) return;
    CellClass* destination = initial.Data.MegaMission.Destination.FUN_006E7C20();
    if (!destination || destination == &InvalidCell) return;
    CellStruct goal = destination->MapCoords;
    if (goal.X == DAT_00AC6640.X && goal.Y == DAT_00AC6640.Y) return;

    DynamicVectorClass<ObjectClass*> units;
    int end = first + count;
    for (int j = first; j < end; ++j) {
        EventClass& event = DAT_00A83ED0.List[(DAT_00A83ED0.unknown_04 + j) & 255];
        ObjectClass* object = static_cast<ObjectClass*>(event.Data.MegaMission.Whom.FUN_006E6F20());
        if (object && object->Flags.IsFoot &&
            static_cast<FootClass*>(object)->TubeIndex < 0) units.AddItem(object);
    }
    if (!units.Count) return;

    CoordStruct centerScratch;
    CoordStruct center = *FUN_005F6790(&centerScratch, &units);
    ObjectClass* leader = FUN_005F6810(&units, &center);
    int i;
    GrowPairVector order = { 0, 0, 0, 0, {0, 0, 0}, 0 };
    for (i = 0; i < units.Count; ++i) {
        CoordStruct location = units.Items[i]->vf_18();
        CoordStruct scratch;
        CoordStruct relative = *scratch.FUN_0041C230(location.X - leader->Location.X,
                             location.Y - leader->Location.Y,
                             location.Z - leader->Location.Z);
        int distance = relative.FUN_0041C380();
        if (order.Capacity >= order.Count + 1 ||
            order.Grow_6525A0(order.Capacity ? order.Capacity : 10)) {
            order.Items[order.Count].Key = i + distance * 1000;
            order.Items[order.Count].Value = reinterpret_cast<int>(units.Items[i]);
            ++order.Count;
            order.Sorted = false;
        }
    }
    units.Clear();
    DynamicVectorClass<Cell> cells;
    DynamicVectorClass<bool> done;
    for (i = 0; i < order.Count; ++i) {
        if (!order.Sorted) {
            FUN_007C8B48(order.Items, order.Count, 8, FUN_00652630);
            order.Cached = 0;
            order.Sorted = true;
        }
        units.AddItem(reinterpret_cast<ObjectClass*>(order.Items[i].Value));
        Cell cell;
        cell.X = goal.X;
        cell.Y = goal.Y;
        cells.AddItem(cell);
        done.AddItem(false);
    }
    CellStruct leaderCell = leader->vf_110();
    for (i = 0; i < units.Count; ++i) {
        ObjectClass* object = units.Items[i];
        CellStruct assigned = goal;
        if (!i) {
            QueueFormationCell(goal)->Flags |= 0x8000;
            done.Items[0] = true;
        } else if (!done.Items[i]) {
            CellStruct last = goal;
            CoordStruct location = object->vf_19(0);
            int level = QueueFormationCell(goal)->Level +
                        ((QueueFormationCell(goal)->Flags & 0x100) ? 4 : 0);
            float x = float(goal.X) + 0.5f;
            float y = float(goal.Y) + 0.5f;
            float z = 0.0f;
            float dx = float(short(location.X / 256) - leaderCell.X);
            float dy = float(short(location.Y / 256) - leaderCell.Y);
            float dz = 0.0f;
            double length = FUN_004CAC40(double(dx * dx + dy * dy));
            if (length != 0.0) {
                dx = float(dx / length);
                dy = float(dy / length);
                dz = float(dz / length);
            }
            TechnoTypeClass* type = object->vf_33();
            int zone = QueueFormationZone(goal, type->MovementZone, true);
            bool blocked = false;
            for (int step = 0; ; ++step) {
                x += dx;
                y += dy;
                z += dz;
                CellStruct candidate;
                candidate.X = short(int(x));
                candidate.Y = short(int(y));
                CellClass* cell = QueueFormationCell(candidate);
                if (!QueueFormationUsable(candidate, true)) { assigned = last; break; }
                int candidateZone = QueueFormationZone(candidate, type->MovementZone,
                                                        (cell->Flags & 0x100) != 0);
                int pass = object->vf_107(cell, -1, level, 0, 1);
                if (candidateZone == zone) {
                    if (cell->Flags & 0x8000) {
                        last = candidate;
                    } else {
                        int height = level - cell->Level - ((cell->Flags & 0x100) ? 4 : 0);
                        if (abs(height) >= 3) { assigned = last; break; }
                        if (pass < 4 || pass == 6) {
                            if (blocked) {
                                int distanceX = abs(candidate.X - goal.X);
                                int distanceY = abs(candidate.Y - goal.Y);
                                zone = (distanceX > distanceY ? distanceX : distanceY) + 3;
                                QueueFormationPath(candidate, goal, object,
                                    (QueueFormationCell(candidate)->Flags & 0x100) != 0,
                                    (QueueFormationCell(goal)->Flags & 0x100) != 0, -1);
                                assigned = last;
                            } else { assigned = candidate; }
                            break;
                        }
                        blocked = true;
                    }
                } else { blocked = true; }
                if (step >= 5) { assigned = last; break; }
            }
            cells.Items[i].X = assigned.X;
            cells.Items[i].Y = assigned.Y;
            QueueAssignFormationTarget(first, end, object, assigned);
            QueueFormationCell(assigned)->Flags |= 0x8000;
            done.Items[i] = true;
        }
        for (int j = i + 1; j < units.Count; ++j) {
            if (!done.Items[j]) {
                CellStruct other = units.Items[j]->vf_110();
                CellStruct here = object->vf_110();
                if (other.X == here.X && other.Y == here.Y) {
                    QueueAssignFormationTarget(first, end, units.Items[j], assigned);
                    done.Items[j] = true;
                }
            }
        }
    }
    for (i = 0; i < cells.Count; ++i) QueueFormationCell(cells.Items[i])->Flags &= ~0x8000U;
    delete[] order.Items;
}

// FUNCTION: GAMEMD 0x64D990
// Signed comparison is JLE64D9BD; storage unsignedness is not changed.
// Incoming ECX ignored; callers pass0. ev_7ec9fd5d2d67d92d6624fb6b66bc4d25e4584f29d0c05c1d6817487828cfb137.
void FUN_0064D990(int)
{
    if (!DAT_008B41F8.Count) return;
    int frame = CurrentFrame; // Snapshot matches single64D99B load for this drain.
    while (DAT_008B41F8.Count &&
           ((DAT_008B41F8.List[DAT_008B41F8.unknown_04].IsExecuted & 1) ||
            int(DAT_008B41F8.List[DAT_008B41F8.unknown_04].Frame) < frame)) {
        DAT_008B41F8.unknown_04 = (DAT_008B41F8.unknown_04 + 1) & 0x3FFF;
        --DAT_008B41F8.Count;
    }
}

// FUNCTION: GAMEMD 0x64D9E0
// Direct qualified file writes at64DA4A/64DA96, not virtual dispatch.
// ev_071984b305daa9ce37b6f977e60696355a8ea4653d1518a4ce518f77027b2d72.
void FUN_0064D9E0()
{
    if (CurrentFrame == 0 && Session_00A8B238.GameMode != 0) return;
    int count = 0;
    int index = DAT_008B41F8.unknown_04;
    int remaining = DAT_008B41F8.Count;
    while (remaining > 0) {
        EventClass& event = DAT_008B41F8.List[index & 0x3FFF];
        if (event.Frame == CurrentFrame && !(event.IsExecuted & 1)) ++count;
        ++index;
        --remaining;
    }
    DAT_00A8D58C.CCFileClass::WriteBytes(&count, 4);
    for (int n = 0; n < DAT_008B41F8.Count; ++n) {
        EventClass& event = DAT_008B41F8.List[(DAT_008B41F8.unknown_04 + n) & 0x3FFF];
        if (event.Frame == CurrentFrame && !(event.IsExecuted & 1)) {
            DAT_00A8D58C.CCFileClass::WriteBytes(&event, sizeof(event));
            --count;
        }
    }
}

// FUNCTION: GAMEMD 0x652100
// Empty function.
void __cdecl FUN_00652100()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x64DAB0
// ev_b93f88ff7b2f454cdca7ba21263e7442238140fd1a38e2904d232c1162c3dc6b.
void FUN_0064DAB0()
{
    DAT_00AC51FC = 0;
    for (int nA83DE8 = 0; nA83DE8 < DAT_00A83DE8.Count; ++nA83DE8) {
        // Element prefix is proven by Location and canonical Facing accesses.
        TechnoClass* item = static_cast<TechnoClass**>(DAT_00A83DE8.Items)[nA83DE8];
        CoordStruct location = item->Location;
        DirStruct direction;
        unsigned heading;
        // 4C93D0 returns allfourbytes, includingPadding; ev_6ce7a1b456c12a5926ab40c1239b11b47165549fa89da53c645c985400daa876.
        memcpy(&heading, item->PrimaryFacing.FUN_004C93D0(&direction), sizeof(heading));
        unsigned value = location.X / 10 + ((location.Y / 10) * 65536U) +
                         (((heading >> 7) + 1) >> 1 & 255);
        DAT_00AC51FC = (unsigned(DAT_00AC51FC) << 1 | unsigned(DAT_00AC51FC) >> 31) + value;
    }
    for (int n8B4108 = 0; n8B4108 < DAT_008B4108.Count; ++n8B4108) {
        // Element prefix is proven by Location and canonical Facing accesses.
        TechnoClass* item = static_cast<TechnoClass**>(DAT_008B4108.Items)[n8B4108];
        CoordStruct location = item->Location;
        DirStruct direction;
        unsigned heading;
        // 4C93D0 returns allfourbytes, includingPadding; ev_6ce7a1b456c12a5926ab40c1239b11b47165549fa89da53c645c985400daa876.
        memcpy(&heading, item->PrimaryFacing.FUN_004C93D0(&direction), sizeof(heading));
        unsigned value = location.X / 10 + ((location.Y / 10) * 65536U) +
                         (((heading >> 7) + 1) >> 1 & 255);
        memcpy(&heading, item->SecondaryFacing.FUN_004C93D0(&direction), sizeof(heading));
        value += ((heading >> 7) + 1) >> 1 & 255;
        DAT_00AC51FC = (unsigned(DAT_00AC51FC) << 1 | unsigned(DAT_00AC51FC) >> 31) + value;
    }
    for (int nA8EB40 = 0; nA8EB40 < DAT_00A8EB40.Count; ++nA8EB40) {
        // Element prefix is proven by Location and canonical Facing accesses.
        TechnoClass* item = static_cast<TechnoClass**>(DAT_00A8EB40.Items)[nA8EB40];
        CoordStruct location = item->Location;
        DirStruct direction;
        unsigned heading;
        // 4C93D0 returns allfourbytes, includingPadding; ev_6ce7a1b456c12a5926ab40c1239b11b47165549fa89da53c645c985400daa876.
        memcpy(&heading, item->PrimaryFacing.FUN_004C93D0(&direction), sizeof(heading));
        unsigned value = location.X / 10 + ((location.Y / 10) * 65536U) +
                         (((heading >> 7) + 1) >> 1 & 255);
        DAT_00AC51FC = (unsigned(DAT_00AC51FC) << 1 | unsigned(DAT_00AC51FC) >> 31) + value;
    }
    for (int h = 0; h < DAT_00A80238; ++h)
        DAT_00AC51FC = (unsigned(DAT_00AC51FC) << 1 | unsigned(DAT_00AC51FC) >> 31) +
                      DAT_00A8022C[h]->MapIsClear;
    for (int layer = 0; layer < 5; ++layer) {
        for (int n = 0; n < DAT_008A0360[layer].Count; ++n) {
            ObjectClass* item = DAT_008A0360[layer].Items[n];
            if (item->vf_11() == 4 && item->vf_rtti_4() == -2) continue;
            CoordStruct location = item->Location;
            int type = item->vf_11();
            DAT_00AC51FC = (unsigned(DAT_00AC51FC) << 1 | unsigned(DAT_00AC51FC) >> 31) +
                          location.X / 10 + type + (location.Y / 10) * 65536U;
        }
    }
    for (int n = 0; n < DAT_0087F778.Count; ++n) {
        ObjectClass* item = static_cast<ObjectClass**>(DAT_0087F778.Items)[n];
        if (item->vf_11() == 4 && item->vf_rtti_4() == -2) continue;
        CoordStruct location = item->Location;
        int type = item->vf_11();
        DAT_00AC51FC = (unsigned(DAT_00AC51FC) << 1 | unsigned(DAT_00AC51FC) >> 31) +
                      location.X / 10 + type + (location.Y / 10) * 65536U;
    }
    int random = DAT_00A8B230->unknown_0218.Random();
    DAT_00AC51FC = (unsigned(DAT_00AC51FC) << 1 | unsigned(DAT_00AC51FC) >> 31) + random;
    FUN_00650A90(CurrentFrame % 256);
}

// Declaration: GAMEMD 0x008373A4 -- string reference
extern const char STR_008373A4[];
// Declaration: GAMEMD 0x00837FA8 -- string reference
extern const char STR_00837FA8[];
// Declaration: GAMEMD 0x00837FD8 -- string reference
extern const char STR_00837FD8[];
// Declaration: GAMEMD 0x00838008 -- string reference
extern const char STR_00838008[];
// Declaration: GAMEMD 0x00838038 -- string reference
extern const char STR_00838038[];
// Declaration: GAMEMD 0x00838064 -- string reference
extern const char STR_00838064[];
// Declaration: GAMEMD 0x0083809C -- string reference
extern const char STR_0083809C[];
// Declaration: GAMEMD 0x008380D0 -- string reference
extern const char STR_008380D0[];
// Declaration: GAMEMD 0x00838104 -- string reference
extern const char STR_00838104[];
// Declaration: GAMEMD 0x00838138 -- string reference
extern const char STR_00838138[];
// Declaration: GAMEMD 0x00838170 -- string reference
extern const char STR_00838170[];
// Declaration: GAMEMD 0x008381A0 -- string reference
extern const char STR_008381A0[];
// Declaration: GAMEMD 0x008381D0 -- string reference
extern const char STR_008381D0[];
// Declaration: GAMEMD 0x0083820C -- string reference
extern const char STR_0083820C[];
// Declaration: GAMEMD 0x00838244 -- string reference
extern const char STR_00838244[];
// Declaration: GAMEMD 0x00838274 -- string reference
extern const char STR_00838274[];
// Declaration: GAMEMD 0x008382AC -- string reference
extern const char STR_008382AC[];
// Declaration: GAMEMD 0x008382DC -- string reference
extern const char STR_008382DC[];
// Declaration: GAMEMD 0x0083830C -- string reference
extern const char STR_0083830C[];
// Declaration: GAMEMD 0x00838340 -- string reference
extern const char STR_00838340[];
// Declaration: GAMEMD 0x00838378 -- string reference
extern const char STR_00838378[];
// Declaration: GAMEMD 0x008383A8 -- string reference
extern const char STR_008383A8[];
// Declaration: GAMEMD 0x008383D8 -- string reference
extern const char STR_008383D8[];
// Declaration: GAMEMD 0x00838408 -- string reference
extern const char STR_00838408[];
// Declaration: GAMEMD 0x00838438 -- string reference
extern const char STR_00838438[];
// Declaration: GAMEMD 0x0083846C -- string reference
extern const char STR_0083846C[];
// Declaration: GAMEMD 0x00838498 -- string reference
extern const char STR_00838498[];
// Declaration: GAMEMD 0x008384C8 -- string reference
extern const char STR_008384C8[];
// Declaration: GAMEMD 0x008384F8 -- string reference
extern const char STR_008384F8[];
// Declaration: GAMEMD 0x0083852C -- string reference
extern const char STR_0083852C[];
// Declaration: GAMEMD 0x00838558 -- string reference
extern const char STR_00838558[];
// Declaration: GAMEMD 0x0083858C -- string reference
extern const char STR_0083858C[];
// Declaration: GAMEMD 0x008385C0 -- string reference
extern const char STR_008385C0[];
// Declaration: GAMEMD 0x008385F4 -- string reference
extern const char STR_008385F4[];
// Declaration: GAMEMD 0x00838620 -- string reference
extern const char STR_00838620[];
// Declaration: GAMEMD 0x00838650 -- string reference
extern const char STR_00838650[];
// Declaration: GAMEMD 0x00838688 -- string reference
extern const char STR_00838688[];
// Declaration: GAMEMD 0x008386B8 -- string reference
extern const char STR_008386B8[];
// Declaration: GAMEMD 0x008386EC -- string reference
extern const char STR_008386EC[];
// Declaration: GAMEMD 0x0083871C -- string reference
extern const char STR_0083871C[];
// Declaration: GAMEMD 0x00838754 -- string reference
extern const char STR_00838754[];
// Declaration: GAMEMD 0x00838780 -- string reference
extern const char STR_00838780[];
// Declaration: GAMEMD 0x008387B4 -- string reference
extern const char STR_008387B4[];
// Declaration: GAMEMD 0x008387E8 -- string reference
extern const char STR_008387E8[];
// Declaration: GAMEMD 0x008387F8 -- string reference
extern const char STR_008387F8[];
// Declaration: GAMEMD 0x00838828 -- string reference
extern const char STR_00838828[];
// Declaration: GAMEMD 0x00838838 -- string reference
extern const char STR_00838838[];
// Declaration: GAMEMD 0x008388F8 -- string reference
extern const char STR_008388F8[];
// Declaration: GAMEMD 0x00838908 -- string reference
extern const char STR_00838908[];
// Declaration: GAMEMD 0x0083892C -- string reference
extern const char STR_0083892C[];
// Declaration: GAMEMD 0x00838940 -- string reference
extern const char STR_00838940[];
// Declaration: GAMEMD 0x00838958 -- string reference
extern const char STR_00838958[];
// Declaration: GAMEMD 0x00838974 -- string reference
extern const char STR_00838974[];
// Declaration: GAMEMD 0x00838990 -- string reference
extern const char STR_00838990[];
// Declaration: GAMEMD 0x008389AC -- string reference
extern const char STR_008389AC[];
// Declaration: GAMEMD 0x008389C8 -- string reference
extern const char STR_008389C8[];
// Declaration: GAMEMD 0x008389E4 -- string reference
extern const char STR_008389E4[];
// Declaration: GAMEMD 0x00838A00 -- string reference
extern const char STR_00838A00[];
// Declaration: GAMEMD 0x00838A1C -- string reference
extern const char STR_00838A1C[];
// Declaration: GAMEMD 0x00838A38 -- string reference
extern const char STR_00838A38[];
// Declaration: GAMEMD 0x00838A6C -- string reference
extern const char STR_00838A6C[];
// Declaration: GAMEMD 0x00838A80 -- string reference
extern const char STR_00838A80[];
// Declaration: GAMEMD 0x00838A90 -- string reference
extern const char STR_00838A90[];
// Declaration: GAMEMD 0x00838AEC -- string reference
extern const char STR_00838AEC[];
// Declaration: GAMEMD 0x00838AFC -- string reference
extern const char STR_00838AFC[];
// Declaration: GAMEMD 0x00838B38 -- string reference
extern const char STR_00838B38[];
// Declaration: GAMEMD 0x00838B4C -- string reference
extern const char STR_00838B4C[];
// Declaration: GAMEMD 0x00838B90 -- string reference
extern const char STR_00838B90[];
// Declaration: GAMEMD 0x00838BCC -- string reference
extern const char STR_00838BCC[];
// Declaration: GAMEMD 0x00838BDC -- string reference
extern const char STR_00838BDC[];
// Declaration: GAMEMD 0x00838C60 -- string reference
extern const char STR_00838C60[];
// Declaration: GAMEMD 0x00838C98 -- string reference
extern const char STR_00838C98[];
// Declaration: GAMEMD 0x00838CA8 -- string reference
extern const char STR_00838CA8[];
// Declaration: GAMEMD 0x00838D08 -- string reference
extern const char STR_00838D08[];
// Declaration: GAMEMD 0x00838D44 -- string reference
extern const char STR_00838D44[];
// Declaration: GAMEMD 0x00838D54 -- string reference
extern const char STR_00838D54[];
// Declaration: GAMEMD 0x00838DC8 -- string reference
extern const char STR_00838DC8[];
// Declaration: GAMEMD 0x00838EB0 -- string reference
extern const char STR_00838EB0[];

// Declaration: GAMEMD 0x5BC450 -- existing matched erased table getter.
int FUN_005BC450(int);
// GLOBAL: GAMEMD 0x00A83C98
extern DynamicVectorClassLayout DAT_00A83C98;
// GLOBAL: GAMEMD 0x00A80228
extern DynamicVectorClassLayout DAT_00A80228;
// GLOBAL: GAMEMD 0x00A83CE0
extern DynamicVectorClassLayout DAT_00A83CE0;
// GLOBAL: GAMEMD 0x00A8E348
extern DynamicVectorClassLayout DAT_00A8E348;
// GLOBAL: GAMEMD 0x00A83C68
extern DynamicVectorClassLayout DAT_00A83C68;
// GLOBAL: GAMEMD 0x00A8B218
extern DynamicVectorClassLayout DAT_00A8B218;
// GLOBAL: GAMEMD 0x00A8E9A8
extern DynamicVectorClassLayout DAT_00A8E9A8;
// GLOBAL: GAMEMD 0x008B4150
extern DynamicVectorClassLayout DAT_008B4150;
// GLOBAL: GAMEMD 0x00A8E8D0
extern DynamicVectorClassLayout DAT_00A8E8D0;
// GLOBAL: GAMEMD 0x00A8ECA0
extern DynamicVectorClassLayout DAT_00A8ECA0;
// GLOBAL: GAMEMD 0x008B40E8
extern DynamicVectorClassLayout DAT_008B40E8;
// GLOBAL: GAMEMD 0x008B41C8
extern DynamicVectorClassLayout DAT_008B41C8;
// GLOBAL: GAMEMD 0x008872B0
extern DynamicVectorClassLayout DAT_008872B0;
// GLOBAL: GAMEMD 0x00B0E780
extern DynamicVectorClassLayout DAT_00B0E780;
// GLOBAL: GAMEMD 0x00B0E720
extern DynamicVectorClassLayout DAT_00B0E720;
// GLOBAL: GAMEMD 0x008B4178
extern DynamicVectorClassLayout DAT_008B4178;
// GLOBAL: GAMEMD 0x00A8EAE8
extern DynamicVectorClassLayout DAT_00A8EAE8;
// GLOBAL: GAMEMD 0x00B0E658
extern DynamicVectorClassLayout DAT_00B0E658;
// GLOBAL: GAMEMD 0x00B0F1A0
extern DynamicVectorClassLayout DAT_00B0F1A0;
// GLOBAL: GAMEMD 0x00A83E30
extern DynamicVectorClassLayout DAT_00A83E30;
// GLOBAL: GAMEMD 0x00A8EB28
extern DynamicVectorClassLayout DAT_00A8EB28;
// GLOBAL: GAMEMD 0x00887388
extern DynamicVectorClassLayout DAT_00887388;
// GLOBAL: GAMEMD 0x008874C0
extern DynamicVectorClassLayout DAT_008874C0;
// GLOBAL: GAMEMD 0x00887568
extern DynamicVectorClassLayout DAT_00887568;
// GLOBAL: GAMEMD 0x00A83D98
extern DynamicVectorClassLayout DAT_00A83D98;
// GLOBAL: GAMEMD 0x00A83DC8
extern DynamicVectorClassLayout DAT_00A83DC8;
// GLOBAL: GAMEMD 0x00A80208
extern DynamicVectorClassLayout DAT_00A80208;
// GLOBAL: GAMEMD 0x00A83D68
extern DynamicVectorClassLayout DAT_00A83D68;
// GLOBAL: GAMEMD 0x00A83C80
extern DynamicVectorClassLayout DAT_00A83C80;
// GLOBAL: GAMEMD 0x00A8ED40
extern DynamicVectorClassLayout DAT_00A8ED40;
// GLOBAL: GAMEMD 0x00B72608
extern DynamicVectorClassLayout DAT_00B72608;
// GLOBAL: GAMEMD 0x00A8EC18
extern DynamicVectorClassLayout DAT_00A8EC18;
// GLOBAL: GAMEMD 0x00A83D80
extern DynamicVectorClassLayout DAT_00A83D80;
// GLOBAL: GAMEMD 0x00ABCA10
extern DynamicVectorClassLayout DAT_00ABCA10;
// GLOBAL: GAMEMD 0x008B4190
extern DynamicVectorClassLayout DAT_008B4190;
// GLOBAL: GAMEMD 0x008B4138
extern DynamicVectorClassLayout DAT_008B4138;
// GLOBAL: GAMEMD 0x008B4120
extern DynamicVectorClassLayout DAT_008B4120;
// GLOBAL: GAMEMD 0x00B0F4E8
extern DynamicVectorClassLayout DAT_00B0F4E8;
// GLOBAL: GAMEMD 0x008A3870
extern DynamicVectorClassLayout DAT_008A3870;

struct QueueTargetDiagnostic
{
    const char* Name;
    int X;
    int Y;
};
static inline QueueTargetDiagnostic QueueDiagnosticTarget(AbstractClass* target)
{
    QueueTargetDiagnostic result;
    result.Name = STR_008373A4;
    result.X = 0;
    result.Y = 0;
    if (target) {
        // Native performs two independent virtual calls, not a cached location.
        result.X = target->vf_18().X;
        result.Y = target->vf_18().Y;
        result.Name = static_cast<const char*>(FUN_0040DCB0(target->vf_11()));
    }
    return result;
}

static inline void QueueDumpLogicType(FILE* file, ObjectClass* item, const char* format)
{
    const char* name = item->vf_34()->ID;
    int index = item->vf_34()->vf_16();
    fprintf(file, format, index, name);
}

static inline void QueueDumpCRCEntries(FILE* file, Obj_004A1D30* checksum,
                                       const DynamicVectorClassLayout& objects,
                                       bool skipRemoved)
{
    // Existing canonical opaque container prefix: Items+4, Count+10.
    // Complete template specialization remains unknown; native vf13 on every
    // element proves the shared AbstractClass checksum interface boundary.
    for (int i = 0; i < objects.Count; ++i) {
        AbstractClass* object = static_cast<AbstractClass**>(objects.Items)[i];
        if (skipRemoved && object->vf_rtti_4() == -2) continue;
        object->vf_13(checksum);
        // Native copies all12 bytes; the format prints the first DWORD.
        fprintf(file, STR_008387E8, i, *checksum);
    }
}

// FUNCTION: GAMEMD 0x64DEA0
void FUN_0064DEA0(EventClass* offending)
{
char filename[512];
sprintf(filename, STR_00838EB0, DAT_00A83D4C->ArrayIndex);
FUN_004068E0(STR_00838E90, filename);
Obj_005BCC40* logger = reinterpret_cast<Obj_005BCC40*>(FUN_005BC450(4));
logger->FUN_005BCC90();
logger->FUN_005BCC40(0, 0);
FILE* file = fopen(filename, DAT_0081D988);
if (!file) {
    FUN_004068E0(STR_00838E4C, GetLastError(), file);
    return;
}
    fprintf(file, STR_00838E40);
    fprintf(file, STR_00838E30, FUN_0074fdc0());
    fprintf(file, STR_00838E18, DAT_00A8ECE0.FUN_0074FAE0());
    char first[128];
    char second[128];
    char third[128];
    first[0] = 0;
    FUN_00777AC0(first, 128);
    const char* secondText = FUN_00777B60(second, 128);
    const char* thirdText = FUN_00777B30(third, 128);
    fprintf(file, STR_00821F0C, thirdText, secondText, first);
    int code = 5;
    char flag = 0;
    FUN_004E6150(&code, &flag, 0, 0);
    fprintf(file, STR_00821EE4, FUN_004E62B0(), flag ? DAT_00821F08 : DAT_00821F04, STR_0084E865);
    fprintf(file, STR_0081D970, CurrentFrame);
    fprintf(file, STR_0081D95C, DAT_00ABCD4C ? DAT_00ABCD48 / DAT_00ABCD4C : 0);
    fprintf(file, STR_0081D948, DAT_00A8B568);
    fprintf(file, STR_0081D930, DAT_00A8DB9C);
    fprintf(file, STR_0081D918, DAT_00A8EB60);
    fprintf(file, STR_00838E04, DAT_00A8B554);
    if (Interface_00887628) {
        for (int i = 0; i < Interface_00887628->GetNumLocalAddresses(); ++i) {
            unsigned char* address = Interface_00887628->GetLocalAddress(i);
            if (address) fprintf(file, STR_0081D8FC, address[0], address[1], address[2], address[3]);
        }
    }
    for (int i = 0; i < 8; ++i) {
        ConnStat& stat = ConnStats_00A8B574[i];
        if (!stat.Name[0]) continue;
        NetworkNumberType network;
        NodeAddressType node;
        stat.Address.FUN_0053EDA0(network, node);
        fprintf(file, STR_0081D8F0, stat.Name);
        fprintf(file, STR_00838DEC, node.Node[0], node.Node[1], node.Node[2], node.Node[3]);
        fprintf(file, STR_0081D8C8, stat.AvgMs);
        fprintf(file, STR_0081D8B4, stat.PeakMs);
        fprintf(file, STR_0081D8A4, stat.unknown_44);
        fprintf(file, STR_0081D88C, stat.unknown_54);
        fprintf(file, STR_0081D870, stat.unknown_58);
        fprintf(file, STR_0081D864, stat.unknown_48);
        fprintf(file, STR_0081D850, stat.unknown_4C);
    }

    for (i = 0; i < 256; ++i) fprintf(file, STR_00838DE0, i, DAT_00B04474[i]);
    fprintf(file, STR_00838DC8);
    for (int h = 0; h < DAT_00A80238; ++h) {
        DAT_00AC51FC = 0;
        HouseClass* house = DAT_00A8022C[h];
        int color = house->ColorSchemeIndex;
        int type = house->Type->ArrayIndex;
        const char* name = FUN_007350C0(reinterpret_cast<const wchar_t*>(house->UIName));
        fprintf(file, STR_00838D54, name, house->IsHumanPlayer,
                ColorSchemeArray.Items[color]->Name, house->ArrayIndex,
                DAT_00A83C9C[type]->Name, house->Edge, house->StartingAllies,
                house->StartingPoint, static_cast<unsigned char>(house->Visionary),
                house->MapIsClear);
        logger->FUN_005BD1F0(STR_00838D44, house->Type->ID.Data, DAT_00AC51FC);
    }

{
// Body phase: per-house infantry details, then logger checksum line.
for (int houseIndex = 0; houseIndex < DAT_00A80238; ++houseIndex) {
    HouseClass* house = DAT_00A8022C[houseIndex];
    DAT_00AC51FC = 0;
    fprintf(file, STR_00838D08, house->Type->ID.Data, house->ArrayIndex);
    for (int i = 0; i < DAT_00A83DE8.Count; ++i) {
        InfantryClass* item = static_cast<InfantryClass**>(DAT_00A83DE8.Items)[i];
        if (item->Owner != house) continue;
        CoordStruct location = item->Location;
        unsigned heading = QueueLogHeading(&item->PrimaryFacing);
        unsigned contribution = unsigned(location.X / 10) +
            unsigned(location.Y / 10) * 65536U + heading;
        // Native rotates the existing value left one, then adds.
        DAT_00AC51FC = (unsigned(DAT_00AC51FC) << 1 | unsigned(DAT_00AC51FC) >> 31) + contribution;
        QueueTargetDiagnostic target = QueueDiagnosticTarget(item->Target);
        QueueTargetDiagnostic destination =
            QueueDiagnosticTarget(static_cast<AbstractClass*>(item->Destination));
        unsigned facing = QueueLogHeading(&item->PrimaryFacing);
        InfantryTypeClass* type = item->Type;
        int speed = int(item->SpeedPercentage * DAT_007E1710);
        int typeIndex = type->ArrayIndex;
        const char* typeName = type->ID;
        int mission = item->vf_97();
        // Evaluate Y before X, preserving the observed callback sequence.
        int y = item->vf_18().Y;
        int x = item->vf_18().X;
        fprintf(file, STR_00838CA8, x, y, facing, mission, typeIndex,
                typeName, target.Name, target.X, target.Y, speed,
                destination.Name, destination.X, destination.Y);
    }
    logger->FUN_005BD1F0(STR_00838C98, house->Type->ID.Data, DAT_00AC51FC);
}

}

{
// Body phase: per-house unit details, then logger checksum line.
for (int houseIndex = 0; houseIndex < DAT_00A80238; ++houseIndex) {
    HouseClass* house = DAT_00A8022C[houseIndex];
    DAT_00AC51FC = 0;
    fprintf(file, STR_00838C60, house->Type->ID.Data, house->ArrayIndex);
    for (int i = 0; i < DAT_008B4108.Count; ++i) {
        UnitClass* item = static_cast<UnitClass**>(DAT_008B4108.Items)[i];
        if (item->Owner != house) continue;
        CoordStruct location = item->Location;
        unsigned heading = QueueLogHeading(&item->PrimaryFacing);
        unsigned secondaryHeading = QueueLogHeading(&item->SecondaryFacing);
        unsigned contribution = unsigned(location.X / 10) +
            unsigned(location.Y / 10) * 65536U + heading + secondaryHeading;
        // Native rotates the existing value left one, then adds.
        DAT_00AC51FC = (unsigned(DAT_00AC51FC) << 1 | unsigned(DAT_00AC51FC) >> 31) + contribution;
        QueueTargetDiagnostic target = QueueDiagnosticTarget(item->Target);
        QueueTargetDiagnostic destination =
            QueueDiagnosticTarget(static_cast<AbstractClass*>(item->Destination));
        // Native resolves all three COM smart-pointer accesses before facing
        // callbacks, then invokes speed/index/track in that order.
        ILocomotion* speedInterface = QueueLogLocomotor(item);
        ILocomotion* indexInterface = QueueLogLocomotor(item);
        ILocomotion* trackInterface = QueueLogLocomotor(item);
        const char* typeName = static_cast<UnitTypeClass*>(item->Type)->ID;
        unsigned secondaryFacing = QueueLogHeading(&item->SecondaryFacing);
        unsigned facing = QueueLogHeading(&item->PrimaryFacing);
        int speed = speedInterface->GetSpeedAccum();
        int trackIndex = indexInterface->GetTrackIndex();
        int trackNumber = trackInterface->GetTrackNumber();
        int typeIndex = static_cast<UnitTypeClass*>(item->Type)->ArrayIndex;
        int mission = item->vf_97();
        // Evaluate Y before X, preserving the observed callback sequence.
        int y = item->vf_18().Y;
        int x = item->vf_18().X;
        fprintf(file, STR_00838BDC, x, y, facing, secondaryFacing, mission,
                typeIndex, typeName, target.Name, target.X, target.Y,
                destination.Name, destination.X, destination.Y,
                trackNumber, trackIndex, speed);
    }
    logger->FUN_005BD1F0(STR_00838BCC, house->Type->ID.Data, DAT_00AC51FC);
}

}

{
// Body phase: per-house building details, then logger checksum line.
for (int houseIndex = 0; houseIndex < DAT_00A80238; ++houseIndex) {
    HouseClass* house = DAT_00A8022C[houseIndex];
    DAT_00AC51FC = 0;
    fprintf(file, STR_00838B90, house->Type->ID.Data, house->ArrayIndex);
    for (int i = 0; i < DAT_00A8EB40.Count; ++i) {
        BuildingClass* item = static_cast<BuildingClass**>(DAT_00A8EB40.Items)[i];
        if (item->Owner != house) continue;
        CoordStruct location = item->Location;
        unsigned heading = QueueLogHeading(&item->PrimaryFacing);
        unsigned contribution = unsigned(location.X / 10) +
            unsigned(location.Y / 10) * 65536U + heading;
        // Native rotates the existing value left one, then adds.
        DAT_00AC51FC = (unsigned(DAT_00AC51FC) << 1 | unsigned(DAT_00AC51FC) >> 31) + contribution;
        QueueTargetDiagnostic target = QueueDiagnosticTarget(item->Target);
        unsigned facing = QueueLogHeading(&item->PrimaryFacing);
        BuildingTypeClass* type = item->Type;
        int typeIndex = type->ArrayIndex;
        const char* typeName = type->ID;
        int mission = item->vf_97();
        // Evaluate Y before X, preserving the observed callback sequence.
        int y = item->vf_18().Y;
        int x = item->vf_18().X;
        fprintf(file, STR_00838B4C, x, y, facing, mission, typeIndex,
                typeName, target.Name, target.X, target.Y);
    }
    logger->FUN_005BD1F0(STR_00838B38, house->Type->ID.Data, DAT_00AC51FC);
}

}

{
// Body phase: per-house aircraft details, then logger checksum line.
for (int houseIndex = 0; houseIndex < DAT_00A80238; ++houseIndex) {
    HouseClass* house = DAT_00A8022C[houseIndex];
    DAT_00AC51FC = 0;
    fprintf(file, STR_00838AFC, house->Type->ID.Data, house->ArrayIndex);
    for (int i = 0; i < DAT_00A8E390.Count; ++i) {
        AircraftClass* item = static_cast<AircraftClass**>(DAT_00A8E390.Items)[i];
        if (item->Owner != house) continue;
        CoordStruct location = item->Location;
        unsigned heading = QueueLogHeading(&item->PrimaryFacing);
        unsigned contribution = unsigned(location.X / 10) +
            unsigned(location.Y / 10) * 65536U + heading;
        // Native rotates the existing value left one, then adds.
        DAT_00AC51FC = (unsigned(DAT_00AC51FC) << 1 | unsigned(DAT_00AC51FC) >> 31) + contribution;
        QueueTargetDiagnostic target = QueueDiagnosticTarget(item->Target);
        unsigned facing = QueueLogHeading(&item->PrimaryFacing);
        AircraftTypeClass* type = static_cast<AircraftTypeClass*>(item->Type);
        int typeIndex = type->ArrayIndex;
        const char* typeName = type->ID;
        int mission = item->vf_97();
        // Evaluate Y before X, preserving the observed callback sequence.
        int y = item->vf_18().Y;
        int x = item->vf_18().X;
        fprintf(file, STR_00838B4C, x, y, facing, mission, typeIndex,
                typeName, target.Name, target.X, target.Y);
    }
    logger->FUN_005BD1F0(STR_00838AEC, house->Type->ID.Data, DAT_00AC51FC);
}

}

{
DAT_00AC51FC = 0;
for (int layer = 0; layer < 5; ++layer) {
    fprintf(file, STR_00838AD4, layer);
    for (int i = 0; i < DAT_008A0360[layer].Count; ++i) {
        ObjectClass* item = DAT_008A0360[layer].Items[i];
        if (item->vf_11() == 4 && item->vf_rtti_4() == -2) continue;
        CoordStruct location = item->Location;
        int rtti = item->vf_11();
        unsigned contribution = unsigned(location.X / 10) +
            unsigned(location.Y / 10) * 65536U + unsigned(rtti);
        DAT_00AC51FC = (unsigned(DAT_00AC51FC) << 1 | unsigned(DAT_00AC51FC) >> 31) + contribution;
        // Native rereads Location after the RTTI callback for printed position.
        CoordStruct printed = item->Location;
        unsigned position = unsigned(printed.X / 10) +
                            unsigned(printed.Y / 10) * 65536U;
        fprintf(file, STR_00838AC4, i, position);
        if (item->vf_11() == 43 || item->vf_11() == 19) {
            const char* name = static_cast<const char*>(FUN_0040DCB0(item->vf_11()));
            fprintf(file, STR_00838AA0, name, 0);
        } else {
            const char* typeName = item->vf_34()->ID;
            int typeIndex = item->vf_34()->vf_16();
            const char* name = static_cast<const char*>(FUN_0040DCB0(item->vf_11()));
            fprintf(file, STR_00838AB0, name, typeIndex, typeName);
        }
        HouseClass* owner = item->vf_15();
        if (owner) fprintf(file, STR_00838A90, owner->Type->ID.Data, owner->ArrayIndex);
        else fprintf(file, STR_00838A80);
    }
}
logger->FUN_005BD1F0(STR_00838A6C, DAT_00AC51FC);

}

{
// Body continuation.
fprintf(file, STR_00838A54);
DAT_00AC51FC = 0;
for (int i = 0; i < DAT_0087F778.Count; ++i) {
    ObjectClass* item = static_cast<ObjectClass**>(DAT_0087F778.Items)[i];
    if (item->vf_11() == 4 && item->vf_rtti_4() == -2) continue;
    CoordStruct location = item->Location;
    int rtti = item->vf_11();
    unsigned contribution = unsigned(location.X / 10) +
        unsigned(location.Y / 10) * 65536U + unsigned(rtti);
    DAT_00AC51FC = (unsigned(DAT_00AC51FC) << 1 | unsigned(DAT_00AC51FC) >> 31) + contribution;
    CoordStruct printed = item->Location;
    unsigned position = unsigned(printed.X / 10) + unsigned(printed.Y / 10) * 65536U;
    fprintf(file, STR_00838AC4, i, position);
    // Repeated virtual queries are observable: retain the actual if-chain.
    if (item->vf_11() == 2) QueueDumpLogicType(file, item, STR_00838A38);
    else if (item->vf_11() == 4) QueueDumpLogicType(file, item, STR_00838A1C);
    else if (item->vf_11() == 6) QueueDumpLogicType(file, item, STR_00838A00);
    else if (item->vf_11() == 8) QueueDumpLogicType(file, item, STR_008389E4);
    else if (item->vf_11() == 15) QueueDumpLogicType(file, item, STR_008389C8);
    else if (item->vf_11() == 20) QueueDumpLogicType(file, item, STR_008389AC);
    else if (item->vf_11() == 29) QueueDumpLogicType(file, item, STR_00838990);
    else if (item->vf_11() == 36) QueueDumpLogicType(file, item, STR_00838974);
    else if (item->vf_11() == 1) QueueDumpLogicType(file, item, STR_00838958);
    HouseClass* owner = item->vf_15();
    if (owner) fprintf(file, STR_0083894C, owner->Type->ID.Data);
    else fprintf(file, STR_00838A80);
}
logger->FUN_005BD1F0(STR_00838940, DAT_00AC51FC);
int random = DAT_00A8B230->unknown_0218.Random();
logger->FUN_005BD1F0(STR_0083892C, random);
fprintf(file, STR_00838918, random);
logger->FUN_005BD1F0(STR_00838908, CurrentFrame);
fprintf(file, STR_008388F8, CurrentFrame);

}
    if (offending) {
        fprintf(file, STR_008388E4);
        fprintf(file, STR_008388D0, offending->Type);
        fprintf(file, STR_008388BC, offending->Frame);
        fprintf(file, STR_008388A8, offending->HouseIndex);
        fprintf(file, STR_00838894, offending->Data.Payload_19.unknown_07);
        fprintf(file, STR_00838880, offending->Data.Payload_19.unknown_0B);
        fprintf(file, STR_0083886C, offending->Data.Payload_19.unknown_0D);
    }
Obj_004A1D30* checksum = new Obj_004A1D30();
fprintf(file, STR_00838838);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
// Loop allocation0064f2b9; Items0x00A83C9C, Count0x00A83CA8.
QueueDumpCRCEntries(file, checksum, DAT_00A83C98, false);
fprintf(file, STR_008387B4);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064f369; Items0x00A8022C, Count0x00A80238.
QueueDumpCRCEntries(file, checksum, DAT_00A80228, false);
fprintf(file, STR_00838780);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064f3f6; Items0x00A83CE4, Count0x00A83CF0.
QueueDumpCRCEntries(file, checksum, DAT_00A83CE0, false);
fprintf(file, STR_00838754);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064f483; Items0x008B410C, Count0x008B4118.
QueueDumpCRCEntries(file, checksum, DAT_008B4108, false);
fprintf(file, STR_0083871C);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064f510; Items0x00A8E34C, Count0x00A8E358.
QueueDumpCRCEntries(file, checksum, DAT_00A8E348, false);
fprintf(file, STR_008386EC);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064f59d; Items0x00A83DEC, Count0x00A83DF8.
QueueDumpCRCEntries(file, checksum, DAT_00A83DE8, false);
fprintf(file, STR_008386B8);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064f62a; Items0x00A83C6C, Count0x00A83C78.
QueueDumpCRCEntries(file, checksum, DAT_00A83C68, false);
fprintf(file, STR_00838688);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064f6b7; Items0x00A8EB44, Count0x00A8EB50.
QueueDumpCRCEntries(file, checksum, DAT_00A8EB40, false);
fprintf(file, STR_00838650);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064f744; Items0x00A8B21C, Count0x00A8B228.
QueueDumpCRCEntries(file, checksum, DAT_00A8B218, false);
fprintf(file, STR_00838620);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064f7d1; Items0x00A8E394, Count0x00A8E3A0.
QueueDumpCRCEntries(file, checksum, DAT_00A8E390, false);
fprintf(file, STR_008385F4);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064f85e; Items0x00A8E9AC, Count0x00A8E9B8.
QueueDumpCRCEntries(file, checksum, DAT_00A8E9A8, true);
fprintf(file, STR_008385C0);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064f8fc; Items0x008B4154, Count0x008B4160.
QueueDumpCRCEntries(file, checksum, DAT_008B4150, false);
fprintf(file, STR_0083858C);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064f989; Items0x00A8E8D4, Count0x00A8E8E0.
QueueDumpCRCEntries(file, checksum, DAT_00A8E8D0, false);
fprintf(file, STR_00838558);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064fa16; Items0x00A8ECA4, Count0x00A8ECB0.
QueueDumpCRCEntries(file, checksum, DAT_00A8ECA0, false);
fprintf(file, STR_0083852C);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064faa3; Items0x008B40EC, Count0x008B40F8.
QueueDumpCRCEntries(file, checksum, DAT_008B40E8, false);
fprintf(file, STR_008384F8);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064fb30; Items0x008B41CC, Count0x008B41D8.
QueueDumpCRCEntries(file, checksum, DAT_008B41C8, false);
fprintf(file, STR_008384C8);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064fbbd; Items0x008872B4, Count0x008872C0.
QueueDumpCRCEntries(file, checksum, DAT_008872B0, false);
fprintf(file, STR_00838498);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064fc4a; Items0x00B0E784, Count0x00B0E790.
QueueDumpCRCEntries(file, checksum, DAT_00B0E780, false);
fprintf(file, STR_0083846C);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064fcd7; Items0x00B0E724, Count0x00B0E730.
QueueDumpCRCEntries(file, checksum, DAT_00B0E720, false);
fprintf(file, STR_00838438);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064fd64; Items0x008B417C, Count0x008B4188.
QueueDumpCRCEntries(file, checksum, DAT_008B4178, false);
fprintf(file, STR_00838408);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064fdf1; Items0x00A8EAEC, Count0x00A8EAF8.
QueueDumpCRCEntries(file, checksum, DAT_00A8EAE8, false);
fprintf(file, STR_008383D8);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064fe7e; Items0x00B0E65C, Count0x00B0E668.
QueueDumpCRCEntries(file, checksum, DAT_00B0E658, false);
fprintf(file, STR_008383A8);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064ff0b; Items0x00B0F1A4, Count0x00B0F1B0.
QueueDumpCRCEntries(file, checksum, DAT_00B0F1A0, false);
fprintf(file, STR_00838378);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0064ff98; Items0x00A83E34, Count0x00A83E40.
QueueDumpCRCEntries(file, checksum, DAT_00A83E30, false);
fprintf(file, STR_00838340);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation00650025; Items0x00A8EB2C, Count0x00A8EB38.
QueueDumpCRCEntries(file, checksum, DAT_00A8EB28, false);
fprintf(file, STR_0083830C);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation006500b2; Items0x0088738C, Count0x00887398.
QueueDumpCRCEntries(file, checksum, DAT_00887388, false);
fprintf(file, STR_008382DC);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0065013f; Items0x008874C4, Count0x008874D0.
QueueDumpCRCEntries(file, checksum, DAT_008874C0, false);
fprintf(file, STR_008382AC);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation006501cc; Items0x0088756C, Count0x00887578.
QueueDumpCRCEntries(file, checksum, DAT_00887568, false);
fprintf(file, STR_00838274);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation00650259; Items0x00A83D9C, Count0x00A83DA8.
QueueDumpCRCEntries(file, checksum, DAT_00A83D98, false);
fprintf(file, STR_00838244);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation006502e6; Items0x00A83DCC, Count0x00A83DD8.
QueueDumpCRCEntries(file, checksum, DAT_00A83DC8, false);
fprintf(file, STR_0083820C);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation00650373; Items0x00A8020C, Count0x00A80218.
QueueDumpCRCEntries(file, checksum, DAT_00A80208, false);
fprintf(file, STR_008381D0);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation00650400; Items0x00A83D6C, Count0x00A83D78.
QueueDumpCRCEntries(file, checksum, DAT_00A83D68, false);
fprintf(file, STR_008381A0);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0065048d; Items0x00A83C84, Count0x00A83C90.
QueueDumpCRCEntries(file, checksum, DAT_00A83C80, false);
fprintf(file, STR_00838170);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0065051a; Items0x00A8ED44, Count0x00A8ED50.
QueueDumpCRCEntries(file, checksum, DAT_00A8ED40, false);
fprintf(file, STR_00838138);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation006505a7; Items0x00B7260C, Count0x00B72618.
QueueDumpCRCEntries(file, checksum, DAT_00B72608, false);
fprintf(file, STR_00838104);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation00650634; Items0x00A8EC1C, Count0x00A8EC28.
QueueDumpCRCEntries(file, checksum, DAT_00A8EC18, false);
fprintf(file, STR_008380D0);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation006506c1; Items0x00A83D84, Count0x00A83D90.
QueueDumpCRCEntries(file, checksum, DAT_00A83D80, false);
fprintf(file, STR_0083809C);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation0065074e; Items0x00ABCA14, Count0x00ABCA20.
QueueDumpCRCEntries(file, checksum, DAT_00ABCA10, false);
fprintf(file, STR_00838064);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation006507db; Items0x008B4194, Count0x008B41A0.
QueueDumpCRCEntries(file, checksum, DAT_008B4190, false);
fprintf(file, STR_00838038);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation00650868; Items0x008B413C, Count0x008B4148.
QueueDumpCRCEntries(file, checksum, DAT_008B4138, false);
fprintf(file, STR_00838008);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation006508f5; Items0x008B4124, Count0x008B4130.
QueueDumpCRCEntries(file, checksum, DAT_008B4120, false);
fprintf(file, STR_00837FD8);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation00650982; Items0x00B0F4EC, Count0x00B0F4F8.
QueueDumpCRCEntries(file, checksum, DAT_00B0F4E8, false);
fprintf(file, STR_00837FA8);
fprintf(file, STR_00838828);
fprintf(file, STR_008387F8);
delete checksum;
checksum = new Obj_004A1D30();
// Loop allocation00650a0f; Items0x008A3874, Count0x008A3880.
QueueDumpCRCEntries(file, checksum, DAT_008A3870, false);
delete checksum;
fclose(file);
}

// FUNCTION: GAMEMD 0x650A90
// ev_b0d56ac44dfec9c9587a602e6fd8b3b9de859a7e489dd2404884aeeb4508d4d1.
void FUN_00650A90(int index)
{
    if (!DAT_00B04880) {
        DAT_00AFA26C = DAT_00A8B230->unknown_0218.Random();
        return;
    }
    Obj_00646CE0& log = DAT_00AC6660[index];
    log.unknown_00 = DAT_00AC51FC;
    log.unknown_04 = DAT_00A8B230->unknown_0218.Random();
    log.unknown_08 = CurrentFrame;
    for (int h = 0; h < 8; ++h) {
        QueuePlayerLog_00650A90& player = log.unknown_0C[h];
        player.unknown_38 = -1;
        if (h >= DAT_00A80238) continue;
        player.unknown_00[0] = 0;
        for (int p = 0; p < PlayerCount_00A8DA84; ++p)
            if (Players_00A8DA78[p]->unknown_6F == h)
                strncpy(player.unknown_00, FUN_007350C0(Players_00A8DA78[p]->Name), 20);
        HouseClass* house = DAT_00A8022C[h];
        if (!player.unknown_00[0] &&
            (!strcmp(house->Type->ID, STR_0082BA08) || !strcmp(house->Type->ID, STR_00817318)))
            strcpy(player.unknown_00, house->Type->ID);
        player.unknown_14 = house->IsHumanPlayer;
        player.unknown_15[31] = 0;
        strncpy(player.unknown_15, ColorSchemeArray.Items[house->ColorSchemeIndex]->Name, 31);
        player.unknown_38 = h;
        player.unknown_3C[31] = 0;
        strncpy(player.unknown_3C, DAT_00A83C9C[house->Type->ArrayIndex]->ID, 31);
    }
    int technoCount = DAT_00A83DE8.Count + DAT_008B4108.Count + DAT_00A8E390.Count + DAT_00A8EB40.Count;
    int objectCount = DAT_0087F778.Count;
    for (int l = 0; l < 5; ++l) objectCount += DAT_008A0360[l].Count;
    if (!log.unknown_334) log.unknown_334 = new char[log.unknown_338];
    unsigned needed = technoCount * sizeof(QueueTechnoLog_00650A90) + objectCount * sizeof(QueueObjectLog_00650A90);
    if (log.unknown_338 < needed + 0x400U) {
        delete[] static_cast<char*>(log.unknown_334);
        log.unknown_338 = (needed + 0xFFFFU) & 0xFFFF0000U;
        FUN_004068E0(STR_00838EC0, index, log.unknown_338 >> 10);
        log.unknown_334 = new char[log.unknown_338];
    }
    QueueTechnoLog_00650A90* out = static_cast<QueueTechnoLog_00650A90*>(log.unknown_334);
    log.unknown_300 = out;
    int total = 0;
    log.unknown_2F0[0] = DAT_00A83DE8.Count;
    for (int iA83DE8 = 0; iA83DE8 < DAT_00A83DE8.Count; ++iA83DE8) {
        // Specific Type offsets are confirmed in650A90; canonical complete
        // object spines provide the inherited fields, no new class view.
        InfantryClass* item = static_cast<InfantryClass**>(DAT_00A83DE8.Items)[iA83DE8];
        QueueLogTechno(out, item, false);
        out->unknown_04 = item->Type->ArrayIndex;
        out->unknown_67 = static_cast<unsigned char>(int(item->SpeedPercentage * DAT_007E1710));
        out->unknown_20 = static_cast<unsigned char>(item->Owner->ArrayIndex);
        out->unknown_08[23] = 0;
        strncpy(out->unknown_08, item->Type->ID, 23);
        out->unknown_40 = QueueLogTarget(static_cast<AbstractClass*>(item->Destination), out->unknown_44);
        out->unknown_24 = QueueLogTarget(item->Target, out->unknown_28);
        ++out;
        ++total;
    }
    log.unknown_2F0[1] = DAT_008B4108.Count;
    for (int i8B4108 = 0; i8B4108 < DAT_008B4108.Count; ++i8B4108) {
        // Specific Type offsets are confirmed in650A90; canonical complete
        // object spines provide the inherited fields, no new class view.
        UnitClass* item = static_cast<UnitClass**>(DAT_008B4108.Items)[i8B4108];
        QueueLogTechno(out, item, true);
        out->unknown_04 = static_cast<UnitTypeClass*>(item->Type)->ArrayIndex;
        out->unknown_67 = static_cast<unsigned char>(int(item->SpeedPercentage * DAT_007E1710));
        out->unknown_20 = static_cast<unsigned char>(item->Owner->ArrayIndex);
        out->unknown_60 = static_cast<short>(QueueLogLocomotor(item)->GetTrackNumber());
        out->unknown_62 = static_cast<short>(QueueLogLocomotor(item)->GetTrackIndex());
        out->unknown_5C = QueueLogLocomotor(item)->GetSpeedAccum();
        out->unknown_08[23] = 0;
        strncpy(out->unknown_08, static_cast<UnitTypeClass*>(item->Type)->ID, 23);
        out->unknown_40 = QueueLogTarget(static_cast<AbstractClass*>(item->Destination), out->unknown_44);
        out->unknown_24 = QueueLogTarget(item->Target, out->unknown_28);
        ++out;
        ++total;
    }
    log.unknown_2F0[2] = DAT_00A8E390.Count;
    for (int iA8E390 = 0; iA8E390 < DAT_00A8E390.Count; ++iA8E390) {
        // Specific Type offsets are confirmed in650A90; canonical complete
        // object spines provide the inherited fields, no new class view.
        AircraftClass* item = static_cast<AircraftClass**>(DAT_00A8E390.Items)[iA8E390];
        QueueLogTechno(out, item, false);
        out->unknown_04 = static_cast<AircraftTypeClass*>(item->Type)->ArrayIndex;
        out->unknown_67 = static_cast<unsigned char>(int(item->SpeedPercentage * DAT_007E1710));
        out->unknown_20 = static_cast<unsigned char>(item->Owner->ArrayIndex);
        out->unknown_08[23] = 0;
        strncpy(out->unknown_08, static_cast<AircraftTypeClass*>(item->Type)->ID, 23);
        out->unknown_40 = QueueLogTarget(static_cast<AbstractClass*>(item->Destination), out->unknown_44);
        out->unknown_24 = QueueLogTarget(item->Target, out->unknown_28);
        ++out;
        ++total;
    }
    log.unknown_2F0[3] = DAT_00A8EB40.Count;
    for (int iA8EB40 = 0; iA8EB40 < DAT_00A8EB40.Count; ++iA8EB40) {
        // Specific Type offsets are confirmed in650A90; canonical complete
        // object spines provide the inherited fields, no new class view.
        BuildingClass* item = static_cast<BuildingClass**>(DAT_00A8EB40.Items)[iA8EB40];
        QueueLogTechno(out, item, false);
        out->unknown_04 = item->Type->ArrayIndex;
        out->unknown_20 = static_cast<unsigned char>(item->Owner->ArrayIndex);
        out->unknown_08[23] = 0;
        strncpy(out->unknown_08, item->Type->ID, 23);
        out->unknown_40 = 0;
        out->unknown_44[0] = 0;
        out->unknown_24 = QueueLogTarget(item->Target, out->unknown_28);
        ++out;
        ++total;
    }
    log.unknown_2EC = total;
    // Allocation is one contiguous byte buffer: 104-byte records precede
    // the40-byte draw-layer records (650A90 pointer stores300/318/330).
    QueueObjectLog_00650A90* objectOut = reinterpret_cast<QueueObjectLog_00650A90*>(out);
    for (l = 0; l < 5; ++l) {
        log.unknown_318[l] = objectOut;
        int added = 0;
        for (int i = 0; i < DAT_008A0360[l].Count; ++i) {
            ObjectClass* item = DAT_008A0360[l].Items[i];
            if (item->vf_11() == 4 && item->vf_rtti_4() == -2) continue;
            QueueLogObject(objectOut, item);
            ++objectOut;
            ++added;
        }
        log.unknown_304[l] = added;
    }
    log.unknown_330 = objectOut;
    total = 0;
    for (int i = 0; i < DAT_0087F778.Count; ++i) {
        ObjectClass* item = static_cast<ObjectClass**>(DAT_0087F778.Items)[i];
        if (item->vf_11() == 4 && item->vf_rtti_4() == -2) continue;
        QueueLogObject(objectOut, item);
        ++objectOut;
        ++total;
    }
    log.unknown_32C = total;
}

// FUNCTION: GAMEMD 0x6516F0
// ev_e88e51e43a5aecdccd75ad04b582065dc9c93b66956cfd2febd45a8477798040.
void FUN_006516F0(int slot, EventClass* offending)
{
    Obj_00646CE0& log = DAT_00AC6660[slot];
    char filename[512];
    sprintf(filename, STR_00839194, DAT_00A83D4C->ArrayIndex, slot);
    FUN_004068E0(STR_00838E90, filename);
    FILE* file = fopen(filename, DAT_0081D988);
    if (!file) {
        FUN_004068E0(STR_00838E4C, GetLastError(), file);
        return;
    }
    fprintf(file, STR_00838E40);
    fprintf(file, STR_00838E30, FUN_0074fdc0());
    fprintf(file, STR_00838E18, DAT_00A8ECE0.FUN_0074FAE0());
    char first[128];
    char second[128];
    char third[128];
    first[0] = 0;
    FUN_00777AC0(first, 128);
    const char* secondText = FUN_00777B60(second, 128);
    const char* thirdText = FUN_00777B30(third, 128);
    fprintf(file, STR_00821F0C, thirdText, secondText, first);
    int code = 5;
    char flag = 0;
    FUN_004E6150(&code, &flag, 0, 0);
    fprintf(file, STR_00821EE4, FUN_004E62B0(), flag ? DAT_00821F08 : DAT_00821F04, STR_0084E865);
    fprintf(file, STR_0081D970, CurrentFrame);
    fprintf(file, STR_0081D95C, DAT_00ABCD4C ? DAT_00ABCD48 / DAT_00ABCD4C : 0);
    fprintf(file, STR_0081D948, DAT_00A8B568);
    fprintf(file, STR_0081D930, DAT_00A8DB9C);
    fprintf(file, STR_0081D918, DAT_00A8EB60);
    fprintf(file, STR_00838E04, DAT_00A8B554);
    fprintf(file, STR_00839188, log.unknown_08);
    fprintf(file, STR_0083917C, slot);
    if (Interface_00887628) {
        for (int i = 0; i < Interface_00887628->GetNumLocalAddresses(); ++i) {
            unsigned char* address = Interface_00887628->GetLocalAddress(i);
            if (address) fprintf(file, STR_0081D8FC, address[0], address[1], address[2], address[3]);
        }
    }
    for (int i = 0; i < 8; ++i) {
        ConnStat& stat = ConnStats_00A8B574[i];
        if (!stat.Name[0]) continue;
        NetworkNumberType network;
        NodeAddressType node;
        stat.Address.FUN_0053EDA0(network, node);
        fprintf(file, STR_0081D8F0, stat.Name);
        fprintf(file, STR_00838DEC, node.Node[0], node.Node[1], node.Node[2], node.Node[3]);
        fprintf(file, STR_0081D8C8, stat.AvgMs);
        fprintf(file, STR_0081D8B4, stat.PeakMs);
        fprintf(file, STR_0081D8A4, stat.unknown_44);
        fprintf(file, STR_0081D88C, stat.unknown_54);
        fprintf(file, STR_0081D870, stat.unknown_58);
        fprintf(file, STR_0081D864, stat.unknown_48);
        fprintf(file, STR_0081D850, stat.unknown_4C);
    }
    for (i = 0; i < 256; ++i)
        fprintf(file, i == slot ? STR_00839168 : STR_00838DE0, i, DAT_00B04474[i]);
    int lastId = 0;
    for (i = 0; i < 8; ++i) {
        QueuePlayerLog_00650A90& player = log.unknown_0C[i];
        if (player.unknown_38 == -1) continue;
        lastId = player.unknown_38;
        fprintf(file, STR_00839138, player.unknown_00, player.unknown_14,
                player.unknown_15, player.unknown_38, player.unknown_3C);
    }
    QueueTechnoLog_00650A90* records = log.unknown_300;
    // Retail uses the last valid ID as the exclusive bound; do not turn it
    // into a count or include the final ID by adding1.
    for (int h0 = 0; h0 < lastId; ++h0) {
        if (log.unknown_0C[h0].unknown_38 == -1) continue;
        fprintf(file, STR_00839100, log.unknown_0C[h0].unknown_00);
        for (int n = 0; n < log.unknown_2F0[0]; ++n) {
            QueueTechnoLog_00650A90& item = records[n];
            if (item.unknown_20 != h0) continue;
            fprintf(file, STR_008390A8, item.unknown_00, item.unknown_64, item.unknown_66,
                item.unknown_04, item.unknown_08, item.unknown_28, item.unknown_24,
                item.unknown_67, item.unknown_44, item.unknown_40);
        }
    }
    records += log.unknown_2F0[0];
    for (int h1 = 0; h1 < lastId; ++h1) {
        if (log.unknown_0C[h1].unknown_38 == -1) continue;
        fprintf(file, STR_00839074, log.unknown_0C[h1].unknown_00);
        for (int n = 0; n < log.unknown_2F0[1]; ++n) {
            QueueTechnoLog_00650A90& item = records[n];
            if (item.unknown_20 != h1) continue;
            fprintf(file, STR_00838FF8, item.unknown_00, item.unknown_64, item.unknown_65,
                item.unknown_66, item.unknown_04, item.unknown_08, item.unknown_28,
                item.unknown_24, item.unknown_44, item.unknown_40,
                item.unknown_60, item.unknown_62, item.unknown_5C);
        }
    }
    records += log.unknown_2F0[1];
    for (int h2 = 0; h2 < lastId; ++h2) {
        if (log.unknown_0C[h2].unknown_38 == -1) continue;
        fprintf(file, STR_00838FC0, log.unknown_0C[h2].unknown_00);
        for (int n = 0; n < log.unknown_2F0[2]; ++n) {
            QueueTechnoLog_00650A90& item = records[n];
            if (item.unknown_20 != h2) continue;
            fprintf(file, STR_00838F70, item.unknown_00, item.unknown_64, item.unknown_66,
                item.unknown_04, item.unknown_08, item.unknown_28, item.unknown_24,
                item.unknown_44, item.unknown_40);
        }
    }
    records += log.unknown_2F0[2];
    for (int h3 = 0; h3 < lastId; ++h3) {
        if (log.unknown_0C[h3].unknown_38 == -1) continue;
        fprintf(file, STR_00838F38, log.unknown_0C[h3].unknown_00);
        for (int n = 0; n < log.unknown_2F0[3]; ++n) {
            QueueTechnoLog_00650A90& item = records[n];
            if (item.unknown_20 != h3) continue;
            fprintf(file, STR_00838EF8, item.unknown_00, item.unknown_64, item.unknown_66,
                item.unknown_04, item.unknown_08, item.unknown_28, item.unknown_24);
        }
    }
    records += log.unknown_2F0[3];
    for (int layer = 0; layer < 5; ++layer) {
        fprintf(file, STR_00838AD4, layer);
        for (int n = 0; n < log.unknown_304[layer]; ++n)
            QueueDumpObject(file, &log, &log.unknown_318[layer][n], n);
    }
    fprintf(file, STR_00838A54);
    for (int n = 0; n < log.unknown_32C; ++n)
        QueueDumpObject(file, &log, &log.unknown_330[n], n);
    fprintf(file, STR_00838918, log.unknown_04);
    if (offending) {
        fprintf(file, STR_008388E4);
        fprintf(file, STR_008388D0, offending->Type);
        fprintf(file, STR_008388BC, offending->Frame);
        fprintf(file, STR_008388A8, offending->HouseIndex);
        fprintf(file, STR_00838894, offending->Data.Payload_19.unknown_07);
        fprintf(file, STR_00838880, offending->Data.Payload_19.unknown_0B);
        fprintf(file, STR_0083886C, offending->Data.Payload_19.unknown_0D);
    }
    fclose(file);
}

// FUNCTION: GAMEMD 0x652070
// Event in ECX, ordinary fastcall receiver argument; no stack arguments.
// ev_5638088471e5ccbdd7f07be5d806152c248d60fa3dc87568cd0a25a5419bd994.
void FUN_00652070(const EventClass* event)
{
    FUN_004068E0(STR_00837F24);
    FUN_004068E0(STR_00837EF8);
    FUN_004068E0(STR_00837EE8, DAT_0082091C[event->Type]);
    FUN_004068E0(STR_00837ED8, event->Frame);
    FUN_004068E0(STR_00837EC8, event->HouseIndex);
    FUN_004068E0(STR_00837EB8, DAT_00A8B550);
    FUN_004068E0(STR_00837EAC, CurrentFrame);
    FUN_004068E0(STR_00837E98, DAT_00A8B554);
}

// FUNCTION: GAMEMD 0x652110
// ev_e1650ffc8d71024b2028827902f0ce65d60ab045d5cdd87917ff2d153952c855.
void FUN_00652110(const Obj_00646D00* records, int index)
{
    if (Session_00A8B238.GameMode != 4) {
        DAT_00A8DB7C[index] = 0;
        return;
    }
    int frame = records[index].unknown_00;
    unsigned elapsed;
    if (Flag_00A8DBA0) {
        // FILD signedDWORD B558 and unsigned-qword representation B554 at
        // 652144..168. SHR65217B uses all32 bits of the record timestamp.
        int correction = int(DAT_007F02A4 /
            (double(DAT_00A8B558) / unsigned(DAT_00A8B554)));
        elapsed = (unsigned(records[index].unknown_10) >> 1) - correction / 2 +
                  (DAT_00A8E2D4 >> 1);
    } else {
        elapsed = unsigned(Manager_00A8E9C0.IPXManagerClass::ResponseTimeOf(index)) >> 1;
    }
    DAT_00A8DB7C[index] = CurrentFrame - (FPSCounter_CurrentFrameRate * elapsed) / 60U - frame;
}

// FUNCTION: GAMEMD 0x6521C0
// Stack by-value event occupies0x70 aligned bytes, RET70. AL-only0/1 result.
// ev_30adb13fe91da3d46ce058f145c54a58a474042fe8c1fe10f5700d5c80b312c8.
bool FUN_006521C0(EventClass event)
{
    event.Frame = CurrentFrame;
    if (DAT_00A802C8.Count < 128) {
        DAT_00A802C8.List[DAT_00A802C8.Head] = event;
        DAT_00A802C8.Time[DAT_00A802C8.Head] = timeGetTime();
        DAT_00A802C8.Head = (DAT_00A802C8.Head + 1) & 127;
        ++DAT_00A802C8.Count;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x652230
// ev_29a221620e4e41e6b15e35706950c7d6d10d87d2d8bfc0e0cb80ca23a71971aa.
void FUN_00652230(EventClass* event)
{
    int frame = CurrentFrame + 1;
    if (DAT_00A8B24C == 2)
        // DIV ECX at652253 proves unsigned interpretation of this frame rounding.
        frame = ((static_cast<unsigned>(DAT_00A8B554) + CurrentFrame) / static_cast<unsigned>(DAT_00A8B554)) * DAT_00A8B554;
    event->Frame = frame;
    if (DAT_008B41F8.Count < 0x4000) {
        if (DAT_008B41F8.unknown_04 == 0) DAT_008B41F8.unknown_04 = 0x3FFF;
        else --DAT_008B41F8.unknown_04;
        DAT_008B41F8.List[DAT_008B41F8.unknown_04] = *event;
        DAT_008B41F8.Time[DAT_008B41F8.unknown_04] = timeGetTime();
        ++DAT_008B41F8.Count;
        return;
    }
    if (Session_00A8B238.GameMode == 0 || Session_00A8B238.GameMode == 5) return;
    if (Session_00A8B238.GameMode == 4) Unsorted_RegisterGameEndTime();
    ++DAT_00A8DAB4;
    Dialog_005D3490 dialog;
    dialog.FUN_005D3490(
        FUN_00734E60(STR_00837474, 0, STR_008374A0, 0x22AE),
        FUN_00734E60(STR_00825FB0, 0, STR_008374A0, 0x22AE), 0, 0, 0);
    --DAT_00A8DAB4;
    DAT_00A8B8B8 = 0;
    DAT_00A8B8BC = 0;
    DAT_00A8E9A0 = 0;
    if (DAT_00B04874) FUN_005BC400();
    if (Session_00A8B238.GameMode == 4) {
        DAT_00B0BD78 = 1;
        DAT_00A8B8C1 = 1;
        DAT_00A8B8C2 = 1;
        Unsorted_RegisterGameEndTime();
        FUN_006C6F50(0);
    }
    FUN_0072DDB0();
    FUN_006842F0(false);
}

// FUNCTION: GAMEMD 0x6523A0
// ev_725d62b0a3d6e6552304cb27873ce783c3e8d262c26f59b7bd3ae34ea8ac73fc.
void FUN_006523A0()
{
    FUN_004068E0(STR_008391CC);
    if (Session_00A8B238.GameMode != 4) return;
    Manager_00A8E9C0.FUN_00543080();
    int queued = Manager_00A8E9C0.IPXManagerClass::vf_7();
    for (int index = 0; index < DAT_00B052E0; ++index) {
        QueuePacket_0064AAE0 packet;
        // Retail initializes and transmits the 47-byte protocol prefix only.
        memset(&packet, 0, 0x2F);
        packet.unknown_00 = 0x2F;
        strcpy(packet.unknown_04, FUN_007350C0(Players_00A8DA78[0]->Name));
        const char* name = IdMap_00B052D0.FUN_006643E0(index);
        if (name && strcmp(name, FUN_007350C0(Players_00A8DA78[0]->Name))) {
            FUN_004068E0(STR_008391A8, name);
            IPXAddressClass address = *IdMap_00B052D0.FUN_006642A0(name);
            Manager_00A8E9C0.FUN_005410F0(&packet, 0x2F, 1, &address,
                                        IdMap_00B052D0.FUN_00664390(name), 0);
        }
    }
    ScenarioElapsedTimer timeout(300);
    while (queued < Manager_00A8E9C0.IPXManagerClass::vf_7() && timeout.GetTimeLeft())
        FUN_0048D080();
    if (Session_00A8B238.GameMode == 4) Manager_00A8E9C0.FUN_00543090();
}

// FUNCTION: GAMEMD 0x652540
// Branching.
template<>
int EventQueue<128>::FUN_00652540()
{
    if (Count != 0)
    {
        unknown_04 = (unknown_04 + 1) & 0x7F;
        Count--;
    }
    return Count;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6525A0
bool GrowPairVector::Grow_6525A0(int extra)
{
    GrowPair* grown;
    int total;
    int i;

    if (extra < 0) goto fail;

    total = Capacity + extra;
    grown = new GrowPair[total];
    if (grown == 0) goto fail;

    for (i = 0; i < Count; i++) {
        int off = i * 8;
        GrowPair* src = (GrowPair*)((char*)Items + off);
        *(GrowPair*)((char*)grown + off) = *src;
    }

    delete[] Items;

    Items    = grown;
    Capacity = Capacity + extra;
    Cached   = 0;
    return true;

fail:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00652630
int __cdecl FUN_00652630(const void* a, const void* b)
{
    if (*(const int*)a == *(const int*)b)
        return 0;
    if (*(const int*)a < *(const int*)b)
        return -1;
    return 1;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x887310
Surface* DAT_00887310;
// GLOBAL: GAMEMD 0x8A0360
Layer_004A9770 DAT_008A0360[5];
// GLOBAL: GAMEMD 0xA8B24C
int DAT_00A8B24C;
// GLOBAL: GAMEMD 0xA8B550
int DAT_00A8B550;
// GLOBAL: GAMEMD 0xA8B554
int DAT_00A8B554;
// GLOBAL: GAMEMD 0xA8B8B8
int DAT_00A8B8B8;
// GLOBAL: GAMEMD 0xA8B8BC
int DAT_00A8B8BC;
// GLOBAL: GAMEMD 0xA8B8C1
unsigned char DAT_00A8B8C1;
// GLOBAL: GAMEMD 0xA8B8C2
unsigned char DAT_00A8B8C2;
// GLOBAL: GAMEMD 0xA8EB60
int DAT_00A8EB60;
// GLOBAL: GAMEMD 0xA8EDA0
int DAT_00A8EDA0;
// GLOBAL: GAMEMD 0xB04874
int DAT_00B04874;
// GLOBAL: GAMEMD 0xB04878
unsigned char DAT_00B04878;
// GLOBAL: GAMEMD 0xB04880
bool DAT_00B04880;
// GLOBAL: GAMEMD 0xB04884
int DAT_00B04884;
// GLOBAL: GAMEMD 0xB04888
int DAT_00B04888;
// GLOBAL: GAMEMD 0xB0488C
unsigned char DAT_00B0488C;
// GLOBAL: GAMEMD 0xB0488D
unsigned char DAT_00B0488D;
// GLOBAL: GAMEMD 0xB0BD78
unsigned char DAT_00B0BD78;
// GLOBAL: GAMEMD 0xB77780
int DAT_00B77780;
// GLOBAL: GAMEMD 0xB77CE0
int DAT_00B77CE0;
// GLOBAL: GAMEMD 0x7F0290
extern const double DAT_007F0290 = 60.0;
// END defined globals
