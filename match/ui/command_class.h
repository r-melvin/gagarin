// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// CommandClass and its keyboard-command subclasses (the hotkey commands built
// at start-up; their sources sit in Init.CPP by the __FILE__ string the
// localised-text loads pass, "D:\\ra2mdpost\\Init.CPP" at 0x825FB8).
//
// Class names and the base relation come from the retail RTTI descriptors.
// Every table has nine slots (0x28 bytes apart including the locator), and the
// slot roles are read off the bodies:
//
//   0  scalar deleting destructor (stores the CommandClass table: the derived
//      classes declare no destructor of their own)
//   1  returns the command's name string
//   2  returns a localised wide string (base: forwards to slot 4)
//   3  returns a localised wide string
//   4  returns a localised wide string
//   5  key test, base `XOR AL,AL` (false)
//   6  key test, base `NOT; SHR 0xB; AND 1` (bit 0x800 clear)
//   7  key test, base false
//   8  execute; takes the key (RET 4)
//
// Slots 1 and 8 are const: the global command list (0x87F658) is a DynamicVectorClass<const CommandClass*>
// (RTTI) and 0x533F50 calls both through its elements.
//
// Slots 1, 3, 4 and 8 of CommandClass hold __purecall (0x4C9150). No slot
// name is attested, so all are placeholders. Slot 0 is modelled as an
// ordinary virtual holding the deleting wrapper, as FileClass does in
// match/core/ram_file_class.h: the constructors live in another translation
// unit, so cl would not emit these tables or a compiler-generated `??_G` here.
//
// The five team-style commands carry one int at +0x04, stored by their
// one-argument constructors (0x535C00, 0x535FC0, 0x5360B0, 0x5361A0,
// 0x536290: `MOV [EAX+4],ECX; MOV [EAX],<vtable>`).
#ifndef GG_MATCH_UI_COMMAND_CLASS_H
#define GG_MATCH_UI_COMMAND_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x7EBE3C
class CommandClass
{
public:
    ~CommandClass() {}
    virtual void* DeletingDtor(unsigned int flags);   // 0
    virtual const char* vf_1() const = 0;      // 1  0x4C9150
    virtual const wchar_t* vf_2();       // 2  0x535CF0
    virtual const wchar_t* vf_3() = 0;   // 3  0x4C9150
    virtual const wchar_t* vf_4() = 0;   // 4  0x4C9150
    virtual bool vf_5(int key);          // 5  0x535BD0
    virtual bool vf_6(int key);          // 6  0x535BE0
    virtual bool vf_7(int key);          // 7  0x535BF0
    virtual void vf_8(int key) const = 0;      // 8  0x4C9150
};

// VTABLE: GAMEMD 0x7EB84C
class CreateTeamCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x535CD0
    virtual const char* vf_1() const;          // 1  0x535C20
    virtual const wchar_t* vf_2();       // 2  0x535C40
    virtual const wchar_t* vf_3();       // 3  0x535C70
    virtual const wchar_t* vf_4();       // 4  0x535C90
    virtual void vf_8(int key) const;          // 8  0x535CC0

    int unknown_04;   // +0x04 (stored by the one-argument constructor)
};
GG_STATIC_ASSERT(offsetof(CreateTeamCommandClass, unknown_04) == 0x04);

// VTABLE: GAMEMD 0x7EBE64
class SelectTeamCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x536090
    virtual const char* vf_1() const;          // 1  0x535FE0
    virtual const wchar_t* vf_2();       // 2  0x536000
    virtual const wchar_t* vf_3();       // 3  0x536030
    virtual const wchar_t* vf_4();       // 4  0x536050
    virtual void vf_8(int key) const;          // 8  0x536080

    int unknown_04;   // +0x04 (stored by the one-argument constructor)
};
GG_STATIC_ASSERT(offsetof(SelectTeamCommandClass, unknown_04) == 0x04);

