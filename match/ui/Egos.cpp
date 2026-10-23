// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit Egos.CPP. The name is the source-file string at 0x8207ec
//   in retail gamemd.exe v1.001, passed by the assert at 0x4c40e4 inside this object's
//   code range (0x4c35a0-0x4c4cff). Functions are in ascending retail address order.
//
// Builds a set of 256-byte colour remap tables from a palette and a list of
// 4-byte entries {index, colour, ratio, -}. The first 256 bytes map each
// entry's index byte to its table number (0xFF elsewhere); table n follows
// at +0x100 * (n + 1) and maps every colour to the palette entry nearest to
// it after blending towards the entry's colour by its ratio. The output is
// allocated when the caller passes none.
//
// The palette and colour views repeat the declarations in
// palette_rgb_blend_methods.cpp (bodies 0x626200 and 0x6612C0 live there and
// in its sibling view).

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

struct ColorRGB_00661350
{
    unsigned char unknown_00;   // +0x00
    unsigned char unknown_01;   // +0x01
    unsigned char unknown_02;   // +0x02

    void Blend(int ratio, const ColorRGB_00661350& target);   // 0x6612C0
};
GG_STATIC_ASSERT(sizeof(ColorRGB_00661350) == 0x03);

struct ColorTable_00626070
{
    ColorRGB_00661350 Colors[256];   // +0x000

    const ColorRGB_00661350& operator[](int index) const { return Colors[index % 256]; }
    int Nearest(const ColorRGB_00661350& color) const;          // 0x626200
};

struct RemapEntry
{
    unsigned char Index;        // +0x0
    unsigned char Color;        // +0x1
    unsigned char Ratio;        // +0x2
    unsigned char unknown_03;   // +0x3
};
GG_STATIC_ASSERT(sizeof(RemapEntry) == 4);   // entry pointer steps by 4


// Retail PAVEgoClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "../core/vector_class_operations.h"

class EgoClass;

// VTABLE: GAMEMD 0x7E86FC -- VectorClass<EgoClass*>.
template class VectorClass<EgoClass*>;
typedef VectorClass<EgoClass*> GgEgoClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgEgoClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgEgoClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgEgoClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgEgoClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E86DC -- DynamicVectorClass<EgoClass*>.
template class DynamicVectorClass<EgoClass*>;
typedef DynamicVectorClass<EgoClass*> GgEgoClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgEgoClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgEgoClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgEgoClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgEgoClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgEgoClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgEgoClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(EgoClass*) == 4);

// FUNCTION: GAMEMD 0x4C38E0
unsigned char* FUN_004c38e0(const ColorTable_00626070& palette, const RemapEntry* entries,
                            int count, unsigned char* buffer)
{
    if (count != 0 && entries != 0)
    {
        if (buffer == 0)
        {
            buffer = new unsigned char[(count + 1) * 256];
        }
        if (buffer != 0)
        {
            memset(buffer, 0xFF, 256);
            unsigned char* table = buffer + 256;
            for (int i = 0; i < count; i++)
            {
                buffer[entries[i].Index] = (unsigned char)i;
                int color_index = entries[i].Color;
                int ratio = entries[i].Ratio;
                ColorRGB_00661350 target = palette[color_index];
                table[0] = 0;
                for (int j = 1; j < 256; j++)
                {
                    ColorRGB_00661350 color = palette[j];
                    color.Blend(ratio, target);
                    table[j] = (unsigned char)palette.Nearest(color);
                }
                table += 256;
            }
        }
    }
    return buffer;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C49A0
// DynamicVectorClass<EgoClass*>::Clear

// FUNCTION: GAMEMD 0x4C49D0
// DynamicVectorClass<EgoClass*>::Slot5

// FUNCTION: GAMEMD 0x4C49F0
// VectorClass<EgoClass*>::Slot6

// FUNCTION: GAMEMD 0x4C4A00
// VectorClass<EgoClass*>::operator==

// FUNCTION: GAMEMD 0x4C4A40
// VectorClass<EgoClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4C4AF0
// VectorClass<EgoClass*>::Clear

// FUNCTION: GAMEMD 0x4C4B20
// VectorClass<EgoClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4C4B60
// VectorClass<EgoClass*>::Slot5

// FUNCTION: GAMEMD 0x4C4B80
// DynamicVectorClass<EgoClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4C4C30
// DynamicVectorClass<EgoClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4C4C60
// VectorClass<EgoClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4C4CB0
// DynamicVectorClass<EgoClass*>::scalar deleting destructor
