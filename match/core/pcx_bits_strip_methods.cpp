// Provenance: own-binary-via-Ghidra
// Draws a strip of randomly chosen 10x12 frames along the top (row y + 1)
// and bottom (row y + height - 16) edges of a rectangle, from two PCX
// images ("bits_i.pcx" with its palette, "bits_a.pcx" without) held by the
// PCX cache at 0xAC4848 (renderer/pcx_get_surface_methods.h names it
// PCX; GetSurface is 0x6BA140, the draw 0x6BA690 is __thiscall `ret 0x20`).
// Every sixth frame leaves a 10-pixel gap. __fastcall free function:
// rectangle in ECX, destination surface in EDX, plain `ret`.
#include <stdlib.h>
#include "../_rt/gg_static_assert.h"

struct Rect_00621D30
{
    int X;        // +0x00
    int Y;        // +0x04
    int Width;    // +0x08
    int Height;   // +0x0C
};
GG_STATIC_ASSERT(sizeof(Rect_00621D30) == 0x10);

struct Palette_00621D30
{
    unsigned char Bytes[0x300];   // +0x000

    // FUNCTION: GAMEMD 0x6B93E0 (decl; reloc)
    void FUN_006B93E0();
};
GG_STATIC_ASSERT(sizeof(Palette_00621D30) == 0x300);

class PCXCache_00621D30
{
public:
    // FUNCTION: GAMEMD 0x6BA140 (decl; reloc)
    void* GetSurface(const char* filename, Palette_00621D30* palette);
    // FUNCTION: GAMEMD 0x6BA690 (decl; reloc)
    int Draw(Rect_00621D30* area, void* dest, void* surface, void* alpha,
             Palette_00621D30* palette, int arg5, int frame, int arg7);
};

// GLOBAL: GAMEMD 0xAC4848
extern PCXCache_00621D30 DAT_00ac4848;

// FUNCTION: GAMEMD 0x621D30
void __fastcall FUN_00621d30(Rect_00621D30* rect, void* dest)
{
    Palette_00621D30 palette;
    void* image = DAT_00ac4848.GetSurface("bits_i.pcx", &palette);
    void* alpha = DAT_00ac4848.GetSurface("bits_a.pcx", NULL);
    int count = 0;
    palette.FUN_006B93E0();

    Rect_00621D30 area = *rect;
    for (int offset = 0; offset < rect->Width; offset += 10) {
        int frame = rand() % 8;
        area.X = rect->X + offset;
        area.Y = rect->Y + 1;
        area.Width = 10;
        area.Height = 12;
        DAT_00ac4848.Draw(&area, dest, image, alpha, &palette, 0, frame * 10, 0);

        frame = rand() % 8;
        area.X = rect->X + offset;
        area.Width = 10;
        area.Height = 12;
        area.Y = rect->Y + rect->Height - 16;
        DAT_00ac4848.Draw(&area, dest, image, alpha, &palette, 0, frame * 10, 0);

        count++;
        if (count % 6 == 0) {
            offset += 10;
        }
    }
}
