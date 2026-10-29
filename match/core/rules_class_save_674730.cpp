// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail 0x674730 (2779 bytes): the RulesClass stream save. It writes the whole 0x18C0-byte object
//   in one call, then each list member: 27 TypeList<int> members expanded inline as count + items
//   loops (the helper 0x67A520 inlined), the remaining lists through the typed helpers
//   0x67A3C0 / 0x67A4A0 / 0x67A520 / 0x67A630 / 0x67A6E0 / 0x67A770 / 0x67A7D0 / 0x67A850 / 0x67A8E0,
//   and finally RGBClass::Save (0x6614F0) over the 16 ColorAdd entries. The only caller is 0x67D300.
#include "../_layout/rules_class.h"
#include "../_layout/rgb_class.h"
#include "vector_stream_save_family_methods.h"

// Inline expansion of the TypeList<int> helper (count, then every item, null pcbWritten).
#define SAVE_INT_LIST(list)                         \
    {                                               \
        int count = (list).Count;                   \
        stream->Write(&count, 4, 0);                \
        for (int i = 0; i < count; ++i) {           \
            stream->Write(&(list).Items[i], 4, 0);  \
        }                                           \
    }

// FUNCTION: GAMEMD 0x674730
// Saves the rules object and its list members to the stream.
void RulesClass::Save(IStream* stream)
{
    stream->Write(this, 0x18C0, 0);
    SAVE_INT_LIST(AIIonCannonConYardValue)
    SAVE_INT_LIST(AIIonCannonWarFactoryValue)
    SAVE_INT_LIST(AIIonCannonPowerValue)
    SAVE_INT_LIST(AIIonCannonTechCenterValue)
    SAVE_INT_LIST(AIIonCannonEngineerValue)
    SAVE_INT_LIST(AIIonCannonThiefValue)
    SAVE_INT_LIST(AIIonCannonHarvesterValue)
    SAVE_INT_LIST(AIIonCannonMCVValue)
    SAVE_INT_LIST(AIIonCannonAPCValue)
    SAVE_INT_LIST(AIIonCannonBaseDefenseValue)
    SAVE_INT_LIST(AIIonCannonPlugValue)
    SAVE_INT_LIST(AIIonCannonHelipadValue)
    SAVE_INT_LIST(AIIonCannonTempleValue)
    SAVE_INT_LIST(FillEarliestTeamProbability)
    SAVE_INT_LIST(TeamDelays)
    SAVE_INT_LIST(list_09A8)
    SAVE_INT_LIST(AlliedBaseDefenseCounts)
    SAVE_INT_LIST(SovietBaseDefenseCounts)
    SAVE_INT_LIST(ThirdBaseDefenseCounts)
    SAVE_INT_LIST(list_0EE8)
    SAVE_INT_LIST(list_0F04)
    SAVE_INT_LIST(list_0F20)
    SAVE_INT_LIST(DisabledDisguiseDetectionPercent)
    SAVE_INT_LIST(AISuperDefenseProbability)
    SAVE_INT_LIST(AIAutoDeployFrameDelay)
    SAVE_INT_LIST(AIPickWallDefensePercent)
    SAVE_INT_LIST(MinimumAIDefensiveTeams)
    SAVE_INT_LIST(MaximumAIDefensiveTeams)
    AICaptureNormal.FUN_0067A520(stream);
    AICaptureWounded.FUN_0067A520(stream);
    AICaptureLowPower.FUN_0067A520(stream);
    AICaptureLowMoney.FUN_0067A520(stream);
    MultiplayerAICM.FUN_0067A520(stream);
    AIVirtualPurifiers.FUN_0067A520(stream);
    AISlaveMinerNumber.FUN_0067A520(stream);
    HarvestersPerRefinery.FUN_0067A520(stream);
    AIExtraRefineries.FUN_0067A520(stream);
    TotalAITeamCap.FUN_0067A520(stream);
    AIHateDelays.FUN_0067A520(stream);
    RadarEventSuppressionDistances.FUN_0067A520(stream);
    RadarEventVisibilityDurations.FUN_0067A520(stream);
    RadarEventDurations.FUN_0067A520(stream);
    BarrelDebris.FUN_0067A3C0(stream);
    ExplosiveVoxelDebris.FUN_0067A3C0(stream);
    PrerequisitePower.FUN_0067A520(stream);
    PrerequisiteFactory.FUN_0067A520(stream);
    PrerequisiteBarracks.FUN_0067A520(stream);
    PrerequisiteRadar.FUN_0067A520(stream);
    PrerequisiteTech.FUN_0067A520(stream);
    PrerequisiteProc.FUN_0067A520(stream);
    list_06CC.FUN_0067A520(stream);
    list_0734.FUN_0067A520(stream);
    list_07C4.FUN_0067A630(stream);
    list_07E0.FUN_0067A630(stream);
    list_07FC.FUN_0067A630(stream);
    list_0818.FUN_0067A630(stream);
    list_0834.FUN_0067A630(stream);
    RepairBay.FUN_0067A6E0(stream);
    Shipyard.FUN_0067A6E0(stream);
    list_08AC.FUN_0067A6E0(stream);
    list_08C8.FUN_0067A6E0(stream);
    list_08E4.FUN_0067A6E0(stream);
    list_0900.FUN_0067A6E0(stream);
    list_091C.FUN_0067A6E0(stream);
    list_0938.FUN_0067A6E0(stream);
    list_0954.FUN_0067A6E0(stream);
    list_0970.FUN_0067A6E0(stream);
    list_098C.FUN_0067A6E0(stream);
    list_09C4.FUN_0067A6E0(stream);
    list_09E0.FUN_0067A6E0(stream);
    list_09FC.FUN_0067A6E0(stream);
    list_0A18.FUN_0067A6E0(stream);
    list_0A34.FUN_0067A6E0(stream);
    list_0A50.FUN_0067A6E0(stream);
    list_0A6C.FUN_0067A6E0(stream);
    list_0A88.FUN_0067A6E0(stream);
    list_0AA4.FUN_0067A6E0(stream);
    list_0AC0.FUN_0067A6E0(stream);
    list_0ADC.FUN_0067A6E0(stream);
    PadAircraft.FUN_0067A7D0(stream);
    list_0B74.FUN_0067A4A0(stream);
    list_0B90.FUN_0067A4A0(stream);
    list_0BC0.FUN_0067A4A0(stream);
    BaseUnit.FUN_0067A770(stream);
    DefaultMirageDisguises.FUN_0067A8E0(stream);
    HarvesterUnit.FUN_0067A770(stream);
    SecretInfantry.FUN_0067A850(stream);
    SecretUnits.FUN_0067A770(stream);
    SecretBuildings.FUN_0067A6E0(stream);
    DeadBodies.FUN_0067A4A0(stream);
    TouchdownAnims.FUN_0067A4A0(stream);
    MetallicDebris.FUN_0067A4A0(stream);
    BridgeExplosions.FUN_0067A4A0(stream);
    list_0648.FUN_0067A520(stream);
    AmerParaDropInf.FUN_0067A850(stream);
    AmerParaDropNum.FUN_0067A520(stream);
    AllyParaDropInf.FUN_0067A850(stream);
    AllyParaDropNum.FUN_0067A520(stream);
    SovParaDropInf.FUN_0067A850(stream);
    SovParaDropNum.FUN_0067A520(stream);
    YuriParaDropInf.FUN_0067A850(stream);
    YuriParaDropNum.FUN_0067A520(stream);
    AnimToInfantry.FUN_0067A850(stream);
    DamageFireTypes.FUN_0067A4A0(stream);
    WeatherConClouds.FUN_0067A4A0(stream);
    WeatherConBolts.FUN_0067A4A0(stream);
    // ColorAdd is the engine's RGBClass array; RGBClass::Save takes the IStream_004C6320 view of the stream.
    for (int i = 0; i < 16; ++i) {
        ((RGBClass*)&ColorAdd[i])->Save((IStream_004C6320*)stream);
    }
}
