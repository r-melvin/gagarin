// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Menus cluster view of WebBrowser (UI input/controls module). Read from the retail gamemd.exe v1.001:
//   RTTI .?AVWebBrowser@@ (vtable 0x7F743C; bases IWOLBrowserEvent then IUnknown, both at offset 0, so the
//   one vtable is the COM table: slots 0..2 are IUnknown, slots 3..16 the event sink, slot 17 the
//   class's own destructor), the bodies in menus_web_browser.cpp (every offset below) and the
//   constructors 0x773450 / 0x773500 (not bound here).
//
//   Address-scoped view. Calling conventions: the sink slots are __stdcall with `this` on the stack (the
//   RET immediates are 4 for this alone, 8 and 12 with one and two arguments); slot 17 is the
//   __thiscall scalar deleting destructor (it reads ECX and its RET 4 pops only the delete flag).
//   The names of slots 3..16 are not recovered; they are named by address. The class has no allocation
//   site in this cluster, so its size is not asserted (offsets only).
#ifndef GG_MATCH_UI_INPUT_CONTROLS_MENUS_WEB_BROWSER_H
#define GG_MATCH_UI_INPUT_CONTROLS_MENUS_WEB_BROWSER_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "../../network/wonline.h"

typedef long MenusHResult;
typedef unsigned long MenusULong;

struct MenusGuid
{
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];
};
GG_STATIC_ASSERT(sizeof(MenusGuid) == 0x10);

// GLOBAL: GAMEMD 0x7F7C90 -- IID_IUnknown.
extern const MenusGuid MenusIidUnknown;
// GLOBAL: GAMEMD 0x7F7C20 -- the IID of the browser event interface the sink answers to.
extern const MenusGuid MenusIidBrowserEvent;

// The embedded browser object (this+8): a COM interface, every slot __stdcall with the receiver pushed.
// Slot 2 is Release, slot 4 (+0x10) and slot 6 (+0x18) are the calls the destructor makes, and slot 16
// (+0x40) takes a wide string and two more words.
class MenusWOLBrowser
{
public:
    virtual MenusHResult __stdcall Slot0();
    virtual MenusULong   __stdcall Slot1();
    virtual MenusULong   __stdcall Release();
    virtual MenusHResult __stdcall Slot3();
    virtual MenusHResult __stdcall Slot4();
    virtual MenusHResult __stdcall Slot5();
    virtual MenusHResult __stdcall Slot6(void* sink);
    virtual MenusHResult __stdcall Slot7();
    virtual MenusHResult __stdcall Slot8();
    virtual MenusHResult __stdcall Slot9();
    virtual MenusHResult __stdcall Slot10();
    virtual MenusHResult __stdcall Slot11();
    virtual MenusHResult __stdcall Slot12();
    virtual MenusHResult __stdcall Slot13();
    virtual MenusHResult __stdcall Slot14();
    virtual MenusHResult __stdcall Slot15();
    virtual MenusHResult __stdcall Navigate(const wchar_t* url, int arg1, const void* arg2);
};

// USER32 / ADVAPI32 imports (dllimport: the calls go through the IAT, 0x7E1474 / 0x7E100C / 0x7E1008 /
// 0x7E1004). GetWindowLongA's result is used as a pointer to the window's data block.
extern "C" __declspec(dllimport) int* __stdcall GetWindowLongA(void* hwnd, int index);
extern "C" __declspec(dllimport) long __stdcall RegOpenKeyExA(unsigned long hkey, const char* subKey,
    unsigned long options, unsigned long sam, unsigned long* result);
extern "C" __declspec(dllimport) long __stdcall RegQueryValueExA(unsigned long hkey, const char* name,
    unsigned long* reserved, unsigned long* type, void* data, unsigned long* size);
extern "C" __declspec(dllimport) long __stdcall RegCloseKey(unsigned long hkey);

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- the debug log call (an empty cdecl function).
void __cdecl MenusDebugLog(const char* format, ...);

// GLOBAL: GAMEMD 0x8496B8 -- the constant the load-page slot passes to Navigate.
extern const int MenusNavigateArg;
// STRING: GAMEMD 0x8496C4 / 0x84962C -- wide strings appended to the two page paths the load-page slot builds.
extern const wchar_t MenusPageSuffixA[];
extern const wchar_t MenusPageSuffixB[];
// STRING: GAMEMD 0x815E74 -- appended to the registry path when it does not end in a separator.
extern const char MenusPathSuffix[];

// A text holder (one pointer): built from a C string by 0x7B4630, assigned from one by 0x7B48D0, released
// by the body at 0x7B46F0 (the same holder as the GraphicMenu name; separate view).
struct MenusWebString
{
    MenusWebString(const char* text);                  // 0x7B4630
    ~MenusWebString();                                 // 0x7B46F0
    MenusWebString& operator=(const char* text);       // 0x7B48D0
    void* Block;                                       // +0x00
};

