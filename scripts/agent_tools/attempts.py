#!/usr/bin/env python3
# Provenance: original.
"""attempts.py — searchable ledger of match attempts (JSONL).

Ledger: $GAG_WORKTREE/state/orchestration/attempts.jsonl (override: --ledger).

Usage:
  attempts.py add ADDR --tu match/x.cpp --variant "swap loads" --raw 99.0
                [--flags "/O2 ..."] [--positional P] [--multiset M]
                [--delta "ecx vs eax in memmove arg"] [--agent claude] [--src FILE]
  attempts.py show ADDR          every attempt at ADDR, oldest first
  attempts.py check ADDR [--src FILE]
                                 would `add` be accepted? exit 3 + reason when it would be refused
  attempts.py defer ADDR --reason TEXT
                                 record "deferred" (a valid outcome, not a failure) and close the address

Refusal rules (Thief3-Decomp try.py), applied by `add` and `check` to the attempts recorded at ADDR
(imported rows only feed the best score): at most 12 attempts; no more after 4 in a row without a
new best score; a source file (sha256) identical to an earlier attempt is refused; a deferred
address is refused until `add --reopen`. `add --force` skips the checks (say why in --variant).
A refusal means defer: `attempts.py defer ADDR --reason ...`.
  attempts.py search TEXT        case-insensitive substring over all fields
  attempts.py best ADDR          the highest raw score recorded for ADDR
  attempts.py import             seed from cap comments in match/**/*.cpp and
                                 $GAG_ATTEMPT_REPORTS/**/report.md; imported rows
                                 are marked "imported, unverified". Re-running skips
                                 rows already imported (same addr+source+line).

--src FILE hashes the source file (sha256) so a later reader knows which text
produced the score. Scores are percentages as the match tools print them.
"""
import argparse
import datetime
import hashlib
import json
import os
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common  # noqa: E402

LEDGER = common.STATE / "attempts.jsonl"
FUNC = re.compile(r"//\s*(?:FUNCTION|SYNTHETIC|TEMPLATE|STUB):\s*GAMEMD\s+(0x[0-9A-Fa-f]+)")
CAP = re.compile(r"(CAPPED at|RESIDUAL|PARTIAL|[Bb]est (?:form kept|measured)[^0-9]{0,20}|best[^0-9\n]{0,30}at)\s*:?\s*([0-9]+(?:\.[0-9]+)?)%")
MD_ROW = re.compile(r"^\|\s*(0x[0-9A-Fa-f]+)\s*\|([^|]*)\|([^|]*)\|\s*([0-9.]+)%([^|]*)\|")


def load(path):
    if not path.exists():
        return []
    return [json.loads(l) for l in path.read_text().splitlines() if l.strip()]


def append(path, rows):
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("a") as f:
        for r in rows:
            f.write(json.dumps(r, sort_keys=True) + "\n")


def norm(addr):
    return f"0x{int(addr, 16):X}"


def fmt(r):
    s = [f"{r['addr']} raw={r.get('raw')}"]
    for k in ("positional", "multiset"):
        if r.get(k) is not None:
            s.append(f"{k[:3]}={r[k]}")
    s.append(f"{r.get('date', '?')} {r.get('agent', '?')} [{r.get('status', 'recorded')}]")
    s.append(f"\n    tu={r.get('tu')} flags={r.get('flags') or '-'} sha={str(r.get('source_sha') or '-')[:12]}")
    s.append(f"\n    variant: {r.get('variant')}")
    if r.get("delta"):
        s.append(f"\n    delta: {r['delta']}")
    return " ".join(s)


MAX_ATTEMPTS = 12
PATIENCE = 4


