// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /MT /Op /Ob2
// Measured /Op retains the native divide-by-60 instruction; /Ob2 emits the
// three dynamic initializers directly. All existing owner rows remain exact.
//   Original translation unit coopcamp.cpp. The name is the source-file string at 0x81f370
//   in retail gamemd.exe v1.001, passed by the assert at 0x49dc91 inside this object's
//   code range (0x49b180-0x49f0df). Functions are in ascending retail address order.
//
// List<INIClass::INISection*> constructor. Retail 0x49E8E0 seats both
// sentinel nodes (0x7E1B0C), the GenericList table (0x7E1B04), links the head
// to the tail, then seats the derived table 0x7E1AFC (RTTI names it
// List<INIClass::INISection*>). Ten callers construct INIClass objects.
//
//   Provenance note: own-binary-via-Ghidra. Direct retail RTTI confirms the non-const
// char* specialization and its zero-offset dynamic base. All entry-origin
// spans and both seven-slot address points are verified against the pinned PE.
// The DynamicVectorClass deleting-dtor full span requires /GX disabled; other
// methods are tested independently. Vtable weak defaults are conditional, not
// final-link proof. The separate const-char* family is not described here.
//
//   Provenance note: own-binary-via-Ghidra. Direct retail RTTI names the two types
// and confirms DynamicVectorClass<DynamicVectorClass<char*>*> derives from
// VectorClass<DynamicVectorClass<char*>*> at offset zero. Entry-origin spans
// and both seven-slot address points were checked against the pinned PE.
// The dynamic deleting-dtor full span needs /GX disabled; the remaining
// tested bodies are exact with /GX as well. Vtable weak defaults are conditional
// slot evidence, not final-link proof. The capacity constructors replace
// address-bound PodElem4 stand-ins; no complete pointee-layout or original-TU
// claim is made.

#include "FUNCTION.H"
#include <math.h>
#include "mathtbl_init_shapes.h"
#include <string.h>
#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "_layout/node_name_type.h"
#pragma intrinsic(pow)

#include "mp_cooperative.h"
#include "ccini_class_methods.h"
#include "_layout/ini_class_default_ctor.h"
#include "ccini_class_default_ctor.h"
#include "ccfile_class.h"
#include "_layout/house_type_class.h"
#include "_layout/house_class.h"
#include "trivial_tu057_methods.h"
#include "trig_table_functions_004cac40.h"


template class DynamicVectorClass<char*>;

// VTABLE: GAMEMD 0x007E5BC4 -- DynamicVectorClass<char*>.
// VTABLE: GAMEMD 0x007E5C24 -- VectorClass<char*>.
typedef VectorClass<char*> GgCharPtrVector;
typedef DynamicVectorClass<char*> GgCharPtrDynamicVector;
GG_STATIC_ASSERT(sizeof(char*) == 4);
GG_STATIC_ASSERT(sizeof(GgCharPtrVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgCharPtrVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCharPtrVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCharPtrVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCharPtrVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgCharPtrVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgCharPtrDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgCharPtrDynamicVector, CapacityIncrement) == 0x14);


template class DynamicVectorClass<DynamicVectorClass<char*>*>;

// VTABLE: GAMEMD 0x007E5BE4 -- DynamicVectorClass<DynamicVectorClass<char*>*>.
// VTABLE: GAMEMD 0x007E5C04 -- VectorClass<DynamicVectorClass<char*>*>.
typedef VectorClass<DynamicVectorClass<char*>*> GgNestedCharVector;
typedef DynamicVectorClass<DynamicVectorClass<char*>*> GgNestedCharDynamicVector;
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<char*>*) == 4);
GG_STATIC_ASSERT(sizeof(GgNestedCharVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgNestedCharVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgNestedCharVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgNestedCharVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgNestedCharVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgNestedCharVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgNestedCharDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgNestedCharDynamicVector, CapacityIncrement) == 0x14);

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).



// SYNTHETIC: GAMEMD 0x49B180
// Compiler-generated dynamic initializer for the native double storage.
// GLOBAL: GAMEMD 0x89F5A0
double DAT_0089F5A0 = FUN_004CAC40(2.0 * pow(256.0, 2.0));

// SYNTHETIC: GAMEMD 0x49B1B0
// GLOBAL: GAMEMD 0x89F670
double DAT_0089F670 = DAT_0089F5A0 / 60.0;

// SYNTHETIC: GAMEMD 0x49B1D0
// GLOBAL: GAMEMD 0x89F658
double DAT_0089F658 = 1.0 / DAT_0089F670;

