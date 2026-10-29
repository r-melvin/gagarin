#!/usr/bin/env python3
"""cache_tool.py stats | gc [--days N] | clear   (object cache used by gates.py)

The cache is content-addressed: obj/<aa>/<key>.obj where key = sha256 of the compiler id,
vc6cl.sh, VC6_FLAGS, the TU path, its VC6FLAGS marker and the content of every file in its
include closure. Nothing in it can go stale (a changed input is a different key); it only
grows. `gc` removes entries not read or written for N days (default 14).
"""
import os
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import landlib as L  # noqa: E402


def walk():
    for root, _, names in os.walk(L.CACHE):
        for n in names:
            p = os.path.join(root, n)
            yield p, os.stat(p)


def main():
    cmd = sys.argv[1] if len(sys.argv) > 1 else "stats"
    if cmd == "stats":
        n = sz = 0
        for _, st in walk():
            n += 1
            sz += st.st_size
        print("%s: %d files, %.1f MB" % (L.CACHE, n, sz / 1e6))
    elif cmd == "gc":
        days = float(sys.argv[sys.argv.index("--days") + 1]) if "--days" in sys.argv else 14
        cut = time.time() - days * 86400
        n = sz = 0
        for p, st in walk():
            if max(st.st_atime, st.st_mtime) < cut:
                os.unlink(p)
                n += 1
                sz += st.st_size
        print("removed %d files, %.1f MB" % (n, sz / 1e6))
    elif cmd == "clear":
        import shutil
        shutil.rmtree(L.CACHE, ignore_errors=True)
        print("cleared", L.CACHE)
    else:
        print(__doc__)
        return 2


if __name__ == "__main__":
    sys.exit(main())
