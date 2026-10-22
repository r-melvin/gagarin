// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x54E6F0 Clear / 0x54E750 Save),
//   cross-checked against YRpp
//   (every offset reconfirmed numerically here).
//
// Kamikaze — the global kamikaze (suicide-aircraft) manager: a frame-counted
// update timer plus a DynamicVectorClass of KamikazeControl nodes (one per
// suicide aircraft + its target cell). Clear() frees the nodes and re-arms the
// timer; Save() serialises the node count followed by each 8-byte node.
#ifndef GG_MATCH_COMBAT_KAMIKAZE_CLASS_METHODS_H
#define GG_MATCH_COMBAT_KAMIKAZE_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class AircraftClass;
class CellClass;

// Unsorted::CurrentFrame — global frame counter @0x00A8ED84. Stamped into the
// re-armed UpdateTimer's StartTime by Clear (MOV EAX,[0x00A8ED84]).
#include "../core/frame_counter.h"

// Game memory free (cdecl, single pointer arg) @0x7C8B3D — `push p; call; add
// esp,4`. Declared (no body) so cl emits a normalised call reloc. GAMEMD 0x7C8B3D.
void __cdecl GameDelete(void* block);

typedef long HRESULT;

// Minimal IStream COM interface. Only the vtable layout matters: the matched
// calls dispatch through Write at slot 4 (+0x10). COM methods are __stdcall, so
// `this` is passed as the first *stacked* argument (PUSH pStm; CALL [vtbl+0x10]).
struct IStream
{
    virtual long          __stdcall QueryInterface(const void* riid, void** ppv) = 0; // +0x00
    virtual unsigned long __stdcall AddRef() = 0;                                     // +0x04
    virtual unsigned long __stdcall Release() = 0;                                    // +0x08
    virtual long          __stdcall Read(void* pv, unsigned long cb,
                                         unsigned long* pcbRead) = 0;                 // +0x0C
    virtual long          __stdcall Write(const void* pv, unsigned long cb,
                                          unsigned long* pcbWritten) = 0;             // +0x10
};

// KamikazeControl — one suicide aircraft and the cell it dives at (8 bytes).
struct KamikazeControl
{
    AircraftClass* Item;   // +0x00
    CellClass*     Cell;   // +0x04
};

GG_STATIC_ASSERT(sizeof(KamikazeControl) == 8);

// DynamicVectorClass<KamikazeControl*> — growable pointer vector.
// Virtuals modelled in their retail vtable order so Clear() dispatches through
// slot 3 (+0x0C) and SetCapacity() through slot 2 (+0x08); only those two and
// the vptr/Items/Capacity/Count members are touched by Kamikaze::Clear.
struct KamikazeNodeVector
{
    virtual ~KamikazeNodeVector();                                      // slot 0 (+0x00)
    virtual bool Equals(const KamikazeNodeVector& other) const;        // slot 1 (+0x04)
    virtual bool SetCapacity(int capacity, void* pMem);                // slot 2 (+0x08)
    virtual void Clear();                                              // slot 3 (+0x0C)

    KamikazeControl** Items;             // +0x04
    int               Capacity;          // +0x08
    int               IsAllocated;       // +0x0C
    int               Count;             // +0x10
    int               CapacityIncrement; // +0x14
};

GG_STATIC_ASSERT(offsetof(KamikazeNodeVector, Items)    == 0x04);
GG_STATIC_ASSERT(offsetof(KamikazeNodeVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(KamikazeNodeVector, Count)    == 0x10);

// CDTimerClass = TimerStruct<FrameTimer> — StartTime, a (functor) CurrentTime
// slot, then TimeLeft; sizeof = 0x0C (YRpp: offsetof(TimeLeft) == 8).
struct CDTimerClass
{
    int StartTime;     // +0x00
    int CurrentTime;   // +0x04  (FrameTimer functor occupies this 4-byte cell)
    int TimeLeft;      // +0x08
};

GG_STATIC_ASSERT(offsetof(CDTimerClass, TimeLeft) == 0x08);
GG_STATIC_ASSERT(sizeof(CDTimerClass)             == 0x0C);

struct Kamikaze
{
    void    Clear();               // GAMEMD 0x54E6F0 __thiscall
    HRESULT Save(IStream* pStm);   // GAMEMD 0x54E750 __thiscall

    CDTimerClass       UpdateTimer; // +0x00
    KamikazeNodeVector Nodes;       // +0x0C
};

GG_STATIC_ASSERT(offsetof(Kamikaze, UpdateTimer) == 0x00);
GG_STATIC_ASSERT(offsetof(Kamikaze, Nodes)       == 0x0C);

#endif  // GG_MATCH_COMBAT_KAMIKAZE_CLASS_METHODS_H
