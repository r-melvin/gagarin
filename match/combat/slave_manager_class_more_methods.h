// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x6AF580,
//   0x6AF650, 0x6B0D60; ctor 0x6AF1A0; primary vtable @0x7F31C8). Names
//   cross-checked against YRpp (
//   every offset reconfirmed numerically from the disassembly below).
//
// SlaveManagerClass extra methods: SetOwner / CreateSlave / Deploy2.
//   * SetOwner re-parents the manager: clears the old owner's back-pointer,
//     destroys any slave-manager already on the new owner (Killed + delete via
//     the COM deleting-dtor at vtable+0x20), installs `this`, and re-stamps the
//     master onto every live slave (slave+0x2DC).
//   * CreateSlave spawns one slave infantry through the owner's coords and the
//     slave type's factory (vt+0x8C), inits it (vt+0xD4), and fills the node.
//   * Deploy2: if Ready(State==0), switch to Working(4) and Guard every live
//     slave (vt+0x3D0), walking SlaveNodes back-to-front.
#ifndef GG_MATCH_COMBAT_SLAVE_MANAGER_CLASS_MORE_METHODS_H
#define GG_MATCH_COMBAT_SLAVE_MANAGER_CLASS_MORE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"

// Unsorted::CurrentFrame — global frame counter @0x00A8ED84.
#include "../core/frame_counter.h"

class SlaveManagerClass;
struct SlaveManagerHandle;
struct SlaveObject;
class HouseClass;

// ---------------------------------------------------------------------------
// TechnoView_006AF580 — the slave miner / master. Only two things are touched:
//   * GetCoords()  (primary vtable index 15 -> 0x3C) — CreateSlave.
//   * SlaveManager (+0x2D8) — the back-pointer to its SlaveManagerClass.
// Modelled with a single vptr (4 bytes) + explicit padding; the COM tail and
// every other member are P2.
// ---------------------------------------------------------------------------
// Retail RTTI 0x817B58 establishes the class key; public access preserves this ABI view.
class TechnoView_006AF580
{
public:
    virtual void _tv0();
    virtual void _tv1();
    virtual void _tv2();
    virtual void _tv3();
    virtual void _tv4();
    virtual void _tv5();
    virtual void _tv6();
    virtual void _tv7();
    virtual void _tv8();
    virtual void _tv9();
    virtual void _tv10();
    virtual void _tv11();
    virtual void _tv12();
    virtual void _tv13();
    virtual void _tv14();
    virtual void* GetCoords();           // index 15 -> 0x3C
    char _pad_tc[0x2D8 - 0x04];           // [0x04 .. 0x2D8)
    SlaveManagerHandle* SlaveManager;     // +0x2D8
};

// ---------------------------------------------------------------------------
// InfantryTypeClass — the slave type. CreateSlave calls its object factory at
// primary vtable index 35 -> 0x8C (takes the spawn coords, returns the slave).
// ---------------------------------------------------------------------------
class InfantryTypeClass
{
public:
    virtual void _itv0();
    virtual void _itv1();
    virtual void _itv2();
    virtual void _itv3();
    virtual void _itv4();
    virtual void _itv5();
    virtual void _itv6();
    virtual void _itv7();
    virtual void _itv8();
    virtual void _itv9();
    virtual void _itv10();
    virtual void _itv11();
    virtual void _itv12();
    virtual void _itv13();
    virtual void _itv14();
    virtual void _itv15();
    virtual void _itv16();
    virtual void _itv17();
    virtual void _itv18();
    virtual void _itv19();
    virtual void _itv20();
    virtual void _itv21();
    virtual void _itv22();
    virtual void _itv23();
    virtual void _itv24();
    virtual void _itv25();
    virtual void _itv26();
    virtual void _itv27();
    virtual void _itv28();
    virtual void _itv29();
    virtual void _itv30();
    virtual void _itv31();
    virtual void _itv32();
    virtual void _itv33();
    virtual void _itv34();
    virtual SlaveObject* CreateObject(void* coords);  // index 35 -> 0x8C
};

