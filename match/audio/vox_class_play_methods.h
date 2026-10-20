// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI:
//     0x750E20 PlayAtPos: pool block popped via `MOV ECX,[0xB1D3A4]; CALL
//       0x407520`; link words re-armed at `[ESI+0x00..0x08]` (0x4072D0);
//       sample handle constructed at `LEA EBX,[ESI+0xC]` (0x405BE0); coords
//       copied to `[ESI+0x20..0x28]`; `[ESI+0x2C]` = stack arg; `[ESI+0x30]`
//       = 0; spliced after the anchor `0xB1D320` (0x407420); counters at
//       0xB1D3A8 (live) / 0xB1D3AC (high-water).
//     0x7531A0 DeleteAll: `[EAX+0x50] = 2` on the object at 0xB1D4C4; the
//       vector at 0xB1D4A0 (vtable `[0xB1D4A0]`, Items `[0xB1D4A4]`, Count
//       `[0xB1D4B0]`) issues FindItemIndex via `[EDX+0x10]` and shifts the
//       tail down (inlined RemoveItem) before `CALL 0x7C8B3D` frees the entry.
//   Method names from YRpp VoxClass.h / VocClass.h (consult-only; names only).
//
// VoxClass -- the EVA voice table (see match/audio/vox_class_methods.h for the
// Play/SilenceIndex side). PlayAtPos spawns a positional EVA voice through the
// VocClass sample path; DeleteAll tears the whole table down at shutdown.
#ifndef GG_MATCH_AUDIO_VOX_CLASS_PLAY_METHODS_H
#define GG_MATCH_AUDIO_VOX_CLASS_PLAY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/intrusive_list_methods.h"   // ListNode / FreeListHead / FUN_00407420

struct CoordStruct
{
    int X;                    // +0x0000
    int Y;                    // +0x0004
    int Z;                    // +0x0008
};
GG_STATIC_ASSERT(offsetof(CoordStruct, Z) == 0x8);
GG_STATIC_ASSERT(sizeof(CoordStruct) == 0xC);

// The per-voice sample handle that 0x405BE0 initialises: three zeroed words
// and a descriptor pointer (`MOV [ECX+0xC],0x87E294`).
struct Obj_00405BE0
{
    int At_00;                // +0x0000
    int At_04;                // +0x0004
    int At_08;                // +0x0008
    const void* At_0C;        // +0x000C

    // FUNCTION: GAMEMD 0x405BE0 (decl; reloc) -- construct/reset the handle.
    void FUN_00405BE0();
};
GG_STATIC_ASSERT(sizeof(Obj_00405BE0) == 0x10);

