// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Original translation unit CD.CPP. The name is the source-file string at 0x81c1ec
//   in retail gamemd.exe v1.001, passed by the assert at 0x479186 inside this object's
//   code range (0x478b9a-0x47b14f). Functions are in ascending retail address order.
//
// Entry-origin 0x473AB0 and the RTTI-backed CD table at 0x7E4C30.
// RTTI identifies CD as the callback-table owner; its full layout and method
// names are not recovered. The outer receiver class remains unknown.
//
// Removable-drive lock / eject helpers. The NT paths open "\\.\X:" and drive
// the FSCTL / IOCTL_STORAGE device controls; the 9x paths go through the
// VWIN32 DOS IOCTL (int 21h 440Dh) block. Each method logs its failures
// through the printf-style sink at 0x4068E0.
//
// LIBRARY: IAT 0x7E11B8 KERNEL32!DeviceIoControl, 0x7E11BC CreateFileA,
//   0x7E11E0 CloseHandle, 0x7E11F0 Sleep, 0x7E1200 GetLastError,
//   0x7E125C GetDriveTypeA.
//
// Locates a file first as given and then under each entry of the search-path
// list at 0x89E410. On success the found name is copied back over the
// caller's buffer and the find handle is kept open in 0x81C8EC (the previous
// one is closed first).
//
// LIBRARY: IAT 0x7E1208 KERNEL32!FindFirstFileA, 0x7E1300 KERNEL32!FindClose.
//
// 0x47AAC0 clears the search-path list at 0x89E410 and tail-jumps to the
// independently callable 0x47AB10 path helper. 0x47AD50 allocates and appends
// an 8-byte search-path node. 0x47ADA0 stores an ECX dword in 0x89E414 and
// shifts the prior value to 0x89E418; 0x47AB10 reads the low byte of 0x89E414
// as an index. Names and original owners remain unknown.
//
//   0x65CA70 / 0x65CB30 / 0x65D420 via the local Ghidra disassembly. The class
//   hierarchy, vtable slot order and member offsets come from the committed
//   model in ccfile_class.h (Handle @0x14, CCFileClass::Availability @0x68),
//   each reconfirmed here from the member-access instructions.
//
// File-open plumbing across the RawFileClass -> ... -> CCFileClass chain.
// Functions ordered ascending by retail address.
//
// CCToolTip slots 1..5 (layout and evidence: sidebar_cctooltip.h).

#include "../_rt/gg_static_assert.h"
#include "../_layout/global_0081c1d0.h"
#include <stddef.h>
GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(sizeof(unsigned int) == 4);

// Slot-0 call view: ECX receiver and one stack dword. The AL result is
// discarded here; void is a caller ABI view, not a recovered CD signature.
struct CallbackView_00473AB0 { virtual void first(int value) = 0; };
// This caller reserves eight stack bytes and writes only the first dword.
// This stack view does not establish sizeof(CD) or its complete layout.
struct CallbackStorage_00473AB0 { void* vtable; unsigned char unknown_04[4]; };
GG_STATIC_ASSERT(offsetof(CallbackStorage_00473AB0, vtable) == 0);
GG_STATIC_ASSERT(offsetof(CallbackStorage_00473AB0, unknown_04) == 4);
GG_STATIC_ASSERT(sizeof(CallbackStorage_00473AB0) == 8);

typedef void (CallbackView_00473AB0::*CallbackCall_00473AB0)(int);
struct CallbackSlots_00473AB0 { CallbackCall_00473AB0 first; };
GG_STATIC_ASSERT(sizeof(CallbackCall_00473AB0) == 4);
GG_STATIC_ASSERT(offsetof(CallbackSlots_00473AB0, first) == 0);

// VTABLE: GAMEMD 0x007E4C30 -- CD slots: 0x4790E0, 0x479110, 0x4791F0.
// The extern is an address binding, not a reconstructed emitted CD vtable.
extern "C" void* DAT_007E4C30;
// The outer receiver and three ignored stack words are ABI views only.

struct FUN_00473AB0_View
{
    unsigned char unknown_00[4];
    unsigned char unknown_04;
    unsigned char unknown_05[3];
    void FUN_00473AB0(int unknown_08, int unknown_0C, int unknown_10);
};
GG_STATIC_ASSERT(offsetof(FUN_00473AB0_View, unknown_04) == 4);

