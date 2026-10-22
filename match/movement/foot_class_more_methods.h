// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 via the local Ghidra CLI
//   (member-access + virtual-call disassembly at 0x4D9920 / 0x7104F0).
//   Signatures cross-checked against YRpp FootClass.h / TechnoClass.h
//   (consult-only, no LICENSE; every offset reconfirmed numerically below).
//
// Two more FootClass methods layered on the committed instance-side spine
// (../_layout/foot_class.h). The spine models the COM vptrs as plain data
// fields, so deriving a no-data host struct adds no vtable and keeps `this` and
// every offset identical; the methods just need their own declarations to emit
// the __thiscall symbols the differ slices.
#ifndef GG_MATCH_MOVEMENT_FOOT_CLASS_MORE_METHODS_H
#define GG_MATCH_MOVEMENT_FOOT_CLASS_MORE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/foot_class.h"   // FootClass + ObjectClass/AbstractClass spine

// Members the two methods touch (self-guards this TU to the 32-bit ABI):
GG_STATIC_ASSERT(offsetof(AbstractClass, Flags) == 0x14);   // flag test &4
GG_STATIC_ASSERT(offsetof(ObjectClass,   NextObject)    == 0x30);   // passenger walk
GG_STATIC_ASSERT(offsetof(ObjectClass,   Location)      == 0x9C);   // coord source
GG_STATIC_ASSERT(offsetof(TechnoClass,   Passengers)    == 0x114);  // &Passengers
GG_STATIC_ASSERT(offsetof(FootClass,     IsScanLimited) == 0x688);  // scan-limit flag

// PassengersClass::GetFirstPassenger (retail 0x473450, `MOV EAX,[ECX+4];RET`):
// returns the FirstPassenger field. Declared on a no-data host so the call site
// emits `LEA ECX,[this+0x114]; CALL <reloc>`.
struct PassengersHost : PassengersClass
{
    void* GetFirstPassenger();   // GAMEMD 0x473450 (referenced, matched elsewhere)
};

// Passenger view: VC6 has no usable __thiscall fn-pointer keyword, so the
// passenger's virtual SetLocation (vtable slot +0x1B4 = index 109) is reached
// through genuine C++ virtual dispatch. 109 placeholder slots precede it. The
// struct is never constructed (only reinterpret-cast onto a live object), so no
// vtable is emitted for it.
struct PassengerObj
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
    virtual void SetLocation(CoordStruct* crd);   // slot 109 -> vtable +0x1B4
};
GG_STATIC_ASSERT(sizeof(PassengerObj) == 4);   // vptr only

// No-data host for the two methods; layout identical to FootClass.
struct FootMore : FootClass
{
    // FUNCTION: GAMEMD 0x4D9920  FootClass::GreatestThreat        (__thiscall)
    AbstractClass* GreatestThreat(unsigned int threat, CoordStruct* pCoord,
                                  bool onlyTargetHouseEnemy);
    // FUNCTION: GAMEMD 0x7104F0  FootClass::UpdatePassengerCoords (__thiscall)
    void UpdatePassengerCoords();

    // TechnoClass::GreatestThreat (retail 0x6F8DF0) — base implementation reached
    // by a direct (non-virtual) CALL. Declared for the reloc-normalised call.
    AbstractClass* GreatestThreatBase(unsigned int threat, CoordStruct* pCoord,
                                      bool onlyTargetHouseEnemy);
};

#endif  // GG_MATCH_MOVEMENT_FOOT_CLASS_MORE_METHODS_H
