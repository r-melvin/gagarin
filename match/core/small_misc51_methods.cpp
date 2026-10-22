// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x45F1D0.

#include "small_misc51_methods.h"

// FUNCTION: GAMEMD 0x45F160
//
// Same skeleton as 0x45F1D0 and the same trailing-block layout - retail's `JNZ`
// jumps forward to the cached case - but both successful paths answer true and
// the value written is a constant rather than the measurement. Written out
// longhand rather than shared with the sibling, per the family rule.
bool Obj_0045F1D0::FUN_0045F160(Shape_0045F1D0** shape, int* bias)
{
    if (Enabled && shape != 0) {
        Shape_0045F1D0* cached = Cached;

        if (cached == 0) {
            Shape_0045F1D0* fresh = vt_09C();

            *shape = fresh;

            if (fresh != 0) {
                if (fresh->Height / 2 > 3) {
                    *bias = 3;

                    return true;
                }
            }
        } else {
            *shape = cached;
            *bias  = 0;

            return true;
        }
    }

    return false;
}

// FUNCTION: GAMEMD 0x45F1D0
bool Obj_0045F1D0::FUN_0045F1D0(Shape_0045F1D0** shape, int* half)
{
    if (Enabled && shape != 0) {
        Shape_0045F1D0* cached = Cached;

        // The cached path is the *trailing* block: retail's `JNZ` at 0x45F1EB
        // jumps forward to it, so the fresh lookup is the fall-through and the
        // guard is written as `cached == 0`. The other way round scores 21.6%.
        if (cached == 0) {
            Shape_0045F1D0* fresh = vt_09C();

            *shape = fresh;

            if (fresh != 0) {
                int height = fresh->Height / 2;

                if (height > 3) {
                    *half = height + 3;

                    return true;
                }
            }
        } else {
            *shape = cached;
            *half  = cached->Height / 2;
        }
    }

    return false;
}

// FUNCTION: GAMEMD 0x4079C0
int FUN_004079C0(Obj_004079C0* self)
{
    Sub_004079C0* sub = self->Sub;

    FUN_004091C0(sub->Buffer, sub->Extent);
    FUN_00409310(sub->Buffer);

    // Read in retail's order: the buffer pointer, then the request, then the
    // capacity off the pointer. Taking the capacity in one expression first
    // swaps which register each ends up in and shifts the compare.
    Buffer_004079C0* buffer = sub->Buffer;

    int requested = sub->Requested;
    int capacity  = buffer->Capacity;

    if (requested > capacity) {
        sub->Extent = capacity;
    } else {
        sub->Extent = requested;
    }

    int extent = sub->Extent;

    self->ExtentA = extent;
    self->ExtentB = extent;

    self->Origin = sub->Buffer->Origin;

    return 0;
}

// FUNCTION: GAMEMD 0x408460
//
// MATCHED 100% (41/41). The long-standing 87.8% residual was one adjacent
// swap: retail computes the header address (`LEA ECX,[ESI+8]`) *before* the
// four clears and cl sank it to just before the call. The cause was the four
// clears themselves being written as `*(volatile int*)&member = 0` — the
// volatile lvalue casts were added to stop the preceding `memset` making them
// dead, but they are what pinned the LEA behind them, and the stores survive
// without them anyway (the `memset` is a `REP STOSD` of a different width, so
// cl does not fold the following dword stores into it). Deleting the four
// qualifiers alone takes it to 100%.
//
// Variants measured in one compile after the qualifiers came off, all 100%
// except where noted: the header bound to a local before the clears (kept),
// the header spelled at the call site, `(char*)node + 8`, the header taken
// before the `memset`, the clears driven from a named zero, and a volatile
// qualifier left on the `Payload` clear only. Re-deriving the clears off the
// header pointer (`hdr[-2] = 0` …) is 82.9% — it addresses the stores off ECX
// where retail addresses them off ESI.
//
// Historic note (superseded): with the volatile clears in place, seven
// spellings of the header address — `(char*)node + 8`, `&node->Header[0]`,
// taken before the `memset`, a `register` local, round-tripped through a
// second local, and the clears from a named zero — all left the LEA sunk, and
// a `volatile` header local was 2.2%. The lever was never the address; it was
// the clears.
Node_00408460* FUN_00408460(int size)
{
    Node_00408460* node = (Node_00408460*)FUN_007C8E17(0x20);

    memset(node, 0, 0x20);

    // The header address is taken before the four clears, which is where
    // retail's `LEA ECX,[ESI+8]` sits. The clears must be plain member stores:
    // volatile lvalue casts here pin the LEA behind them (87.8%).
    void* header = node->Header;

    node->Payload  = 0;
    node->Size     = 0;
    node->field_14 = 0;
    node->field_18 = 0;

    FUN_004072C0(header);

    node->Size = size;

    void* payload = FUN_007C8E17(size);

    node->Payload = payload;

    if (payload == 0) {
        if (node) {
            FUN_007C8B3D(node);
        }

        return 0;
    }

    return node;
}

// FUNCTION: GAMEMD 0x402790
void FUN_00402790(Obj_00402790* self, Node_00402790* node)
{
    self->Node = node;

    if (node) {
        Item_00402790* item = FUN_00408520(node);

        self->Item = item;

        if (item) {
            self->CachedA = item->First;

            int second = item->Second;

            self->CachedB = second;
            self->CachedC = second;

            node->First = 0;

            return;
        }

        Node_00402790* recorded = self->Node;

        self->CachedA = recorded->First;

        int second = recorded->Second;

        self->CachedB = second;
        self->CachedC = second;
    }
}
