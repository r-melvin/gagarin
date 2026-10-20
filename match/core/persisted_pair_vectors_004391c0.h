// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Layout and slot uses are derived from retail gamemd.exe v1.001 instructions
//   at 0x4391C0 and 0x439260. The stream slot conventions are cross-checked
//   against the project's independently matched 0x410320/0x410380 stream
//   methods; all offsets used here are re-confirmed by the two target bodies.
#ifndef GG_MATCH_CORE_PERSISTED_PAIR_VECTORS_004391C0_H
#define GG_MATCH_CORE_PERSISTED_PAIR_VECTORS_004391C0_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "stream_persist_methods.h"

// Stream I/O uses COM stdcall: receiver, buffer, size, null out-count.
// Retail calls +0x10 in Save and +0x0C in Load. This is a slot prefix;
// concrete stream implementations supply the runtime vptr.
struct PairStreamSlots_004391C0 {
    void* slot_00;
    void* slot_04;
    void* slot_08;
    StreamIo read_0C;
    StreamIo write_10;
};
GG_STATIC_ASSERT(offsetof(PairStreamSlots_004391C0, slot_00) == 0);
GG_STATIC_ASSERT(offsetof(PairStreamSlots_004391C0, slot_04) == 4);
GG_STATIC_ASSERT(offsetof(PairStreamSlots_004391C0, slot_08) == 8);
GG_STATIC_ASSERT(offsetof(PairStreamSlots_004391C0, read_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(PairStreamSlots_004391C0, write_10) == 0x10);
GG_STATIC_ASSERT(sizeof(PairStreamSlots_004391C0) == 0x14);

// The load path calls the third vector slot at byte offset +0x08, passing
// this, a new capacity, and null; the indirect callee returns a byte in AL.
// Runtime vptrs are supplied by the objects; retail reveals the +0x08
// vector slot call at 0x4392C1/0x43936A. These three pointer cells record the
// slot offsets used by this view; the concrete table address/targets are not
// initialized in the static image at the caller global.
struct PairVectorVtableSlots_004391C0 {
    void* unknown_00;
    void* unknown_04;
    void* setCapacity_08;
};

struct PairVectorView_004391C0 {
    virtual void unknownSlot_00();
    virtual void unknownSlot_04();
    virtual bool setCapacity_08(int, void*);
    void** items;
    int capacity;
    char unknown_0C;
    unsigned char isAllocated;
    char unknown_0E[2];
    int count;
    int capacityIncrement;
};

struct PairVectorOwnerView_004391C0 {
    PairVectorView_004391C0 first;
    PairVectorView_004391C0 second;

    long Save(Stream_00410320* stream);
    long Load(Stream_00410320* stream);
};

GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(offsetof(PairVectorVtableSlots_004391C0, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(PairVectorVtableSlots_004391C0, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(PairVectorVtableSlots_004391C0, setCapacity_08) == 0x08);
GG_STATIC_ASSERT(sizeof(PairVectorVtableSlots_004391C0) == 0x0C);
GG_STATIC_ASSERT(offsetof(PairVectorView_004391C0, items) == 0x04);
GG_STATIC_ASSERT(offsetof(PairVectorView_004391C0, capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(PairVectorView_004391C0, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(PairVectorView_004391C0, isAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(PairVectorView_004391C0, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(PairVectorView_004391C0, count) == 0x10);
GG_STATIC_ASSERT(offsetof(PairVectorView_004391C0, capacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(PairVectorView_004391C0) == 0x18);
GG_STATIC_ASSERT(offsetof(PairVectorOwnerView_004391C0, first) == 0x00);
GG_STATIC_ASSERT(offsetof(PairVectorOwnerView_004391C0, second) == 0x18);
GG_STATIC_ASSERT(sizeof(PairVectorOwnerView_004391C0) == 0x30);

#endif
