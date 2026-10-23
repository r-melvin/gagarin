// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU186_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU186_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"


struct Obj_00646CE0;
struct Obj_00646D00;

// GLOBAL: GAMEMD 0xA8B238
extern int DAT_00A8B238;
// The canonical manager owns the instance at0xA8E9C0.
#include "../network/transport/connman_class.h"

// LIBRARY: GAMEMD 0x7C8B3D (decl; reloc)
// FUN_007C8B3D
extern "C" void __cdecl FUN_007C8B3D(void*);


// Log records written by650A90 and read by6516F0, offsets verified in
// ev_b0d56ac44dfec9c9587a602e6fd8b3b9de859a7e489dd2404884aeeb4508d4d1.
struct QueuePlayerLog_00650A90
{
    char unknown_00[20];
    signed char unknown_14;
    char unknown_15[32];
    char unknown_35[3];
    int unknown_38;
    char unknown_3C[32];
};
struct QueueTechnoLog_00650A90
{
    int unknown_00;
    int unknown_04;
    char unknown_08[24];
    signed char unknown_20;
    char unknown_21[3];
    unsigned unknown_24;
    char unknown_28[24];
    unsigned unknown_40;
    char unknown_44[24];
    int unknown_5C;
    short unknown_60;
    short unknown_62;
    unsigned char unknown_64, unknown_65, unknown_66;
    signed char unknown_67; // MOVSX byte651B0E
};
struct QueueObjectLog_00650A90
{
    int unknown_00;
    int unknown_04;
    char unknown_08[24];
    signed char unknown_20;
    char unknown_21[3];
    short unknown_24;
    char unknown_26[2];
};
GG_STATIC_ASSERT(offsetof(QueuePlayerLog_00650A90, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(QueuePlayerLog_00650A90, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(QueuePlayerLog_00650A90, unknown_15) == 0x15);
GG_STATIC_ASSERT(offsetof(QueuePlayerLog_00650A90, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(QueuePlayerLog_00650A90, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(sizeof(QueuePlayerLog_00650A90) == 0x5C);
GG_STATIC_ASSERT(offsetof(QueueTechnoLog_00650A90, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(QueueTechnoLog_00650A90, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(QueueTechnoLog_00650A90, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(QueueTechnoLog_00650A90, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(QueueTechnoLog_00650A90, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(QueueTechnoLog_00650A90, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(QueueTechnoLog_00650A90, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(QueueTechnoLog_00650A90, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(QueueTechnoLog_00650A90, unknown_5C) == 0x5C);
GG_STATIC_ASSERT(offsetof(QueueTechnoLog_00650A90, unknown_60) == 0x60);
GG_STATIC_ASSERT(offsetof(QueueTechnoLog_00650A90, unknown_62) == 0x62);
GG_STATIC_ASSERT(offsetof(QueueTechnoLog_00650A90, unknown_64) == 0x64);
GG_STATIC_ASSERT(offsetof(QueueTechnoLog_00650A90, unknown_65) == 0x65);
GG_STATIC_ASSERT(offsetof(QueueTechnoLog_00650A90, unknown_66) == 0x66);
GG_STATIC_ASSERT(offsetof(QueueTechnoLog_00650A90, unknown_67) == 0x67);
GG_STATIC_ASSERT(sizeof(QueueTechnoLog_00650A90) == 0x68);
GG_STATIC_ASSERT(offsetof(QueueObjectLog_00650A90, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(QueueObjectLog_00650A90, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(QueueObjectLog_00650A90, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(QueueObjectLog_00650A90, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(QueueObjectLog_00650A90, unknown_24) == 0x24);
GG_STATIC_ASSERT(sizeof(QueueObjectLog_00650A90) == 0x28);

// Constructor0x646C90 and reverse-array cleanup0x646E60 prove stride0x33C.
struct Obj_00646CE0
{
    unsigned unknown_00;
    int unknown_04;
    int unknown_08;
    QueuePlayerLog_00650A90 unknown_0C[8];
    int unknown_2EC;
    int unknown_2F0[4];
    QueueTechnoLog_00650A90* unknown_300;
    int unknown_304[5];
    QueueObjectLog_00650A90* unknown_318[5];
    int unknown_32C;
    QueueObjectLog_00650A90* unknown_330;
    void* unknown_334;
    unsigned unknown_338;
    // FUNCTION: GAMEMD 0x646C90 (decl; reloc)
    // Obj_00646CE0::Obj_00646CE0
    Obj_00646CE0();
    // FUNCTION: GAMEMD 0x646CE0 (decl; reloc)
    // Obj_00646CE0::~Obj_00646CE0
    ~Obj_00646CE0();
};
GG_STATIC_ASSERT(offsetof(Obj_00646CE0, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_00646CE0, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_00646CE0, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_00646CE0, unknown_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(Obj_00646CE0, unknown_2F0) == 0x2F0);
GG_STATIC_ASSERT(offsetof(Obj_00646CE0, unknown_2EC) == 0x2EC);
GG_STATIC_ASSERT(offsetof(Obj_00646CE0, unknown_300) == 0x300);
GG_STATIC_ASSERT(offsetof(Obj_00646CE0, unknown_304) == 0x304);
GG_STATIC_ASSERT(offsetof(Obj_00646CE0, unknown_318) == 0x318);
GG_STATIC_ASSERT(offsetof(Obj_00646CE0, unknown_32C) == 0x32C);
GG_STATIC_ASSERT(offsetof(Obj_00646CE0, unknown_330) == 0x330);
GG_STATIC_ASSERT(offsetof(Obj_00646CE0, unknown_334) == 0x334);
GG_STATIC_ASSERT(offsetof(Obj_00646CE0, unknown_338) == 0x338);
GG_STATIC_ASSERT(sizeof(Obj_00646CE0) == 0x33C);

struct Obj_00646D00
{
    int unknown_00;   // +0x0000
    unsigned int unknown_04;   // +0x0004
    unsigned int unknown_08;   // +0x0008
    int unknown_0C;   // +0x000C
    int unknown_10;   // +0x0010
    int unknown_14;   // +0x0014
    // FUNCTION: GAMEMD 0x646D00 (decl; reloc)
// Obj_00646D00::Obj_00646D00
    Obj_00646D00();
};
GG_STATIC_ASSERT(offsetof(Obj_00646D00, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_00646D00, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_00646D00, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_00646D00, unknown_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(Obj_00646D00, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(Obj_00646D00, unknown_14) == 0x14);



// FUNCTION: GAMEMD 0x646D50 (decl; reloc)
// FUN_00646D50
void __cdecl FUN_00646D50();
// FUNCTION: GAMEMD 0x646DB0 (decl; reloc)
// FUN_00646DB0
void __cdecl FUN_00646DB0();
// FUNCTION: GAMEMD 0x652100 (decl; reloc)
// FUN_00652100
void __cdecl FUN_00652100();

// GLOBAL: GAMEMD 0xAFA278
extern Obj_00646D00 DAT_00AFA278[7];
// GLOBAL: GAMEMD 0xAFA358
extern Obj_00646D00 DAT_00AFA358[7];
// GLOBAL: GAMEMD 0xAC6660
extern Obj_00646CE0 DAT_00AC6660[256];
GG_STATIC_ASSERT(sizeof(Obj_00646D00) == 0x18);

// LIBRARY: GAMEMD 0x7C978A (decl; reloc)
// FUN_007C978A
int __cdecl FUN_007C978A(void (__cdecl* callback)());
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

#endif  // GG_MATCH_CORE_TRIVIAL_TU186_METHODS_H
