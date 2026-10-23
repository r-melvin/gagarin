// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU256_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU256_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x87F7E8
extern char DAT_0087F7E8[];
// GLOBAL: GAMEMD 0xA8B538
extern int DAT_00A8B538;
// GLOBAL: GAMEMD 0xB0FE58
extern unsigned char DAT_00B0FE58;
// GLOBAL: GAMEMD 0xB0FE65
extern unsigned char DAT_00B0FE65;
// GLOBAL: GAMEMD 0xB0FE68
extern int DAT_00B0FE68;

// FUNCTION: GAMEMD 0x4AC960 (declaration)
void FUN_004AC960(void*, int, int);
// FUNCTION: GAMEMD 0x637AA0 (declaration)
char FUN_00637AA0();
// Import timeGetTime from WINMM.dll (IAT slot 0x7E1530)
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();


// FUNCTION: GAMEMD 0x730AD0
int __cdecl FUN_00730AD0();
// FUNCTION: GAMEMD 0x730AE0
int __cdecl FUN_00730AE0();
// FUNCTION: GAMEMD 0x731A30
void FUN_00731A30(int a1, int a2);
// FUNCTION: GAMEMD 0x731A90
void __cdecl FUN_00731A90();
// FUNCTION: GAMEMD 0x731BE0
void __cdecl FUN_00731BE0();
// FUNCTION: GAMEMD 0x731CF0
void __cdecl FUN_00731CF0();
// FUNCTION: GAMEMD 0x732CA0
void __cdecl FUN_00732CA0();

// GLOBAL: GAMEMD 0xB0FE6C
extern DynamicVectorClass<TechnoClass*>* DAT_00B0FE6C;
// GLOBAL: GAMEMD 0xA8EC78
extern DynamicVectorClass<TechnoClass*> DAT_00A8EC78;
// GLOBAL: GAMEMD 0xA8B238
extern int DAT_00A8B238;
// GLOBAL: GAMEMD 0x845550
extern int DAT_00845550;
// GLOBAL: GAMEMD 0x845554
extern int DAT_00845554;
// GLOBAL: GAMEMD 0x845558
extern int DAT_00845558;
// GLOBAL: GAMEMD 0x84555C
extern int DAT_0084555C;
// FUNCTION: GAMEMD 0x6379C0 (decl; reloc)
void FUN_006379C0();
// FUNCTION: GAMEMD 0x637A10 (decl; reloc)
void FUN_00637A10();
// FUNCTION: GAMEMD 0x63A120 (decl; reloc)
void FUN_0063A120(bool, bool);
// FUNCTION: GAMEMD 0x732950 (decl; reloc)
void __cdecl FUN_00732950();


typedef DynamicVectorClass<TechnoClass*> UICmndsVector;
GG_STATIC_ASSERT(offsetof(UICmndsVector, Items) == 4);
GG_STATIC_ASSERT(offsetof(UICmndsVector, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(UICmndsVector) == 0x18);
GG_STATIC_ASSERT(offsetof(HouseClass, IsInPlayerControl) == 0x1ED);
GG_STATIC_ASSERT(offsetof(ObjectClass, IsSelected) == 0x83);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, IsSelectableCombatant) == 0xDBC);

// GLOBAL: GAMEMD 0xA8ECB8
extern DynamicVectorClass<TechnoClass*> DAT_00A8ECB8;
// GLOBAL: GAMEMD 0xB0FE64
extern unsigned char DAT_00B0FE64;
// FUNCTION: GAMEMD 0x734E60 (decl; reloc)
const wchar_t* FUN_00734E60(const char*, int*, const char*, int);
// LIBRARY: GAMEMD 0x007ca489
// _wcscpy
extern "C" wchar_t* __cdecl wcscpy(wchar_t*, const wchar_t*);


// GLOBAL: GAMEMD 0x00887324
extern Tactical* DAT_00887324;
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, UndeploysInto) == 0x408);

