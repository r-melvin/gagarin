// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   WaveClass destructor 0x75ED30 and its scalar deleting destructor 0x763200 (which carries the
//   same body inline), read off retail gamemd.exe v1.001.
//   Address index: 0x75EBE0 constructor, 0x75ED30 ~WaveClass, 0x763200 scalar deleting destructor.
//   The constructor is here because the compiler only emits the vtable (and so the deleting
//   destructor) in the TU that defines a constructor.

#include "../_layout/wave_class.h"
#include "vector_class_operations.h"

// GLOBAL: GAMEMD 0xA8EC38 -- WaveClass::Array, every live wave.
extern DynamicVectorClass<WaveClass*> DAT_00A8EC38;

// FUNCTION: GAMEMD 0x75F020 (decl; reloc)
void __stdcall FUN_0075F020();
// GLOBAL: GAMEMD 0xB725CC
extern bool DAT_00B725CC;

// FUNCTION: GAMEMD 0x75EBE0
// PARTIAL: 81.7% -- identical instruction multiset; retail stores the scalar fields in the order
// 12C, 138, 140, AC, 12D, 130, ... with the +0x1D8 member constructor after them, while the member
// initialiser list here is emitted in declaration order with the LEA of +0x1D8 hoisted to the top.
WaveClass::WaveClass()
    : unknown_12C(1),
      unknown_138(0),
      unknown_140(0),
      unknown_AC(0),
      unknown_12D(0),
      unknown_130(100),
      unknown_13C(0),
      unknown_144(0),
      unknown_148(0),
      unknown_14C(0),
      unknown_1A0(0),
      unknown_1A4(0),
      unknown_1A8(0),
      unknown_1D0(0),
      unknown_1D4(0),
      unknown_1F0(5)
{
    // The global list's append, expanded in place (growth by the increment).
    DynamicVectorClass<WaveClass*>* list = &DAT_00A8EC38;
    if (list->Count < list->Capacity
        || ((list->IsAllocated || list->Capacity == 0) && list->CapacityIncrement > 0
            && list->SetCapacity(list->CapacityIncrement + list->Capacity, 0))) {
        int index = list->Count++;
        list->Items[index] = this;
    }
    if (!DAT_00B725CC) {
        FUN_0075F020();
    }
}

// FUNCTION: GAMEMD 0x75ED30
// Announces the pointer going away, takes the wave out of the global list and clears the member
// vector through its vtable (retail calls slot 3 before the inline vector teardown).
WaveClass::~WaveClass()
{
    AnnounceExpiredPointer(1);
    DAT_00A8EC38.RemoveItem(this);
    DynamicVectorClass<CellClass*>* shots = &unknown_1F0;
    shots->Clear();
}

// SYNTHETIC: GAMEMD 0x763200 -- compiler-generated scalar deleting destructor.
