// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail TU name is unattested. REA byte evidence and entry-origin CFGs
// establish these routines; source names remain address placeholders.
#include "trivial_tu002_methods.h"
#include "intrusive_list_methods.h"
#include "leaf_accessor_methods.h"
#include "aligned_alloc_methods.h"
#include "small_misc32_methods.h"
#include <string.h>
#include "../platform/ccfile_class.h"
#include "../audio/audio_time_methods.h"
#include "../audio/audio_stop_methods.h"
#include <windows.h>
#include "module_tu002_stream.h"
#include "module_tu002_sound.h"
#include "bounded_copy_methods.h"
#include "list_holder_methods.h"
#include "floored_decrement_methods.h"
#include "slot_array_factory_methods.h"
#include "../audio/dsound_access_methods.h"
#include "../audio/theme_class_ai_methods.h"
#include "../platform/mix_file_class.h"
#include "sorted_list_insert_methods.h"
#include "../audio/pan_and_pitch_methods.h"

// GLOBAL: GAMEMD 0x87E448
extern double DAT_0087E448;
// GLOBAL: GAMEMD 0x7E1750
extern const double DAT_007E1750;
// GLOBAL: GAMEMD 0x87E698
extern double DAT_0087E698;
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x87E680
extern double DAT_0087E680;
// GLOBAL: GAMEMD 0x87E690
extern int DAT_0087E690;
// GLOBAL: GAMEMD 0x87E688
extern int DAT_0087E688;
// GLOBAL: GAMEMD 0x87E68C
extern int DAT_0087E68C;

// LIBRARY: GAMEMD 0x7C94BC (decl; reloc)
// FUN_007C94BC
extern "C" unsigned __cdecl FUN_007C94BC(void*, unsigned, unsigned, void*);
// LIBRARY: GAMEMD 0x7C95D3 (decl; reloc)
// FUN_007C95D3
extern "C" unsigned __cdecl FUN_007C95D3(void*, unsigned, unsigned, void*);

// GLOBAL: GAMEMD 0x816518
extern int DAT_00816518[];
// GLOBAL: GAMEMD 0x816558
extern int DAT_00816558[];
// GLOBAL: GAMEMD 0x87E7F8
extern CRITICAL_SECTION DAT_0087E7F8;
// GLOBAL: GAMEMD 0x87E810
extern ListNode DAT_0087E810;
// GLOBAL: GAMEMD 0x87E81C
extern int DAT_0087E81C;
// FUNCTION: GAMEMD 0x4024A0 (decl; reloc)
// FUN_004024A0
void FUN_004024A0(Peer_00405D40*);
// FUNCTION: GAMEMD 0x402650 (decl; reloc)
// FUN_00402650
void FUN_00402650(Peer_00405D40*);
// FUNCTION: GAMEMD 0x408E70 (decl; reloc)
// FUN_00408E70
void FUN_00408E70(Cursor_00408930*);

// GLOBAL: GAMEMD 0x87E724
extern AudioIDXData* DAT_0087E724;
// GLOBAL: GAMEMD 0x87E734
extern MixFileClass* DAT_0087E734;
// GLOBAL: GAMEMD 0x87E738
extern MixFileClass* DAT_0087E738;
// GLOBAL: GAMEMD 0x87E75C
extern int DAT_0087E75C;
// GLOBAL: GAMEMD 0x87E760
extern unsigned __int64 DAT_0087E760;
// GLOBAL: GAMEMD 0xA83D10
extern ThemeClass DAT_00A83D10;
// GLOBAL: GAMEMD 0x816514
extern void* DAT_00816514;
// FUNCTION: GAMEMD 0x402AF0 (decl; reloc)
// FUN_00402AF0
void* FUN_00402AF0(void*);
// FUNCTION: GAMEMD 0x402C70 (decl; reloc)
// FUN_00402C70
void* FUN_00402C70(int, AudioSampleData*);
// FUNCTION: GAMEMD 0x403530 (decl; reloc)
// FUN_00403530
int FUN_00403530(void*, int);
// FUNCTION: GAMEMD 0x403730 (decl; reloc)
// FUN_00403730
void FUN_00403730(void*, int);
// FUNCTION: GAMEMD 0x402990 (decl; reloc)
// FUN_00402990
void __cdecl FUN_00402990();
// FUNCTION: GAMEMD 0x403FA0 (decl; reloc)
// FUN_00403FA0
void __cdecl FUN_00403FA0();
// FUNCTION: GAMEMD 0x404E70 (decl; reloc)
// FUN_00404E70
void __cdecl FUN_00404E70();
// FUNCTION: GAMEMD 0x4081A0 (decl; reloc)
// FUN_004081A0
void __cdecl FUN_004081A0();
// FUNCTION: GAMEMD 0x752340 (decl; reloc)
// FUN_00752340
void __cdecl FUN_00752340();
// FUNCTION: GAMEMD 0x752B40 (decl; reloc)
// FUN_00752B40
void __cdecl FUN_00752B40();
// FUNCTION: GAMEMD 0x4041D0 (decl; reloc)
// FUN_004041D0
void __cdecl FUN_004041D0();
// FUNCTION: GAMEMD 0x750EC0 (decl; reloc)
// FUN_00750EC0
void __cdecl FUN_00750EC0();
// FUNCTION: GAMEMD 0x752760 (decl; reloc)
// FUN_00752760
void __cdecl FUN_00752760();
// FUNCTION: GAMEMD 0x7B84D0 (decl; reloc)
// FUN_007B84D0
void __cdecl FUN_007B84D0();
// FUNCTION: GAMEMD 0x407780 (decl; reloc)
// FUN_00407780
void FUN_00407780();
// FUNCTION: GAMEMD 0x401080 (decl; reloc)
// FUN_00401080
void FUN_00401080(void*);
// FUNCTION: GAMEMD 0x403810 (decl; reloc)
// FUN_00403810
void FUN_00403810(void*);
// LIBRARY: GAMEMD 0x7C93E8 (decl; reloc)
// FUN_007C93E8
extern "C" void __cdecl FUN_007C93E8(void*);

// GLOBAL: GAMEMD 0x87E73C
extern Obj_00401000* DAT_0087E73C;
// GLOBAL: GAMEMD 0x87E740
extern Obj_00401000* DAT_0087E740;
// GLOBAL: GAMEMD 0x87E744
extern Obj_00401000* DAT_0087E744;
// GLOBAL: GAMEMD 0x87E748
extern Obj_00401000* DAT_0087E748;
// GLOBAL: GAMEMD 0x87E74C
extern Obj_00401000* DAT_0087E74C;
// GLOBAL: GAMEMD 0x87E750
extern Obj_00401000* DAT_0087E750;
// GLOBAL: GAMEMD 0x87E754
extern Obj_00401000* DAT_0087E754;
// GLOBAL: GAMEMD 0x87E758
extern Obj_00401000* DAT_0087E758;
// GLOBAL: GAMEMD 0x87E770
extern StreamState_00407680 DAT_0087E770;
// GLOBAL: GAMEMD 0x87E7F0
extern HANDLE DAT_0087E7F0;
// GLOBAL: GAMEMD 0x87E7F4
extern DWORD DAT_0087E7F4;
// GLOBAL: GAMEMD 0x87E820
extern int DAT_0087E820;
// GLOBAL: GAMEMD 0xB04BEC
extern bool DAT_00B04BEC;
// STRING: GAMEMD 0x81628C
// "Unable to change the priority of the Streamer Thread - %s\n"
extern const char DAT_0081628C[];
// FUNCTION: GAMEMD 0x4072C0 (decl; reloc)
// FUN_004072C0
void FUN_004072C0(void*);
// FUNCTION: GAMEMD 0x407680 (decl; reloc)
// FUN_00407680
DWORD __stdcall FUN_00407680(void*);

// GLOBAL: GAMEMD 0x87E72C
extern int DAT_0087E72C;
// STRING: GAMEMD 0x81626C
// "audio"
extern const char DAT_0081626C[];
// STRING: GAMEMD 0x816274
// "AUDIO.MIX"
extern const char DAT_00816274[];
// STRING: GAMEMD 0x816280
// "AUDIOMD.MIX"
extern const char DAT_00816280[];
// STRING: GAMEMD 0x8162C8
// "Audio Stream"
extern const char DAT_008162C8[];
// STRING: GAMEMD 0x886980
// ""
extern const char DAT_00886980[];
// FUNCTION: GAMEMD 0x4011C0 (decl; reloc)
// FUN_004011C0
AudioIDXData* FUN_004011C0(const char*, const char*);
// FUNCTION: GAMEMD 0x402940 (decl; reloc)
// FUN_00402940
int __cdecl FUN_00402940();
// FUNCTION: GAMEMD 0x403ED0 (decl; reloc)
// FUN_00403ED0
int FUN_00403ED0(void*, AudioIDXData*);
// FUNCTION: GAMEMD 0x409360 (decl; reloc)
// FUN_00409360
void __cdecl FUN_00409360();
// FUNCTION: GAMEMD 0x752290 (decl; reloc)
// FUN_00752290
void __cdecl FUN_00752290();
// FUNCTION: GAMEMD 0x752AD0 (decl; reloc)
// FUN_00752AD0
void __cdecl FUN_00752AD0();
// FUNCTION: GAMEMD 0x407550 (decl; reloc)
// FUN_00407550
int FUN_00407550();
// FUNCTION: GAMEMD 0x4036C0 (decl; reloc)
// FUN_004036C0
Peer_00405D40* FUN_004036C0(void*, int);
// FUNCTION: GAMEMD 0x4079C0 (decl; reloc)
// FUN_004079C0
struct Obj_004079C0;
int FUN_004079C0(Obj_004079C0*);
// FUNCTION: GAMEMD 0x407A30 (decl; reloc)
// FUN_00407A30
int FUN_00407A30(void*);
// FUNCTION: GAMEMD 0x407A60 (decl; reloc)
// FUN_00407A60
int FUN_00407A60(void*);
// LIBRARY: GAMEMD 0x7C9430 (decl; reloc)
// FUN_007C9430
extern "C" void* __cdecl FUN_007C9430(unsigned);