// GLOBAL: GAMEMD 0x00A83D4C
extern HouseClass* DAT_00A83D4C;
// GLOBAL: GAMEMD 0x00A802C8
extern EventQueue<128> DAT_00A802C8;
// GLOBAL: GAMEMD 0x00A8B230
extern unsigned int* DAT_00A8B230;

// GLOBAL: GAMEMD 0x00A8BC60
extern MessageListClass DAT_00A8BC60;
// GLOBAL: GAMEMD 0x00822CF2
extern bool DAT_00822CF2;
// GLOBAL: GAMEMD 0x00A8EC00
extern int DAT_00A8EC00;
// GLOBAL: GAMEMD 0x00A8EC04
extern int DAT_00A8EC04;
// GLOBAL: GAMEMD 0x00A8EC08
extern int DAT_00A8EC08;
// GLOBAL: GAMEMD 0x00A8EC0C
extern int DAT_00A8EC0C;

// FUNCTION: GAMEMD 0x007DDCD6 (decl; reloc)
void __cdecl FUN_007DDCD6(wchar_t* text);

// GLOBAL: GAMEMD 0x0089C3B0
extern BeaconManagerClass DAT_0089C3B0;
// FUNCTION: GAMEMD 0x0063AC60 (decl; reloc)
int FUN_0063AC60();
// FUNCTION: GAMEMD 0x00660BB0 (decl; reloc)
CellStruct* FUN_00660BB0(CellStruct* result);
// FUNCTION: GAMEMD 0x00660BE0 (decl; reloc)
CellStruct* FUN_00660BE0(CellStruct* result);
// GLOBAL: GAMEMD 0x00B0FDF0
extern CellStruct DAT_00B0FDF0;
// GLOBAL: GAMEMD 0x00880990
extern int DAT_00880990;
// GLOBAL: GAMEMD 0x00B0FE10
extern CoordStruct DAT_00B0FE10;
// GLOBAL: GAMEMD 0x008B4108
extern DynamicVectorClass<UnitClass*> DAT_008B4108;
GG_STATIC_ASSERT(offsetof(HouseClass, Buildings) + offsetof(DynamicVectorClassLayout, Items) == 0x6C);
GG_STATIC_ASSERT(offsetof(HouseClass, Buildings) + offsetof(DynamicVectorClassLayout, Count) == 0x78);
GG_STATIC_ASSERT(offsetof(HouseClass, OwnedUnits) == 0x2E8);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, bools_16A4) + 0x15 == 0x16B9);
GG_STATIC_ASSERT(offsetof(TechnoClass, IsPrimaryFactory) == 0x3D3);
GG_STATIC_ASSERT(offsetof(HouseClass, Defeated) == 0x1F5);

// FUNCTION: GAMEMD 0x0063A0D0 (decl; reloc)
void __cdecl FUN_0063A0D0();
GG_STATIC_ASSERT(offsetof(TechnoClass, Berzerk) == 0x298);
GG_STATIC_ASSERT(offsetof(UnitTypeClass, IsSimpleDeployer) == 0xE13);
GG_STATIC_ASSERT(offsetof(UnitTypeClass, Harvester) == 0xE0E);
GG_STATIC_ASSERT(offsetof(TechnoClass, SlaveManager) == 0x2D8);

// GLOBAL: GAMEMD 0x00845560
extern int DAT_00845560;
// GLOBAL: GAMEMD 0x00845564
extern int DAT_00845564;
// GLOBAL: GAMEMD 0x00B0FE54
extern int DAT_00B0FE54;
// GLOBAL: GAMEMD 0x00B0FE70
extern int DAT_00B0FE70;
// GLOBAL: GAMEMD 0x00B0FD70
extern char DAT_00B0FD70[];

