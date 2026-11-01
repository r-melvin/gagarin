#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original tooling; reads only the project's own attempt ledger and packet notes.
"""regmine.py: which source edit fixed, or failed to fix, which diff pattern?

    regmine.py [--ledger JSONL] [--ready-glob GLOB] [--out FILE] [--min-n 1]

Mines two sources for before/after pairs:
  * the attempts ledger (<state>/orchestration/attempts.jsonl): consecutive recorded attempts at one
    address give (score before, score after); the edit is classified from the later row's `variant`
    text, the diff pattern from the earlier row's `delta` text (what the edit was trying to fix);
  * held-packet notes `<scratch>/*/READY/README.md`: lines naming an address with a `A -> B` score pair
    (the packet's `## Change` paragraph classifies the edit, the line itself the diff pattern).
Output is a markdown rulebook of observed effects (counts, outcome split, examples) written under the
main checkout's untracked `.scratch/regmine/`. It states observations, not rules of the compiler: a
cell with n=1 is an anecdote. Text is path-scrubbed and any line matching the local forbidden-word
list is replaced by "[redacted]". Tests: python3 -m unittest test_regmine.
"""
import argparse
import collections
import glob
import json
import os
import re
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))

EDIT_CLASSES = [
    ("operand-order", r"commut|operand order|swap(?:ped)? operands|a \+ b|b \+ a|reverse(?:d)? operands|lhs.?rhs"),
    ("statement-order", r"\bswap|\breorder|statement order|order of (?:the )?(?:statements|stores|loads)|move[ds]? (?:the )?(?:store|load|call|statement)|hoist(?:ed)? the (?:store|load)"),
    ("declaration-order", r"declar\w* order|declare[sd]? .{0,30} (?:first|before)|declaration"),
    ("named-temporary", r"temp(?:orary)?\b|named local|local for|pull(?:ed)? .{0,20} into|\bint cap\b|cache[sd]? in a local"),
    ("inline-temp", r"inlin\w* (?:the )?(?:temp|local)|fold(?:ed)? .{0,20} into"),
    ("if-else-shape", r"if/else|else branch|early.?return|invert|polarity|\bif forms?\b|\bswitch\b"),
    ("loop-form", r"\bfor loop|while loop|do.?while|for \(|loop form"),
    ("expression-form", r"==|&&|\|\||ternary|!\(|negated|short.circuit|bitfield|\bmask forms?\b|bool(?:ean)? form"),
    ("type-width", r"cast|\bchar\b|unsigned|\bshort\b|width|signed"),
    ("flags", r"flags|/O[0-9a-z]|/Ob|/Og|/G[3-7]|/Op"),
    ("calling-convention", r"fastcall|thiscall|stdcall|calling conv"),
    ("structure-port", r"port of|goto|decompile|restructur|canonical"),
    ("helper-or-inline", r"helper|out.of.line|\binline\b|library"),
    ("data-layout", r"member|offset|layout|struct|vtable|header"),
]
PATTERN_CLASSES = [
    ("operand-swap", r"\b(?:add|and|or|xor|imul|cmp|test|mov)\s+(\w+),(\w+)\s+vs\s+\w+\s+\2,\1\b|\bcmp\b.{0,20}\bswap|operand order"),
    ("imm-vs-reg", r"0x[0-9a-f]+\s+vs\s+\w+|\bimm(?:ediate)? vs|test \w+,0xff"),
    ("register-allocation", r"\b[abcd]x\b.{0,12}\bvs\b|\be[sd]i\b.{0,12}\bvs\b|\bvs\b.{0,12}\be[a-d]x\b|reg(?:ister)? alloc|spill|ebx|esi|edi|colou?ring"),
    ("scheduling", r"schedul|multiset identical|transpos|reorder|order only"),
    ("stack-frame", r"frame|\besp\b|\bebp\b|stack slot|sub esp"),
    ("instruction-count", r"\d+\s*(?:vs|/)\s*\d+\s*insns?|extra insn|missing insn|insn count|\binsns\b"),
    ("branch-layout", r"\bj(?:n?e|[lg]e?|n?[sz])\b|polarity|branch|block layout|label"),
    ("call-vs-inline", r"inlin|call vs|out.of.line"),
    ("constant", r"constant|literal|\bimm\b|immediate"),
]
EDIT_RX = [(n, re.compile(p, re.I)) for n, p in EDIT_CLASSES]
PATTERN_RX = [(n, re.compile(p, re.I)) for n, p in PATTERN_CLASSES]
ADDR = re.compile(r"0x[0-9A-Fa-f]{5,6}\b")
ARROW = re.compile(r"(?<![\w.])(\d+(?:\.\d+)?)\s*%?\s*(?:->|→|=>|to)\s*(?:partial\s+|matched\s+)?(\d+(?:\.\d+)?)\s*%?")
PATHISH = re.compile(r"(?:~|/home|/tmp|\.\./)[^\s,;)]*|\S+/\S+\.(?:md|json|tsv|cpp|h)\b")


