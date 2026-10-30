// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   EVA speech queue, read off the user's retail gamemd.exe v1.001 at 0x752370 (drop everything queued),
//   0x752590 (queue an entry by type). Queue heads: pending-by-type lists at 0xB1D3C8 and 0xB1D3F0 and the
//   four priority lists at 0xB1D450 (stride 0xC); the speaking node at 0xB1D4B8; the master switch at
//   0xB1D4BC; the serial counter at 0xB1D4C0.

#include <string.h>
#include <objidl.h>
#include "../platform/ccini_class_methods.h"
#include "../_layout/vox_class.h"
#include "../_layout/obj_00407f40.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);

// STRING: GAMEMD 0x889F64 -- the shared empty default text.
extern const char STR_00889F64[];
// GLOBAL: GAMEMD 0xB1D3C8 -- list of type-3 nodes.
extern ListNode DAT_00B1D3C8;
// GLOBAL: GAMEMD 0xB1D3F0 -- list of priority-3 nodes.
extern ListNode DAT_00B1D3F0;
// GLOBAL: GAMEMD 0xB1D450 -- one list per priority 0..3.
extern ListNode DAT_00B1D450[4];
// GLOBAL: GAMEMD 0xB1D4B8 -- the node being spoken.
extern VoxNode* DAT_00B1D4B8;
// GLOBAL: GAMEMD 0xB1D4BC -- queueing enabled.
extern int DAT_00B1D4BC;
// GLOBAL: GAMEMD 0xB1D4C0 -- serial counter.
extern int DAT_00B1D4C0;
// GLOBAL: GAMEMD 0xB1D4A4 -- the speech entry table (VoxClass::Array Items).
// GLOBAL: GAMEMD 0xB1D4B0 -- how many entries there are.
// GLOBAL: GAMEMD 0xB1D4C4 -- the entry currently speaking.
extern VoxClass* DAT_00B1D4C4;
// GLOBAL: GAMEMD 0xB1D4CC -- the speech engine.
extern Obj_00407F40* DAT_00B1D4CC;

// FUNCTION: GAMEMD 0x752370
// Drop the speaking node and every queued node, marking each node's entry finished.
void VoxClass::ClearQueues()
{
    if (DAT_00B1D4BC != 0) {
        if (DAT_00B1D4B8 != 0) {
            DAT_00B1D4B8->Entry->State = 2;
            delete DAT_00B1D4B8;
            DAT_00B1D4B8 = 0;
        }
        VoxNode* node = static_cast<VoxNode*>(DAT_00B1D3F0.FUN_004073C0());
        while (node != 0) {
            node->Detach();
            node->Entry->State = 2;
            delete node;
            node = static_cast<VoxNode*>(DAT_00B1D3F0.FUN_004073C0());
        }
        node = static_cast<VoxNode*>(DAT_00B1D3C8.FUN_004073C0());
        while (node != 0) {
            node->Detach();
            node->Entry->State = 2;
            delete node;
            node = static_cast<VoxNode*>(DAT_00B1D3C8.FUN_004073C0());
        }
        for (int i = 0; i < 4; ++i) {
            node = static_cast<VoxNode*>(DAT_00B1D450[i].FUN_004073C0());
            while (node != 0) {
                node->Detach();
                node->Entry->State = 2;
                delete node;
                node = static_cast<VoxNode*>(DAT_00B1D450[i].FUN_004073C0());
            }
        }
    }
}

// FUNCTION: GAMEMD 0x752590
// Queue `entry`: type 3 and type 1 go on their own lists, priority 3 on the urgent list; anything else
// is spoken at once when nothing is pending and nothing of equal or higher priority is speaking, and
// is otherwise dropped.
void VoxClass::Enqueue(VoxClass* entry, int type, int priority)
{
    VoxNode* node = (VoxNode*)operator new(sizeof(VoxNode));
    node->FUN_004072D0();
    node->Entry = entry;
    node->Priority = priority;
    node->Type = type;
    node->Serial = DAT_00B1D4C0 % 100;
    DAT_00B1D4C0++;
    entry->State = 1;
    if (type == 3) {
        DAT_00B1D3C8.FUN_00407420(node);
        return;
    }
    if (type == 1) {
        DAT_00B1D450[priority].FUN_00407420(node);
        return;
    }
    if (priority == 3) {
        DAT_00B1D3F0.FUN_00407420(node);
        return;
    }
    if (DAT_00B1D3C8.Next == &DAT_00B1D3C8 && DAT_00B1D3F0.Next == &DAT_00B1D3F0
        && (DAT_00B1D4B8 == 0 || DAT_00B1D4B8->Priority < priority)) {
        DAT_00B1D4B8 = node;
        return;
    }
    entry->State = 2;
    delete node;
}

