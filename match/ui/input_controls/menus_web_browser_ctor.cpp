// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// WebBrowser construction (layout and evidence: menus_web_browser.h). The factory expands the
// constructor and the component set-up inline; both are also kept out of line.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//
// Address index:
//   0x773450  FUN_00773450 (factory)
//   0x773500  WebBrowser::WebBrowser
//   0x773590  WebBrowser::Initialise
//
// LIBRARY: IAT 0x7E15FC OLE32!CoCreateInstance; GAMEMD 0x7C8E17 -- operator new.

#include "menus_web_browser.h"

extern "C" __declspec(dllimport) long __stdcall CoCreateInstance(const MenusGuid& clsid, void* outer,
    unsigned long context, const MenusGuid& iid, void** object);

// GLOBAL: GAMEMD 0x7F7C60 -- CLSID of the embedded browser component.
extern const MenusGuid MenusClsidWOLBrowser;
// GLOBAL: GAMEMD 0x7F7C30 -- the IID the component is asked for.
extern const MenusGuid MenusIidWOLBrowser;

// FUNCTION: GAMEMD 0x773450
// PARTIAL: 93.2% -- retail schedules the first field store of the inlined constructor ahead of
// the log-string push; only that ordering differs (instruction multiset identical).
// Builds a browser for `window`: allocates it, then creates and starts the component.
WebBrowser* __fastcall FUN_00773450(void* window, const void* arg)
{
    WebBrowser* browser = new WebBrowser;
    if (browser)
        browser->Initialise(window, arg);
    return browser;
}

// FUNCTION: GAMEMD 0x773500
WebBrowser::WebBrowser()
    : RefCount(1), Browser(0), unknown_40C(false), Window(0)
{
    MenusDebugLog("Instantiating embedded WebBrowser\n");
}

// FUNCTION: GAMEMD 0x773590
// Remembers the window, creates the browser component, hooks this sink to it and starts it.
bool WebBrowser::Initialise(void* window, const void* arg)
{
    Window = window;
    MenusDebugLog("Creating WOLBrowser component.\n");
    if (CoCreateInstance(MenusClsidWOLBrowser, 0, 1, MenusIidWOLBrowser, (void**)&Browser) >= 0) {
        MenusDebugLog("Starting up WOLBrowser\n");
        Browser->Slot5(this);
        Browser->Slot3(window, arg);
        Browser->Slot15(1);
    }
    return true;
}
