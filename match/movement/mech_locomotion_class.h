// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; member and slot offsets cite the retail | YRpp-cross-check | behaviour-confirmed-name
// Mech entry instructions and the frozen M2 evidence packet. YRpp was consulted
// for candidate member names only; no YRpp layout or declarations were copied.
// Helper type names are address-local ABI views, not claims about original
// declaring classes.
#ifndef GG_MATCH_MOVEMENT_MECH_LOCOMOTION_CLASS_H
#define GG_MATCH_MOVEMENT_MECH_LOCOMOTION_CLASS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "loco_base.h"
#include "loco_foot.h"

struct MechCoord : LocoCoord {
    MechCoord() {}
    MechCoord(const LocoCoord& c) { X=c.X; Y=c.Y; Z=c.Z; }
    MechCoord& operator=(const MechCoord& c) { X=c.X; Y=c.Y; Z=c.Z; return *this; }
    void Set(int x, int y, int z) { X=x; Y=y; Z=z; }
};
GG_STATIC_ASSERT(sizeof(MechCoord)==0xC);
struct MechDirView {
    unsigned int Raw;
    MechDirView() {}
    MechDirView(unsigned long raw) : Raw(raw) {}
};
GG_STATIC_ASSERT(offsetof(MechDirView, Raw)==0);
GG_STATIC_ASSERT(sizeof(MechDirView)==4);
struct MechFacingView {
    char opaque[0x18];
    // FUNCTION: GAMEMD 0x4C9480 (decl; reloc) — address-local call view.
    bool IsRotating();
    // FUNCTION: GAMEMD 0x4C9220 (decl; reloc) — address-local call view.
    void SetDesired(const MechDirView& dir);
};
GG_STATIC_ASSERT(offsetof(MechFacingView, opaque)==0);
GG_STATIC_ASSERT(sizeof(MechFacingView)==0x18);
#define MECH_FACING(f) ((MechFacingView*)((char*)(f)+0x388))

struct MechCellCoord {
    short X; short Y;
    MechCellCoord() {}
    explicit MechCellCoord(const LocoCoord& c) : X((short)(c.X/256)), Y((short)(c.Y/256)) {}
};
GG_STATIC_ASSERT(offsetof(MechCellCoord, X)==0);
GG_STATIC_ASSERT(offsetof(MechCellCoord, Y)==2);
GG_STATIC_ASSERT(sizeof(MechCellCoord)==4);

// Narrow address-local linked-Foot slot view. These declarations pin only
// slots invoked by this Mech source; the full FootClass hierarchy is unknown.
struct MechFootSlots {
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
    virtual void vf_0F4(const LocoCoord*);
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
    virtual bool vf_380();
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
    virtual int vf_538();
};
GG_STATIC_ASSERT(sizeof(void*)==4);
GG_STATIC_ASSERT(sizeof(MechFootSlots)==4);

// Evidence-model vtable prefix: the Mech call sites use these byte offsets
// from the linked FootClass primary address point. Unnamed slots remain opaque;
// this prefix view does not claim the complete FootClass table extent.
struct MechFootVtableEvidencePrefix {
    void* unknown_000[0xF4 / 4];
    void* slot_0F4;
    void* unknown_0F8[(0x1D4 - 0x0F8) / 4];
    void* slot_1D4;
    void* slot_1D8;
    void* unknown_1DC[(0x37C - 0x1DC) / 4];
    void* slot_37C;
    void* slot_380;
    void* unknown_384[(0x538 - 0x384) / 4];
    void* slot_538;
};
GG_STATIC_ASSERT(offsetof(MechFootVtableEvidencePrefix, slot_0F4)==0x0F4);
GG_STATIC_ASSERT(offsetof(MechFootVtableEvidencePrefix, slot_1D4)==0x1D4);
GG_STATIC_ASSERT(offsetof(MechFootVtableEvidencePrefix, slot_1D8)==0x1D8);
GG_STATIC_ASSERT(offsetof(MechFootVtableEvidencePrefix, slot_37C)==0x37C);
GG_STATIC_ASSERT(offsetof(MechFootVtableEvidencePrefix, slot_380)==0x380);
GG_STATIC_ASSERT(offsetof(MechFootVtableEvidencePrefix, slot_538)==0x538);
GG_STATIC_ASSERT(sizeof(MechFootVtableEvidencePrefix)==0x53C);