// FUNCTION: GAMEMD 0x752DB0
// Read one speech entry's section of eva.ini: its volume, queueing type and priority by name, and the
// three per-faction sound names.
bool VoxClass::ReadINI(CCINIClass* ini)
{
    char buffer[500];

    ini->Reset();
    Volume = 1.0f;
    if (ini->INIClass::Exists(Name, 0)) {
        Volume = (float)ini->ReadDouble(Name, "Volume", Volume);
        ini->ReadString(Name, "Type", STR_00889F64, buffer, 500);
        if (strlen(buffer) != 0) {
            if (_stricmp(buffer, "QUEUE") == 0)
                Type = 1;
            else if (_stricmp(buffer, "STANDARD") == 0)
                Type = 0;
            else if (_stricmp(buffer, "INTERRUPT") == 0)
                Type = 2;
            else if (_stricmp(buffer, "QUEUED_INTERRUPT") == 0)
                Type = 3;
        }
        ini->ReadString(Name, "Priority", STR_00889F64, buffer, 500);
        if (strlen(buffer) != 0) {
            if (_stricmp(buffer, "LOW") == 0)
                Priority = 0;
            else if (_stricmp(buffer, "NORMAL") == 0)
                Priority = 1;
            else if (_stricmp(buffer, "IMPORTANT") == 0)
                Priority = 2;
            else if (_stricmp(buffer, "CRITICAL") == 0)
                Priority = 3;
        }
        ini->ReadString(Name, "Yuri", STR_00889F64, buffer, 500);
        strncpy(Yuri, buffer, 9);
        Yuri[8] = 0;
        ini->ReadString(Name, "Russian", STR_00889F64, buffer, 500);
        strncpy(Russian, buffer, 9);
        Russian[8] = 0;
        ini->ReadString(Name, "Allied", STR_00889F64, buffer, 500);
        strncpy(Allied, buffer, 9);
        Allied[8] = 0;
        return true;
    }
    return false;
}

// The entry named `name`: its table index, or -1.
static __inline int VoxFindIndex(const char* name)
{
    if (name) {
        for (int i = 0; i < DAT_00B1D4A0.Count; ++i) {
            if (_stricmp(name, DAT_00B1D4A0.Items[i]->Name) == 0)
                return i;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x753000
// Read [DialogList]: create the entry for every listed name that has none, then read each one's section.
void VoxClass::ReadAll(CCINIClass* ini)
{
    char name[200];

    if (ini->INIClass::Exists("DialogList", 0)) {
        int count = ini->GetKeyCount("DialogList");
        for (int i = 0; i < count; ++i) {
            if (ini->ReadString("DialogList", ini->GetKeyName("DialogList", i), STR_00889F64, name, 200)) {
                int index = VoxFindIndex(name);
                VoxClass* entry;
                if (index == -1)
                    entry = new VoxClass(name);
                else
                    entry = DAT_00B1D4A0.Items[index];
                entry->ReadINI(ini);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x7533F0
// Stop speaking and drop the queues, then restore them from the stream: a signature word, then one
// record (index, type, priority) per queued entry up to the end marker.
long VoxClass::Load(IStream* stream)
{
    if (DAT_00B1D4C4 != 0) {
        DAT_00B1D4C4->State = 2;
        DAT_00B1D4C4 = 0;
    }
    if (DAT_00B1D4CC != 0)
        DAT_00B1D4CC->FUN_00407F40();
    ClearQueues();

    unsigned int tag;
    long result = stream->Read(&tag, 4, 0);
    if (result >= 0 && tag == 0x566F7853) {
        result = stream->Read(&tag, 4, 0);
        while (result >= 0 && tag != 0x566F7845) {
            if (tag != 0x566F7849)
                return 0x80004005;
            int record[3];
            result = stream->Read(record, 12, 0);
            if (result < 0)
                return result;
            if (DAT_00B1D4CC != 0 && record[0] >= 0 && record[0] < DAT_00B1D4A0.Count)
                Enqueue(DAT_00B1D4A0.Items[record[0]], record[1], record[2]);
            result = stream->Read(&tag, 4, 0);
        }
    }
    return result;
}