// GLOBAL: GAMEMD 0x0089E3A0 (byte comparison at 0x4790EE)
extern "C" unsigned char DAT_0089E3A0;
GG_STATIC_ASSERT(sizeof(DAT_0089E3A0) == 1);

// Slot-0 method view at 0x4790E0. The retail RTTI associates this vtable
// with CD, but neither a complete CD layout nor the original method name is
// recovered. This prefix view models only the vptr and dword touched here.
struct CD_004790E0
{
    virtual bool FUN_004790E0(int value);
    unsigned int unknown_04;

    // ABI call view for the direct callee 0x4A8270: ECX is this and one
    // dword is passed on the stack. This declaration does not assign that
    // address to a CD member in the recovered class model.
    // FUNCTION: GAMEMD 0x004A8270 (call target declaration; owner unresolved)
    bool FUN_004A8270(int value);
};
GG_STATIC_ASSERT(offsetof(CD_004790E0, unknown_04) == 4);
typedef bool (CD_004790E0::*CDSlot0Call_004790E0)(int);
struct CDVtablePrefix_004790E0 { CDSlot0Call_004790E0 slot0; };
GG_STATIC_ASSERT(sizeof(CDSlot0Call_004790E0) == 4);
GG_STATIC_ASSERT(offsetof(CDVtablePrefix_004790E0, slot0) == 0);
GG_STATIC_ASSERT(sizeof(CDVtablePrefix_004790E0) == 4);

#include <stddef.h>
#include <stdio.h>
#include "../_rt/gg_static_assert.h"

typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef void* HANDLE;

extern "C" __declspec(dllimport) int __stdcall DeviceIoControl(
    HANDLE device, DWORD code, void* in, DWORD in_size, void* out,
    DWORD out_size, DWORD* returned, void* overlapped);
extern "C" __declspec(dllimport) HANDLE __stdcall CreateFileA(
    char const* name, DWORD access, DWORD share, void* security,
    DWORD disposition, DWORD flags, HANDLE templ);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(HANDLE handle);
extern "C" __declspec(dllimport) void __stdcall Sleep(DWORD ms);
extern "C" __declspec(dllimport) DWORD __stdcall GetLastError(void);
extern "C" __declspec(dllimport) unsigned __stdcall GetDriveTypeA(char const* root);

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

// GLOBAL: GAMEMD 0x887624 -- set when the 9x (VWIN32) path is used.
extern bool DAT_00887624;

// VWIN32 DIOC register block (0x1C bytes).
struct DiocRegisters
{
    DWORD EBX;     // +0x00
    DWORD EDX;     // +0x04
    DWORD ECX;     // +0x08
    DWORD EAX;     // +0x0C
    DWORD EDI;     // +0x10
    DWORD ESI;     // +0x14
    DWORD Flags;   // +0x18
};
GG_STATIC_ASSERT(offsetof(DiocRegisters, EAX) == 0x0C);
GG_STATIC_ASSERT(offsetof(DiocRegisters, Flags) == 0x18);
GG_STATIC_ASSERT(sizeof(DiocRegisters) == 0x1C);   // passed as the DIOC in/out size

// int 21h 440Dh/0848h parameter block.
struct LockParams
{
    BYTE Operation;   // +0x0
    BYTE NumLocks;    // +0x1
};

struct PreventRemoval
{
    BYTE Prevent;
};

#define MAKEWORD(a, b) ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))

class CDDriveControl
{
public:
    void FUN_00479740(char drive);
    bool FUN_00479ba0(char drive);
    bool FUN_00479d60(char drive);
    bool FUN_00479ef0(char drive);
    bool FUN_0047a080(char drive);
    bool FUN_0047a3f0(HANDLE device, char drive);
    static bool __stdcall FUN_0047a6f0(CDDriveControl* self, HANDLE device,
                                       BYTE drive, BYTE level, short permissions);
};

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/cd_search_path.h"

typedef void* HANDLE;

struct FindData
{
    unsigned long Attributes;      // +0x000
    char          unknown_004[0x28];
    char          FileName[260];   // +0x02C
    char          AltName[14];     // +0x130
    char          unknown_13E[2];
};
GG_STATIC_ASSERT(offsetof(FindData, FileName) == 0x2C);
GG_STATIC_ASSERT(sizeof(FindData) == 0x140);   // frame 0x244 = 0x104 path + 0x140

