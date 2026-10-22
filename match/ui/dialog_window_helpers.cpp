// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, IAT slots, globals and strings read off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI (0x775BC0..0x776CCB).
//
// Win32 dialog helpers: a child-window scaler run through EnumChildWindows,
// a font cache keyed by face/size/style, the end of a tree-view drag and the
// tree/list view state load/save walkers.
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <commctrl.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xB732F0 -- the module handle.
extern HINSTANCE DAT_00B732F0;
// GLOBAL: GAMEMD 0xB72F54 / 0xB72F58 -- client extent of the reference dialog.
extern int DAT_00B72F54;
extern int DAT_00B72F58;
// GLOBAL: GAMEMD 0x849DE0 / 0x849DE4 -- target dialog extent.
extern int DAT_00849DE0;
extern int DAT_00849DE4;
// GLOBAL: GAMEMD 0xB7309C -- a tree-view drag is in progress.
extern bool DAT_00B7309C;
// GLOBAL: GAMEMD 0xB730A0 -- the tree view being dragged in.
extern HWND DAT_00B730A0;
// GLOBAL: GAMEMD 0xB730A8 -- the drag image list.
extern HIMAGELIST DAT_00B730A8;
// GLOBAL: GAMEMD 0xB73098 -- INI section the view state lives under.
extern const char* DAT_00B73098;

// STRING: GAMEMD 0x83370C -- "ComboBox"
extern const char STR_0083370C[];
// STRING: GAMEMD 0x849E34 -- "LV%d"
extern const char STR_00849E34[];
// STRING: GAMEMD 0x849E3C -- "SysListView32"
extern const char STR_00849E3C[];
// STRING: GAMEMD 0x849E4C -- "TV%d"
extern const char STR_00849E4C[];
// STRING: GAMEMD 0x849E54 -- "SysTreeView32"
extern const char STR_00849E54[];

// FUNCTION: GAMEMD 0x775B40 (decl; reloc) -- the reference dialog's procedure.
BOOL CALLBACK FUN_00775B40(HWND, UINT, WPARAM, LPARAM);

// The INI reader/writer the view-state walkers are handed through lParam.
class INIClass
{
public:
    // FUNCTION: GAMEMD 0x5275C0 (decl; reloc)
    bool WriteInteger(const char* section, const char* key, int value, int format);
    // FUNCTION: GAMEMD 0x5276D0 (decl; reloc)
    int  ReadInteger(const char* section, const char* key, int defvalue);
    // FUNCTION: GAMEMD 0x529560 (decl; reloc)
    bool WriteBool(const char* section, const char* key, bool value);
    // FUNCTION: GAMEMD 0x5295F0 (decl; reloc)
    bool ReadBool(const char* section, const char* key, bool defvalue);
};

// One cached font: face name, the three creation parameters and the handle.
struct FontCacheEntry
{
    char  Name[0x80];   // +0x00
    int   Height;       // +0x80
    int   Width;        // +0x84
    int   Style;        // +0x88
    HFONT Font;         // +0x8C
};

// The growable array the cache lives in (count, capacity, data).
template<class Elem>
struct FontCacheVector
{
    int Count;      // +0x00
    int Capacity;   // +0x04
    Elem*  Data;       // +0x08

    void Fetch(int index, Elem& item) const
    {
        if (index >= 0 && index < Count) {
            item = Data[index];
        }
    }
    void Grow()
    {
        if (Count >= Capacity) {
            int size = Count * 2;
            if (size < 10) {
                size = 10;
            }
            Elem* data = (Elem*)operator new(size * sizeof(Elem));
            memset(data, 0, size * sizeof(Elem));
            if (Data) {
                memcpy(data, Data, Count * sizeof(Elem));
            }
            operator delete(Data);
            Data = data;
            Capacity = size;
        }
    }
    void Insert(int index, const Elem& item)
    {
        if (index > Count) {
            index = Count;
        }
        if (index >= Capacity) {
            Grow();
        }
        Grow();
        if (index < Count) {
            memmove(&Data[index + 1], &Data[index], (Count - index) * sizeof(Elem));
        }
        Elem* slot = &Data[index];
        if (slot) {
            *slot = item;
        }
        Count++;
    }
};
// `LEA ESI,[EBX+EBX*8]; SHL ESI,4` sizes the grown block in 0x775DB0.
GG_STATIC_ASSERT(sizeof(FontCacheEntry) == 0x90);
// VC6 rejects offsetof on a template instantiation; the +0x04/+0x08 offsets
// are carried by the bound globals 0xB72F3C / 0xB72F40.