// VTABLE: GAMEMD 0x7EBE8C
class AddTeamCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x536180
    virtual const char* vf_1() const;          // 1  0x5360D0
    virtual const wchar_t* vf_2();       // 2  0x5360F0
    virtual const wchar_t* vf_3();       // 3  0x536120
    virtual const wchar_t* vf_4();       // 4  0x536140
    virtual void vf_8(int key) const;          // 8  0x536170

    int unknown_04;   // +0x04 (stored by the one-argument constructor)
};
GG_STATIC_ASSERT(offsetof(AddTeamCommandClass, unknown_04) == 0x04);

// VTABLE: GAMEMD 0x7EBEB4
class CenterTeamCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x536270
    virtual const char* vf_1() const;          // 1  0x5361C0
    virtual const wchar_t* vf_2();       // 2  0x5361E0
    virtual const wchar_t* vf_3();       // 3  0x536210
    virtual const wchar_t* vf_4();       // 4  0x536230
    virtual void vf_8(int key) const;          // 8  0x536260

    int unknown_04;   // +0x04 (stored by the one-argument constructor)
};
GG_STATIC_ASSERT(offsetof(CenterTeamCommandClass, unknown_04) == 0x04);

// VTABLE: GAMEMD 0x7EBEDC
class TauntCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x536580
    virtual const char* vf_1() const;          // 1  0x5362B0
    virtual const wchar_t* vf_2();       // 2  0x5362D0
    virtual const wchar_t* vf_3();       // 3  0x536300
    virtual const wchar_t* vf_4();       // 4  0x536320
    virtual void vf_8(int key) const;          // 8  0x536350

    int unknown_04;   // +0x04 (stored by the one-argument constructor)
};
GG_STATIC_ASSERT(offsetof(TauntCommandClass, unknown_04) == 0x04);

// VTABLE: GAMEMD 0x7EBE14
class MultiplayerDebugCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x537FA0
    virtual const char* vf_1() const;          // 1  0x537A50
    virtual const wchar_t* vf_2();       // 2  0x537A70
    virtual const wchar_t* vf_3();       // 3  0x537A60
    virtual const wchar_t* vf_4();       // 4  0x537A80
    virtual void vf_8(int key) const;          // 8  0x537A90
};

// VTABLE: GAMEMD 0x7EBDEC
class MultiplayerSyncCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x537FC0
    virtual const char* vf_1() const;          // 1  0x537AB0
    virtual const wchar_t* vf_2();       // 2  0x537AD0
    virtual const wchar_t* vf_3();       // 3  0x537AC0
    virtual const wchar_t* vf_4();       // 4  0x537AE0
    virtual void vf_8(int key) const;          // 8  0x537AF0
};

// VTABLE: GAMEMD 0x7EBDC4
class FollowCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x537FE0
    virtual const char* vf_1() const;          // 1  0x5379A0
    virtual const wchar_t* vf_2();       // 2  0x5379B0
    virtual const wchar_t* vf_3();       // 3  0x5379D0
    virtual const wchar_t* vf_4();       // 4  0x5379F0
    virtual void vf_8(int key) const;          // 8  0x537A10
};

// VTABLE: GAMEMD 0x7EBD9C
class View1CommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538000
    virtual const char* vf_1() const;          // 1  0x5372E0
    virtual const wchar_t* vf_2();       // 2  0x5372F0
    virtual const wchar_t* vf_3();       // 3  0x537310
    virtual const wchar_t* vf_4();       // 4  0x537330
    virtual void vf_8(int key) const;          // 8  0x537350
};

// VTABLE: GAMEMD 0x7EBD74
class View2CommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538020
    virtual const char* vf_1() const;          // 1  0x5373D0
    virtual const wchar_t* vf_2();       // 2  0x5373E0
    virtual const wchar_t* vf_3();       // 3  0x537400
    virtual const wchar_t* vf_4();       // 4  0x537420
    virtual void vf_8(int key) const;          // 8  0x537440
};

