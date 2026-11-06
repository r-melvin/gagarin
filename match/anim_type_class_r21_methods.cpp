// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   AnimTypeClass members read off retail gamemd.exe v1.001 (vtable 0x7E3608).
//   Address index: 0x4289D0, 0x428EA0
#include "FUNCTION.H"
#include <new.h>
#include "vector_class_operations.h"
#include "terrain_common_views.h"
#include "ccfile_class.h"
#include "_layout/swizzle_manager_class.h"
#include "shared_constants_globals.h"

// GLOBAL: GAMEMD 0xB0F670 -- the registry every abstract object leaves when destroyed.
extern DynamicVectorClass<AbstractClass*> DAT_00B0F670;
// GLOBAL: GAMEMD 0x8B4150 -- AnimTypeClass::Array.
extern DynamicVectorClass<AnimTypeClass*> DAT_008B4150;
// GLOBAL: GAMEMD 0xA8ED6B -- when set, base-node bookkeeping is skipped.
extern bool DAT_00A8ED6B;
// GLOBAL: GAMEMD 0x822CF8 -- the theater last loaded.
extern int DAT_00822CF8;
// FUNCTION: GAMEMD 0x5F96B0 (decl; reloc)
void FUN_005F96B0(char* name, int idxTheater);
// FUNCTION: GAMEMD 0x5F9710 (decl; reloc)
void FUN_005F9710(char* name);
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- the debug trace print, __cdecl.
void __cdecl FUN_004068E0(const char* format, const char* name);
void __cdecl operator delete(void* p);

// FUNCTION: GAMEMD 0x427530
AnimTypeClass::AnimTypeClass(const char* id) throw()
    : ObjectTypeClass(id), ArrayIndex(-1), MiddleFrameIndex(0), MiddleFrameWidth(0), MiddleFrameHeight(0),
      unknown_2A4(0), Damage(0), Rate(1), Start(0), LoopStart(0), LoopEnd(0), End(0), LoopCount(0), Next(0),
      SpawnsParticle(-1), NumParticles(0), DetailLevel(0), TranslucencyDetailLevel(0),
      RandomLoopDelay(0, 0), RandomRate(0, 0), Translucency(0), Spawns(0), SpawnCount(0), Report(-1),
      StopSound(-1), BounceAnim(0), ExpireAnim(0), TrailerAnim(0), TrailerSeperation(0),
      Elasticity(0.800000011920929), MinZVel(3.5), unknown_double_320(3.5), MaxXYVel(15.0), Warhead(0),
      DamageRadius(0), TiberiumSpawnType(0), TiberiumSpreadRadius(0), YSortAdjust(0), YDrawOffset(0),
      ZAdjust(0), MakeInfantry(-1), RunningFrames(0), IsFlamingGuy(false), IsVeins(false), IsMeteor(false),
      TiberiumChainReaction(false), IsTiberium(false), HideIfNoOre(false), Bouncer(false), Tiled(false),
      ShouldUseCellDrawer(true), UseNormalLight(false), DemandLoad(false), FreeLoad(false),
      IsAnimatedTiberium(false), AltPalette(false), Normalized(false), Layer(3), DoubleThick(false),
      Flat(false), Translucent(false), Scorch(false), Flamer(false), Crater(false), ForceBigCraters(false),
      Sticky(false), PingPong(false), Reverse(false), Shadow(false), PsiWarning(false),
      ShouldFogRemove(true)
{
    vf_rtti_5();
    IsLogic = true;
    RadarInvisible = true;
    Selectable = false;
    LegalTarget = false;
    Insignificant = true;
    Immune = true;
    AllowCellContent = false;
    DAT_008B4150.AddItem(this);
    DAT_00B0F670.AddItem(this);
    ArrayIndex = DAT_008B4150.FindItemIndex(this);
}

// FUNCTION: GAMEMD 0x427A80
// Slot 24: bring the type's art into line with the theater being entered.
void AnimTypeClass::vf_24(int idxTheater)
{
    char path[0x200];

    if (DAT_00A8ED6B || idxTheater != DAT_00822CF8) {
        if (Theater && !DemandLoad) {
            if (Image && ImageAllocated) {
                operator delete(Image);
                ImageAllocated = false;
            }
            Image = 0;
            _makepath(path, 0, 0, ID, MapObjTheaters[idxTheater].Extension);
            Image = MapObjLoadShape(path, 1);
        } else if (NewTheater) {
            vf_40(idxTheater);
        }
    }
}