// GLOBAL: GAMEMD 0x87E2C0
extern Obj_00401000 DAT_0087E2C0;
// GLOBAL: GAMEMD 0x87E4E0
extern Obj_00401000 DAT_0087E4E0;
// GLOBAL: GAMEMD 0x87E578
extern Obj_00401000 DAT_0087E578;
// GLOBAL: GAMEMD 0x87E450
extern Obj_00401000 DAT_0087E450;
// GLOBAL: GAMEMD 0x87E340
extern Obj_00401000 DAT_0087E340;
// GLOBAL: GAMEMD 0x87E6A0
extern Obj_00401000 DAT_0087E6A0;
// GLOBAL: GAMEMD 0x87E5F8
extern Obj_00401000 DAT_0087E5F8;
// GLOBAL: GAMEMD 0x87E3C0
extern Obj_00401000 DAT_0087E3C0;
// FUNCTION: GAMEMD 0x408610 (decl; reloc)
// FUN_00408610
int FUN_00408610(FileClass*, AudioSampleData*, unsigned*);

// GLOBAL: GAMEMD 0xB73550
extern HWND DAT_00B73550;
// GLOBAL: GAMEMD 0x87E874
extern DWORD DAT_0087E874;
// LIBRARY: GAMEMD 0x7C89DA (decl; reloc)
// FUN_007C89DA
extern "C" int __stdcall FUN_007C89DA(const GUID*, DirectSoundResource_00409FF0**, void*);
// FUNCTION: GAMEMD 0x4095B0 (decl; reloc)
// FUN_004095B0
DWORD __stdcall FUN_004095B0(void*);
// FUNCTION: GAMEMD 0x409880 (decl; reloc)
// FUN_00409880
int FUN_00409880(Aux_0040A6D0*, unsigned);
// FUNCTION: GAMEMD 0x409C40 (decl; reloc)
// FUN_00409C40
void FUN_00409C40(Aux_0040A6D0*);
// FUNCTION: GAMEMD 0x409DE0 (decl; reloc)
// FUN_00409DE0
int FUN_00409DE0(void*, void*, int*, const void*, int*);

// STRING: GAMEMD 0x8166D8
// "Unable to change the priority of the Audio Thread - %s\n"
extern const char DAT_008166D8[];
// STRING: GAMEMD 0x81677C
// "Unable to set the desired primary format\n"
extern const char DAT_0081677C[];
// STRING: GAMEMD 0x816828
// "Failed to prefill buffer\n"
extern const char DAT_00816828[];
// STRING: GAMEMD 0x816808
// "Sound frame size = %d bytes\n"
extern const char DAT_00816808[];
// STRING: GAMEMD 0x8167E4
// "Failed to create playback buffer\n"
extern const char DAT_008167E4[];
// STRING: GAMEMD 0x8167C4
// "Sound buffer size = %d bytes\n"
extern const char DAT_008167C4[];
// STRING: GAMEMD 0x8167A8
// "Failed to start playback\n"
extern const char DAT_008167A8[];
// STRING: GAMEMD 0x81674C
// "Failed to restore buffer\n"
extern const char DAT_0081674C[];
// STRING: GAMEMD 0x816768
// "Restored buffer\n"
extern const char DAT_00816768[];
// STRING: GAMEMD 0x816734
// "Failed to lock buffer\n"
extern const char DAT_00816734[];
// STRING: GAMEMD 0x816710
// "Buffer management out by %d bytes\n"
extern const char DAT_00816710[];
// FUNCTION: GAMEMD 0x40ACD0 (decl; reloc)
// FUN_0040ACD0
short FUN_0040ACD0(unsigned code, State_0040ACD0* state);
// FUNCTION: GAMEMD 0x40AA70 (decl; reloc)
// FUN_0040AA70
int FUN_0040AA70(Aux_0040A6D0* state);

