// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Shared declarations for the netshare.cpp block of retail .text
//   (0x5E2430..0x5EF18F). The unit's own path, "D:\ra2mdpost\netshare.cpp",
//   sits at 0x8317D8 and is pushed with its line numbers by the string-table
//   fetches in 0x5E87A0 (see netshare_slot_nodes.h). Everything declared here
//   was read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI
//   at the call sites cited beside each declaration. Names are retail CRT
//   (identified by bytes), import, or address placeholders.
#ifndef GG_MATCH_ECONOMY_NETSHARE_COMMON_H
#define GG_MATCH_ECONOMY_NETSHARE_COMMON_H

#include <stddef.h>
#include <stdarg.h>
#include "../_rt/gg_static_assert.h"
#include "../core/wide_string_class.h"
#include "../network/transport/connman_class.h"

extern "C" {
// LIBRARY: GAMEMD 0x7CA858 (decl; reloc) -- CRT vswprintf (three-argument form).
int __cdecl vswprintf(wchar_t* buffer, const wchar_t* format, va_list args);
// LIBRARY: GAMEMD 0x7CA8C6 (decl; reloc) -- CRT wcschr.
wchar_t* __cdecl wcschr(const wchar_t* text, wchar_t ch);
// LIBRARY: GAMEMD 0x7DDE13 (decl; reloc) -- CRT _wcsdup.
wchar_t* __cdecl _wcsdup(const wchar_t* text);
// LIBRARY: GAMEMD 0x7C93E8 (decl; reloc) -- CRT free.
void __cdecl free(void* block);
// LIBRARY: GAMEMD 0x7C91D0 (decl; reloc) -- CRT strncpy.
char* __cdecl strncpy(char* dst, const char* src, unsigned int count);
// FUNCTION: CRT strcpy, expanded inline by /O2 (REPNZ SCASB / REP MOVSD).
char* __cdecl strcpy(char* dst, const char* src);
// LIBRARY: GAMEMD 0x7CB8E6 (decl; reloc) -- CRT iswgraph: PUSH 0x117 (alpha,
// digit, punct) into _isctype.
int __cdecl iswgraph(unsigned short ch);
}

// FUNCTION: GAMEMD 0x7A2730 (decl; reloc) -- no arguments.
void __cdecl FUN_007A2730();
// The lobby message sent to each remote player. 0x1C7 bytes, byte-packed (the
// send length pushed at every call site is 0x1C7 and the buffer is cleared as
// 0x71 dwords, a word and a byte). Member offsets are the displacements the
// builders store through: +0x00 the message kind, +0x04 the sender's handle
// (an inline strcpy of 0xA8B380), +0x2F the text payload (a second strcpy),
// +0x1BF a dword read from 0xA8B394 and +0x1C3 the hash of the blank name
// (0x5DAC00).
#pragma pack(push, 1)
struct NetsharePacket
{
    int Command;               // +0x00
    char Name[0x2B];           // +0x04
    char Text[0x190];          // +0x2F
    int unknown_1BF;           // +0x1BF
    int unknown_1C3;           // +0x1C3
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(NetsharePacket, Name) == 0x04 &&
                 offsetof(NetsharePacket, Text) == 0x2F &&
                 offsetof(NetsharePacket, unknown_1BF) == 0x1BF &&
                 offsetof(NetsharePacket, unknown_1C3) == 0x1C3 &&
                 sizeof(NetsharePacket) == 0x1C7);

// GLOBAL: GAMEMD 0xA8B394
extern int DAT_00A8B394;
// FUNCTION: GAMEMD 0x5DAC00 (decl; reloc) -- __fastcall: hash of a wide name.
int __fastcall FUN_005DAC00(const wchar_t* name);
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- the debug log printf; declared
// with an int result in network/transport/conn_types.h.
// FUNCTION: GAMEMD 0x48D080 (decl; reloc) -- no arguments.
void __cdecl FUN_0048D080();
// FUNCTION: GAMEMD 0x7350C0 (decl; reloc) -- ANSI form of a wide name (already
// declared as Narrow_007350C0 in netshare_slot_nodes.h).

// The link object at 0xAC116C: reached only through its virtual slots 14 and
// 15 here. Slot positions are the displacements 0x38 and 0x3C of the calls at
// 0x5E3759 and 0x5E38A3; both push `this` as the first stacked argument and
// pop their own arguments, so the slots are __stdcall.
class Obj_00AC116C
{
public:
    virtual void __stdcall vf_0();
    virtual void __stdcall vf_1();
    virtual void __stdcall vf_2();
    virtual void __stdcall vf_3();
    virtual void __stdcall vf_4();
    virtual void __stdcall vf_5();
    virtual void __stdcall vf_6();
    virtual void __stdcall vf_7();
    virtual void __stdcall vf_8();
    virtual void __stdcall vf_9();
    virtual void __stdcall vf_10();
    virtual void __stdcall vf_11();
    virtual void __stdcall vf_12();
    virtual void __stdcall vf_13();
    virtual void __stdcall vf_14(void* message, const char* text);
    virtual void __stdcall vf_15(const char* text);
};
// GLOBAL: GAMEMD 0xAC116C
extern Obj_00AC116C* DAT_00AC116C;

// The message handed to the link's slot 14: 0x6C bytes, the sender's name
// copied in at +0x24.
struct NetshareLinkMessage
{
    char unknown_00[0x24];     // +0x00
    char Name[0x48];           // +0x24
};
GG_STATIC_ASSERT(offsetof(NetshareLinkMessage, Name) == 0x24 &&
                 sizeof(NetshareLinkMessage) == 0x6C);

// GLOBAL: GAMEMD 0xA8D638 -- a NetsharePacket-typed global: 0x5E3923 and
// 0x5E3937 store through 0xA8D7F7 and 0xA8D7FB, i.e. its +0x1BF and +0x1C3.
extern NetsharePacket DAT_00A8D638;
// GLOBAL: GAMEMD 0xA8B238 -- the session object; 0x69B720 is a __thiscall on it
// (the same address as the session-kind int that netshare_slot_nodes.h names).
struct Obj_00A8B238
{
    // FUNCTION: GAMEMD 0x69B720 (decl; reloc) -- no arguments.
    int FUN_0069B720();
    // FUNCTION: GAMEMD 0x69B760 (decl; reloc) -- __thiscall, (value, flag), RET 8.
    void FUN_0069B760(int value, bool flag);
    // FUNCTION: GAMEMD 0x69B7E0 (decl; reloc) -- __thiscall, (value, flag), RET 8.
    void FUN_0069B7E0(int value, bool flag);
};
extern Obj_00A8B238 SessionObject_00A8B238;
// GLOBAL: GAMEMD 0xA8B322 -- a wide string (0x5E32D0 copies it with wcscpy).
extern wchar_t DAT_00A8B322[];
// STRING: GAMEMD 0x831460 "GUI:HostNoMap"
extern char HostNoMapLabel[];
// STRING: GAMEMD 0x8317C4 "GUI:HostMapTransfer"
extern char HostMapTransferLabel[];

// FUNCTION: GAMEMD 0x5E32D0
void __fastcall FUN_005E32D0(char force, char poll);
// FUNCTION: GAMEMD 0x5E3720
void __fastcall FUN_005E3720(const char* text);
// FUNCTION: GAMEMD 0x5E2700 (HWND-free declaration shared with the window code).
void __cdecl FUN_005E2700(int param, const wchar_t* format, ...);

#endif  // GG_MATCH_ECONOMY_NETSHARE_COMMON_H
