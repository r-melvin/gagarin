// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Functions of the online-services translation unit (retail text
// 0x77B690..0x7AF0AF; its assertion path string 0x84A430 is
// "D:\ra2mdpost\wonline.cpp"). Run-time initialisers and atexit cleanups of
// the file-scope objects come first, then the free helpers, in retail
// address order. All names are placeholders.
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy
//   /Ob2: retail inlines the record search 0x77D240 into 0x77D4C0.
#define NO_STRICT
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "wonline.h"
#include "../core/header_init_shapes.h"
#include "../core/hash_table_view.h"
#include "../audio/theme_class_methods.h"
#include "../platform/input_manager_class_methods.h"
#include "../ui/ui_begin_dialog_methods.h"
#include "../ui/ui_updated_methods.h"
#include "../ui/gscreen_class_render_methods.h"

// LIBRARY: GAMEMD 0x7CA564 -- CRT swprintf.
extern "C" int __cdecl swprintf(wchar_t* buffer, const wchar_t* format, ...);
// LIBRARY: GAMEMD 0x7CA405 -- CRT wcslen.
extern "C" size_t __cdecl wcslen(const wchar_t* text);

// ---------------------------------------------------------------------------
// Header initialiser group (see core/header_init_shapes.h).

// GLOBAL: GAMEMD 0xB75F60
extern double DAT_00B75F60;
// GLOBAL: GAMEMD 0x7F7510
const double DAT_007F7510 = 60.0;

// SYNTHETIC: GAMEMD 0x77B6C0
// GLOBAL: GAMEMD 0xB77CD8
double DAT_00B77CD8 = DAT_00B75F60 / DAT_007F7510;
// SYNTHETIC: GAMEMD 0x77B6E0
// GLOBAL: GAMEMD 0xB778E8
double DAT_00B778E8 = 1.0 / DAT_00B77CD8;
// SYNTHETIC: GAMEMD 0x77B860
// GLOBAL: GAMEMD 0xB779F8
HeaderCoordInit DAT_00B779F8(128, 128, 0);

// LIBRARY: GAMEMD 0x77B8C0 -- import thunk OleUninitialize (linker-generated).

// SYNTHETIC: GAMEMD 0x77B8F0 -- atexit cleanup of DAT_00B73AE0.
// GLOBAL: GAMEMD 0xB73AE0
String_007B4620 DAT_00B73AE0;

// ---------------------------------------------------------------------------
// The hash tables of file scope. The teardown at exit is the table
// destructor, inlined into the compiler's cleanup function.

struct Value_00B76640
{
    int unknown_00[0x11];
};
GG_STATIC_ASSERT(sizeof(Value_00B76640) == 0x44);

struct Value_00B76608
{
    int unknown_00[0x43];
};
GG_STATIC_ASSERT(sizeof(Value_00B76608) == 0x10C);

typedef HashTable_006249A0<String_007B4620, Value_00B76640>  Table_00B76640;
typedef HashTable_006249A0<String_007B4620, Value_00B76608> Table_00B76608;
typedef HashTable_006249A0<String_007B4620, Entry_00B77908>  Table_00B77D80;
typedef HashNode_006249A0<String_007B4620, Value_00B76640>  Node_00B76640;
typedef HashNode_006249A0<String_007B4620, Value_00B76608> Node_00B76608;
typedef HashNode_006249A0<String_007B4620, Entry_00B77908>  Node_00B77D80;
GG_STATIC_ASSERT(sizeof(Node_00B76640) == 0x4C);
GG_STATIC_ASSERT(sizeof(Node_00B76608) == 0x114);
GG_STATIC_ASSERT(sizeof(Node_00B77D80) == 0x74);
GG_STATIC_ASSERT(sizeof(Table_00B76640) == 0x38);

// Emptying destructor: every chain is freed (each node's key destroyed),
// then the bucket array is halved down to the floor and freed.
template<class KEY, class VALUE>
HashTable_006249A0<KEY, VALUE>::~HashTable_006249A0()
{
    for (unsigned i = 0; i < this->BucketCount; i++) {
        Node* node = this->Buckets[i];
        while (node != NULL) {
            Node* dead = node;
            node = node->Next;
            delete dead;
        }
        this->Buckets[i] = NULL;
    }
    this->Count = 0;

    while (this->BucketCount > this->MinBuckets && !this->IsFixed) {
        Shrink();
    }
    delete[] this->Buckets;
}