// FUNCTION: GAMEMD 0x406B10
int FUN_00406B10(int enabled)
{
    FUN_00409360();
    struct TimerEntry { Obj_00401000* timer; Obj_00401000** slot; };
    TimerEntry entries[] = {
        { &DAT_0087E2C0, &DAT_0087E73C },
        { &DAT_0087E4E0, &DAT_0087E744 },
        { &DAT_0087E578, &DAT_0087E740 },
        { &DAT_0087E450, &DAT_0087E748 },
        { &DAT_0087E340, &DAT_0087E74C },
        { &DAT_0087E6A0, &DAT_0087E754 },
        { &DAT_0087E5F8, &DAT_0087E750 },
        { &DAT_0087E3C0, &DAT_0087E758 },
    };
    for (int i = 0; i < 8; ++i)
    {
        FUN_00401000(entries[i].timer);
        *entries[i].slot = entries[i].timer;
    }








    if (enabled)
    {
        FUN_00402940();
        FUN_00402AF0(DAT_00816514);
        AudioSampleData format;
        format.FUN_004085A0();
        format.SampleRate = 22050;
        format.Format = 0;
        format.NumChannels = 2;
        format.BytesPerSample = 2;
        format.Data = 4;
        format.FUN_004085B0();
        DAT_0087E728 = FUN_00402C70(-1, &format);
        if (DAT_0087E728 && FUN_00403530(DAT_0087E728, 16) == 16)
        {
            // The first timer group begins at owner+68 in 406C40.
            DAT_0087E73C = reinterpret_cast<Obj_00401000*>(static_cast<char*>(DAT_0087E728) + 0x68);
            bool present;
            { CCFileClass probe(DAT_00816280); present = probe.Exists(false); }
            DAT_0087E734 = new MixFileClass(present ? DAT_00816280 : DAT_00816274, DAT_00886980);
            DAT_0087E724 = FUN_004011C0(DAT_0081626C, 0);
            if (!DAT_0087E724) enabled = 0;
        }
        else enabled = 0;
    }
    FUN_00407550();
    if (!FUN_00403ED0(DAT_0087E728, DAT_0087E724)) enabled = 0;
    FUN_00752290();
    FUN_00752AD0();
    DAT_0087E72C = enabled;
    return 1;
}
// FUNCTION: GAMEMD 0x406D40
void FUN_00406D40()
{
    if (DAT_0087E728) FUN_00403730(DAT_0087E728, 1);
    FUN_00404E70();
    FUN_004081A0();
    FUN_00752340();
    FUN_00752B40();
    FUN_00403FA0();
    FUN_00407780();
    if (DAT_0087E724) { DAT_0087E724->FUN_00401580(); DAT_0087E724 = 0; }
    if (DAT_0087E734) { delete DAT_0087E734; DAT_0087E734 = 0; }
    if (DAT_0087E738) { delete DAT_0087E738; DAT_0087E738 = 0; }
    if (DAT_0087E728) { FUN_004033C0(DAT_0087E728, 0); DAT_0087E728 = 0; }
    FUN_00402990();
}
// FUNCTION: GAMEMD 0x406DE0
int FUN_00406DE0()
{
    FUN_00402AF0(DAT_00816514);
    AudioSampleData format;
    format.FUN_004085A0();
    format.SampleRate = 22050;
    format.Format = 0;
    format.NumChannels = 2;
    format.BytesPerSample = 2;
    format.Data = 4;
    format.FUN_004085B0();
    DAT_0087E728 = FUN_00402C70(-1, &format);
    return DAT_0087E728 && FUN_00403530(DAT_0087E728, 16) == 16;
}
// FUNCTION: GAMEMD 0x406F70
void FUN_00406F70()
{
    if (!DAT_0087E75C && DAT_0087E728)
    {
        DAT_0087E75C = 1;
        unsigned __int64 now = Unsorted_AudioGetTime();
        if (now - DAT_0087E760 > 33)
        {
            FUN_004041D0();
            FUN_00750EC0();
            FUN_00752760();
            DAT_00A83D10.AI();
            FUN_007B84D0();
            DAT_0087E760 = now;
        }
        DAT_0087E75C = 0;
    }
}
// FUNCTION: GAMEMD 0x407160
void Obj_00407060::FUN_00407160() { unknown_00 |= 1; }
// FUNCTION: GAMEMD 0x4071C0
int FUN_004071C0(Timer_00401000* timer)
{
    int difference = timer->Target - timer->Value;
    if (!difference) return 0;
    if (!(timer->Flags32 & 1))
    {
        __int64 now = Unsorted_AudioGetTime();
        unsigned __int64 elapsed = now - timer->unknown_18;
        timer->unknown_18 = now;
        unsigned delta = static_cast<unsigned>(elapsed);
        if (elapsed > timer->unknown_10) delta = static_cast<unsigned>(timer->unknown_10);
        int step = timer->unknown_0C * delta;
        if (difference >= 0)
        {
            if (step <= difference) timer->Value += step;
            else timer->Value += difference;
        }
        else
        {
            if (step <= -difference) timer->Value -= step;
            else timer->Value += difference;
        }
    }
    else timer->Value = timer->Target;
    timer->Flags32 |= 2;
    return 1;
}
// FUNCTION: GAMEMD 0x407330
void __fastcall Node_004072E0::FUN_00407330(Node_004072E0* node)
{
    int requested = node->Key;
    for (Node_004072E0* cursor = Next; cursor; cursor = cursor->Next)
    {
        int key = cursor->Key;
        if (cursor == reinterpret_cast<Node_004072E0*>(key)) break;
        if (key <= requested)
        {
            node->Next = cursor;
            node->Prev = cursor->Prev;
            cursor->Prev = node;
            node->Prev->Next = node;
            return;
        }
    }
    node->Next = this;
    node->Prev = Prev;
    Prev = node;
    node->Prev->Next = node;

}
// FUNCTION: GAMEMD 0x407380
void __fastcall Node_004072E0::FUN_00407380(Node_004072E0* other)
{
    Node_004072E0* first = Next;
    Node_004072E0* last = Prev;
    if (first != this)
    {
        Node_004072E0* previous = other->Prev;
        previous->Next = first;
        first->Prev = previous;
        last->Next = other;
        other->Prev = last;
        Next = this;
        Prev = this;
        // Retail stores the header address in the ordering-key word as sentinel.
        Key = reinterpret_cast<int>(this);
    }
}
// FUNCTION: GAMEMD 0x407400
ListNode* __fastcall ListNode::FUN_00407400(int index)
{
    ListNode* node = Prev;
    while (node != this)
    {
        if (index-- == 0) return node;
        node = node->Prev;
    }
    return 0;
}
// FUNCTION: GAMEMD 0x407490
ListNode* ListNode::FUN_00407490()
{
    ListNode* node = Prev;
    if (node == node->Owner)
    {
        node = node->Prev;
        if (node == node->Owner) node = 0;
    }
    return node;
}
// FUNCTION: GAMEMD 0x4074B0
ListNode* ListNode::FUN_004074B0()
{
    ListNode* node = Next;
    if (node == node->Owner)
    {
        node = node->Next;
        if (node == node->Owner) node = 0;
    }
    return node;
}
// FUNCTION: GAMEMD 0x407540
int Obj_00407520::FUN_00407540() const
{
    int count = 0;
    for (ListNode* node = First; node; node = node->Prev) ++count;
    return count;
}
// FUNCTION: GAMEMD 0x407550
int FUN_00407550()
{
    FUN_004072C0(&DAT_0087E810);
    InitializeCriticalSection(&DAT_0087E7F8);
    DAT_0087E770.unknown_00 = 0;
    DAT_0087E770.unknown_08 = 0;
    DAT_0087E770.unknown_18 = 0;
    DAT_0087E770.unknown_10 = 1000;
    DAT_0087E770.unknown_04 = 0;
    FUN_00403820(&DAT_0087E770.unknown_20);
    DAT_0087E770.unknown_20.FUN_00403870(DAT_0087E770.unknown_10);
    DAT_0087E770.unknown_20.FUN_004038A0(DAT_0087E770.unknown_10 * 4);
    DAT_0087E770.unknown_20.FUN_004038C0(DAT_0087E770.unknown_10 * 4);
    DAT_0087E7F0 = CreateThread(0, 0x1000, FUN_00407680, &DAT_0087E770, 0, &DAT_0087E7F4);
    if (!DAT_0087E7F0) return 0;
    if (!SetThreadPriority(DAT_0087E7F0, 2))
    {
        char text[1024];
        FormatMessageA(0x1000, 0, GetLastError(), 0, text, sizeof(text), 0);
        FUN_004068E0(DAT_0081628C, text);
    }
    DAT_0087E820 = 1;
    DAT_0087E81C = 1;
    return 1;
}
// FUNCTION: GAMEMD 0x407680
DWORD __stdcall FUN_00407680(void* parameter)
{
    StreamState_00407680* state = static_cast<StreamState_00407680*>(parameter);
    state->unknown_18 = 1;
    state->unknown_08 = 0;
    while (!state->unknown_00)
    {
        state->unknown_20.FUN_00403920(Unsorted_AudioGetTime());
        EnterCriticalSection(&DAT_0087E7F8);
        for (ListNode* node = DAT_0087E810.FUN_004073C0(); node; node = node->FUN_004073E0())
        {
            Obj_00407F80* event = reinterpret_cast<Obj_00407F80*>(node);
            if (event->unknown_0C & 4)
            {
                EnterCriticalSection(&DAT_0087E7F8);
                DAT_00B04BEC = true;
                int transferred;
                int result = event->unknown_34->FUN_00408F80(event->unknown_7C, event->unknown_9C, &transferred);
                DAT_00B04BEC = false;
                event->unknown_9C -= transferred;
                if (event->unknown_9C < 1 || result == 2 || result == 0) event->unknown_0C &= ~4;
                LeaveCriticalSection(&DAT_0087E7F8);
            }
        }
        LeaveCriticalSection(&DAT_0087E7F8);
        Sleep(static_cast<DWORD>(state->unknown_10));
        ++state->unknown_04;
    }
    state->unknown_08 = 1;
    return 0;
}
// FUNCTION: GAMEMD 0x407780
void FUN_00407780()
{
    if (DAT_0087E81C)
    {
        if (DAT_0087E820)
        {
            DAT_0087E770.unknown_00 = 1;
            while (!DAT_0087E770.unknown_08) Sleep(0);
            WaitForSingleObject(DAT_0087E7F0, 5000);
            CloseHandle(DAT_0087E7F0);
            DAT_0087E820 = 0;
        }
        ListNode* node = DAT_0087E810.FUN_004073C0();
        while (node)
        {
            Obj_00407F80* event = reinterpret_cast<Obj_00407F80*>(node);
            if (!event->unknown_88 && event->unknown_14)
            {
                EnterCriticalSection(&DAT_0087E7F8);
                event->unknown_14->FUN_004025B0();
                LeaveCriticalSection(&DAT_0087E7F8);
            }
            event->FUN_00407A90();
            node = DAT_0087E810.FUN_004073C0();
        }
        DeleteCriticalSection(&DAT_0087E7F8);
        DAT_0087E81C = 0;
    }
}
// FUNCTION: GAMEMD 0x407860
Obj_00407F80* Pool_00402860::FUN_00407860(unsigned __int64 interval)
{
    if (!this) return 0;
    if (interval < 7000) interval = 7000;
    Obj_00407F80* event = static_cast<Obj_00407F80*>(FUN_007C8E17(sizeof(Obj_00407F80)));
    memset(event, 0, sizeof(Obj_00407F80));
    FUN_004072D0(event);
    event->unknown_10 = this;
    event->unknown_14 = FUN_004036C0(this, 0x1000);
    event->unknown_14->At_94 = 0;
    event->unknown_14->At_90 = 0;
    event->unknown_14->At_98 = 0;
    event->unknown_14->At_9C = 0;
    event->unknown_18 = interval;
    event->unknown_3C.FUN_004084E0();
    event->unknown_5C.FUN_004085A0();
    event->unknown_80 = 0;
    event->unknown_88 = 0;
    strcpy(event->unknown_A4, DAT_008162C8);
    if (event->unknown_14)
    {
        event->unknown_14->Voice = reinterpret_cast<Voice_00405D40*>(event);
        // Retail installs 4079C0 as the generic context callback at +B0.
        event->unknown_14->unknown_B0 = reinterpret_cast<int (__fastcall*)(void*)>(FUN_004079C0);
        event->unknown_14->At_B8 = FUN_00407A30;
        event->unknown_14->At_BC = FUN_00407A60;
        // The existing factory and pool prefixes share asserted size A4 and
        // channels at+18; this is the concrete pointer ABI at 407951.
        event->unknown_30 = reinterpret_cast<Obj_00408D00*>(FUN_004087F0());
        if (event->unknown_30)
        {
            EnterCriticalSection(&DAT_0087E7F8);
            DAT_0087E810.FUN_00407440(&event->Links);
            LeaveCriticalSection(&DAT_0087E7F8);
            return event;
        }
    }
    event->FUN_00407A90();
    return 0;
}
// FUNCTION: GAMEMD 0x407A30
int FUN_00407A30(void* context)
{
    Peer_00405D40* peer = static_cast<Peer_00405D40*>(context);
    // 407A31 loads the stream event back-pointer from +C0. The older opaque
    // peer model names its pointer Voice; this callback proves the event type.
    Obj_00407F80* event = reinterpret_cast<Obj_00407F80*>(peer->Voice);
    if (event->unknown_0C & 3) event->unknown_20 = Unsorted_AudioGetTime();
    event->unknown_0C &= ~7;
    event->unknown_80 = 0;
    return 0;
}
// FUNCTION: GAMEMD 0x407A60
int FUN_00407A60(void* context)
{
    Peer_00405D40* peer = static_cast<Peer_00405D40*>(context);
    Obj_00407F80* event = reinterpret_cast<Obj_00407F80*>(peer->Voice);
    if (event->unknown_0C & 3) event->unknown_20 = Unsorted_AudioGetTime();
    event->unknown_0C &= ~7;
    event->unknown_80 = 0;
    return 0;
}
// FUNCTION: GAMEMD 0x407A90
void Obj_00407F80::FUN_00407A90()
{
    if (Links.Next != &Links)
    {
        EnterCriticalSection(&DAT_0087E7F8);
        Links.FUN_00407450();
        LeaveCriticalSection(&DAT_0087E7F8);
    }
    if (!unknown_88 && unknown_14)
    {
        EnterCriticalSection(&DAT_0087E7F8);
        unknown_14->FUN_004025B0();
        LeaveCriticalSection(&DAT_0087E7F8);
    }
    if (unknown_34) { FUN_00408E70(unknown_34); unknown_34 = 0; }
    if (unknown_38) { FUN_00408E70(unknown_38); unknown_38 = 0; }
    if (unknown_30) unknown_30->FUN_00408840();
    if (unknown_14) FUN_004024A0(unknown_14);
    delete unknown_7C;
    FUN_007C8B3D(this);
}
// The shared file Open interface returns int; this routine remains partial.
// FUNCTION: GAMEMD 0x407B60
int __fastcall Obj_00407F80::FUN_00407B60(const char* name, int mode)
{
    if (unknown_88) return 0;
    if (unknown_14)
    {
        EnterCriticalSection(&DAT_0087E7F8);
        unknown_14->FUN_004025B0();
        LeaveCriticalSection(&DAT_0087E7F8);
    }
    if (unknown_7C) { delete unknown_7C; unknown_7C = 0; }
    if (!mode)
    {
        unknown_7C = new RawFileClass(name);
        if (unknown_7C && !unknown_7C->Exists(false)) { delete unknown_7C; unknown_7C = 0; }
    }
    if (!unknown_7C) unknown_7C = new CCFileClass(name);
    if (!unknown_7C) goto failed;
    if (!unknown_7C->Exists(false) || !unknown_7C->Open(1))
    {
        delete unknown_7C;
        unknown_7C = 0;
        goto failed;
    }
    unknown_7C->SkipCDCheck = true;
    if (!FUN_00408610(unknown_7C, &unknown_5C, &unknown_94)) goto failed;
    unknown_9C = unknown_94;
    unknown_98 = unknown_7C->Seek(0, 1);
    if (unknown_34) { FUN_00408E70(unknown_34); unknown_34 = 0; }
    if (unknown_38) { FUN_00408E70(unknown_38); unknown_38 = 0; }
    {
        int requested = unknown_5C.FUN_00408540(unknown_18);
        unknown_A0 = unknown_5C.FUN_00408540(unknown_14->unknown_1A8 * 2);
        if (unknown_30->FUN_00408D50() != requested)
        {
            unknown_30->FUN_00408970();
            Aligned_00408D80* block = FUN_00408D80(requested, 0);
            if (block) unknown_30->FUN_00408B10(block);
        }
        if (unknown_30->FUN_00408D50() != requested) goto failed;
        unknown_30->FUN_00408A70();
        unknown_34 = unknown_30->FUN_00408C30(0);
        unknown_38 = unknown_30->FUN_00408C30(1);
        if (!unknown_34 || !unknown_38) goto failed;
        unsigned __int64 preload = unknown_14->unknown_1B0 * 2;
        unsigned __int64 minimum = DAT_0087E770.unknown_10 * 4;
        if (preload <= minimum) preload = minimum;
        if (preload < 4001) preload = 4000;
        EnterCriticalSection(&DAT_0087E7F8);
        int bytes = unknown_9C;
        if (preload)
        {
            bytes = unknown_5C.FUN_00408540(preload);
            if (unknown_9C < bytes) bytes = unknown_9C;
        }
        int transferred;
        DAT_00B04BEC = true;
        int result = unknown_34->FUN_00408F80(unknown_7C, bytes, &transferred);
        DAT_00B04BEC = false;
        unknown_9C -= transferred;
        if (unknown_9C < 1 || result == 2 || result == 0) unknown_0C &= ~4;
        LeaveCriticalSection(&DAT_0087E7F8);
        if (!transferred) goto failed;
        unknown_38->FUN_00409310();
        unknown_3C.unknown_00 = unknown_38->unknown_04;
        unknown_3C.unknown_04 = unknown_5C.FUN_00408540(unknown_14->unknown_1A8);
        if (unknown_38->unknown_08 < unknown_3C.unknown_04) unknown_3C.unknown_04 = unknown_38->unknown_08;
        unknown_3C.unknown_14 = &unknown_5C;
        unknown_90 = unknown_3C.unknown_04;
        FUN_00407150(&unknown_14->unknown_10, 0x4000);
        unknown_14->FUN_00402790(&unknown_3C);
        unknown_0C |= 1;
        if (unknown_14->FUN_00402720() == 0)
        {
            unknown_28 = Unsorted_AudioGetTime();
            unknown_20 = unknown_28;
            unknown_0C |= 4;
            return 1;
        }
        unknown_0C &= ~1;
        FUN_00408E70(unknown_34); unknown_34 = 0;
        FUN_00408E70(unknown_38); unknown_38 = 0;
    }
failed:
    if (unknown_34) { FUN_00408E70(unknown_34); unknown_34 = 0; }
    if (unknown_38) { FUN_00408E70(unknown_38); unknown_38 = 0; }
    return 0;
}
// FUNCTION: GAMEMD 0x407F90
int Obj_00407F80::FUN_00407F90()
{
    int result = --unknown_88;
    if (result < 0) unknown_88 = 0;
    return result;
}

