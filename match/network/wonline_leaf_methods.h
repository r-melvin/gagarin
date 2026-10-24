// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Declarations shared by the leaf functions of the online-services
// translation unit (retail text 0x77B690..0x7AF0AF; its assertion path string
// 0x84A430 is "D:\ra2mdpost\wonline.cpp"). All names are placeholders unless
// a string in the binary attests them.
#ifndef GG_MATCH_NETWORK_WONLINE_LEAF_METHODS_H
#define GG_MATCH_NETWORK_WONLINE_LEAF_METHODS_H

#include "../ui/ui_window_contracts.h"
#include <stddef.h>
#include "wonline.h"
#include "../core/hash_table_view.h"
#include "../_rt/gg_static_assert.h"
#include "../audio/theme_class_methods.h"

// FUNCTION: GAMEMD 0x775B10 (decl; reloc)
void* FUN_00775B10();

// FUNCTION: GAMEMD 0x7757E0 (decl; reloc)
void FUN_007757E0(void* object, int flag);



// FUNCTION: GAMEMD 0x4068E0 (decl; reloc)

// The COM-style object at 0xAC116C: a vtable pointer whose slots take the
// object as their first stack argument.
struct Obj_00AC116C;

struct Vtbl_00AC116C
{
    char unknown_00[0x24];
    long (__stdcall* At_24)(Obj_00AC116C* self);                     // +0x24
    char unknown_28[4];
    long (__stdcall* At_2C)(Obj_00AC116C* self, const char* text);   // +0x2C
    char unknown_30[8];
    long (__stdcall* At_38)(Obj_00AC116C* self, Entry_00B77908* entry, const char* text);   // +0x38
    long (__stdcall* At_3C)(Obj_00AC116C* self, const char* text);   // +0x3C
    char unknown_40[0x14];
    long (__stdcall* At_54)(Obj_00AC116C* self, void* record);       // +0x54
    char unknown_58[0x10];
    long (__stdcall* At_68)(Obj_00AC116C* self, int a, int b);       // +0x68
    char unknown_6C[0x10];
    long (__stdcall* At_7C)(Obj_00AC116C* self, int a);              // +0x7C
    char unknown_80[0x0C];
    long (__stdcall* At_8C)(Obj_00AC116C* self, unsigned long value); // +0x8C  given the SKU by 0x786270
};

GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_24) == 0x24);

GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_2C) == 0x2C);

GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_38) == 0x38);

GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_3C) == 0x3C);

GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_54) == 0x54);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_68) == 0x68);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_7C) == 0x7C);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_8C) == 0x8C);

struct Obj_00AC116C
{
    Vtbl_00AC116C* Vtbl;   // +0x00
};

// GLOBAL: GAMEMD 0xAC116C
extern Obj_00AC116C* DAT_00AC116C;

// The second COM-style object, at 0xAC1170; same calling shape.
struct Obj_00AC1170;

struct Vtbl_00AC1170
{
    char unknown_00[0x20];
    // +0x20: given a record's +0x18 value and an out int (the ping) by 0x7A0F40.
    long (__stdcall* At_20)(Obj_00AC1170* self, int value, int* out);
    char unknown_24[0x08];
    // +0x2C: given a host name, a port and 3 by 0x786270.
    long (__stdcall* At_2C)(Obj_00AC1170* self, const char* host, int port, int a);
};

GG_STATIC_ASSERT(offsetof(Vtbl_00AC1170, At_20) == 0x20);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC1170, At_2C) == 0x2C);

struct Obj_00AC1170
{
    Vtbl_00AC1170* Vtbl;   // +0x00
};

// GLOBAL: GAMEMD 0xAC1170
extern Obj_00AC1170* DAT_00AC1170;

// GLOBAL: GAMEMD 0x84D690 -- a record: a dword (0x47) then the string "WOL:AddBuddyQuery".
extern char DAT_0084D690[];

