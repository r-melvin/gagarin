// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 via the local Ghidra CLI
//   (member-access + virtual-call disassembly at 0x4DE710). Signatures
//   cross-checked against YRpp FootClass.h / TechnoClass.h / TechnoTypeClass.h
//   (consult-only, no LICENSE; every offset reconfirmed numerically below).
//
// FootClass::RemoveFirstPassenger (retail 0x4DE710) pops the head of the
// embedded transport cargo list and, when the transport is OpenTopped and the
// list just went empty, dispatches a late FootClass virtual (vtable +0x4D8) on
// the removed passenger. The body dispatches TWO virtuals on `this`:
//   * GetTechnoType()       vtable slot 33  (+0x84)  -> reads OpenTopped @0x805
//   * OnLastPassengerLeft() vtable slot 310 (+0x4D8) -> with the removed node
// Both reach genuine C++ virtual dispatch through a view struct carrying real
// vtable slots (the struct is never constructed -- only reinterpret-cast onto a
// live FootClass -- so no vtable is emitted). The inner pop is the matched-
// elsewhere PassengersClass::RemoveFirstPassenger (retail 0x473430), declared
// here so the call site emits a reloc-normalised CALL.
#ifndef GG_MATCH_MOVEMENT_FOOT_CLASS_PASSENGER_METHODS_H
#define GG_MATCH_MOVEMENT_FOOT_CLASS_PASSENGER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#ifndef NULL
#define NULL 0
#endif

class TechnoTypeClass;
class FootClass;

// PassengersClass -- { int NumPassengers; FootClass* FirstPassenger; } singly
// linked through ObjectClass::NextObject. (YRpp TechnoClass.h)
class PassengersClass
{
public:
    FootClass* RemoveFirstPassenger();   // GAMEMD 0x473430 (matched elsewhere)

    int        NumPassengers;    // +0x00
    FootClass* FirstPassenger;   // +0x04
};
GG_STATIC_ASSERT(offsetof(PassengersClass, NumPassengers)  == 0x00);
GG_STATIC_ASSERT(offsetof(PassengersClass, FirstPassenger) == 0x04);

// TechnoTypeClass -- only the OpenTopped flag byte (+0x805) is needed here
// (MOV CL,[type+0x805] after GetTechnoType).
class TechnoTypeClass
{
public:
    char          _pad_to_805[0x805];   // +0x000 .. +0x804
    unsigned char OpenTopped;           // +0x805
};
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, OpenTopped) == 0x805);