def refusal(rows, addr, sha=None, reopen=False):
    """Why a new attempt at addr must not be run/recorded, or None."""
    rs = for_addr(rows, addr)
    attempts = [r for r in rs if r.get("status") != "deferred"]
    recorded = [r for r in attempts if r.get("status") == "recorded"]
    if not reopen and rs and rs[-1].get("status") == "deferred":
        return "deferred on %s (%s)" % (rs[-1].get("date"), rs[-1].get("delta") or rs[-1].get("variant"))
    if sha:
        for r in recorded:
            if r.get("source_sha") == sha:
                return "source is byte-identical to the attempt of %s (%s)" % (r.get("date"), r.get("variant"))
    if len(recorded) >= MAX_ATTEMPTS:
        return "%d attempts recorded (cap %d)" % (len(recorded), MAX_ATTEMPTS)
    top, streak = None, 0
    for r in attempts:
        raw = r.get("raw")
        if raw is not None and (top is None or raw > top):
            top, streak = raw, 0
        elif r.get("status") == "recorded":
            streak += 1
    if streak >= PATIENCE:
        return "%d attempts in a row without a new best (patience %d, best %s)" % (streak, PATIENCE, top)
    return None


def row_addr(r):
    """The row's address, or None for a hand-written ledger row without a single hex address."""
    try:
        return int(r.get("addr", ""), 16)
    except (TypeError, ValueError):
        return None


def tried_addrs(rows):
    """Addresses with any ledger row, including a defer."""
    return {a for a in map(row_addr, rows) if a is not None}


def for_addr(rows, addr):
    a = int(addr, 16)
    return [r for r in rows if row_addr(r) == a]


def best(rows, addr):
    rs = [r for r in for_addr(rows, addr) if r.get("raw") is not None]
    return max(rs, key=lambda r: r["raw"]) if rs else None


def tu_flags(path):
    try:
        for line in Path(path).read_text(errors="replace").splitlines()[:60]:
            m = re.match(r"\s*//\s*VC6FLAGS:\s*(.*)", line)
            if m:
                return m.group(1).strip()
    except OSError:
        pass
    return None


