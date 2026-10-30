// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   AnimTypeClass::vf_25 (retail 0x427D00, 0xAF6 bytes): the INI reader of the animation type.
//   Every key string, destination offset, reader call and default was read off the user's retail
//   gamemd.exe v1.001 disassembly; field names are the INI key strings themselves.
#include <string.h>
#include <stdlib.h>
#include "../_layout/anim_type_class.h"
#include "../core/rules_class_ini_support.h"

// GLOBAL: GAMEMD 0x887180 -- the art INI selected by the native immediate receivers.
extern CCINIClass DAT_00887180;
// GLOBAL: GAMEMD 0x8B4150 -- AnimTypeClass::Array.
extern DynamicVectorClass<AnimTypeClass*> DAT_008B4150;
// FUNCTION: GAMEMD 0x428F70 (decl; reloc) -- registry lookup-or-create by name; the registry arrives in EDX.
AnimTypeClass* __fastcall FUN_00428F70(const char* id, DynamicVectorClass<AnimTypeClass*>* registry);
// FUNCTION: GAMEMD 0x645430 (decl; reloc) -- particle system type index by name.
int FUN_00645430(const char* name);
struct AnimIniPair : RandomStruct
{
    AnimIniPair() {}
    AnimIniPair(const RandomStruct& other) { Min = other.Min; Max = other.Max; }
    AnimIniPair(int min, int max) { Min = min; Max = max; }
};

class AnimTypeIniView : public CCINIClass
{
public:
    // FUNCTION: GAMEMD 0x477050 (decl; reloc) -- layer enumeration by name.
    int ReadLayer(const char* section, const char* key, int fallback);
    // FUNCTION: GAMEMD 0x529880 (decl; reloc) -- a pair of integers; hidden result pointer, default by reference.
    AnimIniPair* ReadPair(AnimIniPair* result, const char* section, const char* key, const AnimIniPair* fallback);
};

