// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   WalkLocomotionClass, read off the user's retail gamemd.exe v1.001.
//   RTTI `.?AVWalkLocomotionClass@@` (TD 0x847BF0) has three locators: base
//   offset 0 (IPersistStream table 0x7F6AC4, 10 slots), +4 (ILocomotion table
//   0x7F69F8, 50 slots) and +0x18 (IPiggyback table 0x7F69D4, 8 slots), so the
//   class is LocomotionClass plus IPiggyback, like DropPodLocomotionClass.
//   Constructor 0x75AA90 (calls the LocomotionClass constructor 0x55A6C0, then
//   stores the three vptrs); sizeof 0x3C from `PUSH 0x3C` at 0x6C47BC and Size
//   0x75CBD0. Slot owners from `ghidra memory read` of the three tables.
//   This header is the one compiled WalkLocomotionClass.
//   Method names are the ILocomotion/IPiggyback slot names shared with
//   loco_base.h; members keep placeholder names unless a reader fixes a role.
#ifndef GG_MATCH_MOVEMENT_WALK_LOCOMOTION_CLASS_H
#define GG_MATCH_MOVEMENT_WALK_LOCOMOTION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "loco_base.h"
#include "loco_com.h"
#include "loco_foot.h"

// GLOBAL: GAMEMD 0xB45BE8 - the file's empty coordinate (0xB45BE8/EC/F0).
extern LocoCoord DAT_00B45BE8;

inline bool WalkIsEmpty(const LocoCoord& c)
{
    return c.X == DAT_00B45BE8.X && c.Y == DAT_00B45BE8.Y && c.Z == DAT_00B45BE8.Z;
}

// A coordinate with a user-declared copy, as handed to the cell lookup.
struct WalkCoord : LocoCoord
{
    WalkCoord() {}
    WalkCoord(const LocoCoord& c) { X = c.X; Y = c.Y; Z = c.Z; }
};
GG_STATIC_ASSERT(sizeof(WalkCoord) == 0xC);

// A binary-angle direction passed by address to the facing.
struct WalkDirView
{
    unsigned int Raw;
    WalkDirView(unsigned long raw) : Raw(raw) {}
};
GG_STATIC_ASSERT(sizeof(WalkDirView) == 4);

struct WalkFacingView
{
    char opaque[0x18];
    // FUNCTION: GAMEMD 0x4C9300 (decl; reloc) - sets the desired facing.
    void Fun_004C9300(const WalkDirView& dir);
};
GG_STATIC_ASSERT(sizeof(WalkFacingView) == 0x18);