// Supplemental declarations for original-TU calls in address order.
void __cdecl FUN_007307B0();
void __cdecl FUN_007307D0();
void __cdecl FUN_00730950();
void __cdecl FUN_00730970();
bool FUN_00730990(int group);
int FUN_00730A10(int group);
void FUN_00730A90(const wchar_t* text, int duration);
int __cdecl FUN_00730AD0();
int __cdecl FUN_00730AE0();
void __cdecl FUN_00730AF0();
void __cdecl FUN_00730D60();
void __cdecl FUN_00730EA0();
void __cdecl FUN_00730F30();
void __cdecl FUN_00730FE0();
void FUN_00731060(int group);
void FUN_007310D0(int group);
bool FUN_00731130(int group);
void FUN_007313A0(int group);
void FUN_007314C0(int group);
void __cdecl FUN_007315A0();
void FUN_00731840(int data);
void __cdecl FUN_007318F0();
void __cdecl FUN_00731A10();
void FUN_00731A30(int a1, int a2);
void FUN_00731A50(bool value);
void FUN_00731A70(bool value);
void __cdecl FUN_00731A90();
bool __cdecl FUN_00731AA0();
void __cdecl FUN_00731AF0();
void __cdecl FUN_00731BE0();
bool __cdecl FUN_00731BF0();
void __cdecl FUN_00731CF0();
void FUN_00731D10(wchar_t* text);
void FUN_00731D90(wchar_t* text, const wchar_t* value);
UICmndsVector* FUN_00731EB0(bool (__fastcall *predicate)(TechnoClass*, void*), void* context);
UICmndsVector* FUN_00731F70(bool (__fastcall *predicate)(TechnoClass*, void*), void* context);
UICmndsVector* __cdecl FUN_00732050();
void FUN_00732110(UICmndsVector* list, void (__fastcall *callback)(TechnoClass*, void*), void* context);
void FUN_00732140(UICmndsVector* list, bool (__fastcall *predicate)(TechnoClass*, void*),
                 void (__fastcall *callback)(TechnoClass*, void*), void* condition, void* context);
bool FUN_00732190(UICmndsVector* list, bool (__fastcall *callback)(TechnoClass*, void*), void* context);
bool FUN_007321D0(UICmndsVector* list, bool (__fastcall *callback)(TechnoClass*, void*), void* context);
int FUN_00732210(DynamicVectorClass<const char*>* list, const char* text);
void FUN_00732280(bool clear);
int FUN_00732580(TechnoClass* object);
int FUN_007325C0(TechnoClass* object);
void FUN_00732600(const char* text);
int FUN_00732770(TechnoClass* object, const char* text);
void FUN_007327D0(const char* text);
void __cdecl FUN_00732950();
bool FUN_00732C30(TechnoClass* object, DynamicVectorClass<const char*>* list);
void __cdecl FUN_00732CA0();
void __cdecl FUN_00732CC0();
DynamicVectorClass<const char*>* __cdecl FUN_00732D10();
void FUN_00732FF0(void (__fastcall *callback)(TechnoClass*, void*), const char* text, void* context);
void FUN_00733160(TechnoClass* object);
void __cdecl FUN_007331B0();
void FUN_00733380(bool clear);
int FUN_007335F0(TechnoClass* object);
const wchar_t* FUN_00733640(int value);
int FUN_007336A0(int value);
void FUN_007336C0(bool clear);
int FUN_00733990(int value);
void FUN_007339B0(bool clear);
int FUN_00733C60(TechnoClass* object, const char* text);
DynamicVectorClass<const char*>* FUN_00733CD0(UICmndsVector* list);
char* FUN_00733E10(UICmndsVector* list, const char* previous, int limit, int* value);
void __cdecl FUN_00734120();
void __cdecl FUN_00734210();
void FUN_00734250(BuildingClass* object);
bool FUN_007342C0(AbstractClass* object);

#endif  // GG_MATCH_CORE_TRIVIAL_TU256_METHODS_H
