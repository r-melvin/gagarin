// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Small methods from
//   the 0x5D0000-0x6F0000 range; receivers are placeholder views of the members touched.
//
// Address index: 0x642E00 0x6CA5A0 0x6607D0 0x660000

#include <windows.h>
#include <objidl.h>
#include <stddef.h>
#include "../core/mathtbl_init_shapes.h"
#include "../_layout/frame_timer.h"
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/geometry2d.h"
#include "../_layout/obj_0069e430.h"

// The load screen's backdrop shape sits at +0x54 (see LoadScreenClass_00642AD0).
struct LoadScreenShapeView_00642E00
{
    char         unknown_00[0x54];
    Obj_0069E430* Shape;   // +0x54

    void GetPanelSize(int* width, int* height);
};
GG_STATIC_ASSERT(offsetof(LoadScreenShapeView_00642E00, Shape) == 0x54);

// FUNCTION: GAMEMD 0x642E00
// Size of the first frame of the backdrop shape plus a six pixel border.
void LoadScreenShapeView_00642E00::GetPanelSize(int* width, int* height)
{
    RectangleStruct rect = Shape->FUN_0069E7E0(0);
    *width = rect.Width + 6;
    *height = rect.Height + 6;
}

// FUNCTION: GAMEMD 0x6CA5A0
// Parse "hours:minutes:seconds:hundredths" into a count of frames at sixty to the second.
int __fastcall FUN_006CA5A0(const wchar_t* text)
{
    wchar_t buffer[12];
    wcsncpy(buffer, text, 12);
    buffer[11] = 0;
    wchar_t* colon = wcschr(buffer, L':');
    *colon = 0;
    int hours = wcstol(buffer, 0, 10);
    wchar_t* minutesText = colon + 1;
    colon = wcschr(minutesText, L':');
    *colon = 0;
    int minutes = wcstol(minutesText, 0, 10);
    wchar_t* secondsText = colon + 1;
    colon = wcschr(secondsText, L':');
    *colon = 0;
    int seconds = wcstol(secondsText, 0, 10);
    int hundredths = wcstol(colon + 1, 0, 10);
    return (unsigned int)(hundredths * 60) / 100 + (seconds + (minutes + hours * 60) * 60) * 60;
}

// One of the 0x40-byte records of the table at 0xB04DAC; two frame timers and a flag.
struct TimedRecord_00660000
{
    char         unknown_00[0x24];
    CDTimerClass unknown_24;   // +0x24
    CDTimerClass Timer;        // +0x30
    bool         Pending;      // +0x3C
    char         unknown_3D[3];

    // FUNCTION: GAMEMD 0x660050 (decl; reloc) -- process one record.
    void FUN_00660050();
};
GG_STATIC_ASSERT(offsetof(TimedRecord_00660000, Timer) == 0x30);
GG_STATIC_ASSERT(offsetof(TimedRecord_00660000, Pending) == 0x3C);
GG_STATIC_ASSERT(sizeof(TimedRecord_00660000) == 0x40);

// The growable table of records (a DynamicVectorClass of record pointers); slot 4 finds an item.
struct RecordVector_00660000
{
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual int  FindItemIndex(TimedRecord_00660000* const& item);   // slot 4
    TimedRecord_00660000** Items;    // +0x04
    int                    Capacity; // +0x08
    unsigned long          unknown_0C;
    int                    Count;    // +0x10
    int                    CapacityIncrement; // +0x14
};
GG_STATIC_ASSERT(offsetof(RecordVector_00660000, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(RecordVector_00660000, Count) == 0x10);

// GLOBAL: GAMEMD 0xB04DA8 -- the records.
extern RecordVector_00660000 DAT_00B04DA8;
// GLOBAL: GAMEMD 0xB04D78 -- trailing dword saved after the records.
extern MathTblShortPair DAT_00B04D78;

// FUNCTION: GAMEMD 0x6607D0
// Save the record table: the count, each 0x40-byte record, then the trailing dword.
bool __fastcall FUN_006607D0(IStream* stream)
{
    int count = DAT_00B04DA8.Count;
    if (stream->Write(&count, 4, 0) < 0)
        return false;
    for (int i = 0; i < count; i++) {
        if (stream->Write(DAT_00B04DA8.Items[i], 0x40, 0) < 0)
            return false;
    }
    bool saved = stream->Write(&DAT_00B04D78, 4, 0) >= 0;
    return saved;
}

// FUNCTION: GAMEMD 0x660000
// Process every record whose timer still has time left, or that is flagged pending.
void FUN_00660000()
{
    for (int i = 0; i < DAT_00B04DA8.Count; i++) {
        TimedRecord_00660000* record = DAT_00B04DA8.Items[i];
        if (record->Timer.GetTimeLeft() > 0 || record->Pending)
            record->FUN_00660050();
    }
}
