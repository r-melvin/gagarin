// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | structural-reference-only
//   Westwood VQA playback library 5.0 (C++ part), read off the user's retail gamemd.exe v1.001
//   with the REA tools and the local Ghidra CLI at the address in each annotation. The class is
//   named by the retail string "VQAClass::Advance_Frame()"; everything else is a placeholder.
//   Address index: 0x759260, 0x759510, 0x759540, 0x759940, 0x759C30, 0x759FB0,
//   0x75A120, 0x75A2B0, 0x75A350.

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vqa_class.h"

struct VQAOwner_006C9C60
{
    void FUN_006C9C60(unsigned int frames);
};

struct VQAMsg
{
    void* hwnd;
    unsigned int message;
    unsigned int wParam;
    long lParam;
    unsigned long time;
    long pt[2];
};
GG_STATIC_ASSERT(sizeof(VQAMsg) == 0x1C);

struct VQAInput_0087F770
{
    short FUN_0054F000();
    short FUN_0054F050();
};

// LIBRARY: IAT 0x7E14BC USER32!TranslateMessage, 0x7E14C0 USER32!DispatchMessageA, 0x7E11F0 KERNEL32!Sleep.
extern "C" __declspec(dllimport) int __stdcall TranslateMessage(const VQAMsg* msg);
extern "C" __declspec(dllimport) long __stdcall DispatchMessageA(const VQAMsg* msg);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

// GLOBAL: GAMEMD 0xA8ED80 / 0xAA0430 / 0xA8D5F8 / 0xA8EDA0 / 0xB45BA4 / 0x87F770 / 0xA8EBA8
extern char DAT_00A8ED80;
extern int DAT_00AA0430;
extern unsigned char DAT_00A8D5F8;
extern int DAT_00A8EDA0;
extern char DAT_00B45BA4;
extern VQAInput_0087F770* DAT_0087F770;
extern int DAT_00A8EBA8;

extern "C" void __cdecl FUN_004068E0(const char* format, ...);
bool __fastcall FUN_0075A810(int bit);
void __fastcall FUN_00748360();
void __fastcall FUN_00748220(int mode);
void __fastcall FUN_00748380(unsigned short* p, int count);
int __fastcall FUN_007C3690(MovieHandle_007BD470* h, int frame);
int __fastcall FUN_007C3710(MovieHandle_007BD470* h, int* a, int* b, int* c);
int __fastcall FUN_007C3230(MovieHandle_007BD470* h, void (*fn1)(), void (*fn2)());
int __fastcall FUN_007C2D00(MovieHandle_007BD470* h, int mode, int flags);
unsigned int __fastcall FUN_007C3990(MovieHandle_007BD470* h);
void __fastcall FUN_004A4780(unsigned char* palette);
int __fastcall FUN_0053E770(VQAMsg* msg, void* hwnd, unsigned int filterMin, unsigned int filterMax,
                            int remove);
int __fastcall FUN_0053E730(VQAMsg* msg, void* hwnd, unsigned int filterMin, unsigned int filterMax);
bool __fastcall FUN_005B4430(char* name, int* a, unsigned int** b, int* c, int* d);
void FUN_007C6B70();
void FUN_007C6C79();
void FUN_007483B0();
void FUN_00748750();
void FUN_00748AF0();
void FUN_00748C30();
unsigned __cdecl FUN_004116A0(StreamSampleView* sample);
unsigned __cdecl FUN_00412540(StreamSampleView* sample);
int __cdecl FUN_00411820(int a, int b);
int __cdecl FUN_0075A100(MovieHandle_007BD470* h, int op, unsigned int* buf, int size);
int __cdecl FUN_0075A2B0(MovieHandle_007BD470* h, int op, unsigned int* buf, int size);
void* __cdecl FUN_0075A2F0(int unused, int op, unsigned int* p, size_t n);
int __cdecl FUN_0075A350(MovieHandle_007BD470* h, int op, unsigned short* buf, unsigned int size);