// ---------------------------------------------------------------------------
// SlaveObject — one slave infantry. Touched virtuals:
//   * OnSlaveCreated() (index 53 -> 0xD4) — post-spawn init (CreateSlave).
//   * GuardSlot()      (index 244 -> 0x3D0) — re-issue Guard (Deploy2).
// Touched member: SlaveOwner (+0x2DC) — the master TechnoView_006AF580*.
// ---------------------------------------------------------------------------
struct SlaveObject
{
    virtual void _sv0();
    virtual void _sv1();
    virtual void _sv2();
    virtual void _sv3();
    virtual void _sv4();
    virtual void _sv5();
    virtual void _sv6();
    virtual void _sv7();
    virtual void _sv8();
    virtual void _sv9();
    virtual void _sv10();
    virtual void _sv11();
    virtual void _sv12();
    virtual void _sv13();
    virtual void _sv14();
    virtual void _sv15();
    virtual void _sv16();
    virtual void _sv17();
    virtual void _sv18();
    virtual void _sv19();
    virtual void _sv20();
    virtual void _sv21();
    virtual void _sv22();
    virtual void _sv23();
    virtual void _sv24();
    virtual void _sv25();
    virtual void _sv26();
    virtual void _sv27();
    virtual void _sv28();
    virtual void _sv29();
    virtual void _sv30();
    virtual void _sv31();
    virtual void _sv32();
    virtual void _sv33();
    virtual void _sv34();
    virtual void _sv35();
    virtual void _sv36();
    virtual void _sv37();
    virtual void _sv38();
    virtual void _sv39();
    virtual void _sv40();
    virtual void _sv41();
    virtual void _sv42();
    virtual void _sv43();
    virtual void _sv44();
    virtual void _sv45();
    virtual void _sv46();
    virtual void _sv47();
    virtual void _sv48();
    virtual void _sv49();
    virtual void _sv50();
    virtual void _sv51();
    virtual void _sv52();
    virtual void OnSlaveCreated();       // index 53 -> 0xD4
    virtual void _sv54();
    virtual void _sv55();
    virtual void _sv56();
    virtual void _sv57();
    virtual void _sv58();
    virtual void _sv59();
    virtual void _sv60();
    virtual void _sv61();
    virtual void _sv62();
    virtual void _sv63();
    virtual void _sv64();
    virtual void _sv65();
    virtual void _sv66();
    virtual void _sv67();
    virtual void _sv68();
    virtual void _sv69();
    virtual void _sv70();
    virtual void _sv71();
    virtual void _sv72();
    virtual void _sv73();
    virtual void _sv74();
    virtual void _sv75();
    virtual void _sv76();
    virtual void _sv77();
    virtual void _sv78();
    virtual void _sv79();
    virtual void _sv80();
    virtual void _sv81();
    virtual void _sv82();
    virtual void _sv83();
    virtual void _sv84();
    virtual void _sv85();
    virtual void _sv86();
    virtual void _sv87();
    virtual void _sv88();
    virtual void _sv89();
    virtual void _sv90();
    virtual void _sv91();
    virtual void _sv92();
    virtual void _sv93();
    virtual void _sv94();
    virtual void _sv95();
    virtual void _sv96();
    virtual void _sv97();
    virtual void _sv98();
    virtual void _sv99();
    virtual void _sv100();
    virtual void _sv101();
    virtual void _sv102();
    virtual void _sv103();
    virtual void _sv104();
    virtual void _sv105();
    virtual void _sv106();
    virtual void _sv107();
    virtual void _sv108();
    virtual void _sv109();
    virtual void _sv110();
    virtual void _sv111();
    virtual void _sv112();
    virtual void _sv113();
    virtual void _sv114();
    virtual void _sv115();
    virtual void _sv116();
    virtual void _sv117();
    virtual void _sv118();
    virtual void _sv119();
    virtual void _sv120();
    virtual void _sv121();
    virtual void _sv122();
    virtual void _sv123();
    virtual void _sv124();
    virtual void _sv125();
    virtual void _sv126();
    virtual void _sv127();
    virtual void _sv128();
    virtual void _sv129();
    virtual void _sv130();
    virtual void _sv131();
    virtual void _sv132();
    virtual void _sv133();
    virtual void _sv134();
    virtual void _sv135();
    virtual void _sv136();
    virtual void _sv137();
    virtual void _sv138();
    virtual void _sv139();
    virtual void _sv140();
    virtual void _sv141();
    virtual void _sv142();
    virtual void _sv143();
    virtual void _sv144();
    virtual void _sv145();
    virtual void _sv146();
    virtual void _sv147();
    virtual void _sv148();
    virtual void _sv149();
    virtual void _sv150();
    virtual void _sv151();
    virtual void _sv152();
    virtual void _sv153();
    virtual void _sv154();
    virtual void _sv155();
    virtual void _sv156();
    virtual void _sv157();
    virtual void _sv158();
    virtual void _sv159();
    virtual void _sv160();
    virtual void _sv161();
    virtual void _sv162();
    virtual void _sv163();
    virtual void _sv164();
    virtual void _sv165();
    virtual void _sv166();
    virtual void _sv167();
    virtual void _sv168();
    virtual void _sv169();
    virtual void _sv170();
    virtual void _sv171();
    virtual void _sv172();
    virtual void _sv173();
    virtual void _sv174();
    virtual void _sv175();
    virtual void _sv176();
    virtual void _sv177();
    virtual void _sv178();
    virtual void _sv179();
    virtual void _sv180();
    virtual void _sv181();
    virtual void _sv182();
    virtual void _sv183();
    virtual void _sv184();
    virtual void _sv185();
    virtual void _sv186();
    virtual void _sv187();
    virtual void _sv188();
    virtual void _sv189();
    virtual void _sv190();
    virtual void _sv191();
    virtual void _sv192();
    virtual void _sv193();
    virtual void _sv194();
    virtual void _sv195();
    virtual void _sv196();
    virtual void _sv197();
    virtual void _sv198();
    virtual void _sv199();
    virtual void _sv200();
    virtual void _sv201();
    virtual void _sv202();
    virtual void _sv203();
    virtual void _sv204();
    virtual void _sv205();
    virtual void _sv206();
    virtual void _sv207();
    virtual void _sv208();
    virtual void _sv209();
    virtual void _sv210();
    virtual void _sv211();
    virtual void _sv212();
    virtual void _sv213();
    virtual void _sv214();
    virtual void _sv215();
    virtual void _sv216();
    virtual void _sv217();
    virtual void _sv218();
    virtual void _sv219();
    virtual void _sv220();
    virtual void _sv221();
    virtual void _sv222();
    virtual void _sv223();
    virtual void _sv224();
    virtual void _sv225();
    virtual void _sv226();
    virtual void _sv227();
    virtual void _sv228();
    virtual void _sv229();
    virtual void _sv230();
    virtual void _sv231();
    virtual void _sv232();
    virtual void _sv233();
    virtual void _sv234();
    virtual void _sv235();
    virtual void _sv236();
    virtual void _sv237();
    virtual void _sv238();
    virtual void _sv239();
    virtual void _sv240();
    virtual void _sv241();
    virtual void _sv242();
    virtual void _sv243();
    virtual void GuardSlot();            // index 244 -> 0x3D0
    char _pad_so[0x2DC - 0x04];           // [0x04 .. 0x2DC)
    TechnoView_006AF580* SlaveOwner;              // +0x2DC
};

