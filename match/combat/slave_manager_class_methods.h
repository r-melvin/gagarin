// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x6B0A20, 0x6B0C80, ctor 0x6AF1A0),
//   cross-checked against YRpp (
//   reconfirmed numerically here).
//
// SlaveManagerClass — manages a Yuri slave-miner's owned slave infantry.
// LostSlave() finds the node owning a slave, detaches it and marks it Dead
// with the respawn timer restarted. AllGuard() walks the SlaveNodes vector and
// re-issues a Guard virtual to each live (non-Dead, non-null) slave, resetting
// the manager State+LastScanFrame.
#ifndef GG_MATCH_COMBAT_SLAVE_MANAGER_CLASS_METHODS_H
#define GG_MATCH_COMBAT_SLAVE_MANAGER_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"

// Unsorted::CurrentFrame — global frame counter @0x00A8ED84 (read by AllGuard).
#include "../core/frame_counter.h"

// The slave infantry object. AllGuard only needs its vptr to issue the virtual
// call at vtable+0x3D0 (thiscall, no args). VC6 rejects the `__thiscall`
// keyword on a free function pointer, and only a real virtual member places
// `this` in ECX, so the touched slot is modelled as a true virtual at vtable
// index 244 (244 * 4 == 0x3D0). 244 filler virtuals precede it; none are ever
// defined or instantiated — `slave->GuardSlot()` just emits the indirect call.
struct SlaveManagerClass;
struct SlaveObject {
    virtual void _v0();
    virtual void _v1();
    virtual void _v2();
    virtual void _v3();
    virtual void _v4();
    virtual void _v5();
    virtual void _v6();
    virtual void _v7();
    virtual void _v8();
    virtual void _v9();
    virtual void _v10();
    virtual void _v11();
    virtual void _v12();
    virtual void _v13();
    virtual void _v14();
    virtual void _v15();
    virtual void _v16();
    virtual void _v17();
    virtual void _v18();
    virtual void _v19();
    virtual void _v20();
    virtual void _v21();
    virtual void _v22();
    virtual void _v23();
    virtual void _v24();
    virtual void _v25();
    virtual void _v26();
    virtual void _v27();
    virtual void _v28();
    virtual void _v29();
    virtual void _v30();
    virtual void _v31();
    virtual void _v32();
    virtual void _v33();
    virtual void _v34();
    virtual void _v35();
    virtual void _v36();
    virtual void _v37();
    virtual void _v38();
    virtual void _v39();
    virtual void _v40();
    virtual void _v41();
    virtual void _v42();
    virtual void _v43();
    virtual void _v44();
    virtual void _v45();
    virtual void _v46();
    virtual void _v47();
    virtual void _v48();
    virtual void _v49();
    virtual void _v50();
    virtual void _v51();
    virtual void _v52();
    virtual void _v53();
    virtual void _v54();
    virtual void _v55();
    virtual void _v56();
    virtual void _v57();
    virtual void _v58();
    virtual void _v59();
    virtual void _v60();
    virtual void _v61();
    virtual void _v62();
    virtual void _v63();
    virtual void _v64();
    virtual void _v65();
    virtual void _v66();
    virtual void _v67();
    virtual void _v68();
    virtual void _v69();
    virtual void _v70();
    virtual void _v71();
    virtual void _v72();
    virtual void _v73();
    virtual void _v74();
    virtual void _v75();
    virtual void _v76();
    virtual void _v77();
    virtual void _v78();
    virtual void _v79();
    virtual void _v80();
    virtual void _v81();
    virtual void _v82();
    virtual void _v83();
    virtual void _v84();
    virtual void _v85();
    virtual void _v86();
    virtual void _v87();
    virtual void _v88();
    virtual void _v89();
    virtual void _v90();
    virtual void _v91();
    virtual void _v92();
    virtual void _v93();
    virtual void _v94();
    virtual void _v95();
    virtual void _v96();
    virtual void _v97();
    virtual void _v98();
    virtual void _v99();
    virtual void _v100();
    virtual void _v101();
    virtual void _v102();
    virtual void _v103();
    virtual void _v104();
    virtual void _v105();
    virtual void _v106();
    virtual void _v107();
    virtual void _v108();
    virtual void _v109();
    virtual void _v110();
    virtual void _v111();
    virtual void _v112();
    virtual void _v113();
    virtual void _v114();
    virtual void _v115();
    virtual void _v116();
    virtual void _v117();
    virtual void _v118();
    virtual void _v119();
    virtual void _v120();
    virtual void _v121();
    virtual void _v122();
    virtual void _v123();
    virtual void _v124();
    virtual void _v125();
    virtual void _v126();
    virtual void _v127();
    virtual void _v128();
    virtual void _v129();
    virtual void _v130();
    virtual void _v131();
    virtual void _v132();
    virtual void _v133();
    virtual void _v134();
    virtual void _v135();
    virtual void _v136();
    virtual void _v137();
    virtual void _v138();
    virtual void _v139();
    virtual void _v140();
    virtual void _v141();
    virtual void _v142();
    virtual void _v143();
    virtual void _v144();
    virtual void _v145();
    virtual void _v146();
    virtual void _v147();
    virtual void _v148();
    virtual void _v149();
    virtual void _v150();
    virtual void _v151();
    virtual void _v152();
    virtual void _v153();
    virtual void _v154();
    virtual void _v155();
    virtual void _v156();
    virtual void _v157();
    virtual void _v158();
    virtual void _v159();
    virtual void _v160();
    virtual void _v161();
    virtual void _v162();
    virtual void _v163();
    virtual void _v164();
    virtual void _v165();
    virtual void _v166();
    virtual void _v167();
    virtual void _v168();
    virtual void _v169();
    virtual void _v170();
    virtual void _v171();
    virtual void _v172();
    virtual void _v173();
    virtual void _v174();
    virtual void _v175();
    virtual void _v176();
    virtual void _v177();
    virtual void _v178();
    virtual void _v179();
    virtual void _v180();
    virtual void _v181();
    virtual void _v182();
    virtual void _v183();
    virtual void _v184();
    virtual void _v185();
    virtual void _v186();
    virtual void _v187();
    virtual void _v188();
    virtual void _v189();
    virtual void _v190();
    virtual void _v191();
    virtual void _v192();
    virtual void _v193();
    virtual void _v194();
    virtual void _v195();
    virtual void _v196();
    virtual void _v197();
    virtual void _v198();
    virtual void _v199();
    virtual void _v200();
    virtual void _v201();
    virtual void _v202();
    virtual void _v203();
    virtual void _v204();
    virtual void _v205();
    virtual void _v206();
    virtual void _v207();
    virtual void _v208();
    virtual void _v209();
    virtual void _v210();
    virtual void _v211();
    virtual void _v212();
    virtual void _v213();
    virtual void _v214();
    virtual void _v215();
    virtual void _v216();
    virtual void _v217();
    virtual void _v218();
    virtual void _v219();
    virtual void _v220();
    virtual void _v221();
    virtual void _v222();
    virtual void _v223();
    virtual void _v224();
    virtual void _v225();
    virtual void _v226();
    virtual void _v227();
    virtual void _v228();
    virtual void _v229();
    virtual void _v230();
    virtual void _v231();
    virtual void _v232();
    virtual void _v233();
    virtual void _v234();
    virtual void _v235();
    virtual void _v236();
    virtual void _v237();
    virtual void _v238();
    virtual void _v239();
    virtual void _v240();
    virtual void _v241();
    virtual void _v242();
    virtual void _v243();
    virtual void GuardSlot();   // slot 244 -> vtable offset 0x3D0

