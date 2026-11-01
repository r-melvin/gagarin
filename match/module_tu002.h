// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Declarations used by module_tu002.cpp: the module-scope globals and the functions it calls.
#ifndef GG_MATCH_MODULE_TU002_H
#define GG_MATCH_MODULE_TU002_H

#include <windows.h>
#include "module_tu002_stream.h"
#include "floored_decrement_methods.h"
#include "dsound_access_methods.h"
#include "theme_class_ai_methods.h"
#include "mix_file_class.h"

// GLOBAL: GAMEMD 0x87E448
extern double DAT_0087E448;
// GLOBAL: GAMEMD 0x7E1750
extern const double DAT_007E1750;
// GLOBAL: GAMEMD 0x87E698
extern double DAT_0087E698;
// GLOBAL: GAMEMD 0x87E680
extern double DAT_0087E680;
// GLOBAL: GAMEMD 0x87E690
extern int DAT_0087E690;
// GLOBAL: GAMEMD 0x87E688
extern int DAT_0087E688;
// GLOBAL: GAMEMD 0x87E68C
extern int DAT_0087E68C;
// LIBRARY: GAMEMD 0x7C94BC (decl; reloc)
// FUN_007C94BC
extern "C" unsigned __cdecl FUN_007C94BC(void*, unsigned, unsigned, void*);
// LIBRARY: GAMEMD 0x7C95D3 (decl; reloc)
// FUN_007C95D3
extern "C" unsigned __cdecl FUN_007C95D3(void*, unsigned, unsigned, void*);
// GLOBAL: GAMEMD 0x816518
extern int DAT_00816518[];
// GLOBAL: GAMEMD 0x816558
extern int DAT_00816558[];
// GLOBAL: GAMEMD 0x87E7F8
extern CRITICAL_SECTION DAT_0087E7F8;
// GLOBAL: GAMEMD 0x87E810
extern ListNode DAT_0087E810;
// GLOBAL: GAMEMD 0x87E724
extern AudioIDXData* DAT_0087E724;
// GLOBAL: GAMEMD 0x87E734
extern MixFileClass* DAT_0087E734;
// GLOBAL: GAMEMD 0x87E738
extern MixFileClass* DAT_0087E738;
// GLOBAL: GAMEMD 0x87E75C
extern int DAT_0087E75C;
// GLOBAL: GAMEMD 0x87E760
extern unsigned __int64 DAT_0087E760;
// GLOBAL: GAMEMD 0xA83D10
extern ThemeClass DAT_00A83D10;
// GLOBAL: GAMEMD 0x816514
extern void* DAT_00816514;
// FUNCTION: GAMEMD 0x403FA0 (decl; reloc)
// FUN_00403FA0
void __cdecl FUN_00403FA0();
// FUNCTION: GAMEMD 0x404E70 (decl; reloc)
// FUN_00404E70
void __cdecl FUN_00404E70();
// FUNCTION: GAMEMD 0x4081A0 (decl; reloc)
// FUN_004081A0
void __cdecl FUN_004081A0();
// FUNCTION: GAMEMD 0x752340 (decl; reloc)
// FUN_00752340
void __cdecl FUN_00752340();
// FUNCTION: GAMEMD 0x752B40 (decl; reloc)
// FUN_00752B40
void __cdecl FUN_00752B40();
// FUNCTION: GAMEMD 0x4041D0 (decl; reloc)
// FUN_004041D0
void __cdecl FUN_004041D0();
// FUNCTION: GAMEMD 0x750EC0 (decl; reloc)
// FUN_00750EC0
void __cdecl FUN_00750EC0();
// FUNCTION: GAMEMD 0x752760 (decl; reloc)
// FUN_00752760
void __cdecl FUN_00752760();
// FUNCTION: GAMEMD 0x7B84D0 (decl; reloc)
// FUN_007B84D0
void __cdecl FUN_007B84D0();
// GLOBAL: GAMEMD 0x87E73C
extern Obj_00401000* DAT_0087E73C;
// GLOBAL: GAMEMD 0x87E740
extern Obj_00401000* DAT_0087E740;
// GLOBAL: GAMEMD 0x87E744
extern Obj_00401000* DAT_0087E744;
// GLOBAL: GAMEMD 0x87E748
extern Obj_00401000* DAT_0087E748;
// GLOBAL: GAMEMD 0x87E74C
extern Obj_00401000* DAT_0087E74C;
// GLOBAL: GAMEMD 0x87E750
extern Obj_00401000* DAT_0087E750;
// GLOBAL: GAMEMD 0x87E754
extern Obj_00401000* DAT_0087E754;
// GLOBAL: GAMEMD 0x87E770
extern StreamState_00407680 DAT_0087E770;
// GLOBAL: GAMEMD 0x87E7F0
extern HANDLE DAT_0087E7F0;
// GLOBAL: GAMEMD 0x87E7F4
extern DWORD DAT_0087E7F4;
// GLOBAL: GAMEMD 0x87E820
extern int DAT_0087E820;
// GLOBAL: GAMEMD 0xB04BEC
extern bool DAT_00B04BEC;
// STRING: GAMEMD 0x81628C
// "Unable to change the priority of the Streamer Thread - %s\n"
extern const char DAT_0081628C[];
// FUNCTION: GAMEMD 0x407680 (decl; reloc)
// FUN_00407680
DWORD __stdcall FUN_00407680(void*);
// GLOBAL: GAMEMD 0x87E72C
extern int DAT_0087E72C;
// STRING: GAMEMD 0x81626C
// "audio"
extern const char DAT_0081626C[];
// STRING: GAMEMD 0x816274
// "AUDIO.MIX"
extern const char DAT_00816274[];
// STRING: GAMEMD 0x816280
// "AUDIOMD.MIX"
extern const char DAT_00816280[];
// STRING: GAMEMD 0x8162C8
// "Audio Stream"
extern const char DAT_008162C8[];
// STRING: GAMEMD 0x886980
// ""
extern const char DAT_00886980[];
// FUNCTION: GAMEMD 0x402940 (decl; reloc)
// FUN_00402940
int __cdecl FUN_00402940();
// FUNCTION: GAMEMD 0x409360 (decl; reloc)
// FUN_00409360
void __cdecl FUN_00409360();
// FUNCTION: GAMEMD 0x752290 (decl; reloc)
// FUN_00752290
void __cdecl FUN_00752290();
// FUNCTION: GAMEMD 0x752AD0 (decl; reloc)
// FUN_00752AD0
void __cdecl FUN_00752AD0();
// LIBRARY: GAMEMD 0x7C9430 (decl; reloc)
// FUN_007C9430
extern "C" void* __cdecl FUN_007C9430(unsigned);
// GLOBAL: GAMEMD 0x87E2C0
extern Obj_00401000 DAT_0087E2C0;
// GLOBAL: GAMEMD 0x87E4E0
extern Obj_00401000 DAT_0087E4E0;
// GLOBAL: GAMEMD 0x87E578
extern Obj_00401000 DAT_0087E578;
// GLOBAL: GAMEMD 0x87E450
extern Obj_00401000 DAT_0087E450;
// GLOBAL: GAMEMD 0x87E340
extern Obj_00401000 DAT_0087E340;
// GLOBAL: GAMEMD 0x87E6A0
extern Obj_00401000 DAT_0087E6A0;
// GLOBAL: GAMEMD 0x87E5F8
extern Obj_00401000 DAT_0087E5F8;
// GLOBAL: GAMEMD 0x87E3C0
extern Obj_00401000 DAT_0087E3C0;
// GLOBAL: GAMEMD 0xB73550
extern HWND DAT_00B73550;
// GLOBAL: GAMEMD 0x87E874
extern DWORD DAT_0087E874;
// LIBRARY: GAMEMD 0x7C89DA (decl; reloc)
// FUN_007C89DA
extern "C" int __stdcall FUN_007C89DA(const GUID*, DirectSoundResource_00409FF0**, void*);
// FUNCTION: GAMEMD 0x4095B0 (decl; reloc)
// FUN_004095B0
DWORD __stdcall FUN_004095B0(void*);
// STRING: GAMEMD 0x8166D8
// "Unable to change the priority of the Audio Thread - %s\n"
extern const char DAT_008166D8[];
// STRING: GAMEMD 0x81677C
// "Unable to set the desired primary format\n"
extern const char DAT_0081677C[];
// STRING: GAMEMD 0x816828
// "Failed to prefill buffer\n"
extern const char DAT_00816828[];
// STRING: GAMEMD 0x816808
// "Sound frame size = %d bytes\n"
extern const char DAT_00816808[];
// STRING: GAMEMD 0x8167E4
// "Failed to create playback buffer\n"
extern const char DAT_008167E4[];
// STRING: GAMEMD 0x8167C4
// "Sound buffer size = %d bytes\n"
extern const char DAT_008167C4[];
// STRING: GAMEMD 0x8167A8
// "Failed to start playback\n"
extern const char DAT_008167A8[];
// STRING: GAMEMD 0x81674C
// "Failed to restore buffer\n"
extern const char DAT_0081674C[];
// STRING: GAMEMD 0x816768
// "Restored buffer\n"
extern const char DAT_00816768[];
// STRING: GAMEMD 0x816734
// "Failed to lock buffer\n"
extern const char DAT_00816734[];
// STRING: GAMEMD 0x816710
// "Buffer management out by %d bytes\n"
extern const char DAT_00816710[];

#endif  // GG_MATCH_MODULE_TU002_H
