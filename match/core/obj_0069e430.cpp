// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
// /Ob1 and /Ob2 preserve the existing lifetime bodies and frame-data loader.
// Entry69E430 initializes the0x24-byte resource allocated by5B40B0.
// Identity remains unknown; the fields retain address-based names.
#include "../_layout/obj_0069e430.h"
#include "../platform/ccfile_class.h"
#include <string.h>
#include <stdlib.h>
#include <new>
#include "../_layout/geometry2d.h"
#include "../_layout/color_struct.h"

// GLOBAL: GAMEMD 0x0083F870
extern unsigned int DAT_0083F870;
// GLOBAL: GAMEMD 0x00B077B0
extern Obj_0069E430* DAT_00B077B0;
extern const char STR_0083F874[]; // STRING: GAMEMD 0x0083F874 (decl; reloc)

// FUNCTION: GAMEMD 0x69E430
Obj_0069E430::Obj_0069E430(const char* name)
{
    unknown_14 = DAT_0083F870;
    ++DAT_0083F870;
    unknown_08 = _strdup(name);
    unknown_10 = 0;
    unknown_0C = 0;
    unknown_02 = 0;
    unknown_04 = 0;
    unknown_06 = 0;
    CCFileClass file(unknown_08);
    if (file.Exists(false))
        file.ReadBytes(this, 8);
    // Retail evaluates this comparison and discards its result.
    _stricmp(unknown_08, STR_0083F874);
    unknown_00 = -1;
    unknown_18 = DAT_00B077B0;
    unknown_1C = 0;
    if (DAT_00B077B0)
        DAT_00B077B0->unknown_1C = this;
    DAT_00B077B0 = this;
    unknown_20 = 0;
}

// GLOBAL: GAMEMD 0x00B077B4
Obj_0069E430* DAT_00B077B4;
// GLOBAL: GAMEMD 0x00B077B8
int DAT_00B077B8;
// GLOBAL: GAMEMD 0x00B077BC
unsigned int DAT_00B077BC;

// Partial: /Ob1 and /Ob2 score 2.1%; an inline-destructor variant reached
// 8.6% but removed the canonical destructor symbol, so it is not retained.
// Matching is held. The shared inline lifetime definitions are now recovered
// independently; the historical partial score is not remeasured here.
// FUNCTION: GAMEMD 0x69E580
Obj_0069E430* Obj_0069E430::FUN_0069E580()
{
    if (unknown_00 != -1) return this;
    if (unknown_10) return unknown_0C;
    if (DAT_00B077BC == unknown_14) return DAT_00B077B4;
    CCFileClass file(unknown_08);
    if (file.Exists(false)) {
        int size = file.GetFileSize();
        if (!DAT_00B077B4) {
            DAT_00B077B8 = size < 0x300000 ? 0x300000 : size;
            DAT_00B077B4 = static_cast<Obj_0069E430*>(operator new(DAT_00B077B8));
        } else if (DAT_00B077B8 < size) {
            delete DAT_00B077B4;
            DAT_00B077B4 = static_cast<Obj_0069E430*>(operator new(size));
            DAT_00B077B8 = size;
        }
        if (DAT_00B077B4) file.ReadBytes(DAT_00B077B4, size);
        DAT_00B077BC = unknown_14;
        return DAT_00B077B4;
    }
    DAT_00B077BC = 0;
    return 0;
}