// Address-local view of the linked FootClass: the call sites read these
// primary-table slots (byte offsets) and fields.
struct WalkFootSlots
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
    virtual void vf_054();
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
    virtual void vf_084();
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
    virtual void vf_1C8();
    virtual void vf_1CC();
    virtual void vf_1D0();
    virtual bool vf_1D4();
    virtual bool vf_1D8();
    virtual void vf_1DC();
    virtual void vf_1E0();
    virtual void vf_1E4();
    virtual void vf_1E8();
    virtual void vf_1EC();
    virtual void vf_1F0();
    virtual void vf_1F4();
    virtual void vf_1F8();
    virtual void vf_1FC();
    virtual void vf_200();
    virtual void vf_204();
    virtual void vf_208();
    virtual void vf_20C();
    virtual void vf_210();
    virtual void vf_214();
    virtual void vf_218();
    virtual void vf_21C();
    virtual void vf_220();
    virtual void vf_224();
    virtual void vf_228();
    virtual void vf_22C();
    virtual void vf_230();
    virtual void vf_234();
    virtual void vf_238();
    virtual void vf_23C();
    virtual void vf_240();
    virtual void vf_244();
    virtual void vf_248();
    virtual void vf_24C();
    virtual void vf_250();
    virtual void vf_254();
    virtual void vf_258();
    virtual void vf_25C();
    virtual void vf_260();
    virtual void vf_264();
    virtual void vf_268();
    virtual void vf_26C();
    virtual void vf_270();
    virtual void vf_274();
    virtual void vf_278();
    virtual void vf_27C();
    virtual void vf_280();
    virtual void vf_284();
    virtual void vf_288();
    virtual void vf_28C();
    virtual void vf_290();
    virtual void vf_294();
    virtual void vf_298();
    virtual void vf_29C();
    virtual void vf_2A0();
    virtual void vf_2A4();
    virtual void vf_2A8();
    virtual void vf_2AC();
    virtual void vf_2B0();
    virtual void vf_2B4();
    virtual void vf_2B8();
    virtual void vf_2BC();
    virtual void vf_2C0();
    virtual void vf_2C4();
    virtual void vf_2C8();
    virtual void vf_2CC();
    virtual void vf_2D0();
    virtual void vf_2D4();
    virtual void vf_2D8();
    virtual void vf_2DC();
    virtual void vf_2E0();
    virtual void vf_2E4();
    virtual void vf_2E8();
    virtual void vf_2EC();
    virtual void vf_2F0();
    virtual void vf_2F4();
    virtual void vf_2F8();
    virtual void vf_2FC();
    virtual void vf_300();
    virtual void vf_304();
    virtual void vf_308();
    virtual void vf_30C();
    virtual void vf_310();
    virtual void vf_314();
    virtual void vf_318();
    virtual void vf_31C();
    virtual void vf_320();
    virtual void vf_324();
    virtual void vf_328();
    virtual void vf_32C();
    virtual void vf_330();
    virtual void vf_334();
    virtual void vf_338();
    virtual void vf_33C();
    virtual void vf_340();
    virtual void vf_344();
    virtual void vf_348();
    virtual void vf_34C();
    virtual void vf_350();
    virtual void vf_354();
    virtual void vf_358();
    virtual void vf_35C();
    virtual void vf_360();
    virtual void vf_364();
    virtual void vf_368();
    virtual void vf_36C();
    virtual void vf_370();
    virtual void vf_374();
    virtual void vf_378();
    virtual bool vf_37C();
    virtual void vf_380();
    virtual void vf_384();
    virtual void vf_388();
    virtual void vf_38C();
    virtual void vf_390();
    virtual void vf_394();
    virtual void vf_398();
    virtual void vf_39C();
    virtual void vf_3A0();
    virtual void vf_3A4();
    virtual void vf_3A8();
    virtual void vf_3AC();
    virtual void vf_3B0();
    virtual void vf_3B4();
    virtual void vf_3B8();
    virtual void vf_3BC();
    virtual void vf_3C0();
    virtual void vf_3C4();
    virtual void vf_3C8();
    virtual void vf_3CC();
    virtual void vf_3D0();
    virtual void vf_3D4();
    virtual void vf_3D8();
    virtual void vf_3DC();
    virtual void vf_3E0();
    virtual void vf_3E4();
    virtual void vf_3E8();
    virtual void vf_3EC();
    virtual void vf_3F0();
    virtual void vf_3F4();
    virtual void vf_3F8();
    virtual void vf_3FC();
    virtual void vf_400();
    virtual void vf_404();
    virtual void vf_408();
    virtual void vf_40C();
    virtual void vf_410();
    virtual void vf_414();
    virtual void vf_418();
    virtual void vf_41C();
    virtual void vf_420();
    virtual void vf_424();
    virtual void vf_428();
    virtual void vf_42C();
    virtual void vf_430();
    virtual void vf_434();
    virtual void vf_438();
    virtual void vf_43C();
    virtual void vf_440();
    virtual void vf_444();
    virtual void vf_448();
    virtual void vf_44C();
    virtual void vf_450();
    virtual void vf_454();
    virtual void vf_458();
    virtual void vf_45C();
    virtual void vf_460();
    virtual void vf_464();
    virtual void vf_468();
    virtual void vf_46C();
    virtual void vf_470();
    virtual void vf_474();
    virtual void vf_478();
    virtual void vf_47C();
    virtual void vf_480();
    virtual void vf_484();
    virtual void vf_488();
    virtual void vf_48C();
    virtual void vf_490();
    virtual void vf_494();
    virtual void vf_498();
    virtual void vf_49C();
    virtual void vf_4A0();
    virtual void vf_4A4();
    virtual void vf_4A8();
    virtual void vf_4AC();
    virtual void vf_4B0();
    virtual void vf_4B4();
    virtual void vf_4B8();
    virtual void vf_4BC();
    virtual void vf_4C0();
    virtual void vf_4C4();
    virtual void vf_4C8();
    virtual void vf_4CC();
    virtual void vf_4D0();
    virtual void vf_4D4();
    virtual void vf_4D8();
    virtual void vf_4DC();
    virtual void vf_4E0();
    virtual void vf_4E4();
    virtual void vf_4E8();
    virtual void vf_4EC();
    virtual void vf_4F0();
    virtual void vf_4F4();
    virtual void vf_4F8();
    virtual void vf_4FC();
    virtual void vf_500();
    virtual void vf_504();
    virtual void vf_508();
    virtual void vf_50C();
    virtual void vf_510();
    virtual void vf_514();
    virtual void vf_518();
    virtual void vf_51C();
    virtual void vf_520();
    virtual void vf_524();
    virtual void vf_528();
    virtual void vf_52C();
    virtual void vf_530();
    virtual void vf_534();
    virtual void vf_538();
    virtual void vf_53C();
    virtual void vf_540();
    virtual void vf_544();
    virtual void vf_548();
    virtual void vf_54C();
};
GG_STATIC_ASSERT(sizeof(WalkFootSlots) == 4);