// GLOBAL: GAMEMD 0xB72F38 -- the font cache.
extern FontCacheVector<FontCacheEntry> DAT_00B72F38;

// What 0x776490 reports about the window under a drag point (ten dwords; the
// window at +0x04 and the point at +0x10/+0x14 are the fields read here).
struct DragTargetInfo
{
    int  unknown_00;    // +0x00
    HWND Window;        // +0x04
    int  unknown_08;    // +0x08
    int  unknown_0C;    // +0x0C
    int  X;             // +0x10
    int  Y;             // +0x14
    int  unknown_18[4]; // +0x18
};
GG_STATIC_ASSERT(offsetof(DragTargetInfo, Window) == 0x04 &&
                 offsetof(DragTargetInfo, X) == 0x10 &&
                 offsetof(DragTargetInfo, Y) == 0x14);
// `MOV ECX,0xA; REP MOVSD` copies the returned value in 0x776320.
GG_STATIC_ASSERT(sizeof(DragTargetInfo) == 0x28);

// FUNCTION: GAMEMD 0x776490 (decl; reloc)
DragTargetInfo __fastcall FUN_00776490(LPARAM point);

HFONT __fastcall FUN_007760B0(HDC dc, const char* face, int height,
                                    int width, unsigned style);

// FUNCTION: GAMEMD 0x775BC0
//
// EnumChildWindows callback: rescale one child from the reference dialog's
// client extent to the target extent (combo boxes use their dropped-down
// rectangle; `relative` makes the rectangle parent-relative first).
BOOL CALLBACK ScaleChildEnumProc(HWND window, LPARAM relative)
{
    RECT rect;
    RECT other;
    char className[0x80];

    GetWindowRect(window, &rect);
    GetClassNameA(window, className, sizeof(className));
    if (strcmp(className, STR_0083370C) == 0) {
        SendMessageA(window, CB_GETDROPPEDCONTROLRECT, 0, (LPARAM)&rect);
    }

    if (relative) {
        HWND parent = (HWND)GetWindowLongA(window, GWL_HWNDPARENT);
        GetWindowRect(parent, &other);
        rect.left -= other.left;
        rect.right -= other.left;
        rect.top -= other.top;
        rect.bottom -= other.top;
    }

    if (!DAT_00B72F54) {
        HWND dialog = CreateDialogParamA(DAT_00B732F0, MAKEINTRESOURCE(0xC6),
                                         NULL, FUN_00775B40, 0);
        GetClientRect(dialog, &other);
        DestroyWindow(dialog);
        DAT_00B72F54 = other.right;
        DAT_00B72F58 = other.bottom;
    }

    int width = (rect.right - rect.left + 1) * DAT_00849DE0 / DAT_00B72F54;
    int height = (rect.bottom - rect.top + 1) * DAT_00849DE4 / DAT_00B72F58;
    rect.left = DAT_00849DE0 * rect.left / DAT_00B72F54;
    rect.top = DAT_00849DE4 * rect.top / DAT_00B72F58;
    rect.right = width - 1 + rect.left;
    rect.bottom = height - 1 + rect.top;
    MoveWindow(window, rect.left, rect.top, width, height, TRUE);
    return TRUE;
}

