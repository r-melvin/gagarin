// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Statically linked library code in retail gamemd.exe v1.001 that has no
//   reconstructed source in this tree. Source recovery of these functions is
//   out of scope (AGENTS.md); their bytes still belong to the final image.
//   Each marker is followed by the library symbol name, in the by-name form
//   reccmp reads for LIBRARY markers. Evidence per group:
//
//   LZO1X-1 (third-party compression library, GPL v2 or later), the three
//   functions at 0x55BB90-0x55C2A9, called by the LZOPipe/LZOStraw members
//   0x55C350 and 0x55C5E0. The compressor 0x55BB90 and its static helper
//   0x55BC00 are byte-identical (raw match 100%) to LZO 1.00 lzo1x_1.c built
//   by VC6 at /O2 /Gr with signed match offsets. The decompressor 0x55C0E0 is
//   classified on structural evidence only: it sits in the same contiguous
//   library block and is the LZO1X decoder (same opcode classes, distances
//   and end marker), but no available LZO release reproduces its bytes
//   (best normalised-instruction similarity 0.80 against 1.00).
//
//   COMSUPP.LIB (the VC6 compiler COM support library), 11 functions at
//   0x7DC720-0x7DCE60: each body is a unique relocation-wildcarded match of
//   the comsupp.obj or comraise.obj member at that address.
//
//   LIBCMT strchr fragment at 0x7CAF20: a unique relocation-wildcarded match
//   of the 16-byte `found_bx` block of the debug CRT's strchr.obj, which
//   splits the assembler strchr at that label.
//
//   Linker import thunks at 0x7DCE62-0x7DCFC3: 59 six-byte
//   `JMP dword ptr [__imp_X]` stubs (53 KERNEL32, 6 OLEAUT32 by ordinal),
//   each resolved through the retail import address table. They come from
//   the import libraries and have no source.
#ifndef GG_MATCH_RT_LIBRARY_FUNCTIONS_H
#define GG_MATCH_RT_LIBRARY_FUNCTIONS_H

// LZO1X-1 (LZO 1.00 lineage).
// LIBRARY: GAMEMD 0x55bb90
// lzo1x_1_compress

// LIBRARY: GAMEMD 0x55bc00
// do_compress

// Structural classification only; not byte-matched (see above).
// LIBRARY: GAMEMD 0x55c0e0
// lzo1x_decompress

// CRT strchr fragment.
// LIBRARY: GAMEMD 0x7caf20
// _strchr

// COMSUPP.LIB, comsupp.obj.
// LIBRARY: GAMEMD 0x7dc720
// ?_com_issue_error@@YGXJ@Z

// LIBRARY: GAMEMD 0x7dc72e
// ?_com_issue_errorex@@YGXJPAUIUnknown@@ABU_GUID@@@Z

// LIBRARY: GAMEMD 0x7dc78f
// ?_com_dispatch_raw_method@@YAJPAUIDispatch@@JGGPAXPBGZZ

// LIBRARY: GAMEMD 0x7dc7cb
// ?_com_invoke_helper@@YAJPAUIDispatch@@JGGPAXPBGPADPAPAUIErrorInfo@@@Z

// LIBRARY: GAMEMD 0x7dcc74
// ?_com_dispatch_method@@YAJPAUIDispatch@@JGGPAXPBGZZ

// LIBRARY: GAMEMD 0x7dccec
// ?_com_dispatch_raw_propput@@YAJPAUIDispatch@@JGZZ

// LIBRARY: GAMEMD 0x7dcd45
// ?_com_dispatch_propput@@YAJPAUIDispatch@@JGZZ

// COMSUPP.LIB, comraise.obj.
// LIBRARY: GAMEMD 0x7dcd9c
// ?_com_raise_error@@YGXJPAUIErrorInfo@@@Z

// LIBRARY: GAMEMD 0x7dcdc0
// ??0_com_error@@QAE@JPAUIErrorInfo@@_N@Z

// LIBRARY: GAMEMD 0x7dce0e
// ??0_com_error@@QAE@ABV0@@Z

// LIBRARY: GAMEMD 0x7dce3b
// ??1_com_error@@UAE@XZ

// Linker import thunks (JMP through the import address table).
// LIBRARY: GAMEMD 0x7dce62
// KERNEL32!HeapFree

// LIBRARY: GAMEMD 0x7dce68
// KERNEL32!HeapAlloc

// LIBRARY: GAMEMD 0x7dce6e
// KERNEL32!GetTimeZoneInformation

// LIBRARY: GAMEMD 0x7dce74
// KERNEL32!GetLocalTime

// LIBRARY: GAMEMD 0x7dce7a
// KERNEL32!RtlUnwind

// LIBRARY: GAMEMD 0x7dce80
// KERNEL32!GetCommandLineA

// LIBRARY: GAMEMD 0x7dce86
// KERNEL32!GetVersion

// LIBRARY: GAMEMD 0x7dce8c
// KERNEL32!FatalAppExitA

// LIBRARY: GAMEMD 0x7dce92
// KERNEL32!HeapCreate

