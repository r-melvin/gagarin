// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA | compiler-abi-binding
// Engine runtime override: retail's shared pure-slot target 0x4C9150 is
// XOR EAX,EAX / RET. The VC6 LIBCMT default instead calls its error path.
// The compiler-facing name comes from VC6's generated pure-slot relocation;
// no original source filename or source identifier is recovered here.
// FileClass table 0x7F08BC uses this target in slots 1..13 and 16.
// This preserves the engine override, not Microsoft runtime source.

// FUNCTION: GAMEMD 0x4C9150
extern "C" int __cdecl _purecall()
{
    return 0;
}