// FUNCTION: GAMEMD 0x775DB0
//
// Return the cached font for (face, height, width, style), creating and
// caching it when `dc` is supplied.
HFONT __fastcall FUN_00775DB0(HDC dc, const char* face, int height,
                                int width, int style)
{
    FontCacheEntry entry;

    for (int i = 0; i < DAT_00B72F38.Count; i++) {
        DAT_00B72F38.Fetch(i, entry);
        if (strcmp(entry.Name, face) == 0 && entry.Height == height &&
            entry.Width == width && entry.Style == style) {
            return entry.Font;
        }
    }

    if (!dc) {
        return 0;
    }
    HFONT font = FUN_007760B0(dc, face, height, width, style);
    if (!font) {
        return 0;
    }
    strcpy(entry.Name, face);
    entry.Height = height;
    entry.Width = width;
    entry.Style = style;
    entry.Font = font;
    DAT_00B72F38.Insert(DAT_00B72F38.Count, entry);
    return font;
}

// FUNCTION: GAMEMD 0x7760B0
//
// Create a font of the given device size and style bits (1 bold, 2 italic,
// 4 underline, 8 strike-out) in an identity-mapped DC; with a height, the
// width is refitted from the first font's average character width.
HFONT __fastcall FUN_007760B0(HDC dc, const char* face, int height,
                                    int width, unsigned style)
{
    POINT size;
    TEXTMETRICA metrics;
    LOGFONTA font;

    SaveDC(dc);
    SetGraphicsMode(dc, GM_ADVANCED);
    ModifyWorldTransform(dc, NULL, MWT_IDENTITY);
    SetViewportOrgEx(dc, 0, 0, NULL);
    SetWindowOrgEx(dc, 0, 0, NULL);
    size.x = height;
    size.y = width;
    DPtoLP(dc, &size, 1);

    font.lfHeight = -size.y;
    font.lfWidth = 0;
    font.lfEscapement = 0;
    font.lfOrientation = 0;
    font.lfWeight = (style & 1) ? FW_BOLD : 0;
    font.lfItalic = (BYTE)((style >> 1) & 1);
    font.lfUnderline = (BYTE)((style >> 2) & 1);
    font.lfStrikeOut = (BYTE)((style >> 3) & 1);
    font.lfCharSet = 0;
    font.lfOutPrecision = 0;
    font.lfClipPrecision = 0;
    font.lfQuality = 0;
    font.lfPitchAndFamily = 0;
    strcpy(font.lfFaceName, face);
    HFONT result = CreateFontIndirectA(&font);

    if (height) {
        HGDIOBJ old = SelectObject(dc, result);
        GetTextMetricsA(dc, &metrics);
        DeleteObject(SelectObject(dc, old));
        font.lfWidth = (LONG)(fabs((double)size.x) * metrics.tmAveCharWidth
                              / fabs((double)size.y) + 0.5);
        result = CreateFontIndirectA(&font);
    }
    RestoreDC(dc, -1);
    return result;
}

