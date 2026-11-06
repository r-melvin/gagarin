// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The message-log object reached through the table at 0xABF168 (index 4 at 0x54A8C0, read with 0x5BC450).
//   0x5BD1F0 is a variadic member function (so __cdecl with `this` as the first stack word), see
//   message_log_printf_methods.cpp. Class and method names are descriptive; no size is asserted.
#ifndef GG_MATCH_MESSAGE_LOG_005BD0D0_H
#define GG_MATCH_MESSAGE_LOG_005BD0D0_H

class MessageLog_005BD0D0
{
public:
    // FUNCTION: GAMEMD 0x5BD0D0 (decl; reloc)
    void FUN_005BD0D0(const char* text);
    // FUNCTION: GAMEMD 0x5BD1F0 (declaration; body in message_log_printf_methods.cpp)
    void __cdecl Printf(const char* format, ...);
    // FUNCTION: GAMEMD 0x5BD240 (declaration; body in message_log_printf_methods.cpp)
    void __cdecl PrintfWide(const wchar_t* format, ...);

    // GLOBAL: GAMEMD 0xABF23A
    static bool Enabled;
};

#endif  // GG_MATCH_MESSAGE_LOG_005BD0D0_H
