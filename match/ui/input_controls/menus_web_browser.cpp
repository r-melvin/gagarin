// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// WebBrowser entries (layout and evidence: menus_web_browser.h).
// LIBRARY: GAMEMD 0x7C8B3D -- operator delete; GAMEMD 0x7C8DF0 -- _strrchr; GAMEMD 0x7CA45F -- _wcscat;
//          GAMEMD 0x7CC2AC -- _mbstowcs.

#include <string.h>
#include <stdlib.h>
#include "menus_web_browser.h"

// FUNCTION: GAMEMD 0x773A40
MenusHResult __stdcall WebBrowser::QueryInterface(const MenusGuid& iid, void** object)
{
    *object = 0;
    if (memcmp(&iid, &MenusIidUnknown, sizeof(MenusGuid)) == 0
        || memcmp(&iid, &MenusIidBrowserEvent, sizeof(MenusGuid)) == 0) {
        *object = this;
        AddRef();
        return 0;
    }
    return 0x80004002;
}

// FUNCTION: GAMEMD 0x773AA0
MenusULong __stdcall WebBrowser::AddRef()
{
    return ++RefCount;
}

// FUNCTION: GAMEMD 0x773AB0
MenusULong __stdcall WebBrowser::Release()
{
    if (--RefCount == 0) {
        delete this;
        return 0;
    }
    return RefCount;
}

// FUNCTION: GAMEMD 0x773AD0
MenusHResult __stdcall WebBrowser::Slot3()
{
    if (Window) {
        int* data = GetWindowLongA(Window, 8);
        *data = 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x773B10
MenusHResult __stdcall WebBrowser::Slot5(void*, int arg2)
{
    if (arg2)
        Browser->Navigate(PagePath, 0, &MenusNavigateArg);
    return 0;
}

// FUNCTION: GAMEMD 0x773BA0
MenusHResult __stdcall WebBrowser::Slot12()
{
    return 0x80004005;
}

// FUNCTION: GAMEMD 0x773BC0
// Logs the certification failure, then loads the local page named by the HTMLPath registry value.
MenusHResult __stdcall WebBrowser::Slot14()
{
    MenusDebugLog("!!!!! PAGE FAILED CERTIFICATION !!!!!\n");
    unsigned long key;
    if (RegOpenKeyExA(0x80000002, "Software\\Westwood\\Yuri's Revenge", 0, 0x20019, &key) == 0) {
        char path[0x104];
        unsigned long type;
        unsigned long size = 0x104;
        long result = RegQueryValueExA(key, "HTMLPath", 0, &type, path, &size);
        RegCloseKey(key);
        if (result == 0) {
            char* separator = strrchr(path, '\\');
            if (separator == 0 || strlen(path) > (unsigned)(separator - path + 1))
                strcat(path, MenusPathSuffix);
            mbstowcs(PagePath, path, 0x104);
            wcscat(PagePath, MenusPageSuffixA);
            wchar_t page[0x104];
            mbstowcs(page, path, 0x104);
            wcscat(page, MenusPageSuffixB);
            return Browser->Navigate(page, 0, 0);
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x773D20
MenusHResult __stdcall WebBrowser::Slot15(const wchar_t* message)
{
    MenusDebugLog("OnErrorMsg- %S\n", message);
    return 0;
}

// FUNCTION: GAMEMD 0x773D40
// Converts the login and password, looks the profile up, and (when the flag test allows) registers them.
MenusHResult __stdcall WebBrowser::Slot16(const wchar_t* login, const wchar_t* password)
{
    char loginName[0x40];
    char passwordName[0x40];
    wcstombs(loginName, login, 0x40);
    wcstombs(passwordName, password, 0x40);
    MenusWebString name(loginName);
    MenusDebugLog("Register WWOnline login: %s - %s\n", loginName, passwordName);
    MenusProfileRef profile = MenusFindProfile(name);
    MenusLoginFlags flags;
    flags.Func_5175F0();
    if (flags.Func_5176B0()) {
        MenusRegisterLogin(loginName, passwordName, 1, profile.Ptr->Field10);
        MenusWebSessionInstance.Func_6990A0();
    }
    DAT_00B73E40 = loginName;
    DAT_00B7778C = passwordName;
    return 0;
}

// The scalar deleting destructor 0x7740A0 is not reproduced: cl emits ??_G only beside a constructor, and the
// constructor 0x773500 is not matched.
