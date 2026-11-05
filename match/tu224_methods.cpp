// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; complete entry-origin retail disassembly.
// Original translation unit: straw.cpp? (high; bound: between stlscore.cpp and Super.CPP)
#include <stddef.h>
#include "bit_font_print_methods.h"
#include "ccfile_class.h"
#include "_layout/file_straw.h"
extern "C" int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
extern "C" size_t __cdecl strlen(const char*);
long __cdecl FUN_007CB9B8(const wchar_t* text, wchar_t** end, int radix);
extern "C" wchar_t* __cdecl wcschr(const wchar_t*, wchar_t);
struct unknown_P4_6C96E0 {
    float v[4];
    unknown_P4_6C96E0() { for (int i = 0; i < 4; ++i) v[i] = 0; }
    unknown_P4_6C96E0 FUN_006C96E0(const unknown_P4_6C96E0& b) const;
    unknown_P4_6C96E0 FUN_006C9780(const unknown_P4_6C96E0& b) const;
};

// FUNCTION: GAMEMD 0x6C96E0
unknown_P4_6C96E0 unknown_P4_6C96E0::FUN_006C96E0(const unknown_P4_6C96E0& b) const
{
    unknown_P4_6C96E0 r;
    for (int i = 0; i < 4; ++i)
        r.v[i] = b.v[i] + v[i];
    return r;
}

// FUNCTION: GAMEMD 0x6C9780
unknown_P4_6C96E0 unknown_P4_6C96E0::FUN_006C9780(const unknown_P4_6C96E0& b) const
{
    unknown_P4_6C96E0 r;
    for (int i = 0; i < 4; ++i)
        r.v[i] = v[i] - b.v[i];
    return r;
}

struct unknown_Cues_6C9C60;
struct unknown_Parser_6C9B40 {
    char pad_0[0x808];
    void FUN_006C9EC0(FileStraw* r);
    void FUN_006C9F00();
    unknown_Cues_6C9C60* FUN_006C9F10(const char* name);
};
struct unknown_Holder_6C9B40 {
    unknown_Cues_6C9C60* Cues_0;
    bool FUN_006C9B40(const char* name);
};

// FUNCTION: GAMEMD 0x6C9B40
bool unknown_Holder_6C9B40::FUN_006C9B40(const char* name)
{
    if (name && strlen(name)) {
        CCFileClass file("subtitlemd.txt");
        if (file.Exists(0)) {
            FileStraw reader(&file);
            unknown_Parser_6C9B40 parser;
            parser.FUN_006C9EC0(&reader);
            Cues_0 = parser.FUN_006C9F10(name);
            if (!Cues_0) {
                parser.FUN_006C9F00();
                return false;
            }
            parser.FUN_006C9F00();
            return true;
        }
    }
    return false;
}

struct unknown_Cue_6C9C60 {
    unsigned int Start_0;
    unsigned int Length_4;
    unsigned int Color_8;
    int Line_C;
    int Align_10;
    const unsigned short* Text_14;
};
struct unknown_Cues_6C9C60 {
    char pad_0[4];
    unknown_Cue_6C9C60** Items_4;
    char pad_8[8];
    int Count_10;
};
struct unknown_Player_6C9C60 {
    unknown_Cues_6C9C60* Cues_0;
    int Index_4;
    unknown_Cue_6C9C60* Current_8;
    void(__cdecl* Callback_C)();
    Surface* Surface_10;
    RectangleStruct Pending_14;
    RectangleStruct Done_24;
    void FUN_006C9D40(unknown_Cue_6C9C60* cue);
    bool FUN_006C9C60(unsigned int t);
};

// FUNCTION: GAMEMD 0x6C9C60
bool unknown_Player_6C9C60::FUN_006C9C60(unsigned int t)
{
    if (!Cues_0)
        return false;
    bool r = false;
    while (Index_4 < Cues_0->Count_10) {
        unknown_Cue_6C9C60* cue = Cues_0->Items_4[Index_4];
        if (cue->Start_0 > t)
            break;
        Current_8 = cue;
        ++Index_4;
        if (Callback_C) {
            Callback_C();
        } else {
            FUN_006C9D40(cue);
            r = true;
        }
    }
    if (Current_8 && t >= Current_8->Start_0 + Current_8->Length_4) {
        void(__cdecl* cb)() = Callback_C;
        Current_8 = 0;
        if (!cb && Surface_10) {
            Surface_10->FillRect(&Pending_14, 0);
            r = true;
            Done_24 = Pending_14;
            Pending_14.X = 0;
            Pending_14.Y = 0;
            Pending_14.Width = 0;
            Pending_14.Height = 0;
        }
    }
    return r;
}

struct unknown_Parsed_6CA6A0 {
    char pad_0[0xc];
    long Number_C;
    int Kind_10;
};
struct unknown_Kind_6CA6A0 {
    const wchar_t* name;
    int value;
};
extern unknown_Kind_6CA6A0 DAT_008421D8[];

// FUNCTION: GAMEMD 0x6CA6A0
void __fastcall FUN_006CA6A0(wchar_t* text, unknown_Parsed_6CA6A0* out)
{
    wchar_t* colon = wcschr(text, 0x3a);
    if (colon) {
        *colon = 0;
        out->Number_C = FUN_007CB9B8(text, 0, 0);
        text = colon + 1;
    }
    int kind = 2;
    for (int i = 0; DAT_008421D8[i].name; ++i) {
        if (!_wcsicmp(text, DAT_008421D8[i].name)) {
            kind = DAT_008421D8[i].value;
            break;
        }
    }
    out->Kind_10 = kind;
}