// FUNCTION: GAMEMD 0x408150
void FUN_00408150()
{
    if (DAT_0087E81C)
    {
        ListNode* node = DAT_0087E810.FUN_004073C0();
        EnterCriticalSection(&DAT_0087E7F8);
        while (node)
        {
            // Links is the event's asserted zero-offset prefix.
            Obj_00407F80* event = reinterpret_cast<Obj_00407F80*>(node);
            event->unknown_0C &= ~4;
            node = node->FUN_004073E0();
        }
        LeaveCriticalSection(&DAT_0087E7F8);
    }
}
// FUNCTION: GAMEMD 0x4082F0
void FUN_004082F0()
{
    if (DAT_0087E81C)
    {
        for (ListNode* node = DAT_0087E810.FUN_004073C0(); node; node = node->FUN_004073E0())
        {
            Obj_00407F80* event = reinterpret_cast<Obj_00407F80*>(node);
            if (event->unknown_80)
            {
                --event->unknown_80;
                if (event->unknown_80 < 0) event->unknown_80 = 0;
                if (!event->unknown_80 && event->unknown_14)
                {
                    EnterCriticalSection(&DAT_0087E7F8);
                    if (event->unknown_0C & 2) event->unknown_0C = (event->unknown_0C & ~2) | 1;
                    FUN_00402650(event->unknown_14);
                    LeaveCriticalSection(&DAT_0087E7F8);
                }
            }
        }
    }
}
// FUNCTION: GAMEMD 0x408610
int FUN_00408610(FileClass* file, AudioSampleData* output, unsigned* dataSize)
{
    Wave_0040A340* format = 0;
    int result = 0;
    if (dataSize) *dataSize = 0;
    if (!file) return 0;
    file->Seek(0, 0);
    unsigned prefix[3];
    if (file->ReadBytes(prefix, 12) != 12 || prefix[0] != 0x46464952 || prefix[2] != 0x45564157 || !file->HasHandle()) return 0;
    do
    {
        unsigned chunk[2];
        if (file->ReadBytes(chunk, 8) != 8) break;
        if (chunk[0] == 0x20746D66)
        {
            unsigned size = chunk[1] < 18 ? 18 : chunk[1];
            format = static_cast<Wave_0040A340*>(FUN_007C9430(size));
            memset(format, 0, size);
            file->ReadBytes(format, chunk[1]);
            format->extra = 0;
        }
        else
        {
            if (chunk[0] == 0x61746164)
            {
                *dataSize = chunk[1];
                if (!format) return 0;
                if (format->format == 0x11)
                {
                    output->Format = 1;
                    output->BlockAlign = format->alignment;
                    output->BytesPerSample = 2;
                }
                else
                {
                    if (format->format != 1) break;
                    output->Format = 0;
                    output->BytesPerSample = format->bits >> 3;
                }
                output->NumChannels = format->channels;
                output->ByteRate = format->average;
                output->SampleRate = format->rate;
                output->Data = 4;
                int rate = output->BytesPerSample * output->NumChannels * output->SampleRate;
                output->ByteRate = (output->Format == 1 || output->Format == 2) ? rate >> 2 : rate;
                result = 1;
                break;
            }
            file->Seek(chunk[1], 1);
        }
    } while (file->HasHandle());
    if (format) FUN_007C93E8(format);
    return result;
}
// FUNCTION: GAMEMD 0x408840
void Obj_00408D00::FUN_00408840()
{
    ListNode* sentinel = &unknown_04;
    ListNode* node = sentinel->Prev;
    while (node != sentinel)
    {
        node->FUN_00407450();
        Aligned_00408D80* block = reinterpret_cast<Aligned_00408D80*>(node);
        Obj_00408D00* owner = static_cast<Obj_00408D00*>(block->unknown_30);
        block->unknown_30 = 0;
        --owner->unknown_00;
        owner->unknown_14 -= block->Size;
        owner->unknown_10 &= ~2;
        if (block->Raw) FUN_007C8B3D(block->Raw);
        FUN_007C8B3D(block);
        node = sentinel->Prev;
    }
    FUN_00408A70();

    FUN_007C8B3D(this);
}
// FUNCTION: GAMEMD 0x408970
void Obj_00408D00::FUN_00408970()
{
    ListNode* sentinel = &unknown_04;
    ListNode* node = sentinel->Prev;
    while (node != sentinel)
    {
        node->FUN_00407450();
        Aligned_00408D80* block = reinterpret_cast<Aligned_00408D80*>(node);
        Obj_00408D00* owner = static_cast<Obj_00408D00*>(block->unknown_30);
        block->unknown_30 = 0;
        --owner->unknown_00;
        owner->unknown_14 -= block->Size;
        owner->unknown_10 &= ~2;
        if (block->Raw) FUN_007C8B3D(block->Raw);
        FUN_007C8B3D(block);
        node = sentinel->Prev;
    }
    FUN_00408A70();
}
// FUNCTION: GAMEMD 0x408A70
void Obj_00408D00::FUN_00408A70()
{
    ListNode* sentinel = &unknown_04;
    ListNode* first = sentinel->Prev;
    if (first == sentinel) first = 0;
    else if (first)
    {
        int index = 0;
        ListNode* node = first;
        do
        {
            Aligned_00408D80* block = reinterpret_cast<Aligned_00408D80*>(node);
            for (int i = 0; i < 2; ++i)
            {
                block->Entries[i].First = block->Aligned;
                block->Entries[i].Second = block->Size;
            }
            block->unknown_34 = index++;
            node = node->Prev;
        } while (node != sentinel);
    }
    for (int i = 0; i < 2; ++i)
    {
        Cursor_00408930* cursor = &Channels[i];
        cursor->Source = reinterpret_cast<Aligned_00408D80*>(first);
        cursor->unknown_34 = -1001;
        cursor->unknown_38 = cursor->unknown_34;
        cursor->unknown_30 = 0;
        cursor->unknown_2C = 0;
        cursor->unknown_0C = cursor->Source;
        cursor->unknown_04 = first ? cursor->Source->Entries[cursor->Channel].First : 0;
        cursor->unknown_08 = 0;
        cursor->Flags &= ~1;
    }
    Channels[0].unknown_34 += unknown_14;
}
// FUNCTION: GAMEMD 0x408B40
int __fastcall Obj_00408D00::FUN_00408B40(int count, int size, int shift)
{
    int total = 0;
    while (count--)
    {
        Aligned_00408D80* block = FUN_00408D80(size, shift);
        if (!block) return total;
        unknown_04.FUN_00407440(&block->Links);
        ++unknown_00;
        unknown_14 += block->Size;
        block->unknown_30 = this;
        unknown_10 &= ~2;
        ++total;
    }
    return total;
}
// FUNCTION: GAMEMD 0x408C30
Cursor_00408930* __fastcall Obj_00408D00::FUN_00408C30(int channel)
{
    Cursor_00408930* cursor = &Channels[channel];
    if (cursor->unknown_1C) return 0;
    if (!unknown_98) FUN_00408A70();
    ++cursor->unknown_1C;
    ++unknown_98;
    return cursor;
}
// FUNCTION: GAMEMD 0x408D60
int Obj_00408D00::FUN_00408D60() const
{
    return Channels[0].unknown_34 - Channels[0].unknown_38 == 0;
}
// FUNCTION: GAMEMD 0x408E50
Aligned_00408D80* Aligned_00408D80::FUN_00408E50()
{
    ListNode* node = Links.Prev;
    // Retail's sentinel lies one pointer word past the owner's base address.
    ListNode* sentinel = reinterpret_cast<ListNode*>(static_cast<char*>(unknown_30) + 4);
    if (node == sentinel)
    {
        node = node->Prev;
        if (node == sentinel) node = 0;
    }
    return reinterpret_cast<Aligned_00408D80*>(node);
}
// FUNCTION: GAMEMD 0x408EE0
int __fastcall Cursor_00408930::FUN_00408EE0(void* buffer, unsigned count)
{
    int total = 0;
    FUN_004091C0(0);
    do
    {
        unsigned chunk = unknown_08;
        if (static_cast<int>(count) < unknown_08) chunk = count;
        if (!chunk) return total;
        // +4 and descriptor entry First are 32-bit buffer addresses in retail.
        void* current = reinterpret_cast<void*>(unknown_04);
        if (Channel == 0) memcpy(current, buffer, chunk);
        else memcpy(buffer, current, chunk);
        FUN_004091C0(chunk);
        count -= chunk;
        buffer = static_cast<char*>(buffer) + chunk;
        total += chunk;
    } while (count);
    return total;
}
// FUNCTION: GAMEMD 0x00408F80
int __fastcall Cursor_00408930::FUN_00408F80(FileClass* file, int count, int* transferred)
{
    int ignored;
    FUN_004091C0(0);
    if (!transferred) transferred = &ignored;
    *transferred = 0;
    for (;;)
    {
        int chunk = unknown_08;
        if (count < chunk) chunk = count;
        if (!chunk) return 1;
        void* current = reinterpret_cast<void*>(unknown_04);
        int actual = Channel == 0 ? file->ReadBytes(current, chunk) : file->WriteBytes(current, chunk);
        if (actual < 0) unknown_24 = 0x80040000;
        if (!actual) return 2;
        if (actual == -1) return 0;
        FUN_004091C0(actual);
        count -= actual;
        *transferred += actual;
        if (!count) return 1;
    }
}

