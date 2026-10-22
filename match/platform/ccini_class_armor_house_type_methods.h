// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   The armour / land-type / house-type corner of the CCINIClass enumerated
//   reader run, read numerically off the user's retail gamemd.exe v1.001
//   with the local Ghidra CLI. Same contiguous 0x474810..0x475A3D block as
//   ccini_class_small_readers_methods.cpp, whose confirmed ReadString
//   (0x528A10) and WriteString (0x528660) conventions are reused here.
//
//   Table identity confirmed from the binary:
//   0x7E5210 is an array of name pointers reading "none", "flak", ... which
//   is the armour table. The house-type registry's count is read from
//   0xA83CA8 and its item array from 0xA83C9C, twelve bytes apart, the
//   tree's usual vector header; the record's own ID text is inline at +0x24,
//   which the 0x475610 writer copies out with `LEA EDI,[ECX+ESI*4]; ADD
//   EDI,0x24`.
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_ARMOR_HOUSE_TYPE_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_ARMOR_HOUSE_TYPE_METHODS_H

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

// STRING: GAMEMD 0x889F64  ""
extern const char STR_00889F64[];
// STRING: GAMEMD 0x817474  "<none>"
extern const char STR_00817474[];
// STRING: GAMEMD 0x81C008  "<random>"
extern const char STR_0081C008[];

// GLOBAL: GAMEMD 0x7E5210 — the armour name table.
extern const char* DAT_007E5210[];

// FUNCTION: GAMEMD 0x772A50 (decl; reloc) — armour name -> armour index.
int __fastcall FUN_00772A50(const char* name);
// FUNCTION: GAMEMD 0x751590 (decl; reloc) — armour index -> armour name.
const char* __fastcall FUN_00751590(int index);
// FUNCTION: GAMEMD 0x48DFD0 (decl; reloc) — land type -> name.
const char* __fastcall FUN_0048DFD0(int index);
// FUNCTION: GAMEMD 0x48DF80 (decl; reloc) — name -> land type.
int __fastcall FUN_0048DF80(const char* name);

// The house-name helpers the 0x475540 / 0x475610 pair share.
// FUNCTION: GAMEMD 0x510FB0 (decl; reloc) — name -> pseudo-house code.
int __fastcall FUN_00510FB0(const char* name);
// FUNCTION: GAMEMD 0x510F60 (decl; reloc) — is this code a pseudo-house?
bool __fastcall FUN_00510F60(int code);
// FUNCTION: GAMEMD 0x510E10 (decl; reloc) — pseudo-house code -> name. The
// size arrives on the stack and the other two in ECX/EDX, so __fastcall.
void __fastcall FUN_00510E10(int code, char* buffer, int size);
// FUNCTION: GAMEMD 0x5117D0 (decl; reloc) — house-type name -> index, -1 if
// the name is not registered.
int __fastcall FUN_005117D0(const char* name);

// The house-type record. Only the inline ID text at +0x24 is touched, and
// the record is 0x1B0 bytes wide: that is the constant the 0x475540 reader
// hands to operator new.
class HouseType_005113F0
{
public:
    char _pad000[0x24];     // +0x0000
    char ID[0x18C];         // +0x0024

    // FUNCTION: GAMEMD 0x5113F0 (decl; reloc) — the name constructor. The
    // no-throw specification kept /GX, the tree's earlier flag set, from
    // wrapping the
    // new-expression in an unwind funclet retail has no trace of.
    HouseType_005113F0(const char* name) throw();
};
GG_STATIC_ASSERT(offsetof(HouseType_005113F0, ID) == 0x24 &&
                 sizeof(HouseType_005113F0) == 0x1B0);

// The house-type registry: Items at 0xA83C9C, Count at 0xA83CA8.
// Partial registry view through Count; intermediate bytes remain unknown.
struct HouseTypeVector
{
    void*                   _vtable;    // +0x0000
    HouseType_005113F0**    Items;      // +0x0004
    int                     Capacity;   // +0x0008
    char unknown_0C[4];                 // +0x000C
    int                     Count;      // +0x0010
};
GG_STATIC_ASSERT(offsetof(HouseTypeVector, Items) == 0x04 &&
                 offsetof(HouseTypeVector, Count) == 0x10 &&
                 sizeof(HouseTypeVector) == 0x14);

// GLOBAL: GAMEMD 0xA83C98 — the house-type registry.
extern HouseTypeVector DAT_00A83C98;

class CCINI_004753F0
{
public:
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) — INIClass::ReadString.
    int  ReadString(const char* section, const char* key, const char* defaultValue,
                    char* buffer, unsigned int size);
    // FUNCTION: GAMEMD 0x528660 (decl; reloc) — INIClass::WriteString.
    bool WriteString(const char* section, const char* key, const char* value);

    // FUNCTION: GAMEMD 0x4753F0
    int  ReadArmor(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x475460
    bool WriteArmor(const char* section, const char* key, int value);
    // FUNCTION: GAMEMD 0x4754B0
    int  ReadLandType(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x475510
    bool WriteLandType(const char* section, const char* key, int value);
    // FUNCTION: GAMEMD 0x475540
    int  ReadHouseType(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x475610
    bool WriteHouseType(const char* section, const char* key, int value);
};

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_ARMOR_HOUSE_TYPE_METHODS_H