// SYNTHETIC: GAMEMD 0x77C050 -- atexit cleanup of DAT_00B76640 (inlined destructor).
//   Not exact (80%): retail keeps the bucket count in EAX and the floor in ECX
//   through the shrink loop; this build swaps the registers.
// GLOBAL: GAMEMD 0xB76640
Table_00B76640 DAT_00B76640;

// SYNTHETIC: GAMEMD 0x77CA20 -- atexit cleanup of DAT_00B73ACC.
// GLOBAL: GAMEMD 0xB73ACC
String_007B4620 DAT_00B73ACC;
// SYNTHETIC: GAMEMD 0x77CA50 -- atexit cleanup of DAT_00B76E24.
// GLOBAL: GAMEMD 0xB76E24
String_007B4620 DAT_00B76E24;

// SYNTHETIC: GAMEMD 0x77CCD0 -- atexit cleanup of DAT_00B76608 (inlined destructor).
//   Not exact (80%): same register swap as 0x77C050.
// GLOBAL: GAMEMD 0xB76608
Table_00B76608 DAT_00B76608;

// GLOBAL: GAMEMD 0x84A1C4
extern int DAT_0084A1C4;
// GLOBAL: GAMEMD 0x84A1C8
extern int DAT_0084A1C8;
// GLOBAL: GAMEMD 0x84A1D4
extern int DAT_0084A1D4;
// GLOBAL: GAMEMD 0x84A1D8
extern int DAT_0084A1D8;

// SYNTHETIC: GAMEMD 0x77CE10
// GLOBAL: GAMEMD 0xB765F0
int DAT_00B765F0 = DAT_0084A1C8 - DAT_0084A1C4 - 4;
// SYNTHETIC: GAMEMD 0x77CE30
// GLOBAL: GAMEMD 0xB73E3C
int DAT_00B73E3C = DAT_0084A1D8 - DAT_0084A1D4 - 4;

// SYNTHETIC: GAMEMD 0x77CF30 -- atexit cleanup of DAT_00B76AC4.
// GLOBAL: GAMEMD 0xB76AC4
String_007B4620 DAT_00B76AC4;

// GLOBAL: GAMEMD 0xA8B244
extern int DAT_00A8B244;

// FUNCTION: GAMEMD 0x77CF40
int __fastcall FUN_0077CF40()
{
    return DAT_00A8B244 == 3 || DAT_00A8B244 == 1 || DAT_00A8B244 == 2;
}

// FUNCTION: GAMEMD 0x77CF60
int __fastcall FUN_0077CF60()
{
    return DAT_00A8B244 == 2;
}

// SYNTHETIC: GAMEMD 0x77CF90 -- atexit cleanup of DAT_00B76E34.
// GLOBAL: GAMEMD 0xB76E34
String_007B4620 DAT_00B76E34;
// SYNTHETIC: GAMEMD 0x77CFC0 -- atexit cleanup of DAT_00B73B30.
// GLOBAL: GAMEMD 0xB73B30
String_007B4620 DAT_00B73B30;
// SYNTHETIC: GAMEMD 0x77CFF0 -- atexit cleanup of DAT_00B7622C.
// GLOBAL: GAMEMD 0xB7622C
String_007B4620 DAT_00B7622C;
// SYNTHETIC: GAMEMD 0x77D020 -- atexit cleanup of DAT_00B76908.
// GLOBAL: GAMEMD 0xB76908
String_007B4620 DAT_00B76908;
// SYNTHETIC: GAMEMD 0x77D050 -- atexit cleanup of DAT_00B77794.
// GLOBAL: GAMEMD 0xB77794
String_007B4620 DAT_00B77794;
// SYNTHETIC: GAMEMD 0x77D080 -- atexit cleanup of DAT_00B778F4.
// GLOBAL: GAMEMD 0xB778F4
String_007B4620 DAT_00B778F4;
// SYNTHETIC: GAMEMD 0x77D0B0 -- atexit cleanup of DAT_00B778FC.
// GLOBAL: GAMEMD 0xB778FC
String_007B4620 DAT_00B778FC;
// SYNTHETIC: GAMEMD 0x77D0E0 -- atexit cleanup of DAT_00B765EC.
// GLOBAL: GAMEMD 0xB765EC
String_007B4620 DAT_00B765EC;
// SYNTHETIC: GAMEMD 0x77D110 -- atexit cleanup of DAT_00B76900.
// GLOBAL: GAMEMD 0xB76900
String_007B4620 DAT_00B76900;