// VTABLE: GAMEMD 0x7EBD4C
class View3CommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538040
    virtual const char* vf_1() const;          // 1  0x5374C0
    virtual const wchar_t* vf_2();       // 2  0x5374D0
    virtual const wchar_t* vf_3();       // 3  0x5374F0
    virtual const wchar_t* vf_4();       // 4  0x537510
    virtual void vf_8(int key) const;          // 8  0x537530
};

// VTABLE: GAMEMD 0x7EBD24
class View4CommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538060
    virtual const char* vf_1() const;          // 1  0x5375B0
    virtual const wchar_t* vf_2();       // 2  0x5375C0
    virtual const wchar_t* vf_3();       // 3  0x5375E0
    virtual const wchar_t* vf_4();       // 4  0x537600
    virtual void vf_8(int key) const;          // 8  0x537620
};

// VTABLE: GAMEMD 0x7EBCFC
class SetView1CommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538080
    virtual const char* vf_1() const;          // 1  0x5376A0
    virtual const wchar_t* vf_2();       // 2  0x5376B0
    virtual const wchar_t* vf_3();       // 3  0x5376D0
    virtual const wchar_t* vf_4();       // 4  0x5376F0
    virtual void vf_8(int key) const;          // 8  0x537710
};

// VTABLE: GAMEMD 0x7EBCD4
class SetView2CommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x5380A0
    virtual const char* vf_1() const;          // 1  0x537760
    virtual const wchar_t* vf_2();       // 2  0x537770
    virtual const wchar_t* vf_3();       // 3  0x537790
    virtual const wchar_t* vf_4();       // 4  0x5377B0
    virtual void vf_8(int key) const;          // 8  0x5377D0
};

// VTABLE: GAMEMD 0x7EBCAC
class SetView3CommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x5380C0
    virtual const char* vf_1() const;          // 1  0x537820
    virtual const wchar_t* vf_2();       // 2  0x537830
    virtual const wchar_t* vf_3();       // 3  0x537850
    virtual const wchar_t* vf_4();       // 4  0x537870
    virtual void vf_8(int key) const;          // 8  0x537890
};

// VTABLE: GAMEMD 0x7EBC84
class SetView4CommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x5380E0
    virtual const char* vf_1() const;          // 1  0x5378E0
    virtual const wchar_t* vf_2();       // 2  0x5378F0
    virtual const wchar_t* vf_3();       // 3  0x537910
    virtual const wchar_t* vf_4();       // 4  0x537930
    virtual void vf_8(int key) const;          // 8  0x537950
};

// VTABLE: GAMEMD 0x7EBC5C
class OptionsCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538100
    virtual const char* vf_1() const;          // 1  0x537260
    virtual const wchar_t* vf_2();       // 2  0x537270
    virtual const wchar_t* vf_3();       // 3  0x537290
    virtual const wchar_t* vf_4();       // 4  0x5372B0
    virtual void vf_8(int key) const;          // 8  0x5372D0
};

// VTABLE: GAMEMD 0x7EBC34
class SidebarUpCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538120
    virtual const char* vf_1() const;          // 1  0x537140
    virtual const wchar_t* vf_2();       // 2  0x537150
    virtual const wchar_t* vf_3();       // 3  0x537170
    virtual const wchar_t* vf_4();       // 4  0x537190
    virtual void vf_8(int key) const;          // 8  0x5371B0
};

// VTABLE: GAMEMD 0x7EBC0C
class SidebarDownCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538140
    virtual const char* vf_1() const;          // 1  0x5371D0
    virtual const wchar_t* vf_2();       // 2  0x5371E0
    virtual const wchar_t* vf_3();       // 3  0x537200
    virtual const wchar_t* vf_4();       // 4  0x537220
    virtual void vf_8(int key) const;          // 8  0x537240
};

// VTABLE: GAMEMD 0x7EBBE4
class CenterREventCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538160
    virtual const char* vf_1() const;          // 1  0x5370C0
    virtual const wchar_t* vf_2();       // 2  0x5370D0
    virtual const wchar_t* vf_3();       // 3  0x5370F0
    virtual const wchar_t* vf_4();       // 4  0x537110
    virtual void vf_8(int key) const;          // 8  0x537130
};

