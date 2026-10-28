// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2
//
// JumpjetLocomotionClass (layout and tables in _layout/jumpjet_locomotion_class.h).
// The COM / IPiggyback bodies below are the shapes DriveLocomotionClass uses
// (movement/drive_locomotion.cpp). Load's placement new of the no-init
// constructor stores the three vptrs, so VC6 emits Jumpjet's tables here and,
// with them, the ILocomotion (+4) and IPiggyback (+0x18) adjustor thunks.

#include <new.h>
#include "../_layout/jumpjet_locomotion_class.h"
#include "drive_support_views.h"

// GLOBAL: GAMEMD 0xABC5A8 - the empty coordinate this TU compares against.
extern "C" LocoCoord DAT_00ABC5A8;
// GLOBAL: GAMEMD 0xABC5E8 - minimum jump height unit; Height is clamped to twice it (LinkToObject 0x54AD30).
extern "C" int DAT_00ABC5E8;
// GLOBAL: GAMEMD 0xABC5DC - height subtracted over a bridge cell (InWhichLayer 0x54B8D0).
extern "C" int DAT_00ABC5DC;

// Address-local views of the linked FootClass, scoped to the Jumpjet bodies;
// every offset is read from an entry-origin instruction cited beside it.
struct JumpjetFacingView : FacingClass
{
    // FUNCTION: GAMEMD 0x4C91E0 (decl; reloc) - __thiscall constructor, one stack argument (rate of turn).
    JumpjetFacingView(int rate);
    // FUNCTION: GAMEMD 0x4C9300 (decl; reloc) - __thiscall, DoTurn 0x54B6E0.
    void FUN_004C9300(const unsigned long* dir);
    // FUNCTION: GAMEMD 0x4C9300 (decl; reloc) - same entry, LinkToObject passes its DirStruct local.
    void FUN_004C9300(const DirStruct* dir);
};

struct JumpjetTypeView
{
    char          unknown_000[0x5EC];
    unsigned char unknown_5EC;           // +0x5EC EndPiggyback `CMP [EAX+0x5EC],BL`
    char          unknown_5ED[0xD70 - 0x5ED];
    int           JumpjetTurnRate;       // +0xD70 LinkToObject @0x54AD49
    int           JumpjetSpeed;          // +0xD74 @0x54AD5C
    float         JumpjetClimb;          // +0xD78 @0x54AD6F
    float         JumpjetCrash;          // +0xD7C @0x54AD82
    int           JumpjetHeight;         // +0xD80 @0x54AD9B
    float         JumpjetAccel;          // +0xD84 @0x54ADB6
    float         JumpjetWobbles;        // +0xD88 @0x54ADC9
    char          JumpjetNoWobbles;      // +0xD8C @0x54ADEF
    char          unknown_D8D[3];
    int           unknown_D90;           // +0xD90 @0x54ADDC
};
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, JumpjetTurnRate) == 0xD70);
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, JumpjetSpeed) == 0xD74);
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, JumpjetClimb) == 0xD78);
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, JumpjetCrash) == 0xD7C);
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, JumpjetHeight) == 0xD80);
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, JumpjetAccel) == 0xD84);
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, JumpjetWobbles) == 0xD88);
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, JumpjetNoWobbles) == 0xD8C);
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, unknown_D90) == 0xD90);
GG_STATIC_ASSERT(offsetof(JumpjetTypeView, unknown_5EC) == 0x5EC);

struct JumpjetPathView
{
    char          unknown_000[0x1EC];
    unsigned char unknown_1EC;           // +0x1EC EndPiggyback `CMP [EDX+0x1EC],BL`
};
GG_STATIC_ASSERT(offsetof(JumpjetPathView, unknown_1EC) == 0x1EC);

