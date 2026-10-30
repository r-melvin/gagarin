// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RTTI (PAVVoxClass, vector bases) | YRpp-cross-check
//   Layout read numerically off the user's retail gamemd.exe v1.001:
//     the INI reader 0x752DB0 (section = the entry name at +0x00; keys
//     "Volume" -> float +0x28, "Yuri" / "Russian" / "Allied" -> 9-byte
//     strncpy fields at +0x2C / +0x35 / +0x3E, "Priority" -> +0x48 with the
//     value names LOW / NORMAL / IMPORTANT / CRITICAL = 0..3, "Type" -> +0x4C
//     with STANDARD / QUEUE / INTERRUPT / QUEUED_INTERRUPT = 0..3); the
//     [DialogList] loader 0x753000 (operator_new(0x54), defaults Volume 1.0f,
//     Priority 1, Type 0, State 2); PlayIndex 0x752480 (arg 2 defaults from
//     +0x4C, arg 3 from +0x48); the queue-node allocation in 0x752590
//     (operator_new(0x20): entry +0x0C, priority +0x14, type +0x18, serial
//     +0x1C). The State word (2 = finished) is not a key; its name is a
//     placeholder. The one canonical definition of VoxClass / VoxNode.
#ifndef GG_MATCH__LAYOUT_VOX_CLASS_H
#define GG_MATCH__LAYOUT_VOX_CLASS_H

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "../core/vector_class_operations.h"
#include "../core/intrusive_list_methods.h"

class VoxClass;
class CCINIClass;
struct IStream;

// One queued speech node (0x20 bytes): a node of one of the queue lists, the entry it plays and its
// priority, type and serial.
struct VoxNode : ListNode
{
    VoxClass* Entry;    // +0x0C: the speech entry the node plays
    int unknown_10;     // +0x10
    int Priority;       // +0x14
    int Type;           // +0x18
    int Serial;         // +0x1C

    void Detach();              // call target 0x407450
    VoxNode* FUN_004073E0();    // call target 0x4073E0: the next node in the list
};
GG_STATIC_ASSERT(offsetof(VoxNode, Entry) == 0x0C);
GG_STATIC_ASSERT(offsetof(VoxNode, Priority) == 0x14);
GG_STATIC_ASSERT(offsetof(VoxNode, Type) == 0x18);
GG_STATIC_ASSERT(offsetof(VoxNode, Serial) == 0x1C);
GG_STATIC_ASSERT(sizeof(VoxNode) == 0x20);

// GLOBAL: GAMEMD 0xB1D4A0 -- the table of VoxClass entries (Items 0xB1D4A4, Count
// 0xB1D4B0). A file-scope extern rather than a `static` member: a class-type
// static member declared in a header consumes a VC6 `_$E` ordinal in every TU
// that includes it and renumbers that TU's real static initialisers.
extern DynamicVectorClass<VoxClass*> DAT_00B1D4A0;

// One EVA speech entry (eva.ini [DialogList]).
class VoxClass
{
public:
    // Entry for eva.ini [DialogList]; expanded in place by ReadAll (0x753000).
    VoxClass(const char* name)
    {
        Volume = 1.0f;
        strcpy(Name, name);
        Yuri[0] = 0;
        Russian[0] = 0;
        Allied[0] = 0;
        Priority = 1;
        Type = 0;
        State = 2;
        DynamicVectorClass<VoxClass*>& table = DAT_00B1D4A0;
        table.AddItem(this);
    }
    static void Play(const char* pName, int type, int priority);        // 0x752700
    static void PlayIndex(int index, int type, int priority);           // 0x752480
    static void SilenceIndex(int index);                                // 0x752A40
    VoxNode* GetActiveVoice();                                          // 0x752680
    static void ClearQueues();                                          // 0x752370
    static void Enqueue(VoxClass* entry, int type, int priority);       // 0x752590
    static void ReadAll(CCINIClass* ini);                                // 0x753000
    static long Load(IStream* stream);                                   // 0x7533F0
    static void DeleteAll();                                            // 0x7531A0
    void FUN_00752D60();                                                // 0x752D60
    bool ReadINI(CCINIClass* ini);                                      // 0x752DB0

    // Unregisters the entry; expanded in place by DeleteAll's `delete`.
    ~VoxClass()
    {
        DAT_00B1D4A0.RemoveItem(this);
    }

    char  Name[0x28];       // +0x00
    float Volume;           // +0x28
    char  Yuri[9];          // +0x2C
    char  Russian[9];       // +0x35
    char  Allied[9];        // +0x3E
    char  unknown_47;       // +0x47
    int   Priority;         // +0x48
    int   Type;             // +0x4C
    int   State;            // +0x50  2 = finished
};
GG_STATIC_ASSERT(offsetof(VoxClass, Name) == 0x00);
GG_STATIC_ASSERT(offsetof(VoxClass, Volume) == 0x28);
GG_STATIC_ASSERT(offsetof(VoxClass, Yuri) == 0x2C);
GG_STATIC_ASSERT(offsetof(VoxClass, Russian) == 0x35);
GG_STATIC_ASSERT(offsetof(VoxClass, Allied) == 0x3E);
GG_STATIC_ASSERT(offsetof(VoxClass, Priority) == 0x48);
GG_STATIC_ASSERT(offsetof(VoxClass, Type) == 0x4C);
GG_STATIC_ASSERT(offsetof(VoxClass, State) == 0x50);
GG_STATIC_ASSERT(sizeof(VoxClass) == 0x54);

#endif
