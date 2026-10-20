// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x71AB10/0x71AD40/0x71ADE0),
//   cross-checked against YRpp TemporalClass.h (consult-only; every offset and
//   vtable slot reconfirmed numerically from the disassembly here).
//
// TemporalClass - the chrono-warp impactor attached to a TechnoClass while it
// is being chronosphere/temporal-erased. Holds the Owner (the warping unit),
// the Target being erased, and a doubly linked Next/Prev list of co-operating
// "helper" temporals that pool their warp-per-step.
#ifndef GG_MATCH_COMBAT_TEMPORAL_CLASS_METHODS_H
#define GG_MATCH_COMBAT_TEMPORAL_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// --- Owner/Target weapon chain (GetWarpPerStep) -----------------------------
// GetWarpPerStep reads Owner->GetWeapon(Owner->SelectWeapon(0))->WeaponType
// and then the dword at WeaponType+0xA4 (the per-step warp amount). Only the
// touched fields are modelled.
struct WarpWeaponTypeLike
{
    char _pad_a4[0xA4];   // +0x00
    int  WarpAmount;      // +0xA4
};
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(WarpWeaponTypeLike, WarpAmount) == 0xA4);
#endif

struct WarpWeaponStructLike
{
    WarpWeaponTypeLike* WeaponType;  // +0x00  ([ws] -> WeaponType)
};

// --- The warping unit / erased target (a TechnoClass) -----------------------
// The matched methods reach three of this object's virtuals via its vptr
// (SelectWeapon @vtable+0x2E4, GetWeapon @+0x3F8, NotifyOwnerOfDetach @+0x484)
// and two of its data members (a bool @+0x270 and a pointer @+0x278). VC6
// rejects __thiscall on a free function pointer and only a real virtual member
// places `this` in ECX, so the touched slots are modelled as true virtuals at
// the exact vtable indices (slot*4 == byte offset); the filler virtuals are
// never defined or instantiated, they only place the indirect calls.
struct TechnoLike
{
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
    virtual int SelectWeapon(int weaponIndex);            // slot 185 -> 0x2E4
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
    virtual void _v244();
    virtual void _v245();
    virtual void _v246();
    virtual void _v247();
    virtual void _v248();
    virtual void _v249();
    virtual void _v250();
    virtual void _v251();
    virtual void _v252();
    virtual void _v253();
    virtual WarpWeaponStructLike* GetWeapon(int weaponIndex);  // slot 254 -> 0x3F8
    virtual void _v255();
    virtual void _v256();
    virtual void _v257();
    virtual void _v258();
    virtual void _v259();
    virtual void _v260();
    virtual void _v261();
    virtual void _v262();
    virtual void _v263();
    virtual void _v264();
    virtual void _v265();
    virtual void _v266();
    virtual void _v267();
    virtual void _v268();
    virtual void _v269();
    virtual void _v270();
    virtual void _v271();
    virtual void _v272();
    virtual void _v273();
    virtual void _v274();
    virtual void _v275();
    virtual void _v276();
    virtual void _v277();
    virtual void _v278();
    virtual void _v279();
    virtual void _v280();
    virtual void _v281();
    virtual void _v282();
    virtual void _v283();
    virtual void _v284();
    virtual void _v285();
    virtual void _v286();
    virtual void _v287();
    virtual void _v288();
    virtual void NotifyOwnerOfDetach(int unwarp, int detach);  // slot 289 -> 0x484

    char          _pad_to_270[0x270 - 4];  // +0x004  (after the vptr)
    unsigned char TemporalImpact;          // +0x270  (bool, cleared on detach)
    char          _pad_274[0x278 - 0x271]; // +0x271
    void*         TemporalTargetingMe;     // +0x278  (back-pointer, cleared)
};
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(TechnoLike, TemporalImpact)     == 0x270);
GG_STATIC_ASSERT(offsetof(TechnoLike, TemporalTargetingMe) == 0x278);
#endif

// --- TemporalClass ----------------------------------------------------------
// AbstractClass base occupies [0x00..0x23] (P2); every field below is confirmed
// numerically from the disassembly and asserted.
struct TemporalClass
{
    int  GetWarpPerStep(int nHelperCount = 0) const;  // GAMEMD 0x71AB10 __thiscall
    void JustLetGo();                                 // GAMEMD 0x71AD40 __thiscall
    void Detach();                                    // GAMEMD 0x71ADE0 __thiscall

    char         _abstract_base[0x24];  // +0x00  AbstractClass (COM + members) - P2
    TechnoLike*  Owner;                 // +0x24
    TechnoLike*  Target;                // +0x28
    char         _lifeTimer[0x0C];      // +0x2C  CDTimerClass LifeTimer (untouched)
    void*        unknown_pointer_38;    // +0x38
    void*        SourceSW;              // +0x3C  (SuperClass*)
    TemporalClass* NextTemporal;        // +0x40
    TemporalClass* PrevTemporal;        // +0x44
    int          WarpRemaining;         // +0x48
    mutable int  WarpPerStep;           // +0x4C  (cached inside the const getter)
};
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(TemporalClass, Owner)              == 0x24);
GG_STATIC_ASSERT(offsetof(TemporalClass, Target)             == 0x28);
GG_STATIC_ASSERT(offsetof(TemporalClass, unknown_pointer_38) == 0x38);
GG_STATIC_ASSERT(offsetof(TemporalClass, SourceSW)           == 0x3C);
GG_STATIC_ASSERT(offsetof(TemporalClass, NextTemporal)       == 0x40);
GG_STATIC_ASSERT(offsetof(TemporalClass, PrevTemporal)       == 0x44);
GG_STATIC_ASSERT(offsetof(TemporalClass, WarpPerStep)        == 0x4C);
#endif

#endif  // GG_MATCH_COMBAT_TEMPORAL_CLASS_METHODS_H