// FUNCTION: GAMEMD 0x759260
//
// PARTIAL: 97.5% -- same 160 instructions; the compiler hoists the store of +0x544 ahead of +0x548
// where retail stores +0x548 first (statement-order permutations of the three handler stores tried).
// Builds the playback object: file member, callback table, flag words from the option bits.
VQAClass::VQAClass(const char* name, unsigned int mode, int (__cdecl *h540)(), void (__cdecl *h544)(),
                   void (__cdecl *cb548)(), int a6, int a7)
{
    char local;
    Config.FUN_007BE640();
    Mode = mode;
    Config.Self = this;
    Config.unknown_1C = &local;
    Config.Flags40 = 0;
    if (!FUN_0075A810(15)) {
        Config.Flags40 |= 1;
    }
    if (!FUN_0075A810(1)) {
        Config.Flags40 |= 4;
    }
    if (FUN_0075A810(10) == 1) {
        Config.Flags40 |= 0x40;
    }
    if (FUN_0075A810(12) == 1) {
        Config.Flags40 |= 0x80;
    }
    Config.Flags44 |= 8;
    if (Mode & 2) {
        Config.Flags44 |= 0x20;
        if (Mode & 4) {
            Config.Flags44 |= 0x100;
        }
    } else {
        Config.Flags44 &= ~0x20;
    }
    if (FUN_0075A810(17) == 1) {
        Config.Flags44 |= 4;
    } else {
        Config.Flags44 &= ~4;
    }
    if (FUN_0075A810(3) == 1) {
        Config.Flags44 &= ~1;
    } else {
        Config.Flags44 |= 1;
    }
    Config.unknown_20 = -1;
    Config.unknown_24 = -1;
    Config.unknown_28 = 0;
    Config.unknown_2C = 0;
    Config.unknown_0C = 0;
    Config.unknown_30 = a6;
    Config.unknown_34 = a7;
    if (FUN_0075A810(3) == 1) {
        Config.unknown_48 = 1;
    } else {
        Config.unknown_48 = 14;
    }
    Config.unknown_4C = -1;
    if (Mode & 1) {
        Config.Io = FUN_0075A2B0;
    } else {
        Config.Io = FUN_0075A100;
    }
    Config.Alloc = FUN_0075A2F0;
    Config.Palette = FUN_0075A350;
    if (FUN_0075A810(4) == 1) {
        Config.Audio = FUN_00412540;
        Config.unknown_38 = 60;
    } else {
        Config.Audio = FUN_004116A0;
        Config.unknown_38 = 60;
        Config.unknown_84 = DAT_00A8EBA8 & 0xFFFF;
    }
    Config.Timer = FUN_00411820;
    Config.unknown_5C = 0x2000;
    Position = 0;
    Pending = 0;
    FrameCount = 0;
    strcpy(Name, name);
    unknown_518 = 0;
    unknown_51C = 0;
    unknown_520 = 0;
    unknown_524 = 0;
    unknown_510 = -1;
    PaletteDirty = false;
    Handler540 = h540;
    Callback548 = cb548;
    Handler544 = h544;
    FileOpen = false;
    Active = false;
    Sleeping = false;
    PauseLogged = false;
    Owner = 0;
}

// FUNCTION: GAMEMD 0x759510
VQAClass::~VQAClass()
{
    FUN_00748360();
}

// FUNCTION: GAMEMD 0x759540
int VQAClass::FUN_00759540(unsigned int count)
{
    if (!FileOpen) {
        FileOpen = File.OpenEx(Name, 1) != 0;
        if (!FileOpen) {
            return -4;
        }
        DataSize = File.GetFileSize();
        DataCursor = 0;
        DataLoaded = 0;
        Data = (unsigned char*)malloc(DataSize);
        if (Data == 0) {
            File.Close();
            FileOpen = false;
            return -3;
        }
    }
    if (count == 0) {
        count = DataSize - DataLoaded;
    } else if (DataLoaded + count > DataSize) {
        count = DataSize - DataLoaded;
    }
    if (File.ReadBytes(Data + DataLoaded, count) != (int)count) {
        File.Close();
        FileOpen = false;
        DataCursor = 0;
        DataLoaded = 0;
        return -5;
    }
    DataLoaded += count;
    if (DataLoaded >= DataSize) {
        File.Close();
        FileOpen = false;
        return -2;
    }
    return -1;
}