// VTABLE: GAMEMD 0x7EBBBC
class BeaconPlacementCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538180
    virtual const char* vf_1() const;          // 1  0x537030
    virtual const wchar_t* vf_2();       // 2  0x537040
    virtual const wchar_t* vf_3();       // 3  0x537060
    virtual const wchar_t* vf_4();       // 4  0x537080
    virtual void vf_8(int key) const;          // 8  0x5370A0
};

// VTABLE: GAMEMD 0x7EBB94
class ToggleSellCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x5381A0
    virtual const char* vf_1() const;          // 1  0x536FB0
    virtual const wchar_t* vf_2();       // 2  0x536FC0
    virtual const wchar_t* vf_3();       // 3  0x536FE0
    virtual const wchar_t* vf_4();       // 4  0x537000
    virtual void vf_8(int key) const;          // 8  0x537020
};

// VTABLE: GAMEMD 0x7EBB6C
class ToggleRepairCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x5381C0
    virtual const char* vf_1() const;          // 1  0x536F30
    virtual const wchar_t* vf_2();       // 2  0x536F40
    virtual const wchar_t* vf_3();       // 3  0x536F60
    virtual const wchar_t* vf_4();       // 4  0x536F80
    virtual void vf_8(int key) const;          // 8  0x536FA0
};

// VTABLE: GAMEMD 0x7EBB44
class AllianceCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x5381E0
    virtual const char* vf_1() const;          // 1  0x536EB0
    virtual const wchar_t* vf_2();       // 2  0x536EC0
    virtual const wchar_t* vf_3();       // 3  0x536EE0
    virtual const wchar_t* vf_4();       // 4  0x536F00
    virtual void vf_8(int key) const;          // 8  0x536F20
};

// VTABLE: GAMEMD 0x7EBB1C
class CenterBaseCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538200
    virtual const char* vf_1() const;          // 1  0x536E30
    virtual const wchar_t* vf_2();       // 2  0x536E40
    virtual const wchar_t* vf_3();       // 3  0x536E60
    virtual const wchar_t* vf_4();       // 4  0x536E80
    virtual void vf_8(int key) const;          // 8  0x536EA0
};

// VTABLE: GAMEMD 0x7EBAF4
class CenterViewCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538220
    virtual const char* vf_1() const;          // 1  0x536D90
    virtual const wchar_t* vf_2();       // 2  0x536DA0
    virtual const wchar_t* vf_3();       // 3  0x536DC0
    virtual const wchar_t* vf_4();       // 4  0x536DE0
    virtual void vf_8(int key) const;          // 8  0x536E00
};

// VTABLE: GAMEMD 0x7EBACC
class ScatterCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538240
    virtual const char* vf_1() const;          // 1  0x536D10
    virtual const wchar_t* vf_2();       // 2  0x536D20
    virtual const wchar_t* vf_3();       // 3  0x536D40
    virtual const wchar_t* vf_4();       // 4  0x536D60
    virtual void vf_8(int key) const;          // 8  0x536D80
};

// VTABLE: GAMEMD 0x7EBAA4
class GuardCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538260
    virtual const char* vf_1() const;          // 1  0x536C90
    virtual const wchar_t* vf_2();       // 2  0x536CA0
    virtual const wchar_t* vf_3();       // 3  0x536CC0
    virtual const wchar_t* vf_4();       // 4  0x536CE0
    virtual void vf_8(int key) const;          // 8  0x536D00
};

// VTABLE: GAMEMD 0x7EBA7C
class StopCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538280
    virtual const char* vf_1() const;          // 1  0x536B10
    virtual const wchar_t* vf_2();       // 2  0x536B20
    virtual const wchar_t* vf_3();       // 3  0x536B40
    virtual const wchar_t* vf_4();       // 4  0x536B60
    virtual void vf_8(int key) const;          // 8  0x536B80
};

