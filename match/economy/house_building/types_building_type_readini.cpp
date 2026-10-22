// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// BuildingTypeClass::ReadINI (0x45FE50, 0x4C06 bytes): the rules-INI reader. Every key string, default and
// member offset was read from the retail instructions; the statement order is the retail order. The art-INI
// (global 0x887180) reads use the object's image name as their section; the rules reads use the object ID.
//
// The 18 animation slots are expanded by the local macros below, one invocation per slot. A function-style
// helper changes the generated code (the compiler stops expanding it after a few uses), so the repeated shape is
// kept as macros: read the three names (the damaged and garrisoned names fall back to the base name), then, if
// any name is set, the placement values and (where the slot has them) the four power flags. The four SuperAnim
// slots read their X and Y defaults from other slots' values (retail loads them from ActiveAnimFour, ActiveAnimTwo
// and ActiveAnimThree); TYPES_READ_ANIM_QUIRK reproduces that.

#include <stdio.h>
#include <stdlib.h>
#include "types_building_shared.h"

#define TYPES_ANIM_NAME(INI, SECTION, FIELD, KEY)                           \
    (INI).ReadString(SECTION, KEY, TypesEmptyText, animName, 0x10);          \
    if (strlen(animName))                                                    \
        strcpy(FIELD, animName);

#define TYPES_ANIM_NAMES(INI, SECTION, ANIM, PREFIX)                         \
    TYPES_ANIM_NAME(INI, SECTION, (ANIM).Anim, PREFIX)                       \
    TYPES_ANIM_NAME(INI, SECTION, (ANIM).Damaged, PREFIX "Damaged")          \
    if (!strlen((ANIM).Damaged))                                             \
        strcpy((ANIM).Damaged, (ANIM).Anim);                                 \
    TYPES_ANIM_NAME(INI, SECTION, (ANIM).Garrisoned, PREFIX "Garrisoned")    \
    if (!strlen((ANIM).Garrisoned))                                          \
        strcpy((ANIM).Garrisoned, (ANIM).Anim);

#define TYPES_ANIM_PRESENT(ANIM) \
    (strlen((ANIM).Anim) || strlen((ANIM).Damaged) || strlen((ANIM).Garrisoned))

#define TYPES_ANIM_VALUES(INI, SECTION, ANIM, PREFIX, DEFX, DEFY)            \
    (ANIM).X = (INI).ReadInt(SECTION, PREFIX "X", DEFX);                     \
    (ANIM).Y = (INI).ReadInt(SECTION, PREFIX "Y", DEFY);                     \
    (ANIM).ZAdjust = (INI).ReadInt(SECTION, PREFIX "ZAdjust", (ANIM).ZAdjust); \
    (ANIM).YSort = (INI).ReadInt(SECTION, PREFIX "YSort", (ANIM).YSort);

#define TYPES_ANIM_FLAGS(INI, SECTION, ANIM, PREFIX)                         \
    (ANIM).Powered = (INI).ReadBool(SECTION, PREFIX "Powered", (ANIM).Powered); \
    (ANIM).PoweredLight = (INI).ReadBool(SECTION, PREFIX "PoweredLight", (ANIM).PoweredLight); \
    (ANIM).PoweredEffect = (INI).ReadBool(SECTION, PREFIX "PoweredEffect", (ANIM).PoweredEffect); \
    (ANIM).PoweredSpecial = (INI).ReadBool(SECTION, PREFIX "PoweredSpecial", (ANIM).PoweredSpecial);

#define TYPES_READ_ANIM(ANIM, PREFIX)                                        \
    TYPES_ANIM_NAMES(TypesArtIni, ImageFile, ANIM, PREFIX)                   \
    if (TYPES_ANIM_PRESENT(ANIM)) {                                          \
        TYPES_ANIM_VALUES(TypesArtIni, ImageFile, ANIM, PREFIX, (ANIM).X, (ANIM).Y) \
        TYPES_ANIM_FLAGS(TypesArtIni, ImageFile, ANIM, PREFIX)               \
    }

#define TYPES_READ_ANIM_QUIRK(ANIM, PREFIX, DEFX, DEFY)                      \
    TYPES_ANIM_NAMES(TypesArtIni, ImageFile, ANIM, PREFIX)                   \
    if (TYPES_ANIM_PRESENT(ANIM)) {                                          \
        TYPES_ANIM_VALUES(TypesArtIni, ImageFile, ANIM, PREFIX, DEFX, DEFY)  \
        TYPES_ANIM_FLAGS(TypesArtIni, ImageFile, ANIM, PREFIX)               \
    }

