#!/usr/bin/env python3
"""Ratchet on hand-transcribed assembly bodies.

A __declspec(naked) body scores 100% by construction: it is a transcription of
the disassembly, so it proves nothing about the source and recovers nothing.
The project's product is recovered C++, not a re-spelling of the bytes we were
already given. Inline _asm is sanctioned by AGENTS.md where it is the only way
to reach an instruction sequence -- a whole naked body almost never is, and in
practice it has been reached for when a match was merely awkward.

This gate makes the debt visible and one-directional: the count may fall, never
rise. Adding a naked body now requires deliberately raising the baseline, which
leaves a reviewable diff instead of a silent 100%.
"""
import json, pathlib, re, sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
BASELINE = ROOT / "scripts" / "data" / "naked_body_baseline.json"
NAKED = re.compile(r"__declspec\s*\(\s*naked\s*\)")


def scan():
    """Count real naked bodies, not prose about them.

    The marker occurs inside comments -- a file that documents why a body stays
    naked, or a retraction saying one was removed, mentions the spelling without
    declaring anything. Counting those inflates the debt and, worse, hides a
    real removal behind an unchanged total. Only a line that is not a comment
    and actually declares a function counts.
    """
    counts = {}
    for path in sorted((ROOT / "match").rglob("*")):
        if path.suffix not in (".cpp", ".h"):
            continue
        n = 0
        for line in path.read_text(errors="replace").splitlines():
            if not NAKED.search(line):
                continue
            if line.lstrip().startswith(("//", "*", "/*")):
                continue
            n += 1
        if n:
            counts[str(path.relative_to(ROOT))] = n
    return counts


def main():
    counts = scan()
    total = sum(counts.values())
    baseline = json.loads(BASELINE.read_text())
    limit = baseline["max_naked_bodies"]

    for path, n in counts.items():
        print(f"{n:3d}  {path}")
    print(f"\n{total} naked bodies, baseline {limit}")

    if total > limit:
        print(
            f"\nFAIL: naked bodies rose from {limit} to {total}.\n"
            "A naked body is a transcription, not a match. Work the phrasing\n"
            "steps in CONTRIBUTING.md first. If a\n"
            "body genuinely cannot be reached from C++, say so in a comment\n"
            "above it with the variants tried and the residual, then raise\n"
            "max_naked_bodies in scripts/data/naked_body_baseline.json in the same\n"
            "commit so the decision is reviewable.",
            file=sys.stderr,
        )
        return 1

    if total < limit:
        print(f"\nRatchet: lower max_naked_bodies to {total}.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