// VTABLE: GAMEMD 0x7EBA54
class AllToCheerCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x5382A0
    virtual const char* vf_1() const;          // 1  0x536B90
    virtual const wchar_t* vf_2();       // 2  0x536BA0
    virtual const wchar_t* vf_3();       // 3  0x536BC0
    virtual const wchar_t* vf_4();       // 4  0x536BE0
    virtual void vf_8(int key) const;          // 8  0x536C00
};

// VTABLE: GAMEMD 0x7EBA2C
class DeployCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x5382C0
    virtual const char* vf_1() const;          // 1  0x536C10
    virtual const wchar_t* vf_2();       // 2  0x536C20
    virtual const wchar_t* vf_3();       // 3  0x536C40
    virtual const wchar_t* vf_4();       // 4  0x536C60
    virtual void vf_8(int key) const;          // 8  0x536C80
};

// VTABLE: GAMEMD 0x7EBA04
class PrevObjectCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x5382E0
    virtual const char* vf_1() const;          // 1  0x536A10
    virtual const wchar_t* vf_2();       // 2  0x536A20
    virtual const wchar_t* vf_3();       // 3  0x536A40
    virtual const wchar_t* vf_4();       // 4  0x536A60
    virtual void vf_8(int key) const;          // 8  0x536A80
};

// VTABLE: GAMEMD 0x7EB9DC
class NextObjectCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538300
    virtual const char* vf_1() const;          // 1  0x5365A0
    virtual const wchar_t* vf_2();       // 2  0x5365B0
    virtual const wchar_t* vf_3();       // 3  0x5365D0
    virtual const wchar_t* vf_4();       // 4  0x5365F0
    virtual void vf_8(int key) const;          // 8  0x536610
};

// VTABLE: GAMEMD 0x7EB9B4
class PlanningModeCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538320
    virtual const char* vf_1() const;          // 1  0x5366A0
    virtual const wchar_t* vf_2();       // 2  0x5366B0
    virtual const wchar_t* vf_3();       // 3  0x5366D0
    virtual const wchar_t* vf_4();       // 4  0x5366F0
    virtual bool vf_5(int key);          // 5  0x536710
    virtual bool vf_6(int key);          // 6  0x536730
    virtual bool vf_7(int key);          // 7  0x536740
    virtual void vf_8(int key) const;          // 8  0x536750
};

// VTABLE: GAMEMD 0x7EB98C
class CombatantSelectCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538340
    virtual const char* vf_1() const;          // 1  0x536770
    virtual const wchar_t* vf_2();       // 2  0x536780
    virtual const wchar_t* vf_3();       // 3  0x5367A0
    virtual const wchar_t* vf_4();       // 4  0x5367C0
    virtual bool vf_5(int key);          // 5  0x5367E0
    virtual void vf_8(int key) const;          // 8  0x5367F0
};

// VTABLE: GAMEMD 0x7EB964
class TypeSelectCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538360
    virtual const char* vf_1() const;          // 1  0x536810
    virtual const wchar_t* vf_2();       // 2  0x536820
    virtual const wchar_t* vf_3();       // 3  0x536840
    virtual const wchar_t* vf_4();       // 4  0x536860
    virtual bool vf_5(int key);          // 5  0x536880
    virtual bool vf_6(int key);          // 6  0x536890
    virtual bool vf_7(int key);          // 7  0x5368A0
    virtual void vf_8(int key) const;          // 8  0x5368B0
};

// VTABLE: GAMEMD 0x7EB93C
class HealthNavCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538380
    virtual const char* vf_1() const;          // 1  0x5368D0
    virtual const wchar_t* vf_2();       // 2  0x5368E0
    virtual const wchar_t* vf_3();       // 3  0x536900
    virtual const wchar_t* vf_4();       // 4  0x536920
    virtual bool vf_5(int key);          // 5  0x536940
    virtual void vf_8(int key) const;          // 8  0x536950
};