struct JumpjetFootVirtuals
{
    virtual void vf_000();
    virtual void vf_004();
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_010();
    virtual void vf_014();
    virtual void vf_018();
    virtual void vf_01C();
    virtual void vf_020();
    virtual void vf_024();
    virtual void vf_028();
    virtual void vf_02C();
    virtual void vf_030();
    virtual void vf_034();
    virtual void vf_038();
    virtual void vf_03C();
    virtual void vf_040();
    virtual void vf_044();
    virtual void vf_048();
    virtual void vf_04C();
    virtual void vf_050();
    virtual bool vf_054();
    virtual void vf_058();
    virtual void vf_05C();
    virtual void vf_060();
    virtual void vf_064();
    virtual void vf_068();
    virtual void vf_06C();
    virtual void vf_070();
    virtual void vf_074();
    virtual void vf_078();
    virtual void vf_07C();
    virtual void vf_080();
    virtual JumpjetTypeView* vf_084();
    virtual void vf_088();
    virtual void vf_08C();
    virtual void vf_090();
    virtual void vf_094();
    virtual void vf_098();
    virtual void vf_09C();
    virtual void vf_0A0();
    virtual void vf_0A4();
    virtual void vf_0A8();
    virtual void vf_0AC();
    virtual void vf_0B0();
    virtual void vf_0B4();
    virtual void vf_0B8();
    virtual void vf_0BC();
    virtual void vf_0C0();
    virtual void vf_0C4();
    virtual void vf_0C8();
    virtual void vf_0CC();
    virtual void vf_0D0();
    virtual void vf_0D4();
    virtual void vf_0D8();
    virtual void vf_0DC();
    virtual void vf_0E0();
    virtual void vf_0E4();
    virtual void vf_0E8();
    virtual void vf_0EC();
    virtual void vf_0F0();
    virtual void vf_0F4(const LocoCoord* coord);
    virtual void vf_0F8();
    virtual void vf_0FC();
    virtual void vf_100();
    virtual void vf_104();
    virtual void vf_108();
    virtual void vf_10C();
    virtual void vf_110();
    virtual void vf_114();
    virtual void vf_118();
    virtual void vf_11C();
    virtual void vf_120();
    virtual void vf_124();
    virtual void vf_128();
    virtual void vf_12C();
    virtual void vf_130();
    virtual void vf_134();
    virtual void vf_138();
    virtual void vf_13C();
    virtual void vf_140();
    virtual void vf_144();
    virtual void vf_148();
    virtual void vf_14C();
    virtual void vf_150();
    virtual void vf_154();
    virtual void vf_158();
    virtual void vf_15C();
    virtual void vf_160();
    virtual void vf_164();
    virtual void vf_168();
    virtual void vf_16C();
    virtual void vf_170();
    virtual void vf_174();
    virtual void vf_178();
    virtual void vf_17C();
    virtual void vf_180();
    virtual void vf_184();
    virtual void vf_188();
    virtual void vf_18C();
    virtual void vf_190();
    virtual void vf_194();
    virtual void vf_198();
    virtual void vf_19C();
    virtual void vf_1A0();
    virtual void vf_1A4();
    virtual void vf_1A8();
    virtual void vf_1AC();
    virtual void vf_1B0();
    virtual void vf_1B4();
    virtual void vf_1B8();
    virtual void vf_1BC();
    virtual void vf_1C0();
    virtual void vf_1C4();
    virtual int vf_1C8();
    virtual void vf_1CC();
    virtual void vf_1D0();
    virtual void vf_1D4();
    virtual void vf_1D8();
    virtual void vf_1DC();
    virtual void vf_1E0();
    virtual void vf_1E4();
    virtual void vf_1E8(int a, int b);
};

struct JumpjetFootView : JumpjetFootVirtuals
{
    char              unknown_08C_pad[0x08C - 0x004];
    unsigned char     unknown_08C;       // +0x08C InWhichLayer `[EAX+0x8C]`
    unsigned char     unknown_08D;       // +0x08D InWhichLayer `[EDX+0x8D]`
    char              unknown_08E[0x09C - 0x08E];
    LocoCoord         Location;          // +0x09C HeadToCoord 0x54D9B0
    char              unknown_0A8[0x21C - 0x0A8];
    JumpjetPathView*  unknown_21C;       // +0x21C EndPiggyback `MOV EDX,[ECX+0x21C]`
    char              unknown_220[0x388 - 0x220];
    JumpjetFacingView PrimaryFacing;     // +0x388 DoTurn `ADD ECX,0x388`
    char              unknown_3A0[0x428 - 0x3A0];
    int               unknown_428;       // +0x428 EndPiggyback
    int               unknown_42C;       // +0x42C EndPiggyback
    char              unknown_430[0x6AD - 0x430];
    unsigned char     unknown_6AD;       // +0x6AD IsOkToEnd / EndPiggyback
    unsigned char     unknown_6AE;       // +0x6AE IsOkToEnd / EndPiggyback
};
GG_STATIC_ASSERT(offsetof(JumpjetFootView, unknown_08C) == 0x08C);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, unknown_08D) == 0x08D);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, Location) == 0x09C);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, unknown_21C) == 0x21C);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, PrimaryFacing) == 0x388);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, unknown_428) == 0x428);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, unknown_42C) == 0x42C);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, unknown_6AD) == 0x6AD);
GG_STATIC_ASSERT(offsetof(JumpjetFootView, unknown_6AE) == 0x6AE);

