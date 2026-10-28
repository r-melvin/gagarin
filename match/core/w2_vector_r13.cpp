// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of the out-of-line vector-template members listed below. Each is the
//   compiler-emitted body of an explicit instantiation of the shared VectorClass / DynamicVectorClass
//   templates over the element type that the retail RTTI names for the vtable the body stores.
//   The vector deleting destructors (??_E) and constructor closures (??_F) are only emitted when the
//   array form of `new` is seen, so each type has an unreferenced static helper that does that; VC6
//   drops the helper itself.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
//   Address index: see the FUNCTION annotations; element types: HashObject<uint, uint>,
//   HashObject<uint, SubzoneConnectionStruct>, HashObject<HashString, SchemeNode*>,
//   HashObject<RadarTrackingStruct, TechnoClass*>, SubzoneConnectionStruct, ZoneConnectionClass,
//   SubzoneTrackingStruct, Point2D.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
#include "pair_vector_ctor_family_methods.h"
#include "zone_connection_class.h"
#include "../_layout/geometry2d.h"

class TechnoClass;
class SchemeNode;
class HashString { public: char unknown_00[0x100]; HashString(const HashString& o); HashString& operator=(const HashString& o); };
template<class K,class V> struct HashObject { K Key; V Value; HashObject() {} HashObject(const HashObject<K,V>& o) : Key(o.Key), Value(o.Value) {} bool operator==(const HashObject<K,V>& o) const { return Key==o.Key; } bool operator!=(const HashObject<K,V>& o) const { return !(*this==o); } };
template<> struct HashObject<HashString,SchemeNode*> { HashString Key; SchemeNode* Value; HashObject(); HashObject(const HashObject<HashString,SchemeNode*>& o) : Key(o.Key), Value(o.Value) {} bool __fastcall operator==(const HashObject<HashString,SchemeNode*>& o) const; bool __fastcall operator!=(const HashObject<HashString,SchemeNode*>& o) const; };
struct RadarTrackingStruct { int unknown_00; int unknown_04; int unknown_08; RadarTrackingStruct() {} RadarTrackingStruct(const RadarTrackingStruct& o) : unknown_00(o.unknown_00), unknown_04(o.unknown_04), unknown_08(o.unknown_08) {} bool operator==(const RadarTrackingStruct& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04 && unknown_08==o.unknown_08; } bool operator!=(const RadarTrackingStruct& o) const { return !(*this==o); } };
struct SubzoneTrackingStruct
{
    DynamicVectorClass<SubzoneConnectionStruct> unknown_00; // +0x00
    unsigned short unknown_18;                              // +0x18
    unsigned char unknown_1A[2];                            // +0x1A
    int unknown_1C;                                         // +0x1C
    int unknown_20;                                         // +0x20
    SubzoneTrackingStruct();
    bool operator==(const SubzoneTrackingStruct& o) const
    {
        return unknown_18 == o.unknown_18 && unknown_1C == o.unknown_1C;
    }
    bool operator!=(const SubzoneTrackingStruct& o) const { return !(*this == o); }
};
GG_STATIC_ASSERT(sizeof(SubzoneTrackingStruct) == 0x24);

typedef HashObject<unsigned int,unsigned int> HO_II;
typedef HashObject<unsigned int,SubzoneConnectionStruct> HO_SCS;
typedef HashObject<HashString,SchemeNode*> HO_HS;
typedef HashObject<RadarTrackingStruct,TechnoClass*> HO_RT;

#define GG_ARRAY_NEW(N, T) \
    static DynamicVectorClass<T>* GgNewDyn_##N(int n) { return new DynamicVectorClass<T>[n]; } \
    static VectorClass<T>* GgNewVec_##N(int n) { return new VectorClass<T>[n]; }

// ---- HashObject<unsigned int, unsigned int> ----
GG_ARRAY_NEW(II, HO_II)
// FUNCTION: GAMEMD 0x0058AFF0
// VectorClass<HashObject<unsigned int, unsigned int>>::VectorClass(int, T*)
// FUNCTION: GAMEMD 0x0058A630
// DynamicVectorClass<HashObject<unsigned int, unsigned int>>::vector deleting destructor
template class VectorClass<HO_II>;
template class DynamicVectorClass<HO_II>;

// ---- HashObject<unsigned int, SubzoneConnectionStruct> ----
GG_ARRAY_NEW(SCS, HO_SCS)
// FUNCTION: GAMEMD 0x0058B070
// VectorClass<HashObject<unsigned int, SubzoneConnectionStruct>>::VectorClass(int, T*)
// FUNCTION: GAMEMD 0x0058A840
// DynamicVectorClass<HashObject<unsigned int, SubzoneConnectionStruct>>::vector deleting destructor
template class VectorClass<HO_SCS>;
template class DynamicVectorClass<HO_SCS>;

// ---- HashObject<HashString, SchemeNode*> ----
GG_ARRAY_NEW(HS, HO_HS)
// FUNCTION: GAMEMD 0x00628690
// DynamicVectorClass<HashObject<HashString, SchemeNode*>>::vector deleting destructor
// FUNCTION: GAMEMD 0x00628740
// DynamicVectorClass<HashObject<HashString, SchemeNode*>>::vector constructor closure
template class VectorClass<HO_HS>;
template class DynamicVectorClass<HO_HS>;

// ---- HashObject<RadarTrackingStruct, TechnoClass*> ----
GG_ARRAY_NEW(RT, HO_RT)
// FUNCTION: GAMEMD 0x00658C60
// DynamicVectorClass<HashObject<RadarTrackingStruct, TechnoClass*>>::vector deleting destructor
template class VectorClass<HO_RT>;
template class DynamicVectorClass<HO_RT>;

// ---- SubzoneConnectionStruct ----
GG_ARRAY_NEW(SubzoneConn, SubzoneConnectionStruct)
// FUNCTION: GAMEMD 0x00589100
// DynamicVectorClass<SubzoneConnectionStruct>::DynamicVectorClass(int, T*)
template class VectorClass<SubzoneConnectionStruct>;
template class DynamicVectorClass<SubzoneConnectionStruct>;

// ---- ZoneConnectionClass ----
GG_ARRAY_NEW(ZCC, ZoneConnectionClass)
// FUNCTION: GAMEMD 0x0058ADB0
// VectorClass<ZoneConnectionClass>::VectorClass(int, T*)
template class VectorClass<ZoneConnectionClass>;
template class DynamicVectorClass<ZoneConnectionClass>;

// ---- SubzoneTrackingStruct ----
GG_ARRAY_NEW(STS, SubzoneTrackingStruct)
// FUNCTION: GAMEMD 0x00588D60
// DynamicVectorClass<SubzoneTrackingStruct>::Clear
// FUNCTION: GAMEMD 0x00589960
// VectorClass<SubzoneTrackingStruct>::Clear
// FUNCTION: GAMEMD 0x0058A470
// VectorClass<SubzoneTrackingStruct>::scalar deleting destructor
// FUNCTION: GAMEMD 0x0058A5B0
// DynamicVectorClass<SubzoneTrackingStruct>::scalar deleting destructor
template class VectorClass<SubzoneTrackingStruct>;
template class DynamicVectorClass<SubzoneTrackingStruct>;

// ---- Point2D ----
GG_ARRAY_NEW(P2, Point2D)
// FUNCTION: GAMEMD 0x00658D60
// VectorClass<Point2D>::VectorClass(int, T*)
template class VectorClass<Point2D>;
template class DynamicVectorClass<Point2D>;