struct MechFootLayoutView : MechFootSlots {
    char unknown_004[0x9C-4];
    LocoCoord Location;
    char unknown_0A8[0x388-0xA8];
    MechFacingView PrimaryFacing;
};
GG_STATIC_ASSERT(offsetof(MechFootLayoutView, unknown_004)==0x4);
GG_STATIC_ASSERT(offsetof(MechFootLayoutView, Location)==0x9C);
GG_STATIC_ASSERT(offsetof(MechFootLayoutView, PrimaryFacing)==0x388);
inline MechFootLayoutView* MechFoot(FootClass* f) { return (MechFootLayoutView*)f; }

struct MechCellLayoutView {
    char unknown_000[0x140];
    unsigned int Flags;
};
GG_STATIC_ASSERT(offsetof(MechCellLayoutView, unknown_000)==0);
GG_STATIC_ASSERT(offsetof(MechCellLayoutView, Flags)==0x140);
inline MechCellLayoutView* MechCellAt(const MechCoord& c) {
    return (MechCellLayoutView*)DAT_0087F7E8.GetCellAt(c);
}
inline void MechUnmarkAt(MechFootLayoutView* f, const MechCoord& c) { f->vf_0F4(&c); }

// FUNCTION: GAMEMD 0x6D2120 (decl; reloc), address-scoped integer helper.
int __fastcall LocoHeightScale(int value);
// GLOBAL: GAMEMD 0xABEE10
extern LocoCoord DAT_00ABEE10;
// GLOBAL: GAMEMD 0xABEE50
extern int DAT_00ABEE50;
// GLOBAL: GAMEMD 0x7E9AA0; GUID used by GetClassID.
extern "C" const CLSID CLSID_MechLocomotion;

// VTABLE: GAMEMD 0x7EDC38 — primary IPersistStream address point, 10 slots.
// VTABLE: GAMEMD 0x7EDB6C — secondary ILocomotion address point (+4), 50 slots.
// COFF slot checks are in mech-vtable-verification.json. The primary deleting
// destructor slot follows the recorded SEARCH_LIBRARY weak default to the exact
// matched ??_G body; this is conditional on no stronger link-time override.
class MechLocomotionClass : public LocomotionClass {
public:
    MechLocomotionClass();
    MechLocomotionClass(int) : LocomotionClass(0) {}
    virtual ~MechLocomotionClass() {}
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual int Size();
    virtual bool __stdcall IsMoving();
    virtual LocoCoord __stdcall Destination();
    virtual LocoCoord __stdcall HeadToCoord();
    virtual bool __stdcall Process();
    virtual void __stdcall MoveTo(LocoCoord to);
    virtual void __stdcall StopMoving();
    virtual void __stdcall DoTurn(unsigned long dir);
    virtual int __stdcall InWhichLayer();
    virtual void __stdcall ForceImmediateDestination(LocoCoord coord);
    virtual bool __stdcall IsMovingNow();
    virtual void __stdcall MarkAllOccupationBits(int mark);
    virtual bool __stdcall IsMovingHere(LocoCoord to);
    // FUNCTION: GAMEMD 0x5B01C0 (decl; reloc), unowned movement-step binding.
    void MovementStep(int arg);
    LocoCoord unknown_18;
    LocoCoord MoveHeadTo;
    bool Moving;
    char unknown_31[3];
};
GG_STATIC_ASSERT(offsetof(MechLocomotionClass, unknown_18)==0x18);
GG_STATIC_ASSERT(offsetof(MechLocomotionClass, MoveHeadTo)==0x24);
GG_STATIC_ASSERT(offsetof(MechLocomotionClass, Moving)==0x30);
GG_STATIC_ASSERT(offsetof(MechLocomotionClass, unknown_31)==0x31);
GG_STATIC_ASSERT(sizeof(MechLocomotionClass)==0x34);
#endif