// FUNCTION: GAMEMD 0x759940
//
// PARTIAL: 92.7% -- retail caches the Sleep import in EBP where VC6 caches TranslateMessage, and
// keeps the two return paths as branches where VC6 folds them to SETNE.
// Seeks to a frame, then pumps messages and steps the movie until it fails or the user aborts.
bool VQAClass::FUN_00759940(int frame, bool flag)
{
    bool quit = false;
    bool asleep = false;
    int target = frame;
    if (target < 0 || target >= FrameCount) {
        target = FrameCount - 1;
    }
    FUN_007C3690(Handle, target);
    if (unknown_510 != -1) {
        int a;
        int b;
        FUN_007C3710(Handle, &a, &b, &frame);
        if (frame == 1) {
            FUN_00748220(unknown_510);
            if (FUN_0075A810(11)) {
                FUN_007C3230(Handle, FUN_007C6C79, FUN_00748750);
            } else {
                FUN_007C3230(Handle, FUN_007C6B70, FUN_007483B0);
            }
        } else if (frame == 4) {
            FUN_00748220(unknown_510);
            if (FUN_0075A810(11)) {
                FUN_007C3230(Handle, FUN_00748AF0, FUN_00748C30);
            }
        }
    }
    int r = 0;
    for (;;) {
        if (!(r >= 0 || r == -10 || r == -9 || r == -11 || r == -1)) {
            if (quit) {
                return true;
            }
            return false;
        }
        if (quit) {
            return true;
        }
        VQAMsg msg;
        DAT_00AA0430++;
        if (FUN_0053E770(&msg, 0, 0, 0, 0)) {
            if (FUN_0053E730(&msg, 0, 0, 0)) {
                TranslateMessage(&msg);
                DispatchMessageA(&msg);
            }
        }
        if (asleep == true) {
            if (DAT_00A8ED80 == 0) {
                Sleep(33);
                continue;
            }
            asleep = false;
            Sleeping = false;
            FUN_004068E0("Movie is awake\n");
        }
        if (DAT_00A8ED80 == 1 && !Sleeping) {
            r = FUN_007C2D00(Handle, 1, 0);
            if (r >= 0) {
                if (PaletteDirty) {
                    FUN_004A4780(Palette);
                    PaletteDirty = false;
                }
                if (Owner) {
                    Owner->FUN_006C9C60(FUN_007C3990(Handle));
                }
                if (Callback548) {
                    Callback548();
                }
                Position = r + 1;
            }
        } else if (!asleep) {
            asleep = true;
            if (Active && !Sleeping) {
                FUN_007C2D00(Handle, 2, 0);
            }
            Sleeping = true;
            FUN_004068E0("Movie is sleeping\n");
        }
        if (!flag) {
            if (DAT_0087F770->FUN_0054F000() != 0 && DAT_0087F770->FUN_0054F050() == 0x81B) {
                quit = true;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x759C30
bool VQAClass::Advance_Frame(bool* failed)
{
    *failed = false;
    if (!PauseLogged) {
        int a;
        int b;
        int type;
        FUN_007C3690(Handle, FrameCount);
        if (unknown_510 != -1) {
            FUN_007C3710(Handle, &a, &b, &type);
            if (type == 1 || type == 4) {
                FUN_00748220(unknown_510);
                if (type == 1) {
                    FUN_007C3230(Handle, FUN_007C6B70, FUN_007483B0);
                }
            }
        }
        FUN_004068E0("VQAClass::Advance_Frame() - Ready\n");
        PauseLogged = true;
    }
    if (Sleeping == 1 && !(DAT_00A8D5F8 & 2) && DAT_00A8EDA0 == 0) {
        if (DAT_00A8ED80 != 1) {
            goto paused;
        }
        Sleeping = false;
        FUN_004068E0("VQAClass::Advance_Frame() - Unpause\n");
    }
    if (DAT_00A8ED80 == 1 && !Sleeping) {
        int r = FUN_007C2D00(Handle, 1, 0);
        if (r >= 0) {
            if (PaletteDirty) {
                FUN_004A4780(Palette);
                PaletteDirty = false;
            }
            if (Owner) {
                Owner->FUN_006C9C60(FUN_007C3990(Handle));
            }
            if (Callback548) {
                Callback548();
            }
            Position = r + 1;
            return true;
        }
        if (r >= -11 && (r <= -10 || r == -1)) {
            *failed = false;
        } else {
            *failed = true;
        }
        return false;
    }
paused:
    if (!DAT_00B45BA4) {
        if (Active && !Sleeping) {
            FUN_007C2D00(Handle, 2, 0);
        }
        Sleeping = true;
        DAT_00B45BA4 = 1;
        FUN_004068E0("VQAClass::Advance_Frame() - Pause\n");
    }
    return false;
}

// FUNCTION: GAMEMD 0x759FB0
//
// PARTIAL: 88.0% -- the epilogue of the size-query case is scheduled differently (POP ESI before the store).
// File callback of the playback engine: one case per engine request.
int VQAClass::FUN_00759FB0(int op, unsigned int* buf, int size)
{
    int r = 1;
    int tmp;
    switch (op) {
    case 3:
        FileOpen = File.OpenEx((const char*)buf, 1) != 0;
        return !FileOpen;
    case 5:
        return File.ReadBytes(buf, size) != size;
    case 6:
        return true;
    case 7:
        return File.Seek(size, (int)buf) == 0;
    case 8:
        if (size > 0) {
            r = File.Seek(size - 1, (int)buf) == 0;
            if (!r) {
                return File.ReadBytes(&tmp, 1) != 1;
            }
        } else {
            r = File.Seek(size, (int)buf) == 0;
            if (!r) {
                r = File.ReadBytes(&tmp, 1) != 1;
                if (!r) {
                    return File.Seek(-1, 1) == 0;
                }
            }
        }
        break;
    case 9:
        *buf = File.GetFileSize();
    case 1:
    case 2:
        r = 0;
        break;
    case 4:
        File.Close();
        return FileOpen = false;
    }
    return r;
}

// 0x75A100 (not an extent-census entry yet): thunk to 0x759FB0 through the handle.
int __cdecl FUN_0075A100(MovieHandle_007BD470* h, int op, unsigned int* buf, int size)
{
    VQAClass* self = h->unknown_40.unknown_6C;
    return self->FUN_00759FB0(op, buf, size);
}

// FUNCTION: GAMEMD 0x75A120
//
// PARTIAL: 89.8% -- same difference as 0x759FB0 in the size-query case.
// Same callback as 0x759FB0, with the open case resolving the name through the archive lookup first.
int VQAClass::FUN_0075A120(int op, unsigned int* buf, int size)
{
    int r = 1;
    int tmp;
    switch (op) {
    case 3:
        op = 0;
        buf = 0;
        if (FUN_005B4430(Name, 0, &buf, &op, 0)) {
            FileOpen = File.OpenEx((const char*)buf[3], 1) != 0;
            return File.Seek(op, 1) == 0;
        }
        return true;
    case 5:
        return File.ReadBytes(buf, size) != size;
    case 6:
        return true;
    case 7:
        return File.Seek(size, (int)buf) == 0;
    case 8:
        if (size > 0) {
            r = File.Seek(size - 1, (int)buf) == 0;
            if (!r) {
                return File.ReadBytes(&tmp, 1) != 1;
            }
        } else {
            r = File.Seek(size, (int)buf) == 0;
            if (!r) {
                r = File.ReadBytes(&tmp, 1) != 1;
                if (!r) {
                    return File.Seek(-1, 1) == 0;
                }
            }
        }
        break;
    case 9:
        *buf = File.GetFileSize();
    case 1:
    case 2:
        r = 0;
        break;
    case 4:
        File.Close();
        return FileOpen = false;
    }
    return r;
}

// FUNCTION: GAMEMD 0x75A2B0
int __cdecl FUN_0075A2B0(MovieHandle_007BD470* h, int op, unsigned int* buf, int size)
{
    VQAClass* self = h->unknown_40.unknown_6C;
    return self->FUN_0075A120(op, buf, size);
}

// FUNCTION: GAMEMD 0x75A350
int __cdecl FUN_0075A350(MovieHandle_007BD470* h, int op, unsigned short* buf, unsigned int size)
{
    VQAClass* self = h->unknown_40.unknown_6C;
    switch (op) {
    case 2: {
        for (int i = 0; i < 256; i++) {
            ((unsigned char*)buf)[i] <<= 2;
        }
        memcpy(self->Palette, buf, 0x300);
        self->PaletteDirty = true;
        return 0;
    }
    case 3:
        if (self->unknown_510 != -1) {
            FUN_00748380(buf, size >> 1);
        }
        self->Pending = self->Position;
        return 0;
    case 6:
        return self->Handler540();
    case 7:
        self->Handler544();
    }
    return 0;
}