// FUNCTION: GAMEMD 0x776320
//
// Finish a tree-view drag at `point`: ask the window under the point whether
// it takes the drop (0x4C8), show the matching cursor, tear down the drag
// image, deliver the drop (0x4CA) and clear the drop highlight.
bool __fastcall FUN_00776320(LPARAM point)
{
    if (DAT_00B7309C) {
        ImageList_DragShowNolock(FALSE);
        DragTargetInfo target = FUN_00776490(point);
        bool accepted;
        if (SendMessageA(target.Window, 0x4C8, (WPARAM)&target, point)) {
            SetCursor(LoadCursorA(NULL, IDC_ARROW));
            accepted = true;
        } else {
            SetCursor(LoadCursorA(NULL, IDC_NO));
            accepted = false;
        }
        ImageList_DragShowNolock(TRUE);

        RECT rect;
        GetWindowRect(target.Window, &rect);
        ImageList_DragMove(target.X - rect.left, target.Y - rect.top);
        ImageList_EndDrag();
        ReleaseCapture();
        ImageList_Destroy(DAT_00B730A8);
        DAT_00B730A8 = NULL;
        DAT_00B7309C = false;

        DragTargetInfo drop = FUN_00776490(point);
        if (accepted) {
            SendMessageA(drop.Window, 0x4CA, (WPARAM)&drop, point);
        }
        KillTimer(drop.Window, 1);
        SendMessageA(DAT_00B730A0, TVM_SELECTITEM, TVGN_DROPHILITE, 0);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x7768F0
//
// EnumChildWindows callback: restore tree-view expansion ("TV<n>") and
// list-view column widths ("LV<n>") from the INI handed in `lParam`.
BOOL CALLBACK FUN_007768F0(HWND window, LPARAM lParam)
{
    INIClass* ini = (INIClass*)lParam;
    char text[0x40];

    GetClassNameA(window, text, sizeof(text));
    if (strcmp(text, STR_00849E54) == 0) {
        const char* section = DAT_00B73098;
        int index = 0;
        for (HTREEITEM item = (HTREEITEM)SendMessageA(window, TVM_GETNEXTITEM, TVGN_ROOT, 0);
             item;
             item = (HTREEITEM)SendMessageA(window, TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)item)) {
            index++;
            wsprintfA(text, STR_00849E4C, index);
            UINT action;
            if (ini->ReadBool(section, text, false)) {
                action = TVE_EXPAND;
            } else {
                action = TVE_COLLAPSE;
            }
            SendMessageA(window, TVM_EXPAND, action, (LPARAM)item);
        }
    }

    GetClassNameA(window, text, sizeof(text));
    if (strcmp(text, STR_00849E3C) == 0) {
        const char* section = DAT_00B73098;
        if (window) {
            for (int column = 0; column < 10; column++) {
                wsprintfA(text, STR_00849E34, column);
                unsigned width = ini->ReadInteger(section, text,
                    SendMessageA(window, LVM_GETCOLUMNWIDTH, column, 0));
                if (width < 1000) {
                    SendMessageA(window, LVM_SETCOLUMNWIDTH, column, MAKELPARAM(width, 0));
                }
            }
        }
    }
    return TRUE;
}

// FUNCTION: GAMEMD 0x776B40
//
// EnumChildWindows callback: save tree-view expansion ("TV<n>") and list-view
// column widths ("LV<n>") into the INI handed in `lParam`.
BOOL CALLBACK FUN_00776B40(HWND window, LPARAM lParam)
{
    INIClass* ini = (INIClass*)lParam;
    char key[0x20];
    union {
        char    Name[0x40];
        TVITEMA Item;
    } scratch;

    GetClassNameA(window, scratch.Name, sizeof(scratch.Name));
    if (strcmp(scratch.Name, STR_00849E54) == 0) {
        const char* section = DAT_00B73098;
        int index = 0;
        for (HTREEITEM item = (HTREEITEM)SendMessageA(window, TVM_GETNEXTITEM, TVGN_ROOT, 0);
             item;
             item = (HTREEITEM)SendMessageA(window, TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)item)) {
            index++;
            wsprintfA(key, STR_00849E4C, index);
            scratch.Item.mask = TVIF_HANDLE | TVIF_STATE;
            scratch.Item.stateMask = TVIS_EXPANDED;
            scratch.Item.hItem = item;
            if (SendMessageA(window, TVM_GETITEMA, 0, (LPARAM)&scratch.Item)) {
                bool expanded = false;
                if (scratch.Item.state & TVIS_EXPANDED) {
                    expanded = true;
                }
                ini->WriteBool(section, key, expanded);
            }
        }
    }

    GetClassNameA(window, scratch.Name, sizeof(scratch.Name));
    if (strcmp(scratch.Name, STR_00849E3C) == 0) {
        const char* section = DAT_00B73098;
        if (window) {
            for (int column = 0; column < 10; column++) {
                wsprintfA(key, STR_00849E34, column);
                unsigned width = SendMessageA(window, LVM_GETCOLUMNWIDTH, column, 0);
                if (width < 1000) {
                    ini->WriteInteger(section, key, width, 0);
                }
            }
        }
    }
    return TRUE;
}
