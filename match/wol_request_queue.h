// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The request queue at 0xA8EA70 and the 250-byte request blocks the WOL scenario dialog sends
//   through it (0x5F1BF0 takes a block, its size and a flag). Every offset is read off the stores
//   of the senders 0x5B5E90, 0x5B5EF0, 0x5B6CD0 and 0x5B6DA0 in retail gamemd.exe v1.001.
#ifndef GG_MATCH_UI_WOL_REQUEST_QUEUE_H
#define GG_MATCH_UI_WOL_REQUEST_QUEUE_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "_layout/version_class.h"

// The request block 0x5B5E90 sends to the 0xA8EA70 queue: 250 bytes, zero but for the leading code.
struct WolRequestBlock_005B5E90 {
    int Code;
    char unknown_04[246];
};
struct WolRequestQueue_00A8EA70 {
    // FUNCTION: GAMEMD 0x5F1BF0 (decl; reloc)
    void FUN_005F1BF0(WolRequestBlock_005B5E90* block, int size, int flag);
    // FUNCTION: GAMEMD 0x5F1BF0 (decl; reloc) -- the chat request of 0x5B6DA0 goes through the same entry.
    void FUN_005F1BF0(struct WolChatRequest_005B6DA0* block, int size, int flag);
    // FUNCTION: GAMEMD 0x5F1C60 (decl; reloc)
    void FUN_005F1C60();
    // FUNCTION: GAMEMD 0x5F1BF0 (decl; reloc)
    void FUN_005F1BF0(struct WolRequest_005B6CD0* block, int size, int flag);
    void FUN_005F1BF0(struct WolRequest_005B5EF0* block, int size, int flag);
    // FUNCTION: GAMEMD 0x5F1EE0 (decl; reloc)
    int FUN_005F1EE0();
    // FUNCTION: GAMEMD 0x5F1EA0 (decl; reloc)
    int FUN_005F1EA0();
    // FUNCTION: GAMEMD 0x5F1C30 (decl; reloc)
    int FUN_005F1C30(void* buffer, int* length);
    void FUN_005F1BF0(struct WolRequest_005B6F30* block, int size, int flag);
};
// GLOBAL: GAMEMD 0xA8EA70
extern WolRequestQueue_00A8EA70 DAT_00A8EA70;


// The status request 0x5B6CD0 sends: code 0x65 with the handle, colour and the dialog's three
// values. Packed because retail stores a dword at +0x19.
#pragma pack(push, 1)
struct WolRequest_005B6CD0 {
    int Code;                // +0x00
    char Handle[20];         // +0x04
    char unknown_18;         // +0x18
    int unknown_19;          // +0x19
    char Color;              // +0x1D
    unsigned int MinVersion; // +0x1E
    unsigned int MaxVersion; // +0x22
    char unknown_26[0x60];   // +0x26
    int unknown_86;          // +0x86
    char unknown_8A[0x46];   // +0x8A
    int unknown_D0;          // +0xD0
    int unknown_D4;          // +0xD4
    int unknown_D8;          // +0xD8
    char unknown_DC[0x1E];   // +0xDC
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(WolRequest_005B6CD0, unknown_19) == 0x19);
GG_STATIC_ASSERT(offsetof(WolRequest_005B6CD0, MinVersion) == 0x1E);
GG_STATIC_ASSERT(offsetof(WolRequest_005B6CD0, unknown_86) == 0x86);
GG_STATIC_ASSERT(offsetof(WolRequest_005B6CD0, unknown_D8) == 0xD8);
GG_STATIC_ASSERT(sizeof(WolRequest_005B6CD0) == 0xFA);
// The keep-alive request 0x5B5EF0 sends: code 0x69, a byte at +0x18 and a dword at +0x9A.
#pragma pack(push, 1)
struct WolRequest_005B5EF0 {
    int Code;                // +0x00
    char unknown_04[0x14];   // +0x04
    char unknown_18;         // +0x18
    char unknown_19[0x81];   // +0x19
    int unknown_9A;          // +0x9A
    char unknown_9E[0x5C];   // +0x9E
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(WolRequest_005B5EF0, unknown_9A) == 0x9A);
GG_STATIC_ASSERT(sizeof(WolRequest_005B5EF0) == 0xFA);
// The sign-off request 0x5B6F30 sends: code 0x66, the byte at +0x18 and the colour at +0x1D.
#pragma pack(push, 1)
struct WolRequest_005B6F30 {
    int Code;                // +0x00
    char unknown_04[0x14];   // +0x04
    char unknown_18;         // +0x18
    char unknown_19[4];      // +0x19
    char Color;              // +0x1D
    char unknown_1E[0xDC];   // +0x1E
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(WolRequest_005B6F30, Color) == 0x1D);
GG_STATIC_ASSERT(sizeof(WolRequest_005B6F30) == 0xFA);
// The reply 0x5B6F30 reads back: code at +0, the acknowledged byte in the dword at +0x18.
struct WolReply_005B6F30 {
    int Code;                // +0x00
    char unknown_04[0x14];   // +0x04
    int Value;               // +0x18
    char unknown_1C[0xE0];   // +0x1C
};
GG_STATIC_ASSERT(sizeof(WolReply_005B6F30) == 0xFC);
// GLOBAL: GAMEMD 0xA8DB30
extern int DAT_00A8DB30;
// GLOBAL: GAMEMD 0xA8ECE0 -- the network-protocol version record.
extern VersionClass DAT_00A8ECE0;
// FUNCTION: GAMEMD 0x777B50 (decl; reloc)
int FUN_00777B50();


// The 250-byte request 0x5B6DA0 sends: code 0x68, the local handle copied in as ANSI, a colour
// byte and then the message as wide text starting at the odd offset +0x19 (hence the packing).
#pragma pack(push, 1)
struct WolChatRequest_005B6DA0 {
    int Code;               // +0x00
    char Handle[20];        // +0x04
    char Color;             // +0x18
    wchar_t Text[112];      // +0x19
    char unknown_F9;        // +0xF9
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(WolChatRequest_005B6DA0, Color) == 0x18);
GG_STATIC_ASSERT(offsetof(WolChatRequest_005B6DA0, Text) == 0x19);
GG_STATIC_ASSERT(sizeof(WolChatRequest_005B6DA0) == 0xFA);

#endif  // GG_MATCH_UI_WOL_REQUEST_QUEUE_H
