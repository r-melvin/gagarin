// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: primary vtable 0x7E32A4 (".?AVAlphaShapeClass@@"), with the
//   IRTTITypeInfo / INoticeSink / INoticeSource tables 0x7E3288 / 0x7E3280 /
//   0x7E3278 stored by every constructor. Size 0x40 from slot 12 (0x420D90
//   returns 0x40). Fields from the constructors 0x420960 / 0x420AF0: the
//   object at +0x24, the screen rectangle at +0x28 (X/Y from the arguments,
//   width/height from the image header shorts +2/+4), the image at +0x38 and
//   the byte at +0x3C that slot 10 (0x420E70) sets when the object at +0x24
//   expires and the sweep 0x420E90 deletes on.
#ifndef GG_MATCH_LAYOUT_ALPHA_SHAPE_CLASS_H
#define GG_MATCH_LAYOUT_ALPHA_SHAPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "geometry2d.h"
#include "../core/vector_class.h"

class ObjectClass;

// The image the constructor reads its size from (ObjectTypeClass +0xAC):
// only the two header shorts are touched.
struct AlphaShapeImage
{
    short unknown_00;   // +0x00
    short unknown_02;   // +0x02 the rectangle width  (MOVSX @0x4209B0)
    short unknown_04;   // +0x04 the rectangle height (MOVSX @0x4209B4)
};
GG_STATIC_ASSERT(offsetof(AlphaShapeImage, unknown_02) == 2);
GG_STATIC_ASSERT(offsetof(AlphaShapeImage, unknown_04) == 4);

// The screen rectangle. The default constructor zeroes it before the vtable
// stores (a member initialiser) and the main constructor fills it after them
// through one base register (@0x4209B8), the shape of an inline constructor.
struct AlphaShapeRect
{
    int X;        // +0x00
    int Y;        // +0x04
    int Width;    // +0x08
    int Height;   // +0x0C
    AlphaShapeRect() {}
    AlphaShapeRect(int x, int y, int w, int h) : X(x), Y(y), Width(w), Height(h) {}
};
GG_STATIC_ASSERT(sizeof(AlphaShapeRect) == 0x10);

// GLOBAL: GAMEMD 0x88A118 -- a 256x256 byte product table, (hi * lo) / 127 clamped to a byte.
extern unsigned char DAT_0088A118[0x10000];
// GLOBAL: GAMEMD 0x89A134 -- set once the table is built.
extern bool DAT_0089A134;

// The table build, expanded in both constructors and in the sweep 0x420E90.
inline void AlphaShape_BuildTable()
{
    if (!DAT_0089A134) {
        DAT_0089A134 = true;
        for (int i = 0; i < 0x10000; i++) {
            int value = (i % 256) * (i / 256) / 127;
            if (value > 255) {
                value = 255;
            }
            if (value < 0) {
                value = 0;
            } else if (value > 255) {
                value = 255;
            }
            DAT_0088A118[i] = (unsigned char)value;
        }
    }
}

// VTABLE: GAMEMD 0x7E32A4 (IPersistStream side)
// VTABLE: GAMEMD 0x7E3288 (IRTTITypeInfo side, +0x04)
// VTABLE: GAMEMD 0x7E3280 (INoticeSink side, +0x08)
// VTABLE: GAMEMD 0x7E3278 (INoticeSource side, +0x0C)
class AlphaShapeClass : public AbstractClass
{
public:
    // FUNCTION: GAMEMD 0x420960 (declaration)
    AlphaShapeClass(ObjectClass* object, int x, int y);
    // FUNCTION: GAMEMD 0x420AF0 (declaration)
    AlphaShapeClass();
    // FUNCTION: GAMEMD 0x420C50 (declaration; no-initialisation constructor)
    AlphaShapeClass(const AbstractNoInit& noInit);
    // FUNCTION: GAMEMD 0x420C80 (declaration; destructor; slot 8 = 0x421730)
    virtual ~AlphaShapeClass();

    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x420D40
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x420DE0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x420E40
    virtual void vf_10(void* target, bool removed);                       // 10  0x420E70
    virtual int vf_11();                                                  // 11  0x420D80
    virtual int vf_12();                                                  // 12  0x420D90
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x420DA0

    // FUNCTION: GAMEMD 0x420E90 (declaration)
    static void FUN_00420E90();

    ObjectClass*     unknown_24;   // +0x24 the object the shape follows
    AlphaShapeRect   unknown_28;   // +0x28 the screen rectangle
    AlphaShapeImage* unknown_38;   // +0x38 the image (cleared by Load)
    bool             unknown_3C;   // +0x3C set when the object expires

    // GLOBAL: GAMEMD 0x88A0F0
    static DynamicVectorClass<AlphaShapeClass*> Array;
};
GG_STATIC_ASSERT(offsetof(AlphaShapeClass, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(AlphaShapeClass, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(AlphaShapeClass, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(AlphaShapeClass, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(sizeof(AlphaShapeClass) == 0x40);

#endif  // GG_MATCH_LAYOUT_ALPHA_SHAPE_CLASS_H
