// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAUWinsockBufferType@WinsockInterfaceClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
#include "../network/transport/winsock_interface_class.h"

// FUNCTION: GAMEMD 0x7B2840
// DynamicVectorClass<WinsockInterfaceClass::WinsockBufferType*>::Clear

// FUNCTION: GAMEMD 0x7B2870
// DynamicVectorClass<WinsockInterfaceClass::WinsockBufferType*>::Slot5

// FUNCTION: GAMEMD 0x7B2890
// VectorClass<WinsockInterfaceClass::WinsockBufferType*>::Slot6

// FUNCTION: GAMEMD 0x7B28A0
// VectorClass<WinsockInterfaceClass::WinsockBufferType*>::operator==

// FUNCTION: GAMEMD 0x7B28E0
// VectorClass<WinsockInterfaceClass::WinsockBufferType*>::SetCapacity

// FUNCTION: GAMEMD 0x7B2990
// VectorClass<WinsockInterfaceClass::WinsockBufferType*>::Clear

// FUNCTION: GAMEMD 0x7B29C0
// VectorClass<WinsockInterfaceClass::WinsockBufferType*>::FindItemIndex

// FUNCTION: GAMEMD 0x7B2A00
// VectorClass<WinsockInterfaceClass::WinsockBufferType*>::Slot5

// FUNCTION: GAMEMD 0x7B2A20
// DynamicVectorClass<WinsockInterfaceClass::WinsockBufferType*>::SetCapacity

// FUNCTION: GAMEMD 0x7B2AD0
// DynamicVectorClass<WinsockInterfaceClass::WinsockBufferType*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x7B2B00
// VectorClass<WinsockInterfaceClass::WinsockBufferType*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x7B2B50
// DynamicVectorClass<WinsockInterfaceClass::WinsockBufferType*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7F7A3C -- VectorClass<WinsockInterfaceClass::WinsockBufferType*>.
template class VectorClass<WinsockInterfaceClass::WinsockBufferType*>;
typedef VectorClass<WinsockInterfaceClass::WinsockBufferType*> GgWinsockbufferVectorClass;
GG_STATIC_ASSERT(offsetof(GgWinsockbufferVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgWinsockbufferVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgWinsockbufferVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgWinsockbufferVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F7A1C -- DynamicVectorClass<WinsockInterfaceClass::WinsockBufferType*>.
template class DynamicVectorClass<WinsockInterfaceClass::WinsockBufferType*>;
typedef DynamicVectorClass<WinsockInterfaceClass::WinsockBufferType*> GgWinsockbufferDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgWinsockbufferDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgWinsockbufferDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgWinsockbufferDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgWinsockbufferDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgWinsockbufferDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgWinsockbufferDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(WinsockInterfaceClass::WinsockBufferType*) == 4);