// FUNCTION: GAMEMD 0x00409030
int __fastcall Cursor_00408930::FUN_00409030(void* file, int count, int* transferred)
{
    int ignored;
    FUN_004091C0(0);
    if (!transferred) transferred = &ignored;
    *transferred = 0;
    for (;;)
    {
        int chunk = unknown_08;
        if (count < chunk) chunk = count;
        if (!chunk) return 1;
        void* current = reinterpret_cast<void*>(unknown_04);
        int actual = Channel == 0 ? FUN_007C94BC(current, 1, chunk, file) : FUN_007C95D3(current, 1, chunk, file);
        if (actual < 0) unknown_24 = 0x80040000;
        if (!actual) return 2;
        if (actual == -1) return 0;
        FUN_004091C0(actual);
        count -= actual;
        *transferred += actual;
        if (!count) return 1;
    }
}
// FUNCTION: GAMEMD 0x409100
int Cursor_00408930::FUN_00409100()
{
    int amount = unknown_2C;
    if (!amount) return 0;
    Cursor_00408930* other = static_cast<Cursor_00408930*>(FUN_00409340());
    unknown_38 += amount;
    other->unknown_34 += amount;
    Source_00408930* block = Source;
    int left = amount;
    do
    {
        Entry8b* entry = &block->Entries[Channel];
        if (left < entry->Second)
        {
            entry->First += left;
            entry->Second -= left;
            break;
        }
        left -= entry->Second;
        entry->First = block->Aligned;
        entry->Second = block->Size;
        block = block->FUN_00408E50();
    } while (left);
    Source = block;
    unknown_2C = 0;
    unknown_0C = block;
    unknown_04 = block ? block->Entries[Channel].First : 0;
    unknown_08 = 0;
    Flags &= ~1;
    FUN_004091C0(0);
    return amount;
}
// FUNCTION: GAMEMD 0x4091C0
int __fastcall Cursor_00408930::FUN_004091C0(int count)
{
    int total = 0;
    int remaining = unknown_34 - unknown_38 - unknown_2C;
    if (!remaining) { unknown_08 = 0; return 0; }
    if (remaining < count) count = remaining;
    int channel = Channel;
    for (;;)
    {
        Source_00408930* block = unknown_0C;
        if (!(Flags & 1))
        {
            int available = block->Entries[channel].Second - unknown_04 + block->Entries[channel].First;
            unknown_08 = available < remaining ? available : remaining;
        }
        else unknown_08 = remaining;
        if (!count) break;
        int used = unknown_08;
        int next;
        if (count < used) { next = unknown_04 + count; used = count; }
        else
        {
            Source_00408930* following = block->FUN_00408E50();
            unknown_0C = following;
            if (following == Source) { Flags |= 1; next = following->Aligned; }
            else next = following->Entries[channel].First;
        }
        count -= used;
        total += used;
        unknown_04 = next;
        remaining -= used;
    }
    unknown_2C += total;
    unknown_30 += total;
    // Owner's +14 is the total ring capacity (408D50 and 40928A).
    unsigned capacity = *reinterpret_cast<unsigned*>(unknown_00 + 0x14);
    if (unknown_30 >= capacity) unknown_30 %= capacity;
    if (unknown_2C && !unknown_18) FUN_00409100();
    return total;
}
// FUNCTION: GAMEMD 0x4092B0
int Cursor_00408930::FUN_004092B0()
{
    Source_00408930* block = Source;
    unknown_2C = 0;
    unknown_0C = block;
    unknown_04 = block ? block->Entries[Channel].First : 0;
    unknown_08 = 0;
    Flags &= ~1;
    return FUN_004091C0(0);
}
// FUNCTION: GAMEMD 0x409340
void* Cursor_00408930::FUN_00409340()
{
    int index = Channel + 1;
    if (index == 2) index = 0;
    return unknown_00 + 0x18 + index * 0x40;
}
// FUNCTION: GAMEMD 0x409470
int Pool_00402860::FUN_00409470()
{
    InitializeCriticalSection(&DAT_0087E880);
    if (FUN_007C89DA(0, &DAT_0087E89C, 0)) return 0x80040000;
    DAT_0087E89C->Vptr->SetCooperativeLevel(DAT_0087E89C, DAT_00B73550, 2);
    unknown_18 = 1;
    if (!DAT_0087E898)
    {
        DAT_0087E878 = 0;
        DAT_0087E850.unknown_00 = 0;
        DAT_0087E850.unknown_08 = 0;
        DAT_0087E850.unknown_18 = 0;
        DAT_0087E850.unknown_10 = 33;
        DAT_0087E850.unknown_14 = 0;
        DAT_0087E850.unknown_04 = 0;
        DAT_0087E86C = CreateThread(0, 0x1000, FUN_004095B0, &DAT_0087E850, 0, &DAT_0087E874);
        if (!DAT_0087E86C) return 0x80040000;
        ++DAT_0087E878;
        DAT_0087E898 = 1;
        if (!SetThreadPriority(DAT_0087E86C, 15))
        {
            char text[1024];
            FormatMessageA(0x1000, 0, GetLastError(), 0, text, sizeof(text), 0);
            FUN_004068E0(DAT_008166D8, text);
        }
    }
    else ++DAT_0087E878;
    return 0;
}
// FUNCTION: GAMEMD 0x4095B0
DWORD __stdcall FUN_004095B0(void* parameter)
{
    BackendState_004095B0* thread = static_cast<BackendState_004095B0*>(parameter);
    thread->unknown_18 = 1;
    thread->unknown_08 = 0;
    while (!thread->unknown_00)
    {
        Pool_00402860* owner = thread->unknown_20;
        DWORD delay = thread->unknown_10;
        if (owner)
        {
            if (owner->Pending) delay = 5;
            else
            {
                EnterCriticalSection(&DAT_0087E880);
                __int64 now = Unsorted_AudioGetTime();
                owner->unknown_170.FUN_00403920(now);
                Holder_004035D0 holder;
                ListNode* node = FUN_004035B0(owner, &holder.Node);
                while (node)
                {
                    // The enumerated voice has the list links at its zero prefix.
                    Voice_0040A6D0* voice = reinterpret_cast<Voice_0040A6D0*>(node);
                    if (voice->unknown_A4 & 1)
                    {
                        Sink_0040A6D0* buffer = voice->Aux->Sink;
                        unsigned status;
                        if (buffer && buffer->Vptr->At_24(buffer, &status) == 0 && (status & 1))
                        {
                            Aux_0040A6D0* state = voice->Aux;
                            state->unknown_18 = now - state->unknown_10;
                            state->unknown_10 = now;
                            unsigned play;
                            state->Sink->Vptr->At_10(state->Sink, &play, &state->unknown_34);
                            int difference = play / state->unknown_6C - state->unknown_0C;
                            if (difference < 0) difference += 4;
                            if (difference > 0)
                            {
                                state->unknown_0C += difference;
                                if (static_cast<unsigned>(state->unknown_0C) >= 4) state->unknown_0C &= 3;
                                state->unknown_D4 += difference;
                                unsigned bytes = difference * state->unknown_6C;
                                int result = FUN_00409880(state, bytes);
                                if (static_cast<int>(bytes) < static_cast<int>(state->unknown_40)) state->unknown_40 = bytes;
                                state->unknown_08 -= bytes;
                                if (state->unknown_08 < 1 || !result) state->Sink->Vptr->At_48(state->Sink);
                            }
                            ++state->unknown_D0;
                        }
                        else
                        {
                            buffer = voice->Aux->Sink;
                            if (buffer) buffer->Vptr->At_48(buffer);
                            if (voice->unknown_164) voice->unknown_164(voice);
                        }
                    }
                    node = holder.FUN_004035D0();
                }
                if (owner)
                {
                    FUN_00401080(DAT_0087E744);
                    FUN_00401080(DAT_0087E748);
                    FUN_00401080(DAT_0087E740);
                    FUN_00401080(DAT_0087E73C);
                    FUN_00401080(DAT_0087E754);
                    FUN_00401080(DAT_0087E758);
                    FUN_00401080(DAT_0087E750);
                    FUN_00401080(DAT_0087E74C);
                    FUN_00403810(owner);
                    FUN_00401170(DAT_0087E748);
                    FUN_00401170(DAT_0087E744);
                    FUN_00401170(DAT_0087E740);
                    FUN_00401170(DAT_0087E73C);
                    FUN_00401170(DAT_0087E754);
                    FUN_00401170(DAT_0087E758);
                    FUN_00401170(DAT_0087E750);
                    FUN_00401170(DAT_0087E74C);
                }
                LeaveCriticalSection(&DAT_0087E880);
            }
        }
        Sleep(delay);
        ++thread->unknown_04;
    }
    thread->unknown_08 = 1;
    return 0;
}
// FUNCTION: GAMEMD 0x409880
int FUN_00409880(Aux_0040A6D0* state, unsigned count)
{
    void* first = 0;
    void* second = 0;
    unsigned firstLength = 0;
    unsigned secondLength = 0;
    bool locked = false;
    int result = 0;
    if (static_cast<int>(count) > 0)
    {
        do
        {
        if (state->unknown_38 < 1)
        {
            state->unknown_30 = 0;
            state->unknown_38 = state->unknown_68;
        }
        unsigned requested = count;
        if (static_cast<unsigned>(state->unknown_38) < requested) requested = state->unknown_38;
        if (locked)
        {
            state->Sink->Vptr->At_4C(state->Sink, first, firstLength, second, secondLength);
            locked = false;
        }
        unsigned offset = state->unknown_30;
        int error = state->Sink->Vptr->At_2C(state->Sink, offset, requested, &first, &firstLength, &second, &secondLength, 0);
        int tries = 3;
        while (error)
        {
            if (state->Sink->Vptr->At_50(state->Sink))
            {
                FUN_004068E0(DAT_0081674C);
                goto finished;
            }
            state->unknown_2C = 0;
            state->unknown_08 = 0;
            state->unknown_3C = state->unknown_6C << 2;
            state->Sink->Vptr->At_34(state->Sink, 0);
            unsigned play;
            state->Sink->Vptr->At_10(state->Sink, &play, &state->unknown_34);
            state->unknown_0C = play / state->unknown_6C;
            state->unknown_10 = Unsorted_AudioGetTime();
            state->unknown_40 = state->unknown_68;
            state->Sink->Vptr->At_10(state->Sink, &state->unknown_30, &state->unknown_34);
            state->unknown_38 = state->unknown_68 - state->unknown_30;
            state->unknown_D0 = 0;
            state->unknown_D8 = state->unknown_0C;
            state->unknown_D4 = 0;
            state->unknown_DC = state->unknown_30;
            FUN_004068E0(DAT_00816768);
            if (tries-- == 0)
            {
                FUN_004068E0(DAT_00816734);
                goto finished;
            }
            error = state->Sink->Vptr->At_2C(state->Sink, offset, requested, &first, &firstLength, &second, &secondLength, 0);
        }
        locked = true;
        if (second || firstLength != requested || secondLength)
        {
            FUN_004068E0(DAT_00816710, secondLength);
            goto finished;
        }
        unsigned remaining = requested;
        unsigned written = 0;
        unsigned char* destination = static_cast<unsigned char*>(first);
        while (remaining)
        {
            unsigned transferred = remaining;
            if (!state->unknown_2C)
            {
                state->unknown_2C = -1;
                if (!state->unknown_CC)
                {
                    state->Settings->unknown_15C(state->Settings);
                    state->unknown_CC = 1;
                }
                if (!state->Settings->unknown_174 && !state->unknown_A8)
                {
                    state->Settings->unknown_160(state->Settings);
                    if (state->Settings->unknown_174) FUN_00409C40(state);
                }
                if (state->Settings->unknown_174)
                {
                    state->unknown_CC = 0;
                    state->unknown_28 = state->Settings->unknown_170;
                    state->unknown_20 = state->Settings->unknown_170;
                    state->unknown_24 = state->Settings->unknown_174;
                    state->unknown_2C = state->Settings->unknown_174;
                }
                if (!state->unknown_2C) state->unknown_2C = -1;
            }
            if (state->unknown_2C <= 0 && !state->unknown_A8)
            {
                memset(destination, state->Settings->unknown_18C == 2 ? 0 : 0x80, transferred);
                state->unknown_3C -= transferred;
            }
            else
            {
                int inputUsed = state->unknown_2C;
                int outputBytes = transferred;
                if (inputUsed < 1)
                {
                    if (!state->unknown_70(state, destination, &outputBytes, 0, 0)) goto finished;
                    inputUsed = 0;
                    state->unknown_2C = 0;
                }
                else if (!state->unknown_70(state, destination, &outputBytes, state->unknown_28, &inputUsed)) goto finished;
                transferred = outputBytes;
                state->unknown_28 += inputUsed;
                state->unknown_2C -= inputUsed;
                state->unknown_08 += transferred;
            }
            state->unknown_30 += transferred;
            state->unknown_38 -= transferred;
            written += transferred;
            destination += transferred;
            remaining -= transferred;
        }
        count -= written;
    
        } while (static_cast<int>(count) > 0);
    }
    result = 1;
finished:
    if (locked) state->Sink->Vptr->At_4C(state->Sink, first, firstLength, second, secondLength);
    return result;
}
// FUNCTION: GAMEMD 0x409C40
void FUN_00409C40(Aux_0040A6D0* state)
{
    Voice_0040A6D0* owner = state->Settings;
    if (!owner->unknown_168) return;
    AudioSampleData* format = owner->unknown_168->unknown_14;
    if (!format) format = &owner->unknown_AC->unknown_44;
    state->unknown_98 = 0;
    state->unknown_84 = 0;
    state->unknown_80 = 0;
    state->unknown_74 = 3;
    state->unknown_8C = 0;
    state->unknown_A0 = 0;
    state->unknown_A8 = 0;
    state->unknown_A4 = format->NumChannels;
    switch (format->Format)
    {
    case 0: state->unknown_70 = FUN_00409D90; break;
    case 1:
        state->unknown_70 = FUN_00409DE0;
        state->unknown_B0 = FUN_0040AA70;
        state->unknown_8C = format->BlockAlign;
        state->unknown_AC = format->BlockAlign;
        state->unknown_A0 = format->BlockAlign * 4 + 128;
        break;
    case 2: state->unknown_70 = FUN_00409DE0; break;
    }
    if (state->unknown_88 < state->unknown_8C)
    {
        if (state->unknown_7C) FUN_007C93E8(state->unknown_7C);
        state->unknown_7C = static_cast<unsigned char*>(FUN_007C9430(state->unknown_8C));
        state->unknown_88 = state->unknown_7C ? state->unknown_8C : 0;
    }
    if (state->unknown_9C < state->unknown_A0)
    {
        if (state->unknown_90) FUN_007C93E8(state->unknown_90);
        state->unknown_90 = static_cast<unsigned char*>(FUN_007C9430(state->unknown_A0));
        state->unknown_9C = state->unknown_90 ? state->unknown_A0 : 0;
    }
}
// FUNCTION: GAMEMD 0x409DE0
int FUN_00409DE0(void* context, void* destination, int* outputSize,
                 const void* input, int* inputSize)
{
    Aux_0040A6D0* state = static_cast<Aux_0040A6D0*>(context);
    unsigned inputLeft = inputSize ? *inputSize : 0;
    unsigned outputLeft = outputSize ? *outputSize : 0;
    unsigned inputUsed = 0;
    unsigned outputUsed = 0;
    unsigned char* dest = static_cast<unsigned char*>(destination);
    const unsigned char* src = static_cast<const unsigned char*>(input);
    if (!state->unknown_90 || !state->unknown_7C) return 0;
    for (;;)
    {
        if (state->unknown_74 == 0)
        {
            if (!state->unknown_84 || !src)
            {
                state->unknown_84 = 0;
                state->unknown_74 = state->unknown_78;
            }
            else
            {
                unsigned chunk = state->unknown_84;
                if (static_cast<int>(inputLeft) < static_cast<int>(chunk)) chunk = inputLeft;
                if (!chunk) goto finished;
                memcpy(state->unknown_7C + state->unknown_80 - state->unknown_84, src, chunk);
                inputLeft -= chunk;
                inputUsed += chunk;
                state->unknown_84 -= chunk;
                state->unknown_A8 = 1;
                src += chunk;
            }
        }
        else if (state->unknown_74 == 1)
        {
            if (!state->unknown_98)
            {
                state->unknown_A8 = 0;
                state->unknown_74 = state->unknown_78;
            }
            else
            {
                unsigned chunk = state->unknown_98;
                if (static_cast<int>(outputLeft) < static_cast<int>(chunk)) chunk = outputLeft;
                if (!chunk) goto finished;
                memcpy(dest, state->unknown_90 + state->unknown_94 - state->unknown_98, chunk);
                outputLeft -= chunk;
                outputUsed += chunk;
                dest += chunk;
                state->unknown_98 -= chunk;
            }
        }
        else if (state->unknown_74 == 2)
        {
            if (!state->unknown_B0(state)) return 0;
            state->unknown_74 = 1;
            state->unknown_98 = state->unknown_94;
            state->unknown_78 = 3;
        }
        else if (state->unknown_74 == 3)
        {
            if (!src) goto finished;
            state->unknown_74 = 0;
            state->unknown_80 = state->unknown_AC;
            state->unknown_84 = state->unknown_AC;
            state->unknown_78 = 2;
        }
    }
finished:
    if (inputSize) *inputSize = inputUsed;
    if (outputSize) *outputSize = outputUsed;
    return 1;
}
// FUNCTION: GAMEMD 0x40A090
int Pool_00402860::FUN_0040A090()
{
    Capacity = 100;
    unknown_170.FUN_00403870(33);
    unknown_170.FUN_004038A0(1056);
    unknown_170.FUN_004038C0(3168);
    Wave_0040A340 wave;
    wave.format = 1;
    wave.channels = static_cast<unsigned short>(unknown_44.NumChannels);
    wave.rate = unknown_44.SampleRate;
    wave.alignment = static_cast<unsigned short>(unknown_44.BytesPerSample * unknown_44.NumChannels);
    wave.average = wave.alignment * wave.rate;
    wave.bits = static_cast<unsigned short>(unknown_44.BytesPerSample << 3);
    wave.extra = 0;
    Descriptor_0040A340 descriptor = { 20, 1, 0, 0, 0 };
    DAT_0087E850.unknown_20 = this;
    if (DAT_0087E89C->Vptr->CreateBuffer(DAT_0087E89C, &descriptor, &DAT_0087E8A0, 0))
    {
        DAT_0087E8A0 = 0;
        return 0x80040000;
    }
    Sink_0040A6D0* buffer = reinterpret_cast<Sink_0040A6D0*>(DAT_0087E8A0);
    if (buffer->Vptr->At_38(buffer, &wave)) FUN_004068E0(DAT_0081677C);
    Caps_0040A090 caps;
    memset(&caps, 0, sizeof(caps));
    caps.size = sizeof(caps);
    DAT_0087E89C->Vptr->GetCaps(DAT_0087E89C, &caps);
    buffer = reinterpret_cast<Sink_0040A6D0*>(DAT_0087E8A0);
    buffer->Vptr->At_30(buffer, 0, 0, 1);
    unknown_1D8 = 4;
    unknown_1DC = 8;
    unknown_1E0 = 0;
    return 0;
}
// FUNCTION: GAMEMD 0x40A210
void FUN_0040A210()
{
    EnterCriticalSection(&DAT_0087E880);
    DAT_0087E850.unknown_20 = 0;
    LeaveCriticalSection(&DAT_0087E880);
    if (DAT_0087E8A0)
    {
        // Both existing declarations denote the imported sound-buffer COM ABI.
        Sink_0040A6D0* buffer = reinterpret_cast<Sink_0040A6D0*>(DAT_0087E8A0);
        buffer->Vptr->At_48(buffer);
        buffer = reinterpret_cast<Sink_0040A6D0*>(DAT_0087E8A0);
        buffer->Vptr->At_08(buffer);
        DAT_0087E8A0 = 0;
    }
}
// FUNCTION: GAMEMD 0x40A2D0
int Voice_0040A6D0::FUN_0040A2D0()
{
    Aux_0040A6D0* state = Aux;
    if (state)
    {
        if (state->unknown_7C)
        {
            FUN_007C93E8(state->unknown_7C);
            state->unknown_7C = 0;
            state->unknown_88 = 0;
        }
        if (state->unknown_90)
        {
            FUN_007C93E8(state->unknown_90);
            state->unknown_90 = 0;
            state->unknown_9C = 0;
        }
        if (state->Sink) { state->Sink->Vptr->At_08(state->Sink); state->Sink = 0; }
        FUN_007C8B3D(state);
        Aux = 0;
    }
    return 0;
}
// FUNCTION: GAMEMD 0x40A340
int Voice_0040A6D0::FUN_0040A340()
{
    Aux_0040A6D0* state = Aux;
    AudioSampleData* format = unknown_168->unknown_14;
    if (!format) format = &unknown_AC->unknown_44;
    state->Settings->FUN_00402800(format);
    if (state->Sink)
    {
        if (state->unknown_44.NumChannels == format->NumChannels && state->unknown_44.SampleRate == format->SampleRate && state->unknown_44.BytesPerSample == format->BytesPerSample)
        {
            state->Settings->unknown_1A0 = 0;
            goto ready;
        }
        state->Settings->unknown_1A0 = 1;
    }
    if (state->Sink) { state->Sink->Vptr->At_08(state->Sink); state->Sink = 0; }
    {
        Wave_0040A340 wave;
        wave.format = 1;
        wave.channels = static_cast<unsigned short>(format->NumChannels);
        wave.rate = format->SampleRate;
        wave.alignment = static_cast<unsigned short>(format->BytesPerSample * format->NumChannels);
        wave.average = wave.alignment * wave.rate;
        wave.bits = static_cast<unsigned short>(format->BytesPerSample << 3);
        wave.extra = 0;
        state->unknown_44 = *format;
        int bytes = static_cast<int>((wave.average * 3 / 100) * 8 + 1023);
        state->unknown_6C = (bytes / 1024) * 1024;
        FUN_004068E0(DAT_00816808, state->unknown_6C);
        Descriptor_0040A340 descriptor = { 20, 0xE8, state->unknown_6C << 2, 0, &wave };
        // Imported COM output interface is identical at this concrete call.
        if (DAT_0087E89C->Vptr->CreateBuffer(DAT_0087E89C, &descriptor, reinterpret_cast<SoundBuffer_0040A7B0**>(&state->Sink), 0))
        {
            state->Sink = 0;
            FUN_004068E0(DAT_008167E4);
            return 0x80040000;
        }
        state->unknown_68 = descriptor.bytes;
        FUN_004068E0(DAT_008167C4, descriptor.bytes);
    }
ready:
    state->unknown_2C = 0;
    state->unknown_08 = 0;
    state->unknown_3C = state->unknown_6C << 2;
    state->Sink->Vptr->At_34(state->Sink, 0);
    unsigned position;
    state->Sink->Vptr->At_10(state->Sink, &position, &state->unknown_34);
    state->unknown_0C = position / state->unknown_6C;
    state->unknown_10 = Unsorted_AudioGetTime();
    state->unknown_40 = state->unknown_68;
    state->Sink->Vptr->At_10(state->Sink, &state->unknown_30, &state->unknown_34);
    state->unknown_38 = state->unknown_68 - state->unknown_30;
    state->unknown_D0 = 0;
    state->unknown_D8 = state->unknown_0C;
    state->unknown_D4 = 0;
    state->unknown_DC = state->unknown_30;
    FUN_00409C40(state);
    state->unknown_CC = 0;
    state->unknown_28 = state->Settings->unknown_170;
    state->unknown_20 = state->Settings->unknown_170;
    state->unknown_24 = state->Settings->unknown_174;
    state->unknown_2C = state->Settings->unknown_174;
    if (!FUN_00409880(state, state->unknown_68))
    {
        FUN_004068E0(DAT_00816828);
        return 0x80040000;
    }
    FUN_0040A6D0();
    if (state->Sink->Vptr->At_30(state->Sink, 0, 0, 1))
    {
        FUN_004068E0(DAT_008167A8);
        return 0x80040000;
    }
    return 0;
}
// FUNCTION: GAMEMD 0x40A650
int Voice_0040A6D0::FUN_0040A650()
{
    Sink_0040A6D0* sink = Aux->Sink;
    if (sink) sink->Vptr->At_48(sink);
    return 0;
}
// FUNCTION: GAMEMD 0x40A670
int Voice_0040A6D0::FUN_0040A670()
{
    Sink_0040A6D0* sink = Aux->Sink;
    if (sink && sink->Vptr->At_30(sink, 0, 0, 1) == 0) return 0;
    return 0x80040000;
}
// FUNCTION: GAMEMD 0x40A6A0
int Voice_0040A6D0::FUN_0040A6A0()
{
    Sink_0040A6D0* sink = Aux->Sink;
    unsigned status;
    if (sink && sink->Vptr->At_24(sink, &status) == 0) return status & 1;
    return 0;
}







