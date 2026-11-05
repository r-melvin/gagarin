// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x642B10/0x642B20 (Ghidra
//   disasm). Names cross-checked against YRpp (consult-
//   only, no LICENSE; the +0x80 offset reconfirmed against the user's binary).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x642A60   ProgressScreenClass::Setup     (__thiscall)
//   FUNCTION: GAMEMD 0x642B10   ProgressScreenClass::SetSide   (__thiscall)
//   FUNCTION: GAMEMD 0x642B20   ProgressScreenClass::GetSide   (__thiscall)

#include "progress_screen_class.h"
#include "wwlib/surface/surface_class.h"
#include "file_system_load_whole_methods.h"
#include "_layout/geometry2d.h"
#include "bit_font.h"
#include "global_getter_family_methods.h"
#include "dsurface_class.h"
#include "pcx_get_surface_methods.h"

// FUNCTION: GAMEMD 0x735120 (decl; reloc) -- ANSI to wide, ECX = text.
const wchar_t* FUN_00735120(const char* text);
// FUNCTION: GAMEMD 0x4E3560 (decl; reloc) -- the loaded picture for a side index, or null.
Surface* __fastcall FUN_004E3560(int index);

class ColorScheme;
// FUNCTION: GAMEMD 0x4A61C0 (decl; reloc) -- print text inside a clip rectangle; cdecl, the result point
// comes back through a hidden first stack word.
Point2D __cdecl FUN_004A61C0(const wchar_t* text, Surface* surface, RectangleStruct* clip, Point2D* position,
                             ColorScheme* scheme, int background, int flags);

// Width of the sample line the panel is laid out around: fifteen of the same wide glyph.
static inline int SampleTextWidth(BitFont* font)
{
    unsigned short text[16];
    for (int i = 0; i < 15; i++) {
        text[i] = *FUN_00735120("W");
    }
    text[15] = 0;
    return font->FUN_00433ED0(text, 0);
}

// GLOBAL: GAMEMD 0xAC4848 -- the loaded-PCX table.
extern PCX DAT_00AC4848;

// FUNCTION: GAMEMD 0x52FF90 (decl; reloc)
void __fastcall FUN_0052FF90(const char* name, bool refresh);

// GLOBAL: GAMEMD 0x88730C -- the primary surface: every non-null store is a `new DSurface` (0x24 bytes, constructor
// 0x4BA5A0) at 0x53410D and 0x534391.
extern DSurface* DAT_0088730C;

// FUNCTION: GAMEMD 0x642A60  (__thiscall, RET 0x10)
// Start a screen: store the two leading words, clear the slot pairs, raise the flag, and
// either keep the given value or blank the primary surface; reset the progress word.
void ProgressScreenClass::Setup(int first, int second, char slotCount, int unknown)
{
    unknown_48 = first;
    unknown_4C = second;
    unknown_61 = slotCount;
    for (int i = 0; i < unknown_61; i++) {
        int* slot = &Table08[i * 2];
        slot[0] = 0;
        slot[1] = 0;
    }
    unknown_60 = true;
    if (unknown != 0) {
        unknown_64 = unknown;
    } else {
        DAT_0088730C->Fill(0);
    }
    unknown_50 = 0;
    unknown_7C = -1;
}

// FUNCTION: GAMEMD 0x642B10  (__thiscall)
// MOV EAX,[ESP+4]; MOV [ECX+0x80],EAX; RET 4
void ProgressScreenClass::SetSide(int idx)
{
    this->PlayerSide = idx;
}

// FUNCTION: GAMEMD 0x642B20  (__thiscall)
// MOV EAX,[ECX+0x80]; RET
int ProgressScreenClass::GetSide()
{
    return this->PlayerSide;
}

// FUNCTION: GAMEMD 0x642C20 (__thiscall, RET 0xC)
// Replace the screen's data file buffer with the named file, then optionally show its picture
// and remember the value.
void ProgressScreenClass::LoadBackground(const char* file, const char* picture, int value)
{
    if (file != 0) {
        if (Buffer != 0) {
            if (BufferOwned) {
                delete Buffer;
                BufferOwned = false;
            }
            Buffer = 0;
        }
        Buffer = (char*)FileSystem_LoadWholeFileEx(file, &BufferOwned);
        if (Buffer != 0) {
            if (picture != 0) {
                unknown_5C = picture;
                FUN_0052FF90(picture, false);
            }
            unknown_74 = value;
        }
    }
}

// FUNCTION: GAMEMD 0x642E80  (__fastcall)
// Width of the sample line and the font height.
void __fastcall FUN_00642E80(int* width, int* height)
{
    BitFont* font = FUN_004A60D0(0x46);
    *width = SampleTextWidth(font);
    *height = font->unknown_1C;
}

// FUNCTION: GAMEMD 0x6435B0  (__stdcall, RET 0xC)
// Blit the side picture at (x, y), keying out magenta in the display's pixel format.
void __stdcall FUN_006435B0(int x, int y, Surface* picture)
{
    int width;
    int height;
    Surface* source = FUN_004E3560(0);
    if (source == 0) {
        width = 0;
        height = 0;
    } else {
        width = source->GetWidth();
        height = source->GetHeight();
    }
    RectangleStruct area;
    area.X = x;
    area.Y = y;
    area.Width = width;
    area.Height = height;
    unsigned int key = (0xFF >> gg_b_translucent_pixel_format.loss0 << gg_b_translucent_pixel_format.pos0)
                     | (0 >> gg_b_translucent_pixel_format.loss1 << gg_b_translucent_pixel_format.pos1)
                     | (0xFF >> gg_b_translucent_pixel_format.loss2 << gg_b_translucent_pixel_format.pos2);
    if (DAT_0088730C != 0 && !DAT_0088730C->FUN_004BAFE0()) {
        DAT_00AC4848.FUN_006BA580(&area, DAT_0088730C, picture, key);
    }
}

// FUNCTION: GAMEMD 0x643670  (__stdcall, RET 0x14)
// PARTIAL: 96.5%, same instruction multiset; retail loads the `width` argument one instruction before the
// font height, here the height load comes first.
// Print `text` at `position` inside a clip as wide as the sample line (or `width` when given).
void __stdcall FUN_00643670(Point2D position, const wchar_t* text, ColorScheme* scheme, int width)
{
    BitFont* font = FUN_004A60D0(0x46);
    int sampleWidth = SampleTextWidth(font);
    int height = font->unknown_1C;
    sampleWidth = (width != -1) ? width : sampleWidth;
    RectangleStruct clip;
    clip.Width = sampleWidth + position.X;
    clip.Height = height + position.Y;
    clip.X = 0;
    clip.Y = 0;
    FUN_004A61C0(text, DAT_0088730C, &clip, &position, scheme, 0, 0x19);
}

// FUNCTION: GAMEMD 0x643E80
void ProgressScreenClass::Slot0(int value)
{
    Field04 = value;
}