// VTABLE: GAMEMD 0x7EB914
class VeterancyNavCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x5383A0
    virtual const char* vf_1() const;          // 1  0x536970
    virtual const wchar_t* vf_2();       // 2  0x536980
    virtual const wchar_t* vf_3();       // 3  0x5369A0
    virtual const wchar_t* vf_4();       // 4  0x5369C0
    virtual bool vf_5(int key);          // 5  0x5369E0
    virtual void vf_8(int key) const;          // 8  0x5369F0
};

// VTABLE: GAMEMD 0x7EB8EC
class SetStructureTabCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x5383C0
    virtual const char* vf_1() const;          // 1  0x535D20
    virtual const wchar_t* vf_2();       // 2  0x535D30
    virtual const wchar_t* vf_3();       // 3  0x535D50
    virtual const wchar_t* vf_4();       // 4  0x535D70
    virtual void vf_8(int key) const;          // 8  0x535D90
};

// VTABLE: GAMEMD 0x7EB8C4
class SetDefenseTabCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x5383E0
    virtual const char* vf_1() const;          // 1  0x535DE0
    virtual const wchar_t* vf_2();       // 2  0x535DF0
    virtual const wchar_t* vf_3();       // 3  0x535E10
    virtual const wchar_t* vf_4();       // 4  0x535E30
    virtual void vf_8(int key) const;          // 8  0x535E50
};

// VTABLE: GAMEMD 0x7EB89C
class SetUnitTabCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538400
    virtual const char* vf_1() const;          // 1  0x535F30
    virtual const wchar_t* vf_2();       // 2  0x535F40
    virtual const wchar_t* vf_3();       // 3  0x535F60
    virtual const wchar_t* vf_4();       // 4  0x535F80
    virtual void vf_8(int key) const;          // 8  0x535FA0
};

// VTABLE: GAMEMD 0x7EB874
class SetInfantryTabCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538420
    virtual const char* vf_1() const;          // 1  0x535EA0
    virtual const wchar_t* vf_2();       // 2  0x535EB0
    virtual const wchar_t* vf_3();       // 3  0x535ED0
    virtual const wchar_t* vf_4();       // 4  0x535EF0
    virtual void vf_8(int key) const;          // 8  0x535F10
};

// VTABLE: GAMEMD 0x7EBF04
class ScreenCaptureCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538440
    virtual const char* vf_1() const;          // 1  0x537B50
    virtual const wchar_t* vf_2();       // 2  0x537B80
    virtual const wchar_t* vf_3();       // 3  0x537B60
    virtual const wchar_t* vf_4();       // 4  0x537BA0
    virtual void vf_8(int key) const;          // 8  0x537BC0
};

// VTABLE: GAMEMD 0x7EBF2C
class PageUserCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538460
    virtual const char* vf_1() const;          // 1  0x537DE0
    virtual const wchar_t* vf_2();       // 2  0x537DF0
    virtual const wchar_t* vf_3();       // 3  0x537E10
    virtual const wchar_t* vf_4();       // 4  0x537E30
    virtual void vf_8(int key) const;          // 8  0x537E50
};

// VTABLE: GAMEMD 0x7EBF54
class CursorPositionCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x538480
    virtual const char* vf_1() const;          // 1  0x537E80
    virtual const wchar_t* vf_2();       // 2  0x537E90
    virtual const wchar_t* vf_3();       // 3  0x537EB0
    virtual const wchar_t* vf_4();       // 4  0x537ED0
    virtual void vf_8(int key) const;          // 8  0x537EF0
};

// VTABLE: GAMEMD 0x7EBF7C
class DeleteCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);   // 0  0x5384A0
    virtual const char* vf_1() const;          // 1  0x537F20
    virtual const wchar_t* vf_2();       // 2  0x537F30
    virtual const wchar_t* vf_3();       // 3  0x537F50
    virtual const wchar_t* vf_4();       // 4  0x537F70
    virtual void vf_8(int key) const;          // 8  0x537F90
};

#endif  // GG_MATCH_UI_COMMAND_CLASS_H