// One live positional voice: an intrusive list link, the sample handle, the
// world position and the caller's extra word.
struct VoxPlayNode
{
    ListNode     Link;        // +0x0000
    Obj_00405BE0 Handle;      // +0x000C
    char         _pad01C[4];  // +0x001C
    CoordStruct  Coords;      // +0x0020
    int          At_2C;       // +0x002C
    int          At_30;       // +0x0030
};
GG_STATIC_ASSERT(offsetof(VoxPlayNode, Handle) == 0x0C);
GG_STATIC_ASSERT(offsetof(VoxPlayNode, Coords) == 0x20);
GG_STATIC_ASSERT(offsetof(VoxPlayNode, At_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(VoxPlayNode, At_30) == 0x30);

// FUNCTION: GAMEMD 0x4072D0 (decl; reloc) -- re-arm a link: Prev = Next =
// self, Owner = 0. Single-argument __fastcall is byte-identical to __thiscall.
void __fastcall FUN_004072D0(ListNode* node);

// GLOBAL: GAMEMD 0xB1D3A4 -- pool of free VoxPlayNode blocks (pointer global).
extern FreeListHead* DAT_00B1D3A4;
// GLOBAL: GAMEMD 0xB1D320 -- anchor of the live positional-voice list.
extern ListNode DAT_00B1D320;
// GLOBAL: GAMEMD 0xB1D3A8 -- live positional-voice count.
extern int DAT_00B1D3A8;
// GLOBAL: GAMEMD 0xB1D3AC -- high-water mark of that count.
extern int DAT_00B1D3AC;

struct VocClass
{
    // FUNCTION: GAMEMD 0x7509E0 (decl; reloc) -- start the sample for `index`
    // at `coords` through `handle`; returns the play token.
    static void* __fastcall PlayAt(int index, CoordStruct* coords, Obj_00405BE0* handle);
};

// The audio-event object whose state word is forced to 2 on teardown (the same
// +0x50 SilenceIndex writes in match/audio/vox_class_methods.h).
struct VoxEvent
{
    char _pad000[0x50];       // +0x0000
    int  State;               // +0x0050
};
GG_STATIC_ASSERT(offsetof(VoxEvent, State) == 0x50);

struct Obj_00407F40
{
    // FUNCTION: GAMEMD 0x407F40 (decl; reloc) -- stop the streamer.
    void FUN_00407F40();
};

// FUNCTION: GAMEMD 0x752370 (decl; reloc) -- drop the current/queued voice.
void FUN_00752370();

// GLOBAL: GAMEMD 0xB1D4C4 -- the currently playing EVA event, if any.
extern VoxEvent* DAT_00B1D4C4;
// GLOBAL: GAMEMD 0xB1D4CC -- the EVA streamer, if any.
extern Obj_00407F40* DAT_00B1D4CC;

struct VoxClass;

// DynamicVectorClass<VoxClass*> -- vptr@0, Items@4, Capacity@8, IsInitialized
// @0xC, IsAllocated@0xD, Count@0x10, CapacityIncrement@0x14. The retail
// vtable order puts FindItemIndex at slot 4 ([vtbl+0x10]); the virtuals are
// declared only so cl emits the indirect call, and the non-virtual Remove /
// RemoveItem are the inlined bodies.
class VoxVectorClass
{
public:
    virtual ~VoxVectorClass();                                       // 0x00
    virtual bool operator==(const VoxVectorClass& other) const;     // 0x04
    virtual bool SetCapacity(int capacity, VoxClass** pMem);        // 0x08
    virtual void Clear();                                            // 0x0C
    virtual int  FindItemIndex(VoxClass* const& item) const;        // 0x10
    virtual int  GetItemIndex(VoxClass* const* pItem) const;        // 0x14
    virtual VoxClass* GetItem(int index) const;                     // 0x18

    bool RemoveItem(int index)
    {
        if (index < this->Count)
        {
            --this->Count;
            for (int i = index; i < this->Count; ++i)
                this->Items[i] = this->Items[i + 1];
            return true;
        }
        return false;
    }

    bool Remove(VoxClass* item)
    {
        int idx = this->FindItemIndex(item);
        if (idx != -1)
            return this->RemoveItem(idx);
        return false;
    }

    VoxClass** Items;         // +0x0004
    int   Capacity;           // +0x0008
    bool  IsInitialized;      // +0x000C
    bool  IsAllocated;        // +0x000D
    int   Count;              // +0x0010
    int   CapacityIncrement;  // +0x0014
};
GG_STATIC_ASSERT(offsetof(VoxVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(VoxVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(VoxVectorClass) == 0x18);

struct VoxClass
{
    // GLOBAL: GAMEMD 0xB1D4A0 -- VoxClass::Array (Items 0xB1D4A4, Count 0xB1D4B0).
    static VoxVectorClass Array;

    // Unregisters the entry; expanded in place by DeleteAll's `delete`.
    ~VoxClass()
    {
        Array.Remove(this);
    }

    // FUNCTION: GAMEMD 0x750E20
    static void* __fastcall PlayAtPos(int index, CoordStruct* coords, int unk);
    // FUNCTION: GAMEMD 0x7531A0
    static void DeleteAll();

    char Name[0x28];          // +0x0000
};
GG_STATIC_ASSERT(offsetof(VoxClass, Name) == 0x00);

#endif  // GG_MATCH_AUDIO_VOX_CLASS_PLAY_METHODS_H