// STRING: GAMEMD 0x817474 -- the "<none>" placeholder name.
extern char DAT_00817474[];
// STRING: GAMEMD 0x817694 -- the "none" placeholder name.
extern char DAT_00817694[];
// The lookup-or-create of 0x428B80, expanded inline in the reader for the three animation links.
static AnimTypeClass* AnimLookup(const char* id)
{
    if (_stricmp(DAT_00817474, id) && _stricmp(DAT_00817694, id)) {
        for (int i = 0; i < DAT_008B4150.Count; i++) {
            if (!_stricmp(DAT_008B4150.Items[i]->ID.Data, id))
                return DAT_008B4150.Items[i];
        }
        return new AnimTypeClass(id);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x427D00
// PARTIAL: 60.0% (instruction multiset identical, 804 of 804). The remaining delta is register naming from
// the RandomLoopDelay pair copy: retail loads the returned pair into ECX/EAX, the compiler picks EDX/ECX for
// the same two loads, and every temporary after it rotates one register out of phase. Variants tried:
// struct assignment, field-wise copy, named temporaries, raw result pointer, base-class slicing, an inline
// copy member.
// Reads the animation type's rules section: the object type reader first, then every key over its
// current value.
bool AnimTypeClass::vf_25(CCINIClass* ini)
{
    char buffer[0x80];
    AnimTypeClass* anim;

    ini->Reset();
    if (ObjectTypeClass::vf_25(ini)) {
        {
            // STRING: GAMEMD 0x818660
            bool shadow = ini->ReadBool(ID.Data, "Shadow", Shadow);
            if (shadow != Shadow) {
                Shadow = shadow;
                if (shadow)
                    End /= 2;
                else
                    End *= 2;
                if (LoopEnd > End)
                    LoopEnd = End;
            }
        }
        if (ImageFile.Data[0]) {
            if (Image == 0) {
                // STRING: GAMEMD 0x818658
                Theater = DAT_00887180.ReadBool(ID.Data, "Theater", Theater);
                // STRING: GAMEMD 0x81864C
                NewTheater = DAT_00887180.ReadBool(ID.Data, "NewTheater", NewTheater);
            }
            vf_40(-1);
        }
        // STRING: GAMEMD 0x818644
        Layer = static_cast<AnimTypeIniView*>(ini)->ReadLayer(ID.Data, "Layer", Layer);
        // STRING: GAMEMD 0x818638
        AltPalette = DAT_00887180.ReadBool(ID.Data, "AltPalette", AltPalette);
        // STRING: GAMEMD 0x81862C
        DoubleThick = ini->ReadBool(ID.Data, "DoubleThick", DoubleThick);
        // STRING: GAMEMD 0x818624
        Flat = ini->ReadBool(ID.Data, "Flat", Flat);
        // STRING: GAMEMD 0x81861C
        Flamer = ini->ReadBool(ID.Data, "Flamer", Flamer);
        // STRING: GAMEMD 0x818610
        Normalized = ini->ReadBool(ID.Data, "Normalized", Normalized);
        // STRING: GAMEMD 0x818604
        Translucent = ini->ReadBool(ID.Data, "Translucent", Translucent);
        // STRING: GAMEMD 0x8185FC
        Scorch = ini->ReadBool(ID.Data, "Scorch", Scorch);
        // STRING: GAMEMD 0x8185F4
        Crater = ini->ReadBool(ID.Data, "Crater", Crater);
        // STRING: GAMEMD 0x8185E4
        ForceBigCraters = ini->ReadBool(ID.Data, "ForceBigCraters", ForceBigCraters);
        // STRING: GAMEMD 0x816E3C
        Sticky = ini->ReadBool(ID.Data, "Sticky", Sticky);
        // STRING: GAMEMD 0x8185D8
        PingPong = ini->ReadBool(ID.Data, "PingPong", PingPong);
        // STRING: GAMEMD 0x8185D0
        Reverse = ini->ReadBool(ID.Data, "Reverse", Reverse);
        // STRING: GAMEMD 0x8185C4
        PsiWarning = ini->ReadBool(ID.Data, "PsiWarning", PsiWarning);
        // STRING: GAMEMD 0x8185AC
        TiberiumChainReaction = ini->ReadBool(ID.Data, "TiberiumChainReaction", TiberiumChainReaction);
        // STRING: GAMEMD 0x8185A4
        int rate = ini->ReadInteger(ID.Data, "Rate", -1);
        if (rate != -1) {
            Rate = rate > 0 ? 900 / rate : 0;
        }
        // STRING: GAMEMD 0x81859C
        Damage = ini->ReadDouble(ID.Data, "Damage", Damage);
        // STRING: GAMEMD 0x818594
        Start = ini->ReadInteger(ID.Data, "Start", Start);
        // STRING: GAMEMD 0x818590
        End = ini->ReadInteger(ID.Data, "End", End);
        // STRING: GAMEMD 0x818584
        LoopStart = ini->ReadInteger(ID.Data, "LoopStart", LoopStart);
        // STRING: GAMEMD 0x81857C
        LoopEnd = ini->ReadInteger(ID.Data, "LoopEnd", LoopEnd);
        // STRING: GAMEMD 0x818570
        LoopCount = ini->ReadInteger(ID.Data, "LoopCount", LoopCount);
        // STRING: GAMEMD 0x818568
        { AnimTypeClass* t = Next; Next = ini->ReadString(ID.Data, "Next", STR_00889F64, buffer, 0x80) ? FUN_00428F70(buffer, &DAT_008B4150) : t; }
        // STRING: GAMEMD 0x81855C
        DetailLevel = ini->ReadInteger(ID.Data, "DetailLevel", DetailLevel);
        // STRING: GAMEMD 0x818544
        TranslucencyDetailLevel = ini->ReadInteger(ID.Data, "TranslucencyDetailLevel", TranslucencyDetailLevel);
        {
            AnimIniPair delay(RandomLoopDelay);
            AnimIniPair result;
            // STRING: GAMEMD 0x818534
            AnimIniPair* r = static_cast<AnimTypeIniView*>(ini)->ReadPair(&result, ID.Data, "RandomLoopDelay", &delay);
            int lo = r->Min;
            int hi = r->Max;
            RandomLoopDelay.Min = lo;
            RandomLoopDelay.Max = hi;
        }
        // STRING: GAMEMD 0x818524
        Translucency = ini->ReadInteger(ID.Data, "Translucency", Translucency);
        // STRING: GAMEMD 0x818518
        IsTiberium = ini->ReadBool(ID.Data, "IsTiberium", IsTiberium);
        // STRING: GAMEMD 0x81850C
        HideIfNoOre = ini->ReadBool(ID.Data, "HideIfNoOre", HideIfNoOre);
        // STRING: GAMEMD 0x818500
        YSortAdjust = ini->ReadInteger(ID.Data, "YSortAdjust", YSortAdjust);
        // STRING: GAMEMD 0x8184F4
        Elasticity = ini->ReadDouble(ID.Data, "Elasticity", Elasticity);
        // STRING: GAMEMD 0x8184E8
        MaxXYVel = ini->ReadDouble(ID.Data, "MaxXYVel", MaxXYVel);
        // STRING: GAMEMD 0x8184E0
        MinZVel = ini->ReadDouble(ID.Data, "MinZVel", MinZVel);
        // STRING: GAMEMD 0x8184D0
        MakeInfantry = ini->ReadInteger(ID.Data, "MakeInfantry", MakeInfantry);
        // STRING: GAMEMD 0x8184C8
        { AnimTypeClass* t = Spawns; Spawns = ini->ReadString(ID.Data, "Spawns", STR_00889F64, buffer, 0x80) ? FUN_00428F70(buffer, &DAT_008B4150) : t; }
        // STRING: GAMEMD 0x8184BC
        SpawnCount = ini->ReadInteger(ID.Data, "SpawnCount", SpawnCount);
        // STRING: GAMEMD 0x8184B0
        IsMeteor = ini->ReadBool(ID.Data, "IsMeteor", IsMeteor);
        // STRING: GAMEMD 0x8184A8
        IsVeins = ini->ReadBool(ID.Data, "IsVeins", IsVeins);
        // STRING: GAMEMD 0x818490
        TiberiumSpreadRadius = ini->ReadInteger(ID.Data, "TiberiumSpreadRadius", TiberiumSpreadRadius);
        // STRING: GAMEMD 0x81847C
        { OverlayTypeClass* t = TiberiumSpawnType; TiberiumSpawnType = ini->ReadString(ID.Data, "TiberiumSpawnType", STR_00889F64, buffer, 0x80) ? OverlayType_FindPtr(buffer) : t; }
        // STRING: GAMEMD 0x818468
        IsAnimatedTiberium = ini->ReadBool(ID.Data, "IsAnimatedTiberium", IsAnimatedTiberium);
        // STRING: GAMEMD 0x818458
        ShouldFogRemove = ini->ReadBool(ID.Data, "ShouldFogRemove", ShouldFogRemove);
        // STRING: GAMEMD 0x818448
        IsFlamingGuy = ini->ReadBool(ID.Data, "IsFlamingGuy", IsFlamingGuy);
        // STRING: GAMEMD 0x818438
        RunningFrames = ini->ReadInteger(ID.Data, "RunningFrames", RunningFrames);
        // STRING: GAMEMD 0x81842C
        YDrawOffset = ini->ReadInteger(ID.Data, "YDrawOffset", YDrawOffset);
        // STRING: GAMEMD 0x818424
        ZAdjust = ini->ReadInteger(ID.Data, "ZAdjust", ZAdjust);
        {
            int sound = Report;
            int index;
            // STRING: GAMEMD 0x818418
            Report = (ini->ReadString(ID.Data, "StartSound", STR_00889F64, buffer, 0x80) && (index = VocClass::FindIndex(buffer)) != -1) ? index : sound;
            if (Report == -1) {
                // STRING: GAMEMD 0x818410
                Report = (ini->ReadString(ID.Data, "Report", STR_00889F64, buffer, 0x80) && (index = VocClass::FindIndex(buffer)) != -1) ? index : -1;
            }
        }
        {
            int sound = StopSound;
            int index;
            // STRING: GAMEMD 0x818404
            StopSound = (ini->ReadString(ID.Data, "StopSound", STR_00889F64, buffer, 0x80) && (index = VocClass::FindIndex(buffer)) != -1) ? index : sound;
        }
        {
            anim = BounceAnim;
            // STRING: GAMEMD 0x8183F8
            if (ini->ReadString(ID.Data, "BounceAnim", STR_00889F64, buffer, 0x80)) {
                AnimTypeClass* found = AnimLookup(buffer);
                anim = found;
            }
            BounceAnim = anim;
        }
        // STRING: GAMEMD 0x8183EC
        { AnimTypeClass* t = ExpireAnim; ExpireAnim = ini->ReadString(ID.Data, "ExpireAnim", STR_00889F64, buffer, 0x80) ? AnimLookup(buffer) : t; }
        // STRING: GAMEMD 0x8183E0
        { AnimTypeClass* t = TrailerAnim; TrailerAnim = ini->ReadString(ID.Data, "TrailerAnim", STR_00889F64, buffer, 0x80) ? AnimLookup(buffer) : t; }
        // STRING: GAMEMD 0x8183CC
        TrailerSeperation = ini->ReadInteger(ID.Data, "TrailerSeperation", TrailerSeperation);
        // STRING: GAMEMD 0x8183BC
        DamageRadius = ini->ReadInteger(ID.Data, "DamageRadius", DamageRadius);
        // STRING: GAMEMD 0x8183B4
        { WarheadTypeClass* t = Warhead; Warhead = ini->ReadString(ID.Data, "Warhead", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t; }
        // STRING: GAMEMD 0x8183AC
        Bouncer = ini->ReadBool(ID.Data, "Bouncer", Bouncer);
        // STRING: GAMEMD 0x8183A4
        Tiled = ini->ReadBool(ID.Data, "Tiled", Tiled);
        // STRING: GAMEMD 0x818390
        ShouldUseCellDrawer = ini->ReadBool(ID.Data, "ShouldUseCellDrawer", ShouldUseCellDrawer);
        // STRING: GAMEMD 0x818380
        UseNormalLight = ini->ReadBool(ID.Data, "UseNormalLight", UseNormalLight);
        {
            char particle[0x20];
            // STRING: GAMEMD 0x818370
            if (ini->ReadString(ID.Data, "SpawnsParticle", 0, particle, 0x20))
                SpawnsParticle = FUN_00645430(particle);
        }
        // STRING: GAMEMD 0x818360
        NumParticles = ini->ReadInteger(ID.Data, "NumParticles", NumParticles);
        {
            AnimIniPair none(-1, -1);
            AnimIniPair pair;
            // STRING: GAMEMD 0x818354
            static_cast<AnimTypeIniView*>(ini)->ReadPair(&pair, ID.Data, "RandomRate", &none);
            int low = pair.Min;
            int high = pair.Max;
            if (low != -1) {
                RandomRate.Min = low > 0 ? 900 / low : 0;
            }
            if (high != -1) {
                RandomRate.Max = high > 0 ? 900 / high : 0;
            }
        }
        if (RandomRate.Max < 0)
            RandomRate.Max = 0;
        if (RandomRate.Min > RandomRate.Max)
            RandomRate.Min = RandomRate.Max;
        return true;
    }
    return false;
}
