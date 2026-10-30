// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | private-ref-cross-check | behaviour-confirmed-name
//   Original translation unit Techno.CPP. The name is the source-file string at 0x843178
//   in retail gamemd.exe v1.001, passed by the assert at 0x70aad3 inside this object's
//   code range (0x6f28a0-0x7108df). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   Original translation unit Techno.CPP. The name is the source-file string at 0x843178
//   in retail gamemd.exe v1.001, passed by the assert at 0x70aad3 inside this object's
//   code range (0x6f28a0-0x7108df). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   Original translation unit Techno.CPP. The name is the source-file string at 0x843178
//   in retail gamemd.exe v1.001, passed by the assert at 0x70aad3 inside this object's
//   code range (0x6f28a0-0x7108df). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Retail 0x6FBFA0 and 0x6FC030, read instruction by instruction from gamemd.exe v1.001: two
// object-state gates next to each other. The object and its owner are placeholder views whose
// offsets are asserted below.
//   0x6FBFA0 0x6FC030
//
//   Original translation unit Techno.CPP. The name is the source-file string at 0x843178
//   in retail gamemd.exe v1.001, passed by the assert at 0x70aad3 inside this object's
//   code range (0x6f28a0-0x7108df). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   Original translation unit Techno.CPP. The name is the source-file string at 0x843178
//   in retail gamemd.exe v1.001, passed by the assert at 0x70aad3 inside this object's
//   code range (0x6f28a0-0x7108df). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   Original translation unit Techno.CPP. The name is the source-file string at 0x843178
//   in retail gamemd.exe v1.001, passed by the assert at 0x70aad3 inside this object's
//   code range (0x6f28a0-0x7108df). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   Original translation unit Techno.CPP. The name is the source-file string at 0x843178
//   in retail gamemd.exe v1.001, passed by the assert at 0x70aad3 inside this object's
//   code range (0x6f28a0-0x7108df). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   Original translation unit Techno.CPP. The name is the source-file string at 0x843178
//   in retail gamemd.exe v1.001, passed by the assert at 0x70aad3 inside this object's
//   code range (0x6f28a0-0x7108df). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   Original translation unit Techno.CPP. The name is the source-file string at 0x843178
//   in retail gamemd.exe v1.001, passed by the assert at 0x70aad3 inside this object's
//   code range (0x6f28a0-0x7108df). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   Original translation unit Techno.CPP. The name is the source-file string at 0x843178
//   in retail gamemd.exe v1.001, passed by the assert at 0x70aad3 inside this object's
//   code range (0x6f28a0-0x7108df). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Retail 0x6F6F40, read instruction by instruction from gamemd.exe v1.001: converts a record's
// value at +8 into tens of rules units.
//
//   Original translation unit Techno.CPP. The name is the source-file string at 0x843178
//   in retail gamemd.exe v1.001, passed by the assert at 0x70aad3 inside this object's
//   code range (0x6f28a0-0x7108df). Functions are in ascending retail address order.
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
//
// The nine tail-jump thunks, ordered ascending by retail address.
//
//   Names cross-checked against YRpp (RecoilData::Fire,
//   JMP_THIS(0x70ECE0)) — each offset reconfirmed
//   against the user's binary.
//
// Disassembly skeleton (0x70ECE0..0x70ED0B, len 0x2C):
//   PUSH ECX                ; reserve 4-byte stack slot for the cached Travel
//   MOV  EAX,[ECX]          ; travel = Turret.Travel
//   TEST EAX,EAX
//   MOV  [ESP],EAX          ; spill travel
//   JZ   end
//   MOV  EAX,[ECX+4]        ; CompressFrames
//   MOV  EDX,1
//   CMP  EAX,EDX
//   MOV  [ECX+0x18],EDX     ; State = 1
//   MOV  [ECX+0x1c],EAX     ; TravelFramesLeft = CompressFrames
//   JGE  skip               ; (CompressFrames >= 1)
//   MOV  [ECX+0x1c],EDX     ; TravelFramesLeft = 1
//  skip:
//   FILD  [ESP]             ; (float)travel
//   FIDIV [ECX+0x1c]        ;  / TravelFramesLeft  (integer divisor)
//   FSTP  [ECX+0x10]        ; TravelPerFrame = ...
//  end:
//   POP  ECX
//   RET
//
//   len 0x20, 0x7010D0 len 0x45, 0x701120 len 0x1A, 0x70C5A0 len 0xC,
//   0x70EFD0 len 0xE, 0x70F090 len 0x12, 0x70F850 len 0x33).
//
// Seven adjacent TechnoClass virtual-slot bases. They share a receiver and a
// shape: read one member or one slot, and report a decision.
//
//   Every displacement, constant, table bound and callee below was read off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. None of the owning classes is bound by RTTI or
//   a binary string here, so all keep placeholder names. The imports are named
//   by the PE import table (CloseHandle 0x7E11E0; ImmAssociateContext through
//   its thunk at 0x7C8A1C).
//
// Small leaves (64 bytes or less) between 0x6B0000 and 0x7B0000 that other
// translation units already declared as callees but nothing defined.
//
//   LIBRARY: GAMEMD 0x7C5F00  __ftol (CRT double->long; the (int) casts; reloc)
//
//   the YRpp method map).
//
//   Offsets, vtable slots and callees read off the user's retail gamemd.exe
//   v1.001 (Ghidra disasm) at the addresses annotated below. Methods live on
//   the canonical TechnoClass (match/_layout/techno_class.h).
//   LIBRARY: GAMEMD 0x7C5F00  __ftol (CRT double->long; reloc)
//
// Address index:
//   0x7013E0  TechnoClass::FUN_007013E0
//   0x70BE50  TechnoClass::FUN_0070BE50
//   0x70D7A0  TechnoClass::FUN_0070D7A0
//   0x70DD20  TechnoClass::FUN_0070DD20
//   0x710590  TechnoClass::FUN_00710590
//
//   TechnoClass members read off retail gamemd.exe v1.001 (Techno.CPP, code range
//   0x6f28a0-0x7108df), round 16. The overrides that the canonical TechnoClass already declares
//   are defined on it; the rest sit on TechnoView_r16, a plain derived view, so no shared header
//   changes. Functions are in ascending retail address order.
//   Address index: 0x707DD0, 0x70DC70.
//
//   Offsets, vtable slots and callees read off the user's retail gamemd.exe
//   v1.001 (Ghidra disasm) at the addresses annotated below. Methods live on
//   the canonical TechnoClass (match/_layout/techno_class.h).
//
// Address index:
//   0x707750  TechnoClass::FUN_00707750
//   0x707D20  TechnoClass::FUN_00707D20
//
//   Disassembly of 0x6F3330 in retail gamemd.exe v1.001 (Techno.CPP range): picks the weapon
//   slot a techno uses against a target, from the two weapons' warheads and projectiles, the
//   target's kind (building, cell or other) and the owner's state. Result is a weapon index.
//
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. TechnoClass timer starters.
//   The countdown is built as a temporary and copied over the member, which carries the temporary's
//   never-written middle word across (see CDTimerClass in frame_timer.h).
//
// Address index: 0x70E2B0 0x70E300 0x70F770
//
//   Two TechnoClass virtuals that forward to the object's type, read off retail
//   gamemd.exe v1.001. Functions are in ascending retail address order.
//
//   0x70E280-0x70E2A4, len 0x25). Names cross-checked against YRpp.
//
//   0x7099E0 len 0x35, 0x709A30 len 0x3, 0x709A40 len 0x42).
//
//   GLOBAL:   GAMEMD 0xA8ED84  Unsorted::CurrentFrame
//
//   cross-checked against YRpp.
//
//   len 0x49, 0x6F4A70 len 0x33).
//
//   cross-checked against YRpp. Each function is
//
// reccmp annotations:
//
//   cross-checked against YRpp (each
//   offset reconfirmed against the binary in techno_class_setters.h).
//
//   0x708DC0 len 0x3D, 0x709020 len 0x3D, 0x709060 len 0x3D).
//
// Three near-identical voice-response virtuals. Each asks its own type for a
// voice index; if the type declares one it is queued, otherwise the object
// falls back to a different voice virtual. All three return void — the exit is
// a bare `RET` with nothing written to EAX or AL.
//
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Small leaf bodies from
//   the 0x6E0000-0x724000 range; the receivers are placeholder views of the members touched.
//
// Address index: 0x6EC220 0x70C250 0x71DD80 0x720440 0x7211E0 0x721290
//                0x723CA0 0x723CE0
//
//   the YRpp method map).
//
//   Disassembly of 0x700600 in retail gamemd.exe v1.001 (Techno.CPP range), vtable slot 28:
//   which cursor action this object offers over a map cell (attack, enter, harvest-style
//   action, move), from the modifier keys held, ownership, the weapon it would pick and the
//   cell's overlay, fogged objects and veinhole monster.
//
// Address index:
//   0x700600  TechnoClass::vf_28
//
//   Disassembly of 0x6FB740 in retail gamemd.exe v1.001 (Techno.CPP range): the per-frame cloak state
//   machine. It steps the cloak stage timer and moves the object between uncloaked, cloaking, cloaked
//   and uncloaking according to its state, rank, health and surroundings.
//
//   Disassembly of 0x6F6F60 and 0x6F70E0 in retail gamemd.exe v1.001 (Techno.CPP range): both turn
//   the height difference between the cells under two objects into a range bonus using the
//   ElevationIncrement fields of the rules object at 0x8871E0.
//
//   address below). Lies inside the Techno.CPP code range 0x6F28A0-0x7108DF.
//
//   Every displacement and callee below was read off the user's retail gamemd.exe v1.001 with the local
//   Ghidra CLI at the address in the annotation. The receivers are placeholder views whose offsets are
//   asserted below.
//
//   address below). Lies inside the Techno.CPP code range 0x6F28A0-0x7108DF.
//
//   0x70F6E0-0x70F72E, len 0x4F). Names cross-checked against YRpp.
//
//   0x70E1A0-0x70E1D7 len 0x38, 0x710550-0x710583 len 0x34). Names
//   cross-checked against YRpp.
//
// Both bodies are virtual-dispatch heavy (slots +0x84, +0x3C8, +0x3F8). The
// dispatches are written as ordinary member-pointer calls through a modelled
// vtable struct, which is what emits retail's `MOV reg,[this]; CALL [reg+slot]`
// pair; the two direct calls carry their receiver in ECX and so are declared as
// members of their own classes.

#include <stddef.h>
#include <windows.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/cell.h"

struct TypeView_006FBFA0 {
    unsigned char unknown_00[0x1A6];
    bool unknown_1A6;   // +0x01A6
};
GG_STATIC_ASSERT(offsetof(TypeView_006FBFA0, unknown_1A6) == 0x1A6);

struct OwnerView_006FBFA0 {
    unsigned char unknown_00[0x34];
    TypeView_006FBFA0* unknown_34;   // +0x0034
    // FUNCTION: GAMEMD 0x50B6F0 (decl; reloc)
    bool FUN_0050B6F0();
};
GG_STATIC_ASSERT(offsetof(OwnerView_006FBFA0, unknown_34) == 0x34);

struct TagView_006FBFA0 {
    // FUNCTION: GAMEMD 0x6E53A0 (decl; reloc)
    void FUN_006E53A0(int a1, void* a2, CellStruct a3, int a4, int a5);
};

struct ObjectView_006FBFA0 {
    virtual void vf_000();
    virtual void vf_001();
    virtual void vf_002();
    virtual void vf_003();
    virtual void vf_004();
    virtual void vf_005();
    virtual void vf_006();
    virtual void vf_007();
    virtual void vf_008();
    virtual void vf_009();
    virtual void vf_010();
    virtual void vf_011();
    virtual void vf_012();
    virtual void vf_013();
    virtual void vf_014();
    virtual void vf_015();
    virtual void vf_016();
    virtual void vf_017();
    virtual void vf_018();
    virtual void vf_019();
    virtual void vf_020();
    virtual void vf_021();
    virtual void vf_022();
    virtual void vf_023();
    virtual void vf_024();
    virtual void vf_025();
    virtual void vf_026();
    virtual void vf_027();
    virtual void vf_028();
    virtual void vf_029();
    virtual void vf_030();
    virtual void vf_031();
    virtual void vf_032();
    virtual void vf_033();
    virtual void vf_034();
    virtual void vf_035();
    virtual void vf_036();
    virtual void vf_037();
    virtual void vf_038();
    virtual void vf_039();
    virtual void vf_040();
    virtual void vf_041();
    virtual void vf_042();
    virtual void vf_043();
    virtual void vf_044();
    virtual void vf_045();
    virtual void vf_046();
    virtual void vf_047();
    virtual void vf_048();
    virtual void vf_049();
    virtual void vf_050();
    virtual void vf_051();
    virtual void vf_052();
    virtual void vf_053();
    virtual void vf_054();
    virtual void vf_055();
    virtual void vf_056();
    virtual void vf_057();
    virtual void vf_058();
    virtual void vf_059();
    virtual void vf_060();
    virtual void vf_061();
    virtual void vf_062();
    virtual void vf_063();
    virtual void vf_064();
    virtual void vf_065();
    virtual void vf_066();
    virtual void vf_067();
    virtual void vf_068();
    virtual void vf_069();
    virtual void vf_070();
    virtual void vf_071();
    virtual void vf_072();
    virtual void vf_073();
    virtual void vf_074();
    virtual void vf_075();
    virtual void vf_076();
    virtual void vf_077();
    virtual void vf_078();
    virtual void vf_079();
    virtual void vf_080();
    virtual void vf_081();
    virtual void vf_082();
    virtual void vf_083();
    virtual void vf_084();
    virtual void vf_085();
    virtual void vf_086();
    virtual void vf_087();
    virtual void vf_088();
    virtual void vf_089();
    virtual void vf_090();
    virtual void vf_091();
    virtual void vf_092();
    virtual void vf_093();
    virtual void vf_094();
    virtual void vf_095();
    virtual void vf_096();
    virtual void vf_097();
    virtual void vf_098();
    virtual void vf_099();
    virtual void vf_100();
    virtual void vf_101();
    virtual void vf_102();
    virtual void vf_103();
    virtual void vf_104();
    virtual void vf_105();
    virtual void vf_106();
    virtual void vf_107();
    virtual void vf_108();
    virtual void vf_109();
    virtual void vf_110();
    virtual void* vf_111();
    virtual void vf_112();
    virtual void vf_113();
    virtual void vf_114();
    virtual void vf_115();
    virtual void vf_116();
    virtual void vf_117();
    virtual void vf_118();
    virtual void vf_119();
    virtual void vf_120();
    virtual void vf_121();
    virtual void vf_122();
    virtual void vf_123();
    virtual void vf_124();
    virtual void vf_125();
    virtual void vf_126();
    virtual void vf_127();
    virtual void vf_128();
    virtual void vf_129();
    virtual void vf_130();
    virtual void vf_131();
    virtual void vf_132();
    virtual void vf_133();
    virtual void vf_134();
    virtual void vf_135();
    virtual void vf_136();
    virtual void vf_137();
    virtual void vf_138();
    virtual void vf_139();
    virtual void vf_140();
    virtual void vf_141();
    virtual void vf_142();
    virtual void vf_143();
    virtual void vf_144();
    virtual void vf_145();
    virtual void vf_146();
    virtual void vf_147();
    virtual void vf_148();
    virtual void vf_149();
    virtual void vf_150();
    virtual void vf_151();
    virtual void vf_152();
    virtual void vf_153();
    virtual void vf_154();
    virtual void vf_155();
    virtual void vf_156();
    virtual void vf_157();
    virtual void vf_158();
    virtual void vf_159();
    virtual void vf_160();
    virtual void vf_161();
    virtual void vf_162();
    virtual void vf_163();
    virtual void vf_164();
    virtual void vf_165();
    virtual void vf_166();
    virtual void vf_167();
    virtual void vf_168();
    virtual void vf_169();
    virtual void vf_170();
    virtual void vf_171();
    virtual void vf_172();
    virtual void vf_173();
    virtual void vf_174();
    virtual void vf_175();
    virtual void vf_176();
    virtual void vf_177();
    virtual void vf_178();
    virtual void vf_179();
    virtual void vf_180();
    virtual void vf_181();
    virtual void vf_182();
    virtual void vf_183();
    virtual void vf_184();
    virtual void vf_185();
    virtual void vf_186();
    virtual void vf_187();
    virtual void vf_188();
    virtual void vf_189();
    virtual void vf_190();
    virtual void vf_191();
    virtual void vf_192();
    virtual void vf_193();
    virtual void vf_194();
    virtual void vf_195();
    virtual void vf_196();
    virtual void vf_197();
    virtual void vf_198();
    virtual void vf_199();
    virtual void vf_200();
    virtual void vf_201();
    virtual void vf_202();
    virtual void vf_203();
    virtual void vf_204();
    virtual void vf_205();
    virtual void vf_206();
    virtual void vf_207();
    virtual void vf_208();
    virtual void vf_209();
    virtual void vf_210();
    virtual void vf_211();
    virtual void vf_212();
    virtual void vf_213();
    virtual void vf_214();
    virtual void vf_215();
    virtual void vf_216();
    unsigned char unknown_04[0x30];
    TagView_006FBFA0* unknown_34;   // +0x0034
    unsigned char unknown_38[0x190];
    unsigned char unknown_1C8;   // +0x01C8
    unsigned char unknown_1C9[0x53];
    OwnerView_006FBFA0* unknown_21C;   // +0x021C
    unsigned char unknown_220[0xBC];
    int unknown_2DC;   // +0x02DC
    unsigned char unknown_2E0[4];
    int unknown_2E4;   // +0x02E4
    unsigned char unknown_2E8[0x130];
    bool unknown_418;   // +0x0418
    unsigned char unknown_419[2];
    bool unknown_41B;   // +0x041B

    // FUNCTION: GAMEMD 0x5F4520 (decl; reloc)
    bool FUN_005F4520();
    // FUNCTION: GAMEMD 0x5F6C70 (decl; reloc)
    bool FUN_005F6C70();
    // FUNCTION: GAMEMD 0x637840 (decl; reloc)
    void FUN_00637840();
    // FUNCTION: GAMEMD 0x6FBFA0
    bool FUN_006FBFA0();
    // FUNCTION: GAMEMD 0x6FC030
    bool FUN_006FC030();
};
GG_STATIC_ASSERT(offsetof(ObjectView_006FBFA0, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(ObjectView_006FBFA0, unknown_1C8) == 0x1C8);
GG_STATIC_ASSERT(offsetof(ObjectView_006FBFA0, unknown_21C) == 0x21C);
GG_STATIC_ASSERT(offsetof(ObjectView_006FBFA0, unknown_2DC) == 0x2DC);
GG_STATIC_ASSERT(offsetof(ObjectView_006FBFA0, unknown_2E4) == 0x2E4);
GG_STATIC_ASSERT(offsetof(ObjectView_006FBFA0, unknown_418) == 0x418);
GG_STATIC_ASSERT(offsetof(ObjectView_006FBFA0, unknown_41B) == 0x41B);

// GLOBAL: GAMEMD 0xB73550
extern "C" HWND DAT_00B73550;
// GLOBAL: GAMEMD 0xB0EA50
extern CellStruct DAT_00B0EA50;
// GLOBAL: GAMEMD 0x822CF2
extern bool DAT_00822CF2;

// FUNCTION: GAMEMD 0x47C520 (decl; reloc)
void* __fastcall FUN_0047C520(void* arg);

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB0EA50
CellStruct DAT_00B0EA50;
// GLOBAL: GAMEMD 0x822CF2
bool DAT_00822CF2 = true;
// END defined globals

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Record_006F6F40 {
    unsigned char unknown_00[8];
    int unknown_08;   // +0x0008
};
GG_STATIC_ASSERT(offsetof(Record_006F6F40, unknown_08) == 0x8);


// GLOBAL: GAMEMD 0x8871E0
#include "../_layout/rules_class.h"
extern RulesClass* DAT_008871E0;

#include "techno_class_combat_damage_methods.h"

#include "techno_class_gattling_rate_methods.h"

#include "techno_class_nearby_location_methods.h"

#include "techno_class_passive_acquire_methods.h"

#include "techno_class_reloading_methods.h"
#include "../_layout/spawn_manager_class.h"

#include "../core/abstract_class_untargetable_methods.h"
#include "../network/event_class_ctors.h"
#include "../network/event_queue.h"

#include <string.h>

// LIBRARY: GAMEMD 0x7C8B3D -- CRT free.
extern "C" void __cdecl gg_free(void*);

extern int DAT_00A9FABC;
extern void* DAT_00ABF3F4;
extern int DAT_00B2FF78[0x4000];
extern int DAT_00B1D5E0[0x4000];
extern void* DAT_00B77F54;
extern void* DAT_00B77F60;

#include "../core/member_setter_family_methods.h"

#include "../core/pair_vector_grow_sweep.h"

#include "../core/tail_jmp_thunk_sweep.h"



#include "../core/trivial_tu237_methods.h"

#include <windows.h>
#include <imm.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);

// ---------------------------------------------------------------------------

#include "../_layout/quad_006c95e0.h"

// GLOBAL: GAMEMD 0x00B0CB78
extern "C" int DAT_00B0CB78[];

#include "../_layout/rect_006cfdb0.h"

// GLOBAL: GAMEMD 0x00B0FC60
extern "C" Rect_006CFDB0* DAT_00B0FC60;
// GLOBAL: GAMEMD 0x00B0FC68
extern "C" Rect_006CFDB0* DAT_00B0FC68;
// GLOBAL: GAMEMD 0x00B0FC6C
extern "C" Rect_006CFDB0* DAT_00B0FC6C;
// GLOBAL: GAMEMD 0x00B0CB54
extern "C" int DAT_00B0CB54;
// GLOBAL: GAMEMD 0x00B0CC2C
extern "C" int DAT_00B0CC2C;

#include "../_layout/link_006ef5f0.h"

#include "../_layout/obj_006ef5f0.h"

#include "../_layout/obj_00705d20.h"

// GLOBAL: GAMEMD 0x00843108
extern "C" char DAT_00843108;

#include "../_layout/obj_00711eb0.h"

#include "../_layout/obj_00717880.h"

#include "../_layout/obj_00726910.h"

// GLOBAL: GAMEMD 0x00B0FE54
extern "C" int DAT_00B0FE54;
// GLOBAL: GAMEMD 0x00B0FE58
extern "C" char DAT_00B0FE58;

// GLOBAL: GAMEMD 0x008463B8 (eighteen string pointers)
extern "C" const char* const DAT_008463B8[18];

#include "../_layout/item_00751040.h"

#include "../_layout/holder_00751040.h"

#include "../_layout/node_00751040.h"

#include "../_layout/list_00751040.h"

// GLOBAL: GAMEMD 0x00B1D320
extern "C" List_00751040 DAT_00B1D320;

#include "../_layout/named_00751590.h"

#include "../_layout/entry_00751590.h"

// GLOBAL: GAMEMD 0x00B1D37C
extern "C" Entry_00751590** DAT_00B1D37C;
// GLOBAL: GAMEMD 0x00B1D388
extern "C" int DAT_00B1D388;
// GLOBAL: GAMEMD 0x00846574
extern "C" const char DAT_00846574[];
// GLOBAL: GAMEMD 0x00817474
extern "C" const char DAT_00817474[];

#include "../_layout/obj_00753510.h"

// GLOBAL: GAMEMD 0x00B1D4D8
extern "C" Obj_00753510* DAT_00B1D4D8;
// GLOBAL: GAMEMD 0x00B1D4CC
extern "C" Obj_00753510* DAT_00B1D4CC;
// GLOBAL: GAMEMD 0x00B1D428
extern "C" int DAT_00B1D428;

struct Record_007559B0
{
    int unknown_0[12];
};

// GLOBAL: GAMEMD 0x00B45188 (48-byte records)
extern "C" Record_007559B0 DAT_00B45188[];

// GLOBAL: GAMEMD 0x007E5210 (eleven string pointers)
extern "C" const char* const DAT_007E5210[11];

// GLOBAL: GAMEMD 0x008497A4
extern "C" const char DAT_008497A4[];

// 0x4068E0: cdecl text sink taking a format string (callee only).
extern "C" int __cdecl FUN_004068E0(const char* format, ...);

#include "../_layout/obj_00774950.h"

// GLOBAL: GAMEMD 0x00B73550
extern "C" HWND DAT_00B73550;
// GLOBAL: GAMEMD 0x00B7355C
extern "C" HIMC DAT_00B7355C;

// GLOBAL: GAMEMD 0x00B76B24
extern "C" int DAT_00B76B24;
#include "../_layout/flags_0077d940.h"

// GLOBAL: GAMEMD 0x00B76B30
extern "C" Flags_0077D940 DAT_00B76B30;

#include "../movement/locomotion_begin_drain_methods.h"

#include "../movement/locomotion_com_helpers.h"

#include "../movement/locomotion_forget_pointer_methods.h"

#include "../movement/locomotion_link_query_methods.h"

#include "../movement/locomotion_velocity_methods.h"

#include "../movement/techno_class_release_locomotor_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F4880
extern const double DAT_007F4880;
// GLOBAL: GAMEMD 0xB0EA58
extern double DAT_00B0EA58;
// GLOBAL: GAMEMD 0xB0EB10
extern double DAT_00B0EB10;
// GLOBAL: GAMEMD 0xB0EB18
extern int DAT_00B0EB18;
// GLOBAL: GAMEMD 0xB0EB1C
extern int DAT_00B0EB1C;
// GLOBAL: GAMEMD 0xB0EB20
extern int DAT_00B0EB20;
// GLOBAL: GAMEMD 0xB0EB28
extern double DAT_00B0EB28;


// ---- from the former Techno.cpp ----
//   CLI (disasm from each entry point). Original TU: Techno.CPP, attested by the
//   __FILE__ assert string at 0x843178 (pushed at 0x70AAD3, 0x70ABFD, 0x70AC33);
//   the TU spans 0x6F28A0-0x7108DF. Class layout and vtable slots come from the committed
//   spine match/_layout/techno_class.h. Slot numbers are RTTI-derived
//   (TechnoClass vtable 0x7F4960); the vf_N names are placeholders.

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "weapon_type_class.h"
#include "../core/frame_counter.h"
#include "../_layout/cell_class.h"
#include "../_layout/house_class.h"

// Declaration: GAMEMD 0x00637AA0
char FUN_00637AA0();
// Declaration: GAMEMD 0x00639FD0; bound through this packet's scoped symbol map.
void __fastcall FUN_00639FD0(char* event);
// WinMM import: GAMEMD 0x007E1530 (timeGetTime).
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
// GLOBAL: GAMEMD 0x00A802C8
extern EventQueue<128> DAT_00A802C8;

// Offsets this TU relies on, each read from an instruction in the matched bodies.
GG_STATIC_ASSERT(offsetof(TechnoClass, CurrentTurretNumber)       == 0x124);  // 0x70DD00
GG_STATIC_ASSERT(offsetof(TechnoClass, unknown_int_128)           == 0x128);  // 0x70DD00
GG_STATIC_ASSERT(offsetof(TechnoClass, GattlingValue)             == 0x144);  // 0x70DE40
GG_STATIC_ASSERT(offsetof(TechnoClass, AirstrikeTimer)            == 0x1A8);  // 0x70E340
GG_STATIC_ASSERT(offsetof(TechnoClass, LastTarget)                == 0x2B8);  // 0x7013A0
GG_STATIC_ASSERT(offsetof(TechnoClass, IsOwnedByCurrentPlayer)    == 0x41A);  // 0x7018C0
GG_STATIC_ASSERT(offsetof(TechnoClass, DiscoveredByCurrentPlayer) == 0x41B);  // 0x6F4A40
GG_STATIC_ASSERT(offsetof(TechnoClass, IsRadarTracked)            == 0x423);  // 0x70CC90
GG_STATIC_ASSERT(offsetof(TechnoClass, QueuedVoiceIndex)          == 0x4F0);  // 0x708D90
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Drainable)             == 0x5EF);  // 0x70FED0
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Speed)                 == 0x678);  // 0x70EFE0
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, SprayAttack)           == 0x691);  // 0x70DD70
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, HasTurretTooltips)     == 0x806);  // 0x70DC50
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, WeaponCount)           == 0x80C);  // 0x70E1E0