// Binary view: frame records begin after the eight-byte header at 69E7B9.
struct GgShapeFrameRecord
{
    short unknown_00;
    short unknown_02;
    short unknown_04;
    short unknown_06;
    unsigned char unknown_08;
    unsigned char unknown_09[3];
    ColorStruct unknown_0C;
    unsigned char unknown_0F[5];
    unsigned int unknown_14;
};
GG_STATIC_ASSERT(offsetof(GgShapeFrameRecord, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(GgShapeFrameRecord, unknown_02) == 2);
GG_STATIC_ASSERT(offsetof(GgShapeFrameRecord, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(GgShapeFrameRecord, unknown_06) == 6);
GG_STATIC_ASSERT(offsetof(GgShapeFrameRecord, unknown_08) == 8);
GG_STATIC_ASSERT(sizeof(((GgShapeFrameRecord*)0)->unknown_08) == 1);
GG_STATIC_ASSERT(offsetof(GgShapeFrameRecord, unknown_0C) == 12);
GG_STATIC_ASSERT(sizeof(short) == 2);
GG_STATIC_ASSERT(offsetof(GgShapeFrameRecord, unknown_14) == 20);
GG_STATIC_ASSERT(sizeof(((GgShapeFrameRecord*)0)->unknown_14) == 4);
GG_STATIC_ASSERT(sizeof(GgShapeFrameRecord) == 24);

// FUNCTION: GAMEMD 0x69E740
char* Obj_0069E430::FUN_0069E740(unsigned int index)
{
    if (unknown_00 == -1 && !unknown_10) {
        CCFileClass file(unknown_08);
        Obj_0069E430* loaded = static_cast<Obj_0069E430*>(file.ReadWholeFile());
        if (loaded) {
            unknown_0C = loaded;
            unknown_10 = 1;
        }
    }
    Obj_0069E430* data = FUN_0069E580();
    if (data && index < static_cast<unsigned int>(data->unknown_06)) {
        GgShapeFrameRecord* record = reinterpret_cast<GgShapeFrameRecord*>(reinterpret_cast<char*>(data) + 8) + index;
        if (record && record->unknown_14) return reinterpret_cast<char*>(data) + record->unknown_14;
    }
    return 0;
}

// GLOBAL: GAMEMD 0x00B077A0
RectangleStruct DAT_00B077A0;

// FUNCTION: GAMEMD 0x69E7E0
RectangleStruct Obj_0069E430::FUN_0069E7E0(unsigned int index)
{
    Obj_0069E430* data = FUN_0069E580();
    if (data && index < static_cast<unsigned int>(data->unknown_06)) {
        GgShapeFrameRecord* record = reinterpret_cast<GgShapeFrameRecord*>(reinterpret_cast<char*>(data) + 8) + index;
        if (record) {
            RectangleStruct result = { record->unknown_00, record->unknown_02, record->unknown_04, record->unknown_06 };
            return result;
        }
    }
    return DAT_00B077A0;
}

// FUNCTION: GAMEMD 0x69E860
ColorStruct Obj_0069E430::FUN_0069E860(unsigned int index)
{
    Obj_0069E430* data = FUN_0069E580();
    if (data && index < static_cast<unsigned int>(data->unknown_06)) {
        GgShapeFrameRecord* record = reinterpret_cast<GgShapeFrameRecord*>(reinterpret_cast<char*>(data) + 8) + index;
        if (record) return ColorStruct(record->unknown_0C.R, record->unknown_0C.G, record->unknown_0C.B);
    }
    return ColorStruct(0, 0, 0);
}

// FUNCTION: GAMEMD 0x0069E8D0
bool Obj_0069E430::FUN_0069E8D0(unsigned int index)
{
    Obj_0069E430* data = FUN_0069E580();
    if (data && index < static_cast<unsigned int>(data->unknown_06)) {
        GgShapeFrameRecord* record = reinterpret_cast<GgShapeFrameRecord*>(reinterpret_cast<char*>(data) + 8) + index;
        if (record) return (record->unknown_08 & 1);
    }
    return false;
}

// Partial: native AND 2; SHR 1, compiled SHR 1; AND 1 (88.2%).
// Bitfield layout and byte-return variants did not improve this.
// FUNCTION: GAMEMD 0x0069E900
bool Obj_0069E430::FUN_0069E900(unsigned int index)
{
    Obj_0069E430* data = FUN_0069E580();
    if (data && index < static_cast<unsigned int>(data->unknown_06)) {
        GgShapeFrameRecord* record = reinterpret_cast<GgShapeFrameRecord*>(reinterpret_cast<char*>(data) + 8) + index;
        if (record) return (record->unknown_08 & 2) >> 1;
    }
    return false;
}