def classify(text, table):
    t = text or ""
    found = [n for n, rx in table if rx.search(t)]
    if "operand-swap" in found and "register-allocation" in found:
        found.remove("register-allocation")     # the swap already explains the differing registers
    return found or ["unclassified"]


def outcome(before, after):
    if after is None or before is None:
        return "unknown"
    if after >= 99.995:
        return "fixed"
    if after > before + 0.05:
        return "improved"
    if after < before - 0.05:
        return "regressed"
    return "no-change"


def load_forbidden(main):
    p = Path(os.environ.get("GAG_FORBIDDEN_WORDS") or Path(main) / ".coordination" / "forbidden_words.txt")
    out = []
    try:
        for line in p.read_text().splitlines():
            line = line.strip()
            if line and not line.startswith("#"):
                out.append(re.compile(line, re.I))
    except (OSError, re.error):
        pass
    return out


def scrub(text, forbidden=(), limit=150):
    """One short, path-free excerpt; nothing that matches the local forbidden list leaves this function."""
    t = PATHISH.sub("<path>", re.sub(r"\s+", " ", text or "").strip())
    if any(rx.search(t) for rx in forbidden):
        return "[redacted]"
    return t if len(t) <= limit else t[:limit - 1] + "…"


def ledger_pairs(rows):
    """Consecutive recorded attempts at one address -> observations."""
    by = collections.OrderedDict()
    for r in rows:
        if r.get("status") == "recorded" and r.get("raw") is not None:
            by.setdefault(int(r["addr"], 16), []).append(r)
    obs = []
    for addr, rs in by.items():
        for prev, cur in zip(rs, rs[1:]):
            pat_text = prev.get("delta") or cur.get("delta") or ""
            obs.append(dict(addr="0x%X" % addr, before=prev["raw"], after=cur["raw"], source="ledger",
                            edit=classify(cur.get("variant"), EDIT_RX),
                            pattern=classify(pat_text, PATTERN_RX), remaining=classify(cur.get("delta"), PATTERN_RX)
                            if cur.get("delta") else [], outcome=outcome(prev["raw"], cur["raw"]),
                            variant=cur.get("variant") or "", delta=pat_text, date=cur.get("date")))
    return obs


def readme_pairs(text, packet):
    """Lines of a packet README naming an address and an `A -> B` percentage pair."""
    m = re.search(r"^##\s+Change\s*\n(.*?)(?=^##\s|\Z)", text, re.S | re.M)
    change = m.group(1).strip() if m else ""
    edit = classify(change[:900], EDIT_RX)
    obs = []
    for line in text.splitlines():
        a, p = ADDR.search(line), ARROW.search(line)
        if not (a and p) or "matched 100" in line and "partial" not in line:
            continue
        try:
            before, after = float(p.group(1)), float(p.group(2))
        except ValueError:
            continue
        if not (0 <= before <= 100 and 0 <= after <= 100) or before >= 99.995:
            continue    # not a percentage pair, or a deliberate demotion from matched (no edit effect to learn)
        obs.append(dict(addr=a.group(0).upper().replace("0X", "0x"), before=before, after=after, source="packet:" + packet,
                        edit=edit, pattern=classify(line, PATTERN_RX), remaining=[], outcome=outcome(before, after),
                        variant=change[:200], delta=line.strip(), date=None))
    return obs


def mine(ledger_rows, readmes):
    obs = ledger_pairs(ledger_rows)
    for packet, text in readmes:
        obs += readme_pairs(text, packet)
    return obs