// The map singleton (GAMEMD 0x87F7E8). Only the cell lookup is reached here; it
// reads the X and Y words of the coordinate it is handed.
class MapView_565730_2
{
public:
    // FUNCTION: GAMEMD 0x565730 (decl; reloc) -- the cell under a coordinate.
    CellClass* GetTargetCell(const CoordStruct& where);
    // FUNCTION: GAMEMD 0x655560 (decl; reloc) -- takes the unit and its RadarPosition.
    void FUN_00655560(TechnoClass* unit, Point2D position);
    // FUNCTION: GAMEMD 0x655740 (decl; reloc) -- takes the unit and its RadarPosition.
    void FUN_00655740(TechnoClass* unit, Point2D position);
};

// GLOBAL: GAMEMD 0x87F7E8
extern MapView_565730_2 MapClass_Instance;
// GLOBAL: GAMEMD 0xB0EA80 -- a frame timer restarted by 0x70D150.
extern CDTimerClass DAT_00B0EA80;
// GLOBAL: GAMEMD 0x822CF2
extern bool DAT_00822CF2;
// GLOBAL: GAMEMD 0xA83D4C -- the local player's house.
extern HouseClass* CurrentPlayer;

static inline CellStruct CoordToCell(const CoordStruct& coord)
{
    CellStruct cell;
    cell.X = (short)(coord.X / 256);
    cell.Y = (short)(coord.Y / 256);
    return cell;
}


// TechnoClass bodies for primary-table (0x7F4960) slots 25, 186, 180 and 102
// (0x6F32D0..0x6F4A3E). Slot numbers come from the RTTI-located table; names
// are placeholders (techno_class.h).

// Translation unit: BuildingClass::IsBeingDrained.

//   member offsets derived directly from the disassembly.


#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/house_class.h"
#include "../_layout/tag_class.h"

// GLOBAL: GAMEMD 0xA83D4C
extern HouseClass* CurrentPlayer;
// GLOBAL: GAMEMD 0xA8E7AC
extern int DAT_00A8E7AC;
// GLOBAL: GAMEMD 0xB0EA50
extern CellStruct DAT_00B0EA50;

#include "../core/techno_class_kill_passengers_methods.h"

// The null-safe FootClass cast retail inlined at the loop's back edge: null
// stays null, anything without the AbstractClass foot bit (+0x14, mask 4)
// becomes null, so the walk stops at the first non-foot link. Written as a
// ternary the `object != 0` test lands as `CMP EAX,ECX; JZ ret` and the flag
// test as `TEST byte ptr [EAX+0x14],DL` (0x7104E0..0x7104E7).
static __inline FootClass* foot_cast_007104C0(void* object)
{
    return (object != 0 && ((AbstractClass*)object)->Flags.IsFoot)
               ? (FootClass*)object
               : 0;
}

#include "techno_class_ability_methods.h"

#include "techno_class_deactivate_methods.h"

#include "techno_class_reactivate_methods.h"

#include "techno_class_update_methods.h"

#include "../economy/building_class_drain.h"

#include "../_layout/foot_class.h"
#include "../_layout/infantry_class.h"
#include "../_layout/bomb_list_class.h"

#ifndef NULL
#define NULL 0
#endif

#include "../_layout/unit_class.h"
#include "../_layout/ebolt_class.h"
#include "../core/cell_step_tables.h"
#include "../map/cell_class_bridge_tile_queries.h"

#include "../renderer/techno_class_drawer_methods.h"

// GLOBAL: GAMEMD 0xA83D4C
HouseClass* DAT_00A83D4C;
// GLOBAL: GAMEMD 0xB054D0
ColorSchemeVec_00705D70 DAT_00B054D0;

#include "../_layout/house_type_class.h"
#include "../ui/input_controls/ui_display_chain.h"

#include "../_layout/map_0087f7e8.h"

#include "../_layout/tactical.h"
// GLOBAL: GAMEMD 0x887324 -- the tactical view.
extern Tactical* DAT_00887324;

// Coordinate arithmetic shared by the two segment routines.
static __inline CoordStruct times3_006F6030(const CoordStruct* v)
{
    CoordStruct r;
    r.X = v->X * 3;
    r.Y = v->Y * 3;
    r.Z = v->Z * 3;
    return r;
}

static __inline CoordStruct plus_006F6030(const CoordStruct& l, const CoordStruct* r)
{
    CoordStruct s;
    s.X = l.X + r->X;
    s.Y = l.Y + r->Y;
    s.Z = l.Z + r->Z;
    return s;
}

static __inline CoordStruct quarter_step_006F6030(const CoordStruct* a, const CoordStruct* b)
{
    CoordStruct s = plus_006F6030(times3_006F6030(a), b);
    CoordStruct r;
    r.X = s.X / 4;
    r.Y = s.Y / 4;
    r.Z = s.Z / 4;
    return r;
}

// Draw a line between two coordinates as two segments, each running from one
// end to the point three quarters of the way back; a segment is always given
// to the draw call with its higher end first.
// Unclaimed (below partial bar), GAMEMD 0x6F5EF0
void __fastcall FUN_006F5EF0(const CoordStruct* a, const CoordStruct* b, int color)
{
    CoordStruct scratch;
    CoordStruct sumA = plus_006F6030(times3_006F6030(a), b);
    CoordStruct nearA = *scratch.FUN_0041C230(sumA.X / 4, sumA.Y / 4, sumA.Z / 4);
    CoordStruct sumB = plus_006F6030(times3_006F6030(b), a);
    CoordStruct nearB = *scratch.FUN_0041C230(sumB.X / 4, sumB.Y / 4, sumB.Z / 4);
    if (a->Z > nearA.Z) {
        DAT_00887324->vf_24(a, &nearA, color, 0);
    } else {
        DAT_00887324->vf_24(&nearA, a, color, 0);
    }
    if (b->Z > nearB.Z) {
        DAT_00887324->vf_24(b, &nearB, color, 0);
    } else {
        DAT_00887324->vf_24(&nearB, b, color, 0);
    }
}

// The cell a coordinate lies in.
static __inline CellStruct cell_from_coord_006FBDC0(const CoordStruct& coord)
{
    CellStruct cell;
    cell.X = (short)(coord.X / 256);
    cell.Y = (short)(coord.Y / 256);
    return cell;
}

// The shortest primary-weapon range among the occupants of a transport,
// from INT_MAX. The walk follows the NextObject links while they stay feet.
static __inline int shortest_passenger_range_007012C0(TechnoClass* transport)
{
    int best = 0x7FFFFFFF;
    TechnoClass* node = (TechnoClass*)transport->Passengers.GetFirstPassenger();
    if (node != 0) {
        do {
            WeaponStruct* weapon = node->GetPrimaryWeapon();
            if (weapon->WeaponType != 0 && weapon->WeaponType->Range < best) {
                best = weapon->WeaponType->Range;
            }
            node = (TechnoClass*)node->NextObject;
        } while (node != 0 && node->Flags.IsFoot);
    }
    return best;
}

// Unclaimed (below partial bar), GAMEMD 0x7012C0
int TechnoClass::vf_90(int weapon)
{
    WeaponStruct* chosen = vf_254(weapon);
    if (chosen->WeaponType != 0) {
        int range = chosen->WeaponType->Range;
        if (vf_33()->OpenTopped) {
            if (range < shortest_passenger_range_007012C0(this)) {
                return range;
            }
            return shortest_passenger_range_007012C0(this);
        }
        return range;
    }
    return 0;
}

// GLOBAL: GAMEMD 0x84314C -- the two-letter name tested by the voice routine.
extern "C" const char DAT_0084314C[];
#include "../core/randomizer.h"

// GLOBAL: GAMEMD 0xAC147C -- the pip shape file.
extern SHPStruct* DAT_00AC147C;
// GLOBAL: GAMEMD 0x887314 -- the surface drawn to.
extern void* DAT_00887314;
// GLOBAL: GAMEMD 0x87F6C4 -- the palette conversion drawn with.
extern void* DAT_0087F6C4;
// Declaration: GAMEMD 0x4AED70 -- ECX surface, EDX conversion, RET56.
void __fastcall FUN_004AED70(void* surface, void* conversion, void* shape,
    int frame, const Point2D* point, RectangleStruct* clip, int flags,
    int a8, int z, int a10, int intensity, int a12, int a13, int a14,
    Point2D offset);

// FUNCTION: GAMEMD 0x70A990
// Draw the rank pip beside this object: the veteran or elite frame, or the
// special one, nudged further for anything that is not infantry.
void TechnoClass::vf_277(Point2D* where, RectangleStruct* clip)
{
    vf_34();
    SHPStruct* pips = DAT_00AC147C;
    int frame = -1;
    if (Veterancy.FUN_0074FF90()) {
        frame = 14;
    }
    if (Veterancy.FUN_00750010()) {
        frame = 15;
    }
    if (Veterancy.FUN_0074FFF0()) {
        frame = 19;
    } else if (frame == -1) {
        return;
    }
    Point2D at = *where;
    at.Y += 2;
    at.X += 5;
    if (vf_11() != 15) {
        at.X += 5;
        at.Y += 4;
    }
    Point2D zero(0, 0);
    FUN_004AED70(DAT_00887314, DAT_0087F6C4, pips, frame, &at, clip,
        0xE00, 0, -2, 0, 1000, 0, 0, 0, zero);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// GLOBAL: GAMEMD 0x7E3808 -- 0.01
extern const double DAT_007E3808;
// GLOBAL: GAMEMD 0x7E1718 -- 1.0
extern const double DAT_007E1718;
extern const double GG_ZERO;
#include "../_layout/session_class.h"

// Unclaimed (below partial bar), GAMEMD 0x70B1D0
// Reveal the map around where this object last looked. A pending reveal
// (flag at +0x250) is spent here, for the given house when one is passed with
// the third argument, else for the owner; otherwise it reveals only when the
// third argument is set and a house was passed.
void TechnoClass::vf_291(int a1, int a2, bool a3, HouseClass* a4)
{
    if (IsInPlayfield) {
        HouseClass* owner = Owner;
        if (!owner->Type->MultiplayPassive) {
            int range;
            if (unknown_bool_250) {
                range = LastSightRange;
                unknown_bool_250 = 0;
                if (range != 0 && a3 && a4) {
                    DAT_0087F7E8.FUN_005678E0(LastSightCoords, range, a4, a1, a2, 0, 1, 1);
                } else if (range != 0) {
                    DAT_0087F7E8.FUN_005678E0(LastSightCoords, range, owner, a1, a2, 0, 1, 1);
                }
            } else if (a3 && LastSightRange != 0 && a4) {
                DAT_0087F7E8.FUN_005678E0(LastSightCoords, LastSightRange, a4, a1, a2, 0, 1, 1);
            }
        }
    }
}

// Declaration: GAMEMD 0x7509E0 -- VocClass::PlayAt; ECX index, EDX coordinate address, controller on the stack.
void* __fastcall FUN_007509E0(int index, CoordStruct* coords, void* controller);

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
#include "techno_static_timers.h"
#include "../_layout/rules_class.h"
#include "../_layout/abstract_class.h"
#include "../_layout/player_ptr_00a83d4c.h"
// GLOBAL: GAMEMD 0xB0EB38
AbstractClass* DAT_00B0EB38;
// GLOBAL: GAMEMD 0xB0EB3C
int DAT_00B0EB3C;
GG_STATIC_ASSERT(sizeof(DAT_00B0EB38) == 4);
GG_STATIC_ASSERT(sizeof(DAT_00B0EB3C) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, TalkBubbleTime) == 0x1800);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->TalkBubbleTime) == 4);

// Queue layout used by vf_221, confirmed by the retail stores at 0x6FFE8C-0x6FFF43.
GG_STATIC_ASSERT(offsetof(EventQueue128, Count) == 0x00);
GG_STATIC_ASSERT(offsetof(EventQueue128, Head) == 0x08);
GG_STATIC_ASSERT(offsetof(EventQueue128, List) == 0x0C);
GG_STATIC_ASSERT(offsetof(EventQueue128, Time) == 0x378C);
GG_STATIC_ASSERT(sizeof(EventQueue128) == 0x398C);

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB0EA80
CDTimerClass DAT_00B0EA80;
// END defined globals

#include "techno_class_death_weapon_methods.h"

#include "techno_class_invuln_tint_methods.h"

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"

struct Rules_0070D7A0
{
    char   _pad000[0x1700];
    double Threshold;          // +0x1700
};
GG_STATIC_ASSERT(offsetof(Rules_0070D7A0, Threshold) == 0x1700);
// GLOBAL: GAMEMD 0x8871E0 -- RulesClass::Instance.
extern Rules_0070D7A0* RulesInstance_0070D7A0;

struct WeaponTypeBase_r14
{
    char _pad000[0xB4];
    int  Range;                // +0xB4
};
GG_STATIC_ASSERT(offsetof(WeaponTypeBase_r14, Range) == 0xB4);

// The linked object at TechnoClass+0x310 (DamageParticleSystem slot): only
// its vtable slot 0xF8 is used here.
struct LinkedVtbl_r14;
struct LinkedObj_r14
{
    LinkedVtbl_r14* Vtbl;
};
typedef void (LinkedObj_r14::*FnF8_r14)();
struct LinkedVtbl_r14
{
    char     _pad000[0xF8];
    FnF8_r14 At_F8;                   // +0xF8
};

// Interface sub-object living at TechnoClass+4 (COM-style stdcall slot 4).
struct SubIface_r14;
typedef int (__stdcall *FnSub10_r14)(SubIface_r14* self);
struct SubIfaceVtbl_r14
{
    char        _pad000[0x10];
    FnSub10_r14 At_10;                // +0x10
};
struct SubIface_r14
{
    SubIfaceVtbl_r14* Vtbl;
};

// First node of an embedded list head (reads the head's +4 pointer).
struct ListHead_r14
{
    // FUNCTION: GAMEMD 0x473450 (decl; reloc)
    TechnoClass* FUN_00473450();
};

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"

// One row of the per-difficulty table in the rules, as far as the first flag byte.
struct TechnoRulesDifficulty_r16
{
    char Flag;   // +0x00
    char unknown_01[0x4F];
};
// The rules object, as far as the two members the cost weight reads.
struct TechnoRulesView_r16
{
    char unknown_0000[0x1450];
    int unknown_1450;   // +0x1450
    char unknown_1454[0x1582 - 0x1454];
    TechnoRulesDifficulty_r16 Difficulty[3];   // +0x1582, stride 0x50
};
GG_STATIC_ASSERT(offsetof(TechnoRulesView_r16, unknown_1450) == 0x1450);
GG_STATIC_ASSERT(offsetof(TechnoRulesView_r16, Difficulty) == 0x1582);
// GLOBAL: GAMEMD 0x8871E0 -- the rules.
extern TechnoRulesView_r16* DAT_008871E0_r16;

// A plain derived view of TechnoClass for the overrides the canonical class does not declare.
class TechnoView_r16 : public TechnoClass
{
public:
    virtual int vf_96();
};

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../core/randomizer.h"

// The tactical view object (GLOBAL 0x887324): only the word at +0xB4 is read.
struct TacticalView_r21_4
{
    char  _pad000[0xB4];
    short ViewWord;            // +0xB4
};
GG_STATIC_ASSERT(offsetof(TacticalView_r21_4, ViewWord) == 0xB4);
// GLOBAL: GAMEMD 0x887324 -- Tactical::Instance.
extern TacticalView_r21_4* TacticalInstance_r21_4;

// The rules object, as far as the four per-side crew values.
struct RulesView_00707D20
{
    char _pad000[0xF6C];
    int  DefaultCrew;          // +0xF6C
    char _pad0F70[0x8];
    int  SideCrew0;            // +0xF78
    int  SideCrew1;            // +0xF7C
    int  SideCrew2;            // +0xF80
};
GG_STATIC_ASSERT(offsetof(RulesView_00707D20, DefaultCrew) == 0xF6C);
GG_STATIC_ASSERT(offsetof(RulesView_00707D20, SideCrew0) == 0xF78);
GG_STATIC_ASSERT(offsetof(RulesView_00707D20, SideCrew2) == 0xF80);
// GLOBAL: GAMEMD 0x8871E0 -- the rules.
extern RulesView_00707D20* RulesInstance_00707D20;

// The scenario object, as far as the random number generator it carries.
struct ScenarioView_00707D20
{
    char       _pad000[0x218];
    Randomizer Random;         // +0x218
};
GG_STATIC_ASSERT(offsetof(ScenarioView_00707D20, Random) == 0x218);
// GLOBAL: GAMEMD 0xA8B230 -- the scenario.
extern ScenarioView_00707D20* ScenarioInstance_00707D20;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x887324
TacticalView_r21_4* TacticalInstance_r21_4;
// END defined globals

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/building_class.h"
#include "../_layout/building_type_class_layout.h"
#include "../_layout/aircraft_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/house_class.h"
#include "../_layout/warhead_type_class.h"
#include "weapon_type_class.h"
#include "bullet_type_class.h"

// GLOBAL: GAMEMD 0x7E2800 -- 0.0, read from memory rather than FLDZ.
extern const double DAT_007E2800;

static inline BuildingClass* AsBuilding(AbstractClass* object)
{
    return object->vf_11() == 6 ? (BuildingClass*)object : 0;
}

#include "../_layout/techno_class.h"
#include "../core/scenario_class_methods.h"

#include "../_layout/scenario_ptr_00a8b230.h"
// GLOBAL: GAMEMD 0xA8E7AC -- nonzero while a scenario is being set up.
extern int DAT_00A8E7AC;

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"

#include "../core/techno_class_disguise.h"

#include "../_layout/techno_class.h"
#include "../_layout/temporal_class.h"

GG_STATIC_ASSERT(offsetof(TechnoClass, IdleActionTimer) == 0x168);
GG_STATIC_ASSERT(offsetof(TechnoClass, IdleActionTimer) + offsetof(CDTimerClass, TimeLeft) == 0x170);
GG_STATIC_ASSERT(offsetof(TechnoClass, TemporalImUsing) == 0x274);
GG_STATIC_ASSERT(sizeof(((TechnoClass*)0)->TemporalImUsing) == 4);
GG_STATIC_ASSERT(offsetof(TemporalClass, Target) == 0x28);
GG_STATIC_ASSERT(sizeof(((TemporalClass*)0)->Target) == 4);

#include "../core/techno_class_mc.h"

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"

GG_STATIC_ASSERT(offsetof(TechnoTypeClass, bools_C8C) + 8 == 0xC94);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->bools_C8C[8]) == 1);
GG_STATIC_ASSERT(offsetof(TechnoClass, IsTether) == 0x418);
GG_STATIC_ASSERT(sizeof(((TechnoClass*)0)->IsTether) == 1);

#include "../core/techno_class_opentopped_methods.h"

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x87F778
LogicClass LogicInstance;
// END defined globals

#include "../core/techno_class_owner_methods.h"

// Sidebar "tab object" globals @ 0x00B0FE5C / 0x00B0FE60. Declared-only so cl
// emits reloc-normalised absolute stores/compares.
extern TechnoClass* SidebarTabObjectA;   // 0x00B0FE5C
extern TechnoClass* SidebarTabObjectB;   // 0x00B0FE60