#define TYPES_READ_ANIM_NOBOOLS(ANIM, PREFIX)                                \
    TYPES_ANIM_NAMES(TypesArtIni, ImageFile, ANIM, PREFIX)                   \
    if (TYPES_ANIM_PRESENT(ANIM)) {                                          \
        TYPES_ANIM_VALUES(TypesArtIni, ImageFile, ANIM, PREFIX, (ANIM).X, (ANIM).Y) \
    }

// The turret slot is read from the rules INI under the object ID.
#define TYPES_READ_ANIM_NOBOOLS_RULES(ANIM, PREFIX)                          \
    TYPES_ANIM_NAMES(*ini, ID, ANIM, PREFIX)                                 \
    if (TYPES_ANIM_PRESENT(ANIM)) {                                          \
        TYPES_ANIM_VALUES(*ini, ID, ANIM, PREFIX, (ANIM).X, (ANIM).Y)        \
    }

// CAPPED at 72.2% aligned-instruction match (4204 of 5819 retail instructions; 5861 compiled); 91.0% when
// register names are ignored. Observed delta, all of it layout and scheduling rather than missing statements:
//  - the stack frame is 12 bytes larger than retail's (sub esp,0x364 against 0x358), which shifts every
//    esp-relative local and the incoming argument by 12; with that shift removed the frame-text and
//    default-text buffers (0x140/0x180 in retail) are swapped;
//  - retail keeps `this` in EBP, the section pointer in EBX (ESI early on) and the reader in ESI (EDI early on);
//    this build puts `this` in EBX, the section pointer in EBP and the reader in ESI;
//  - the MuzzleFlash / DamageFireOffset loops: retail walks the member array through a pointer kept in a stack
//    slot and compares against a register holding 0xFFFF that is also the default's source; this build indexes
//    the array and compares against immediates (the pointer-walking form was tried and scored 71.6%);
//  - the RemoveOccupy / AddOccupy defaults and the coordinate defaults are built in different stack temporaries.
// Forms tried: (1) every buffer declared inside its own block (66.6%); (2) every buffer declared once at function
// scope, giving the key and name buffers retail's shared addresses (72.2%, kept); (3) the occupancy loops with a
// running pointer (71.6%, dropped). The anim-slot macros, the unmodified statement order and all key strings
// are as retail.