struct WalkFootView : WalkFootSlots
{
    char           unknown_004[0x9C - 0x4];
    LocoCoord      Location;                          // +0x09C
    char           unknown_0A8[0x388 - 0xA8];
    WalkFacingView PrimaryFacing;                     // +0x388
    char           unknown_3A0[0x578 - 0x3A0];
    double         unknown_578;                       // +0x578
    char           unknown_580[0x6AD - 0x580];
    bool           unknown_6AD;                       // +0x6AD
};
GG_STATIC_ASSERT(offsetof(WalkFootView, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(WalkFootView, PrimaryFacing) == 0x388);
GG_STATIC_ASSERT(offsetof(WalkFootView, unknown_578) == 0x578);
GG_STATIC_ASSERT(offsetof(WalkFootView, unknown_6AD) == 0x6AD);
inline WalkFootView* WalkFoot(FootClass* f) { return (WalkFootView*)f; }

struct WalkCellView
{
    char         unknown_000[0x140];
    unsigned int Flags;                               // +0x140
};
GG_STATIC_ASSERT(offsetof(WalkCellView, Flags) == 0x140);
inline WalkCellView* WalkCellAt(const WalkCoord& c)
{
    return (WalkCellView*)DAT_0087F7E8.GetCellAt(c);
}

// FUNCTION: GAMEMD 0x6D2120 (decl; reloc), address-scoped integer helper.
int LocoHeightScale(int value);

// VTABLE: GAMEMD 0x7F6AC4
// VTABLE: GAMEMD 0x7F69F8
// VTABLE: GAMEMD 0x7F69D4
class WalkLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
    // FUNCTION: GAMEMD 0x75AA90
    WalkLocomotionClass();
    WalkLocomotionClass(int) : LocomotionClass(0) {}
    // The scalar deleting destructor 0x75CBE0 is compiler output around this
    // inline body; the standalone body 0x75AB00 is scored elsewhere.
    virtual ~WalkLocomotionClass() {}

    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);   // 0x75C7F0
    virtual ULONG   __stdcall AddRef();                                   // 0x75CB80
    virtual ULONG   __stdcall Release();                                  // 0x75CB90

    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 0x75C640
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 0x75C680
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 0x75C700
    virtual int Size();                                                   // 0x75CBD0

    virtual bool __stdcall IsMoving();                                    // 4   0x75AB30
    virtual LocoCoord __stdcall Destination();                            // 5   0x75ABA0
    virtual LocoCoord __stdcall HeadToCoord();                            // 6   0x75AC00
    virtual bool __stdcall Process();                                     // 16  0x75AC80
    virtual void __stdcall MoveTo(LocoCoord to);                          // 17  0x75ACB0
    virtual void __stdcall StopMoving();                                  // 18  0x75ADA0
    virtual void __stdcall DoTurn(unsigned long dir);                     // 19  0x75AE00
    virtual int __stdcall InWhichLayer();                                 // 29  0x75C7E0
    virtual void __stdcall ForceImmediateDestination(LocoCoord coord);    // 30  0x75AE30
    virtual bool __stdcall IsMovingNow();                                 // 32  0x75AB40
    virtual void __stdcall MarkAllOccupationBits(int mark);               // 39  0x75CA30
    virtual bool __stdcall IsMovingHere(LocoCoord to);                    // 40  0x75CA80
    virtual bool __stdcall IsReallyMovingNow();                           // 42  0x75CB20
    virtual void __stdcall StopMovementAnimation();                       // 43  0x75CBC0
    virtual void __stdcall ClearCoords();                                 // 44  0x75CB30

    virtual HRESULT __stdcall BeginPiggyback(ILocomotion* loco);          // 0x75C850
    virtual HRESULT __stdcall EndPiggyback(ILocomotion** out);            // 0x75C8A0
    virtual bool __stdcall IsOkToEnd();                                   // 0x75C8E0
    virtual HRESULT __stdcall PiggybackCLSID(CLSID* out);                 // 0x75C920
    virtual bool __stdcall IsPiggybacking();                              // 0x75CBA0

    // FUNCTION: GAMEMD 0x75AEC0 (decl; reloc) - the per-frame movement step.
    void MovementStep(int arg);
    // FUNCTION: GAMEMD 0x75C240 (decl; reloc) - takes a coordinate by address.
    void Fun_0075C240(const WalkCoord& coord);

    // +0x18 is the IPiggyback vptr.
    LocoCoord      unknown_1C;   // +0x1C  returned by Destination()
    LocoCoord      MoveHeadTo;        // +0x28  returned by HeadToCoord()
    bool           unknown_34;        // +0x34  returned by IsMoving()
    bool           unknown_35;        // +0x35  set around MovementStep in Process()
    bool           unknown_36;        // +0x36  returned by IsReallyMovingNow()
    char           unknown_37;        // +0x37
    ILocomotionPtr Piggybackee;       // +0x38
};
GG_STATIC_ASSERT(offsetof(WalkLocomotionClass, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(WalkLocomotionClass, MoveHeadTo) == 0x28);
GG_STATIC_ASSERT(offsetof(WalkLocomotionClass, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(WalkLocomotionClass, unknown_35) == 0x35);
GG_STATIC_ASSERT(offsetof(WalkLocomotionClass, unknown_36) == 0x36);
GG_STATIC_ASSERT((size_t)&reinterpret_cast<const char&>(((WalkLocomotionClass*)0)->Piggybackee) == 0x38);
GG_STATIC_ASSERT(sizeof(WalkLocomotionClass) == 0x3C);

#endif  // GG_MATCH_MOVEMENT_WALK_LOCOMOTION_CLASS_H
