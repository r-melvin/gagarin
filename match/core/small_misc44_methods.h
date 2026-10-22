// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, globals and slot displacements read numerically off the user's
//   retail gamemd.exe v1.001 via the local Ghidra CLI at 0x408410 and 0x40A950.
#ifndef GG_MATCH_CORE_SMALL_MISC44_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC44_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "intrusive_list_methods.h"

// ---------------------------------------------------------------------------
// 0x408410 — "is every armed entry settled?"
//
// Walk the list at 0x87E810; for each node whose bit 0 is set, compare two
// counters on the object it points at and answer false the moment they differ.
// An empty or disabled list is vacuously true.
//
// The answer is an `int`, not a `bool`: retail's exits are `XOR EAX,EAX` and
// `MOV EAX,0x1` on the full register, where a `bool` return would only define
// AL (`XOR AL,AL` / `MOV AL,0x1`).
// ---------------------------------------------------------------------------
struct Tracked_00408410
{
    char _pad000[0x14];
    int  Head;   // +0x0014
    int  Tail;   // +0x0018
};
GG_STATIC_ASSERT(offsetof(Tracked_00408410, Tail) == 0x18);

struct Entry_00408410
{
    ListNode         Link;      // +0x0000
    char             Flags;     // +0x000C
    char             _pad00D[0x14 - 0x0D];
    Tracked_00408410* Tracked;  // +0x0014
};
GG_STATIC_ASSERT(offsetof(Entry_00408410, Flags) == 0xC);
GG_STATIC_ASSERT(offsetof(Entry_00408410, Tracked) == 0x14);

// GLOBAL: GAMEMD 0x87E81C — the gate; 0x87E810 is the list header itself.
extern int      DAT_0087E81C;
extern ListNode DAT_0087E810;

// FUNCTION: GAMEMD 0x408410
int __cdecl FUN_00408410();

// ---------------------------------------------------------------------------
// 0x4081A0 — run one state transition per idle armed entry, each under the
// critical section at 0x87E7F8.
//
// Both critical-section imports are hoisted into registers before the loop
// (`MOV EBX,[0x7E11EC]` then `MOV EDI,[0x7E11E8]`) and called indirectly
// through them, which is what taking their addresses into locals gives. Retail
// loads EBX (leave) before EDI (enter), and the register each ends up in
// follows the *declaration* order rather than the load order - declaring enter
// first is what produces retail's assignment.
// ---------------------------------------------------------------------------
struct CriticalSection_004081A0 { char Opaque[0x18]; };

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CriticalSection_004081A0*);  // IAT 0x7E11E8
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CriticalSection_004081A0*);  // IAT 0x7E11EC

extern CriticalSection_004081A0 DAT_0087E7F8;   // GLOBAL: GAMEMD 0x87E7F8

// FUNCTION: GAMEMD 0x4025B0 — the transition, __fastcall.
void FUN_004025B0(void* subject);

struct Armed_004081A0
{
    ListNode Link;      // +0x0000
    char     _pad00C[0x14 - 0x0C];
    void*    Subject;   // +0x0014
    char     _pad018[0x88 - 0x18];
    int      Busy;      // +0x0088
};
GG_STATIC_ASSERT(offsetof(Armed_004081A0, Subject) == 0x14);
GG_STATIC_ASSERT(offsetof(Armed_004081A0, Busy) == 0x88);

// FUNCTION: GAMEMD 0x4081A0
void __cdecl FUN_004081A0();

// ---------------------------------------------------------------------------
// 0x40A950 — poll the singleton at 0x87E8A0 and act on two status bits.
//
// Slot +0x24 fills a 4-byte status word the caller allocates with `PUSH ECX`;
// bit 1 asks for slot +0x50 and a clear bit 0 asks for slot +0x30 with three
// arguments. All three are __stdcall virtuals - the receiver goes on the stack.
//
// The global is re-read before each call rather than held, which is what retail
// does (`MOV EAX,[0x87E8A0]` three times).
// ---------------------------------------------------------------------------
struct Poller_0040A950;

typedef void (__stdcall* PollSlot1)(Poller_0040A950*, void*);
typedef void (__stdcall* PollSlot0)(Poller_0040A950*);
typedef void (__stdcall* PollSlot3)(Poller_0040A950*, int, int, int);

#define POLL_CALL1(p, off, a)       ((*(PollSlot1*)(*(char**)(p) + (off)))(p, a))
#define POLL_CALL0(p, off)          ((*(PollSlot0*)(*(char**)(p) + (off)))(p))
#define POLL_CALL3(p, off, a, b, c) ((*(PollSlot3*)(*(char**)(p) + (off)))(p, a, b, c))

extern Poller_0040A950* DAT_0087E8A0;   // GLOBAL: GAMEMD 0x87E8A0

// FUNCTION: GAMEMD 0x40A950
void __cdecl FUN_0040A950();

// ---------------------------------------------------------------------------
// 0x435560 — deleting destructor that also drops a global singleton.
//
// The singleton at 0x89C4D0 is destroyed through its own slot 0 (a deleting
// destructor, hence the `PUSH 1`), and the global is only cleared if it still
// points at what we just destroyed - that re-read is retail's `CMP ESI,[0x89C4D0]`
// and is the whole point of holding the old value in ESI.
//
// CLASS IDENTITY CORRECTION (re-verified against the binary): an earlier proposal claimed this was
// `BitFont`'s own scalar deleting destructor, reasoning that 0x7E3A80 is
// "slot +0x08 of BitFont's vtable 0x7E3A78". It is not - the disasm here
// stamps `MOV [this], 0x7E3A80`, and 0x7E3A80 carries its OWN complete object
// locator at 0x7E3A7C (independent of BitFont's, at 0x7E3A74): type
// descriptor 0x818B80, name string `.?AVBitText@@`. 0x7E3A78 (1 slot: BitFont's
// own destructor at 0x434A40, confirmed by its own `MOV [this],0x7E3A78`) and
// 0x7E3A80 (BitText's vtable) simply sit contiguously in .rdata, which is what
// made the "slot +8" reading look plausible from the vtable dump alone.
// match/ui/bit_text_ctor_methods.h already carries this correctly - it
// installs `virtual ~BitText()` as an empty stand-in specifically so its own
// vtable has something to point at, with a comment flagging 0x435560 as the
// real body, "not annotated - matching 0x435560 is separate work". This is
// that work: the class is BitText, not BitFont.
// ---------------------------------------------------------------------------
extern "C" void __cdecl FUN_007C8B3D(void* block);

extern char VT_007E3A80;   // VTABLE: GAMEMD 0x7E3A80

struct Singleton_00435560
{
    virtual void* vt_000(char flags);   // +0x0000  deleting destructor
};

extern Singleton_00435560* DAT_0089C4D0;   // GLOBAL: GAMEMD 0x89C4D0

// This TU's own minimal view of BitText (RTTI-confirmed: vtable 0x7E3A80,
// locator @0x7E3A7C -> type descriptor 0x818B80 -> `.?AVBitText@@`) - only the
// vtable-pointer field this destructor touches. Sibling minimal view in
// bit_text_ctor_methods.h models the constructor + a stand-in dtor.
class BitText
{
public:
    char* Vtable;   // +0x0000

    // FUNCTION: GAMEMD 0x435560
    void* ScalarDeletingDestructor(char flags);
};

#endif  // GG_MATCH_CORE_SMALL_MISC44_METHODS_H
