// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; YRpp consulted for names only.
// Address-local, non-owning Rocket views. Listed fields and slots are limited
// to the Rocket call sites; these are not complete declarations of other objects.
#ifndef GG_MATCH_MOVEMENT_ROCKET_LOCOMOTION_VIEWS_H
#define GG_MATCH_MOVEMENT_ROCKET_LOCOMOTION_VIEWS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "loco_interfaces.h"
// Only the listed call-site slots are used by the Rocket rows. Placeholder
// declarations between them preserve slot indices; their C++ signatures are
// not recovered and must not be used as ABI evidence. This prefix view is not
// a complete FootClass definition.
struct RocketNoInit {};
struct RocketHouseView;
struct RocketTypeView {
    char unknown_000[0x52C];
    void* unknown_52C;
    char unknown_530[0x148];
    int unknown_678;
};
GG_STATIC_ASSERT(offsetof(RocketTypeView,unknown_52C)==0x52C);
GG_STATIC_ASSERT(offsetof(RocketTypeView,unknown_678)==0x678);
struct RocketCoordMapView;
struct RocketObjectView;
// A returned cell pair. The empty user-declared constructor models the hidden
// return pointer observed at Rocket vcall sites 0x662613, 0x6626B8 and 0x662F92.
struct RocketCellCoord { short X; short Y; RocketCellCoord() {} };
GG_STATIC_ASSERT(offsetof(RocketCellCoord,X)==0); GG_STATIC_ASSERT(offsetof(RocketCellCoord,Y)==2); GG_STATIC_ASSERT(sizeof(RocketCellCoord)==4);
// The empty constructor models the out-pointer return observed at 0x663470
// before the caller reads Raw from the returned address.
struct RocketDirView { unsigned int Raw; RocketDirView() {} };
GG_STATIC_ASSERT(offsetof(RocketDirView,Raw)==0); GG_STATIC_ASSERT(sizeof(RocketDirView)==4);
struct RocketFacingView { char opaque[0x18]; RocketDirView Current(); void SetDesired(short* dir); };
GG_STATIC_ASSERT(sizeof(RocketFacingView)==0x18);
struct RocketAttachInner { char unknown_00[4]; bool Check(); };
GG_STATIC_ASSERT(sizeof(RocketAttachInner)==4);
struct RocketAttachView { char unknown_000[0x150]; RocketAttachInner inner; };
GG_STATIC_ASSERT(offsetof(RocketAttachView,inner)==0x150);
struct RocketMissileSpec { int unknown_00; int unknown_04; float unknown_08; float unknown_0C; float unknown_10; int unknown_14; float unknown_18; int unknown_1C; char unknown_20[0xC]; char unknown_2C; char unknown_2D[3]; void* Type; };
GG_STATIC_ASSERT(offsetof(RocketMissileSpec,unknown_00)==0); GG_STATIC_ASSERT(offsetof(RocketMissileSpec,unknown_04)==4); GG_STATIC_ASSERT(offsetof(RocketMissileSpec,unknown_08)==8); GG_STATIC_ASSERT(offsetof(RocketMissileSpec,unknown_0C)==0xC); GG_STATIC_ASSERT(offsetof(RocketMissileSpec,unknown_10)==0x10); GG_STATIC_ASSERT(offsetof(RocketMissileSpec,unknown_14)==0x14); GG_STATIC_ASSERT(offsetof(RocketMissileSpec,unknown_18)==0x18); GG_STATIC_ASSERT(offsetof(RocketMissileSpec,unknown_1C)==0x1C); GG_STATIC_ASSERT(offsetof(RocketMissileSpec,unknown_2C)==0x2C); GG_STATIC_ASSERT(offsetof(RocketMissileSpec,Type)==0x30); GG_STATIC_ASSERT(sizeof(RocketMissileSpec)==0x34);
// Prefix at the rules pointer read from 0x8871E0. Only these three Rocket
// parameter blocks are represented; this is not a complete rules layout.
struct RocketRulesView { char unknown_000[0x4B0]; RocketMissileSpec SpecA; RocketMissileSpec SpecB; RocketMissileSpec SpecC; };
GG_STATIC_ASSERT(offsetof(RocketRulesView,SpecA)==0x4B0); GG_STATIC_ASSERT(offsetof(RocketRulesView,SpecB)==0x4E4); GG_STATIC_ASSERT(offsetof(RocketRulesView,SpecC)==0x518); GG_STATIC_ASSERT(sizeof(RocketRulesView)==0x54C);
struct RocketAnimTypeView;
struct RocketAnimTypeArray { int unknown_00; RocketAnimTypeView** Items; };
GG_STATIC_ASSERT(offsetof(RocketAnimTypeArray,Items)==4); GG_STATIC_ASSERT(sizeof(RocketAnimTypeArray)==8);
// Opaque allocation used by Rocket: the entry allocates 0x1C8 bytes and calls
// the retail constructor with seven stack arguments (RET 0x1C).
struct RocketAnimView { char opaque[0x1C8]; RocketAnimView(void*, LocoCoord*, int,int,int,int,char); };
GG_STATIC_ASSERT(sizeof(RocketAnimView)==0x1C8);
struct RocketObjectView;
struct RocketMapView { char unknown_00[4]; void Submit(FootClass* foot); bool FUN_00568300(RocketCellCoord* cell); };
GG_STATIC_ASSERT(sizeof(RocketMapView)==4);
struct RocketFootVirtuals {
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
    // Slot 0x12: call site uses a hidden LocoCoord return.
    virtual LocoCoord vf_048();
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
    // Slot 0x21: call site uses a pointer result. Only Type fields +0x52C/+0x678 are read.
    virtual RocketTypeView* vf_084();
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
    virtual void vf_0F4();
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
    // Slot 0x49: caller passes one int; cleanup and this adjustment are entry-confirmed.
    virtual void vf_124(int arg);
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
    // Slot 0x6D: caller passes a LocoCoord pointer.
    virtual void vf_1B4(LocoCoord* coord);
    // Slot 0x6E: caller supplies a 4-byte out slot and consumes EAX as its address.
    virtual RocketCellCoord vf_1B8();
    virtual void vf_1BC();
    virtual void vf_1C0();
    virtual void vf_1C4();
    // Slot 0x72: caller consumes an integer result.
    virtual int vf_1C8();
    virtual void vf_1CC();
    virtual void vf_1D0();
    virtual void vf_1D4();
    virtual void vf_1D8();
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
    // Slot 0xBD: call site consumes the returned 4-byte cell pair by value.
    virtual RocketCellCoord vf_2F4();
};