static inline JumpjetFootView* JumpjetFoot(JumpjetLocomotionClass* self)
{
    return (JumpjetFootView*)self->LinkedTo;
}

static inline bool JumpjetIsSet(const LocoCoord& c)
{
    return c.X != DAT_00ABC5A8.X || c.Y != DAT_00ABC5A8.Y || c.Z != DAT_00ABC5A8.Z;
}

// LIBRARY: OLE32!OleLoadFromStream, IAT 0x7E15F8 (declared by <ole2.h>).

// FUNCTION: GAMEMD 0x54B750
HRESULT __stdcall JumpjetLocomotionClass::Load(IStream* pStm)
{
    HRESULT hr = LocomotionClass::Load(pStm);
    if (hr >= 0) {
        new (this) JumpjetLocomotionClass(0);
        bool hasPiggyback;
        pStm->Read(&hasPiggyback, 1, 0);
        if (hasPiggyback)
            hr = OleLoadFromStream(pStm, IID_ILocomotion, (void**)&Piggybackee);
    }
    return hr;
}

// FUNCTION: GAMEMD 0x54DA00
HRESULT __stdcall JumpjetLocomotionClass::BeginPiggyback(ILocomotion* loco)
{
    if (!loco)
        return E_POINTER;
    if (Piggybackee == 0) {
        Piggybackee = loco;
        return S_OK;
    }
    return E_FAIL;
}

// FUNCTION: GAMEMD 0x54DB50
HRESULT __stdcall JumpjetLocomotionClass::PiggybackCLSID(CLSID* out)
{
    if (!out)
        return E_POINTER;
    if (Piggybackee) {
        IPersistPtr persist(Piggybackee);
        if (persist == 0)
            return E_FAIL;
        return persist->GetClassID(out);
    }
    IPersistPtr persist(static_cast<LocomotionClass*>(this));
    if (persist == 0)
        return E_FAIL;
    return persist->GetClassID(out);
}