// SYNTHETIC: GAMEMD 0x0049B350
// GLOBAL: GAMEMD 0x0089F660
MathTblCoord DAT_0089F660;

// FUNCTION: GAMEMD 0x49B420
// Tail-calls a method on a global object.
void FUN_0049B420(int a1, int a2)
{
    FUN_0049E510(DAT_0089F518, a2);
}


struct Arg1_0049D0C0;
struct Arg1_0049D0F0;
struct Arg2_0049D0C0;
struct Arg2_0049D0F0;
struct Obj_0049D0C0;
struct Obj_0049D0F0;

struct Arg1_0049D0C0
{
    int unknown_00;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Arg1_0049D0C0, unknown_00) == 0x0);

struct Arg1_0049D0F0
{
    int unknown_00;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Arg1_0049D0F0, unknown_00) == 0x0);

struct Arg2_0049D0C0
{
    int unknown_00;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Arg2_0049D0C0, unknown_00) == 0x0);

struct Arg2_0049D0F0
{
    int unknown_00;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Arg2_0049D0F0, unknown_00) == 0x0);

struct Obj_0049D0C0
{
    char unknown_00[0x14];
    int unknown_14;   // +0x0014
    int unknown_18;   // +0x0018
    char unknown_1C[0x50];
    unsigned char unknown_6C;   // +0x006C
    // FUNCTION: GAMEMD 0x49D0C0
    unsigned char FUN_0049D0C0(Arg1_0049D0C0* a1, Arg2_0049D0C0* a2);
};
GG_STATIC_ASSERT(offsetof(Obj_0049D0C0, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_0049D0C0, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(Obj_0049D0C0, unknown_6C) == 0x6C);

struct Obj_0049D0F0
{
    char unknown_00[0x30];
    int unknown_30;   // +0x0030
    int unknown_34;   // +0x0034
    char unknown_38[0x34];
    unsigned char unknown_6C;   // +0x006C
    // FUNCTION: GAMEMD 0x49D0F0
    unsigned char FUN_0049D0F0(Arg1_0049D0F0* a1, Arg2_0049D0F0* a2);
};
GG_STATIC_ASSERT(offsetof(Obj_0049D0F0, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(Obj_0049D0F0, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(Obj_0049D0F0, unknown_6C) == 0x6C);

extern char DAT_0089F118[];

// The value of one hexadecimal digit, 0 for any other character.
inline int HexDigit(char c)
{
    if (c <= '9' && c >= '0')
        return c - '0';
    if (c <= 'f' && c >= 'a')
        return c - 'a' + 10;
    if (c <= 'F' && c >= 'A')
        return c - 'A' + 10;
    return 0;
}

extern char DAT_0089ED18[];

// LIBRARY: GAMEMD 0x7C9A31 isalnum
extern "C" int __cdecl isalnum(int c);

// The upper-case hexadecimal digit of a nibble, 0 when out of range.
inline char HexChar(int v)
{
    if (v < 0 || v > 15)
        return 0;
    if (v < 10)
        return (char)(v + '0');
    return (char)(v + '7');
}

// FUNCTION: GAMEMD 0x49B540
// Copies a string into the shared decode buffer, turning "=" followed by up to two
// hexadecimal digits into the byte they spell; returns the buffer.
char* __fastcall FUN_0049B540(const char* text)
{
    char* out = DAT_0089F118;
    while (*text != 0) {
        if (*text == '=') {
            if (text[1] == 0)
                break;
            *out = HexDigit(text[1]);
            text++;
            if (text[1] != 0) {
                *out = *out << 4;
                *out |= HexDigit(text[1]);
                text++;
            }
        } else {
            *out = *text;
        }
        text++;
        out++;
    }
    *out = 0;
    return DAT_0089F118;
}

// FUNCTION: GAMEMD 0x49B660
CoopCampaignClass* CoopCampaignClass::FUN_0049B660(const unsigned short* first, const unsigned short* second)
{
    if (first)
        strcpy(Name, NarrowName_007350C0(first));
    else
        Name[0] = 0;
    if (second)
        strcpy(Name2, NarrowName_007350C0(second));
    else
        Name2[0] = 0;
    unknown_14 = -2;
    unknown_30 = -2;
    unknown_18 = -2;
    unknown_34 = -2;
    unknown_3C = 0;
    unknown_44 = -1;
    unknown_38 = -1;
    unknown_6C = false;
    unknown_40 = 0;
    unknown_48 = 0;
    unknown_4C = 0;
    unknown_50 = 0;
    unknown_54 = 0;
    unknown_58 = 0;
    unknown_5C = 0;
    unknown_68 = 0;
    unknown_60 = 0;
    unknown_64 = 0;
    return this;
}

// Two short name strings stored back to back; only the starts of the two
// buffers are established by the body (the length of the second is not).
struct NamePair_0049B760
{
    char First[0x1C];   // +0x00
    char Second[1];     // +0x1C
    void FUN_0049B760(const unsigned short* first, const unsigned short* second);
};
GG_STATIC_ASSERT(offsetof(NamePair_0049B760, First) == 0x00);
GG_STATIC_ASSERT(offsetof(NamePair_0049B760, Second) == 0x1C);

// FUNCTION: GAMEMD 0x49B760
// Stores two UTF16 names as narrow strings, or an empty string for a missing name.
void NamePair_0049B760::FUN_0049B760(const unsigned short* first, const unsigned short* second)
{
    if (first)
        strcpy(First, NarrowName_007350C0(first));
    else
        First[0] = 0;
    if (second)
        strcpy(Second, NarrowName_007350C0(second));
    else
        Second[0] = 0;
}

// GLOBAL: GAMEMD 0xA80228 -- the house registry (Items +0x04 = 0xA8022C, Count +0x10 = 0xA80238).
extern DynamicVectorClass<HouseClass*> DAT_00A80228;
// STRING: GAMEMD 0x81B41C "Loser", 0x81B424 "Winner", 0x81F03C the score line format.
extern const char DAT_0081B41C[]; // STRING: GAMEMD 0x0081B41C
extern const char DAT_0081B424[]; // STRING: GAMEMD 0x0081B424
extern const char DAT_0081F03C[]; // STRING: GAMEMD 0x0081F03C
extern "C" void __cdecl FUN_004068E0(const char* format, ...);
// FUNCTION: GAMEMD 0x7350C0 (decl; reloc) -- narrow a UTF16 name into a shared buffer.
const char* NarrowName_007350C0(const unsigned short* name);
extern "C" unsigned short* __cdecl wcscpy(unsigned short* dst, const unsigned short* src);

// FUNCTION: GAMEMD 0x49B7E0
// Fill a score entry from the first (second == 0) or the next human house that takes part: name, colour scheme,
// winner count, losses, kills, production and score; the entry is traced to the debug log.
void __fastcall FUN_0049B7E0(ScoreEntry_00A8D1FC* entry, char second)
{
    int count = DAT_00A80228.Count;
    for (int i = 0; i < count; i++) {
        HouseClass* house = DAT_00A80228.Items[i];
        if (house == 0 || house->Type->MultiplayPassive == true || !house->IsHumanPlayer)
            continue;
        if (second == 0) {
            entry->unknown_2C = 0;
            wcscpy(entry->Name, house->UIName);
            entry->unknown_30[0] = 0;
            entry->unknown_40[0] = 0;
            entry->unknown_50[0] = 0;
            entry->unknown_60[0] = 0;
            entry->unknown_28 = house->ColorSchemeIndex;
            if (!house->Defeated)
                entry->unknown_2C++;
            int kills = 0;
            int k;
            for (k = 0; k < 20; k++)
                kills += house->KilledUnitsOfHouses[k];
            for (k = 0; k < count; k++)
                kills += house->KilledBuildingsOfHouses[k];
            entry->unknown_40[0] = kills;
            entry->unknown_30[0] = house->TotalKilledUnits + house->TotalKilledBuildings;
            int built = house->ActiveBuildingTypes.FUN_0049FB60();
            built += house->ActiveUnitTypes.FUN_0049FB60();
            built += house->ActiveInfantryTypes.FUN_0049FB60();
            built += house->ActiveAircraftTypes.FUN_0049FB60();
            entry->unknown_50[0] = house->TotalKilledUnits + house->TotalKilledBuildings + built;
            if (house->PointTotal > 0)
                entry->unknown_60[0] += house->PointTotal;
            FUN_004068E0(DAT_0081F03C, NarrowName_007350C0(entry->Name), entry->unknown_2C > 0 ? DAT_0081B424 : DAT_0081B41C,
                         entry->unknown_28, entry->unknown_30[0], entry->unknown_40[0], entry->unknown_50[0],
                         entry->unknown_60[0]);
            return;
        }
        second = 0;
    }
}

// STRING: GAMEMD 0x81F0F8 "coopsave.ini"
extern const char DAT_0081F0F8[]; // STRING: GAMEMD 0x0081F0F8
// FUNCTION: GAMEMD 0x49B430 (decl; reloc) -- the hexadecimal digit of a nibble.
char __fastcall FUN_0049B430(int nibble);

// The encoder the save-file code expands inline: the first digit is spelled out, the second comes from 0x49B430.
inline const char* CoopEncode(const char* text)
{
    int n = 0;
    while (*text != 0) {
        if (n >= 0x3FD)
            break;
        if (isalnum(*text) == 0) {
            DAT_0089ED18[n++] = '=';
            DAT_0089ED18[n++] = HexChar(*text >> 4);
            DAT_0089ED18[n++] = FUN_0049B430(*text & 0xF);
        } else {
            DAT_0089ED18[n++] = *text;
        }
        text++;
    }
    DAT_0089ED18[n] = 0;
    return DAT_0089ED18;
}

// GLOBAL: GAMEMD 0x89F570 -- the records of the 0x89F518 list, 0x4C bytes each: +0x08 is the
// number of name triples, +0x0C the table of 0x104-byte names.
struct CoopRecord_0089F570
{
    char unknown_00[4];
    const unsigned short* unknown_04;  // +0x04 the wide display name
    signed char unknown_08;    // +0x08
    char unknown_09[3];
    char (*unknown_0C)[0x104]; // +0x0C
    char unknown_10[0x3C];
};
GG_STATIC_ASSERT(sizeof(CoopRecord_0089F570) == 0x4C);
GG_STATIC_ASSERT(offsetof(CoopRecord_0089F570, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(CoopRecord_0089F570, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(CoopRecord_0089F570, unknown_0C) == 0x0C);
extern CoopRecord_0089F570* DAT_0089F570;
// GLOBAL: GAMEMD 0x89F574 -- the record count.
extern int DAT_0089F574;
// GLOBAL: GAMEMD 0x89F578 -- set once the list is loaded.
extern char DAT_0089F578;
// FUNCTION: GAMEMD 0x49DB00 (decl; reloc) -- loads the 0x89F518 list.
void __fastcall FUN_0049DB00(void* list);

// FUNCTION: GAMEMD 0x49CAF0
// Selects record `a` of the list: clears the running totals, and when it is a different
// record than before replaces the name table with a randomly shifted copy of its names.
bool CoopCampaignClass::FUN_0049CAF0(int a)
{
    if (DAT_0089F578 == 0)
        FUN_0049DB00(DAT_0089F518);
    if (a >= 0 && a < DAT_0089F574) {
        CoopRecord_0089F570* record = DAT_0089F570 + a;
        unknown_6C = true;
        unknown_38 = -1;
        unknown_48 = 0;
        unknown_4C = 0;
        unknown_50 = 0;
        unknown_54 = 0;
        unknown_60 = 0;
        unknown_64 = 0;
        unknown_58 = 0;
        unknown_5C = 0;
        unknown_68 = 0;
        if (unknown_44 != a) {
            if (unknown_3C != 0) {
                for (int i = 0; i < unknown_40; i++) {
                    if (unknown_3C[i] != 0)
                        delete unknown_3C[i];
                }
                delete unknown_3C;
            }
            unknown_3C = 0;
            unknown_40 = 0;
            unknown_3C = new char*[record->unknown_08];
            int i = 0;
            if (record->unknown_08 > 0) {
                int offset = 0;
                do {
                    int shift = MPCoopScenario_00A8B230->Random.FUN_0065C7E0(0, 2);
                    unknown_3C[i] = new char[0x104];
                    strncpy(unknown_3C[i], record->unknown_0C[offset + shift], 0x103);
                    i++;
                    offset += 3;
                } while (i < record->unknown_08);
            }
            unknown_40 = record->unknown_08;
            unknown_38 = 0;
        }
        unknown_44 = a;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x49D0C0
// Branching.
unsigned char Obj_0049D0C0::FUN_0049D0C0(Arg1_0049D0C0* a1, Arg2_0049D0C0* a2)
{
    if (unknown_6C != 0)
    {
        a1->unknown_00 = unknown_14;
        a2->unknown_00 = unknown_18;
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x49D0F0
// Branching.
unsigned char Obj_0049D0F0::FUN_0049D0F0(Arg1_0049D0F0* a1, Arg2_0049D0F0* a2)
{
    if (unknown_6C != 0)
    {
        a1->unknown_00 = unknown_30;
        a2->unknown_00 = unknown_34;
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x49D120
// True when coopsave.ini holds the section named by the two encoded names of this campaign.
bool CoopCampaignClass::FUN_0049D120()
{
    if (Name[0] == 0 || Name2[0] == 0)
        return false;
    CCFileClass file(DAT_0081F0F8);
    CCINIClass ini;
    if (!ini.ReadCCFile(&file, false, false)) {
        file.Close();
        return false;
    }
    file.Close();
    char key[100];
    strcpy(key, CoopEncode(Name));
    strcat(key, CoopEncode(Name2));
    return ini.GetSection(key) != 0;
}

// STRING: GAMEMD 0x81F19C "CurrentMap", 0x81F114 "Map%d", 0x81F108 "undefined"
extern const char DAT_0081F19C[]; // STRING: GAMEMD 0x0081F19C
extern const char DAT_0081F114[]; // STRING: GAMEMD 0x0081F114
extern const char DAT_0081F108[]; // STRING: GAMEMD 0x0081F108
extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

// FUNCTION: GAMEMD 0x49D390
// Read back the map saved for this campaign from coopsave.ini into `map` (0x104 bytes); true when the entry is
// still the "undefined" placeholder.
bool CoopCampaignClass::FUN_0049D390(char* map)
{
    if (Name[0] != 0 && Name2[0] != 0) {
        CCFileClass file(DAT_0081F0F8);
        CCINIClass ini;
        if (!ini.ReadCCFile(&file, false, false)) {
            file.Close();
            return false;
        }
        file.Close();
        char key[100];
        strcpy(key, CoopEncode(Name));
        strcat(key, CoopEncode(Name2));
        int current = ini.FUN_005276D0(key, DAT_0081F19C, 0);
        char label[32];
        sprintf(label, DAT_0081F114, current + 1);
        ini.FUN_00528A10(key, label, DAT_0081F108, map, 0x104);
        if (strcmp(map, DAT_0081F108) == 0)
            return true;
    }
    return false;
}


// GLOBAL: GAMEMD 0xA83C98 -- HouseTypeClass::Array.
extern DynamicVectorClass<HouseTypeClass*> HouseTypeArray;

// FUNCTION: GAMEMD 0x49D9F0
// Resolve a country by its display name or INI ID and answer its position in the house-type array. The
// "<random>" sentinel answers -2, an unknown name -1.
int FUN_0049D9F0(const char* name)
{
    if (_stricmp(name, "<random>") == 0)
        return -2;

    if (name != 0) {
        for (int i = 0; i < HouseTypeArray.Count; i++) {
            HouseTypeClass* type = HouseTypeArray.Items[i];

            if (_stricmp(type->Name, name) == 0 || _stricmp(type->ID, name) == 0)
                return i;
        }
    }

    return -1;
}


// TEMPLATE: GAMEMD 0x49E8E0
// ??0?$List@PAUINISection@INIClass@@@@QAE@XZ
// VC6 cannot instantiate a constructor alone; only its visible body is emitted.
// The instantiation also yields the vtable 0x7E1AFC and its scalar deleting
// destructor.
// SYNTHETIC: GAMEMD 0x40E4C0 -- List<INISection*> scalar deleting destructor.
template class List<INIClass::INISection*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049E950
// FUNCTION: GAMEMD 0x0049E980
// FUNCTION: GAMEMD 0x0049E9A0
// FUNCTION: GAMEMD 0x0049EA30
// FUNCTION: GAMEMD 0x0049EA70
// FUNCTION: GAMEMD 0x0049EB20
// FUNCTION: GAMEMD 0x0049EE10
// FUNCTION: GAMEMD 0x0049EE60
// FUNCTION: GAMEMD 0x0049EF10
// FUNCTION: GAMEMD 0x0049EF40
// FUNCTION: GAMEMD 0x0049EF80
// FUNCTION: GAMEMD 0x0049EFA0
template class VectorClass<char*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049E9B0
// FUNCTION: GAMEMD 0x0049E9E0
// FUNCTION: GAMEMD 0x0049EA00
// FUNCTION: GAMEMD 0x0049EA10
IndexClassRaw::IndexClassRaw()
{
}

// FUNCTION: GAMEMD 0x0049EB50
// FUNCTION: GAMEMD 0x0049EB90
// FUNCTION: GAMEMD 0x0049EC40
// FUNCTION: GAMEMD 0x0049EC70
// FUNCTION: GAMEMD 0x0049ECB0
// FUNCTION: GAMEMD 0x0049ECD0
// FUNCTION: GAMEMD 0x0049ED30
// FUNCTION: GAMEMD 0x0049EDE0
// FUNCTION: GAMEMD 0x0049EFF0
// FUNCTION: GAMEMD 0x0049F040
// FUNCTION: GAMEMD 0x0049F090
template class VectorClass<DynamicVectorClass<char*>*>;