// FootClass view. Carries the full leading vtable so both dispatched slots are
// genuine C++ virtuals; the Passengers list head sits at +0x114. Never
// constructed (reinterpret-cast onto a live FootClass), so no vtable emitted.
class FootClass
{
public:
    virtual void _vt000();
    virtual void _vt001();
    virtual void _vt002();
    virtual void _vt003();
    virtual void _vt004();
    virtual void _vt005();
    virtual void _vt006();
    virtual void _vt007();
    virtual void _vt008();
    virtual void _vt009();
    virtual void _vt010();
    virtual void _vt011();
    virtual void _vt012();
    virtual void _vt013();
    virtual void _vt014();
    virtual void _vt015();
    virtual void _vt016();
    virtual void _vt017();
    virtual void _vt018();
    virtual void _vt019();
    virtual void _vt020();
    virtual void _vt021();
    virtual void _vt022();
    virtual void _vt023();
    virtual void _vt024();
    virtual void _vt025();
    virtual void _vt026();
    virtual void _vt027();
    virtual void _vt028();
    virtual void _vt029();
    virtual void _vt030();
    virtual void _vt031();
    virtual void _vt032();
    virtual TechnoTypeClass* GetTechnoType() const;          // slot 33  -> vtable +0x84
    virtual void _vt034();
    virtual void _vt035();
    virtual void _vt036();
    virtual void _vt037();
    virtual void _vt038();
    virtual void _vt039();
    virtual void _vt040();
    virtual void _vt041();
    virtual void _vt042();
    virtual void _vt043();
    virtual void _vt044();
    virtual void _vt045();
    virtual void _vt046();
    virtual void _vt047();
    virtual void _vt048();
    virtual void _vt049();
    virtual void _vt050();
    virtual void _vt051();
    virtual void _vt052();
    virtual void _vt053();
    virtual void _vt054();
    virtual void _vt055();
    virtual void _vt056();
    virtual void _vt057();
    virtual void _vt058();
    virtual void _vt059();
    virtual void _vt060();
    virtual void _vt061();
    virtual void _vt062();
    virtual void _vt063();
    virtual void _vt064();
    virtual void _vt065();
    virtual void _vt066();
    virtual void _vt067();
    virtual void _vt068();
    virtual void _vt069();
    virtual void _vt070();
    virtual void _vt071();
    virtual void _vt072();
    virtual void _vt073();
    virtual void _vt074();
    virtual void _vt075();
    virtual void _vt076();
    virtual void _vt077();
    virtual void _vt078();
    virtual void _vt079();
    virtual void _vt080();
    virtual void _vt081();
    virtual void _vt082();
    virtual void _vt083();
    virtual void _vt084();
    virtual void _vt085();
    virtual void _vt086();
    virtual void _vt087();
    virtual void _vt088();
    virtual void _vt089();
    virtual void _vt090();
    virtual void _vt091();
    virtual void _vt092();
    virtual void _vt093();
    virtual void _vt094();
    virtual void _vt095();
    virtual void _vt096();
    virtual void _vt097();
    virtual void _vt098();
    virtual void _vt099();
    virtual void _vt100();
    virtual void _vt101();
    virtual void _vt102();
    virtual void _vt103();
    virtual void _vt104();
    virtual void _vt105();
    virtual void _vt106();
    virtual void _vt107();
    virtual void _vt108();
    virtual void _vt109();
    virtual void _vt110();
    virtual void _vt111();
    virtual void _vt112();
    virtual void _vt113();
    virtual void _vt114();
    virtual void _vt115();
    virtual void _vt116();
    virtual void _vt117();
    virtual void _vt118();
    virtual void _vt119();
    virtual void _vt120();
    virtual void _vt121();
    virtual void _vt122();
    virtual void _vt123();
    virtual void _vt124();
    virtual void _vt125();
    virtual void _vt126();
    virtual void _vt127();
    virtual void _vt128();
    virtual void _vt129();
    virtual void _vt130();
    virtual void _vt131();
    virtual void _vt132();
    virtual void _vt133();
    virtual void _vt134();
    virtual void _vt135();
    virtual void _vt136();
    virtual void _vt137();
    virtual void _vt138();
    virtual void _vt139();
    virtual void _vt140();
    virtual void _vt141();
    virtual void _vt142();
    virtual void _vt143();
    virtual void _vt144();
    virtual void _vt145();
    virtual void _vt146();
    virtual void _vt147();
    virtual void _vt148();
    virtual void _vt149();
    virtual void _vt150();
    virtual void _vt151();
    virtual void _vt152();
    virtual void _vt153();
    virtual void _vt154();
    virtual void _vt155();
    virtual void _vt156();
    virtual void _vt157();
    virtual void _vt158();
    virtual void _vt159();
    virtual void _vt160();
    virtual void _vt161();
    virtual void _vt162();
    virtual void _vt163();
    virtual void _vt164();
    virtual void _vt165();
    virtual void _vt166();
    virtual void _vt167();
    virtual void _vt168();
    virtual void _vt169();
    virtual void _vt170();
    virtual void _vt171();
    virtual void _vt172();
    virtual void _vt173();
    virtual void _vt174();
    virtual void _vt175();
    virtual void _vt176();
    virtual void _vt177();
    virtual void _vt178();
    virtual void _vt179();
    virtual void _vt180();
    virtual void _vt181();
    virtual void _vt182();
    virtual void _vt183();
    virtual void _vt184();
    virtual void _vt185();
    virtual void _vt186();
    virtual void _vt187();
    virtual void _vt188();
    virtual void _vt189();
    virtual void _vt190();
    virtual void _vt191();
    virtual void _vt192();
    virtual void _vt193();
    virtual void _vt194();
    virtual void _vt195();
    virtual void _vt196();
    virtual void _vt197();
    virtual void _vt198();
    virtual void _vt199();
    virtual void _vt200();
    virtual void _vt201();
    virtual void _vt202();
    virtual void _vt203();
    virtual void _vt204();
    virtual void _vt205();
    virtual void _vt206();
    virtual void _vt207();
    virtual void _vt208();
    virtual void _vt209();
    virtual void _vt210();
    virtual void _vt211();
    virtual void _vt212();
    virtual void _vt213();
    virtual void _vt214();
    virtual void _vt215();
    virtual void _vt216();
    virtual void _vt217();
    virtual void _vt218();
    virtual void _vt219();
    virtual void _vt220();
    virtual void _vt221();
    virtual void _vt222();
    virtual void _vt223();
    virtual void _vt224();
    virtual void _vt225();
    virtual void _vt226();
    virtual void _vt227();
    virtual void _vt228();
    virtual void _vt229();
    virtual void _vt230();
    virtual void _vt231();
    virtual void _vt232();
    virtual void _vt233();
    virtual void _vt234();
    virtual void _vt235();
    virtual void _vt236();
    virtual void _vt237();
    virtual void _vt238();
    virtual void _vt239();
    virtual void _vt240();
    virtual void _vt241();
    virtual void _vt242();
    virtual void _vt243();
    virtual void _vt244();
    virtual void _vt245();
    virtual void _vt246();
    virtual void _vt247();
    virtual void _vt248();
    virtual void _vt249();
    virtual void _vt250();
    virtual void _vt251();
    virtual void _vt252();
    virtual void _vt253();
    virtual void _vt254();
    virtual void _vt255();
    virtual void _vt256();
    virtual void _vt257();
    virtual void _vt258();
    virtual void _vt259();
    virtual void _vt260();
    virtual void _vt261();
    virtual void _vt262();
    virtual void _vt263();
    virtual void _vt264();
    virtual void _vt265();
    virtual void _vt266();
    virtual void _vt267();
    virtual void _vt268();
    virtual void _vt269();
    virtual void _vt270();
    virtual void _vt271();
    virtual void _vt272();
    virtual void _vt273();
    virtual void _vt274();
    virtual void _vt275();
    virtual void _vt276();
    virtual void _vt277();
    virtual void _vt278();
    virtual void _vt279();
    virtual void _vt280();
    virtual void _vt281();
    virtual void _vt282();
    virtual void _vt283();
    virtual void _vt284();
    virtual void _vt285();
    virtual void _vt286();
    virtual void _vt287();
    virtual void _vt288();
    virtual void _vt289();
    virtual void _vt290();
    virtual void _vt291();
    virtual void _vt292();
    virtual void _vt293();
    virtual void _vt294();
    virtual void _vt295();
    virtual void _vt296();
    virtual void _vt297();
    virtual void _vt298();
    virtual void _vt299();
    virtual void _vt300();
    virtual void _vt301();
    virtual void _vt302();
    virtual void _vt303();
    virtual void _vt304();
    virtual void _vt305();
    virtual void _vt306();
    virtual void _vt307();
    virtual void _vt308();
    virtual void _vt309();
    virtual void OnLastPassengerLeft(FootClass* passenger);  // slot 310 -> vtable +0x4D8

    FootClass* RemoveFirstPassenger();   // GAMEMD 0x4DE710 __thiscall (matched here)

    char            _pad_to_114[0x114 - 4];   // +0x004 .. +0x113 (after vptr)
    PassengersClass Passengers;               // +0x114
};
GG_STATIC_ASSERT(offsetof(FootClass, Passengers) == 0x114);

#endif  // GG_MATCH_MOVEMENT_FOOT_CLASS_PASSENGER_METHODS_H
