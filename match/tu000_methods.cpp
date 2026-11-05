// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; complete entry-origin retail disassembly.
// Original translation unit: between start-of-.text and AbsType.cpp
#include <stddef.h>
#include "audio_sample_methods.h"
#include "ccfile_class.h"
#include <string.h>
extern "C" void* __cdecl memset(void*, int, size_t);
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
struct unknown_Timer_401000 {
    void FUN_00401000();
};
struct unknown_Cue_4016F0 {
    char Name_0[0x10];
    int Offset_10;
    int Size_14;
    int Rate_18;
    int Flags_1C;
    char pad_20[4];
};
struct unknown_Bank_4016F0 {
    unknown_Cue_4016F0* Cues_0;
    char pad_4[4];
    char Path_8[0x104];
    FileClass* Source_10C;
    FileClass* File_110;
    int HasPath_114;
    FileClass* Active_118;
    int Remain_11C;
    int __fastcall FUN_004016F0(int index);
};
int __fastcall FUN_00408610(FileClass* file, AudioSampleData* header, unsigned int* length);

// FUNCTION: GAMEMD 0x4016F0
int __fastcall unknown_Bank_4016F0::FUN_004016F0(int index)
{
    unknown_Cue_4016F0* cue = &Cues_0[index];
    int result = 1;
    Active_118 = 0;
    if (File_110) {
        delete File_110;
        File_110 = 0;
    }
    Active_118 = Source_10C;
    Remain_11C = cue->Size_14;
    if (Source_10C->Seek(cue->Offset_10, 0) != cue->Offset_10)
        result = 0;
    if (cue->Size_14 == 0)
        result = 0;
    if (HasPath_114) {
        char name[0x104];
        strcpy(name, Path_8);
        strcat(name, cue->Name_0);
        strcat(name, ".wav");
        RawFileClass* f = new RawFileClass(name);
        File_110 = f;
        if (f->Exists(0) && f->Open((FileAccessMode)1)) {
            AudioSampleData hdr;
            hdr.FUN_004085A0();
            unsigned int len;
            if (FUN_00408610(f, &hdr, &len)) {
                cue->Flags_1C = 2;
                if (hdr.BytesPerSample == 2)
                    cue->Flags_1C = 6;
                if (hdr.NumChannels == 2)
                    cue->Flags_1C |= 1;
                cue->Rate_18 = hdr.SampleRate;
                Remain_11C = result;
                Active_118 = File_110;
                return 1;
            }
        }
        if (File_110) {
            delete File_110;
            File_110 = 0;
        }
    }
    return result;
}

struct unknown_Pool_4019E0 {
    void FUN_00407510();
    void __fastcall FUN_00407530(void* item);
};
struct unknown_Sub_4019E0 {
    void FUN_00407450();
    void FUN_00408600();
};
struct unknown_SubList_4019E0 {
    unknown_Sub_4019E0* FUN_00407470();
};
struct unknown_Links_4019E0 {
    char pad_0[4];
    unknown_Pool_4019E0* Pool_4;
    unknown_Pool_4019E0* Pool_8;
};
struct unknown_Tail_4019E0 {
    void FUN_00408530();
};
struct unknown_Entry_4019E0 {
    char pad_0[4];
    unknown_Entry_4019E0* Self_4;
    char pad_8[0x14];
    unknown_Tail_4019E0 Tail_1C;
    char pad_1D[7];
    unknown_SubList_4019E0 Subs_24;
    char pad_25[0x17];
    unknown_Links_4019E0* Owner_3C;
    void FUN_00407450();
};
struct unknown_EntryList_4019E0 {
    unknown_Entry_4019E0* FUN_00407470();
    void FUN_004072C0();
};
struct unknown_Node_4019E0 {
    void* Owner_0;
    unknown_Pool_4019E0* Pool_4;
    unknown_Pool_4019E0* Pool_8;
    unknown_EntryList_4019E0 List_C;
    char pad_D[0xb];
    int Arg_18;
    char pad_1C[0xcc];
    void FUN_004072C0();
};
unknown_Pool_4019E0* __fastcall FUN_004074D0(int a, int b);
// FUNCTION: GAMEMD 0x4019E0
unknown_Node_4019E0* __fastcall FUN_004019E0(void* owner, int total, int count, int arg)
{
    unknown_Node_4019E0* node = new unknown_Node_4019E0;
    memset(node, 0, sizeof(unknown_Node_4019E0));
    node->Owner_0 = owner;
    node->Arg_18 = arg;
    node->Pool_4 = FUN_004074D0(total / (arg + 0x1c), arg + 0x1c);
    node->Pool_8 = FUN_004074D0(count, 100);
    node->List_C.FUN_004072C0();
    unknown_Node_4019E0* result = node;
    if (!node->Pool_4 || !node->Pool_8) {
        unknown_Entry_4019E0* e = node->List_C.FUN_00407470();
        while (e) {
            if (e->Self_4 != e)
                e->FUN_00407450();
            unknown_Sub_4019E0* sub = e->Subs_24.FUN_00407470();
            while (sub) {
                sub->FUN_00407450();
                sub->FUN_00408600();
                e->Owner_3C->Pool_4->FUN_00407530(sub);
                sub = e->Subs_24.FUN_00407470();
            }
            e->Tail_1C.FUN_00408530();
            e->Owner_3C->Pool_8->FUN_00407530(e);
            e = node->List_C.FUN_00407470();
        }
        if (node->Pool_4)
            node->Pool_4->FUN_00407510();
        if (node->Pool_8)
            node->Pool_8->FUN_00407510();
        delete node;
        result = 0;
    }
    return result;
}