// FUNCTION: GAMEMD 0x427B50
// Slot 40: load the art for the given theater (unless it is demand-loaded) and derive the frame bookkeeping.
void AnimTypeClass::vf_40(int idxTheater)
{
    char path[0x200];

    if (!DemandLoad) {
        if (Theater) {
            FUN_005F9070();
        } else {
            if (Image && ImageAllocated) {
                operator delete(Image);
                ImageAllocated = false;
            }
            Image = 0;
            _makepath(path, 0, 0, ImageFile[0] ? (const char*)ImageFile : (const char*)ID, TypesShpExtension);
            FUN_005F96B0(path, idxTheater);
            Image = MapObjLoadShape(path, 1);
            if (!Image) {
                FUN_005F9710(path);
                Image = MapObjLoadShape(path, 1);
            }
        }
    }
    if (Image) {
        MapObjShapeView* shape = static_cast<MapObjShapeView*>(Image);
        unknown_2A4 = 1;
        if (End == 0) {
            End = shape->FrameCount;
            if (Shadow)
                End /= 2;
        }
        if (LoopEnd == 0)
            LoopEnd = End;
        MiddleFrameIndex = shape->FrameCount / 2;
        MiddleFrameWidth = -1;
        MiddleFrameHeight = -1;
    }
}

// FUNCTION: GAMEMD 0x428800
HRESULT __stdcall AnimTypeClass::Load(IStream* pStm)
{
    HRESULT hr = ObjectTypeClass::Load(pStm);
    if (hr >= 0) {
        new (this) AnimTypeClass(AbstractNoInit());
        FUN_005F8110();
        FUN_005F9070();
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Next);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&ExpireAnim);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&TrailerAnim);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&BounceAnim);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Spawns);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Warhead);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&TiberiumSpawnType);
        if (!DemandLoad) {
            if (Theater) {
                char path[0x200];
                _makepath(path, 0, 0, ID, MapObjTheaters[MapObjScenario->TheaterIndex].Extension);
                Image = MapObjLoadShape(path, 1);
            } else if (NewTheater) {
                vf_40(MapObjScenario->TheaterIndex);
            }
        }
        hr = 0;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x4289D0
// Slot 13: feed the synchronisation checksum with the type's layer, flags and timing.
void AnimTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1D50(Layer);
    crc->FUN_004A1CA0(Normalized);
    crc->FUN_004A1CA0(Flat);
    crc->FUN_004A1CA0(Translucent);
    crc->FUN_004A1CA0(Scorch);
    crc->FUN_004A1CA0(Flamer);
    crc->FUN_004A1CA0(Crater);
    crc->FUN_004A1CA0(Sticky);
    crc->FUN_004A1CA0(PingPong);
    crc->FUN_004A1CA0(Reverse);
    crc->FUN_004A1CA0(Shadow);
    crc->FUN_004A1D50(MiddleFrameIndex);
    crc->FUN_004A1D90(Damage);
    crc->FUN_004A1CA0(TiberiumChainReaction);
    crc->FUN_004A1D50(Rate);
    crc->FUN_004A1D50(Start);
    crc->FUN_004A1D50(LoopStart);
    crc->FUN_004A1D50(LoopEnd);
    crc->FUN_004A1D50(End);
    crc->FUN_004A1D50(Report);
    crc->FUN_004A1D50(StopSound);
    crc->FUN_004A1D50(NumParticles);
    crc->FUN_004A1D50(DetailLevel);
    crc->FUN_004A1D50(TranslucencyDetailLevel);
    crc->FUN_004A1D50(RandomLoopDelay.Min);
    crc->FUN_004A1D50(RandomLoopDelay.Max);
    crc->FUN_004A1D50(Translucency);
    crc->FUN_004A1CA0(Tiled);
}

// FUNCTION: GAMEMD 0x428C30
// Slot 39: the demand-loaded art, read from disk on first use.
void* AnimTypeClass::vf_39()
{
    if (Image == 0 && DemandLoad) {
        char path[0x200];
        FUN_004068E0("Demand loading image for %s\n", Name);
        _makepath(path, 0, 0, ImageFile[0] ? (const char*)ImageFile : (const char*)ID, TypesShpExtension);
        if (Theater) {
            _makepath(path, 0, 0, ID, MapObjTheaters[MapObjScenario->TheaterIndex].Extension);
        } else if (NewTheater) {
            FUN_005F96B0(path, MapObjScenario->TheaterIndex);
        }
        CCFileClass file(path);
        Image = file.ReadWholeFile();
        if (Image) {
            ImageAllocated = true;
        } else {
            FUN_005F9710(path);
            CCFileClass retry(path);
            Image = retry.ReadWholeFile();
            if (Image)
                ImageAllocated = true;
        }
        vf_40(MapObjScenario->TheaterIndex);
        return Image;
    }
    return Image;
}

// The scalar deleting form of the destructor (??_G); the destructor body is inlined into it.
// FUNCTION: GAMEMD 0x427880
// FUNCTION: GAMEMD 0x428EA0
AnimTypeClass::~AnimTypeClass()
{
    DAT_00B0F670.RemoveItem(this);
    DAT_008B4150.RemoveItem(this);
}
