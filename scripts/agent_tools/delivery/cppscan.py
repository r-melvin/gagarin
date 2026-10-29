#!/usr/bin/env python3
# Provenance: original. Small C++ text scanners shared by the lint rules (no compiler).
"""cppscan.py: comment/string stripping and top-level function-body discovery.

strip_code(text)       text with comments and string/char literals blanked (newlines and offsets kept)
function_bodies(text)  [(header, body, first_line, last_line)] for every brace body whose header ends in ')'
                       (optionally const/throw/initialiser list), descending into class/struct/namespace/extern "C"
                       blocks. Lines are 1-based. Header and body come from the stripped text.
"""
import re


def strip_code(text):
    out = []
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if text.startswith("//", i):
            j = text.find("\n", i)
            j = n if j < 0 else j
            out.append(" " * (j - i))
            i = j
        elif text.startswith("/*", i):
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append(re.sub(r"[^\n]", " ", text[i:j]))
            i = j
        elif c in "\"'":
            j = i + 1
            while j < n and text[j] != c and text[j] != "\n":
                j += 2 if text[j] == "\\" else 1
            j = min(j + 1, n)
            out.append(c + " " * (j - i - 2) + c if j - i >= 2 else c)
            i = j
        else:
            out.append(c)
            i += 1
    return "".join(out)


_BLOCK = re.compile(r"\b(class|struct|union|namespace|enum)\b|extern\s*\"")


def function_bodies(text):
    s = strip_code(text)
    res = []
    stack = []          # (is_function, header, start_index)
    last = 0            # index after the previous top-of-scope ; { or }
    for i, c in enumerate(s):
        if c == "{":
            header = s[last:i]
            if not stack or not stack[-1][0]:
                is_fn = bool(re.search(r"\)\s*(const\s*)?(throw\s*\([^)]*\)\s*)?(:[^{;]*)?$", header.strip()) or
                             re.search(r"\)\s*(const\s*)?$", header.strip())) and not _BLOCK.search(header.split("(")[0])
            else:
                is_fn = True        # nested braces inside a function body
            stack.append((is_fn, header, i))
            last = i + 1
        elif c == "}":
            if stack:
                is_fn, header, start = stack.pop()
                if is_fn and not any(f for f, _, _ in stack):
                    res.append((header.strip(), s[start + 1:i], s.count("\n", 0, start) + 1, s.count("\n", 0, i) + 1))
            last = i + 1
        elif c == ";" and (not stack or not stack[-1][0]):
            last = i + 1
    return res