// FUNCTION: GAMEMD 0x77D190
void __fastcall FUN_0077D190()
{
}

// SYNTHETIC: GAMEMD 0x77D1C0 -- atexit cleanup of DAT_00B76230.
// GLOBAL: GAMEMD 0xB76230
WideString_007B66C0 DAT_00B76230;

// FUNCTION: GAMEMD 0x77D210
// Replaces every space in the text with an underscore.
void __fastcall FUN_0077D210(char* text)
{
    char* p = strchr(text, ' ');
    while (p != NULL) {
        *p = '_';
        p = strchr(p, ' ');
    }
}

// LIBRARY: GAMEMD 0x7C8D20 -- CRT _stricmp.
extern "C" int __cdecl _stricmp(const char* a, const char* b);

// GLOBAL: GAMEMD 0xB77900
extern int DAT_00B77900;
// GLOBAL: GAMEMD 0xB77908
extern Entry_00B77908* DAT_00B77908;

// FUNCTION: GAMEMD 0x77D240
// Index of the record whose +0x24 name equals `name` (case-insensitive), or -1.
int __fastcall FUN_0077D240(String_007B4620* name)
{
    Entry_00B77908* entry = NULL;

    for (int i = 0; i < DAT_00B77900; i++) {
        if (i >= 0 && i < DAT_00B77900) {
            entry = &DAT_00B77908[i];
        }
        if (_stricmp(name->FUN_007B5440(), entry->unknown_24) == 0) {
            return i;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x775940 (decl; reloc)
int __fastcall FUN_00775940(int id);
// FUNCTION: GAMEMD 0x7B7D90 (decl; reloc)
bool __fastcall FUN_007B7D90(void* object);

// GLOBAL: GAMEMD 0xB779C0
extern int DAT_00B779C0;
// GLOBAL: GAMEMD 0xB779DC
extern int DAT_00B779DC;

struct Obj_0077D2A0
{
    unsigned char unknown_00;   // +0x00 -- bit 0 tested
};

// FUNCTION: GAMEMD 0x77D2A0
bool __fastcall FUN_0077D2A0(Obj_0077D2A0* flags)
{
    if (flags == NULL) return false;
    if (flags->unknown_00 & 1) return true;
    if (FUN_00775940(0xC2)) return true;
    if (FUN_00775940(0xC9)) return true;
    return DAT_00B779C0 != 0;
}

// FUNCTION: GAMEMD 0x77D2E0
bool __fastcall FUN_0077D2E0(Obj_0077D2A0* flags, void* object)
{
    if (flags == NULL) return false;
    if (flags->unknown_00 & 1) return true;
    if (FUN_00775940(0xC2)) return true;
    if (FUN_00775940(0xC9)) return true;
    if (FUN_007B7D90(object)) return DAT_00B779C0 != 0;
    return DAT_00B779DC != 0;
}

// FUNCTION: GAMEMD 0x734E60 (decl; reloc)
const wchar_t* __fastcall FUN_00734E60(const char* label, int* out, const char* file, int line);
// FUNCTION: GAMEMD 0x7DDE80 (decl; reloc)
int __cdecl FUN_007DDE80(void* target, const wchar_t* text, int length);

// STRING: GAMEMD 0x84A430
static const char DAT_0084A430[] = "D:\\ra2mdpost\\wonline.cpp";

// FUNCTION: GAMEMD 0x77D350
bool __fastcall FUN_0077D350(void* target)
{
    wchar_t text[256];
    swprintf(text, FUN_00734E60("TXT_BUDDY_FILTER", NULL, DAT_0084A430, 0x369));
    return FUN_007DDE80(target, text, wcslen(text)) == 0;
}

// GLOBAL: GAMEMD 0xB76AF0
extern bool DAT_00B76AF0;
// GLOBAL: GAMEMD 0xB73AD0
extern bool DAT_00B73AD0;
// GLOBAL: GAMEMD 0xB73AA8
extern int DAT_00B73AA8;
// GLOBAL: GAMEMD 0xB73AB0
extern String_007B4620* DAT_00B73AB0;

// Whether the record's +0x24 name is in the list at 0xB73AB0.
static inline bool FUN_0077D4C0_InList(Entry_00B77908* entry)
{
    int count = DAT_00B73AA8;
    String_007B4620 name;
    for (int i = 0; i < count; i++) {
        if (i >= 0 && i < DAT_00B73AA8) name = DAT_00B73AB0[i];
        if (strcmp(name.FUN_007B5400(), entry->unknown_24) == 0) return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x77D4C0
//   Not exact (75% aligned): retail keeps one 4-byte frame slot and shares the
//   exits; this build allocates two slots and duplicates the epilogues.
bool __fastcall FUN_0077D4C0(Entry_00B77908* entry)
{
    if (!DAT_00B76AF0 && !DAT_00B73AD0) return true;
    if (!FUN_00775940(0x113)) return true;

    int index = FUN_0077D240(&DAT_00B73E40);
    Entry_00B77908* found = NULL;
    if (index < 0) return true;
    if (index < DAT_00B77900) found = &DAT_00B77908[index];

    if (DAT_00B76AF0) {
        if (DAT_00B73AD0) {
            if (found != NULL) {
                if (entry == NULL) return false;
                if (_stricmp(found->unknown_2E, entry->unknown_2E) == 0) return true;
            }
            if (entry == NULL) return false;
            return FUN_0077D4C0_InList(entry);
        }
        if (entry == NULL) return false;
        return FUN_0077D4C0_InList(entry);
    }
    if (DAT_00B73AD0 && found != NULL && entry != NULL
        && _stricmp(found->unknown_2E, entry->unknown_2E) == 0) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x77F900 (decl; reloc)
void __fastcall FUN_0077F900();

// FUNCTION: GAMEMD 0x77D710
void __fastcall FUN_0077D710()
{
    FUN_0077F900();
}

// LIBRARY: GAMEMD 0x7C896E -- WS2_32 ordinal 14 (ntohl), import thunk.
extern "C" unsigned long __stdcall ntohl(unsigned long value);

// A four-byte address followed by a port.
struct Address_0077D720
{
    unsigned char unknown_00[4];   // +0x00
    unsigned short unknown_04;      // +0x04
};
GG_STATIC_ASSERT(sizeof(Address_0077D720) == 6);

// The 12-byte value built by 0x53ECE0 from an int, an address and a flag.
struct Value_0053ECE0
{
    // FUNCTION: GAMEMD 0x53ECE0 (decl; reloc)
    Value_0053ECE0(int* first, Address_0077D720* address, int flag);

    int unknown_00;   // +0x00
    int unknown_04;   // +0x04
    int unknown_08;   // +0x08
};
GG_STATIC_ASSERT(sizeof(Value_0053ECE0) == 0xC);

struct Obj_0077D720
{
    char unknown_00[0x18];   // +0x00
    unsigned long unknown_18;   // +0x18 -- network byte order
};
GG_STATIC_ASSERT(offsetof(Obj_0077D720, unknown_18) == 0x18);

// FUNCTION: GAMEMD 0x77D720
//   Not exact (29% aligned): retail zeroes the address as one dword and
//   schedules the octet stores differently.
Value_0053ECE0 __fastcall FUN_0077D720(Obj_0077D720* host)
{
    Address_0077D720 address = { { 0, 0, 0, 0 }, 0 };
    int first = 0;
    unsigned long ip = ntohl(host->unknown_18);
    address.unknown_00[3] = (unsigned char)ip;
    address.unknown_00[2] = (unsigned char)(ip >> 8);
    address.unknown_00[0] = (unsigned char)(ip >> 24);
    address.unknown_00[1] = (unsigned char)(ip >> 16);
    Value_0053ECE0 value(&first, &address, 0);
    return value;
}

// GLOBAL: GAMEMD 0xA83D10
extern ThemeClass DAT_00A83D10;
// STRING: GAMEMD 0x8263A8
static const char DAT_008263A8[] = "INTRO";

// FUNCTION: GAMEMD 0x77D7A0
void __fastcall FUN_0077D7A0(bool start)
{
    if (start) {
        if (!DAT_00A83D10.FUN_00720FD0()) {
            DAT_00A83D10.Stop(false);
            DAT_00A83D10.QueueSong(-2);
        } else {
            int theme = DAT_00A83D10.LastTheme;
            if (theme == -1) theme = DAT_00A83D10.QueuedTheme;
            if (theme == DAT_00A83D10.FindIndex(DAT_008263A8)) {
                DAT_00A83D10.Stop(false);
                DAT_00A83D10.QueueSong(-2);
            }
        }
    } else {
        DAT_00A83D10.QueueSong(-3);
    }
}

// FUNCTION: GAMEMD 0x5E26C0 (decl; reloc)
void* __fastcall FUN_005E26C0();


// FUNCTION: GAMEMD 0x77D820
bool __fastcall FUN_0077D820()
{
    UI::Updated();
    void* window = FUN_005E26C0();
    if (window != NULL) {
        InvalidateRect(window, NULL, 1);
    }
    return false;
}

// FUNCTION: GAMEMD 0x78D120 (decl; reloc)
int __stdcall FUN_0078D120(void* window, unsigned int message, unsigned int wparam, long lparam);
// FUNCTION: GAMEMD 0x7759E0 (decl; reloc)
void __fastcall FUN_007759E0(void* window, bool (__fastcall* idle)(), int unknown, bool flag1, bool flag2);

// GLOBAL: GAMEMD 0xA8ED9C
extern bool DAT_00A8ED9C;
struct Obj_00A8B230
{
    char unknown_0000[0x35A2];   // +0x0000
    bool unknown_35A2;           // +0x35A2
};
GG_STATIC_ASSERT(offsetof(Obj_00A8B230, unknown_35A2) == 0x35A2);

// GLOBAL: GAMEMD 0xA8B230
extern Obj_00A8B230* DAT_00A8B230;
// GLOBAL: GAMEMD 0x87F7E8 -- the map, through its GScreenClass part.
extern GScreen_004F4480 GScreen_0087F7E8;

// FUNCTION: GAMEMD 0x77D840
//   The idle callback is chosen by two whole calls: cl merges their common
//   pushes and selects EDX last, as retail does.
void __fastcall FUN_0077D840()
{
    void* window = UI_BeginDialog(0xCF, FUN_0078D120, 0);
    DAT_00A8ED9C = true;
    DAT_0087F770->DoSomething();
    ShowWindow(window, 1);
    void* parent = FUN_005E26C0();
    if (parent != NULL)
        FUN_007759E0(window, FUN_0077D820, 0, true, true);
    else
        FUN_007759E0(window, UI::Updated, 0, true, true);
    DAT_0087F770->DoSomething();
    DAT_00A8ED9C = DAT_00A8B230->unknown_35A2;
    GScreen_0087F7E8.FlagToRedraw(2);
}

// FUNCTION: GAMEMD 0x773E90 (decl; reloc)
void __fastcall FUN_00773E90(const char* page);

// FUNCTION: GAMEMD 0x77D8C0
void __fastcall FUN_0077D8C0()
{
    FUN_00773E90("Battleclans");
}

// FUNCTION: GAMEMD 0x77D8D0
void __fastcall FUN_0077D8D0()
{
    FUN_00773E90("Battleclans");
}

// FUNCTION: GAMEMD 0x77D8E0
void __fastcall FUN_0077D8E0()
{
    FUN_00773E90("Ladder");
}

// FUNCTION: GAMEMD 0x77D8F0
void __fastcall FUN_0077D8F0()
{
    FUN_00773E90("News");
}

// FUNCTION: GAMEMD 0x77D900
void __fastcall FUN_0077D900()
{
    FUN_00773E90("Manage");
}

// GLOBAL: GAMEMD 0xA8B238 -- session game mode.
extern int DAT_00A8B238;

struct Obj_0077D910
{
    char unknown_00[0x14];      // +0x00
    int unknown_14;             // +0x14
    char unknown_18[0x08];      // +0x18
    unsigned unknown_20_0 : 8;  // +0x20 bits 0..7
    unsigned unknown_20_8 : 1;          // +0x20 bit 8
    unsigned unknown_20_9 : 2;  // +0x20 bits 9..10
    unsigned unknown_20_11 : 1;         // +0x20 bit 11
    unsigned unknown_20_12 : 1;         // +0x20 bit 12
};
GG_STATIC_ASSERT(offsetof(Obj_0077D910, unknown_14) == 0x14);
GG_STATIC_ASSERT(sizeof(Obj_0077D910) == 0x24);

// FUNCTION: GAMEMD 0x77D910
//   Not exact (45% aligned): retail spills the bit to a byte local and returns
//   0/1 through EAX.
bool __fastcall FUN_0077D910(Obj_0077D910* flags)
{
    if (DAT_00A8B238 != 4) return false;
    if (flags->unknown_14 != 0) return true;
    bool bit = flags->unknown_20_8;
    return bit;
}

// FUNCTION: GAMEMD 0x77D990
bool __fastcall FUN_0077D990(Obj_0077D910* flags)
{
    if (DAT_00A8B238 != 4) return false;
    return flags->unknown_20_8;
}

// FUNCTION: GAMEMD 0x77D9B0
bool __fastcall FUN_0077D9B0(Obj_0077D910* flags)
{
    if (DAT_00A8B238 != 4) return false;
    return flags->unknown_20_11;
}

// FUNCTION: GAMEMD 0x77D9D0
bool __fastcall FUN_0077D9D0(Obj_0077D910* flags)
{
    if (DAT_00A8B238 != 4) return false;
    return flags->unknown_20_12;
}

// SYNTHETIC: GAMEMD 0x77DA10 -- atexit cleanup of DAT_00B73E40.
String_007B4620 DAT_00B73E40;
// SYNTHETIC: GAMEMD 0x77DA40 -- atexit cleanup of DAT_00B7778C.
// GLOBAL: GAMEMD 0xB7778C
String_007B4620 DAT_00B7778C;

// FUNCTION: GAMEMD 0x7350C0 (decl; reloc)
const char* __fastcall FUN_007350C0(const wchar_t* text);

// GLOBAL: GAMEMD 0xB779C4
extern int DAT_00B779C4;
// GLOBAL: GAMEMD 0xB77D80
extern Table_00B77D80 DAT_00B77D80;
// GLOBAL: GAMEMD 0xB768C0
extern Table_00B77D80 DAT_00B768C0;

// Chain lookup in a table: the value of the node whose key equals `key`, or
// null (inlined at every use).
template<class KEY, class VALUE>
inline VALUE* HashFind_0077DA50(HashTable_006249A0<KEY, VALUE>& table, const KEY& key)
{
    if (table.Count == 0) return 0;

    int hash = table.Hash(&key);
    HashNode_006249A0<KEY, VALUE>* node = table.Buckets[((1 << table.BitWidth) - 1) & hash];

    while (node != 0) {
        if (node->Key == key) break;
        node = node->Next;
    }
    return node != 0 ? &node->Value : 0;
}

// FUNCTION: GAMEMD 0x77DA50
//   Not exact (94% aligned): retail re-tests the value pointer after adding
//   the node offset.
// A fresh copy of the record filed under the lower-cased name, or a zeroed
// one when it is absent; null when allocation fails.
Entry_00B77908* __fastcall FUN_0077DA50(const wchar_t* name)
{
    String_007B4620 key(FUN_007350C0(name));
    key.FUN_007B5B30();

    Entry_00B77908* copy = new Entry_00B77908;
    if (copy == NULL) return NULL;
    memset(copy, 0, sizeof(*copy));

    Entry_00B77908* found;
    if (DAT_00B779C4 != 2) {
        found = HashFind_0077DA50(DAT_00B77D80, key);
    } else {
        found = HashFind_0077DA50(DAT_00B768C0, key);
    }
    if (found != NULL) *copy = *found;
    return copy;
}

// FUNCTION: GAMEMD 0x5E93F0 (decl; reloc)
bool __fastcall FUN_005E93F0(const wchar_t* text);
// FUNCTION: GAMEMD 0x5EDEF0 (decl; reloc)
String_007B4620 __fastcall FUN_005EDEF0(const wchar_t* text);
// FUNCTION: GAMEMD 0x7B7F90 (decl; reloc)
String_007B4620 __fastcall FUN_007B7F90(const WideString_007B66C0& text);
// LIBRARY: GAMEMD 0x7CB550 -- CRT strncat.

// GLOBAL: GAMEMD 0xA8DA90
extern const wchar_t* DAT_00A8DA90[8];
// STRING: GAMEMD 0x84A480
extern const char DAT_0084A480[];
// STRING: GAMEMD 0x817F70
extern const char DAT_00817F70[];

struct Vtbl_00AC116C;
struct Obj_00AC116C
{
    Vtbl_00AC116C* Vtbl;   // +0x00
};
struct Vtbl_00AC116C
{
    void* unknown_00[0x0F];                                      // +0x00
    long (__stdcall* At_3C)(Obj_00AC116C* self, const char* text);   // +0x3C
};
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_3C) == 0x3C);

// GLOBAL: GAMEMD 0xAC116C
extern Obj_00AC116C* DAT_00AC116C;

// FUNCTION: GAMEMD 0x77DB90
void __fastcall FUN_0077DB90()
{
    char text[256];
    strcpy(text, DAT_0084A480);

    for (int i = 0; i < 8; i++) {
        const wchar_t* item = DAT_00A8DA90[i];
        String_007B4620 name;
        if (FUN_005E93F0(item)) {
            WideString_007B66C0 wide(item);
            name = FUN_007B7F90(wide);
        } else {
            name = FUN_005EDEF0(item);
        }
        strncat(text, name.FUN_007B5400(), sizeof(text));
        strncat(text, DAT_00817F70, sizeof(text));
    }
    DAT_00AC116C->Vtbl->At_3C(DAT_00AC116C, text);
}

// LIBRARY: GAMEMD 0x7CD460 -- CRT tmpnam.
// LIBRARY: GAMEMD 0x7CA845 -- CRT fopen.
// LIBRARY: GAMEMD 0x7CA7D8 -- CRT fprintf.
// LIBRARY: GAMEMD 0x7CA75B -- CRT fclose.
// LIBRARY: GAMEMD 0x7CD455 -- CRT remove.
// LIBRARY: GAMEMD 0x7C8EF4 -- CRT sprintf.

// FUNCTION: GAMEMD 0x5E2CD0 (decl; reloc)
int __fastcall FUN_005E2CD0(const wchar_t* text, int buttons, void (__fastcall* idle)(), bool flag);

// STRING: GAMEMD 0x82976C
extern const char DAT_0082976C[];
// STRING: GAMEMD 0x82AF10
extern const char DAT_0082AF10[];
// STRING: GAMEMD 0x829748
extern const char DAT_00829748[];
// GLOBAL: GAMEMD 0xA8ED80
extern bool DAT_00A8ED80;

// FUNCTION: GAMEMD 0x77DC90
// Opens `url` in the system browser (found through a temporary HTML file)
// and waits for the browser to exit or the game to come back to the front.
// Without `quiet` the player is asked first.
void __fastcall FUN_0077DC90(const char* url, int quiet)
{
    char command[272];
    char browser[264];
    char probe[160];
    tmpnam(probe);
    strcat(probe, DAT_0082976C);
    FILE* file = fopen(probe, DAT_0082AF10);
    fprintf(file, "<title>Hi there</title>");
    fclose(file);

    HINSTANCE found = FindExecutableA(probe, NULL, browser);
    remove(probe);

    if ((int)found > 32) {
        if (quiet == 0) {
            if (FUN_005E2CD0(FUN_00734E60("TXT_LAUNCHBROWSER", NULL, DAT_0084A430, 0x576), 4, FUN_0077D710, false) != IDYES) {
                return;
            }
        }

        sprintf(command, DAT_00829748, url);
        STARTUPINFOA startup;
        memset(&startup, 0, sizeof(startup));
        startup.cb = sizeof(startup);
        PROCESS_INFORMATION process;
        if (!CreateProcessA(browser, command, NULL, NULL, FALSE, 0, NULL, NULL, &startup, &process)) return;
        HANDLE handle = process.hProcess;
        if (handle == NULL) return;

        int done = 0;
        FUN_0077F900();
        WaitForInputIdle(handle, 5000);
        do {
            FUN_0077F900();
            Sleep(500);
            DWORD code;
            GetExitCodeProcess(handle, &code);
            if (code != STILL_ACTIVE) done = 1;
            if (DAT_00A8ED80 || GetTopWindow(NULL) == DAT_00B73550 || GetForegroundWindow() == DAT_00B73550) {
                done = 1;
            }
            FUN_0077F900();
        } while (!done);

        FUN_0077F900();
        if (GetTopWindow(NULL) != DAT_00B73550) {
            FUN_0077F900();
            SetForegroundWindow(DAT_00B73550);
            ShowWindow(DAT_00B73550, SW_RESTORE);
            FUN_0077F900();
        }
        for (int i = 10; i != 0; i--) {
            Sleep(100);
            FUN_0077F900();
        }
    } else {
        FUN_005E2CD0(FUN_00734E60("TXT_NOBROWSER", NULL, DAT_0084A430, 0x5BA), 0, FUN_0077D710, false);
    }
}