struct RocketFootView : RocketFootVirtuals {
    char unknown_004[0x06C-4]; int unknown_06C;
    char unknown_070[0x090-0x070]; bool unknown_090;
    char unknown_091[0x09C-0x091]; LocoCoord Location;
    char unknown_0A8[0x2D4-0x0A8]; RocketAttachView* Attachment;
    char unknown_2D8[0x388-0x2D8]; RocketFacingView PrimaryFacing;
    char unknown_3A0[0x560-0x3A0]; RocketCellCoord unknown_560;
    char unknown_564[0x6C4-0x564]; void* Type;
};
GG_STATIC_ASSERT(sizeof(RocketFootVirtuals)==4);
GG_STATIC_ASSERT(offsetof(RocketFootView,unknown_06C)==0x06C);
GG_STATIC_ASSERT(offsetof(RocketFootView,unknown_090)==0x090);
GG_STATIC_ASSERT(offsetof(RocketFootView,Location)==0x09C);
GG_STATIC_ASSERT(offsetof(RocketFootView,Attachment)==0x2D4);
GG_STATIC_ASSERT(offsetof(RocketFootView,PrimaryFacing)==0x388);
GG_STATIC_ASSERT(offsetof(RocketFootView,unknown_560)==0x560);
GG_STATIC_ASSERT(offsetof(RocketFootView,Type)==0x6C4);
GG_STATIC_ASSERT(sizeof(RocketFootView)==0x6C8);
// Slot +0x1B8 is used indirectly by Process. Its receiver and returned
// two-short cell value are modeled from the caller; original owner is unknown.
#endif
