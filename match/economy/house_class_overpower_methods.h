// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x4F9AF0 (CanOverpower)
//   and 0x50C8C0 (Cheer), via the local Ghidra CLI. Cross-checked vs YRpp
//   HouseClass.h / TechnoClass.h / AbstractClass.h (consult-only; every
//   offset, vtable slot and global address reconfirmed against the disasm).
//
// Only the members/slots these two methods touch are modelled:
//   HouseClass: ArrayIndex @0x30, Allies bitfield dword @0x5788.
//   TechnoClass: AbstractFlags @0x14 (byte test &2), Owner @0x21C, and two
//     virtuals — GetOwningHouse @vtable+0x3C (slot 15) and the cheer hook
//     @vtable+0x388 (slot 226). The filler virtuals are declared (never
//     defined) only to place the indirect calls at the exact vtable byte
//     offsets; a real virtual member is the only construct that both puts
//     `this` in ECX and emits `call [vtable+N]`.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_OVERPOWER_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_OVERPOWER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class HouseClass;  // forward declaration (TechnoClass::GetOwningHouse / Owner)

// ---------------------------------------------------------------------------
// TechnoClass — modelled as the polymorphic game object whose primary vtable
// carries GetOwningHouse() at slot 15 (+0x3C) and the per-house cheer hook
// at slot 226 (+0x388). Data members: AbstractFlags @0x14, Owner @0x21C.
// ---------------------------------------------------------------------------
class TechnoClass
{
public:
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
    virtual HouseClass* GetOwningHouse() const;  // slot 15 -> vtable+0x3C
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
    virtual void OnHouseCheer(int);              // slot 226 -> vtable+0x388

    char  _pad04[0x14 - 0x04];   // +0x04  (after the vptr)
    int   AbstractFlags;         // +0x14
    char  _pad18[0x21C - 0x18];  // +0x18
    HouseClass* Owner;           // +0x21C
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(TechnoClass, AbstractFlags) == 0x14);
GG_STATIC_ASSERT(offsetof(TechnoClass, Owner)         == 0x21C);
#endif

// ---------------------------------------------------------------------------
// HouseClass — only ArrayIndex (+0x30) and the Allies bitfield dword (+0x5788)
// are touched (by CanOverpower). Cheer uses `this` only as an identity value.
// ---------------------------------------------------------------------------
class HouseClass
{
public:
    bool CanOverpower(TechnoClass* pTarget) const;  // GAMEMD 0x4F9AF0 __thiscall
    void Cheer();                                   // GAMEMD 0x50C8C0 __thiscall

    char _pad00[0x30];                 // [0x00..0x2F] opaque base — P2
    int  ArrayIndex;                   // +0x30
    char _pad34[0x5788 - (0x30 + 4)];  // [0x34..0x5787] opaque — P2
    int  Allies;                       // +0x5788 (one bit per allied house)
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(HouseClass, ArrayIndex) == 0x30);
GG_STATIC_ASSERT(offsetof(HouseClass, Allies)     == 0x5788);
#endif

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_OVERPOWER_METHODS_H