def import_rows(existing):
    seen = {(r.get("addr"), r.get("import_source")) for r in existing}
    out = []
    root = common.WORKTREE
    for p in sorted(q for q in (root / "match").rglob("*") if q.suffix.lower() == ".cpp"):
        lines = p.read_text(errors="replace").splitlines()
        rel = str(p.relative_to(root))
        flags = tu_flags(p)
        sha = hashlib.sha256(p.read_bytes()).hexdigest()
        for i, line in enumerate(lines):
            m = CAP.search(line)
            if not m or not line.lstrip().startswith("//"):
                continue
            # attribute to the next FUNCTION annotation at/after the comment
            # (cap comments sit in the block above the function), else previous.
            addr = None
            for j in range(i, min(i + 80, len(lines))):
                f = FUNC.search(lines[j])
                if f:
                    addr = f.group(1)
                    break
            if addr is None:
                for j in range(i, -1, -1):
                    f = FUNC.search(lines[j])
                    if f:
                        addr = f.group(1)
                        break
            if addr is None:
                continue
            # the comment block around the hit is the delta text
            k = i
            block = []
            while k < len(lines) and lines[k].lstrip().startswith("//") and len(block) < 6:
                block.append(lines[k].lstrip()[2:].strip())
                k += 1
            src = f"{rel}:{i + 1}"
            key = (norm(addr), src)
            if key in seen:
                continue
            seen.add(key)
            out.append(dict(addr=norm(addr), tu=rel, flags=flags, source_sha=sha,
                            variant="best form recorded in source comment", raw=float(m.group(2)),
                            positional=None, multiset=None, delta=" ".join(block)[:600],
                            agent="unknown", date=None, status="imported, unverified",
                            import_source=src))
    for p in (sorted(Path(os.environ["GAG_ATTEMPT_REPORTS"]).rglob("report.md")) if os.environ.get("GAG_ATTEMPT_REPORTS") else []):
        if "extern_eval" in p.parts:
            continue
        text = p.read_text(errors="replace")
        flags = None
        fm = re.search(r"VC6FLAGS:\s*([^\n(]*)", text)
        if fm:
            flags = fm.group(1).strip()
        tum = re.search(r"(match/\S+\.(?:cpp|CPP|Cpp))", text)
        for i, line in enumerate(text.splitlines()):
            m = MD_ROW.match(line)
            if not m:
                continue
            src = f"{p}:{i + 1}"
            key = (norm(m.group(1)), src)
            if key in seen:
                continue
            seen.add(key)
            out.append(dict(addr=norm(m.group(1)), tu=tum.group(1) if tum else None, flags=flags,
                            source_sha=None, variant=f"report row: {m.group(2).strip()}",
                            raw=float(m.group(4)), positional=None, multiset=None,
                            delta=(m.group(5).strip() or None), agent="claude (report)",
                            date=datetime.date.fromtimestamp(p.stat().st_mtime).isoformat(),
                            status="imported, unverified", import_source=src))
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--ledger", type=Path, default=LEDGER)
    sub = ap.add_subparsers(dest="cmd", required=True)
    a = sub.add_parser("add")
    a.add_argument("addr")
    a.add_argument("--tu", required=True)
    a.add_argument("--variant", required=True)
    a.add_argument("--raw", type=float, required=True)
    a.add_argument("--positional", type=float)
    a.add_argument("--multiset", type=float)
    a.add_argument("--flags")
    a.add_argument("--delta")
    a.add_argument("--agent", default="unknown")
    a.add_argument("--src", help="source file to hash (default: --tu under the worktree)")
    for c in ("show", "best"):
        sub.add_parser(c).add_argument("addr")
    sub.add_parser("search").add_argument("text")
    sub.add_parser("import")
    c = sub.add_parser("check")
    c.add_argument("addr")
    c.add_argument("--src", type=Path)
    c.add_argument("--reopen", action="store_true")
    d = sub.add_parser("defer")
    d.add_argument("addr")
    d.add_argument("--reason", required=True)
    d.add_argument("--tu")
    d.add_argument("--agent", default="unknown")
    a.add_argument("--force", action="store_true", help="skip the refusal rules")
    a.add_argument("--reopen", action="store_true", help="allow an attempt at a deferred address")
    args = ap.parse_args(argv)
    rows = load(args.ledger)

    if args.cmd == "add":
        src = Path(args.src) if args.src else common.WORKTREE / args.tu
        sha = hashlib.sha256(src.read_bytes()).hexdigest() if src.exists() else None
        why = None if args.force else refusal(rows, args.addr, sha, args.reopen)
        if why:
            print("refused %s: %s\ndefer instead: attempts.py defer %s --reason TEXT" % (norm(args.addr), why, norm(args.addr)))
            return 3
        r = dict(addr=norm(args.addr), tu=args.tu, flags=args.flags or tu_flags(src), source_sha=sha,
                 variant=args.variant, raw=args.raw, positional=args.positional, multiset=args.multiset,
                 delta=args.delta, agent=args.agent, date=datetime.date.today().isoformat(),
                 status="recorded")
        append(args.ledger, [r])
        print(fmt(r))
    elif args.cmd == "check":
        sha = hashlib.sha256(args.src.read_bytes()).hexdigest() if args.src and args.src.exists() else None
        why = refusal(rows, args.addr, sha, args.reopen)
        print("refused %s: %s\ndefer instead: attempts.py defer %s --reason TEXT" % (norm(args.addr), why, norm(args.addr))
              if why else "ok %s" % norm(args.addr))
        return 3 if why else 0
    elif args.cmd == "defer":
        r = dict(addr=norm(args.addr), tu=args.tu, flags=None, source_sha=None, variant="deferred", raw=None,
                 positional=None, multiset=None, delta=args.reason, agent=args.agent,
                 date=datetime.date.today().isoformat(), status="deferred")
        append(args.ledger, [r])
        print(fmt(r))
    elif args.cmd == "show":
        rs = for_addr(rows, args.addr)
        for r in rs:
            print(fmt(r))
        if not rs:
            print(f"no attempts recorded for {norm(args.addr)}")
            return 1
    elif args.cmd == "best":
        r = best(rows, args.addr)
        if not r:
            print(f"no attempts recorded for {norm(args.addr)}")
            return 1
        print(fmt(r))
    elif args.cmd == "search":
        t = args.text.lower()
        hits = [r for r in rows if t in json.dumps(r).lower()]
        for r in hits:
            print(fmt(r))
        print(f"{len(hits)} match(es)")
    elif args.cmd == "import":
        new = import_rows(rows)
        append(args.ledger, new)
        print(f"imported {len(new)} row(s) into {args.ledger} ({len(rows) + len(new)} total)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
