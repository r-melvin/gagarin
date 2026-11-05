// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every displacement, constant and callee below was read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//   The classes are not bound by RTTI or a binary string at these addresses, so each
//   receiver keeps a placeholder name derived from its address. The DirectDraw calls
//   reach the surface through the slots of match/dsurface_class.h.
//
// The triangle batch (0x8A0E10) that draws the overlay texture.
// Ordered ascending by retail address.
#include <windows.h>
#include <stddef.h>
#include <string.h>
#include "_rt/gg_static_assert.h"
#include "dsurface_class.h"

// The 0x78-byte texture object built at 0x4A3270 for the objects at 0x8A0E08 / 0x8A0E0C: the
// kind, the surface description it was created from, the surface and the interface queried
// from it. Only the surface is read here.
struct Texture_004A3270
{
    int          unknown_00;         // +0x00 kind: 0 plain, 1 filled, 2 render target
    DDSurfaceDesc unknown_04;        // +0x04
    DDSurface*   unknown_70;         // +0x70 the surface
    void*        unknown_74;         // +0x74 the interface queried from it
};
GG_STATIC_ASSERT(offsetof(Texture_004A3270, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(Texture_004A3270, unknown_70) == 0x70);
GG_STATIC_ASSERT(offsetof(Texture_004A3270, unknown_74) == 0x74);
GG_STATIC_ASSERT(sizeof(Texture_004A3270) == 0x78);

// GLOBAL: GAMEMD 0x8A0E08 -- the texture the batch binds.
extern Texture_004A3270* DAT_008A0E08;

// The surface interface the batch binds before drawing: slot 3 (+0x0C) takes the texture's
// surface, slot 8 (+0x20) detaches one.
struct BoundTexture_004A3660;
struct BoundTextureVtbl_004A3660
{
    void* unknown_00[3];                                                                       // +0x00
    long (__stdcall* unknown_0C)(BoundTexture_004A3660* self, DDSurface* surface);             // +0x0C
    void* unknown_10[4];                                                                       // +0x10
    long (__stdcall* unknown_20)(BoundTexture_004A3660* self, int zero, DDSurface* surface);   // +0x20
};
GG_STATIC_ASSERT(offsetof(BoundTextureVtbl_004A3660, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(BoundTextureVtbl_004A3660, unknown_20) == 0x20);
struct BoundTexture_004A3660
{
    const BoundTextureVtbl_004A3660* lpVtbl;
};

// The renderer's device: slot 15 (+0x3C) binds a texture, slot 23 (+0x5C) sets one render
// state, slot 29 (+0x74) draws one primitive.
struct Device_004A3660;
struct DeviceVtbl_004A3660
{
    void* unknown_00[15];                                                                      // +0x00
    long (__stdcall* unknown_3C)(Device_004A3660* self, BoundTexture_004A3660* texture, int zero); // +0x3C
    void* unknown_40[7];                                                                       // +0x40
    long (__stdcall* unknown_5C)(Device_004A3660* self, int state, int value);                 // +0x5C
    void* unknown_60[5];                                                                       // +0x60
    long (__stdcall* unknown_74)(Device_004A3660* self, int type, int format, void* vertices, int count,
                                 int flags);                                                   // +0x74
};
GG_STATIC_ASSERT(offsetof(DeviceVtbl_004A3660, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(DeviceVtbl_004A3660, unknown_5C) == 0x5C);
GG_STATIC_ASSERT(offsetof(DeviceVtbl_004A3660, unknown_74) == 0x74);
struct Device_004A3660
{
    const DeviceVtbl_004A3660* lpVtbl;
};

// The interface at +0x74 of the objects at 0x8A0E04 / 0x8A0E0C: slot 3 (+0x0C) hands back a value
// for the device.
struct Source_004A3660;
struct SourceVtbl_004A3660
{
    void* unknown_00[3];                                                                       // +0x00
    long (__stdcall* unknown_0C)(Source_004A3660* self, Device_004A3660* device, int* out);    // +0x0C
};
GG_STATIC_ASSERT(offsetof(SourceVtbl_004A3660, unknown_0C) == 0x0C);
struct Source_004A3660
{
    const SourceVtbl_004A3660* lpVtbl;
};
struct SourceHolder_004A3660
{
    char            unknown_00[0x74];
    Source_004A3660* unknown_74;   // +0x74
};
GG_STATIC_ASSERT(offsetof(SourceHolder_004A3660, unknown_74) == 0x74);

// GLOBAL: GAMEMD 0x8A0E04
extern SourceHolder_004A3660* DAT_008A0E04;
// GLOBAL: GAMEMD 0x8A0E0C -- the second texture; its interface is preferred when it exists.
extern SourceHolder_004A3660* DAT_008A0E0C;
// GLOBAL: GAMEMD 0x8A0DF8
extern Device_004A3660* DAT_008A0DF8;
// GLOBAL: GAMEMD 0x89F970 -- the texture currently bound to the device.
extern BoundTexture_004A3660* DAT_0089F970;

// The 0x18004-byte batch of 96-byte vertex triples built by 0x4A3840.
struct Batch_004A3660
{
    char unknown_00[0x18000];
    int  unknown_18000;            // +0x18000 triangles queued

    // FUNCTION: GAMEMD 0x4A3660
    unsigned Draw(BoundTexture_004A3660* texture);
};
GG_STATIC_ASSERT(offsetof(Batch_004A3660, unknown_18000) == 0x18000);

// FUNCTION: GAMEMD 0x4A3660
// Bind the texture to the device, set the fixed render states and draw every queued triangle;
// the queue is emptied either way. Returns -1 when a piece is missing, else the first failure.
unsigned Batch_004A3660::Draw(BoundTexture_004A3660* texture)
{
    int count = unknown_18000;
    unknown_18000 = 0;
    if (texture == 0 || DAT_008A0E04 == 0 || DAT_008A0E04->unknown_74 == 0 || DAT_008A0E08 == 0 ||
        DAT_008A0E08->unknown_70 == 0)
    {
        return 0xFFFFFFFF;
    }
    unsigned result;
    if (DAT_0089F970 != texture)
    {
        if (DAT_0089F970 != 0)
        {
            result = DAT_0089F970->lpVtbl->unknown_20(DAT_0089F970, 0, DAT_008A0E08->unknown_70);
            if (result != 0)
            {
                return result;
            }
            DAT_0089F970 = 0;
        }
        result = texture->lpVtbl->unknown_0C(texture, DAT_008A0E08->unknown_70);
        if (result != 0)
        {
            return result;
        }
        result = DAT_008A0DF8->lpVtbl->unknown_3C(DAT_008A0DF8, texture, 0);
        if (result != 0)
        {
            return result;
        }
        DAT_0089F970 = texture;
    }
    Source_004A3660* source;
    if (DAT_008A0E0C != 0)
    {
        source = DAT_008A0E0C->unknown_74;
    }
    else
    {
        source = DAT_008A0E04->unknown_74;
    }
    int value;
    result = source->lpVtbl->unknown_0C(source, DAT_008A0DF8, &value);
    if (result != 0)
    {
        return result;
    }
    result = DAT_008A0DF8->lpVtbl->unknown_5C(DAT_008A0DF8, 1, value);
    if (result != 0)
    {
        return result;
    }
    result = DAT_008A0DF8->lpVtbl->unknown_5C(DAT_008A0DF8, 7, 1);
    if (result != 0)
    {
        return result;
    }
    result = DAT_008A0DF8->lpVtbl->unknown_5C(DAT_008A0DF8, 0xE, 0);
    if (result != 0)
    {
        return result;
    }
    result = DAT_008A0DF8->lpVtbl->unknown_5C(DAT_008A0DF8, 0x11, 2);
    result |= DAT_008A0DF8->lpVtbl->unknown_5C(DAT_008A0DF8, 0x13, 2);
    result |= DAT_008A0DF8->lpVtbl->unknown_5C(DAT_008A0DF8, 0x14, 2);
    result |= DAT_008A0DF8->lpVtbl->unknown_5C(DAT_008A0DF8, 0x1D, 0);
    result |= DAT_008A0DF8->lpVtbl->unknown_5C(DAT_008A0DF8, 0x1B, 1);
    result |= DAT_008A0DF8->lpVtbl->unknown_5C(DAT_008A0DF8, 0x16, 1);
    if (result != 0)
    {
        return result;
    }
    int i;
    for (i = 0; i < count; i++)
    {
        result = DAT_008A0DF8->lpVtbl->unknown_74(DAT_008A0DF8, 4, 3, unknown_00 + i * 0x60, 3, 0);
        if (result != 0)
        {
            break;
        }
    }
    return result;
}