#include "../core/techno_class_setters.h"

#include "../core/techno_class_voice_methods.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "../core/vector_class_operations.h"

// A link up a chain of owners (the link lives at +0x54 here and at +0x5D8 in the owner).
struct Owned_006EC220
{
    unsigned char unknown_00[0x54];
    struct Chain_006EC220* Owner;   // +0x54

    bool FUN_006EC220(Chain_006EC220* ancestor) const;
};
struct Chain_006EC220
{
    unsigned char unknown_00[0x5D8];
    Chain_006EC220* Parent;         // +0x5D8
};
GG_STATIC_ASSERT(offsetof(Owned_006EC220, Owner) == 0x54);
GG_STATIC_ASSERT(offsetof(Chain_006EC220, Parent) == 0x5D8);

// FUNCTION: GAMEMD 0x65AC40 (decl; reloc)
void __stdcall FUN_0065AC40(int a, int b, int c);

// LIBRARY: GAMEMD 0x7C8D20 -- CRT string compare (cdecl, two pointers).
extern "C" int __cdecl FUN_007C8D20(const char* a, const char* b);

struct Obj_0071DD80
{
    unsigned char unknown_00[0x24];
    char ID[1];                     // +0x24, name buffer
};
extern DynamicVectorClass<Obj_0071DD80*> DAT_00A8E318;

// A record with a 0x290-byte tail of small state.
struct Record_00720440
{
    unsigned char Flag0;           // +0x000
    unsigned char unknown_001[0xFF];
    unsigned char Flag100;         // +0x100
    unsigned char unknown_101[0xFF];
    unsigned short Word200;        // +0x200
    unsigned char unknown_202[0x7E];
    int Field280;                  // +0x280
    int Field284;                  // +0x284
    unsigned char Active;          // +0x288
    unsigned char Flag289;         // +0x289
    unsigned char Flag28A;         // +0x28A
    unsigned char unknown_28B;
    int Field28C;                  // +0x28C

    Record_00720440* FUN_00720440();
};
GG_STATIC_ASSERT(offsetof(Record_00720440, Word200) == 0x200);
GG_STATIC_ASSERT(offsetof(Record_00720440, Field280) == 0x280);
GG_STATIC_ASSERT(offsetof(Record_00720440, Active) == 0x288);
GG_STATIC_ASSERT(offsetof(Record_00720440, Field28C) == 0x28C);

// A list of the records above, held as a pointer array and a count.
struct RecordList_007211E0
{
    unsigned char unknown_00[0x18];
    Record_00720440** Items;   // +0x18
    unsigned char unknown_1C[8];
    unsigned int Count;        // +0x24

    bool FUN_007211E0(unsigned int index) const;
};
GG_STATIC_ASSERT(offsetof(RecordList_007211E0, Items) == 0x18);
GG_STATIC_ASSERT(offsetof(RecordList_007211E0, Count) == 0x24);

struct Level_00721290
{
    unsigned char unknown_00[0xC];
    int Value;   // +0x0C

    void FUN_00721290(int value);
};
GG_STATIC_ASSERT(offsetof(Level_00721290, Value) == 0xC);

// A pair of dwords written as "%d,%d".
struct IntPair_00723CA0
{
    int First;    // +0x00
    int Second;   // +0x04

    void FUN_00723CA0(const char* text);
    int FUN_00723CE0(char* out) const;
};
GG_STATIC_ASSERT(offsetof(IntPair_00723CA0, Second) == 0x04);

#include "../renderer/techno_class_airstrike_tint_methods.h"

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/unit_type_class.h"
#include "../_layout/foot_class.h"
#include "../_layout/house_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/map_0087f7e8.h"
#include "../_layout/veinhole_monster_class.h"
#include "../_layout/warhead_type_class.h"
#include "../_layout/player_ptr_00a83d4c.h"
#include "../platform/input_manager_class_methods.h"
#include "../core/scenario_class_methods.h"
#include "weapon_type_class.h"

// GLOBAL: GAMEMD 0xA8B230 -- the current scenario.
extern ScenarioClass* DAT_00A8B230;

// GLOBAL: GAMEMD 0xA8EBF8 .. 0xA8EC0C -- the modifier key codes tested below.
extern int DAT_00A8EBF8;
extern int DAT_00A8EBFC;
extern int DAT_00A8EC00;
extern int DAT_00A8EC04;
extern int DAT_00A8EC08;
extern int DAT_00A8EC0C;

#include "../_layout/overlay_type_class.h"
// GLOBAL: GAMEMD 0xA83D84 -- overlay type records by index
extern OverlayTypeClass** DAT_00A83D84;
// GLOBAL: GAMEMD 0xA8022C -- HouseClass::Array.Items
extern HouseClass** DAT_00A8022C;