struct unknown_Obj_402040;
struct unknown_Svc_402040 {
    void* Fn_0;
    int(__fastcall* Fn_4)(unknown_Obj_402040* obj);
    void(__fastcall* Fn_8)(unknown_Obj_402040* obj);
};
struct unknown_Parent_402040 {
    char pad_0[0x44];
    int Copy_44[8];
    char pad_64[0x1d0 - 0x64];
    unknown_Svc_402040* Svc_1D0;
    struct unknown_Obj_402040* FUN_00402040();
};
struct unknown_Obj_402040 {
    char pad_0[0xc];
    int Live_C;
    unknown_Timer_401000 Timer_10;
    char pad_11[0x7f];
    int Zero_90;
    int Value_94;
    int Zero_98;
    int Zero_9C;
    int Zero_A0;
    int Zero_A4;
    int Zero_A8;
    unknown_Parent_402040* Parent_AC;
    int Zero_B0;
    int Zero_B4;
    int Zero_B8;
    int Zero_BC;
    int Zero_C0;
    char pad_C4[0x10];
    unknown_Svc_402040* Svc_D4;
    unknown_Timer_401000 Timer_D8;
    char pad_D9[0x83];
    void* Fn_15C;
    void* Fn_160;
    void* Fn_164;
    int Zero_168;
    char pad_16C[0x10];
    int Copy_17C[8];
    int Zero_19C;
    int Zero_1A0;
    char pad_1A4[0x1c];
    void FUN_004072D0();
};
void FUN_004022C0();
void FUN_00402330();
void FUN_004023F0();
extern int DAT_0087DE30;

// FUNCTION: GAMEMD 0x402040
unknown_Obj_402040* unknown_Parent_402040::FUN_00402040()
{
    unknown_Obj_402040* obj = new unknown_Obj_402040;
    memset(obj, 0, sizeof(unknown_Obj_402040));
    obj->FUN_004072D0();
    obj->Zero_A8 = 0;
    obj->Zero_A4 = 0;
    obj->Timer_D8.FUN_00401000();
    obj->Fn_15C = FUN_004022C0;
    obj->Fn_160 = FUN_00402330;
    obj->Fn_164 = FUN_004023F0;
    obj->Zero_B0 = 0;
    obj->Zero_B4 = 0;
    obj->Zero_B8 = 0;
    obj->Zero_BC = 0;
    obj->Zero_C0 = 0;
    obj->Live_C = 1;
    obj->Zero_A8 = 0;
    obj->Zero_A4 = 0;
    obj->Zero_A0 = 0;
    obj->Value_94 = DAT_0087DE30;
    obj->Timer_10.FUN_00401000();
    obj->Zero_90 = 0;
    obj->Zero_98 = 0;
    obj->Zero_9C = 0;
    obj->Zero_168 = 0;
    obj->Parent_AC = this;
    obj->Svc_D4 = Svc_1D0;
    memcpy(obj->Copy_17C, Copy_44, sizeof(Copy_44));
    obj->Zero_19C = 0;
    obj->Zero_1A0 = 0;
    if (Svc_1D0->Fn_4(obj)) {
        if (obj) {
            obj->Svc_D4->Fn_8(obj);
            delete obj;
        }
        return 0;
    }
    return obj;
}

