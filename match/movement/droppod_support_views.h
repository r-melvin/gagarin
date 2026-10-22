// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: pinned retail gamemd.exe v1.001 entry-origin member accesses and
//             slot calls in the DropPod cluster only.
// These are address-local access/slot views used by DropPod bodies. They do
// not claim complete FootClass, HouseClass, ObjectClass or AnimClass ownership
// or size. Every named data offset is asserted below.
#ifndef GG_MATCH_MOVEMENT_DROPPOD_SUPPORT_VIEWS_H
#define GG_MATCH_MOVEMENT_DROPPOD_SUPPORT_VIEWS_H

#include <stddef.h>
#include "loco_interfaces.h"
#include "loco_com.h"
#include "../core/coordinate_storage_008a0820.h"
#include "../_rt/gg_static_assert.h"

struct DropPodObjectView;
struct DropPodHouseView;

struct DropPodHouseView
{
    char unknown_00[4];
    // FUNCTION: GAMEMD 0x4F9A90 (decl; reloc), argument shape established at DropPod call.
    bool IsAlliedWith(DropPodObjectView* object);
};

struct DropPodObjectView
{
    // FUNCTION: GAMEMD 0x47C3D0 (decl; reloc), call shape from DropPod's map-cell path.
    DropPodObjectView* FindTechnoNearestTo(LocoPoint2D* offset, bool alt,
                                           DropPodObjectView* exclude);
};

struct DropPodFacingView
{
    char unknown_00[0x18];
    // FUNCTION: GAMEMD 0x4C9300 (decl; reloc), used by DropPod MoveTo.
    void Set(short* direction);
};
GG_STATIC_ASSERT(sizeof(DropPodFacingView) == 0x18);

// Minimal vtable prefix through slot 0x484. Unused slots are placeholders;
// only the called slot signatures below are modeled from DropPod call sites.
struct DropPodFootVirtuals
{
    virtual long __stdcall vf_000(const void* riid, void** ppv);
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
    virtual bool vf_0D8(LocoCoord* coord, int dir);
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
    virtual void vf_174(const CoordinateStorage_008A0820* coord, int a, int b);
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
    virtual void vf_1B4(LocoCoord* coord);
    virtual void vf_1B8();
    virtual void vf_1BC();
    virtual void vf_1C0();
    virtual void vf_1C4();
    virtual int vf_1C8();
    virtual void vf_1CC(int height);
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
    virtual void vf_37C();
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
    virtual bool vf_484(int a, int b);
};

struct DropPodFootView : DropPodFootVirtuals
{
    char unknown_004[0x09C - 0x004];
    LocoCoord Location;                  // +0x09C
    char unknown_0A8[0x21C - 0x0A8];
    DropPodHouseView* House;             // +0x21C
    char unknown_220[0x388 - 0x220];
    DropPodFacingView PrimaryFacing;     // +0x388
    char unknown_3A0[0x674 - 0x3A0];
    ILocomotionPtr Locomotor;             // +0x674
};
GG_STATIC_ASSERT(offsetof(DropPodFootView, Location) == 0x09C);
GG_STATIC_ASSERT(offsetof(DropPodFootView, House) == 0x21C);
GG_STATIC_ASSERT(offsetof(DropPodFootView, PrimaryFacing) == 0x388);
GG_STATIC_ASSERT((size_t)&reinterpret_cast<const char&>(((DropPodFootView*)0)->Locomotor) == 0x674);

struct DropPodAnimAllocationView
{
    char storage[0x1C8];
    // FUNCTION: GAMEMD 0x421EA0 (decl; reloc); constructor call ABI view.
    DropPodAnimAllocationView(void* type, LocoCoord* coord, int a, int b, int c, int d, char e);
    DropPodAnimAllocationView(void* type, const LocoCoord& coord, int a, int b, int c, int d, int e);
};
GG_STATIC_ASSERT(sizeof(DropPodAnimAllocationView) == 0x1C8);

#endif