// A fogged object, as far as this routine reads it.
struct FogView_00700600
{
    char unknown_000[0x24];
    int  unknown_24;            // +0x24
    HouseClass* unknown_28;     // +0x28
    char unknown_2C[4];
    int  unknown_30;            // +0x30
    char unknown_34[0x74 - 0x34];
    bool unknown_74;            // +0x74
    // FUNCTION: GAMEMD 0x4D28C0 (decl; reloc)
    OverlayTypeClass* FUN_004D28C0();
};
GG_STATIC_ASSERT(offsetof(FogView_00700600, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(FogView_00700600, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(FogView_00700600, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(FogView_00700600, unknown_74) == 0x74);

// The cell, as far as the cursor routine reads it beyond CellClass.
struct CellView_00700600
{
    // FUNCTION: GAMEMD 0x486900 (decl; reloc)
    bool FUN_00486900();
};

// The overlay type record at an index.
static inline OverlayTypeClass* OverlayAt(int index)
{
    return DAT_00A83D84[index];
}

// Whether an object is a building (null-safe).
static inline bool IsBuilding(AbstractClass* object)
{
    return object && object->vf_11() == 6;
}

// Whether a key is held, via the shared input manager.
static inline bool KeyDown(int key)
{
    return DAT_0087F770->IsKeyPressed(key);
}

// Whether the object can attack the centre of a cell with the given weapon.
static inline bool CanTargetCell(TechnoClass* object, CellStruct* cell, int weapon)
{
    CoordStruct coords;
    coords.Z = 0;
    coords.X = cell->X * 256 + 128;
    coords.Y = cell->Y * 256 + 128;
    return object->vf_89(coords, weapon);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8EBF8
int DAT_00A8EBF8;
// GLOBAL: GAMEMD 0xA8EBFC
int DAT_00A8EBFC;
// GLOBAL: GAMEMD 0xA8EC00
int DAT_00A8EC00;
// GLOBAL: GAMEMD 0xA8EC04
int DAT_00A8EC04;
// GLOBAL: GAMEMD 0xA8EC08
int DAT_00A8EC08;
// GLOBAL: GAMEMD 0xA8EC0C
int DAT_00A8EC0C;
// GLOBAL: GAMEMD 0xA83D84
OverlayTypeClass** DAT_00A83D84;
// END defined globals

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/building_class.h"
#include "../_layout/building_type_class_layout.h"
#include "../_layout/unit_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/house_class.h"
#include "../_layout/rules_class.h"
#include "../_layout/map_0087f7e8.h"
#include "../_layout/scenario_ptr_00a8b230.h"
#include "../core/scenario_class_methods.h"
#include "../core/vector_class_operations.h"
#include "../core/vector_class_mutation.h"
#include "../core/mathtbl_init_shapes.h"

// GLOBAL: GAMEMD 0xA8EC78 -- TechnoClass::Array.
extern DynamicVectorClass<TechnoClass*> DAT_00A8EC78;
// GLOBAL: GAMEMD 0xB0EA90
extern MathTblZero3 DAT_00B0EA90;

// Rank-granted cloak: a veteran whose type grants the cloak ability at the veteran tier, or an elite
// granted it at either tier.
static inline bool CloaksByRank(TechnoClass* self)
{
    VeterancyStruct* vet = &self->Veterancy;
    TechnoTypeClass* type;
    return (vet->FUN_0074FF90() || vet->FUN_00750010())
        && (type = self->vf_33(),
            (vet->FUN_0074FF90() && type->VeteranAbilities._raw[6])
            || (vet->FUN_00750010() && (type->VeteranAbilities._raw[6] || type->EliteAbilities._raw[6])));
}

// The stage advance shared by both paths: when the timer has run out and a rate is set, step the value and
// restart the timer; the changed flag reports whether it advanced.
static inline void AdvanceStage(StageClass& stage)
{
    if (!stage.Timer.FUN_00426630() && stage.Rate != 0) {
        stage.HasChanged = true;
        stage.Value += stage.Step;
        stage.Timer = CDTimerClass(stage.Rate);
    } else {
        stage.HasChanged = false;
    }
}

#include "../_layout/techno_class.h"
#include "../_layout/rules_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/map_0087f7e8.h"

extern float __cdecl FUN_004CAC40(double value);

// GLOBAL: GAMEMD 0xB0EB34
extern int DAT_00B0EB34;

static inline double ElevationCap()
{
    return Rules->ElevationBonusCap;
}

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/foot_class.h"
#include "../core/randomizer.h"
#include "../_layout/rules_class.h"
#include "../_layout/tactical.h"
#include "../_layout/building_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/house_class.h"
#include "../core/frame_counter.h"

// Null-tolerant "as FootClass" casts, as retail inlined them into callers that
// pass `this` (the null test is in the retail bytes at 0x6FCD67 / 0x700D13).
static inline bool IsFootObject(TechnoClass* object)
{
    return object && object->Flags.IsFoot;
}

static inline FootClass* AsFootByRtti(TechnoClass* object)
{
    if (object && object->vf_11() == 1) {
        return (FootClass*)object;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x750E20 (decl; reloc) -- play a positional sound; RET 4.
void __fastcall FUN_00750E20(int sound, CoordStruct* where, int unused);

// FUNCTION: GAMEMD 0x6B7100 / 0x6B7BB0 (decl; reloc) -- SpawnManager teardown steps.
#include "../_layout/spawn_manager_class.h"

// Rules fields read here that the shared RulesClass layout has not named yet.
struct RulesView_DF4 {
    char unknown_000[0x1C4];
    int  unknown_1C4;
    char unknown_1C8[0x628 - 0x1C8];
    int  unknown_628;
    char unknown_62C[0x6A0 - 0x62C];
    int  unknown_6A0;
    char unknown_6A4[0xDF4 - 0x6A4];
    int  unknown_DF4;
    char unknown_DF8[0x16E0 - 0xDF8];
    double unknown_16E0;
    char unknown_16E8[0x17E9 - 0x16E8];
    unsigned char unknown_17E9;
};

GG_STATIC_ASSERT(offsetof(RulesView_DF4, unknown_16E0) == 0x16E0);
GG_STATIC_ASSERT(offsetof(RulesView_DF4, unknown_17E9) == 0x17E9);
GG_STATIC_ASSERT(offsetof(RulesView_DF4, unknown_628) == 0x628);
GG_STATIC_ASSERT(offsetof(RulesView_DF4, unknown_6A0) == 0x6A0);
GG_STATIC_ASSERT(offsetof(RulesView_DF4, unknown_1C4) == 0x1C4);
GG_STATIC_ASSERT(offsetof(RulesView_DF4, unknown_DF4) == 0xDF4);

// FUNCTION: GAMEMD 0x7509E0 (decl; reloc) -- play a sound at a coordinate; index in ECX,
// coordinate in EDX, RET 4.
void __fastcall FUN_007509E0(int index, const CoordStruct& where, int controller);

#include "../_layout/overlay_type_class.h"
// GLOBAL: GAMEMD 0xA83D84 -- table of type records indexed by a cell's overlay type.
extern OverlayTypeClass** DAT_00A83D84;

// FUNCTION: GAMEMD 0x4870F0 (decl; reloc) -- cell test taking an object's +0x30 link.
class CellView_004870F0 {
public:
    bool FUN_004870F0(void* link);
};

#include "../_layout/player_ptr_00a83d4c.h"

// GLOBAL: GAMEMD 0x887324
extern Tactical* DAT_00887324;

// GLOBAL: GAMEMD 0xB0EA50
extern CellStruct DAT_00B0EA50;

// GLOBAL: GAMEMD 0x886B88
extern Randomizer DAT_00886B88;

// GLOBAL: GAMEMD 0x7E27F8
extern double DAT_007E27F8;

// GLOBAL: GAMEMD 0x7E2800
extern const double DAT_007E2800;

static inline bool CellsDiffer(const CellStruct& a, const CellStruct& b)
{
    return a.X != b.X || a.Y != b.Y;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7E27F8
double DAT_007E27F8 = 900.0;
// END defined globals

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// 0x70FE50: stop draining power from another object.
struct House_0070FE50
{
    char unknown_0000[0x5778];
    unsigned char RecheckPower;   // +0x5778
};
GG_STATIC_ASSERT(offsetof(House_0070FE50, RecheckPower) == 0x5778);

struct Drained_0070FE50
{
    char unknown_000[0x1D0];
    void* DrainingMe;             // +0x1D0
    char unknown_1D4[0x21C - 0x1D4];
    House_0070FE50* Owner;        // +0x21C
};
GG_STATIC_ASSERT(offsetof(Drained_0070FE50, DrainingMe) == 0x1D0);
GG_STATIC_ASSERT(offsetof(Drained_0070FE50, Owner) == 0x21C);

struct DrainAnim_0070FE50
{
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Slot8();
    virtual void Slot9();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Slot28();
    virtual void Slot29();
    virtual void Slot30();
    virtual void Slot31();
    virtual void Slot32();
    virtual void Slot33();
    virtual void Slot34();
    virtual void Slot35();
    virtual void Slot36();
    virtual void Slot37();
    virtual void Slot38();
    virtual void Slot39();
    virtual void Slot40();
    virtual void Slot41();
    virtual void Slot42();
    virtual void Slot43();
    virtual void Slot44();
    virtual void Slot45();
    virtual void Slot46();
    virtual void Slot47();
    virtual void Slot48();
    virtual void Slot49();
    virtual void Slot50();
    virtual void Slot51();
    virtual void Slot52();
    virtual void Slot53();
    virtual void Slot54();
    virtual void Slot55();
    virtual void Slot56();
    virtual void Slot57();
    virtual void Slot58();
    virtual void Slot59();
    virtual void Slot60();
    virtual void Slot61();
    virtual void Release();   // +0xF8
};

struct Techno_0070FE50
{
    char unknown_000[0x1CC];
    Drained_0070FE50* DrainTarget;   // +0x1CC
    void* DrainingMe;                // +0x1D0
    DrainAnim_0070FE50* DrainAnim;   // +0x1D4
    void FUN_0070FE50();
};
GG_STATIC_ASSERT(offsetof(Techno_0070FE50, DrainTarget) == 0x1CC);
GG_STATIC_ASSERT(offsetof(Techno_0070FE50, DrainAnim) == 0x1D4);

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/capture_manager_class.h"

#include "../core/techno_class_threat_methods.h"

#include "../core/techno_class_weapon_methods.h"

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ============================================================================
// TechnoClass_00707000 - offsets confirmed from disassembly
// ============================================================================
struct TechnoClass_00707000
{
    char _pad0[256];
    char _pad100[36];        // 256+36 = 292
    int CurrentTurret;       // +0x0124 (292)
    char _pad128[24];        // 296 + 24 = 320
    int CaptureTarget;       // +0x0140 (320)
    int Ammo;                // +0x0144 (324)

    int GetCurrentTurret() const;   // 0x70DCF0
    int GetCaptureTarget() const;   // 0x70DDC0
    int GetAmmo() const;            // 0x70DDF0
};

GG_STATIC_ASSERT(offsetof(TechnoClass_00707000, CurrentTurret) == 292);
GG_STATIC_ASSERT(offsetof(TechnoClass_00707000, CaptureTarget) == 320);
GG_STATIC_ASSERT(offsetof(TechnoClass_00707000, Ammo) == 324);

// FUNCTION: GAMEMD 0x6F3270
// The techno type: slot 34 viewed as the derived type class.
TechnoTypeClass* TechnoClass::vf_33()
{
    return static_cast<TechnoTypeClass*>(vf_34());
}

// FUNCTION: GAMEMD 0x6F3280  (__thiscall)
// A mission gate: true when the object's current mission is none of 0, 6 and
// 0x10, and its type does not carry the byte at +0xC94.
//
// Retail dispatches GetCurrentMission three separate times rather than caching
// it, which is what an ordinary virtual call in three separate conditions
// gives — cl will not common a virtual call either, so the three-test spelling
// is the literal one. The gates are nested so `return false` remains the
// trailing fall-through and cl materialises `MOV AL,0x1`; spelled as early
// returns the last gate folds into a SET and the constant disappears.
bool TechnoClass::FUN_006F3280()
{
    if (vf_97() != 0) {
        if (vf_97() != 6) {
            if (vf_97() != 0x10) {
                if (!vf_33()->bools_C8C[8]) {
                    return true;
                }
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x6F32D0
// Alive, out of limbo, in the playfield, not of kind 6, discovered by the
// current player, of a selectable type, and owned by the current player.
bool TechnoClass::vf_25()
{
    return Health > 0 && !InLimbo && IsInPlayfield && vf_11() != 6
        && DiscoveredByCurrentPlayer && vf_33()->Selectable
        && Owner->IsControlledByCurrentPlayer();
}

// FUNCTION: GAMEMD 0x6F3330
// The weapon index to use against a target.
int TechnoClass::vf_185(AbstractClass* target)
{
    if (vf_33()->FUN_00717880() && !vf_33()->IsGattling) {
        return CurrentWeaponNumber == -1 ? 0 : CurrentWeaponNumber;
    }
    if (!vf_256()) {
        WeaponTypeClass* secondary = vf_254(1)->WeaponType;
        if (secondary) {
            WeaponTypeClass* primary = vf_254(0)->WeaponType;
            if (primary && !secondary->NeverUse && target) {
                if (InOpenToppedTransport && vf_33()->OpenTransportWeapon != -1) {
                    return vf_33()->OpenTransportWeapon;
                }
                TechnoClass* techno = target->Flags.IsTechno ? (TechnoClass*)target : 0;
                if (vf_33()->IsGattling) {
                    int stage = CurrentGattlingStage;
                    if (secondary->Projectile->unknown_2A4 && techno && techno->IsInAir()) {
                        return stage * 2 + 1;
                    }
                    return stage * 2;
                }
                if (secondary->Warhead->Airstrike) {
                    if (target->vf_11() == 6) {
                        if (AsBuilding(target)->Type->bools_1570[7]) {
                            if (AsBuilding(target)->vf_33()->ResourceDestination) {
                                if (!AsBuilding(target)->vf_33()->ResourceGatherer) {
                                    return 1;
                                }
                            } else {
                                return 1;
                            }
                        }
                    }
                } else {
                    if (primary->Warhead->IsLocomotor && techno && techno->vf_11() == 6) {
                        return 1;
                    }
                    if (secondary->DrainWeapon && techno && techno->vf_33()->Drainable
                        && !DrainTarget && !Owner->FUN_004F9A90(techno)) {
                        return 1;
                    }
                    if (secondary->AreaFire && vf_97() == 0x10) {
                        return 1;
                    }
                    if (vf_11() == 6 && ((BuildingClass*)this)->IsOverpowered) {
                        return 1;
                    }
                    if (target->vf_11() == 6 && Owner->CanOverpower((TechnoClass*)target)
                        && secondary->Warhead->ElectricAssault
                        && ((BuildingClass*)target)->Type->bools_1570[5]) {
                        return 1;
                    }
                    if (vf_11() == 2 && ((AircraftClass*)this)->IsKamikaze) {
                        return 1;
                    }
                    if (target->vf_11() == 0xB) {
                        CellClass* cell = (CellClass*)target;
                        if (((cell->LandType != 2 && target->IsOnFloor())
                                || ((cell->Flags & 0x100) && vf_33()->Naval))
                            && !target->IsInAir() && vf_33()->LandTargeting == 2) {
                            return 1;
                        }
                    }
                    if (techno) {
                        if (secondary->Warhead->Verses[techno->vf_33()->Armor] != DAT_007E2800) {
                            if (primary->Warhead->Verses[techno->vf_33()->Armor] == DAT_007E2800) {
                                return 1;
                            }
                            bool ground = techno->vf_111()->LandType == 2 || techno->vf_111()->LandType == 6;
                            if (techno->IsInAir()) {
                                ground = false;
                            }
                            if (!techno->OnBridge && ground) {
                                int weapon = vf_186((TechnoClass*)target);
                                if (weapon == -1) {
                                    weapon = 0;
                                }
                                return weapon;
                            } else {
                                if (!techno->IsInAir() && vf_33()->LandTargeting == 2) {
                                    return 1;
                                }
                                if (secondary->Projectile->unknown_2A4 && techno->IsInAir()) {
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6F3820
// -1, 0 or 1 for another techno, by this type's NavalTargeting mode and the
// other type's Underwater, SpeedType and two other flags. -1 when the other
// object is missing or not a techno.
int TechnoClass::vf_186(TechnoClass* other)
{
    if (other == 0 || !other->Flags.IsTechno) {
        return -1;
    }
    bool underwater = other->vf_33()->Underwater;
    bool flag_D97 = other->vf_33()->bools_D94[0xD97 - 0xD94];
    bool speed3 = other->vf_33()->SpeedType == 3;
    bool unnatural = other->vf_33()->Unnatural;

    switch (vf_33()->NavalTargeting) {
    case 0:
        if (underwater && other->CloakState != 0) {
            return -1;
        }
        break;
    case 1:
        return underwater != 0;
    case 2:
        return underwater ? 0 : -1;
    case 3:
        if (flag_D97 || unnatural) {
            return 1;
        }
        break;
    case 4:
        if (!speed3 && !flag_D97) {
            return 1;
        }
        break;
    case 5:
        return 0;
    case 6:
        return -1;
    case 7:
        return 0;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6F3950
int TechnoClass::vf_180()
{
    return vf_33()->Crewed != 0;
}

// FUNCTION: GAMEMD 0x6F3970
//
// The damage one weapon does, or, asked about no weapon in particular, the
// average over the weapons this object actually carries. A burst-firing
// type that is not itself a gattling reports only the weapon its current
// stage selects.
//
// PARTIAL (24.4%, up from 6.5%; 120 instructions against retail's 123).
// The lever was block placement, not phrasing: retail tests `which != -1`
// and jumps AWAY to the single-weapon path, so the all-weapons body is the
// fallthrough and the single-weapon body sits at the end of the function.
// Writing the guard the other way round (`if (which != -1) { ...; return
// total; }` first) puts the short arm inline and shifts all 120 instructions.
// Inverting it to `if (which == -1) { ...big...} ` with the single-weapon
// tail trailing reproduces retail's own layout and every call, guard and
// accumulation lines up.
//
// Residual, and it is two separate 8447-vs-8804 backend differences:
//   * retail DUPLICATES the averaging tail into the burst arm and divides by
//     a register holding one (`MOV EBX,1; ... CDQ; IDIV EBX`); cl 8804
//     propagates the constant into the division and deletes it. Measured:
//     a per-arm `return total / count;` costs an extra zero-return block and
//     scores 23.4%; one shared tail keeps 24.4% and is kept.
//   * retail reaches the zero return with `TEST EBX,EBX; JLE` backwards to a
//     shared `XOR EAX,EAX` block placed inline in the burst arm; cl inlines
//     its own zero return at the test and jumps over it with `JG`. Routing
//     both zero exits through one `goto zero;` label makes cl merge the burst
//     arm's two zero blocks as well and loses three more instructions
//     (21.1% / 22.0% over three label placements), so the guards stay
//     separate.
int Techno_006F3970::CombatDamage(int which)
{
    int total = 0;

    if (which == -1) {
        int count = 0;
        if (FUN_00717880((this->*Vptr->GetTechnoType)())
            && (this->*Vptr->GetTechnoType)()->IsGattling == 0) {
            Weapon_006F3970* weapon = (this->*Vptr->GetWeapon)(GattlingStage);
            if (weapon == 0) {
                return 0;
            }
            WeaponType_006F3970* type = weapon->Type;
            if (type == 0) {
                return 0;
            }
            total = type->Damage + type->At_98;
            count = 1;
        } else {
            if ((this->*Vptr->GetWeapon)(0)->Type != 0) {
                total = (this->*Vptr->GetWeapon)(0)->Type->Damage;
                count = 1;
                total += (this->*Vptr->GetWeapon)(0)->Type->At_98;
            }
            if ((this->*Vptr->GetWeapon)(1)->Type != 0) {
                total += (this->*Vptr->GetWeapon)(1)->Type->Damage;
                total += (this->*Vptr->GetWeapon)(1)->Type->At_98;
                count++;
            }
            if (count <= 0) {
                return 0;
            }
        }
        return total / count;
    }

    if ((this->*Vptr->GetWeapon)(which)->Type != 0) {
        total = (this->*Vptr->GetWeapon)(which)->Type->Damage;
        total += (this->*Vptr->GetWeapon)(which)->Type->At_98;
    }
    return total;
}

// FUNCTION: GAMEMD 0x6F4960
// Mark this object discovered by a house. Returns false when it already was
// or the base refuses; a computer house's discovery can switch a mission 14
// object to mission 15, and the current player's fires tag event 4 and flags
// the owner's power and radar for a recheck.
bool TechnoClass::vf_102(HouseClass* house)
{
    if (house == CurrentPlayer) {
        if (DiscoveredByCurrentPlayer) {
            return false;
        }
    } else {
        if (DiscoveredByComputer) {
            return false;
        }
        DiscoveredByComputer = true;
    }
    if (!ObjectClass::vf_102(house)) {
        return false;
    }
    if (!house->IsControlledByHuman() && vf_97() == 14) {
        vf_122(15, false);
    }
    if (house == CurrentPlayer) {
        DiscoveredByCurrentPlayer = true;
        Owner->RecheckPower = true;
        Owner->RecheckRadar = true;
        if (!IsOwnedByCurrentPlayer) {
            if (!DAT_00A8E7AC && AttachedTag) {
                AttachedTag->FUN_006E53A0(4, this, DAT_00B0EA50, false, 0);
            }
            Owner->DiscoveredByPlayer = true;
        }
    } else {
        DiscoveredByComputer = true;
    }
    return true;
}

// FUNCTION: GAMEMD 0x6F4A40
void TechnoClass::vf_71()
{
    if (this->DiscoveredByCurrentPlayer) {
        if (!this->Owner->IsControlledByHuman()) {
            this->DiscoveredByCurrentPlayer = false;
        }
    }
}

// FUNCTION: GAMEMD 0x6F4A70  (__thiscall)
// Run the base step; if it declines, decline. If it succeeds and this object is
// tethered to a radio partner, send the partner message 0xD, then report
// success either way.
//
// The argument arrives as `MOV EAX,[ESP+0x4]` and the exit is `RET 4`: a
// stack-passed argument, so a plain __thiscall member rather than __fastcall.
//
// LEVER, the same one as its neighbour: the success path has to be nested with
// `return false` left as the function's trailing fall-through. Written as an
// early `if (!base) return false;` cl inverts the branch and inlines a second
// `POP ESI; RET 4` where retail has one shared `XOR AL,AL; POP ESI; RET 4`
// cold tail (30.0%, multiset off by a jump polarity and the XOR).
bool TechnoClass::vf_73(int mode)
{
    if (ObjectClass::vf_73(mode)) {
        if (this->IsTether) {
            vf_157(0xD);
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x6F6030
// One segment of the line above: from `a` to the point three quarters of the
// way to `b`, higher end first.
void __fastcall FUN_006F6030(const CoordStruct* a, const CoordStruct* b, int color)
{
    CoordStruct mid = quarter_step_006F6030(a, b);
    if (a->Z > mid.Z) {
        DAT_00887324->vf_24(a, &mid, color, 0);
    } else {
        DAT_00887324->vf_24(&mid, a, color, 0);
    }
}

// FUNCTION: GAMEMD 0x6F60C0
// Empty function that pops its stack arguments. Vtable slot 274 of TechnoClass (RTTI) and 5 derived vtable(s).
void Obj_006F60C0::FUN_006F60C0(int a1, int a2)
{
}

// FUNCTION: GAMEMD 0x6F6F40
int __stdcall FUN_006F6F40(Record_006F6F40* record)
{
    return record->unknown_08 / DAT_008871E0->LeptonsPerSightIncrease * 10;
}

// FUNCTION: GAMEMD 0x6F6F60
// Range bonus for an arcing shot: the height difference of the two cells (never negative) is
// turned into a vertical lepton figure, and the result combines it with the same figure
// scaled by DAT_00B0EB34 into a diagonal distance.
int TechnoClass::FUN_006F6F60(AbstractClass* target)
{
    if (IsOnFloor() && target->IsOnFloor()) {
        CellStruct hereCell = CoordToCell(vf_18());
        CellStruct thereCell = CoordToCell(target->vf_18());
        CellClass* hereCellObj = DAT_0087F7E8.FUN_005657A0(&hereCell);
        CellClass* thereCellObj = DAT_0087F7E8.FUN_005657A0(&thereCell);
        int height;
        if (hereCellObj->FUN_00487D50() - thereCellObj->FUN_00487D50() < 0) {
            height = 0;
        } else {
            height = hereCellObj->FUN_00487D50() - thereCellObj->FUN_00487D50();
        }
        int steps = height / Rules->ElevationIncrement;
        double bonus = steps * Rules->ElevationIncrementBonus;
        if (bonus >= ElevationCap()) {
            bonus = ElevationCap();
        }
        int vertical = DAT_00B0EB34 * height;
        int rise = (int)bonus << 8;
        return (int)FUN_004CAC40((double)(rise * rise + vertical * vertical));
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6F70E0
// The vertical part of the same bonus, in leptons (the result of 0x6F6F60 without the diagonal).
int TechnoClass::FUN_006F70E0(AbstractClass* target)
{
    if (IsOnFloor() && target->IsOnFloor()) {
        CellStruct hereCell = CoordToCell(vf_18());
        CellStruct thereCell = CoordToCell(target->vf_18());
        CellClass* hereCellObj = DAT_0087F7E8.FUN_005657A0(&hereCell);
        CellClass* thereCellObj = DAT_0087F7E8.FUN_005657A0(&thereCell);
        int height;
        if (hereCellObj->FUN_00487D50() - thereCellObj->FUN_00487D50() < 0) {
            height = 0;
        } else {
            height = hereCellObj->FUN_00487D50() - thereCellObj->FUN_00487D50();
        }
        int steps = height / Rules->ElevationIncrement;
        double bonus = steps * Rules->ElevationIncrementBonus;
        if (bonus >= ElevationCap()) {
            bonus = ElevationCap();
        }
        return (int)bonus << 8;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6F7780  (__thiscall)
// Is the target inside the range of the weapon this object would pick for it?
// One weapon selection feeding one range test, both on the same cached vtable.
bool TechnoClass::IsCloseEnoughToAttack(AbstractClass* target)
{
    return vf_234(target, vf_185(target));
}

// FUNCTION: GAMEMD 0x6F78D0
// Attack the target using whichever weapon is current: slot 234 (in range of
// that weapon) when the weapon type has the byte flag at +0x136, else slot 235.
bool TechnoClass::vf_237(AbstractClass* target)
{
    int weapon = vf_250();
    WeaponStruct* ws = vf_254(weapon);
    if (ws && ws->WeaponType && *((char*)ws->WeaponType + 0x136)) {
        return vf_234(target, weapon);
    }
    return IsCloseEnoughToAttack(target);
}

// FUNCTION: GAMEMD 0x6F7930
void TechnoClass::vf_236(CoordStruct* a1)
{
    CellClass* cell = MapClass_Instance.GetTargetCell(*a1);
    this->vf_234(cell, this->vf_185(cell));
}

// FUNCTION: GAMEMD 0x6F7970
bool TechnoClass::vf_89(const CoordStruct& coord, int weapon)
{
    return this->vf_234(MapClass_Instance.GetTargetCell(coord), weapon);
}

// FUNCTION: GAMEMD 0x6F9DB0
// Member getter (dword). Vtable slot 14 of TechnoClass (RTTI) and 5 derived vtable(s).
int Obj_006F9DB0::FUN_006F9DB0() const
{
    return unknown_21C->unknown_30;
}

// FUNCTION: GAMEMD 0x6F9DC0
// Member getter (dword). Vtable slot 15 of TechnoClass (RTTI) and 5 derived vtable(s).
int Obj_006F9DC0::FUN_006F9DC0() const
{
    return unknown_21C;
}

// FUNCTION: GAMEMD 0x6F9DD0
void TechnoClass::vf_82(int a1)
{
    if (this->vf_50(CurrentPlayer)) {
        if (!this->vf_52(true)) {
            return;
        }
    }
    this->DurationRemaining = a1;
}

// FUNCTION: GAMEMD 0x6F9E10
bool TechnoClass::vf_166()
{
    TechnoTypeClass* type = this->vf_33();
    if (!type->MainVoxel.unknown_00) {
        return false;
    }

    type = this->vf_33();
    return ((const unsigned char*)type->MainVoxel.unknown_00)[0] == 0;
}

// FUNCTION: GAMEMD 0x6FB010
void TechnoClass::vf_265()
{
    TechnoTypeClass* type = this->vf_33();
    int typeAmmo = type->Ammo;
    if (typeAmmo == -1) {
        return;
    }

    int ammo = this->Ammo;
    if (ammo >= typeAmmo) {
        return;
    }

    int timeLeft = this->ReloadTimer.TimeLeft;
    int startTime = this->ReloadTimer.StartTime;
    if (startTime != -1) {
        int elapsed = CurrentFrame - startTime;
        if (elapsed >= timeLeft) goto ready_to_reload;
        timeLeft -= elapsed;
    }
    if (timeLeft != 0) {
        return;
    }

ready_to_reload:
    this->Ammo++;
    this->vf_73(2);
    this->StartReloading();
}

// FUNCTION: GAMEMD 0x6FB080
//
// (Re)arm the reload countdown when the clip is not full. An empty clip with a
// distinct EmptyReload uses that; otherwise the delay is Reload plus
// ReloadIncrement scaled by the square of how many pip-wraps are loaded (one
// when the type does not wrap).
//
// The type is fetched through the virtual before every read, as retail does,
// and the timer is rewritten as a whole-struct copy of a fresh temporary, so
// the clock slot in the middle carries an uninitialised stack dword.
//
// Two named locals are load-bearing: the type's Ammo is bound before the
// compare so the techno's Ammo is read after the call (a single expression
// hoists the member load above the call into EDI and adds a push/pop pair),
// and the increment product is bound before the sum so the add lands in the
// Reload register (`ADD EAX,EDI`) rather than the product's.
void Techno_006FB080::StartReloading()
{
    int full = (this->*this->Vtbl->GetTechnoType)()->Ammo;
    if (this->Ammo < full) {
        if (this->Ammo == 0
            && (this->*this->Vtbl->GetTechnoType)()->EmptyReload != -1) {
            this->ReloadTimer =
                CDTimer_006FB080((this->*this->Vtbl->GetTechnoType)()->EmptyReload);
            return;
        }

        int wraps;
        if ((this->*this->Vtbl->GetTechnoType)()->PipWrap == 0) {
            wraps = 1;
        } else {
            wraps = this->Ammo / (this->*this->Vtbl->GetTechnoType)()->PipWrap;
        }

        int extra = (this->*this->Vtbl->GetTechnoType)()->ReloadIncrement * wraps * wraps;
        this->ReloadTimer = CDTimer_006FB080(
            (this->*this->Vtbl->GetTechnoType)()->Reload + extra);
    }
}

// FUNCTION: GAMEMD 0x6FB740
// Per-frame cloak update.
void TechnoClass::vf_260(int)
{
    if (CloakState == 0) {
        if (!IsCloakable() || IsUnderEMP() || vf_224() || vf_117() || vf_118()) {
            if (!CloaksByRank(this)) {
                return;
            }
        }
        TechnoClass* link = FUN_0065AD30(0);
        if (link && link->vf_11() == 6 && ((BuildingClass*)link)->Type->bools_16A4[25]) {
            return;
        }
        AdvanceStage(CloakProgress);
        if (vf_168()) {
            if (FUN_005F5C60() > Rules->ConditionRed) {
                vf_280(false);
                return;
            }
            if (DAT_00A8B230->unknown_0218.RandomRanged(0, 99) < 4) {
                vf_280(false);
            }
        }
        return;
    }
    AdvanceStage(CloakProgress);
    if (CloakProgress.Value < 0) {
        CloakProgress.Value = 0;
    }
    switch (CloakState) {
    case 3:
        vf_73(2);
        switch (vf_26(1, 0)) {
        case 0: {
            CloakProgress.SetRate(0);
            CloakProgress.Value = 0;
            CloakState = 0;
            CDTimerClass delay;
            delay.StartTime = delay.CurrentTime;
            delay.TimeLeft = (int)(Rules->CloakDelay * 900.0);
            CloakDelayTimer = delay;
            vf_73(2);
            return;
        }
        case 1:
            if (vf_168()) {
                vf_280(true);
            }
            break;
        }
        break;
    case 2:
        if (vf_169()) {
            vf_279(false);
        }
        break;
    case 1:
        vf_73(2);
        if (CloakProgress.Rate == 0) {
            CloakProgress.SetRate(1);
        }
        switch (vf_26(1, 0)) {
        case 2:
            if (FUN_005F5C60() > Rules->ConditionRed) {
                return;
            }
            if (DAT_00A8B230->unknown_0218.RandomRanged(0, 99) < 10) {
                vf_279(true);
            }
            break;
        case 3:
        case 5:
            CloakState = 2;
            CloakProgress.SetRate(0);
            CloakProgress.Value = 0;
            vf_73(2);
            if (vf_11() == 1 && ((UnitClass*)this)->FlagHouseIndex != -1) {
                vf_63();
            } else {
                DynamicVectorClass<TechnoClass*> watchers;
                for (int i = DAT_00A8EC78.Count - 1; i >= 0; i--) {
                    TechnoClass* other = DAT_00A8EC78.Items[i];
                    if (other->Target == this) {
                        if (DAT_0087F7E8.FUN_00565730(vf_18())->FUN_004870D0(other->Owner->ArrayIndex)
                            || other->Owner == Owner) {
                            watchers.AddItem(other);
                        }
                    }
                }
                vf_55(false);
                for (int j = watchers.Count - 1; j >= 0; j--) {
                    watchers.Items[j]->vf_242(this);
                }
            }
            if (vf_11() == 1 && !Owner->FUN_0050B730()) {
                vf_93(DAT_00B0EA90, true, false);
            }
            break;
        }
        break;
    }
}

// FUNCTION: GAMEMD 0x6FBDC0
// May this object cloak now: it must be able to (outright, or through a rank
// ability, or by standing in a cell its house owns the shroud of), not be
// mid-cloak, not be rearming or still waiting out the cloak delay, not be
// firing at something it is close enough to attack, and not be a foot object
// held by a locomotor attack.
bool TechnoClass::vf_168()
{
    if (!IsCloakable()) {
        if (Veterancy.FUN_0074FF90() || Veterancy.FUN_00750010()) {
            TechnoTypeClass* type = vf_33();
            if (Veterancy.FUN_0074FF90() && type->VeteranAbilities._raw[6]) {
                goto cloakable;
            }
            if (Veterancy.FUN_00750010() && (type->VeteranAbilities._raw[6] || type->EliteAbilities._raw[6])) {
                goto cloakable;
            }
        }
        CellStruct here = cell_from_coord_006FBDC0(vf_18());
        if (!reinterpret_cast<CellClass*>(DAT_0087F7E8.FUN_005657A0(&here))->FUN_004870B0(Owner->ArrayIndex) && !Cloakable) {
            return false;
        }
    }
cloakable:
    if (CloakState == 2) {
        return false;
    }
    int startTime = RearmTimer.StartTime;
    int timeLeft = RearmTimer.TimeLeft;
    int elapsed;
    if (startTime != -1) {
        elapsed = CurrentFrame - startTime;
        if (elapsed >= timeLeft) goto rearmed;
        timeLeft -= elapsed;
    }
    if (timeLeft != 0) {
        return false;
    }
rearmed:
    if (Target) {
        if (IsCloseEnoughToAttack(Target)) {
            return false;
        }
    }
    if (vf_11() != 6 && CloakProgress.Value) {
        return false;
    }
    startTime = CloakDelayTimer.StartTime;
    timeLeft = CloakDelayTimer.TimeLeft;
    if (startTime != -1) {
        elapsed = CurrentFrame - startTime;
        if (elapsed >= timeLeft) goto delayed;
        timeLeft -= elapsed;
    }
    if (timeLeft != 0) {
        return false;
    }
delayed:
    if (LocomotorSource) {
        FootClass* foot = foot_cast_007104C0(this);
        if (foot && foot->IsAttackedByLocomotor) {
            return false;
        }
    }
    return vf_114() <= 0;
}

// FUNCTION: GAMEMD 0x6FBFA0
// When allowed, tells the attached tag, wakes the object and reports success.
bool ObjectView_006FBFA0::FUN_006FBFA0()
{
    if (unknown_41B || unknown_21C->FUN_0050B6F0() || DAT_00B73550 == 0) {
        if (FUN_005F4520()) {
            if (unknown_34 != 0) {
                unknown_34->FUN_006E53A0(0x21, this, DAT_00B0EA50, 0, 0);
            }
            if (unknown_21C->FUN_0050B6F0() || unknown_21C->unknown_34->unknown_1A6) {
                if (DAT_00822CF2) {
                    vf_216();
                }
            }
            FUN_00637840();
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x6FC030
// True only when none of the blocking fields is set and the base check passes.
bool ObjectView_006FBFA0::FUN_006FC030()
{
    if (unknown_2DC != 0) {
        return false;
    }
    if (unknown_1C8) {
        return false;
    }
    if (unknown_2E4 != 0) {
        return false;
    }
    if (unknown_418 && FUN_0047C520(vf_111()) != 0) {
        return false;
    }
    return FUN_005F6C70();
}

// FUNCTION: GAMEMD 0x6FC090
// Calls other functions. Vtable slot 239 of TechnoClass (RTTI) and 5 derived vtable(s).
void Obj_006FC090::FUN_006FC090(int a1, int a2)
{
    vf_240(a1, a2, 0);
}

// FUNCTION: GAMEMD 0x6FCD40
// Stand down: clear the target, clear the destination, set slot 160 to 3.
// Then, unless this is a foot object that is being carried by a locomotor,
// tear down the spawn manager (if any) and run slot 55 with true. Finish with
// slot 84.
void TechnoClass::vf_232()
{
    vf_242(0);
    SetDestination(0, true);
    vf_160(3);
    if (!(IsFootObject(this) && ((FootClass*)this)->IsAttackedByLocomotor)) {
        if (SpawnManager) {
            ((SpawnManagerClass*)SpawnManager)->KillNodes();
            ((SpawnManagerClass*)SpawnManager)->ResetTarget();
        }
        vf_55(true);
    }
    vf_84();
}

// FUNCTION: GAMEMD 0x6FD570
// Pick the weapon for the target, build the bolt at the fire coordinate of that weapon and,
// for a live unit that has no bolt yet, take the bolt as its own and make this the owner.
EBolt* TechnoClass::FUN_006FD570(AbstractClass* target)
{
    int weaponIndex = vf_185(target);
    WeaponTypeClass* weapon = vf_254(weaponIndex)->WeaponType;
    CoordStruct none;
    none.X = 0;
    none.Y = 0;
    none.Z = 0;
    CoordStruct source = vf_44(weaponIndex, none);
    EBolt* bolt = FUN_006FD460(target, weapon, &source);
    if (bolt && vf_11() == 1 && IsAlive && ((UnitClass*)this)->ElectricBolt == 0) {
        ((UnitClass*)this)->ElectricBolt = bolt;
        bolt->SetOwner((UnitClass*)this, weaponIndex);
    }
    return bolt;
}

// FUNCTION: GAMEMD 0x6FF950
// Empty function.
void __cdecl FUN_006FF950()
{
}

// FUNCTION: GAMEMD 0x6FFE00
bool TechnoClass::vf_221(int eventType)
{
    TargetClass target;
    EventClass event(CurrentPlayer->ArrayIndex, eventType,
                     *target.FUN_006E6AB0(this));

    if (FUN_00637AA0()) {
        FUN_00639FD0(reinterpret_cast<char*>(&event));
        return false;
    }

    if (DAT_00A802C8.Count < 128) {
        DAT_00A802C8.List[DAT_00A802C8.Head] = event;
        DAT_00A802C8.Time[DAT_00A802C8.Head] = timeGetTime();
        DAT_00A802C8.Head = (DAT_00A802C8.Head + 1) & 0x7F;
        DAT_00A802C8.Count++;
    }
    return true;
}

// FUNCTION: GAMEMD 0x700600
// The cursor action over a map cell.
int TechnoClass::vf_28(CellStruct* cell, char a2, char a3)
{
    if (Berzerk) {
        return 0;
    }
    if (DirectRockerLinkedUnit && !vf_33()->Pushy) {
        return 0;
    }
    CellClass* mapCell = DAT_0087F7E8.FUN_005657A0(cell);
    OverlayTypeClass* overlay = 0;
    bool x = !a3 && (KeyDown(DAT_00A8EC00) || KeyDown(DAT_00A8EC04));
    bool y = !a3 && (KeyDown(DAT_00A8EC08) || KeyDown(DAT_00A8EC0C));
    bool z = !a3 && (KeyDown(DAT_00A8EBF8) || KeyDown(DAT_00A8EBFC));
    if (y && x) {
        y = false;
        x = false;
    }
    int overlayIndex = -1;
    bool flag = false;
    if (vf_117() || vf_118()) {
        return 0;
    }
    if ((DAT_00A8B230->unknown_0000 & 0x1000) && a2 && mapCell->FoggedObjects) {
        for (int i = 0; i < mapCell->FoggedObjects->Count; i++) {
            FogView_00700600* fog = (FogView_00700600*)mapCell->FoggedObjects->Items[i];
            if (fog->unknown_74) {
                if (fog->unknown_30 == 0x14) {
                    overlayIndex = fog->unknown_24;
                } else if (fog->unknown_30 == 6) {
                    if (!fog->unknown_28 || !DAT_00A83D4C->IsAlliedWith(fog->unknown_28)) {
                        if (!fog->FUN_004D28C0() || fog->FUN_004D28C0()->LegalTarget) {
                            flag = true;
                        }
                    }
                }
            }
        }
    }
    if (overlayIndex != -1) {
        overlay = DAT_00A83D84[overlayIndex];
    } else if (mapCell->OverlayTypeIndex != -1) {
        overlay = DAT_00A83D84[mapCell->OverlayTypeIndex];
    }
    bool canAttack = vf_204();
    if (Owner->IsControlledByCurrentPlayer() && ((x && z) || unknown_bool_43A) && vf_40()
        && (vf_39() || canAttack)) {
        if (!DAT_00A83D4C->GetPlanningWaypointAt(cell) && !unknown_bool_43A) {
            return 0x1a;
        }
        return 0x33;
    }
    WeaponStruct* primary;
    if (Owner->IsControlledByCurrentPlayer() && (primary = GetPrimaryWeapon()) != 0 && primary->WeaponType) {
        int weapon = vf_185(DAT_0087F7E8.FUN_005657A0(cell));
        bool unfriendly = ((CellView_00700600*)DAT_0087F7E8.FUN_005657A0(cell))->FUN_00486900();
        if (unfriendly) {
            WeaponTypeClass* fireWeapon = GetPrimaryWeapon()->WeaponType;
            if (fireWeapon->Warhead->Fire) {
                unfriendly = false;
            }
        }
        if (x || (overlay && overlay->LegalTarget) || unfriendly || flag) {
            WarheadTypeClass* warhead = GetPrimaryWeapon()->WeaponType->Warhead;
            bool notAllied;
            if (mapCell->WallOwnerIndex != -1) {
                notAllied = !DAT_00A8022C[mapCell->WallOwnerIndex]->IsAlliedWith(Owner);
            } else {
                notAllied = false;
            }
            VeinholeMonsterClass* monster = VeinholeMonsterClass::GetVeinholeMonsterFrom(cell);
            bool alive = monster && !monster->IsDead && monster->Health > 0;
            if (x || !overlay || alive
                || (notAllied && overlay->Wall
                    && (warhead->Wall || (warhead->Wood && overlay->Armor == 6)))) {
                if (vf_40() || CanTargetCell(this, cell, weapon)) {
                    return 5;
                }
            }
        }
        if (vf_230(mapCell)) {
            if (vf_40() || CanTargetCell(this, cell, weapon)) {
                return 5;
            }
        }
    }
    if (Owner->IsControlledByCurrentPlayer() && (vf_40() || vf_161())) {
        if (DAT_0087F7E8.FUN_00578460(cell, 1)) {
            if (y) {
                return 1;
            }
            if (vf_161() && z) {
                return 1;
            }
            if (vf_40()) {
                if (!a2) {
                    if (vf_107(DAT_0087F7E8.FUN_005657A0(cell), -1, -1, 0, true) > 1) {
                        if (IsBuilding(this) && vf_33()->UndeploysInto
                            && vf_33()->UndeploysInto->ResourceGatherer) {
                            return 1;
                        }
                        if (vf_33()->bools_D20[12]
                            && vf_107(DAT_0087F7E8.FUN_005657A0(cell), -1, -1, 0, false) <= 1) {
                            return 1;
                        }
                        return 2;
                    }
                }
                return 1;
            }
        }
        return 2;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x700C40
bool TechnoClass::vf_40()
{
    if (!this->Owner->IsControlledByCurrentPlayer()) {
        return false;
    }
    if (this->IsUnderEMP()) {
        return false;
    }
    if (this->BunkerLinkedItem != 0) {
        return false;
    }

    TechnoTypeClass* type = this->vf_33();
    if (type->Spawned) {
        return false;
    }
    if (this->vf_224()) {
        return false;
    }
    if (!this->vf_120()) {
        return false;
    }
    if (this->SlaveOwner != 0) {
        return false;
    }
    if (this->Deactivated) {
        return false;
    }

    if (this->SpawnManager != 0) {
        int launching = static_cast<SpawnManagerClass*>(this->SpawnManager)->CountLaunchingSpawns();
        if (launching > 0) {
            type = this->vf_33();
            launching = static_cast<SpawnManagerClass*>(this->SpawnManager)->CountLaunchingSpawns();
            if (launching < type->SpawnsNumber) {
                return false;
            }
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x700D10
// False when this is an RTTI-1 object that either has a tube index with slot
// 313 true, or is under EMP; true otherwise.
bool TechnoClass::vf_196()
{
    FootClass* foot = AsFootByRtti(this);
    if (foot) {
        if ((foot->TubeIndex >= 0 && foot->vf_313()) || IsUnderEMP()) {
            return false;
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x7010D0  (__thiscall)
// Is this object sitting on guard with a usable weapon, for the local player?
// Four gates: not switched off, owned by the house the human is playing,
// holding a turret weapon with a real WeaponType behind it, and not currently
// EMP-locked.
//
// The exit is `MOV AL,0x1` / `XOR AL,AL`, so the return type is bool.
//
// LEVER: the gates have to be NESTED with `return false` as the function's
// trailing fall-through, not written as four early `return false`s. Spelled as
// early returns the last gate folds into `TEST AL,AL; SETE AL` and the
// materialised `MOV AL,0x1` disappears (59.3%); inverting only the last gate
// does not help, because cl folds whichever negated test ends the function.
bool TechnoClass::vf_39()
{
    if (!this->Deactivated) {
        if (this->Owner->IsControlledByCurrentPlayer()) {
            WeaponStruct* weapon = GetPrimaryWeapon();
            if (weapon != 0 && weapon->WeaponType != 0) {
                if (!IsUnderEMP()) {
                    return true;
                }
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x701120  (__thiscall)
// Does this object have a weapon at all? The turret-weapon slot has to hand
// back a record, and the record has to name a WeaponType.
//
// The exit is `MOV EAX,0x1` / `XOR EAX,EAX` (VC6 materialises a bool-typed
// `&&` result that way); every caller tests only AL, so the slot is bool.
bool TechnoClass::IsArmed()
{
    WeaponStruct* weapon = GetPrimaryWeapon();

    return weapon != 0 && weapon->WeaponType != 0;
}

// FUNCTION: GAMEMD 0x701140
// For an RTTI-6 object whose type is Repairable: true when Health differs from
// the type's Strength.
bool TechnoClass::vf_37()
{
    if (vf_11() != 6) {
        return false;
    }
    return vf_33()->Repairable && Health != vf_34()->Strength;
}

// FUNCTION: GAMEMD 0x701190
// Returns a constant boolean. Vtable slot 212 of TechnoClass (RTTI) and 4 derived vtable(s).
bool Obj_00701190::FUN_00701190() const
{
    return false;
}

// FUNCTION: GAMEMD 0x7013A0
void TechnoClass::vf_125(int mission, AbstractClass* a2, AbstractClass* a3)
{
    this->LastTarget = this->Target;
    MissionClass::vf_125(mission, a2, a3);
    this->vf_242(a2);
}

// FUNCTION: GAMEMD 0x7013E0
//
// When the base check passes, dispatch slot 0x3C8 with the +0x2B8 value and
// report success; otherwise report failure.
bool TechnoClass::FUN_007013E0()
{
    if (FUN_005B36B0()) {
        vf_242(LastTarget);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x701410
// Restore to full strength: run slot 73 with 2, set Health and EstimatedHealth
// to the type's Strength and, for an RTTI-6 (building) object, refresh its
// damaged-state animations and play the rules sound at its coordinate.
void TechnoClass::vf_259()
{
    vf_73(2);
    int strength = vf_33()->Strength;
    Health = strength;
    EstimatedHealth = strength;
    if (vf_11() == 6) {
        vf_103(0);
        ((BuildingClass*)this)->ToggleDamagedAnims(
            GetHealthPercentage() <= RulesInstance->ConditionYellow);
        FUN_007509E0(((RulesView_DF4*)RulesInstance)->unknown_1C4, vf_18(), 0);
    }
}

// FUNCTION: GAMEMD 0x7018C0
void TechnoClass::FUN_007018C0(HouseClass* house)
{
    this->Owner = house;
    this->IsOwnedByCurrentPlayer = (house == CurrentPlayer && CurrentPlayer != 0);
}

// FUNCTION: GAMEMD 0x703590
//
// A free cell near an object (or near this techno when none is given) that
// this techno's speed and movement zone can use. Amphibious speed is treated
// as wheeled; the zone type is looked up first, or -1 when the type has no
// zone.
//
// PARTIAL (52.9%, 55/104). The body between the speed test and the zone
// lookup is byte-exact once the cell comes from a by-value inline helper
// (two copies of the divide, each ending in a dword load of the temporary
// in the parameter slot, one shared store to the named cell). The residual
// is retail's constant handling in the final call: it keeps zero in EBP
// from the object null test (`XOR EBP,EBP; CMP ECX,EBP`) and spends it on
// the two trailing bool pushes and the word stores of the close-to cell
// (built late, in the parameter slot, as the thirteenth argument), then
// holds the repeated 1 in ECX/EDX (`MOV ECX,1; MOV EDX,ECX`) and pushes
// the registers; cl 8804 tests the pointer against itself, stores the zero
// words as immediates and pushes every constant as an immediate, which
// also drops the EBP save. The same materialised-constant shape appears at
// every retail NearByLocation call site (0x4FBF60, 0x41A2C0) and is
// recorded as a suspected 8447-vs-8804 difference. Tried: close-to cell
// declared at the top (kept), after the cell, after the zone lookup; as a
// two-argument constructor temporary and as an inline zero helper in the
// argument list; the by-value NearByLocation wrapper (homes the bool
// argument in a byte slot and reloads it as a dword); bool member passed
// with and without `!= 0`.
Cell_00703590 Obj_00703590::NearbyLocation(Obj_00703590* object)
{
    int speed = (this->*Vptr->GetTechnoType)()->SpeedType;
    if (speed == 4) {
        speed = 1;
    }
    Cell_00703590 closeTo;
    closeTo.X = 0;
    closeTo.Y = 0;

    Cell_00703590 cell;
    Coord_00703590 buf;
    if (object != 0) {
        cell = CoordToCell_00703590((object->*object->Vptr->GetCoords)(&buf));
    } else {
        cell = CoordToCell_00703590((this->*Vptr->GetCoords)(&buf));
    }

    int zone = (this->*Vptr->GetTechnoType)()->MovementZone;
    int zoneType;
    if (zone != -1) {
        zoneType = MapInstance_00703590.GetMovementZoneType(cell, zone, OnBridge);
    } else {
        zoneType = -1;
    }

    Cell_00703590 out;
    return *MapInstance_00703590.NearByLocation(&out, cell, speed, zoneType, zone,
                                                OnBridge, 1, 1, false, false,
                                                false, true, closeTo, false, false);
}

// FUNCTION: GAMEMD 0x7036C0
// Begin decloaking from the cloaked or cloaking states: enter state 3, restart
// the cloak progress stage from the rules' step count at the type's cloaking
// speed, and (unless silent) play the rules sound at this location.
void TechnoClass::vf_279(bool silent)
{
    if (CloakState == 2 || CloakState == 1) {
        CloakState = 3;
        CloakProgress.Value = ((RulesView_DF4*)RulesInstance)->unknown_628 - 1;
        CloakProgress.SetRate(vf_33()->CloakingSpeed);
        CloakProgress.Step = -1;
        if (!silent) {
            CoordStruct where = Location;
            FUN_007509E0(((RulesView_DF4*)RulesInstance)->unknown_6A0, where, 0);
        }
    }
}

// FUNCTION: GAMEMD 0x703770
// Begin cloaking from the uncloaked or fully-decloaking states: run slot 55 with
// false, enter state 1, restart the cloak progress stage from zero at the
// type's cloaking speed counting up, and (unless silent) play the rules sound
// at this location. Then, if this object is selected and not the local
// player's, run slot 84.
void TechnoClass::vf_280(bool silent)
{
    if (CloakState == 0 || CloakState == 3) {
        vf_55(false);
        CloakState = 1;
        CloakProgress.Value = 0;
        CloakProgress.SetRate(vf_33()->CloakingSpeed);
        CloakProgress.Step = 1;
        if (!silent) {
            CoordStruct where = Location;
            FUN_007509E0(((RulesView_DF4*)RulesInstance)->unknown_6A0, where, 0);
        }
        if (Owner != DAT_00A83D4C && IsSelected) {
            vf_84();
        }
    }
}

// FUNCTION: GAMEMD 0x703850
// Calls other functions. Vtable slot 63 of TechnoClass (RTTI) and 5 derived vtable(s).
void Obj_00703850::FUN_00703850()
{
    vf_279(0);
}

// The cell one step from `here` at a facing.
static __inline CellClass* step_cell_00703B10(const CellStruct& here, int facing)
{
    CellStruct c = here + DAT_0089F688[facing];
    return DAT_0087F7E8.FUN_005657A0(&c);
}

// FUNCTION: GAMEMD 0x703B10
// Step test on the four cells at facing steps 0, 2, 4, 6 around this object's cell: flag 0x100 / 0x800 tests.
bool TechnoClass::FUN_00703B10()
{
    CellStruct here = vf_110();
    CellClass* cell = DAT_0087F7E8.FUN_005657A0(&here);
    if (!cell || OnBridge) {
        return false;
    }
    CellClass* cell2 = step_cell_00703B10(here, 4);
    CellClass* cell0 = step_cell_00703B10(here, 0);
    CellClass* cell1 = step_cell_00703B10(here, 2);
    CellClass* cell3 = step_cell_00703B10(here, 6);
    if ((cell->Flags & 0x100)
        || (cell2 && (cell2->Flags & 0x100) && (cell2->Flags & 0x800))
        || (cell3 && (cell3->Flags & 0x100) && !(cell3->Flags & 0x800))
        || (cell1 && (cell1->Flags & 0x100) && !(cell1->Flags & 0x800))
        || (cell0 && (cell0->Flags & 0x100) && (cell0->Flags & 0x800))) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x703CC0
// Step test on the four cells at facing steps 0, 2, 4, 6 around this object's cell: flag 0x400 / 0x800 tests.
bool TechnoClass::FUN_00703CC0()
{
    CellStruct here = vf_110();
    CellClass* cell = DAT_0087F7E8.FUN_005657A0(&here);
    if (!cell || OnBridge) {
        return false;
    }
    CellClass* cell2 = step_cell_00703B10(here, 4);
    CellClass* cell0 = step_cell_00703B10(here, 0);
    CellClass* cell1 = step_cell_00703B10(here, 2);
    CellClass* cell3 = step_cell_00703B10(here, 6);
    if ((cell->Flags & 0x400)
        || (cell2 && (cell2->Flags & 0x400) && (cell2->Flags & 0x800))
        || (cell3 && (cell3->Flags & 0x400) && !(cell3->Flags & 0x800))
        || (cell1 && (cell1->Flags & 0x400) && !(cell1->Flags & 0x800))
        || (cell0 && (cell0->Flags & 0x400) && (cell0->Flags & 0x800))) {
        return true;
    }
    return false;
}

// The tile index lies 6..15 above the bridge tile base (and is not one of the two
// "no tile" markers).
static __inline CellClass* step_cell_00703E70(const CellStruct& here, int facing)
{
    CellStruct c = DAT_0089F688[facing] + here;
    return DAT_0087F7E8.FUN_005657A0(&c);
}

static __inline bool in_bridge_set_00703E70(int tile, int base)
{
    if (tile != 0xFFFF && tile != 0xFF) {
        int d = tile - base + 1;
        if (d >= 7 && d <= 16) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x703E70
// Counts bridge-tile cells among three of the cells around this object's cell, when the cell is
// valid and one of the two step tests (0x703B10, 0x703CC0) holds.
int TechnoClass::FUN_00703E70()
{
    CellStruct here = vf_110();
    int count = 0;
    if (DAT_0087F7E8.FUN_005657A0(&here)) {
        if (FUN_00703B10() || FUN_00703CC0()) {
            CellClass* a = step_cell_00703E70(here, 4);
            CellClass* b = step_cell_00703E70(here, 2);
            CellClass* c = step_cell_00703E70(here, 3);
            if (a && b && c) {
                int base = GgBridgeTileBase;
                if (in_bridge_set_00703E70(a->IsoTileTypeIndex, base)) {
                    count = 1;
                }
                if (in_bridge_set_00703E70(b->IsoTileTypeIndex, base)) {
                    count = 1;
                }
                if (in_bridge_set_00703E70(c->IsoTileTypeIndex, base)) {
                    count++;
                }
            }
        }
    }
    return count;
}

// FUNCTION: GAMEMD 0x704240
// Height-step probe toward facing step 3: 2 when the neighbouring cell stands at least 4 levels
// above this object's cell, 1 when the cell beyond it does (and the neighbour exists), else 0.
int TechnoClass::FUN_00704240()
{
    int result = 0;
    CellStruct here = vf_110();
    CellClass* cell = DAT_0087F7E8.FUN_005657A0(&here);
    if (!OnBridge) {
        CellStruct next = vf_110() + DAT_0089F688[3];
        CellClass* nextCell = DAT_0087F7E8.FUN_005657A0(&next);
        if (nextCell) {
            if (nextCell->Level - cell->Level >= 4) {
                result = 2;
            }
            CellStruct coords = nextCell->MapCoords;
            CellStruct beyond = coords + DAT_0089F688[3];
            CellClass* beyondCell = DAT_0087F7E8.FUN_005657A0(&beyond);
            if (beyondCell) {
                if (beyondCell->Level - cell->Level >= 4) {
                    return 1;
                }
                return result;
            }
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x705CA0
CoordStruct TechnoClass::vf_267()
{
    if (this->vf_97() == 1 && this->Target != 0) {
        return this->Target->vf_22();
    }
    return this->Location;
}

// FUNCTION: GAMEMD 0x00705D10
//
// Store the argument into the member at +0x514.
void Setter_00487C70::FUN_00705D10(int value)
{
    *(int*)(Bytes + 0x514) = value;
}

// FUNCTION: GAMEMD 0x00705D20
int FUN_00705D20(Obj_00705D20* self)
{
    return self->unknown_514;
}

// FUNCTION: GAMEMD 0x705D30
// Branching.
unsigned char Obj_00705D30::FUN_00705D30()
{
    if (unknown_514 == 0)
    {
        return 0;
    }
    return (unknown_514->FUN_00636DC0() > 0) ? true : false;
}

// FUNCTION: GAMEMD 0x705D50
// Calls other functions. Vtable slot 268 of TechnoClass (RTTI) and 4 derived vtable(s).
bool Obj_00705D50::FUN_00705D50()
{
    return (vf_118() == 0) ? true : false;
}

// FUNCTION: GAMEMD 0x705D60
void FUN_00705D60(void* self)
{
    FUN_006385C0(self);
}

// FUNCTION: GAMEMD 0x705D70
//
// Which house-colour remap table draws this object. A type with its own
// Palette= list supplies one ColorScheme per house, indexed by the owner's
// colour-scheme index. Otherwise the global ColorScheme array is used — for the
// owner, unless the local player cannot see through a disguise and the object
// is disguised as some house, in which case that house's colours are drawn.
// The disguise house is fetched twice rather than cached, as retail does.
LightConvertClass* Techno_00705D70::GetDrawer()
{
    TechnoType_00705D70* type = (this->*(*(Vtbl_00705D70**)this)->At_084)();
    int index = this->Owner->ColorSchemeIndex;

    if (type->Palette != 0) {
        return (*type->Palette)[index]->LightConvert;
    }

    if (!(this->*(*(Vtbl_00705D70**)this)->At_440)(DAT_00A83D4C)) {
        if ((this->*(*(Vtbl_00705D70**)this)->At_0D0)(1) != 0) {
            return DAT_00B054D0[(this->*(*(Vtbl_00705D70**)this)->At_0D0)(1)->ColorSchemeIndex]->LightConvert;
        }
    }

    return DAT_00B054D0[index]->LightConvert;
}

// FUNCTION: GAMEMD 0x707750
//
// Derive the +0x3CA angle word from the tactical view word, the first
// argument and the second argument's word, then pull it back by 8 or 12
// depending on which eighth of the circle the primary facing points into.
void TechnoClass::FUN_00707750(int a, DirStruct d)
{
    short t = TacticalInstance_r21_4->ViewWord;
    t += a;
    this->unknown_3CA = t + d.Raw - 10;
    DirStruct* cur = this->PrimaryFacing.FUN_004C93D0(&d);
    int octant = ((*(unsigned int*)cur >> 12) + 1) >> 1 & 7;
    if (octant == 0 || octant == 6) {
        this->unknown_3CA -= 8;
    } else if (octant == 7) {
        this->unknown_3CA -= 12;
    }
}

// FUNCTION: GAMEMD 0x707CB0  TechnoClass::KillPassengers (__thiscall, ret 0x4)
// Empty a transport by killing everything inside it. Each passenger is first
// released from its team, then unlinked, then recursively emptied itself — a
// transport carrying a transport unwinds all the way down — before being
// destroyed through its own two virtuals.
//
// The empty check is hoisted out and the body is a do/while: retail tests
// FirstPassenger (+0x118, the list head) once up front and again at the bottom
// of the loop, with the loop head at the GetFirstPassenger call rather than at
// the test.
void TechnoClass::KillPassengers(TechnoClass* source)
{
    if (Passengers.FirstPassenger == 0)
        return;

    do
    {
        FootClass* first = Passengers.GetFirstPassenger();
        if (first->Team != 0)
            first->Team->LiberateMember(first, -1, 0);

        FootClass* passenger = Passengers.RemoveFirstPassenger();
        if (passenger != 0)
        {
            // Retail passes the passenger itself here, not `source`
            // (`PUSH ESI; MOV ECX,ESI; CALL 0x707CB0`); only the outer
            // virtual at +0xE0 receives the original killer.
            passenger->KillPassengers(passenger);
            passenger->vf_56(source);
            passenger->vf_62();
        }
    }
    while (Passengers.FirstPassenger != 0);
}

// FUNCTION: GAMEMD 0x707D20
//
// The crew value for a crewed object: picked by the owner's side index,
// replaced by the default when the owner's type has no side, and also
// replaced by the default when the object is armed and a 0..99 roll lands
// below 15. Zero for an uncrewed type.
int TechnoClass::FUN_00707D20()
{
    if (!vf_33()->Crewed) {
        return 0;
    }
    HouseClass* house = this->Owner;
    int crew;
    if (house->SideIndex == 0) {
        crew = RulesInstance_00707D20->SideCrew0;
    } else if (house->SideIndex == 1) {
        crew = RulesInstance_00707D20->SideCrew1;
    } else if (house->SideIndex == 2) {
        crew = RulesInstance_00707D20->SideCrew2;
    } else {
        crew = RulesInstance_00707D20->DefaultCrew;
    }
    if (house->Type->SideIndex != -1) {
        if (IsArmed()) {
            if (ScenarioInstance_00707D20->Random.RandomRanged(0, 99) < 15) {
                crew = RulesInstance_00707D20->DefaultCrew;
            }
        }
    } else {
        crew = RulesInstance_00707D20->DefaultCrew;
    }
    return crew;
}

// FUNCTION: GAMEMD 0x707DD0
// The weight of this object: its type's points, its own extra, and its passengers' when the
// house's difficulty or intelligence level counts them.
int TechnoView_r16::vf_96()
{
    int total = 0;
    if ((DAT_008871E0_r16->Difficulty[Owner->AIDifficulty].Flag != 0 ||
         Owner->IQLevel2 >= DAT_008871E0_r16->unknown_1450) &&
        Passengers.FirstPassenger != 0) {
        for (ObjectClass* passenger = reinterpret_cast<ObjectClass*>(Passengers.GetFirstPassenger());
             passenger != 0; passenger = reinterpret_cast<ObjectClass*>(passenger->NextObject)) {
            total += passenger->vf_96();
        }
    }
    return vf_33()->Points + vf_176() + total;
}

// FUNCTION: GAMEMD 0x707E60
// Range for a guard/scan mode: -1 stays -1; mode 0 is the type's GuardRange
// unless slot 204 is true; other modes use twice the type's GuardRange (or, if
// that is zero, twice the larger of slot 90 for modes 0 and 1), clamped to
// 0x1000 (and to at least 0x700 for mode 2, at least 0 otherwise).
int TechnoClass::vf_199(int mode)
{
    if (mode == -1) {
        return -1;
    }
    if (mode == 0) {
        bool blocked = vf_204();
        if (vf_33()->GuardRange && !blocked) {
            return vf_33()->GuardRange;
        }
        return 0;
    }
    int range = vf_33()->GuardRange;
    if (!range) {
        range = vf_90(0) > vf_90(1) ? vf_90(0) : vf_90(1);
    }
    range += range;
    if (mode == 2) {
        if (range < 0x700) {
            return 0x700;
        }
        if (range > 0x1000) {
            return 0x1000;
        }
    } else {
        if (range < 0) {
            return 0;
        }
        if (range > 0x1000) {
            range = 0x1000;
        }
    }
    return range;
}

// FUNCTION: GAMEMD 0x708B30
int TechnoClass::vf_35()
{
    return vf_33()->vf_28();
}

// FUNCTION: GAMEMD 0x708B40
// The threat value of this object: for an RTTI-6 object with a positive slot
// 258 value, that value times the rules multiplier at +0xDF4; otherwise the
// type's ThreatPosed (the bunker-linked partner's when there is one). Zero when
// there is no type.
int TechnoClass::vf_176()
{
    TechnoTypeClass* type = vf_33();
    if (type) {
        if (vf_11() == 6) {
            if (vf_258() > 0) {
                int multiplier = ((RulesView_DF4*)RulesInstance)->unknown_DF4;
                return vf_258() * multiplier;
            }
            if (BunkerLinkedItem) {
                return BunkerLinkedItem->vf_33()->ThreatPosed;
            }
        }
        return type->ThreatPosed;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x708BC0
// Fraction of the type's storage capacity currently held (0.0 when the type
// has no storage).
double TechnoClass::vf_173()
{
    if (vf_33()->Storage) {
        double held = Tiberium.GetTotalAmount();
        return held / vf_33()->Storage;
    }
    return DAT_007E2800;
}

// FUNCTION: GAMEMD 0x708C10
// Store the global at 0xB0EA50 through the second argument and return 0.
int TechnoClass::vf_193(int a1, CellStruct* out)
{
    *out = DAT_00B0EA50;
    return 0;
}

// FUNCTION: GAMEMD 0x708C30
// Number of filled pips: the held amount for the type's pip scale (ammo,
// stored tiberium, passengers or mind-controlled units) as a fraction of its
// maximum, scaled by the type's slot 29 value and rounded; at least 1 when
// anything is held.
int TechnoClass::vf_174()
{
    double value;
    double limit;
    switch (vf_33()->PipScale) {
    case 1:
        value = Ammo;
        limit = vf_33()->vf_29();
        break;
    case 5:
        if (!CaptureManager) {
            return 0;
        }
        value = ((CaptureManagerClass*)CaptureManager)->GetControlledCount();
        limit = vf_33()->vf_29();
        break;
    case 3:
        value = Passengers.NumPassengers;
        limit = vf_33()->vf_29();
        break;
    case 2:
        value = Tiberium.GetTotalAmount();
        limit = vf_33()->Storage;
        break;
    default:
        return 0;
    }
    int pips = (int)(value / limit * vf_33()->vf_29() + 0.5);
    if (pips == 0 && value > 0.0) {
        pips = 1;
    }
    return pips;
}

// FUNCTION: GAMEMD 0x708D70
DirStruct TechnoClass::vf_194()
{
    return this->vf_170();
}

// FUNCTION: GAMEMD 0x708D90
void TechnoClass::vf_213(int a1)
{
    if (DAT_00822CF2 && a1 != -1 && this->Owner->IsControlledByCurrentPlayer()) {
        this->QueuedVoiceIndex = a1;
    }
}

// FUNCTION: GAMEMD 0x708DC0  (__thiscall)
// Voice played when this object captures something. Falls back to the
// enter-transport voice (slot +0x358) when the type declares no capture voice.
//
// The GetTechnoType dispatch appears twice in retail and that is literal: the
// guard reads the index and the queued call reads it again. Caching it in a
// local collapses the second dispatch and loses six instructions.
void TechnoView_00708DC0::VoiceCapture()
{
    if ((this->*this->Vfptr->At_84)()->VoiceCapture != -1) {
        (this->*this->Vfptr->At_354)((this->*this->Vfptr->At_84)()->VoiceCapture);
    } else {
        (this->*this->Vfptr->At_358)();
    }
}

// FUNCTION: GAMEMD 0x708EB0
// Play a randomly chosen select voice through slot 213: from the type's
// enslaved list when this has a slave owner, else its deactivated list when
// deactivated, else its normal select list. Does nothing for an empty list.
void TechnoClass::vf_216()
{
    if (SlaveOwner) {
        TypeList<int>* voices = &vf_33()->VoiceSelectEnslaved;
        if (voices->Count) {
            unsigned int r = DAT_00886B88.Random();
            TypeList<int>& list = vf_33()->VoiceSelectEnslaved;
            vf_213(list.Items[r % list.Count]);
        }
    } else if (Deactivated) {
        TypeList<int>* voices = &vf_33()->VoiceSelectDeactivated;
        if (voices->Count) {
            unsigned int r = DAT_00886B88.Random();
            TypeList<int>& list = vf_33()->VoiceSelectDeactivated;
            vf_213(list.Items[r % list.Count]);
        }
    } else {
        TypeList<int>* voices = &vf_33()->VoiceSelect;
        if (voices->Count) {
            unsigned int r = DAT_00886B88.Random();
            TypeList<int>& list = vf_33()->VoiceSelect;
            vf_213(list.Items[r % list.Count]);
        }
    }
}

// FUNCTION: GAMEMD 0x708FC0
// Play a randomly chosen entry of the type's VoiceMove list through slot 213;
// does nothing when the list is empty.
void TechnoClass::vf_218()
{
    TypeList<int>* voices = &vf_33()->VoiceMove;
    if (voices->Count) {
        unsigned int r = DAT_00886B88.Random();
        TypeList<int>& list = vf_33()->VoiceMove;
        vf_213(list.Items[r % list.Count]);
    }
}

// FUNCTION: GAMEMD 0x709020  (__thiscall)
// Voice played when this object enters a transport or a structure. Falls back
// to the move voice (slot +0x368).
void TechnoView_00708DC0::VoiceEnter()
{
    if ((this->*this->Vfptr->At_84)()->VoiceEnter != -1) {
        (this->*this->Vfptr->At_354)((this->*this->Vfptr->At_84)()->VoiceEnter);
    } else {
        (this->*this->Vfptr->At_368)();
    }
}

// FUNCTION: GAMEMD 0x709060  (__thiscall)
// Voice played when a harvester is sent to gather. Falls back to the move
// voice (slot +0x368), which is why an ore truck without a harvest voice still
// acknowledges the order.
void TechnoView_00708DC0::VoiceHarvest()
{
    if ((this->*this->Vfptr->At_84)()->VoiceHarvest != -1) {
        (this->*this->Vfptr->At_354)((this->*this->Vfptr->At_84)()->VoiceHarvest);
    } else {
        (this->*this->Vfptr->At_368)();
    }
}

// FUNCTION: GAMEMD 0x7090A0
// Voice the attack order for a target: the repair line when the weapon heals
// and the object is of the repair kind, else the primary or secondary weapon
// line (elite variants for an elite object); with none set, a random pick from
// the type's attack list.
void TechnoClass::vf_220(AbstractClass* target)
{
    int weapon = vf_185(target);
    int voice;
    WeaponStruct* chosen = vf_254(weapon);
    if (chosen->WeaponType != 0 && chosen->WeaponType->Damage < 0 && FUN_005F3E50(DAT_0084314C)) {
        voice = Rules->VoiceIFVRepair;
    } else if (Veterancy.FUN_00750010()) {
        if (weapon == 0) {
            voice = vf_33()->VoicePrimaryEliteWeaponAttack;
        } else {
            voice = vf_33()->VoiceSecondaryEliteWeaponAttack;
        }
    } else {
        if (weapon == 0) {
            voice = vf_33()->VoicePrimaryWeaponAttack;
        } else {
            voice = vf_33()->VoiceSecondaryWeaponAttack;
        }
    }
    TypeList<int>* attack = &vf_33()->VoiceAttack;
    if (attack->Count == 0) {
        if (voice != -1) {
            vf_213(voice);
        }
    } else {
        if (voice != -1) {
            vf_213(voice);
            return;
        }
        unsigned int pick = DAT_00886B88.Random();
        TypeList<int>& list = vf_33()->VoiceAttack;
        vf_213(list.Items[pick % list.Count]);
    }
}

// FUNCTION: GAMEMD 0x7091D0
//
// Whether this object may pick up targets of its own accord. A chain of
// rejections: while warping something out, while enslaved, when the type
// forbids it, when an occupiable building has no occupants, when a human-owned
// object of the kind that defers to the player, when captured beyond control;
// then only an armed object says yes.
//
// Written as one &&-chained precondition with the ||-chained building exemption
// nested inside and a single trailing `return false`: that is what gives retail
// its one shared `XOR AL,AL` tail. A ladder of `if (...) return false;` gives
// every rejection its own pop/xor/ret block (7.3%). The captured flag is a
// named bool (BL) computed before the ownership test.
bool Obj_007091D0::CanPassiveAcquireTargets()
{
    if (!(this->*this->Vtbl->At_1DC)()
        && this->SlaveOwner == 0
        && (this->*this->Vtbl->GetTechnoType)()->At_D99 != 0
        && ((this->*this->Vtbl->WhatAmI)() != 6
            || this->BuildingType->At_157B == 0
            || (this->*this->Vtbl->At_408)() != 0))
    {
        bool captured = this->CaptureManager != 0
                        && this->CaptureManager->CannotControlAnyMore();

        if ((!(this->*this->Vtbl->At_330)() || !this->Owner->IsControlledByHuman())
            && !captured
            && (this->*this->Vtbl->At_2AC)())
        {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x709460
// Branching.
int __stdcall FUN_00709460(int a1)
{
    return a1 != 5 && a1 != 6 && a1 != 8;
}

// FUNCTION: GAMEMD 0x709480
// If this object may retarget, ask the virtual that picks a target from where
// it stands; report whether it ended up with a different target, and flag the
// shoot-at-once state when it did.
bool TechnoClass::FUN_00709480()
{
    bool changed = false;
    if (FUN_00709290()) {
        AbstractClass* previous = Target;
        unknown_4FC = CurrentFrame;
        changed = vf_231(vf_18(), 1);
        if (changed && Target != previous) {
            ShouldLoseTargetNow = 1;
        }
    }
    return changed;
}

// FUNCTION: GAMEMD 0x7094E0
// Branching.
int Obj_007094E0::FUN_007094E0()
{
    return unknown_AC == 2 || unknown_AC == 0xA || unknown_AC == 5;
}

// FUNCTION: GAMEMD 0x709500
int TechnoClass::FUN_00709500()
{
    int mission = this->CurrentMission;
    if (mission == 0 || mission == 7 || mission == 13 || mission == 14 || mission == 16
        || mission == 18 || mission == 19 || mission == 20 || mission == 22 || mission == 23
        || mission == 28 || mission == 24) {
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x709800
// Branching.
int __stdcall FUN_00709800(int a1)
{
    return a1 != 5 && a1 != 6;
}

// FUNCTION: GAMEMD 0x7099D0
// Returns zero; pops its stack arguments. Vtable slot 64 of TechnoClass (RTTI) and 3 derived vtable(s).
int Obj_007099D0::FUN_007099D0(int a1, int a2) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x7099E0  (__thiscall)
// Has the idle-action countdown run out? CDTimerClass::GetTimeLeft is
// inlined (TimeLeft read once, a return per arm) and the `== 0` test is
// duplicated into each return, giving retail's two `setz cl; mov al,cl` tails.
// The exit is `MOV AL,CL`, so the return type is bool, not int.
bool TechnoClass::IsTimeForIdleAction()
{
    return this->IdleActionTimer.GetTimeLeft() == 0;
}

// FUNCTION: GAMEMD 0x709A20
// Empty function that pops its stack arguments. Vtable slot 287 of TechnoClass (RTTI) and 1 derived vtable(s).
void Obj_00709A20::FUN_00709A20(int a1)
{
}

// FUNCTION: GAMEMD 0x709A30  (__thiscall)
// The TechnoClass base of the destination virtual does nothing: a plain
// `RET 8`, i.e. two stack arguments accepted and discarded. Only the movement
// leaves override it.
void TechnoClass::SetDestination(AbstractClass* dest, bool now)
{
}

// FUNCTION: GAMEMD 0x709A40  (__thiscall)
// The TechnoClass base of "settle into idle". It releases any Chrono-legionnaire
// erase currently pointed at a target, then — only when the object is not
// already busy (slot +0x4D0) and is eligible (slot +0x430) — advances the
// planning-token walk. It always reports false; the movement leaves override it
// to say otherwise.
//
// Both arguments are unused, which is why they never appear: the `RET 8` alone
// records them.
bool TechnoClass::EnterIdleMode(bool initial, bool unused)
{
    TemporalClass* temporal = this->TemporalImUsing;

    if (temporal != 0 && temporal->Target != 0) {
        temporal->FUN_0071ABC0();
    }
    if (!vf_308()) {
        if (vf_268()) {
            this->TryNextPlanningTokenNode();
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x70AD50
CellStruct TechnoClass::vf_191(AbstractClass* a1, int a2)
{
    return CoordToCell(this->vf_42(a1));
}

// FUNCTION: GAMEMD 0x70ADA0
// Forward the owner house to the type's slot 46 with a zero second argument.
void TechnoClass::vf_175()
{
    vf_33()->vf_46(Owner, 0);
}

// FUNCTION: GAMEMD 0x70ADC0
// Reveal the map around this object by its sight: the type's sight scaled by
// the sight bonus gained from the height it stands at, and again by the rank
// bonus. Not for an object held off the playfield, nor for a passive house
// outside the campaign modes.
void TechnoClass::vf_72(int a1, int a2)
{
    if (!IsInPlayfield) {
        return;
    }
    if (Owner->Type->MultiplayPassive && Session_00A8B238.GameMode != 0) {
        return;
    }
    CoordStruct here = Location;
    int level = here.Z / Rules->LeptonsPerSightIncrease * 10;
    if (level > SightIncrease) {
        a1 = 0;
    }
    SightIncrease = (char)level;
    int sight = (int)(vf_33()->Sight * (SightIncrease * DAT_007E3808 + DAT_007E1718));
    if (Veterancy.FUN_0074FF90() || Veterancy.FUN_00750010()) {
        TechnoTypeClass* type = vf_33();
        if ((Veterancy.FUN_0074FF90() && type->VeteranAbilities._raw[5])
            || (Veterancy.FUN_00750010() && (type->VeteranAbilities._raw[5] || type->EliteAbilities._raw[5]))) {
            if (Rules->VeteranSight != GG_ZERO) {
                sight = (int)(sight * Rules->VeteranSight);
            }
        }
    }
    if (sight != 0) {
        CoordStruct where = Location;
        DAT_0087F7E8.FUN_005673A0(where, sight, Owner, a1, a2, 0, 1, 1);
    }
}

// FUNCTION: GAMEMD 0x70BE50
//
// Frame-phase value: the interface sub-object's slot-4 answer plus the
// truncated +0x24C float, taken modulo 400.
int TechnoClass::FUN_0070BE50()
{
    SubIface_r14* sub = (SubIface_r14*)((char*)this + 4);
    int a = sub->Vtbl->At_10(sub);
    return ((int)this->WarpFactor + a) % 400;
}

// FUNCTION: GAMEMD 0x70BE80
// Periodic self-heal gate: true on the frames that divide evenly by the rules'
// heal interval when the object is damaged (alive and below full strength),
// provided its type self-heals or its veteran/elite rank grants it.
bool TechnoClass::vf_165()
{
    if (!vf_33()->SelfHealing) {
        bool allowed = false;
        if (Veterancy.FUN_0074FF90() || Veterancy.FUN_00750010()) {
            TechnoTypeClass* type = vf_33();
            if (Veterancy.FUN_0074FF90() && type->VeteranAbilities._raw[9]) {
                allowed = true;
            } else if (Veterancy.FUN_00750010() &&
                       (type->VeteranAbilities._raw[9] || type->EliteAbilities._raw[9])) {
                allowed = true;
            }
        }
        if (!allowed) {
            return false;
        }
    }
    double base = ((RulesView_DF4*)RulesInstance)->unknown_16E0;
    int interval = (int)(base * DAT_007E27F8);
    if (CurrentFrame % interval != 0) {
        return false;
    }
    int health = Health;
    if (health == vf_33()->Strength) {
        return false;
    }
    bool damaged = health != 0;
    return damaged;
}

// FUNCTION: GAMEMD 0x70C250
// Forwards its three arguments and reports zero.
int __stdcall FUN_0070C250(int a, int b, int c)
{
    FUN_0065AC40(a, b, c);
    return 0;
}

// FUNCTION: GAMEMD 0x70C5A0  (__thiscall)
// Can this object cloak? The flag is a byte, and the `TEST AL,AL; SETNZ AL`
// normalisation is the char-to-bool conversion — a member already declared
// bool would return with a bare `MOV AL,[..]; RET`, which is exactly what the
// neighbouring accessor at 0x70C5B0 does.
//
// LEVER, measured over nine spellings in one probe compile: `return C != 0;`,
// the same through a named `unsigned char` local, a `char` member, an `int`
// member, and `char`/`int` return types ALL emit `MOV DL,[..]; XOR EAX,EAX;
// TEST DL,DL; SETNE AL` — five instructions against retail's four, because cl
// takes a fresh register and zeroes EAX. Only the two branching forms —
// `C ? true : false` and the explicit `if` below — reuse AL and reach retail's
// exact four. This is the concrete case behind the "never write
// `return a == b;`" rule: the bare comparison costs the zeroing instruction.
bool TechnoClass::IsCloakable()
{
    if (this->Cloakable) {
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70C5B0
// Member getter (byte). Vtable slot 117 of TechnoClass (RTTI) and 5 derived vtable(s).
unsigned char Obj_0070C5B0::FUN_0070C5B0() const
{
    return unknown_270;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70C5C0
// Member getter (byte). Vtable slot 118 of TechnoClass (RTTI) and 5 derived vtable(s).
unsigned char Obj_0070C5C0::FUN_0070C5C0() const
{
    return unknown_271;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70C5D0
// Branching. Vtable slot 119 of TechnoClass (RTTI) and 5 derived vtable(s).
bool Obj_0070C5D0::FUN_0070C5D0()
{
    if (unknown_274 == 0 || unknown_274->unknown_28 == 0)
    {
        return false;
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70C5F0
// Branching. Vtable slot 120 of TechnoClass (RTTI) and 5 derived vtable(s).
bool Obj_0070C5F0::FUN_0070C5F0()
{
    if (unknown_270 != 0 || unknown_271 != 0)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x70C610  (__thiscall)
// Store the supplied archive target pointer unconditionally.
//   MOV EAX,[ESP+4]; MOV [ECX+0x218],EAX; RET 4
void TechnoClass::SetArchiveTarget(AbstractClass* pTarget)
{
    this->ArchiveTarget = pTarget;
}

// FUNCTION: GAMEMD 0x70C620
// True when the cell under this object's location is not the cell that
// slot 110 reports.
bool TechnoClass::vf_172()
{
    CoordStruct where = Location;
    CellStruct here = DAT_00887324->FUN_006D6410(&where);
    return CellsDiffer(here, vf_110());
}

// FUNCTION: GAMEMD 0x70CC90
void TechnoClass::vf_293()
{
    MapClass_Instance.FUN_00655560(this, this->RadarPosition);
    this->IsRadarTracked = true;
}

// FUNCTION: GAMEMD 0x70CCC0
void TechnoClass::vf_294()
{
    MapClass_Instance.FUN_00655740(this, this->RadarPosition);
    this->IsRadarTracked = false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70CCF0
// Calls other functions. Vtable slot 295 of TechnoClass (RTTI) and 4 derived vtable(s).
void FUN_0070CCF0(int a1, int a2)
{
    FUN_006562D0(&DAT_0087F7E8, a2, a1 + 0x208);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70D0D0
//
// Does this object currently enjoy the given veteran/elite ability? Nothing
// below veteran rank has any. A veteran has the ability when its type grants it
// at the veteran tier; an elite has it when the type grants it at either tier
// (elite is a superset). The type is fetched through the GetTechnoType virtual
// only once a rank test has passed.
bool Techno_0070D0D0::HasAbility(int ability)
{
    VeterancyStruct* vet = &this->Veterancy;

    if (FUN_0074FF90(vet) || FUN_00750010(vet)) {
        TechnoType_0070D0D0* type = (this->*(*(Vtbl_0070D0D0**)this)->At_084)();

        if (FUN_0074FF90(vet) && type->VeteranAbilities[ability]) {
            return true;
        }
        if (FUN_00750010(vet)
            && (type->VeteranAbilities[ability] || type->EliteAbilities[ability])) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x70D150
void FUN_0070D150()
{
    CDTimerClass timer;
    timer.StartTime = CurrentFrame;
    timer.TimeLeft = 25;
    DAT_00B0EA80 = timer;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0070D180
void FUN_0070D180(char value)
{
    DAT_00843108 = value;
}

// FUNCTION: GAMEMD 0x70D190
int TechnoClass::vf_281(int a1)
{
    if ((this->DurationRemaining & 2) == 2) {
        return (a1 > 1500) ? 500 : 2000;
    }
    return a1;
}

// FUNCTION: GAMEMD 0x70D420
bool TechnoClass::vf_202()
{
    if (CurrentPlayer != 0) {
        CellClass* cell = MapClass_Instance.GetTargetCell(this->vf_18());
        return cell->FUN_004870D0(CurrentPlayer->ArrayIndex);
    }
    return false;
}

// FUNCTION: GAMEMD 0x70D460
bool TechnoClass::vf_203(HouseClass* a1)
{
    if (a1 != 0) {
        CellClass* cell = MapClass_Instance.GetTargetCell(this->vf_18());
        return cell->FUN_004870D0(a1->ArrayIndex);
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70D4A0  AbstractClass::BecomeUntargetable
//
// Nothing may keep pointing at this object. Every techno targeting it drops
// the target (an infantry mid-mission 0x19 also loses its sub-state), unless
// this is a live techno whose +0x294 link is owned by that techno. Then the
// two references in the second array are cleared. The null-safe techno view
// is an if/else with the null case first (retail's fall-through), then the
// branchless flag mask; `self = 0; if (this) ...` puts the XOR first (1.2%).
void Abstract_0070D4A0::BecomeUntargetable()
{
    Techno_0070D4A0* self;
    if (this == 0)
        self = 0;
    else
        self = (AbstractFlags & 1) ? (Techno_0070D4A0*)this : 0;

    for (int i = DAT_00A8EC88 - 1; i >= 0; --i) {
        Techno_0070D4A0* techno = DAT_00A8EC7C[i];
        bool drop = true;
        if (self != 0 && techno->At_294 != 0 && techno->At_294->At_50 == this
            && self->Health > 0 && self->At_90 != 0)
            drop = false;
        if (techno->Target == this && drop) {
            (techno->*techno->Vptr->At_1F8)();
            if ((techno->*techno->Vptr->WhatAmI)() == 2 && techno->CurrentMission == 0x19) {
                techno->At_BC = 0;
                techno->At_6D2 = 0;
            }
            if (techno->Target == this)
                (techno->*techno->Vptr->At_3C8)(0);
        }
    }

    for (int j = DAT_008B40F8 - 1; j >= 0; --j) {
        Ref_0070D4A0* ref = DAT_008B40EC[j];
        if (ref->At_3C == this)
            ref->At_3C = 0;
        if (ref->At_40 == this)
            ref->At_40 = 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70D670
// Branching. Vtable slot 228 of TechnoClass (RTTI) and 4 derived vtable(s).
int Obj_0070D670::FUN_0070D670()
{
    int t1 = unknown_2FC;
    if (t1 > 0)
    {
        unknown_2FC = t1 - 1;
        return t1 - 1;
    }
    return t1;
}

// FUNCTION: GAMEMD 0x70D690
//
// Fire the object's death weapon at its own position. The weapon is the type's
// DeathWeapon, else the turret weapon, else the rules fallback; the damage is
// the weapon's damage scaled by the type's death-weapon modifier (half the
// type's strength for the fallback), plus the caller's extra. A bullet is
// created on this object, given the weapon, detonated at our coordinates and
// released. Returns the damage dealt, or zero when there was no weapon.
//
// The turret-weapon test binds one call result to a local (retail tests
// `EAX` and then `[EAX]` off a single `CALL [EDX+0x3F4]`), while the weapon
// itself is read through a second call; the death-weapon branch instead
// calls GetTechnoType three times. Phrasing the test as two calls scored
// 81.3%; binding the type or turret result for the damage line 21.1%.
int TechnoView_0070D690::FireDeathWeapon(int extraDamage)
{
    Weapon_0070D690* weapon;
    int damage;

    if ((this->*this->Vtbl->GetTechnoType)()->DeathWeapon != 0) {
        weapon = (this->*this->Vtbl->GetTechnoType)()->DeathWeapon;
        damage = (int)(weapon->Damage * (this->*this->Vtbl->GetTechnoType)()->DeathWeaponDamageModifier);
    } else {
        WeaponStruct_0070D690* turret = (this->*this->Vtbl->GetTurretWeapon)();
        if (turret != 0 && turret->WeaponType != 0) {
            weapon = (this->*this->Vtbl->GetTurretWeapon)()->WeaponType;
            damage = (int)(weapon->Damage * (this->*this->Vtbl->GetTechnoType)()->DeathWeaponDamageModifier);
        } else {
            weapon = RulesInstance_0070D690->At_FDC;
            damage = (int)((this->*this->Vtbl->GetTechnoType)()->Strength * 0.5);
        }
    }

    if (weapon == 0) {
        return 0;
    }

    damage += extraDamage;

    Bullet_0070D690* bullet = FUN_0046B050(weapon->Projectile, this, this, damage,
                                           weapon->Warhead, 0, weapon->Bright);
    if (bullet != 0) {
        bullet->FUN_0046B260(weapon);
        (bullet->*bullet->Vtbl->At_D4)();
        CoordStruct_0070D690 coord;
        bullet->Detonate((this->*this->Vtbl->GetCoords)(&coord));
        bullet->Vtbl->Release(bullet);
    }

    return damage;
}

// FUNCTION: GAMEMD 0x70D7A0
//
// When the health ratio exceeds the rules threshold, or slot 0x1C8 answers
// below -10, tell the linked object (if any) through its slot 0xF8.
void TechnoClass::FUN_0070D7A0()
{
    if (FUN_005F5C60() > RulesInstance_0070D7A0->Threshold
        || vf_114() < -10) {
        LinkedObj_r14* linked = (LinkedObj_r14*)this->DamageParticleSystem;
        if (linked != 0) {
            (linked->*linked->Vtbl->At_F8)();
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70D980
// Empty function. Vtable slot 184 of TechnoClass (RTTI) and 4 derived vtable(s).
void Obj_0070D980::FUN_0070D980()
{
}

// FUNCTION: GAMEMD 0x70DC50
bool TechnoClass::FUN_0070DC50()
{
    return this->vf_33()->HasTurretTooltips;
}

// FUNCTION: GAMEMD 0x70DC60
bool TechnoClass::FUN_0070DC60()
{
    return this->vf_33()->FUN_00717880();
}

// FUNCTION: GAMEMD 0x70DC70
// Pick the turret for a weapon number (0 when it is out of range); chargers keep theirs.
void TechnoClass::FUN_0070DC70(int mode)
{
    if (!vf_33()->IsChargeTurret) {
        if (mode >= 0 && mode < 18) {
            CurrentTurretNumber = vf_33()->FUN_007178B0(mode);
            CurrentWeaponNumber = mode;
        } else {
            CurrentTurretNumber = vf_33()->FUN_007178B0(0);
            CurrentWeaponNumber = 0;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70DCE0
// Returns a comparison result.
bool Obj_0070DCE0::FUN_0070DCE0() const
{
    return unknown_124 != -1;
}

// FUNCTION: GAMEMD 0x0070DCF0
int TechnoClass_00707000::GetCurrentTurret() const { return this->CurrentTurret; }

// FUNCTION: GAMEMD 0x0070DDC0
int TechnoClass_00707000::GetCaptureTarget() const { return this->CaptureTarget; }

// FUNCTION: GAMEMD 0x0070DDF0
int TechnoClass_00707000::GetAmmo() const { return this->Ammo; }

// FUNCTION: GAMEMD 0x70DD00
int TechnoClass::FUN_0070DD00()
{
    int changed = this->CurrentTurretNumber != this->unknown_int_128;
    this->unknown_int_128 = this->CurrentTurretNumber;
    return changed;
}

// FUNCTION: GAMEMD 0x70DD20
//
// The +0x138 value when the type's FUN_00717880 holds, else zero.
int TechnoClass::FUN_0070DD20()
{
    if (vf_33()->FUN_00717880()) {
        return this->CurrentWeaponNumber;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x70DD50
// The weapon-type byte at +0x150 of the weapon in slot 252, false when there is
// no weapon record or it names no type.
bool TechnoClass::vf_248()
{
    WeaponStruct* weapon = this->vf_252();
    if (weapon != 0 && weapon->WeaponType != 0) {
        return weapon->WeaponType->AreaFire;
    }
    return false;
}

// FUNCTION: GAMEMD 0x70DD70
int TechnoClass::vf_249()
{
    return !this->vf_33()->SprayAttack;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70DD90
// Returns a constant. Vtable slot 250 of TechnoClass (RTTI) and 5 derived vtable(s).
int Obj_0070DD90::FUN_0070DD90() const
{
    return 1;
}

// FUNCTION: GAMEMD 0x70DDA0
int TechnoClass::vf_251()
{
    return !this->vf_33()->SprayAttack;
}

// FUNCTION: GAMEMD 0x70DDD0  (__thiscall)
// Store idx only when non-negative (the JL guards out negatives).
//   MOV EAX,[ESP+4]; TEST EAX,EAX; JL ret; MOV [ECX+0x140],EAX; RET 4
void TechnoClass::SetCurrentWeaponStage(int idx)
{
    if (idx >= 0)
        this->CurrentGattlingStage = idx;
}

// FUNCTION: GAMEMD 0x70DE00  TechnoClass::SetGattlingValue (__thiscall, ret 0x4)
// Guarded setter: a negative value is ignored rather than clamped. The value is
// also the return, which retail gets for free — EAX still holds the argument.
//
// NOTE: the name is descriptive. YRpp carries this address only as
// `sub_70DE00(int State)`; the member it writes is the committed spine's
// GattlingValue @0x144, which is what the name follows.
int TechnoClass::SetGattlingValue(int value)
{
    if (value >= 0)
        GattlingValue = value;

    return value;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70DE20
// Updates one member in place.
void Obj_0070DE20::FUN_0070DE20(int a1)
{
    unknown_144 += a1;
}

// FUNCTION: GAMEMD 0x70DE40
void TechnoClass::FUN_0070DE40(int a1)
{
    this->GattlingValue -= a1;
    if (this->GattlingValue < 0 || a1 == 0) {
        this->GattlingValue = 0;
    }
}

// FUNCTION: GAMEMD 0x70DE70
// Spin the gattling gun up. The value rises by RateUp per tick while below the
// last stage's threshold (elite or normal table); once it reaches the current
// stage's threshold the stage steps up. The spin-up sound of the weapon for
// the current stage is started when none is playing.
void TechnoClass::FUN_0070DE70(int a)
{
    int stages = vf_33()->WeaponStages;
    int limit;
    if (Veterancy.FUN_00750010()) {
        limit = vf_33()->EliteStage[stages - 1];
    } else {
        limit = vf_33()->WeaponStage[stages - 1];
    }
    int value = GattlingValue;
    if (value < limit) {
        GattlingValue += vf_33()->RateUp * a;
    }
    int stage = CurrentGattlingStage;
    WeaponTypeClass* weapon = vf_254(stage * 2)->WeaponType;
    UnusedGattlingSoundController.Stop();
    IsUnusedGattlingSoundPlaying = 0;
    if (stage >= 0 && stage < stages - 1) {
        int threshold;
        if (Veterancy.FUN_00750010()) {
            threshold = vf_33()->EliteStage[stage];
        } else {
            threshold = vf_33()->WeaponStage[stage];
        }
        if (value >= threshold) {
            stage++;
            if (stage >= 0) {
                CurrentGattlingStage = stage;
            }
            weapon = vf_254(stage * 2)->WeaponType;
            GattlingSoundController.Stop();
            IsGattlingSoundPlaying = 0;
        }
    }
    if (!IsGattlingSoundPlaying && weapon->Reports.Count > 0) {
        AudioController* controller = &GattlingSoundController;
        controller->Stop();
        unsigned int count = weapon->Reports.Count;
        CoordStruct where = Location;
        int sound = weapon->Reports.Items[DAT_00886B88.Random() % count];
        FUN_007509E0(sound, &where, controller);
        IsGattlingSoundPlaying = 1;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70E000
//
// Spin the gattling gun down. The value drops by RateDown per tick and is
// clamped at zero; once both value and stage are zero any still-playing
// spin sounds are stopped. Otherwise the weapon for the current stage is
// re-selected and, when the value has fallen below the stage's threshold
// (elite or normal table), the stage steps down and the spin-down sound
// stops.
void Techno_0070E000::GattlingRateDown(int rate)
{
    GattlingSoundController.EndLooping();
    IsGattlingSoundPlaying = 0;

    int step = (this->*Vptr->GetTechnoType)()->RateDown * rate;
    GattlingValue -= step;
    if (GattlingValue < 0 || step == 0) {
        GattlingValue = 0;
    }

    int value = GattlingValue;
    int stage = CurrentGattlingStage;
    if (value == 0 && stage == 0) {
        if (IsUnusedGattlingSoundPlaying || IsGattlingSoundPlaying) {
            GattlingSoundController.Stop();
            UnusedGattlingSoundController.Stop();
            IsUnusedGattlingSoundPlaying = 0;
            IsGattlingSoundPlaying = 0;
        }
    } else {
        (this->*Vptr->GetWeapon)(stage * 2);
        if (stage > 0) {
            int threshold;
            if (FUN_00750010(&Veterancy)) {
                threshold = (this->*Vptr->GetTechnoType)()->EliteStage[stage - 1];
            } else {
                threshold = (this->*Vptr->GetTechnoType)()->WeaponStage[stage - 1];
            }
            if (value < threshold) {
                stage--;
                if (stage >= 0) {
                    CurrentGattlingStage = stage;
                }
                (this->*Vptr->GetWeapon)(stage * 2);
                UnusedGattlingSoundController.Stop();
                IsUnusedGattlingSoundPlaying = 0;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x70E120
WeaponStruct* TechnoClass::vf_252()
{
    return this->vf_254(this->vf_249());
}

// FUNCTION: GAMEMD 0x70E140
WeaponStruct* TechnoClass::vf_254(int a1)
{
    if (a1 == -1) {
        return 0;
    }
    if (this->Veterancy.FUN_00750010()) {
        WeaponStruct* weapon = this->vf_33()->GetEliteWeapon(a1);
        if (weapon != 0 && weapon->WeaponType != 0) {
            return weapon;
        }
    }
    return this->vf_33()->GetWeapon(a1);
}

// FUNCTION: GAMEMD 0x70E1A0  (__thiscall)
// The weapon a turreted unit is currently aiming with, or weapon zero for
// everything else.
//
// Retail has the GetWeapon dispatch twice, which reads as two call sites and is
// not: the source selects the index on the two arms of one test and calls once,
// and cl duplicates the short tail into both arms. Spelled as two returns the
// else arm folds its index to `PUSH 0` where retail materialises it with
// `XOR EAX,EAX; PUSH EAX` (68.2%); with one call and an else-assignment the
// index is a live variable in EAX on both paths, which is retail exactly.
// The index also has to be a named local rather than the member expression, or
// cl hoists the vtable load above it (40.9%).
WeaponStruct* TechnoView_0070E1A0::GetPrimaryWeapon()
{
    int weaponIndex;

    if ((this->*this->Vfptr->At_84)()->HasTurret()) {
        weaponIndex = this->CurrentWeaponNumber;
    } else {
        weaponIndex = 0;
    }
    return (this->*this->Vfptr->At_3F8)(weaponIndex);
}

// FUNCTION: GAMEMD 0x70E1E0
int TechnoClass::FUN_0070E1E0(int a1)
{
    bool low = a1 < 2;
    bool inRange = this->vf_33()->FUN_00717880() && a1 < this->vf_33()->WeaponCount;
    if (a1 >= -1 && (low || inRange)) {
        return 1;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0070E240
// True when `slot` is non-null and holds a non-zero value.
int __stdcall FUN_0070E240(const int* slot)
{
    if (slot != NULL && *slot != 0) {
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x70E260
int TechnoClass::FUN_0070E260()
{
    WeaponStruct* weapon = this->GetPrimaryWeapon();
    if (weapon != 0 && weapon->WeaponType != 0) {
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x70E280  (__thiscall)
// Record the start of a disguise -- set the flag and stamp the creation frame
// -- when a target was supplied, then dispatch the virtual that actually
// applies it and hand its result straight back.
unsigned long TechnoView_0070E280::DisguiseAs(AbstractClass* pTarget)
{
    if (pTarget != 0) {
        this->Disguised = 1;
        this->DisguiseCreationFrame = CurrentFrame;
    }
    return (this->*this->Vfptr->At_49C)();
}

// FUNCTION: GAMEMD 0x70E2B0
// Starts the invulnerability countdown and notes whether it forces the shield.
void TechnoClass::FUN_0070E2B0(int duration, int unused, bool forceShielded)
{
    IronCurtainTimer = CDTimerClass(duration);
    IronTintStage = 0;
    if (forceShielded) {
        ForceShielded = 1;
    } else {
        ForceShielded = 0;
    }
}

// FUNCTION: GAMEMD 0x70E300
// Starts the airstrike countdown.
void TechnoClass::FUN_0070E300(int duration)
{
    AirstrikeTimer = CDTimerClass(duration);
    AirstrikeTintStage = 0;
}

// FUNCTION: GAMEMD 0x70E340
void TechnoClass::vf_86()
{
    CDTimerClass timer;
    timer.StartTime = CurrentFrame;
    timer.TimeLeft = 0;
    this->AirstrikeTimer = timer;
}

// FUNCTION: GAMEMD 0x70E360  (__thiscall)
// The total effect tint is the invulnerability tint folded through the
// airstrike tint helper:
//   GetAirstrikeTintIntensity(GetInvulnerabilityTintIntensity(current)).
// Retail passes `current` on the stack to the first helper, then the result on
// to the second (both __thiscall on `this`); neither helper is matched here.
int TechnoClass::GetEffectTintIntensity(int currentIntensity) const
{
    return GetAirstrikeTintIntensity(GetInvulnerabilityTintIntensity(currentIntensity));
}

// FUNCTION: GAMEMD 0x70E380  TechnoClass::GetInvulnerabilityTintIntensity (__thiscall, ret 0x4)
//
// Scale a tint intensity by the iron-curtain flash. The timer's remaining
// frames drive a per-stage ramp (a 256-based fixed-point factor), the product
// is scaled back down and capped at 2000. Stages outside 1..9 pass the
// intensity through.
int TechnoClass::GetInvulnerabilityTintIntensity(int currentIntensity)
{
    int left = this->IronTintTimer.GetTimeLeft();
    int factor;

    switch (this->IronTintStage) {
    case 1:
        factor = ((12 - left) * 256) / 6;
        break;
    case 2:
    case 8:
        factor = 0x200;
        break;
    case 3:
        factor = (left * 461 + 1020) / 20;
        break;
    case 4:
        factor = (1024 - left * 77) / 8;
        break;
    case 5:
        factor = (left * 77 + 816) / 16;
        break;
    case 6:
        factor = 51;
        break;
    case 7:
        factor = (3072 - left * 461) / 6;
        break;
    case 9:
        factor = ((left + 20) * 256) / 20;
        break;
    default:
        return currentIntensity;
    }

    int result = (factor * currentIntensity) >> 8;
    if (result > 2000) {
        result = 2000;
    }
    return result;
}

// FUNCTION: GAMEMD 0x70E4B0  TechnoView_0070E4B0::GetAirstrikeTintIntensity (__thiscall, ret 0x4)
//
// Scale a tint intensity by the airstrike-target flash. The timer's remaining
// frames drive a per-stage ramp (a 256-based fixed-point factor: fading in,
// holding, fading out for the two shapes), the product is scaled back down
// and capped at 2000. Stages outside 1..9 pass the intensity through.
int TechnoView_0070E4B0::GetAirstrikeTintIntensity(int currentIntensity)
{
    int left = this->AirstrikeTintTimer.GetTimeLeft();
    int factor;

    switch (this->AirstrikeTintStage) {
    case 1:
    case 7:
        factor = ((12 - left) * 256) / 6;
        break;
    case 2:
    case 8:
        factor = 0x200;
        break;
    case 4:
        factor = ((128 - left) * 256) / 64;
        break;
    case 5:
        factor = ((left + 64) * 256) / 64;
        break;
    case 6:
        factor = 0x100;
        break;
    case 3:
    case 9:
        factor = ((left + 20) * 256) / 20;
        break;
    default:
        return currentIntensity;
    }

    int result = (factor * currentIntensity) >> 8;
    if (result > 2000) {
        result = 2000;
    }
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70ECE0  RecoilData::Fire  (__thiscall)
void RecoilData::Fire()
{
    int travel = this->Turret.Travel;
    if (travel != 0) {
        this->State = 1;
        this->TravelFramesLeft = this->Turret.CompressFrames;
        if (this->Turret.CompressFrames < 1) {
            this->TravelFramesLeft = 1;
        }
        this->TravelPerFrame = (float)travel / (float)this->TravelFramesLeft;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70ED10
//
// One frame of turret/barrel recoil. While a recoil is in progress the travel
// accumulates by the per-frame step and the frame countdown ticks; when it
// expires the state machine advances Compressing(1) -> Holding(2) ->
// Recovering(3) -> Inactive(0). Entering Holding zeroes the step and loads the
// hold count (a hold of <= 1 frame drops straight into Recovering); entering
// Recovering loads the recover count (clamped to at least 1) and sets the step
// to walk the full travel back over that many frames.
void RecoilData_0070ED10::Update()
{
    unsigned int state = this->State;

    if (state != 0) {
        this->TravelSoFar = this->TravelPerFrame + this->TravelSoFar;
        this->TravelFramesLeft = this->TravelFramesLeft - 1;

        if (this->TravelFramesLeft <= 0) {
            switch (state) {
            case 1:
                this->State = 2;
                this->TravelFramesLeft = this->Turret.HoldFrames;
                this->TravelPerFrame = 0.0f;
                if (this->TravelFramesLeft > 1) {
                    break;
                }
                // fall through
            case 2:
                this->State = 3;
                this->TravelFramesLeft = this->Turret.RecoverFrames;
                if (this->TravelFramesLeft < 1) {
                    this->TravelFramesLeft = 1;
                }
                this->TravelPerFrame = -((float)this->Turret.Travel / (float)this->TravelFramesLeft);
                break;
            case 3:
                this->State = 0;
                this->TravelSoFar = 0.0f;
                break;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x70EE30
// False when the frame falls in the 0x48..0x77 window of the 256-frame cycle
// started at DisguiseCreationFrame, or when the cell under this object refuses
// the other object's +0x30 link. True otherwise, and always true while the blink
// timer is running and the owner is not the current player.
bool TechnoClass::vf_272(ObjectClass* a1)
{
    if (DisguiseBlinkTimer.GetTimeLeft() == 0 || Owner->IsControlledByCurrentPlayer()) {
        if (Owner->IsControlledByCurrentPlayer() && vf_49()) {
            int phase = (CurrentFrame - (int)DisguiseCreationFrame + 0x40) % 256;
            if (phase >= 0x48 && phase <= 0x77) {
                return false;
            }
        } else {
            CellView_004870F0* cell = (CellView_004870F0*)vf_111();
            if (vf_49() && cell && !cell->FUN_004870F0(a1->NextObject)) {
                return false;
            }
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x70EF00
// Whether the weapon chosen against the target may be used on it. Needs a
// weapon type; the byte flag at +0x138 on that type gates every case except the
// RTTI-0x24 target, where the rules flag at +0x17E9 can stand in for it. A cell
// target also qualifies through its overlay record's byte at +0x2B5; an object
// target qualifies when slot 49 is true and slot 52(true) is null.
bool TechnoClass::vf_230(AbstractClass* target)
{
    WeaponStruct* ws = vf_254(vf_185(target));
    char* weaponType = (char*)ws->WeaponType;
    if (weaponType) {
        if (target->vf_11() == 0x24) {
            if (((RulesView_DF4*)RulesInstance)->unknown_17E9 || weaponType[0x138]) {
                return true;
            }
            return false;
        }
        if (weaponType[0x138]) {
            if (target->vf_11() == 0xB) {
                int overlay = ((CellClass*)target)->OverlayTypeIndex;
                if (overlay != -1 && DAT_00A83D84[overlay]->IsARock) {
                    return true;
                }
            }
            if (target && target->Flags.unknown_14_1) {
                ObjectClass* object = (ObjectClass*)target;
                if (object->vf_49() && !object->vf_52(true)) {
                    return true;
                }
            }
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70EFD0  (__thiscall)
// Is an EMP still holding this object down? `SETG` is the signed test, so the
// remaining-lock counter is a signed int.
bool TechnoClass::IsUnderEMP()
{
    return this->EMPLockRemaining > 0;
}

// FUNCTION: GAMEMD 0x70EFE0
int TechnoClass::vf_227()
{
    TechnoTypeClass* type = this->vf_33();
    if (type != 0) {
        return type->Speed;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F000
// Member getter (byte sx); pops its stack arguments. Vtable slot 297 of TechnoClass (RTTI) and 1 derived vtable(s).
int Obj_0070F000::FUN_0070F000(Arg1_0070F000* a1) const
{
    return a1->unknown_0C;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F010
// Empty function. Vtable slot 298 of TechnoClass (RTTI) and 1 derived vtable(s).
void Obj_0070F010::FUN_0070F010()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F020
// Returns a constant boolean. Vtable slot 299 of TechnoClass (RTTI) and 1 derived vtable(s).
bool Obj_0070F020::FUN_0070F020() const
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F030
// Returns a constant boolean. Vtable slot 300 of TechnoClass (RTTI) and 1 derived vtable(s).
bool Obj_0070F030::FUN_0070F030() const
{
    return false;
}

// FUNCTION: GAMEMD 0x70F040
int TechnoClass::vf_301()
{
    return -1;
}

// FUNCTION: GAMEMD 0x70F050
CoordStruct TechnoClass::vf_302()
{
    CoordStruct coord;
    coord.X = -1;
    coord.Y = -1;
    coord.Z = -1;
    return coord;
}

// FUNCTION: GAMEMD 0x70F070
bool TechnoClass::vf_303()
{
    return this->vf_33()->vf_40();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F090  (__thiscall)
// Forwarded wholesale to the type: the object asks what it is, then asks the
// type whether that kind of thing may fire while moving. Retail tail-jumps
// (`JMP [EDX+0xa4]`) rather than calling, which is what cl emits when the
// dispatch is the whole return expression.
bool TechnoClass::CanAttackOnTheMove()
{
    TechnoTypeClass* type = vf_33();

    return type->vf_41();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F0B0
//
// Map a locomotor kind onto its expansion replacement. Only two kinds are
// remapped, and only while the expansion's rule set is active; everything
// else is handed back unchanged.
int FUN_0070F0B0(int kind, int, int)
{
    bool expansion = FUN_00731BF0();
    if (kind == 1) {
        if (expansion) {
            return 0x3E;
        }
    } else if (kind == 5) {
        if (expansion) {
            return 0x3F;
        }
    }
    return kind;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F0E0
// Returns a constant boolean. Vtable slot 305 of TechnoClass (RTTI) and 1 derived vtable(s).
bool Obj_0070F0E0::FUN_0070F0E0() const
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F0F0
// Returns a constant boolean. Vtable slot 306 of TechnoClass (RTTI) and 1 derived vtable(s).
bool Obj_0070F0F0::FUN_0070F0F0() const
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F100
// Empty function. Vtable slot 307 of TechnoClass (RTTI) and 1 derived vtable(s).
void Obj_0070F100::FUN_0070F100()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F110
// Returns a constant boolean. Vtable slot 308 of TechnoClass (RTTI) and 1 derived vtable(s).
bool Obj_0070F110::FUN_0070F110() const
{
    return false;
}

// FUNCTION: GAMEMD 0x70F120
// Physical fastcall arguments are nullable ECX object and EDX value.
// TU placement and original lexical ownership are inferred, not proved.
void __fastcall FUN_0070F120(AbstractClass* object, int value)
{
    if (object && value) {
        DAT_00B0EB3C = value;
        DAT_00B0EB38 = object;
        int duration = Rules->TalkBubbleTime;
        TechnoStatics::ClockTimer = TechnoStaticClockTimer(duration);
        DAT_0087F7E8.FUN_005673A0(object->vf_18(), 2, DAT_00A83D4C, 0, 0, 0, 1, 1);
    } else {
        DAT_00B0EB3C = 0;
        DAT_00B0EB38 = 0;
        TechnoStatics::ClockTimer = TechnoStaticClockTimer(0);
    }
}

// FUNCTION: GAMEMD 0x70F670
//
// Add this object's current contribution to the mover, remembering what was
// contributed so the undo below can take exactly that much back out.
void VelocitySource_0070F670::ApplyVelocity(Mover_0070F670* mover)
{
    if (mover != 0) {
        int amount = (this->*this->Vtbl->CurrentContribution)();
        this->Contribution = amount;
        mover->Accumulate((this->*this->Vtbl->Convert)(amount));
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F6A0
//
// Take the remembered contribution back out of the mover and forget it.
void VelocitySource_0070F670::RemoveVelocity(Mover_0070F670* mover)
{
    if (mover != 0) {
        int amount = -this->Contribution;
        mover->Accumulate((this->*this->Vtbl->Convert)(amount));
        this->Contribution = 0;
    }
}

// FUNCTION: GAMEMD 0x70F6E0  (__thiscall)
// Re-stamp this object's threat contribution into a cell's per-house threat
// map: take the old contribution out, recompute it, and put the new one in.
void TechnoView_0070F6E0::UpdateThreatInCell(CellClass* Cell)
{
    if (Cell != 0) {
        Cell->AddThreat((this->*this->Vfptr->At_38)(), -this->ThreatPosed);
        this->ThreatPosed = 0;

        int threat = (this->*this->Vfptr->At_2C0)();

        this->ThreatPosed = threat;
        Cell->AddThreat((this->*this->Vfptr->At_38)(), threat);
    }
}

// FUNCTION: GAMEMD 0x70F740
void TechnoClass::FUN_0070F740(int a1)
{
    CDTimerClass timer;
    timer.StartTime = CurrentFrame;
    timer.TimeLeft = a1;
    this->TargetingTimer = timer;
}

// FUNCTION: GAMEMD 0x70F770
// While more than ten frames remain on the targeting timer (and no scenario is loading),
// restarts it with a random 4 to 8 frames.
void TechnoClass::FUN_0070F770()
{
    if (TargetingTimer.GetTimeLeft() > 10 && !DAT_00A8E7AC) {
        TargetingTimer = CDTimerClass(DAT_00A8B230->unknown_0218.RandomRanged(4, 8));
    }
}

// FUNCTION: GAMEMD 0x70F7E0  (__thiscall)
// Inlines CDTimerClass::GetTimeLeft on TargetingTimer and reports whether it has
// expired. StartTime == -1 means "not running" -> the stored TimeLeft is the
// remaining value verbatim; otherwise subtract the elapsed frames, clamping the
// remainder at 0. The countdown is finished when the remainder is 0.
//
// The accessor is inlined with TimeLeft read once into a local and a return
// in each arm; the caller's `== 0` is then duplicated into each return, which
// is retail's two long-form tails (`xor ecx,ecx; test eax,eax; setz cl;
// mov al,cl`): one after the live SUB, one shared by the stopped and clamped
// paths.
bool TechnoClass::TargetingTimerFinished() const
{
    return this->TargetingTimer.GetTimeLeft() == 0;
}

// FUNCTION: GAMEMD 0x70F820  (__thiscall)
// The house that originally owned this object. When mind-controlled, the
// controlling unit's CaptureManager remembers the original owner; when held by
// a house's mind-control, OriginallyOwnedByHouse holds it; otherwise the live
// Owner is the original owner.
HouseClass* TechnoClass::GetOriginalOwner() const
{
    if (this->MindControlledBy != NULL)
        return ((CaptureManagerClass*)((TechnoClass*)this->MindControlledBy)->CaptureManager)->GetOriginalOwner(
            const_cast<TechnoClass*>(this));
    if (this->MindControlledByHouse != NULL)
        return (HouseClass*)this->OriginallyOwnedByHouse;
    return this->Owner;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F850  (__thiscall)
// Drop everything and go idle: clear the movement destination, clear the combat
// target, forget the archived target, and force the object into mission 5.
void TechnoClass::CancelAndGoIdle()
{
    SetDestination(0, true);
    vf_242(0);
    this->ArchiveTarget = 0;
    vf_124(5);
}

// FUNCTION: GAMEMD 0x70F890
// Set the berserk duration; on the first switch-on, a foot object leaves its
// team, then the current target is dropped and the object is put on mission 15.
void TechnoClass::FUN_0070F890(int duration)
{
    BerzerkDurationLeft = duration;
    if (!Berzerk) {
        Berzerk = 1;
        FootClass* foot = foot_cast_007104C0(this);
        if (foot && foot->Team) {
            foot->Team->LiberateMember(foot, -1, 0);
        }
        vf_242(0);
        vf_122(15, false);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// The redraw is ObjectClass primary slot 73 (vtable offset 0x124), called with 2.
// FUNCTION: GAMEMD 0x70FBD0  (__thiscall)
bool UnitClass::IsDeactivated() const
{
    return Deactivated;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70FBE0
//
// Reset through the +0x3D0 virtual first. If this object is a FootClass
// (AbstractFlags bit 2), power its locomotor back on through the COM slot at
// +0x58 — the null check and E_POINTER report are the smart-pointer dereference
// inlined. Then, if it was deactivated and its type names an ActivateSound,
// play that sound at the object's own location; finally clear Deactivated.
//
// Two phrasings matter. The Deactivated test and the sound-index test are one
// `&&` condition: split into nested `if`s VC6 loads the GetTechnoType() vtable
// pointer into EAX where retail has EDX (and shifts the coordinate-copy
// registers with it) — a pure register-naming diff at 76.5%. And the vtable
// pointer is re-read at every virtual call rather than held in a local;
// GetTechnoType() is called twice (once to test, once to fetch), as retail does.
// These casts express the binary's zero-offset AbstractClass/ObjectClass views.
// The shared spine models public inheritance; these casts do not establish
// any additional hierarchy.
void TechnoReactivate::Reactivate()
{
    (this->*(*(ReactVtbl**)this)->At_3D0)();

    if (this != 0 && (((AbstractClass*)(void*)this)->Flags.IsFoot))
    {
        FootClass* foot = (FootClass*)this;
        if (foot->Locomotor == 0)
            FUN_007DC720(0x80004003);
        LOCO_CALL0((ILocomotion*)foot->Locomotor, 0x58);
    }

    if (this->Deactivated
        && (this->*(*(ReactVtbl**)this)->GetTechnoType)()->ActivateSound != -1)
    {
        CoordStruct crd = ((ObjectClass*)(void*)this)->Location;
        VocClass_PlayAt((this->*(*(ReactVtbl**)this)->GetTechnoType)()->ActivateSound, &crd, 0);
    }

    this->Deactivated = 0;
}

// FUNCTION: GAMEMD 0x70ED80
// Adds bit 2 or bit 4 to the argument by the phase of a 256-frame cycle taken from
// DisguiseCreationFrame; the phase is only sampled when the blink timer has run out
// or its owner is controlled by the current player.
int TechnoClass::FUN_0070ED80(int flags)
{
    int result = flags;
    int frame = CurrentFrame;
    int startTime = DisguiseBlinkTimer.StartTime;
    int timeLeft = DisguiseBlinkTimer.TimeLeft;
    if (startTime != -1) {
        int elapsed = frame - startTime;
        if (elapsed >= timeLeft) goto sample;
        timeLeft -= elapsed;
    }
    if (timeLeft != 0) {
        if (!Owner->IsControlledByCurrentPlayer()) {
            return result;
        }
        frame = CurrentFrame;
    }
sample:
    int phase = (frame - DisguiseCreationFrame + 0x40) % 256;
    if (phase >= 0x40) {
        if (phase < 0x44) {
            result |= 2;
        } else if (phase < 0x4C) {
            result |= 4;
        } else if (phase < 0x50) {
            result |= 2;
        } else if (phase >= 0x70) {
            if (phase < 0x74) {
                result |= 2;
            } else if (phase < 0x7C) {
                result |= 4;
            } else if (phase < 0x80) {
                result |= 2;
            }
        }
    }
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70FC90
//
// Power the object down. When the +0x418 flag is set and the probe agrees,
// an object sitting on this cell that is the probe's own answer means there
// is nothing to do. Otherwise go through the +0x3D0 and +0x150 virtuals, cut a
// FootClass's locomotor through its COM slot +0x5C (smart-pointer null check
// and E_POINTER inlined), play the type's deactivate sound at the object's
// location if it was not already off, and set Deactivated.
void TechnoDeactivate::Deactivate()
{
    if (this->IsTether && this->FUN_0065AD30(0)) {
        TechnoDeactivate* occupant = (this->*(*(DeactVtbl**)this)->GetCell)()->FUN_0047C520();
        if (occupant == (TechnoDeactivate*)this->FUN_0065AD30(0))
            return;
    }

    (this->*(*(DeactVtbl**)this)->At_3D0)();
    (this->*(*(DeactVtbl**)this)->At_150)();

    if (this != 0 && (((AbstractClass*)(void*)this)->Flags.IsFoot))
    {
        FootClass* foot = (FootClass*)this;
        if (foot->Locomotor == 0)
            FUN_007DC720(0x80004003);
        LOCO_CALL0_DEACT((ILocomotion*)foot->Locomotor, 0x5C);
    }

    if (!this->Deactivated
        && (this->*(*(DeactVtbl**)this)->GetTechnoType)()->DeactivateSound != -1)
    {
        CoordStruct crd = ((ObjectClass*)(void*)this)->Location;
        VocClass_PlayAt((this->*(*(DeactVtbl**)this)->GetTechnoType)()->DeactivateSound, &crd, 0);
    }

    this->Deactivated = 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70FD70
//
// Begin draining the given target: link the two objects together, mark the
// target's owner, release whatever the target was holding, spawn the drain
// animation and attach it, then refresh this object's display.
//
// The display refresh is a thiscall: retail loads the display pointer from
// this+0x5D4 into ECX and passes owner, -1 and 1 on the stack. Modelling it
// as a free stdcall function omitted the display receiver.
void Drainer_0070FD70::BeginDraining(Target_0070FD70* target)
{
    if (target == 0) {
        return;
    }
    if (FUN_0047C520((this->*this->Vtbl->OccupiedCell)()) != target) {
        return;
    }

    target->DrainedBy = this;
    this->DrainingWhom = target;
    target->Owner->IsDraining = 1;

    if (target->Buffer != 0) {
        FUN_00472140(target->Buffer);
    }

    AnimClass* anim = new AnimClass(
        RulesInstance->DrainAnimationType,
        (this->*this->Vtbl->BuildCoord)(),
        0, 1, 0x600, 0, false);
    this->DrainAnim = anim;
    if (anim != 0) {
        anim->FUN_00424B50(this);
    }

    if (this != 0 && (this->Flags & 4) != 0) {
        Display_0070FD70* display = this->Display;
        if (display != 0) {
            display->Refresh(this, -1, 1);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70FE40
// Stores its argument in a member; pops its stack arguments.
void Obj_0070FE40::FUN_0070FE40(int a1)
{
    unknown_1D0 = a1;
}

// FUNCTION: GAMEMD 0x70FE50
// Releases the drain animation and detaches from the drained object, asking
// its owner to recheck power.
void Techno_0070FE50::FUN_0070FE50()
{
    if (DrainAnim) {
        DrainAnim->Release();
        DrainAnim = 0;
    }
    if (DrainTarget) {
        DrainTarget->DrainingMe = 0;
        if (DrainTarget->Owner) {
            DrainTarget->Owner->RecheckPower = 1;
        }
        DrainTarget = 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70FEB0
//
// Is this object draining another. The twin at 0x70FEC0, already matched in
// match/economy/building_class_drain.cpp, asks the same question of the other
// end of the link.
bool LocoObject_0070FEB0::IsDraining() const
{
    return this->DrainingWhom != 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70FEC0  (__thiscall)
//
// Retail body (len 0xE):
//   MOV  EDX,[ECX+0x1d0]   ; DrainingMe
//   XOR  EAX,EAX
//   TEST EDX,EDX
//   SETNZ AL
//   RET
//
// i.e. `return DrainingMe != 0;` — boolean of a pointer null test, which cl
// lowers to the xor/test/setnz tail above.
bool BuildingClass::IsBeingDrained() const
{
    return this->DrainingMe != 0;
}

// FUNCTION: GAMEMD 0x70FED0
bool TechnoClass::FUN_0070FED0()
{
    return this->vf_33()->Drainable;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70FEE0
//
// Drop the object this techno's locomotor is carrying. A carried foot unit
// still in the air is marked crashing and manipulated by this techno's
// owner, told to forget its target and destination; one on the ground is
// simply let go. Either way the link is cleared and, on request, so is
// this techno's own target.
void Techno_0070FEE0::ReleaseLocomotor(bool clearTarget)
{
    if (LocomotorTarget != 0) {
        LocomotorTarget->LocomotorSource = 0;
        if (LocomotorTarget != 0 && (LocomotorTarget->AbstractFlags & 4)) {
            if ((LocomotorTarget->*LocomotorTarget->Vptr->GetHeight)() > 0) {
                LocomotorTarget->IsCrashing = 1;
                LocomotorTarget->IsBeingManipulated = 1;
                LocomotorTarget->BeingManipulatedBy = this;
                LocomotorTarget->ChronoWarpedByHouse = Owner;
                (LocomotorTarget->*LocomotorTarget->Vptr->At_3A0)();
                (LocomotorTarget->*LocomotorTarget->Vptr->SetDestination)(0, true);
                LocomotorTarget = 0;
                if (clearTarget) {
                    (this->*Vptr->SetTarget)(0);
                }
                return;
            }
            (LocomotorTarget->*LocomotorTarget->Vptr->SetDestination)(0, true);
            Techno_0070FEE0* foot;
            if (LocomotorTarget == 0) {
                foot = 0;
            } else {
                foot = (LocomotorTarget->AbstractFlags & 4) ? LocomotorTarget : 0;
            }
            foot->IsLetGoByLocomotor = 1;
            (LocomotorTarget->*LocomotorTarget->Vptr->SetDestination)(0, true);
        }
        LocomotorTarget = 0;
        if (clearTarget) {
            (this->*Vptr->SetTarget)(0);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x710410
//
// Forget the item wherever this holder still refers to it, then pass it on to
// the shared release helper.
void Holder_00710410::FUN_00710410(void* item)
{
    if (item == this->RefA) {
        this->RefA = 0;
    }
    if (item == this->RefB) {
        this->RefB = 0;
    }
    if (item == this->RefC) {
        this->RefC = 0;
    }
    if (item == this->RefD) {
        this->RefD = 0;
    }
    FUN_005F6DA0(item);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x710460
//
// Release the waypoint buffer if one is held. Retail tail-jumps into the
// release helper with the buffer already in the receiver register.
void LocoObject_0070FEB0::FreeWaypointBuffer()
{
    if (this->WaypointBuffer != 0) {
        FUN_00472140(this->WaypointBuffer);
    }
}

// FUNCTION: GAMEMD 0x710470  TechnoClass::EnteredOpenTopped (__thiscall, ret 0x4)
// A passenger boarding an open-topped transport stays visible and keeps firing,
// so it is flagged, given its own per-entry notification, and pushed onto the
// global logic list. `this` (the transport) is never touched.
void TechnoClass::EnteredOpenTopped(TechnoClass* who)
{
    if (who != 0) {
        who->InOpenToppedTransport = true;
        TECHNO_SLOT_3D0(who);
        LogicInstance.AddObject(who, false);
    }
}

// FUNCTION: GAMEMD 0x7104A0  (__thiscall)
// Clear the passed object's InOpenToppedTransport flag (this/ECX unused).
//   MOV EAX,[ESP+4]; TEST EAX,EAX; JZ ret; MOV byte [EAX+0x82],0; RET 4
void TechnoClass::ExitedOpenTopped(TechnoClass* pWho)
{
    if (pWho)
        pWho->InOpenToppedTransport = false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7104C0  TechnoClass::MarkPassengersAsExited (__thiscall)
// Walk the cargo chain clearing the open-topped flag, stopping at the first
// link that is not a foot-class object (the +0x14 flag word, mask 4). The chain
// is the shared object list, so the type test is what bounds it.
//
// The loop is a top-tested `while (passenger != 0)` whose body guards the
// store with its own `if (passenger != 0)` and advances through the checked
// cast. Retail keeps the body's guard (`CMP EAX,ECX; JZ 0x7104DD`) even
// though the cast has just proved it; VC6 keeps it too once the advance is
// the ternary cast above — the earlier do/while spellings with the null test
// in the loop condition let the optimiser delete it (33.3%).
void TechnoClass::MarkPassengersAsExited()
{
    FootClass* passenger = Passengers.GetFirstPassenger();
    while (passenger != 0)
    {
        if (passenger != 0)
            passenger->InOpenToppedTransport = false;
        passenger = foot_cast_007104C0(passenger->NextObject);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7104F0  (__thiscall)
// Snap every passenger's Location to the transport's own Location. Walks the
// passenger linked list (first via Passengers.GetFirstPassenger, thereafter via
// NextObject) while each node carries AbstractFlags bit 0x4.
//   CALL 0x473450 ; copy this->Location -> stack coord ; CALL [vtbl+0x1B4] per node
void FootClass::UpdatePassengerCoords()
{
    ObjectClass* p = this->Passengers.GetFirstPassenger();
    CoordStruct crd = this->Location;
    if (p != NULL)
    {
        do
        {
            p->vf_109(crd);
            p = (ObjectClass*)p->NextObject;
        }
        while (p != NULL && p->Flags.IsFoot);
    }
}

// FUNCTION: GAMEMD 0x710550  (__thiscall)
// Hand a new target to every occupant of the transport. The walk stops at the
// end of the chain, and also as soon as a link turns up without the abstract
// flag bit that marks it as a live in-transport object.
//
// The loop has to be top-tested with the continuation condition negated into an
// early return. A `do`/`while` with the same condition as the latch peels the
// first iteration (51.9%) or, with the null test folded into the latch, leaves
// cl shrink-wrapping the EDI save into the loop arm where retail saves it in
// the prologue (70.0%). Hoisting the target copy above the list read, using the
// parameter directly, and a `for` over the link all hold 70.0%; a `for` with
// the lookahead in the body is 63.6%.
void TechnoView_0070E1A0::SetTargetForPassengers(AbstractClass* target)
{
    FootView_0070E1A0* passenger = this->Passengers.GetFirstPassenger();
    AbstractClass* newTarget = target;

    while (passenger != 0) {
        (passenger->*passenger->Vfptr->At_3C8)(newTarget);
        passenger = passenger->NextObject;
        if (passenger == 0 || (passenger->AbstractFlags & 4) == 0) {
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x710590
//
// Smallest weapon range over the object list headed at +0x114, starting
// from INT_MAX; the walk follows the +0x30 links while the +0x14 flag bit 4
// stays set.
int TechnoClass::FUN_00710590()
{
    int best = 0x7FFFFFFF;
    TechnoClass* node = ((ListHead_r14*)&this->Passengers)->FUN_00473450();
    if (node != 0) {
        do {
            WeaponStruct* w = node->GetPrimaryWeapon();
            WeaponTypeBase_r14* wt = (WeaponTypeBase_r14*)w->WeaponType;
            if (wt != 0 && wt->Range < best) {
                best = wt->Range;
            }
            node = (TechnoClass*)node->NextObject;
        } while (node != 0 && node->Flags.IsFoot);
    }
    return best;
}

// FUNCTION: GAMEMD 0x7105E0  (__thiscall)
// Mind-controlled iff a controller object is attached OR the "by a unit" flag
// is set. Retail short-circuits: `MOV EAX,[+0x2C0] / JNZ ret1` then tests the
// +0x2C4 byte, converging on `MOV EAX,1` / `XOR EAX,EAX`.
bool TechnoClass::IsMindControlled() const
{
    return MindControlledBy != NULL || MindControlledByAUnit;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x710600
//
// May this object fire while on the ground: it must be of the first kind, and
// its type must not carry the blocking flag.
int LocoObject_0070FEB0::CanFireFromGround()
{
    if ((this->*this->Vtbl->WhatAmI)() == 1) {
        if ((this->*this->Vtbl->GetType)()->Flag_D97 == 0) {
            return 1;
        }
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x710630
//
// May this object fire at all: the fifteenth kind always may, the first kind
// may only when its type carries the flag, and nothing else may.
//
// MATCHED 100% (23/23) once the two cold tails were spelled as explicit goto
// targets AND written in the order opposite to retail's block layout. cl 8804
// emits the two goto-target blocks in reverse source order, so retail's
// `false` block first / `true` block second comes from writing `yes:` first
// and `no:` second. The same skeleton in retail's own order reads 78.3%
// (blocks transposed, branch polarities inverted with them), and every
// single-exit spelling previously measured here sat at 3.6-4.2%: the nested
// form 42.3%, a short-circuit disjunction 4.2%, a mutated answer variable
// 3.6%, the positive form with a trailing zero return 3.7%, nested positive
// guards 3.7%. The lever is the goto skeleton plus the label transposition;
// neither alone gets there.
int LocoObject_0070FEB0::CanFireAny()
{
    if ((this->*this->Vtbl->WhatAmI)() == 15) goto yes;
    if ((this->*this->Vtbl->WhatAmI)() != 1) goto no;
    if ((this->*this->Vtbl->GetType)()->Flag_D97 == 0) goto no;
yes:
    return 1;
no:
    return 0;
}

// FUNCTION: GAMEMD 0x710670
// Add the object to the passenger list and, if one was given and the type has
// an enter-transport sound, play it at this object's location.
void TechnoClass::vf_229(FootClass* passenger)
{
    Passengers.AddPassenger(passenger);
    if (passenger && vf_33()->EnterTransportSound != -1) {
        CoordStruct where = Location;
        FUN_00750E20(vf_33()->EnterTransportSound, &where, 0);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x710750
bool GrowPairVector::Grow_710750(int extra)
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
// FUNCTION: GAMEMD 0x00710860
int __cdecl FUN_00710860(const void* a, const void* b)
{
    if (*(const int*)a == *(const int*)b)
        return 0;
    if (*(const int*)a < *(const int*)b)
        return -1;
    return 1;
}