// FUNCTION: GAMEMD 0x54DC60
HRESULT __stdcall JumpjetLocomotionClass::QueryInterface(REFIID riid, void** ppv)
{
    HRESULT hr = LocomotionClass::QueryInterface(riid, ppv);
    if (hr == E_NOINTERFACE) {
        if (riid == IID_IPiggyback)
            *ppv = static_cast<IPiggyback*>(this);
        if (*ppv == 0)
            return E_NOINTERFACE;
        AddRef();
        hr = S_OK;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x54B6E0
void __stdcall JumpjetLocomotionClass::DoTurn(unsigned long dir)
{
    unsigned long desired = dir;
    JumpjetFoot(this)->PrimaryFacing.FUN_004C9300(&desired);
}

// FUNCTION: GAMEMD 0x54DB00
bool __stdcall JumpjetLocomotionClass::IsOkToEnd()
{
    if (!IsMoving() && Piggybackee != 0 && !unknown_91
        && (!JumpjetFoot(this)->unknown_6AD || JumpjetFoot(this)->unknown_6AE))
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x54D9B0
LocoCoord __stdcall JumpjetLocomotionClass::HeadToCoord()
{
    LocoCoord c;
    if (unknown_50 == 0) {
        LocoCoord here = JumpjetFoot(this)->Location;
        c.X = here.X;
        c.Y = here.Y;
        c.Z = here.Z;
        return c;
    }
    c.X = DestCoord.X;
    c.Y = DestCoord.Y;
    c.Z = DestCoord.Z;
    return c;
}

// FUNCTION: GAMEMD 0x54AE60
LocoCoord __stdcall JumpjetLocomotionClass::Destination()
{
    LocoCoord c;
    if (IsMoving()) {
        c.X = DestCoord.X;
        c.Y = DestCoord.Y;
        c.Z = DestCoord.Z;
        return c;
    }
    c.X = DAT_00ABC5A8.X;
    c.Y = DAT_00ABC5A8.Y;
    c.Z = DAT_00ABC5A8.Z;
    return c;
}

// FUNCTION: GAMEMD 0x54D930 (partial: retail copies the returned coordinate into the local before comparing)
void __stdcall JumpjetLocomotionClass::MarkAllOccupationBits(int mark)
{
    if (mark == 0) {
        LocoCoord head;
        LocoCoord got = HeadToCoord();
        head.X = got.X;
        head.Y = got.Y;
        head.Z = got.Z;
        if (JumpjetIsSet(head) && (unknown_50 == 0 || unknown_90)) {
            JumpjetFoot(this)->vf_0F4(&head);
            unknown_90 = 0;
        }
    }
}

// FUNCTION: GAMEMD 0x54DA50
HRESULT __stdcall JumpjetLocomotionClass::EndPiggyback(ILocomotion** out)
{
    if (!out)
        return E_POINTER;
    if (JumpjetFoot(this)) {
        if (JumpjetFoot(this)->unknown_6AD || JumpjetFoot(this)->unknown_6AE) {
            JumpjetFoot(this)->unknown_6AD = 0;
            JumpjetFoot(this)->unknown_6AE = 0;
            if (!JumpjetFoot(this)->unknown_21C->unknown_1EC
                && JumpjetFoot(this)->vf_084()->unknown_5EC)
                JumpjetFoot(this)->vf_1E8(10, 0);
        }
        JumpjetFoot(this)->unknown_428 = 0;
        JumpjetFoot(this)->unknown_42C = 0;
    }
    if (Piggybackee) {
        *out = Piggybackee;
        Piggybackee.Detach();
        return S_OK;
    }
    return S_FALSE;
}

// FUNCTION: GAMEMD 0x54B8D0
int __stdcall JumpjetLocomotionClass::InWhichLayer()
{
    int height = JumpjetFoot(this)->vf_1C8();
    if (!JumpjetFoot(this)->unknown_08C) {
        LocoCoord here = JumpjetFoot(this)->Location;
        if (DriveMap().FUN_00565730(&here)->Flags & 0x100) {
            if (height >= DAT_00ABC5DC && !JumpjetFoot(this)->unknown_08D)
                height -= DAT_00ABC5DC;
        }
    }
    if (!JumpjetFoot(this)->vf_054())
        return 2;
    if (height == 0)
        return 2;
    return (height >= Height) + 3;
}

// FUNCTION: GAMEMD 0x54AD30 (partial 82.6%: retail CSEs the facing address into EAX for SetDesired and recomputes it for 0x4C9300)
HRESULT __stdcall JumpjetLocomotionClass::LinkToObject(FootClass* object)
{
    JumpjetFootView* foot = (JumpjetFootView*)object;
    TurnRate = foot->vf_084()->JumpjetTurnRate;
    Speed = foot->vf_084()->JumpjetSpeed;
    Climb = foot->vf_084()->JumpjetClimb;
    Crash = foot->vf_084()->JumpjetCrash;
    int height = foot->vf_084()->JumpjetHeight;
    int floor = DAT_00ABC5E8 + DAT_00ABC5E8;
    Height = height > floor ? height : floor;
    Accel = foot->vf_084()->JumpjetAccel;
    Wobbles = foot->vf_084()->JumpjetWobbles;
    unknown_38 = foot->vf_084()->unknown_D90;
    NoWobbles = foot->vf_084()->JumpjetNoWobbles;
    LocomotionFacing = JumpjetFacingView(TurnRate);
    {
        DirStruct turn;
        turn.Raw = 0x4000;
        LocomotionFacing.SetDesired(turn);
    }
    {
        DirStruct turn;
        turn.Raw = 0x4000;
        ((JumpjetFacingView&)LocomotionFacing).FUN_004C9300(&turn);
    }
    return LocomotionClass::LinkToObject(object);
}

// SYNTHETIC: GAMEMD 0x54DFA0 -- compiler-generated scalar deleting destructor.
// SYNTHETIC: GAMEMD 0x54DFF0 -- compiler-generated ILocomotion QI adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x54E000 -- compiler-generated ILocomotion AddRef adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x54E010 -- compiler-generated ILocomotion Release adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x54E020 -- compiler-generated IPiggyback QI adjustor thunk (this -= 0x18).
// SYNTHETIC: GAMEMD 0x54E030 -- compiler-generated IPiggyback AddRef adjustor thunk (this -= 0x18).
// SYNTHETIC: GAMEMD 0x54E040 -- compiler-generated IPiggyback Release adjustor thunk (this -= 0x18).