def rulebook(obs, forbidden=(), min_n=1):
    """Markdown rulebook: (diff pattern, edit class) -> outcome counts with examples."""
    cells = collections.defaultdict(list)
    for o in obs:
        for pat in o["pattern"]:
            for ed in o["edit"]:
                cells[(pat, ed)].append(o)

    def split(os_):
        c = collections.Counter(x["outcome"] for x in os_)
        return c

    lines = ["# regmine rulebook: observed effects of source edits on diff patterns", "",
             "%d before/after observations (%d from the ledger, %d from packet notes). A cell is an observation, not a rule: "
             "n=1 is an anecdote. Outcomes: fixed = 100%%, improved = score up, no-change, regressed." % (
                 len(obs), sum(1 for o in obs if o["source"] == "ledger"), sum(1 for o in obs if o["source"] != "ledger")),
             "", "Edit classes and diff patterns are keyword-classified from the free text workers wrote; "
             "`unclassified` means no keyword matched.", ""]
    tot = split(obs)
    lines += ["Overall: " + ", ".join("%s %d" % kv for kv in sorted(tot.items())), ""]

    def score(item):
        os_ = item[1]
        c = split(os_)
        return (-(3 * c["fixed"] + c["improved"]), -len(os_), item[0])

    unattributed = [o for o in obs if o["edit"] == ["unclassified"] and o["pattern"] == ["unclassified"]]
    cells = {k: v for k, v in cells.items() if k != ("unclassified", "unclassified")}
    ranked = [kv for kv in sorted(cells.items(), key=score) if len(kv[1]) >= min_n]
    helped = [kv for kv in ranked if split(kv[1])["fixed"] + split(kv[1])["improved"]]
    lines += ["## Top entries: edits that moved a score", "",
              "| diff pattern | source edit | n | fixed | improved | no-change | regressed | best example |",
              "|---|---|---|---|---|---|---|---|"]
    for (pat, ed), os_ in helped[:25]:
        c = split(os_)
        ex = max(os_, key=lambda x: (x["after"] or 0) - (x["before"] or 0))
        lines.append("| %s | %s | %d | %d | %d | %d | %d | %s %s→%s: %s |" % (
            pat, ed, len(os_), c["fixed"], c["improved"], c["no-change"], c["regressed"], ex["addr"], ex["before"], ex["after"],
            scrub(ex["variant"], forbidden, 90)))
    lines += ["", "## Edits that did not help (every observation no-change or regressed)", "",
              "| diff pattern | source edit | n | no-change | regressed | example |", "|---|---|---|---|---|---|"]
    for (pat, ed), os_ in [kv for kv in ranked if kv not in helped][:25]:
        c = split(os_)
        ex = os_[0]
        lines.append("| %s | %s | %d | %d | %d | %s %s→%s: %s |" % (
            pat, ed, len(os_), c["no-change"], c["regressed"], ex["addr"], ex["before"], ex["after"], scrub(ex["variant"], forbidden, 90)))
    by_pat = collections.defaultdict(list)
    for o in obs:
        for pat in o["pattern"]:
            by_pat[pat].append(o)
    if unattributed:
        c = split(unattributed)
        lines += ["", "%d observations had neither an edit class nor a diff pattern (free text matched no keyword): %s." % (
            len(unattributed), ", ".join("%s %d" % kv for kv in sorted(c.items())))]
    lines += ["", "## Diff patterns seen", "", "| diff pattern | n | fixed | improved | no-change | regressed |", "|---|---|---|---|---|---|"]
    for pat, os_ in sorted(by_pat.items(), key=lambda kv: -len(kv[1])):
        c = split(os_)
        lines.append("| %s | %d | %d | %d | %d | %d |" % (pat, len(os_), c["fixed"], c["improved"], c["no-change"], c["regressed"]))
    lines += ["", "## Observations", "", "| addr | before | after | outcome | edit | pattern | note |", "|---|---|---|---|---|---|---|"]
    for o in sorted(obs, key=lambda x: (int(x["addr"], 16), x["before"] or 0)):
        lines.append("| %s | %s | %s | %s | %s | %s | %s |" % (
            o["addr"], o["before"], o["after"], o["outcome"], ",".join(o["edit"]), ",".join(o["pattern"]),
            scrub(o["variant"] or o["delta"], forbidden, 110)))
    return "\n".join(lines) + "\n"


def default_out():
    import common
    return Path(common.MAIN) / ".scratch" / "regmine" / "rulebook.md"


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--ledger", type=Path)
    ap.add_argument("--ready-glob")
    ap.add_argument("--out", type=Path)
    ap.add_argument("--min-n", type=int, default=1)
    a = ap.parse_args(argv)
    import common
    ledger = a.ledger or (common.STATE / "attempts.jsonl")
    rows = [json.loads(l) for l in ledger.read_text().splitlines() if l.strip()] if ledger.exists() else []
    scratch = os.environ.get("GAG_SCRATCH_ROOT") or os.path.join(os.path.dirname(str(common.MAIN)), "gagarin-scratch")
    pattern = a.ready_glob or os.path.join(scratch, "*", "READY", "README.md")
    readmes = []
    for p in sorted(glob.glob(pattern)):
        try:
            readmes.append((Path(p).parts[-3], Path(p).read_text(errors="replace")))
        except OSError:
            pass
    obs = mine(rows, readmes)
    text = rulebook(obs, load_forbidden(common.MAIN), a.min_n)
    out = (a.out or default_out()).resolve()
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(text)
    tot = collections.Counter(o["outcome"] for o in obs)
    print("%d ledger rows, %d packet notes, %d observations %s -> %s" % (len(rows), len(readmes), len(obs), dict(tot), out))
    return 0


if __name__ == "__main__":
    sys.exit(main())
