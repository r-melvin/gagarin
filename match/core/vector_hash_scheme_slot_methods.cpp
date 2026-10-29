// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI names VectorClass/DynamicVectorClass<HashObject<HashString, SchemeNode*>> (0x104-byte elements: a 0x100-byte
// string buffer and a pointer). Element ctor 0x4F4C20, copy ctor 0x4F4C70, assignment 0x4F4CB0 and the fastcall comparisons
// 0x4F4D80/0x4F4D90 are out-of-line bodies bound by symbol map.
#include "vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

class SchemeNode; struct HashString { char unknown_00[0x100]; HashString(const HashString& o); HashString& operator=(const HashString& o); }; template<class K,class V> struct HashObject; template<> struct HashObject<HashString,SchemeNode*> { HashString Key; SchemeNode* Value; HashObject(); HashObject(const HashObject<HashString,SchemeNode*>& o) : Key(o.Key), Value(o.Value) {} bool __fastcall operator==(const HashObject<HashString,SchemeNode*>& o) const; bool __fastcall operator!=(const HashObject<HashString,SchemeNode*>& o) const; };
// FUNCTION: GAMEMD 0x006288A0
// VectorClass<HashObject<HashString, SchemeNode*>>::operator==
// FUNCTION: GAMEMD 0x006288F0
// VectorClass<HashObject<HashString, SchemeNode*>>::SetCapacity
// FUNCTION: GAMEMD 0x00628AD0
// VectorClass<HashObject<HashString, SchemeNode*>>::Slot5
// FUNCTION: GAMEMD 0x00628860
// VectorClass<HashObject<HashString, SchemeNode*>>::Slot6
// FUNCTION: GAMEMD 0x00628BB0
// DynamicVectorClass<HashObject<HashString, SchemeNode*>>::SetCapacity
// FUNCTION: GAMEMD 0x00628830
// DynamicVectorClass<HashObject<HashString, SchemeNode*>>::Slot5
template class VectorClass<HashObject<HashString,SchemeNode*> >;
template class DynamicVectorClass<HashObject<HashString,SchemeNode*> >;