// FUNCTION: GAMEMD 0x45FE50
bool BuildingTypeClass::ReadINI(TypesIniView* ini)
{
    int i;
    HBCoord coordDefault;
    char animName[0x80];
    TypesPoint2D pointDefault;
    TypesPoint2D pointDefault2;
    char name[0x80];
    char frameText[0x40];
    char frameDefault[0x40];
    char dockKey[0x20];
    char yKey[0x40];
    char sortKey[0x40];
    char animKey[0x40];
    char damagedKey[0x40];
    char zKey[0x40];
    char xKey[0x40];

    ini->ClearCache();
    if (TypesBuildingTypeTechnoView::ReadINI(ini)) {
        BuildCat = ini->ReadBuildCat(ID, "BuildCat", BuildCat);
        AntiInfantryValue = ini->ReadInt(ID, "AntiInfantryValue", AntiInfantryValue);
        AntiArmorValue = ini->ReadInt(ID, "AntiArmorValue", AntiArmorValue);
        AntiAirValue = ini->ReadInt(ID, "AntiAirValue", AntiAirValue);
        HasSpotlight = ini->ReadBool(ID, "HasSpotlight", HasSpotlight);
        HalfDamageSmokeLocation1 = ini->ReadCoord(ID, "HalfDamageSmokeLocation1", HalfDamageSmokeLocation1);
        HalfDamageSmokeLocation2 = ini->ReadCoord(ID, "HalfDamageSmokeLocation2", HalfDamageSmokeLocation2);
        Radar = ini->ReadBool(ID, "Radar", Radar);
        SpySat = ini->ReadBool(ID, "SpySat", SpySat);
        unknown_67C = ini->ReadBool(ID, "WaterBound", unknown_67C == 5) ? 5 : -1;
        Adjacent = ini->ReadInt(ID, "Adjacent", Adjacent);
        Capturable = ini->ReadBool(ID, "Capturable", Capturable);
        Powered = ini->ReadBool(ID, "Powered", Powered);
        PoweredSpecial = ini->ReadBool(ID, "PoweredSpecial", PoweredSpecial);
        Overpowerable = ini->ReadBool(ID, "Overpowerable", Overpowerable);
        Spyable = ini->ReadBool(ID, "Spyable", Spyable);
        CanC4 = ini->ReadBool(ID, "CanC4", CanC4);
        WantsExtraSpace = ini->ReadBool(ID, "WantsExtraSpace", WantsExtraSpace);
        Bib = ini->ReadBool(ID, "Bib", Bib);
        Unsellable = ini->ReadBool(ID, "Unsellable", Unsellable);
        ClickRepairable = ini->ReadBool(ID, "ClickRepairable", ClickRepairable);
        CanBeOccupied = ini->ReadBool(ID, "CanBeOccupied", CanBeOccupied);
        CanOccupyFire = ini->ReadBool(ID, "CanOccupyFire", CanOccupyFire);
        ShowOccupantPips = ini->ReadBool(ID, "ShowOccupantPips", ShowOccupantPips);
        MaxNumberOccupants = ini->ReadInt(ID, "MaxNumberOccupants", MaxNumberOccupants);
        NumberImpassableRows = ini->ReadInt(ID, "NumberImpassableRows", NumberImpassableRows);
        ProduceCashStartup = ini->ReadInt(ID, "ProduceCashStartup", ProduceCashStartup);
        ProduceCashAmount = ini->ReadInt(ID, "ProduceCashAmount", ProduceCashAmount);
        ProduceCashDelay = ini->ReadInt(ID, "ProduceCashDelay", ProduceCashDelay);
        InfantryGainSelfHeal = ini->ReadInt(ID, "InfantryGainSelfHeal", InfantryGainSelfHeal);
        UnitsGainSelfHeal = ini->ReadInt(ID, "UnitsGainSelfHeal", UnitsGainSelfHeal);
        RefinerySmokeFrames = ini->ReadInt(ID, "RefinerySmokeFrames", RefinerySmokeFrames);
        BaseNormal = ini->ReadBool(ID, "BaseNormal", BaseNormal);
        EligibileForAllyBuilding = ini->ReadBool(ID, "EligibileForAllyBuilding", EligibileForAllyBuilding);
        EligibleForDelayKill = ini->ReadBool(ID, "EligibleForDelayKill", EligibleForDelayKill);
        NeedsEngineer = ini->ReadBool(ID, "NeedsEngineer", NeedsEngineer);
        CaptureEvaEvent = ini->ReadEvaEvent(ID, "CaptureEvaEvent", CaptureEvaEvent);
        ProtectWithWall = ini->ReadBool(ID, "ProtectWithWall", ProtectWithWall);
        for (i = 0; i < MaxNumberOccupants; ++i) {
            char number[0x10];
            strcpy(animName, "MuzzleFlash");
            itoa(i, number, 10);
            strcat(animName, number);
            pointDefault = TypesMakePoint(0xFFFF, 0xFFFF);
            MuzzleFlash[i] = TypesArtIni.ReadPoint(ImageFile, animName, pointDefault);
            if (MuzzleFlash[i].X == 0xFFFF && MuzzleFlash[i].Y == 0xFFFF) {
                MuzzleFlash[i].X = 0;
                MuzzleFlash[i].Y = 0;
            }
        }
        for (i = 0; i < 8; ++i) {
            char number[0x10];
            strcpy(animName, "DamageFireOffset");
            itoa(i, number, 10);
            strcat(animName, number);
            pointDefault = TypesMakePoint(0xFFFF, 0xFFFF);
            DamageFireOffset[i] = TypesArtIni.ReadPoint(ImageFile, animName, pointDefault);
            if (DamageFireOffset[i].X == 0xFFFF && DamageFireOffset[i].Y == 0xFFFF) {
                DamageFireOffset[i].X = TypesZeroCoord.X;
                DamageFireOffset[i].Y = TypesZeroCoord.Y;
                break;
            }
        }
        Wall = ini->ReadBool(ID, "Wall", Wall);
        Weeder = ini->ReadBool(ID, "Weeder", Weeder);
        Helipad = ini->ReadBool(ID, "Helipad", Helipad);
        OrePurifier = ini->ReadBool(ID, "OrePurifier", OrePurifier);
        FactoryPlant = ini->ReadBool(ID, "FactoryPlant", FactoryPlant);
        Factory = ini->ReadFactory(ID, "Factory", Factory);
        {
            void* old = FreeUnit;
            FreeUnit = ini->ReadString(ID, "FreeUnit", TypesEmptyText, name, 0x80) ? (void*)TypesFindUnitType(name) : old;
        }
        HoverPad = ini->ReadBool(ID, "HoverPad", HoverPad);
        IsTemple = ini->ReadBool(ID, "IsTemple", IsTemple);
        IsPlug = ini->ReadBool(ID, "IsPlug", IsPlug);
        {
            void* old = SecretInfantry;
            SecretInfantry = ini->ReadString(ID, "SecretInfantry", TypesEmptyText, name, 0x80) ? (void*)TypesFindInfantryType(name) : old;
        }
        {
            void* old = SecretUnit;
            SecretUnit = ini->ReadString(ID, "SecretUnit", TypesEmptyText, name, 0x80) ? (void*)TypesFindUnitType(name) : old;
        }
        {
            void* old = SecretBuilding;
            SecretBuilding = ini->ReadString(ID, "SecretBuilding", TypesEmptyText, name, 0x80) ? TypesFindBuildingType(name, &TypesBuildingTypeArray) : old;
        }
        InfantryCostBonus = (float)ini->ReadDouble(ID, "InfantryCostBonus", InfantryCostBonus);
        UnitsCostBonus = (float)ini->ReadDouble(ID, "UnitsCostBonus", UnitsCostBonus);
        AircraftCostBonus = (float)ini->ReadDouble(ID, "AircraftCostBonus", AircraftCostBonus);
        BuildingsCostBonus = (float)ini->ReadDouble(ID, "BuildingsCostBonus", BuildingsCostBonus);
        DefensesCostBonus = (float)ini->ReadDouble(ID, "DefensesCostBonus", DefensesCostBonus);
        TogglePower = ini->ReadBool(ID, "TogglePower", TogglePower);
        {
            int sound = BuildupSound;
            if (ini->ReadString(ID, "BuildupSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = BuildupSound;
            }
            BuildupSound = sound;
        }
        {
            int sound = PackupSound;
            if (ini->ReadString(ID, "PackupSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = PackupSound;
            }
            PackupSound = sound;
        }
        {
            int sound = CreateUnitSound;
            if (ini->ReadString(ID, "CreateUnitSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = CreateUnitSound;
            }
            CreateUnitSound = sound;
        }
        {
            int sound = UnitExitSound;
            if (ini->ReadString(ID, "UnitExitSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = UnitExitSound;
            }
            UnitExitSound = sound;
        }
        {
            int sound = UnitEnterSound;
            if (ini->ReadString(ID, "UnitEnterSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = UnitEnterSound;
            }
            UnitEnterSound = sound;
        }
        {
            int sound = WorkingSound;
            if (ini->ReadString(ID, "WorkingSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = WorkingSound;
            }
            WorkingSound = sound;
        }
        {
            int sound = NotWorkingSound;
            if (ini->ReadString(ID, "NotWorkingSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = NotWorkingSound;
            }
            NotWorkingSound = sound;
        }
        UnitRepair = ini->ReadBool(ID, "UnitRepair", UnitRepair);
        UnitReload = ini->ReadBool(ID, "UnitReload", UnitReload);
        Bunker = ini->ReadBool(ID, "Bunker", Bunker);
        Cloning = ini->ReadBool(ID, "Cloning", Cloning);
        Grinding = ini->ReadBool(ID, "Grinding", Grinding);
        UnitAbsorb = ini->ReadBool(ID, "UnitAbsorb", UnitAbsorb);
        InfantryAbsorb = ini->ReadBool(ID, "InfantryAbsorb", InfantryAbsorb);
        SecretLab = ini->ReadBool(ID, "SecretLab", SecretLab);
        DockUnload = ini->ReadBool(ID, "DockUnload", DockUnload);
        Gate = ini->ReadBool(ID, "Gate", Gate);
        SAM = ini->ReadBool(ID, "SAM", SAM);
        ConstructionYard = ini->ReadBool(ID, "ConstructionYard", ConstructionYard);
        NukeSilo = ini->ReadBool(ID, "NukeSilo", NukeSilo);
        Refinery = ini->ReadBool(ID, "Refinery", Refinery);
        WeaponsFactory = ini->ReadBool(ID, "WeaponsFactory", WeaponsFactory);
        LaserFencePost = ini->ReadBool(ID, "LaserFencePost", LaserFencePost);
        LaserFence = ini->ReadBool(ID, "LaserFence", LaserFence);
        FirestormWall = ini->ReadBool(ID, "FirestormWall", FirestormWall);
        Hospital = ini->ReadBool(ID, "Hospital", Hospital);
        Armory = ini->ReadBool(ID, "Armory", Armory);
        GDIBarracks = ini->ReadBool(ID, "GDIBarracks", GDIBarracks);
        NODBarracks = ini->ReadBool(ID, "NODBarracks", NODBarracks);
        YuriBarracks = ini->ReadBool(ID, "YuriBarracks", YuriBarracks);
        EMPulseCannon = ini->ReadBool(ID, "EMPulseCannon", EMPulseCannon);
        TickTank = ini->ReadBool(ID, "TickTank", TickTank);
        ChargedAnimTime = (float)ini->ReadDouble(ID, "ChargedAnimTime", ChargedAnimTime);
        SuperWeapon = ini->ReadSuperWeapon(ID, "SuperWeapon", SuperWeapon);
        SuperWeapon2 = ini->ReadSuperWeapon(ID, "SuperWeapon2", SuperWeapon2);
        CloakGenerator = ini->ReadBool(ID, "CloakGenerator", CloakGenerator);
        SensorArray = ini->ReadBool(ID, "SensorArray", SensorArray);
        CloakRadiusInCells = (unsigned char)ini->ReadInt(ID, "CloakRadiusInCells", (signed char)CloakRadiusInCells);
        PsychicDetectionRadius = ini->ReadInt(ID, "PsychicDetectionRadius", PsychicDetectionRadius);
        BarrelStartPitch = ini->ReadInt(ID, "BarrelStartPitch", BarrelStartPitch >> 5) << 5;
        DeployFacing = ini->ReadInt(ID, "DeployFacing", DeployFacing >> 5) << 5;
        LightVisibility = ini->ReadInt(ID, "LightVisibility", LightVisibility);
        LightIntensity = (int)(ini->ReadDouble(ID, "LightIntensity", (double)(LightIntensity / 1000)) * 1000.0 + 0.1);
        LightRedTint = (int)(ini->ReadDouble(ID, "LightRedTint", (double)(LightRedTint / 1000)) * 1000.0 + 0.1);
        LightGreenTint = (int)(ini->ReadDouble(ID, "LightGreenTint", (double)(LightGreenTint / 1000)) * 1000.0 + 0.1);
        LightBlueTint = (int)(ini->ReadDouble(ID, "LightBlueTint", (double)(LightBlueTint / 1000)) * 1000.0 + 0.1);
        GateCloseDelay = ini->ReadDouble(ID, "GateCloseDelay", GateCloseDelay);
        InvisibleInGame = ini->ReadBool(ID, "InvisibleInGame", InvisibleInGame);
        {
            ini->ReadString(ID, "PowersUpBuilding", TypesEmptyText, animName, 0x18);
            if (strlen(animName))
                strcpy(PowersUpBuilding, animName);
        }
        PowersUpToLevel = ini->ReadInt(ID, "PowersUpToLevel", PowersUpToLevel);
        BridgeRepairHut = ini->ReadBool(ID, "BridgeRepairHut", BridgeRepairHut);
        HasStupidGuardMode = ini->ReadBool(ID, "HasStupidGuardMode", HasStupidGuardMode);
        CrateBeneath = ini->ReadBool(ID, "CrateBeneath", CrateBeneath);
        CrateBeneathIsMoney = ini->ReadBool(ID, "CrateBeneathIsMoney", CrateBeneathIsMoney);
        LeaveRubble = ini->ReadBool(ID, "LeaveRubble", LeaveRubble);
        PlaceAnywhere = ini->ReadBool(ID, "PlaceAnywhere", PlaceAnywhere);
        ICBMLauncher = ini->ReadBool(ID, "ICBMLauncher", ICBMLauncher);
        Artillary = ini->ReadBool(ID, "Artillary", Artillary);
        {
            coordDefault = TargetCoordOffset;
            TargetCoordOffset = ini->ReadCoord(ID, "TargetCoordOffset", coordDefault);
        }
        {
            coordDefault = ExitCoord;
            ExitCoord = ini->ReadCoord(ID, "ExitCoord", coordDefault);
        }
        AIBuildThis = ini->ReadBool(ID, "AIBuildThis", AIBuildThis);
        IsBaseDefense = ini->ReadBool(ID, "IsBaseDefense", IsBaseDefense);
        IsThreatRatingNode = ini->ReadBool(ID, "IsThreatRatingNode", IsThreatRatingNode);
        ConcentricRadialIndicator = ini->ReadBool(ID, "ConcentricRadialIndicator", ConcentricRadialIndicator);
        unknown_718 = unknown_CA1 ? 0x20 : 1;
        {
            int power = PowerBonus > 0 ? PowerBonus : -PowerDrain;
            power = ini->ReadInt(ID, "Power", power);
            PowerBonus = power;
            if (power < 0) {
                PowerDrain = -power;
                PowerBonus = 0;
            } else {
                PowerDrain = 0;
            }
        }
        {
            int power = ExtraPowerBonus > 0 ? ExtraPowerBonus : -ExtraPowerDrain;
            power = ini->ReadInt(ID, "ExtraPower", power);
            ExtraPowerBonus = power;
            if (power < 0) {
                ExtraPowerDrain = -power;
                ExtraPowerBonus = 0;
            }
        }
        Height = TypesArtIni.ReadInt(ImageFile, "Height", Height);
        OccupyHeight = TypesArtIni.ReadInt(ImageFile, "OccupyHeight", Height);
        Recoilless = TypesArtIni.ReadBool(ImageFile, "Recoilless", Recoilless);
        DoubleThick = TypesArtIni.ReadBool(ImageFile, "DoubleThick", DoubleThick);
        Flat = TypesArtIni.ReadBool(ImageFile, "Flat", Flat);
        SiloDamage = TypesArtIni.ReadBool(ImageFile, "SiloDamage", SiloDamage);
        ChargeAnim = TypesArtIni.ReadBool(ImageFile, "ChargeAnim", ChargeAnim);
        IsAnimDelayedFire = TypesArtIni.ReadBool(ImageFile, "IsAnimDelayedFire", IsAnimDelayedFire);
        DelayedFireDelay = TypesArtIni.ReadInt(ImageFile, "DelayedFireDelay", DelayedFireDelay);
        {
            void* old = ToOverlay;
            ToOverlay = TypesArtIni.ReadString(ImageFile, "ToOverlay", TypesEmptyText, name, 0x80) ? TypesFindOverlay(name) : old;
        }
        Foundation = TypesArtIni.ReadFoundation(ImageFile, "Foundation", Foundation);
        {
            int foundation = TypesArtIni.ReadFoundation(ID, "Foundation", Foundation);
            if (foundation)
                Foundation = foundation;
        }
        MidPoint = TypesArtIni.ReadInt(ImageFile, "MidPoint", MidPoint);
        DoorStages = TypesArtIni.ReadInt(ImageFile, "DoorStages", DoorStages);
        DamagedDoor = TypesArtIni.ReadBool(ImageFile, "DamagedDoor", DamagedDoor);
        TerrainPalette = TypesArtIni.ReadBool(ImageFile, "TerrainPalette", TerrainPalette);
        GateStages = TypesArtIni.ReadInt(ImageFile, "GateStages", GateStages);
        PrimaryFirePixelOffset = TypesArtIni.ReadPoint(ImageFile, "PrimaryFirePixelOffset", PrimaryFirePixelOffset);
        SecondaryFirePixelOffset = TypesArtIni.ReadPoint(ImageFile, "SecondaryFirePixelOffset", SecondaryFirePixelOffset);
        PrimaryFireDualOffset = TypesArtIni.ReadBool(ImageFile, "PrimaryFireDualOffset", PrimaryFireDualOffset);
        ExtraDamageStage = TypesArtIni.ReadBool(ImageFile, "ExtraDamageStage", ExtraDamageStage);
        SpecialZOverlayZAdjust = TypesArtIni.ReadInt(ImageFile, "SpecialZOverlayZAdjust", SpecialZOverlayZAdjust);
        NormalZAdjust = TypesArtIni.ReadInt(ImageFile, "NormalZAdjust", NormalZAdjust);
        ZShapePointMove = TypesArtIni.ReadPoint(ImageFile, "ZShapePointMove", ZShapePointMove);
        ExtraLight = (short)TypesArtIni.ReadInt(ImageFile, "ExtraLight", (short)ExtraLight);
        CanHideThings = TypesArtIni.ReadBool(ID, "CanHideThings", CanHideThings);
        for (i = 1; i <= 8; ++i) {
            wsprintfA(animName, "RemoveOccupy%d", i);
            pointDefault = TypesMakePoint(0xFFFF, 0xFFFF);
            RemoveOccupy[i - 1] = TypesArtIni.ReadPoint(ImageFile, animName, pointDefault);
            wsprintfA(animName, "AddOccupy%d", i);
            pointDefault2 = TypesMakePoint(0xFFFF, 0xFFFF);
            AddOccupy[i - 1] = TypesArtIni.ReadPoint(ImageFile, animName, pointDefault2);
        }
        {
            pointDefault = TypesMakePoint(0, 0);
            QueueingCell = TypesArtIni.ReadPoint(ImageFile, "QueueingCell", pointDefault);
        }
        FoundationData = &TypesFoundationCells[Foundation];
        FoundationOutside = &TypesFoundationOutsideCells[Foundation];
        {
            TypesArtIni.ReadString(ImageFile, "Buildup", TypesEmptyText, animName, 0x10);
            if (strlen(animName))
                strcpy(BuildupFile, animName);
        }
        StampTheater(TypesScenario->TheaterIndex);
        {
            sprintf(frameDefault, "%d,%d,%d", BuildingAnimFrame[1].Start, BuildingAnimFrame[1].Count, BuildingAnimFrame[1].Rate);
            if (TypesArtIni.ReadString(ImageFile, "AnimIdle", frameDefault, frameText, 0x40) > 0)
                sscanf(frameText, "%d,%d,%d", &BuildingAnimFrame[1].Start, &BuildingAnimFrame[1].Count, &BuildingAnimFrame[1].Rate);
        }
        {
            sprintf(frameDefault, "%d,%d,%d", BuildingAnimFrame[2].Start, BuildingAnimFrame[2].Count, BuildingAnimFrame[2].Rate);
            if (TypesArtIni.ReadString(ImageFile, "AnimActive", frameDefault, frameText, 0x40) > 0)
                sscanf(frameText, "%d,%d,%d", &BuildingAnimFrame[2].Start, &BuildingAnimFrame[2].Count, &BuildingAnimFrame[2].Rate);
        }
        {
            sprintf(frameDefault, "%d,%d,%d", BuildingAnimFrame[4].Start, BuildingAnimFrame[4].Count, BuildingAnimFrame[4].Rate);
            if (TypesArtIni.ReadString(ImageFile, "AnimAux1", frameDefault, frameText, 0x40) > 0)
                sscanf(frameText, "%d,%d,%d", &BuildingAnimFrame[4].Start, &BuildingAnimFrame[4].Count, &BuildingAnimFrame[4].Rate);
        }
        {
            sprintf(frameDefault, "%d,%d,%d", BuildingAnimFrame[5].Start, BuildingAnimFrame[5].Count, BuildingAnimFrame[5].Rate);
            if (TypesArtIni.ReadString(ImageFile, "AnimAux2", frameDefault, frameText, 0x40) > 0)
                sscanf(frameText, "%d,%d,%d", &BuildingAnimFrame[5].Start, &BuildingAnimFrame[5].Count, &BuildingAnimFrame[5].Rate);
        }
        TYPES_READ_ANIM(BuildingAnim[3], "ActiveAnim")
        TYPES_READ_ANIM(BuildingAnim[4], "ActiveAnimTwo")
        TYPES_READ_ANIM(BuildingAnim[5], "ActiveAnimThree")
        TYPES_READ_ANIM(BuildingAnim[6], "ActiveAnimFour")
        TYPES_READ_ANIM_QUIRK(BuildingAnim[14], "SuperAnim", BuildingAnim[6].X, BuildingAnim[6].Y)
        TYPES_READ_ANIM_QUIRK(BuildingAnim[15], "SuperAnimTwo", BuildingAnim[4].X, BuildingAnim[4].Y)
        TYPES_READ_ANIM_QUIRK(BuildingAnim[16], "SuperAnimThree", BuildingAnim[5].X, BuildingAnim[5].Y)
        TYPES_READ_ANIM_QUIRK(BuildingAnim[17], "SuperAnimFour", BuildingAnim[5].X, BuildingAnim[5].Y)
        TYPES_READ_ANIM(BuildingAnim[10], "SpecialAnim")
        TYPES_READ_ANIM(BuildingAnim[11], "SpecialAnimTwo")
        TYPES_READ_ANIM(BuildingAnim[12], "SpecialAnimThree")
        TYPES_READ_ANIM(BuildingAnim[13], "SpecialAnimFour")
        TYPES_READ_ANIM(BuildingAnim[19], "LowPower")
        TYPES_READ_ANIM(BuildingAnim[20], "SuperLowPower")
        TYPES_READ_ANIM_NOBOOLS(BuildingAnim[8], "ProductionAnim")
        TYPES_READ_ANIM(BuildingAnim[18], "IdleAnim")
        TYPES_READ_ANIM_NOBOOLS(BuildingAnim[7], "PreProductionAnim")
        TYPES_READ_ANIM_NOBOOLS_RULES(BuildingAnim[9], "TurretAnim")
        TurretAnimIsVoxel = ini->ReadBool(ID, "TurretAnimIsVoxel", TurretAnimIsVoxel);
        BarrelAnimIsVoxel = ini->ReadBool(ID, "BarrelAnimIsVoxel", BarrelAnimIsVoxel);
        ini->ReadString(ID, "VoxelBarrelFile", VoxelBarrelFile, VoxelBarrelFile, 0x10);
        {
            coordDefault = VoxelBarrelOffsetToPitchPivotPoint;
            VoxelBarrelOffsetToPitchPivotPoint = ini->ReadCoord(ID, "VoxelBarrelOffsetToPitchPivotPoint", coordDefault);
        }
        {
            coordDefault = VoxelBarrelOffsetToRotatePivotPoint;
            VoxelBarrelOffsetToRotatePivotPoint = ini->ReadCoord(ID, "VoxelBarrelOffsetToRotatePivotPoint", coordDefault);
        }
        {
            coordDefault = VoxelBarrelOffsetToBuildingPivotPoint;
            VoxelBarrelOffsetToBuildingPivotPoint = ini->ReadCoord(ID, "VoxelBarrelOffsetToBuildingPivotPoint", coordDefault);
        }
        {
            coordDefault = VoxelBarrelOffsetToBarrelEnd;
            VoxelBarrelOffsetToBarrelEnd = ini->ReadCoord(ID, "VoxelBarrelOffsetToBarrelEnd", coordDefault);
        }
        Upgrades = ini->ReadInt(ID, "Upgrades", Upgrades);
        if (Upgrades > 0) {
            for (i = 1; i - 1 < Upgrades; ++i) {
                BuildingTypeAnim& slot = BuildingAnim[i - 1];
                sprintf(animKey, "PowerUp%01dAnim", i);
                sprintf(damagedKey, "PowerUp%01dDamagedAnim", i);
                sprintf(xKey, "PowerUp%01dLocXX", i);
                sprintf(yKey, "PowerUp%01dLocYY", i);
                sprintf(zKey, "PowerUp%01dLocZZ", i);
                sprintf(sortKey, "PowerUp%01dYSort", i);
                TypesArtIni.ReadString(ImageFile, animKey, TypesEmptyText, animName, 0x10);
                if (strlen(animName))
                    strcpy(slot.Anim, animName);
                TypesArtIni.ReadString(ImageFile, damagedKey, TypesEmptyText, animName, 0x10);
                if (strlen(animName))
                    strcpy(slot.Damaged, animName);
                slot.X = TypesArtIni.ReadInt(ImageFile, xKey, slot.X);
                slot.Y = TypesArtIni.ReadInt(ImageFile, yKey, slot.Y);
                slot.ZAdjust = TypesArtIni.ReadInt(ImageFile, zKey, slot.ZAdjust);
                slot.YSort = TypesArtIni.ReadInt(ImageFile, sortKey, slot.YSort);
            }
        }
        {
            int oldDocks = NumberOfDocks;
            NumberOfDocks = ini->ReadInt(ID, "NumberOfDocks", oldDocks);
            if (NumberOfDocks > DockingOffsets.Capacity) {
                DockingOffsets.SetCapacity(NumberOfDocks, 0);
                for (i = oldDocks; i < NumberOfDocks; ++i) {
                    TypesDockCoord zero;
                    zero.X = 0;
                    zero.Y = 0;
                    zero.Z = 0;
                    DockingOffsets.Items[i] = zero;
                }
            }
            for (i = 0; i < NumberOfDocks; ++i) {
                sprintf(dockKey, "DockingOffset%d", i);
                coordDefault = *(HBCoord*)&DockingOffsets.Items[i];
                HBCoord result = TypesArtIni.ReadCoord(ImageFile, dockKey, coordDefault);
                *(HBCoord*)&DockingOffsets.Items[i] = result;
            }
        }
        return true;
    }
    return false;
}