extern "C" __declspec(dllimport) HANDLE __stdcall FindFirstFileA(char const* name, FindData* data);
extern "C" __declspec(dllimport) int __stdcall FindClose(HANDLE handle);

// GLOBAL: GAMEMD 0x81C8EC -- open find handle, -1 when none.
extern HANDLE DAT_0081C8EC;

#include "../_rt/gg_static_assert.h"
#include "../_layout/cd_search_path.h"

// FUNCTION: GAMEMD 0x0047AB10 (decl; reloc; ECX path/EAX result ABI view; original return type unknown)
int __fastcall FUN_0047AB10(char* basePath);

// GLOBAL: GAMEMD 0x0089E41C (writable path buffer; capacity not established)
extern char DAT_0089E41C[];

// LIBRARY: GAMEMD 0x007C93E8 (caller cleanup)
extern "C" void __cdecl FUN_007C93E8(void* block);
// LIBRARY: GAMEMD 0x007C8B3D (caller cleanup)
extern "C" void __cdecl FUN_007C8B3D(void* block);
// LIBRARY: GAMEMD 0x007D5408 (decl; reloc; caller-cleanup duplicate helper)
extern "C" char* __cdecl FUN_007D5408(char* text);
// LIBRARY: GAMEMD 0x007C8E17 (caller cleanup; operator new)
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);

GG_STATIC_ASSERT(sizeof(unsigned int) == 4);

// GLOBAL: GAMEMD 0x0089E414
extern unsigned int DAT_0089E414;
// GLOBAL: GAMEMD 0x0089E418
extern unsigned int DAT_0089E418;
GG_STATIC_ASSERT(sizeof(DAT_0089E414) == 4);
GG_STATIC_ASSERT(sizeof(DAT_0089E418) == 4);

#include "trivial_tu049_methods.h"

#include "../platform/ccfile_class.h"

#include "../ui/input_controls/sidebar_cctooltip.h"