// The profile the login slot looks up; only the word at +0x10 is read.
struct MenusProfile
{
    char _pad000[0x10];
    int  Field10;  // +0x10
};
GG_STATIC_ASSERT(offsetof(MenusProfile, Field10) == 0x10);

// rc_ptr<PlayerProfile>: a reference-counted pointer. The base destructor body is 0x65D460 (it sets the
// base vtable 0x7F094C, then releases); the derived inline destructor stores vtable 0x7F3F44 and calls it.
class MenusRcBase
{
public:
    virtual ~MenusRcBase();   // 0x65D460
    MenusProfile* Ptr;        // +0x04
};
GG_STATIC_ASSERT(offsetof(MenusRcBase, Ptr) == 0x04);

class MenusProfileRef : public MenusRcBase
{
public:
    virtual ~MenusProfileRef() {}
};

// FUNCTION: GAMEMD 0x778A20 (decl; reloc) -- __fastcall(hidden result in ECX, name in EDX), plain RET.
MenusProfileRef __fastcall MenusFindProfile(const MenusWebString& name);

// A five-byte flag record: zeroed inline, filled in by 0x5175F0, tested by 0x5176B0.
struct MenusLoginFlags
{
    MenusLoginFlags() : Bits(0), Mode(0) {}
    void Func_5175F0();
    bool Func_5176B0();
    int  Bits;   // +0x00
    char Mode;   // +0x04
};

// FUNCTION: GAMEMD 0x789500 (decl; reloc) -- __fastcall(login ECX, password EDX, 1, profile word), RET 8.
void __fastcall MenusRegisterLogin(const char* login, const char* password, int one, int profileWord);

// SessionClass::Instance (0xA8B238); only 0x6990A0 is called here.
struct MenusWebSession
{
    void Func_6990A0();
};
// GLOBAL: GAMEMD 0xA8B238
extern MenusWebSession MenusWebSessionInstance;

// VTABLE: GAMEMD 0x7F743C
class WebBrowser
{
public:
    virtual MenusHResult __stdcall QueryInterface(const MenusGuid& iid, void** object);  // 0x773A40
    virtual MenusULong   __stdcall AddRef();                                             // 0x773AA0
    virtual MenusULong   __stdcall Release();                                            // 0x773AB0
    virtual MenusHResult __stdcall Slot3();                                              // 0x773AD0
    virtual MenusHResult __stdcall Slot4();                                              // 0x773B00 (not bound)
    virtual MenusHResult __stdcall Slot5(void* arg1, int arg2);                          // 0x773B10
    virtual MenusHResult __stdcall Slot6();                                              // 0x773B40 (not bound)
    virtual MenusHResult __stdcall Slot7();                                              // 0x773B50 (not bound)
    virtual MenusHResult __stdcall Slot8();                                              // 0x773B60 (not bound)
    virtual MenusHResult __stdcall Slot9();                                              // 0x773B70 (not bound)
    virtual MenusHResult __stdcall Slot10();                                             // 0x773B80 (not bound)
    virtual MenusHResult __stdcall Slot11();                                             // 0x773B90 (not bound)
    virtual MenusHResult __stdcall Slot12();                                             // 0x773BA0
    virtual MenusHResult __stdcall Slot13();                                             // 0x773BB0 (not bound)
    virtual MenusHResult __stdcall Slot14();                                             // 0x773BC0
    virtual MenusHResult __stdcall Slot15(const wchar_t* message);                       // 0x773D20
    virtual MenusHResult __stdcall Slot16(const wchar_t* login, const wchar_t* password);// 0x773D40
    virtual ~WebBrowser()                                                                // 0x7740A0
    {
        MenusDebugLog("Destructing embedded WebBrowser\n");
        if (Browser) {
            MenusDebugLog("Releasing WOLBrowser\n");
            Browser->Slot6(this);
            Browser->Slot4();
        }
        if (Browser)
            Browser->Release();
    }

    MenusULong       RefCount;      // +0x04
    MenusWOLBrowser* Browser;       // +0x08
    wchar_t          PagePath[0x202];  // +0x0C
    void*            Window;        // +0x410
};
GG_STATIC_ASSERT(offsetof(WebBrowser, RefCount) == 0x04);
GG_STATIC_ASSERT(offsetof(WebBrowser, Browser) == 0x08);
GG_STATIC_ASSERT(offsetof(WebBrowser, PagePath) == 0x0C);
GG_STATIC_ASSERT(offsetof(WebBrowser, Window) == 0x410);

#endif  // GG_MATCH_UI_INPUT_CONTROLS_MENUS_WEB_BROWSER_H
