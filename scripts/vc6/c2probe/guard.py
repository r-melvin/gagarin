#!/usr/bin/env python3
"""guard.py - fail closed if anything from the c2probe shim driver reaches a packet or a land gate.

The shim is inert (its objects equal the real compiler's outside the COFF timestamp), so an
object cannot carry a stamp.  The guard therefore checks four independent things:

  env        the driver variables (C2PROBE_*) must not be set in the shell running a gate
  toolchain  the c2.dll in the real toolchain path must be the pinned 12.00.8447 image
  ledger     no .obj/.o in the scanned paths may hash like an object the driver produced
             (toolchain/c2probe/ledger.tsv, written by c2probe.py for every probe object)
  marker     no scanned text file (log, report, json/tsv manifest row, patch) may contain the
             driver's report marker or a path into toolchain/c2probe or build/c2probe

Used by delivery/pktlint.py (rule `c2probe`) and land/gates.py (gate `c2probe`); runnable alone:
  guard.py [--packet DIR] [--tree DIR --base REV]
"""
import argparse, hashlib, os, subprocess, sys
from pathlib import Path

PINNED_C2 = "a0cc45f83fd0ed009aa4f43df5598105a1049ad9675de0b1089be7cce7d3c153"
MARKER = "C2PROBE" + " DIAGNOSTIC-ONLY"
PATH_MARKS = ("toolchain/c2probe", "build/c2probe", "toolchain\\c2probe", "build\\c2probe", "C2PROBE_DRIVER")
SELF_DIR = "scripts/vc6/c2probe/"          # the tool itself may name its own marker
ENV_KEYS = ("C2PROBE_DRIVER", "C2PROBE_LOG", "C2PROBE_FILTER", "C2PROBE_INLINE_FORCE",
            "C2PROBE_REG_FORCE", "C2PROBE_MERGE_VETO")


def _repo():
    return Path(__file__).resolve().parents[3]


def _toolchain():
    return (_repo() / "toolchain").resolve()


def env_findings():
    return [f"env {k} is set: a shim-driver session must not run packet lint or land gates"
            for k in ENV_KEYS if os.environ.get(k)]


def toolchain_findings():
    c2 = _toolchain() / "MSVC600/VC98/Bin/c2.dll"
    if not c2.is_file():
        return []                       # no toolchain here (CI without one): nothing to check
    h = hashlib.sha256(c2.read_bytes()).hexdigest()
    if h != PINNED_C2:
        return [f"{c2} is not the pinned c2.dll (sha256 {h[:12]}...): a shim may be installed in the real toolchain path"]
    return []


def ledger_hashes():
    p = _toolchain() / "c2probe/ledger.tsv"
    if not p.is_file():
        return set()
    return {ln.split("\t", 1)[0] for ln in p.read_text().splitlines() if ln}


def scan_bytes(name, data, ledger):
    out = []
    if name.lower().endswith((".obj", ".o")):
        if hashlib.sha256(data).hexdigest() in ledger:
            out.append(f"{name}: object produced by the c2probe driver (ledger sha256 match)")
        return out
    text = data.decode("utf-8", "replace")
    if MARKER in text:
        out.append(f"{name}: contains the c2probe report marker")
    for m in PATH_MARKS:
        if m in text:
            out.append(f"{name}: names the c2probe toolchain/work path ({m!r})")
            break
    return out


def scan_dir(d):
    ledger = ledger_hashes()
    out = []
    for p in sorted(Path(d).rglob("*")):
        if p.is_file() and not p.is_symlink() and p.stat().st_size < 64 * 1024 * 1024:
            out += scan_bytes(str(p), p.read_bytes(), ledger)
    return out


def scan_diff(tree, base):
    """Added lines and changed object files between *base* and the working tree/index."""
    ledger = ledger_hashes()
    out = []
    names = subprocess.run(["git", "-C", tree, "diff", "--name-only", base, "--"], capture_output=True, text=True).stdout.split()
    for n in names:
        if n.startswith(SELF_DIR):
            continue
        p = Path(tree) / n
        if p.is_file() and not p.is_symlink():
            out += scan_bytes(n, p.read_bytes(), ledger)
    return out


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument("--packet")
    ap.add_argument("--tree")
    ap.add_argument("--base", default="HEAD")
    a = ap.parse_args(argv)
    f = env_findings() + toolchain_findings()
    if a.packet:
        f += scan_dir(a.packet)
    if a.tree:
        f += scan_diff(a.tree, a.base)
    for x in f:
        print("c2probe-guard FAIL:", x)
    print(f"c2probe-guard: {len(f)} finding(s)")
    return 1 if f else 0


if __name__ == "__main__":
    sys.exit(main())
