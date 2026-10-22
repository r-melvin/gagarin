// Provenance: own-binary-via-Ghidra
//
// Constructor of an 8-bit top-down DIB section wrapper: builds a 256-colour
// BITMAPINFO from a palette, creates the section on the window's DC, derives
// the scan-line start and signed pitch, and wraps the bits in a 1-byte-per-
// pixel buffered surface (XSurface vtable 0x7E2104, then BSurface 0x7E2070,
// pixels through MemoryBuffer 0x43AD00). Any failure sets the leading flag.
//
// The surface pair is a TU-local view: the canonical BSurface header has no
// constructor and declares Surface's out of line, while retail expands both
// here.
//
// LIBRARY: IAT 0x7E13A4 USER32!GetDC, 0x7E1464 USER32!ReleaseDC,
//   0x7E1058 GDI32!CreateDIBSection.

#include <stddef.h>
#include <stdlib.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/memory_buffer.h"

extern "C" __declspec(dllimport) void* __stdcall GetDC(void* window);
extern "C" __declspec(dllimport) int __stdcall ReleaseDC(void* window, void* dc);
extern "C" __declspec(dllimport) void* __stdcall CreateDIBSection(void* dc, void const* info, unsigned usage,
                                                                  void** bits, void* section, unsigned offset);

struct DibColor
{
    unsigned char Red;     // +0x0
    unsigned char Green;   // +0x1
    unsigned char Blue;    // +0x2
};

struct DibPalette
{
    DibColor Colors[256];
    DibColor const& operator[](int index) const { return Colors[index % 256]; }
};

struct DibQuad
{
    unsigned char Blue;       // +0x0
    unsigned char Green;      // +0x1
    unsigned char Red;        // +0x2
    unsigned char Reserved;   // +0x3
};

struct DibInfo
{
    unsigned long  Size;           // +0x00
    long           Width;          // +0x04
    long           Height;         // +0x08
    unsigned short Planes;         // +0x0C
    unsigned short BitCount;       // +0x0E
    unsigned long  Compression;    // +0x10
    unsigned long  SizeImage;      // +0x14
    long           XPelsPerMeter;  // +0x18
    long           YPelsPerMeter;  // +0x1C
    unsigned long  ClrUsed;        // +0x20
    unsigned long  ClrImportant;   // +0x24
    DibQuad        Colors[256];    // +0x28
    char           unknown_428[4];
};
GG_STATIC_ASSERT(offsetof(DibInfo, Colors) == 0x28);
GG_STATIC_ASSERT(sizeof(DibInfo) == 0x42C);   // operator new(0x42C) at 0x4A686F

// VTABLE: GAMEMD 0x7E2104
struct DibSurfaceBase
{
    DibSurfaceBase(int width, int height) : Width(width), Height(height), LockLevel(0) {}
    virtual ~DibSurfaceBase();

    int Width;       // +0x04
    int Height;      // +0x08
    int LockLevel;   // +0x0C
};

// VTABLE: GAMEMD 0x7E2070
struct DibSurface : DibSurfaceBase
{
    DibSurface(int width, int height, int bpp, void* buffer)
        : DibSurfaceBase(width, height), BytesPerPixel(bpp), Pixels(buffer, width * height * bpp)
    {
    }
    virtual ~DibSurface();

    int          BytesPerPixel;   // +0x10
    MemoryBuffer Pixels;          // +0x14
};
GG_STATIC_ASSERT(offsetof(DibSurface, BytesPerPixel) == 0x10);
GG_STATIC_ASSERT(offsetof(DibSurface, Pixels) == 0x14);
GG_STATIC_ASSERT(sizeof(DibSurface) == 0x20);   // operator new(0x20) at 0x4A699A

class DibSectionClass
{
public:
    DibSectionClass(void* window, int width, int height, DibPalette const& palette);

    bool        Failed;     // +0x00
    DibInfo*    Info;       // +0x04
    void*       Bitmap;     // +0x08
    char*       Bits;       // +0x0C
    int         Width;      // +0x10
    int         Height;     // +0x14
    char*       Start;      // +0x18
    int         Pitch;      // +0x1C
    DibSurface* Surface;    // +0x20
};
GG_STATIC_ASSERT(offsetof(DibSectionClass, Info) == 0x04);
GG_STATIC_ASSERT(offsetof(DibSectionClass, Bitmap) == 0x08);
GG_STATIC_ASSERT(offsetof(DibSectionClass, Bits) == 0x0C);
GG_STATIC_ASSERT(offsetof(DibSectionClass, Width) == 0x10);
GG_STATIC_ASSERT(offsetof(DibSectionClass, Height) == 0x14);
GG_STATIC_ASSERT(offsetof(DibSectionClass, Start) == 0x18);
GG_STATIC_ASSERT(offsetof(DibSectionClass, Pitch) == 0x1C);
GG_STATIC_ASSERT(offsetof(DibSectionClass, Surface) == 0x20);

// FUNCTION: GAMEMD 0x4A6840
DibSectionClass::DibSectionClass(void* window, int width, int height, DibPalette const& palette)
    : Failed(false),
      Info(0),
      Bitmap(0),
      Bits(0),
      Width(width),
      Height(height),
      Start(0),
      Pitch(0),
      Surface(0)
{
    Info = new DibInfo;
    if (Info == 0)
    {
        Failed = true;
        return;
    }
    Info->Size = 0x28;
    Info->Width = width;
    Info->Height = -height;
    Info->Planes = 1;
    Info->BitCount = 8;
    Info->Compression = 0;
    Info->SizeImage = 0;
    Info->XPelsPerMeter = 0;
    Info->YPelsPerMeter = 0;
    Info->ClrUsed = 256;
    Info->ClrImportant = 256;
    for (int i = 0; i < 256; i++)
    {
        DibColor const& color = palette[i];
        Info->Colors[i].Blue = color.Blue;
        Info->Colors[i].Green = color.Green;
        Info->Colors[i].Red = color.Red;
        Info->Colors[i].Reserved = 0;
    }
    void* dc = GetDC(window);
    Bitmap = CreateDIBSection(dc, Info, 0, (void**)&Bits, 0, 0);
    ReleaseDC(window, dc);
    if (Bitmap == 0)
    {
        Failed = true;
        return;
    }
    Width = Info->Width;
    Height = abs(Info->Height);
    int pitch = (Width + 3) & ~3;
    Pitch = pitch;
    if (Info->Height > 0)
    {
        Start = Bits + (Height - 1) * Width;
        pitch = -pitch;
    }
    else
    {
        Start = Bits;
    }
    Pitch = pitch;
    int stride = abs(pitch);
    Surface = new DibSurface(stride, Height, 1, Bits);
    if (Surface == 0)
    {
        Failed = true;
    }
}
