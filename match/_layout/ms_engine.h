// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Canonical MSEngine (the map-stage screen engine; base of MapSelect). Read from the retail gamemd.exe v1.001:
//   RTTI .?AVMSEngine@@ (no base), vtable 0x7EEBD4: slot 0 0x5D2700 (scalar deleting destructor), slot 1 0x5AE590,
//   slot 2 0x5D26F0 (empty). Constructor 0x5D1AA0 builds, in order, a VectorClass<TRect<int>> at +0x08 (vtable
//   0x7ED970, then SetCapacity(0x14, 0)), a DynamicVectorClass<MSAnim*> at +0x18 (0x7EEC04, increment 10) and a
//   DynamicVectorClass<MSSfx*> at +0x30 (0x7EEBE4, increment 10), stores the vptr, clears +0x04 and empties both
//   dynamic vectors. Destructor 0x5D1B30 destroys every MSSfx (its destructor 0x5D5850, then operator delete),
//   clears that vector, deletes every MSAnim through its slot-0 deleting destructor, clears that vector and runs
//   the inlined vector destructors. The constructor's callers place the next member right after it: 0x4F1CA0 /
//   0x4F2140 build the engine at +4 of a 0x70-byte object and the following member at +0x4C, and 0x76C290 builds
//   it at +0 and the next member at +0x48, so sizeof(MSEngine) == 0x48 (no member past +0x30 vector).
//   +0x04 counts the dirty rectangles queued in the VectorClass at +0x08 (0x5D1FD0 appends or merges one, 0x5D2260
//   flushes them to the screen and zeroes it).
#ifndef GG_MATCH_LAYOUT_MS_ENGINE_H
#define GG_MATCH_LAYOUT_MS_ENGINE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/vector_class.h"
#include "geometry2d.h"
#include "ms_anim.h"

class MouseSurfaceView;

// A sound effect owned by the engine: the constructor 0x5D5820 copies the name through the string duplicator
// (when the allocator helper 0x407000 allows it) and clears the other two members; its second argument is unread.
class MSSfx
{
public:
    // FUNCTION: GAMEMD 0x5D5820 (decl; reloc)
    MSSfx(const char* name, const char* unused);
    // FUNCTION: GAMEMD 0x5D5850 (decl; reloc)
    ~MSSfx();

    char* Name;              // +0x00
    int   unknown_04;        // +0x04
    bool  unknown_08;        // +0x08
};
GG_STATIC_ASSERT(offsetof(MSSfx, unknown_04) == 0x04 && offsetof(MSSfx, unknown_08) == 0x08 && sizeof(MSSfx) == 0x0C);

// VTABLE: GAMEMD 0x7EEBD4
class MSEngine
{
public:
    // FUNCTION: GAMEMD 0x5D1AA0
    MSEngine();
    virtual ~MSEngine();            // slot 0, 0x5D2700 (scalar deleting); body 0x5D1B30
    virtual void OnRedraw(MouseSurfaceView* surface);   // slot 1, 0x5AE590 (RET 4): called once the whole screen was repainted
    virtual void Process();                    // slot 2, 0x5D26F0 (empty): called once per frame by 0x5D2410

    // 0x5D1C20: queue an animation; its index, or -1 when it is null or the list cannot grow.
    int AddAnim(MSAnim* anim);
    // 0x5D1C90: queue `added` right after `replaced`, then drop and delete `replaced`.
    void ReplaceAnim(MSAnim* added, MSAnim* replaced);
    // 0x5D1D80: drop an animation and delete it.
    void RemoveAnim(MSAnim* anim);
    // 0x5D1DF0: run frames until the animation is gone or reports itself finished (or the delay is zero).
    void WaitForAnim(MSAnim* anim, unsigned int milliseconds);
    // 0x5D1E70: repaint everything when the pending-redraw flag is up, then step every animation.
    void Draw(MouseSurfaceView* surface);
    // 0x5D1FD0: queue a dirty rectangle, merging it with overlapping ones (or the cheapest one once all 20 are used).
    void AddDirtyRect(const RectangleStruct& rect);
    // 0x5D2260: copy every queued dirty rectangle of the back surface to the screen.
    void FlushDirtyRects(MouseSurfaceView* surface);
    // 0x5D2350: copy one rectangle of the back surface to the screen.
    void PresentRect(MouseSurfaceView* surface, const RectangleStruct& rect);
    // 0x5D2410: one frame (repeated `frames` times, each a millisecond long): callbacks, Process, Draw, flush, pump.
    void Run(int frames);
    // 0x5D2530: while the program is inactive pause the animations, sleep and pump messages, then resume them.
    void PauseWhileInactive();
    // 0x5D25D0: queue a sound effect; false when an argument is null or the list cannot grow.
    bool AddSfx(const char* name, const char* unused);

    int DirtyRectCount;                       // +0x04
    VectorClass<TRect<int> > Rects;           // +0x08
    DynamicVectorClass<MSAnim*> Anims;        // +0x18
    DynamicVectorClass<MSSfx*> Sfxs;          // +0x30
};
GG_STATIC_ASSERT(offsetof(MSEngine, Rects) == 0x08
              && offsetof(MSEngine, Anims) == 0x18
              && offsetof(MSEngine, Sfxs) == 0x30
              && sizeof(MSEngine) == 0x48);

#endif  // GG_MATCH_LAYOUT_MS_ENGINE_H