// LIBRARY: GAMEMD 0x7dce98
// KERNEL32!VirtualFree

// LIBRARY: GAMEMD 0x7dce9e
// KERNEL32!VirtualAlloc

// LIBRARY: GAMEMD 0x7dcea4
// KERNEL32!HeapReAlloc

// LIBRARY: GAMEMD 0x7dceaa
// KERNEL32!IsBadWritePtr

// LIBRARY: GAMEMD 0x7dceb0
// KERNEL32!HeapSize

// LIBRARY: GAMEMD 0x7dceb6
// KERNEL32!LCMapStringA

// LIBRARY: GAMEMD 0x7dcebc
// KERNEL32!LCMapStringW

// LIBRARY: GAMEMD 0x7dcec2
// KERNEL32!TlsSetValue

// LIBRARY: GAMEMD 0x7dcec8
// KERNEL32!TlsAlloc

// LIBRARY: GAMEMD 0x7dcece
// KERNEL32!TlsFree

// LIBRARY: GAMEMD 0x7dced4
// KERNEL32!SetLastError

// LIBRARY: GAMEMD 0x7dceda
// KERNEL32!TlsGetValue

// LIBRARY: GAMEMD 0x7dcee0
// KERNEL32!GetCurrentThread

// LIBRARY: GAMEMD 0x7dcee6
// KERNEL32!RaiseException

// LIBRARY: GAMEMD 0x7dceec
// KERNEL32!FlushFileBuffers

// LIBRARY: GAMEMD 0x7dcef2
// KERNEL32!SetHandleCount

// LIBRARY: GAMEMD 0x7dcef8
// KERNEL32!GetStdHandle

// LIBRARY: GAMEMD 0x7dcefe
// KERNEL32!GetFileType

// LIBRARY: GAMEMD 0x7dcf04
// KERNEL32!GetCPInfo

// LIBRARY: GAMEMD 0x7dcf0a
// KERNEL32!GetACP

// LIBRARY: GAMEMD 0x7dcf10
// KERNEL32!GetOEMCP

// LIBRARY: GAMEMD 0x7dcf16
// KERNEL32!SetConsoleCtrlHandler

// LIBRARY: GAMEMD 0x7dcf1c
// KERNEL32!GetFileAttributesA

// LIBRARY: GAMEMD 0x7dcf22
// KERNEL32!GetCurrentProcessId

// LIBRARY: GAMEMD 0x7dcf28
// KERNEL32!UnhandledExceptionFilter

// LIBRARY: GAMEMD 0x7dcf2e
// KERNEL32!FreeEnvironmentStringsA

// LIBRARY: GAMEMD 0x7dcf34
// KERNEL32!FreeEnvironmentStringsW

// LIBRARY: GAMEMD 0x7dcf3a
// KERNEL32!GetEnvironmentStrings

// LIBRARY: GAMEMD 0x7dcf40
// KERNEL32!GetEnvironmentStringsW

// LIBRARY: GAMEMD 0x7dcf46
// KERNEL32!IsValidLocale

// LIBRARY: GAMEMD 0x7dcf4c
// KERNEL32!IsValidCodePage

// LIBRARY: GAMEMD 0x7dcf52
// KERNEL32!GetLocaleInfoA

// LIBRARY: GAMEMD 0x7dcf58
// KERNEL32!EnumSystemLocalesA

// LIBRARY: GAMEMD 0x7dcf5e
// KERNEL32!GetUserDefaultLCID

// LIBRARY: GAMEMD 0x7dcf64
// KERNEL32!SetStdHandle

// LIBRARY: GAMEMD 0x7dcf6a
// KERNEL32!GetStringTypeA

// LIBRARY: GAMEMD 0x7dcf70
// KERNEL32!GetStringTypeW

// LIBRARY: GAMEMD 0x7dcf76
// KERNEL32!CompareStringA

// LIBRARY: GAMEMD 0x7dcf7c
// KERNEL32!CompareStringW

// LIBRARY: GAMEMD 0x7dcf82
// KERNEL32!SetEnvironmentVariableA

// LIBRARY: GAMEMD 0x7dcf88
// KERNEL32!SetEndOfFile

// LIBRARY: GAMEMD 0x7dcf8e
// KERNEL32!GetLocaleInfoW

// LIBRARY: GAMEMD 0x7dcf94
// KERNEL32!lstrlenW

// LIBRARY: GAMEMD 0x7dcf9a
// KERNEL32!LocalFree

// LIBRARY: GAMEMD 0x7dcfa0
// OLEAUT32!ordinal 200

// LIBRARY: GAMEMD 0x7dcfa6
// OLEAUT32!ordinal 201

// LIBRARY: GAMEMD 0x7dcfac
// OLEAUT32!ordinal 12

// LIBRARY: GAMEMD 0x7dcfb2
// OLEAUT32!ordinal 202

// LIBRARY: GAMEMD 0x7dcfb8
// OLEAUT32!ordinal 9

// LIBRARY: GAMEMD 0x7dcfbe
// OLEAUT32!ordinal 8

#endif  // GG_MATCH_RT_LIBRARY_FUNCTIONS_H