// A 0xF8-byte record of the table at 0xB778E0 (count 0xB778D8).
struct Record_00B778E0
{
    char unknown_00[0xF8];
};

GG_STATIC_ASSERT(sizeof(Record_00B778E0) == 0xF8);

// GLOBAL: GAMEMD 0xB76468
extern int DAT_00B76468;

// GLOBAL: GAMEMD 0xB778D8 -- counted array of 0xF8-byte records: count +0x00, items +0x08.
struct Vec_00B778D8
{
    int count;                    // +0x00
    int unknown_04;               // +0x04
    Record_00B778E0* data;        // +0x08
};
extern Vec_00B778D8 DAT_00B778D8;

// FUNCTION: GAMEMD 0x7864C0 (decl; reloc)
bool FUN_007864C0(Record_00B778E0* record);

// GLOBAL: GAMEMD 0xA8DA84
extern int DAT_00A8DA84;

// GLOBAL: GAMEMD 0xB73BB4
extern int DAT_00B73BB4[];

// GLOBAL: GAMEMD 0x84A1E0
extern int DAT_0084A1E0[];

// GLOBAL: GAMEMD 0xB76B10
extern int DAT_00B76B10[0x43];

// GLOBAL: GAMEMD 0xB73BE8
extern int DAT_00B73BE8[0x43];

// GLOBAL: GAMEMD 0x84A210
extern char DAT_0084A210;


// GLOBAL: GAMEMD 0xB77DD0
extern int DAT_00B77DD0;

// A counted array of 0xF8-byte records: count +0x00, items +0x08.
struct Obj_007AC9D0
{
    int Count;                    // +0x00
    int unknown_04;               // +0x04
    Record_00B778E0* Items;       // +0x08

    bool FUN_007AC9D0(Record_00B778E0** out, int index);
};

// GLOBAL: GAMEMD 0xB77E14
extern int DAT_00B77E14;

// GLOBAL: GAMEMD 0xB73A20
extern int DAT_00B73A20;

// GLOBAL: GAMEMD 0xB77D70
extern int DAT_00B77D70;

// GLOBAL: GAMEMD 0xB77A88
extern int DAT_00B77A88;

// FUNCTION: GAMEMD 0x785740 (decl; reloc)
void FUN_00785740(int value);

struct Obj_007ACD30
{
    int Count;                  // +0x00
    int unknown_04;             // +0x04
    String_007B4620* Items;     // +0x08

    void FUN_007ACD30();
};

struct Obj_00781380
{
    int unknown_00;
    int Value;      // +0x04
};

// GLOBAL: GAMEMD 0xB77DC8
extern unsigned int DAT_00B77DC8;

// GLOBAL: GAMEMD 0xB77908
// GLOBAL: GAMEMD 0xB77900 -- counted array: count +0x00, items +0x08.
struct Vec_00B77900
{
    int count;                    // +0x00
    int unknown_04;               // +0x04
    Entry_00B77908* data;         // +0x08
};
extern Vec_00B77900 DAT_00B77900;

// GLOBAL: GAMEMD 0xB777B0
extern Entry_00B77908 DAT_00B777B0;

// GLOBAL: GAMEMD 0xB777D4 -- the +0x24 name field of DAT_00B777B0.
extern char DAT_00B777D4[];

// LIBRARY: GAMEMD 0x7C8D20 -- CRT _stricmp.
extern "C" int __cdecl _stricmp(const char* a, const char* b);

struct Value_007AE180
{
    int unknown_00;
};

struct Value_007AE8E0
{
    int unknown_00[0x43];
};

GG_STATIC_ASSERT(sizeof(Value_007AE8E0) == 0x10C);

struct Table_007AE180 : public HashTable_006249A0<String_007B4620, Value_007AE180>
{
    bool FUN_007AE180(const String_007B4620& key, Value_007AE180** out);
    bool FUN_007AE7C0(const String_007B4620& key, Value_007AE180** out);
};