    char               _pad004[0x2DC - 0x04];   // +0x004
    SlaveManagerClass* SlaveOwner;              // +0x2DC  cleared by LostSlave
};
GG_STATIC_ASSERT(offsetof(SlaveObject, SlaveOwner) == 0x2DC);

// A frame-clocked countdown (CDTimerClass). The constructor writes only the
// start tick and the duration; the clock slot at +0x04 is never initialised,
// and LostSlave's 12-byte copy of a temporary carries it out of the dead stack
// slot exactly as retail does (MOV EDX,[ESP+0x10] at 0x6B0A7B).
struct SlaveTimerClass
{
    int StartTime;    // +0x00
    int unknown_04;   // +0x04  (clock slot)
    int TimeLeft;     // +0x08

    explicit SlaveTimerClass(int duration)
    {
        StartTime = CurrentFrame;
        TimeLeft = duration;
    }
};
GG_STATIC_ASSERT(offsetof(SlaveTimerClass, TimeLeft) == 0x08);
GG_STATIC_ASSERT(sizeof(SlaveTimerClass) == 0x0C);

// One entry in the SlaveNodes vector. AllGuard touches Slave (+0x00) and the
// State enum (+0x04); LostSlave also restarts the RespawnTimer (+0x08).
struct SlaveControl
{
    SlaveObject*    Slave;          // +0x00
    int             State;          // +0x04  SlaveControlStatus (6 == Dead)
    SlaveTimerClass RespawnTimer;   // +0x08
};
GG_STATIC_ASSERT(offsetof(SlaveControl, RespawnTimer) == 0x08);
GG_STATIC_ASSERT(offsetof(SlaveControl, Slave) == 0x00);
GG_STATIC_ASSERT(offsetof(SlaveControl, State) == 0x04);

struct SlaveManagerClass
{
    char               _base[0x30];     // +0x00  AbstractClass + Owner..SlaveCount
    int                RegenRate;       // +0x30  respawn delay handed to the node timer
    int                ReloadRate;      // +0x34
    DynamicVectorClassLayout SlaveNodes;      // +0x38  Items@0x3C, Count@0x48
    char               _respawnTimer[0x0C];  // +0x50  RespawnTimer (CDTimerClass)
    int                State;           // +0x5C  SlaveManagerStatus
    int                LastScanFrame;   // +0x60

    void LostSlave(SlaveObject* slave); // GAMEMD 0x6B0A20 __thiscall
    void AllGuard();                    // GAMEMD 0x6B0C80 __thiscall
};
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, RegenRate)     == 0x30);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, SlaveNodes)    == 0x38);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, State)         == 0x5C);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, LastScanFrame) == 0x60);
// SlaveNodes.Items / .Count land at the retail offsets:
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, SlaveNodes) + offsetof(DynamicVectorClassLayout, Items) == 0x3C);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, SlaveNodes) + offsetof(DynamicVectorClassLayout, Count) == 0x48);

#endif  // GG_MATCH_COMBAT_SLAVE_MANAGER_CLASS_METHODS_H
