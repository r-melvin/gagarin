// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   FoggedObjectClass as far as it is modelled: the nested DrawRecord element named by the retail vector RTTI
//   (a 0x10-byte record whose equality compares the first two words, as the vector FindItemIndex inlines).
#ifndef GG_MATCH_LAYOUT_FOGGED_OBJECT_CLASS_H
#define GG_MATCH_LAYOUT_FOGGED_OBJECT_CLASS_H

class FoggedObjectClass
{
public:
    struct DrawRecord
    {
        int unknown_00;
        int unknown_04;
        unsigned char unknown_08;
        int unknown_0C;
        DrawRecord() : unknown_00(0), unknown_04(0), unknown_08(0), unknown_0C(0) {}
        DrawRecord(const DrawRecord& o) : unknown_00(o.unknown_00), unknown_04(o.unknown_04), unknown_08(o.unknown_08), unknown_0C(o.unknown_0C) {}
        bool operator==(const DrawRecord& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04; }
        bool operator!=(const DrawRecord& o) const { return !(*this==o); }
    };
};

#endif  // GG_MATCH_LAYOUT_FOGGED_OBJECT_CLASS_H