struct Table_007ADC60 : public HashTable_006249A0<String_007B4620, Entry_00B77908>
{
    bool FUN_007ADC60(const String_007B4620& key, Entry_00B77908** out);
};

struct Table_007AE8E0 : public HashTable_006249A0<String_007B4620, Value_007AE8E0>
{
    bool FUN_007AE8E0(const String_007B4620& key, Value_007AE8E0** out);
};

// FUNCTION: GAMEMD 0x734E60 (decl; reloc)
const wchar_t* FUN_00734E60(const char* label, int* out, const char* file, int line);



// FUNCTION: GAMEMD 0x622820 (decl; reloc)
void FUN_00622820(HWND window, int id);





// FUNCTION: GAMEMD 0x79DB50 (decl; reloc)
int __stdcall FUN_0079DB50(HWND window, unsigned int message, unsigned int wparam, long lparam);

// FUNCTION: GAMEMD 0x793280 (decl; reloc)
int __stdcall FUN_00793280(HWND window, unsigned int message, unsigned int wparam, long lparam);





// A record with a name (+0x04) and a flag word (+0x08), as ordered by the
// callbacks below.
struct Obj_00781CC0
{
    int unknown_00;
    const char* Name;   // +0x04
    int Flag;           // +0x08
};

// FUNCTION: GAMEMD 0x781FB0 (decl; reloc)
void FUN_00781FB0(void* object, bool flag);

// FUNCTION: GAMEMD 0x782320 (decl; reloc)
void FUN_00782320(void* object, bool flag);

// FUNCTION: GAMEMD 0x782BB0 (decl; reloc)
void FUN_00782BB0(void* object, bool flag);

// GLOBAL: GAMEMD 0xB77E48
extern int DAT_00B77E48;

// FUNCTION: GAMEMD 0x5E2700 (decl; reloc)
void __cdecl FUN_005E2700(int id, const wchar_t* format, ...);

// FUNCTION: GAMEMD 0x5E2CD0 (decl; reloc)
int FUN_005E2CD0(const wchar_t* text, int a, void* proc, bool b);

// FUNCTION: GAMEMD 0x735120 (decl; reloc)
const wchar_t* FUN_00735120(const char* text);

// FUNCTION: GAMEMD 0x77EBA0 (decl; reloc)
int FUN_0077EBA0(String_007B4620* name);

// LIBRARY: GAMEMD 0x7CA564 -- CRT swprintf.
extern "C" int __cdecl swprintf(wchar_t* buffer, const wchar_t* format, ...);

// GLOBAL: GAMEMD 0xB77DC1
extern char DAT_00B77DC1;

// GLOBAL: GAMEMD 0x7EEF28
extern int DAT_007EEF28;

// GLOBAL: GAMEMD 0xB73684
extern HANDLE DAT_00B73684[];

// GLOBAL: GAMEMD 0xB76E24
extern String_007B4620 DAT_00B76E24;

// GLOBAL: GAMEMD 0xB76990
extern HashTable_006249A0<String_007B4620, int> DAT_00B76990;

// FUNCTION: GAMEMD 0x7350C0 (decl; reloc)
const char* FUN_007350C0(void* player);



// FUNCTION: GAMEMD 0x4E34A0 (decl; reloc)
void FUN_004E34A0(void* object, int slot, int value);

// FUNCTION: GAMEMD 0x5E93F0 (decl; reloc)
bool FUN_005E93F0(void* player);

// FUNCTION: GAMEMD 0x7A0EA0
void FUN_007A0EA0(const char* name, int value);

// GLOBAL: GAMEMD 0xA8DA90 -- the eight player slots.
extern void* DAT_00A8DA90[8];

// GLOBAL: GAMEMD 0xB76440
extern int DAT_00B76440[8];

// FUNCTION: GAMEMD 0x792BE0 (decl; reloc)
void FUN_00792BE0(int mode, WideString_007B66C0* text, int flag);

