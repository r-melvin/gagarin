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
    SAVE_INT_LIST(list_1194)
    SAVE_INT_LIST(list_11B0)
    SAVE_INT_LIST(list_11CC)
    SAVE_INT_LIST(list_11E8)
    SAVE_INT_LIST(list_1204)
    SAVE_INT_LIST(list_1220)
    SAVE_INT_LIST(list_123C)
    SAVE_INT_LIST(list_1258)
    SAVE_INT_LIST(list_1274)
    SAVE_INT_LIST(list_1290)
    SAVE_INT_LIST(list_12AC)
    SAVE_INT_LIST(list_12C8)
    SAVE_INT_LIST(list_12E4)
    SAVE_INT_LIST(list_13F0)
    SAVE_INT_LIST(list_1158)
    SAVE_INT_LIST(list_09A8)
    SAVE_INT_LIST(list_0D80)
    SAVE_INT_LIST(list_0D9C)
    SAVE_INT_LIST(list_0DB8)
    SAVE_INT_LIST(list_0EE8)
    SAVE_INT_LIST(list_0F04)
    SAVE_INT_LIST(list_0F20)
    SAVE_INT_LIST(list_0E10)
    SAVE_INT_LIST(list_0EC4)
    SAVE_INT_LIST(list_0E2C)
    SAVE_INT_LIST(list_0DD4)
    SAVE_INT_LIST(list_1390)
    SAVE_INT_LIST(list_13AC)
    list_0E4C.FUN_0067A520(stream);
    list_0E68.FUN_0067A520(stream);
    list_0E84.FUN_0067A520(stream);
    list_0EA0.FUN_0067A520(stream);
    list_1304.FUN_0067A520(stream);
    list_1320.FUN_0067A520(stream);
    list_133C.FUN_0067A520(stream);
    list_1358.FUN_0067A520(stream);
    list_1374.FUN_0067A520(stream);
    list_13C8.FUN_0067A520(stream);
    list_1174.FUN_0067A520(stream);
    list_043C.FUN_0067A520(stream);
    list_0458.FUN_0067A520(stream);
    list_0474.FUN_0067A520(stream);
    list_0058.FUN_0067A3C0(stream);
    list_0600.FUN_0067A3C0(stream);
    list_0358.FUN_0067A520(stream);
    list_0374.FUN_0067A520(stream);
    list_0390.FUN_0067A520(stream);
    list_03AC.FUN_0067A520(stream);
    list_03C8.FUN_0067A520(stream);
    list_03E4.FUN_0067A520(stream);
    list_06CC.FUN_0067A520(stream);
    list_0734.FUN_0067A520(stream);
    list_07C4.FUN_0067A630(stream);
    list_07E0.FUN_0067A630(stream);
    list_07FC.FUN_0067A630(stream);
    list_0818.FUN_0067A630(stream);
    list_0834.FUN_0067A630(stream);
    list_0850.FUN_0067A6E0(stream);
    list_0880.FUN_0067A6E0(stream);
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
    list_0B58.FUN_0067A7D0(stream);
    list_0B74.FUN_0067A4A0(stream);
    list_0B90.FUN_0067A4A0(stream);
    list_0BC0.FUN_0067A4A0(stream);
    unknown_B20.FUN_0067A770(stream);
    list_0FF8.FUN_0067A8E0(stream);
    list_0B3C.FUN_0067A770(stream);
    list_0D00.FUN_0067A850(stream);
    list_0D1C.FUN_0067A770(stream);
    list_0D38.FUN_0067A6E0(stream);
    list_0120.FUN_0067A4A0(stream);
    TouchdownAnims.FUN_0067A4A0(stream);
    list_013C.FUN_0067A4A0(stream);
    list_0158.FUN_0067A4A0(stream);
    list_0648.FUN_0067A520(stream);
    list_0C04.FUN_0067A850(stream);
    list_0C20.FUN_0067A520(stream);
    list_0C3C.FUN_0067A850(stream);
    list_0C58.FUN_0067A520(stream);
    list_0C74.FUN_0067A850(stream);
    list_0C90.FUN_0067A520(stream);
    list_0CAC.FUN_0067A850(stream);
    list_0CC8.FUN_0067A520(stream);
    list_0CE4.FUN_0067A850(stream);
    list_02A0.FUN_0067A4A0(stream);
    list_02BC.FUN_0067A4A0(stream);
    list_02D8.FUN_0067A4A0(stream);
    // ColorAdd is the engine's RGBClass array; RGBClass::Save takes the IStream_004C6320 view of the stream.
    for (int i = 0; i < 16; ++i) {
        ((RGBClass*)&ColorAdd[i])->Save((IStream_004C6320*)stream);
    }
}
