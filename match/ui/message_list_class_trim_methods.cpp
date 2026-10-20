// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5D4B20.

#include "message_list_class_trim_methods.h"

// FUNCTION: GAMEMD 0x5D4B20
//
// Split the head off a wide string at a break character (any code below or
// equal to a space, but not the terminator), looking between minLen and
// maxLen characters in — forwards, or backwards from the far end when
// fromEnd is set. When no break is found the cut lands at minLen. The head
// is copied into dest (when given) and terminated, the remainder of src is
// shifted down over it, and the cut length is returned; a non-positive
// minLen does nothing and returns zero (`minLen <= 0` gives retail's
// `TEST/JG`; `< 1` gives `CMP,1/JGE`).
//
// The tail-move length written as `(len - cut + 1) * sizeof(wchar_t)` is
// what produces retail's odd `NEG; SHL 0x1F; SUB; ADD; LEA [EAX*2+2]` fold
// (cl multiplies the subtracted term by 0x7FFFFFFF before doubling); the head
// copy is the /Oi memcpy intrinsic (`REP MOVSD`/`REP MOVSB`).
int MessageList_005D4B20::TrimMessage(wchar_t* dest, wchar_t* src, int minLen,
                                      int maxLen, int fromEnd)
{
    int cut;

    if (minLen <= 0) {
        return 0;
    }

    int len = wcslen(src);
    if (maxLen > len) {
        maxLen = len;
    }

    if (fromEnd == 0) {
        for (cut = minLen; cut <= maxLen; cut++) {
            wchar_t c = src[cut - 1];
            if (c != 0 && c <= 0x20) {
                goto found;
            }
        }
        cut = minLen;
    } else {
        for (cut = maxLen; cut >= minLen; cut--) {
            wchar_t c = src[cut - 1];
            if (c != 0 && c <= 0x20) {
                goto found;
            }
        }
        cut = minLen;
    }

found:
    if (dest != 0) {
        memcpy(dest, src, cut * sizeof(wchar_t));
        dest[cut] = 0;
    }
    memmove(src, src + cut, (len - cut + 1) * sizeof(wchar_t));
    return cut;
}