// FUNCTION: GAMEMD 0x797640 (decl; reloc)
void FUN_00797640(int mode);

// GLOBAL: GAMEMD 0xA8B244
extern int DAT_00A8B244;

// GLOBAL: GAMEMD 0xB77DF4
extern int DAT_00B77DF4;

// GLOBAL: GAMEMD 0xB77E60
extern int DAT_00B77E60;

// GLOBAL: GAMEMD 0xB77E64
extern int DAT_00B77E64;

// FUNCTION: GAMEMD 0x5EC880 (decl; reloc)
void FUN_005EC880(HWND window, int a, int b, int c);

// GLOBAL: GAMEMD 0xA8E050 -- per-slot port numbers.
extern short DAT_00A8E050[];

// GLOBAL: GAMEMD 0x84A1F0 -- control ids, per slot.
extern int DAT_0084A1F0[];

// GLOBAL: GAMEMD 0xB75F54
extern char DAT_00B75F54[];

// FUNCTION: GAMEMD 0x6C6D00 (decl; reloc)
void __cdecl FUN_006C6D00();

// FUNCTION: GAMEMD 0x6C6DE0 (decl; reloc)
void __cdecl FUN_006C6DE0();

// GLOBAL: GAMEMD 0xB77E40
extern char DAT_00B77E40;

// GLOBAL: GAMEMD 0xB76230
extern WideString_007B66C0 DAT_00B76230;

// A 0x10C-byte record of the table at 0xB76AE8 (count 0xB76AE0); the word at
// +0x28 is the sort key.
struct Record_00B76AE8
{
    char unknown_00[0x28];
    int Key;                // +0x28
    char unknown_2C[0xE0];
};

GG_STATIC_ASSERT(sizeof(Record_00B76AE8) == 0x10C);

// GLOBAL: GAMEMD 0xB76AE8
// GLOBAL: GAMEMD 0xB76AE0 -- counted array: count +0x00, items +0x08.
struct Vec_00B76AE0
{
    int count;                    // +0x00
    int unknown_04;               // +0x04
    Record_00B76AE8* data;        // +0x08
};
extern Vec_00B76AE0 DAT_00B76AE0;

struct Item_007830C0
{
    int Index;      // +0x00
    int Key;        // +0x04
    int Flag;       // +0x08
};

// FUNCTION: GAMEMD 0x7A1330 (decl; reloc)
void __cdecl FUN_007A1330();

// FUNCTION: GAMEMD 0x7A1060 (decl; reloc)
void __cdecl FUN_007A1060();

// FUNCTION: GAMEMD 0x783C80 (decl; reloc)
void FUN_00783C80(int, unsigned char);

// GLOBAL: GAMEMD 0xB77780
extern int DAT_00B77780;

// GLOBAL: GAMEMD 0xB77CE0
extern int DAT_00B77CE0;

// GLOBAL: GAMEMD 0xB736F4
extern int DAT_00B736F4;


// FUNCTION: GAMEMD 0x77D710 (decl; reloc)
void __cdecl FUN_0077D710();

// GLOBAL: GAMEMD 0xAC10C8
extern int DAT_00AC10C8;

struct Item_007835C0
{
    int Index;          // +0x00 -- record index in the table at 0xB77908
    const char* Name;   // +0x04
    int Flag;           // +0x08
};

// GLOBAL: GAMEMD 0xA83D10
extern ThemeClass DAT_00A83D10;
// GLOBAL: GAMEMD 0xB779BC
extern int DAT_00B779BC;
// GLOBAL: GAMEMD 0xB779F0
extern int DAT_00B779F0;
// GLOBAL: GAMEMD 0xB76234
extern int DAT_00B76234;
// GLOBAL: GAMEMD 0xB7690C
extern int DAT_00B7690C;
// FUNCTION: GAMEMD 0x5EE350 (decl; reloc)
void FUN_005EE350(int value);

#endif // GG_MATCH_NETWORK_WONLINE_LEAF_METHODS_H
