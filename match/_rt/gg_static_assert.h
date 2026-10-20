// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: original
//
// Compile-time-assert + 32-bit-ABI guard for the matching-decomp tree.
//
// The matching target is the 32-bit MSVC 6.0 ABI (4-byte pointers). MSVC6 has
// no C++11 `static_assert`, so layout/vtable asserts use the negative-array
// typedef idiom, which VC6 accepts.
//
// Struct-layout offsets are inherently 32-bit-ABI-specific: under a 64-bit
// compiler (e.g. a clangd IDE index), pointer members are 8 bytes and every
// downstream `offsetof` shifts, so the asserts would *falsely* fail there.
// GG_STATIC_ASSERT therefore self-guards: it is the real negative-array check
// only when GG_TARGET_ABI_32 (the VC6 build, the binding oracle), and a benign
// no-op everywhere else. Callers can use it unconditionally; no per-site
// `#if GG_TARGET_ABI_32` wrapping is needed.
#ifndef GG_MATCH_RT_STATIC_ASSERT_H
#define GG_MATCH_RT_STATIC_ASSERT_H

#define GG_SA_CAT_(a, b) a##b
#define GG_SA_CAT(a, b) GG_SA_CAT_(a, b)

#if defined(_M_IX86) || defined(__i386__) || \
    (defined(__SIZEOF_POINTER__) && __SIZEOF_POINTER__ == 4)
#  define GG_TARGET_ABI_32 1
#else
#  define GG_TARGET_ABI_32 0
#endif

#if GG_TARGET_ABI_32
// Fails to compile (negative array bound) when `cond` is false.
#  define GG_STATIC_ASSERT(cond) \
       typedef char GG_SA_CAT(gg_static_assert_, __LINE__)[(cond) ? 1 : -1]
#else
// 64-bit IDE/tooling: offsets are arch-dependent and unverifiable here; the
// binding layout check runs under the 32-bit VC6 build. No-op to avoid false
// failures while keeping the assert lines valid C++.
#  define GG_STATIC_ASSERT(cond) \
       typedef char GG_SA_CAT(gg_static_assert_, __LINE__)[1]
#endif

#endif  // GG_MATCH_RT_STATIC_ASSERT_H
