// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail RTTI names VectorClass/DynamicVectorClass over HashObject<unsigned int, unsigned int> and
// Point2D (both 8-byte elements with a user-declared default constructor, so the element array is
// built by the array-new counter loop). The bodies are the DynamicVectorClass constructors taking a
// capacity and optional storage, with the VectorClass constructor expanded inline.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

template<class K,class V> struct HashObject { K Key; V Value; HashObject() {} HashObject(const HashObject<K,V>& o) : Key(o.Key), Value(o.Value) {} bool operator==(const HashObject<K,V>& o) const { return Key==o.Key; } bool operator!=(const HashObject<K,V>& o) const { return !(*this==o); } };

// FUNCTION: GAMEMD 0x005BEA30
// Constructor (capacity, optional storage) of the vector of unsigned-pair hash objects.
template class DynamicVectorClass<HashObject<unsigned int,unsigned int> >;