// FUNCTION: GAMEMD 0x40A9A0
void FUN_0040A9A0(void* context)
{
    if (context)
    {
        FUN_00401080(DAT_0087E744);
        FUN_00401080(DAT_0087E748);
        FUN_00401080(DAT_0087E740);
        FUN_00401080(DAT_0087E73C);
        FUN_00401080(DAT_0087E754);
        FUN_00401080(DAT_0087E758);
        FUN_00401080(DAT_0087E750);
        FUN_00401080(DAT_0087E74C);
        FUN_00403810(context);
        FUN_00401170(DAT_0087E748);
        FUN_00401170(DAT_0087E744);
        FUN_00401170(DAT_0087E740);
        FUN_00401170(DAT_0087E73C);
        FUN_00401170(DAT_0087E754);
        FUN_00401170(DAT_0087E758);
        FUN_00401170(DAT_0087E750);
        FUN_00401170(DAT_0087E74C);
    }
}
// FUNCTION: GAMEMD 0x40AA70
int FUN_0040AA70(Aux_0040A6D0* state)
{
    int remaining = state->unknown_80 - state->unknown_84;
    const unsigned char* input = state->unknown_7C;
    short* output = reinterpret_cast<short*>(state->unknown_90);
    state->unknown_94 = 0;
    int channels = state->unknown_A4;
    if (remaining < channels * 4) return 0;
    for (int channel = 0; channel < channels; ++channel)
    {
        State_0040ACD0* decoder = &state->unknown_B4[channel];
        int initial = input[0] + input[1] * 256;
        decoder->unknown_00 = (initial & 0x8000) ? initial - 0x10000 : initial;
        decoder->unknown_04 = input[2];
        if (input[2] > 88 || input[3]) return 0;
        input += 4;
        remaining -= 4;
        *output++ = static_cast<short>(decoder->unknown_00);
        state->unknown_94 += 2;
    }
    if (channels == 1)
    {
        int blocks = (remaining + 3U) >> 2;
        int residual = remaining - blocks * 4;
        while (blocks--)
        {
            short* dest = reinterpret_cast<short*>(state->unknown_90 + state->unknown_94);
            for (int i = 0; i < 4; ++i)
            {
                unsigned byte = *input++;
                *dest++ = FUN_0040ACD0(byte & 15, &state->unknown_B4[0]);
                *dest++ = FUN_0040ACD0(byte >> 4, &state->unknown_B4[0]);
            }
            state->unknown_94 += 16;
        }
        return residual == 0;
    }
    while (remaining > 0)
    {
        for (int channel = 0; channel < state->unknown_A4; ++channel)
        {
            short* dest = reinterpret_cast<short*>(state->unknown_90 + state->unknown_94) + channel;
            for (int i = 0; i < 4; ++i)
            {
                unsigned byte = *input++;
                *dest = FUN_0040ACD0(byte & 15, &state->unknown_B4[channel]);
                dest[state->unknown_A4] = FUN_0040ACD0(byte >> 4, &state->unknown_B4[channel]);
                dest += state->unknown_A4 * 2;
            }
        }
        state->unknown_94 += state->unknown_A4 * 16;
        remaining -= state->unknown_A4 * 4;
    }
    return remaining == 0;
}
// FUNCTION: GAMEMD 0x40ACD0
short FUN_0040ACD0(unsigned code, State_0040ACD0* state)
{
    int step = DAT_00816558[state->unknown_04];
    int delta = step >> 3;
    if (code & 1) delta += step >> 2;
    if (code & 2) delta += step >> 1;
    if (code & 4) delta += step;
    if (code & 8) delta = -delta;
    state->unknown_00 += delta;
    if (state->unknown_00 > 32767) state->unknown_00 = 32767;
    else if (state->unknown_00 < -32768) state->unknown_00 = -32768;
    state->unknown_04 += DAT_00816518[code & 255];
    if (state->unknown_04 < 0) state->unknown_04 = 0;
    else if (state->unknown_04 > 88) state->unknown_04 = 88;
    return static_cast<short>(state->unknown_00);
}







