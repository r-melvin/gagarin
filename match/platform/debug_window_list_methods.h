// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every fact below is read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x53E3C0 / 0x53E420. No YRpp
//   binding exists for this pair, so the retail placeholder names are kept.
//
// The debug-window registry — a small fixed-capacity open-addressed table of
// window handles that the 0x53Exxx logging module echoes output to.
//
// Naming: YRpp does not bind these two addresses,
// so they keep their Ghidra placeholder names per the project's naming rule.
// What they do is unambiguous from the bytes and the call sites: 0x53E3C0 adds
// a handle to the table if it is not already present, 0x53E420 clears it out
// again, and both are inert while the module is switched off.
//
// What the table holds is settled by the call sites, all of which hand over a
// USER32 window handle:
//   0x4C8445  a DialogProc calls ShowWindow(h, 1) on the value, then registers it
//   0x60FA08  an EnumWindows-style callback calls GetClientRect(h, &rc) on it
//   0x618431  the value is registered twice, then passed to SendMessageA
// 0x53E420 was previously read as an audio-streamer handle release and
// committed as `Streamer_ReleaseHandle`; the USER32 evidence above rules that
// out. Nothing in this cluster touches audio — the neighbouring code at
// 0x53E4F0 opens a log file under a critical section and formats IP and MAC
// addresses, so this is the network/debug logging module's window registry.
//
// Calling convention: both are reached as `MOV ECX,ESI; CALL <addr>` from a
// DialogProc (0x4C8445) with ESI holding an HWND, and both `RET` with no stack
// adjustment — one register argument, nothing on the stack. That is __fastcall.
// The handle is modelled as `void*` so this TU stays free of <windows.h>.
#ifndef GG_MATCH_PLATFORM_DEBUG_WINDOW_LIST_METHODS_H
#define GG_MATCH_PLATFORM_DEBUG_WINDOW_LIST_METHODS_H

// GLOBAL: GAMEMD 0x00AA0448 — module-active flag. Both entry points open by
// loading it (`MOV EAX,[0xAA0448]`) and fall straight through to the epilogue
// when it is zero, so nothing below runs until the logging module is armed.
extern int DebugWindowListActive;

// GLOBAL: GAMEMD 0x00AA0374 — table capacity, read as a signed int and compared
// against the walking index with `JLE`/`JL`.
extern int DebugWindowListCapacity;

// GLOBAL: GAMEMD 0x00AA044C — base of the handle table. Walked with `ADD EAX,4`,
// which pins the element size at one pointer.
extern void** DebugWindowList;

// GLOBAL: GAMEMD 0x00AA0450 — number of occupied slots. Bumped by the add path
// (`INC EAX` at 0x53E40B) and decremented by the remove path (`DEC EAX` at
// 0x53E45B); it is a running count, never a scan bound.
extern int DebugWindowListCount;

// Both walks start their index at 1 rather than 0 while the pointer starts at
// the table base, so the last slot is never examined. That is retail's own
// off-by-one, reproduced here deliberately — the loop guard is `i < capacity`
// with `i` pre-set to 1 (`MOV ESI,0x1` at 0x53E3DB, `MOV EDX,0x1` at 0x53E439).

// FUNCTION: GAMEMD 0x53E3C0
void __fastcall FUN_0053E3C0(void* window);

// FUNCTION: GAMEMD 0x53E420
void __fastcall FUN_0053E420(void* window);

#endif  // GG_MATCH_PLATFORM_DEBUG_WINDOW_LIST_METHODS_H