// ---------------------------------------------------------------------------
// SlaveManagerHandle — the polymorphic view of an *existing* SlaveManagerClass
// found on the new owner during SetOwner. We only need its COM deleting
// destructor slot (vtable index 8 -> 0x20) so that `delete` emits the retail
// `mov edx,[ecx]; push 1; call [edx+0x20]`, plus the non-virtual Killed().
// ---------------------------------------------------------------------------
struct SlaveManagerHandle
{
    virtual void _h0();
    virtual void _h1();
    virtual void _h2();
    virtual void _h3();
    virtual void _h4();
    virtual void _h5();
    virtual void _h6();
    virtual void _h7();
    virtual ~SlaveManagerHandle();        // index 8 -> vtable 0x20 (deleting dtor)
    void Killed(TechnoView_006AF580* killer, HouseClass* forced);  // GAMEMD 0x6B0AE0
};

// ---------------------------------------------------------------------------
// CDTimerClass — TimerStruct<FrameTimer>: { StartTime; CurrentTime; TimeLeft }.
// FrameTimer is empty in YRpp but occupies the 4-byte +0x04 slot (TimeLeft@0x08).
// The (int) ctor mirrors Start(duration): StartTime <- CurrentFrame, TimeLeft
// <- duration; CurrentTime is left untouched (read uninitialised on copy).
// ---------------------------------------------------------------------------
#include "../_layout/frame_timer.h"
GG_STATIC_ASSERT(offsetof(CDTimerClass, TimeLeft) == 0x08);

// One entry in the SlaveNodes vector.
struct SlaveControl
{
    SlaveObject* Slave;          // +0x00
    int          State;          // +0x04  (6 == Dead)
    CDTimerClass RespawnTimer;   // +0x08  (0x0C bytes)
};
GG_STATIC_ASSERT(offsetof(SlaveControl, Slave)       == 0x00);
GG_STATIC_ASSERT(offsetof(SlaveControl, State)       == 0x04);
GG_STATIC_ASSERT(offsetof(SlaveControl, RespawnTimer) == 0x08);

// ---------------------------------------------------------------------------
// SlaveManagerClass — modelled non-polymorphically (COM base [0x00..0x24) is
// P2). Only the members the three methods touch are named + asserted.
// ---------------------------------------------------------------------------
class SlaveManagerClass
{
public:
    char               _base[0x24];     // +0x00  COM vptrs + Array/RegenRate (P2)
    TechnoView_006AF580*       Owner;           // +0x24
    InfantryTypeClass* SlaveType;       // +0x28
    char               _pad2c[0x0C];    // [0x2C .. 0x38)
    DynamicVectorClassLayout SlaveNodes;      // +0x38  Items@0x3C, Count@0x48
    char               _pad50[0x0C];    // +0x50  RespawnTimer (CDTimerClass)
    int                State;           // +0x5C
    int                LastScanFrame;   // +0x60

    void SetOwner(TechnoView_006AF580* NewOwner);   // GAMEMD 0x6AF580
    void CreateSlave(SlaveControl* Node);   // GAMEMD 0x6AF650
    void Deploy2();                         // GAMEMD 0x6B0D60
    void GuardAllSlaves();                  // GAMEMD 0x6B0490
};
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, Owner)         == 0x24);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, SlaveType)     == 0x28);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, SlaveNodes)    == 0x38);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, State)         == 0x5C);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, LastScanFrame) == 0x60);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, SlaveNodes) + offsetof(DynamicVectorClassLayout, Items) == 0x3C);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, SlaveNodes) + offsetof(DynamicVectorClassLayout, Count) == 0x48);

#endif  // GG_MATCH_COMBAT_SLAVE_MANAGER_CLASS_MORE_METHODS_H