// The display's pixel packer, expanded inline (see sidebar_cctooltip.h).
inline unsigned int PackColor(const TipRGB_00478E30& c)
{
    unsigned int blue = (c.B >> BlueRight_008A0DDC) << BlueLeft_008A0DD8;
    unsigned int green = (c.G >> GreenRight_008A0DE4) << GreenLeft_008A0DE0;
    unsigned int red = (c.R >> RedRight_008A0DD4) << RedLeft_008A0DD0;
    return blue | green | red;
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// Slot 1: positions the tooltip text box next to the gadget it belongs to, flipping
// it to the other side of the area's midline, clamping it to the area and growing
// the box to the measured text size.
//
// PARTIAL (99.0%, 189/191). Same instruction multiset as retail; the only two
// positional differences are the load order of `area->X` and `area->Width` in the
// horizontal overflow sum (retail loads X into EDX then Width into EBP, cl loads Width
// first and X second; the vertical sum matches). Variants tried: the expression in all
// 24 operand orders (cl canonicalises them, identical output), stepwise `over -= ..`
// statements, and named locals for `fx`, `ax`, `aw` loaded in either order.
// FUNCTION: GAMEMD 0x478BA0
bool CCToolTip::Update(ToolTipManagerData& from)
{
    if (WWMouseClassInstance->GetHideCount() >= 0) {
    TipFont_00478BA0* font = FontInstance_0089C4D0;
    const TipRect_00478BA0* area;
    if (SidebarSideFlag_00A8EB7C == 1) {
        if (from.X > TacticalRect_00886FA0.X + TacticalRect_00886FA0.Width) {
            area = &SidebarRect_00886F90;
            TipTouchedSidebar_00884B8E = 1;
        } else {
            area = &TacticalRect_00886FA0;
        }
    } else {
        if (from.X <= SidebarRect_00886F90.X + SidebarRect_00886F90.Width) {
            area = &SidebarRect_00886F90;
            TipTouchedSidebar_00884B8E = 1;
        } else {
            area = &TacticalRect_00886FA0;
        }
    }
    if (area) {
        int w;
        int h;
        font->FUN_00433CF0(from.HelpText, &w, &h, area->Width);
        w += 4;
        h += 3;
        from.Width = w > from.Width ? w : from.Width;
        from.Height = h > from.Height ? h : from.Height;
        if (from.Width >= area->Width) {
            font->FUN_00433CF0(from.HelpText, &w, &h, area->Width - 4);
            w += 4;
            h += 3;
            from.Width = w > from.Width ? w : from.Width;
            from.Height = h > from.Height ? h : from.Height;
        }
        const ToolTip* tip = CurrentToolTip;
        if (tip && tip->field_18) {
            const ToolTipBounds b = tip->Bounds;
            if (b.X < area->X + area->Width / 2) {
                from.X = b.X + b.Width - 5;
            } else {
                from.X = b.X - w + 5;
            }
            from.X = area->X > from.X ? area->X : from.X;
            if (b.Y < area->Y + area->Height / 2) {
                from.Y = b.Y + b.Height - 5;
            } else {
                from.Y = b.Y - h + 5;
            }
            from.Y = area->Y > from.Y ? area->Y : from.Y;
        } else {
            int over = from.X - area->X - area->Width + from.Width;
            if (over > 0) {
                from.X -= over;
            }
            from.Y += 16;
            over = from.Y - area->Y - area->Height + from.Height;
            if (over > 0) {
                from.Y = from.Y - from.Height - 16;
            }
        }
    }
    return true;
    }
    return false;
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x478DB0
void CCToolTip::MarkToRedraw(ToolTipManagerData& from)
{
    if (SidebarSideFlag_00A8EB7C == 1) {
        if (from.X >= TacticalRect_00886FA0.X + TacticalRect_00886FA0.Width) {
            TipTouchedSidebar_00884B8E = 1;
            SidebarNeedsRedraw_00884B8F = 1;
        }
    } else {
        if (from.X <= SidebarRect_00886F90.X + SidebarRect_00886F90.Width) {
            TipTouchedSidebar_00884B8E = 1;
            SidebarNeedsRedraw_00884B8F = 1;
        }
    }
    MapInstance_0087F7E8.FlagToRedraw(0);
    ToolTipManager::MarkToRedraw(from);
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x478E10
void CCToolTip::Draw(bool onSidebar)
{
    OnSidebar = onSidebar;
    ToolTipManager::Draw(!onSidebar);
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// Slot 4: draws the tooltip: picks the composite or sidebar surface from the side
// flag and the box position, measures the text, clamps the box to the surface,
// fills it with the packed tooltip colour and prints the text inside it.
//
// CAPPED at 2.9% positional (5/175; LCS 119/175 = 68%). Multiset delta: retail has 2
// `mov` that cl does not (everything else is identical). Retail loads the side flag
// byte into BL (`MOV BL,[0xA8EB7C]` ... `CMP BL,1`) between loading `from.X` (EAX) and
// `from.Y` (EDI); cl folds it into `CMP BYTE PTR [flag],1` and so hands EBX to the
// y local, which shifts every later register and the whole positional score. Variants
// tried: the flag as an unsigned char local declared first / between x and y / as a
// bool; the global typed unsigned char / char / bool / int; the two arms as `switch`
// (worse, 3.4% positional, LCS 68%); x and y as locals vs. direct field reads; the
// colour pack as a by-value copy, a const reference with locals declared B/G/R and
// every other declaration order (the by-reference inline reproduces retail's word load
// of G,B). Retail's frame (0x2C) and the `EBP` save around the print call match.
// FUNCTION: GAMEMD 0x478E30
void CCToolTip::DrawText(ToolTipManagerData& from)
{
    TipSurface_00478E30* surface;
    unsigned char side = SidebarSideFlag_00A8EB7C;
    int x = from.X;
    int y = from.Y;
    if (side == 1) {
        int limit = TacticalRect_00886FA0.X + TacticalRect_00886FA0.Width;
        if (from.X + from.Width <= limit) {
            surface = CompositeSurface_0088731C;
        } else {
            if (OnSidebar != 1 || from.X < limit) return;
            surface = SidebarSurface_00887300;
            x = from.X - limit;
            SidebarSurfaceUsed_00B0B518 = 1;
        }
    } else {
        int limit = SidebarRect_00886F90.X + SidebarRect_00886F90.Width;
        if (from.X >= limit) {
            surface = CompositeSurface_0088731C;
            x = from.X - limit;
        } else {
            if (OnSidebar != 1 || from.X + from.Width >= limit) return;
            surface = SidebarSurface_00887300;
            SidebarSurfaceUsed_00B0B518 = 1;
        }
    }
    if (!surface) return;

    const wchar_t* text = from.HelpText;
    TipFont_00478BA0* font = FontInstance_0089C4D0;
    TipRectLTRB_00478E30 box;
    box.Top = y;
    box.Bottom = y;
    box.Left = x;
    box.Right = x;
    int w;
    int h;
    font->FUN_00433CF0(text, &w, &h, (surface->*surface->Vtbl->At_7C)());
    box.Bottom = box.Top + h;
    box.Right = box.Left + w;
    int boxH = box.Bottom - box.Top + 4;
    int boxW = box.Right - box.Left + 8;
    if (box.Left + boxW > (surface->*surface->Vtbl->At_7C)()) {
        box.Left = (surface->*surface->Vtbl->At_7C)() - boxW;
    }
    box.Right = box.Left + boxW;
    box.Bottom = box.Top + boxH;
    unsigned int color = PackColor(TipColor_00B0FA1C);
    TipRect_00478BA0 fill;
    fill.X = box.Left;
    fill.Y = box.Top;
    fill.Width = boxW;
    fill.Height = boxH;
    (surface->*surface->Vtbl->At_14)(&fill, 0);
    (surface->*surface->Vtbl->At_58)(&fill, color);
    font->FUN_00433C90(1);
    font->FUN_00433CA0(&box);
    font->FUN_00433C70((unsigned short)color);
    PrinterInstance_0089C4B8->FUN_00434CD0(font, surface, text, box.Left + 4, box.Top + 2,
                                           box.Right - box.Left, box.Bottom - box.Top, 0, 0, 0);
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x479050
wchar_t* CCToolTip::GetToolTipText(unsigned int id)
{
    if (WWMouseClassInstance->GetHideCount() < 0) {
        return 0;
    }
    return MapInstance_0087F7E8.FUN_006D1800(id);
}

// FUNCTION: GAMEMD 0x004790E0 (44 bytes, ending RET 4)
bool CD_004790E0::FUN_004790E0(int value)
{
    if (value == -2) return true;
    if (DAT_0089E3A0 == 1) return true;
    unknown_04 = 0xffffffff;
    return FUN_004A8270(value);
}

// FUNCTION: GAMEMD 0x479700
// Empty function.
void __cdecl FUN_00479700()
{
}

// FUNCTION: GAMEMD 0x479730
// Empty function.
void __cdecl FUN_00479730()
{
}

// FUNCTION: GAMEMD 0x479740
void CDDriveControl::FUN_00479740(char drive)
{
    if (DAT_00887624)
    {
        FUN_0047a080(drive);
        return;
    }
    char root[4];
    char name[8];
    PreventRemoval removal;
    DWORD returned;
    sprintf(root, "%c:\\", drive + 'A');
    DWORD access;
    switch (GetDriveTypeA(root))
    {
        case 2:
            access = 0xC0000000;
            break;
        case 5:
            access = 0x80000000;
            break;
        default:
            FUN_004068E0("Attempt to open non-removable volume for locking or ejection\n");
            return;
    }
    sprintf(name, "\\\\.\\%c:", drive + 'A');
    HANDLE device = CreateFileA(name, access, 3, 0, 3, 0, 0);
    if (device == (HANDLE)-1)
    {
        FUN_004068E0("Unable to open drive %c: for ejection\n", drive + 'A');
        return;
    }
    for (int i = 0; i < 20; i++)
    {
        if (DeviceIoControl(device, 0x90018, 0, 0, 0, 0, &returned, 0))
        {
            if (!DeviceIoControl(device, 0x90020, 0, 0, 0, 0, &returned, 0))
            {
                FUN_004068E0("DeviceIoControl failed to dismount volume. Error %d - %s\n", GetLastError(), 0);
            }
            else
            {
                    removal.Prevent = 0;
                if (!DeviceIoControl(device, 0x2D4804, &removal, 1, 0, 0, &returned, 0))
                {
                    FUN_004068E0("DeviceIoControl failed to prevent media removal. Error %d - %s\n", GetLastError(), 0);
                }
                else if (!DeviceIoControl(device, 0x2D4808, 0, 0, 0, 0, &returned, 0))
                {
                    FUN_004068E0("DeviceIoControl failed to eject media. Error %d - %s\n", GetLastError(), 0);
                }
            }
            CloseHandle(device);
            return;
        }
        FUN_004068E0("DeviceIoControl failed to lock volume. Error %d - %s\n", GetLastError(), 0);
        Sleep(500);
    }
    CloseHandle(device);
}

// FUNCTION: GAMEMD 0x479BA0
bool CDDriveControl::FUN_00479ba0(char drive)
{
    bool ejected = false;
    char root[4];
    char name[8];
    PreventRemoval removal;
    DWORD returned;
    sprintf(root, "%c:\\", drive + 'A');
    DWORD access;
    switch (GetDriveTypeA(root))
    {
        case 2:
            access = 0xC0000000;
            break;
        case 5:
            access = 0x80000000;
            break;
        default:
            FUN_004068E0("Attempt to open non-removable volume for locking or ejection\n");
            return false;
    }
    sprintf(name, "\\\\.\\%c:", drive + 'A');
    HANDLE device = CreateFileA(name, access, 3, 0, 3, 0, 0);
    if (device == (HANDLE)-1)
    {
        FUN_004068E0("Unable to open drive %c: for ejection\n", drive + 'A');
        return false;
    }
    for (int i = 0; i < 20; i++)
    {
        if (DeviceIoControl(device, 0x90018, 0, 0, 0, 0, &returned, 0))
        {
            if (!DeviceIoControl(device, 0x90020, 0, 0, 0, 0, &returned, 0))
            {
                FUN_004068E0("DeviceIoControl failed to dismount volume. Error %d - %s\n", GetLastError(), 0);
            }
            else
            {
                    removal.Prevent = 0;
                if (!DeviceIoControl(device, 0x2D4804, &removal, 1, 0, 0, &returned, 0))
                {
                    FUN_004068E0("DeviceIoControl failed to prevent media removal. Error %d - %s\n", GetLastError(), 0);
                }
                else if (!DeviceIoControl(device, 0x2D4808, 0, 0, 0, 0, &returned, 0))
                {
                    FUN_004068E0("DeviceIoControl failed to eject media. Error %d - %s\n", GetLastError(), 0);
                }
                else
                {
                    ejected = true;
                }
            }
            break;
        }
        FUN_004068E0("DeviceIoControl failed to lock volume. Error %d - %s\n", GetLastError(), 0);
        Sleep(500);
    }
    CloseHandle(device);
    return ejected;
}

// FUNCTION: GAMEMD 0x479D60
bool CDDriveControl::FUN_00479d60(char drive)
{
    char root[4];
    char name[8];
    PreventRemoval removal;
    DWORD returned;
    sprintf(root, "%c:\\", drive + 'A');
    DWORD access;
    switch (GetDriveTypeA(root))
    {
        case 2:
            access = 0xC0000000;
            break;
        case 5:
            access = 0x80000000;
            break;
        default:
            FUN_004068E0("Attempt to open non-removable volume for locking or ejection\n");
            return false;
    }
    sprintf(name, "\\\\.\\%c:", drive + 'A');
    HANDLE device = CreateFileA(name, access, 3, 0, 3, 0, 0);
    if (device == (HANDLE)-1)
    {
        FUN_004068E0("Unable to open drive %c: for ejection\n", drive + 'A');
        return false;
    }
    int i;
    for (i = 0; i < 20; i++)
    {
        if (DeviceIoControl(device, 0x90018, 0, 0, 0, 0, &returned, 0))
        {
            removal.Prevent = 1;
            if (!DeviceIoControl(device, 0x2D4804, &removal, 1, 0, 0, &returned, 0))
            {
                FUN_004068E0("DeviceIoControl failed to prevent media removal. Error %d - %s\n", GetLastError(), 0);
            }
            break;
        }
        FUN_004068E0("DeviceIoControl failed to lock volume. Error %d - %s\n", GetLastError(), 0);
        Sleep(500);
    }
    for (i = 0; i < 20; i++)
    {
        if (DeviceIoControl(device, 0x9001C, 0, 0, 0, 0, &returned, 0))
        {
            break;
        }
        FUN_004068E0("DeviceIoControl failed to unlock volume. Error %d - %s\n", GetLastError(), 0);
        Sleep(500);
    }
    CloseHandle(device);
    return true;
}

// FUNCTION: GAMEMD 0x479EF0
bool CDDriveControl::FUN_00479ef0(char drive)
{
    char root[4];
    char name[8];
    PreventRemoval removal;
    DWORD returned;
    sprintf(root, "%c:\\", drive + 'A');
    DWORD access;
    switch (GetDriveTypeA(root))
    {
        case 2:
            access = 0xC0000000;
            break;
        case 5:
            access = 0x80000000;
            break;
        default:
            FUN_004068E0("Attempt to open non-removable volume for locking or ejection\n");
            return false;
    }
    sprintf(name, "\\\\.\\%c:", drive + 'A');
    HANDLE device = CreateFileA(name, access, 3, 0, 3, 0, 0);
    if (device == (HANDLE)-1)
    {
        FUN_004068E0("Unable to open drive %c: for ejection\n", drive + 'A');
        return false;
    }
    int i;
    for (i = 0; i < 20; i++)
    {
        if (DeviceIoControl(device, 0x90018, 0, 0, 0, 0, &returned, 0))
        {
            removal.Prevent = 0;
            if (!DeviceIoControl(device, 0x2D4804, &removal, 1, 0, 0, &returned, 0))
            {
                FUN_004068E0("DeviceIoControl failed to prevent media removal. Error %d - %s\n", GetLastError(), 0);
            }
            break;
        }
        FUN_004068E0("DeviceIoControl failed to lock volume. Error %d - %s\n", GetLastError(), 0);
        Sleep(500);
    }
    for (i = 0; i < 20; i++)
    {
        if (DeviceIoControl(device, 0x9001C, 0, 0, 0, 0, &returned, 0))
        {
            break;
        }
        FUN_004068E0("DeviceIoControl failed to unlock volume. Error %d - %s\n", GetLastError(), 0);
        Sleep(500);
    }
    CloseHandle(device);
    return true;
}

// FUNCTION: GAMEMD 0x47A3F0
bool CDDriveControl::FUN_0047a3f0(HANDLE device, char drive)
{
    LockParams params;
    DiocRegisters regs = {0};
    DWORD returned;

    params.NumLocks = 0;
    regs.EDX = (DWORD)&params;
    params.Operation = 2;
    regs.EAX = 0x440D;
    regs.EBX = drive;
    regs.ECX = 0x848;
    bool result = DeviceIoControl(device, 1, &regs, sizeof(regs), &regs, sizeof(regs), &returned, 0) != 0;
    if (result)
    {
        if (regs.Flags & 1)
        {
            if (regs.EAX != 0xB0 && regs.EAX != 1)
            {
                return false;
            }
            result = true;
        }
        FUN_004068E0("Apparent number of locks to undo = %d\n", params.NumLocks);
        if (params.NumLocks == 0)
        {
            params.NumLocks = 1;
        }
        for (int i = 0; i < params.NumLocks; i++)
        {
            regs.EDX = (DWORD)&params;
            params.Operation = 1;
            regs.EAX = 0x440D;
            regs.EBX = drive;
            regs.ECX = 0x848;
            bool ok = DeviceIoControl(device, 1, &regs, sizeof(regs), &regs, sizeof(regs), &returned, 0) != 0;
            if (!ok)
            {
                FUN_004068E0("DeviceIoControl failed to perform DOS IO control function. Error %d - %s\n", GetLastError(), 0);
            }
            if (!ok || (regs.Flags & 1))
            {
                result = false;
                break;
            }
            result = true;
        }
    }
    else
    {
        FUN_004068E0("DeviceIoControl failed to perform DOS IO control function. Error %d - %s\n", GetLastError(), 0);
        return false;
    }
    return result;
}

// FUNCTION: GAMEMD 0x47A6F0
bool __stdcall CDDriveControl::FUN_0047a6f0(CDDriveControl* self, HANDLE device,
                                            BYTE drive, BYTE level, short permissions)
{
    DiocRegisters regs = {0};
    DWORD returned;
    int retries = 5;
    do
    {
        BYTE category = 0;
        do
        {
            category = category ? 0x08 : 0x48;
            regs.EDX = permissions;
            regs.ECX = MAKEWORD(0x4A, category);
            regs.EAX = 0x440D;
            regs.EBX = MAKEWORD(drive, level);
            bool ok = DeviceIoControl(device, 1, &regs, sizeof(regs), &regs, sizeof(regs), &returned, 0) != 0;
            if (!ok)
            {
                FUN_004068E0("DeviceIoControl failed to perform DOS IO control function. Error %d - %s\n", GetLastError(), 0);
            }
            if (ok && !(regs.Flags & 1))
            {
                return true;
            }
        } while (category != 0x08);
        retries--;
        switch (regs.EAX)
        {
            case 0x01:
                FUN_004068E0("LOCK return eax error 'Function not supported'\n");
                break;
            case 0xB0:
                FUN_004068E0("LOCK return eax error 'Volume not locked in drive'\n");
                break;
            case 0xB2:
                FUN_004068E0("LOCK return eax error 'Volume not removable'\n");
                break;
            case 0xB4:
                FUN_004068E0("LOCK return eax error 'Lock count exceeded'\n");
                break;
            default:
                FUN_004068E0("LOCK return eax error %d\n", regs.EAX);
                break;
        }
        Sleep(1000);
    } while (retries > 0);
    return false;
}

// FUNCTION: GAMEMD 0x47AAB0  CDFileClass::Open (__thiscall)
// CDFileClass's vtable 0x7E1668 holds this at slot 7; CCFileClass's slot 7 is
// its own Open at 0x473D10, which calls this one. Straight delegation to the
// buffered-IO base. This cannot become a tail jump:
// the callee is __thiscall and pops its own argument, so the caller still owes
// its own RET 4.
bool CDFileClass::Open(FileAccessMode access)
{
    return BufferIOFileClass::Open(access);
}

// FUNCTION: GAMEMD 0x0047AAC0 (0x43-byte wrapper; tail jump to 0x47AB10)
int __cdecl FUN_0047AAC0(void)
{
    SearchPath_0047AE10* node = DAT_0089E410;
    while (node != 0) {
        SearchPath_0047AE10* next = node->Next;
        if (node->Path != 0) {
            FUN_007C93E8((void*)node->Path);
        }
        FUN_007C8B3D(node);
        node = next;
    }
    DAT_0089E410 = 0;
    return FUN_0047AB10(DAT_0089E41C);
}

// FUNCTION: GAMEMD 0x0047AD50 (69 bytes, entry-origin)
void __fastcall FUN_0047AD50(char* path)
{
    SearchPath_0047AE10* added =
        (SearchPath_0047AE10*)FUN_007C8E17(8);
    added->Path = FUN_007D5408(path);
    added->Next = 0;

    if (DAT_0089E410 == 0) {
        DAT_0089E410 = added;
        return;
    }

    SearchPath_0047AE10* tail = DAT_0089E410;
    while (tail->Next != 0) {
        tail = tail->Next;
    }
    tail->Next = added;
}

// FUNCTION: GAMEMD 0x0047ADA0 (17 bytes, entry-origin, RET)
void __fastcall FUN_0047ADA0(unsigned int value)
{
    unsigned int previous = DAT_0089E414;
    DAT_0089E414 = value;
    DAT_0089E418 = previous;
}

// FUNCTION: GAMEMD 0x0047ADC0 (66 bytes, no-argument caller view)
// Retail callers provide no arguments and ignore EAX; the original distinction
// between a global cdecl entry and another thisless no-argument convention is
// not observable from those call sites.
void __cdecl FUN_0047ADC0(void)
{
    SearchPath_0047AE10* node = DAT_0089E410;
    if (node != 0) {
        do {
            SearchPath_0047AE10* next = node->Next;
            if (node->Path != 0) {
                FUN_007C93E8((void*)node->Path);
            }
            FUN_007C8B3D(node);
            node = next;
        } while (node != 0);
        DAT_0089E410 = node;
        return;
    }
    DAT_0089E410 = 0;
}

// FUNCTION: GAMEMD 0x47AF70
bool __fastcall FUN_0047af70(char* name)
{
    if (name == 0)
    {
        return false;
    }
    if (DAT_0081C8EC != (HANDLE)-1)
    {
        FindClose(DAT_0081C8EC);
        DAT_0081C8EC = (HANDLE)-1;
    }
    char path[0x104];
    FindData data;
    strcpy(path, name);
    HANDLE handle = FindFirstFileA(path, &data);
    if (handle != (HANDLE)-1 && !(data.Attributes & 0x116))
    {
        strcpy(name, data.FileName);
        DAT_0081C8EC = handle;
        return true;
    }
    for (SearchPath_0047AE10* entry = DAT_0089E410; entry != 0; entry = entry->Next)
    {
        strcpy(path, entry->Path);
        strcat(path, name);
        handle = FindFirstFileA(path, &data);
        if (handle != (HANDLE)-1 && !(data.Attributes & 0x116))
        {
            strcpy(name, data.FileName);
            DAT_0081C8EC = handle;
            return true;
        }
    }
    return false;
}
