#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Run reccmp's image-level tools over the M3 hybrid link.

  reccmp_image.py [--out DIR] [--jobs N] [--queue queue.tsv] [--top 30] [--reuse] [--skip-stack]

Needs GAMEMD_BINARY (the pinned retail image; its SHA-256 is checked against reccmp-project.yml) and the reccmp
tools in PATH (reccmp-reccmp, -vtable, -datacmp, -roadmap, -stackcmp). Everything is written under DIR (default
build-vc6/reccmp, ignored by git), never /tmp. Stages:

  1 objects      the plain project objects (build-vc6/gate) and a /Z7 copy (DIR/obj)
  2 links        the M3 link of each (DIR/plain-link, DIR/link); the /Z7 link adds /DEBUG /PDB
  3 neutrality   debug_neutral.py: every object's non-debug sections and relocations, and the two images' sections
  4 reccmp       reccmp-reccmp --json over DIR/link (baseline), -vtable, -datacmp, -roadmap
  5 audit        reccmp_audit.py against scripts/data/match_manifest.json, with reccmp's own annotation reading
                 (sources copied and adjusted by reccmp_sanitize.py) and with functions paired by address
  6 stack        the --top near-miss partials of --queue (multiset_identical, still partial) linked into an
                 M1-style analysis image (link_m1.py --promote) and compared by reccmp_stack.py

DIR/summary.json holds the numbers; the per-stage logs and reports sit beside it. --reuse keeps objects and links
that already exist (the object directories are checked against the tracked sources first).

The hybrid image gets its non-project bytes from the retail image, so reccmp's verdict is only evidence about bytes
the project compiled: reccmp_audit.py tags every row with the placement origin (project / library / retail).
"""

import argparse
import csv
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
VC6 = ROOT / "scripts/vc6"
M3_FLAGS = ["--hybrid", "--pin-data", "--order-tail", "--source-data", "--search-literals", "--distribution-patches",
            "--rsrc-from-project", "--rsrc-art-from-retail"]
TOOLS = ["reccmp-reccmp", "reccmp-vtable", "reccmp-datacmp", "reccmp-roadmap", "reccmp-stackcmp"]
NOISE = re.compile(r"MESA|pci id|fixme|err:system|^\s*$")


def run(cmd, log, env=None, check=True):
    """Run cmd, send its output to `log`, return the exit code (SystemExit on failure when check)."""
    print("+", " ".join(str(c) for c in cmd), flush=True)
    with open(log, "w") as stream:
        code = subprocess.run([str(c) for c in cmd], stdout=stream, stderr=subprocess.STDOUT, env=env, cwd=ROOT).returncode
    if check and code:
        raise SystemExit(f"reccmp_image: {cmd[0]} {cmd[1] if len(cmd) > 1 else ''} failed ({code}); see {log}")
    return code


def pinned_hash():
    text = (ROOT / "reccmp-project.yml").read_text()
    return re.search(r"sha256:\s*([0-9a-f]{64})", text).group(1)


def reccmp_python():
    """The interpreter of the reccmp installation (read from the reccmp-reccmp script's first line)."""
    script = shutil.which("reccmp-reccmp")
    if not script:
        raise SystemExit("reccmp_image: reccmp-reccmp is not in PATH")
    first = Path(script).read_text().splitlines()[0]
    return first[2:].strip() if first.startswith("#!") else sys.executable


def reccmp_summary(log):
    """The 'Implemented/Accuracy/Progress' lines reccmp-reccmp prints."""
    out = {}
    for line in Path(log).read_text(errors="replace").splitlines():
        m = re.match(r"(Implemented|Accuracy|Progress):\s+([\d.]+)%(?:\s+\((\d+) / (\d+)\))?", line)
        if m:
            out[m[1].lower()] = float(m[2])
            if m[3]:
                out["functions_implemented"], out["functions_total"] = int(m[3]), int(m[4])
        m = re.match(r"(\d+) functions are aligned", line)
        if m:
            out["aligned"] = int(m[1])
    return out


def stack_targets(queue, manifest, top):
    """Addresses of the `top` highest-percentage rows of the permq queue that are multiset_identical and still partial."""
    status = {int(r["addr"], 16): r["status"] for r in json.loads(manifest.read_text())}
    with queue.open() as stream:
        rows = [r for r in csv.DictReader(stream, delimiter="\t")
                if r["multiset_identical"] == "True" and status.get(int(r["addr"], 16)) == "partial"]
    rows.sort(key=lambda r: -float(r["pct"]))
    return [r["addr"] for r in rows[:top]]


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--out", type=Path, default=ROOT / "build-vc6/reccmp")
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--queue", type=Path, help="permq queue.tsv; without it the stack stage is skipped")
    ap.add_argument("--top", type=int, default=30)
    ap.add_argument("--reuse", action="store_true", help="keep existing objects and links")
    ap.add_argument("--skip-stack", action="store_true")
    args = ap.parse_args(argv)
    out = args.out.resolve()
    if ROOT / "build-vc6" not in out.parents:
        ap.error("--out must be under build-vc6/ (the outputs embed retail bytes)")
    binary = os.environ.get("GAMEMD_BINARY")
    if not binary or not Path(binary).is_file():
        raise SystemExit("reccmp_image: GAMEMD_BINARY is not set to the retail image")
    if hashlib.sha256(Path(binary).read_bytes()).hexdigest() != pinned_hash():
        raise SystemExit("reccmp_image: GAMEMD_BINARY does not match the SHA-256 pinned in reccmp-project.yml")
    missing = [t for t in TOOLS if not shutil.which(t)]
    if missing:
        raise SystemExit(f"reccmp_image: not in PATH: {', '.join(missing)}")
    py = reccmp_python()
    out.mkdir(parents=True, exist_ok=True)
    (out / "logs").mkdir(exist_ok=True)
    logs = out / "logs"
    plain_obj, dbg_obj = ROOT / "build-vc6/gate", out / "obj"
    plain_link, dbg_link = out / "plain-link", out / "link"
    summary = {"retail_sha256": pinned_hash()}
    python = sys.executable

    # 1 objects
    if not (args.reuse and run([python, VC6 / "build_project.py", "--check", "--out", plain_obj], logs / "plain-check.log",
                                check=False) == 0):
        run([python, VC6 / "build_project.py", "--out", plain_obj, "--jobs", args.jobs], logs / "plain-build.log")
    if not (args.reuse and run([python, VC6 / "build_project.py", "--check", "--out", dbg_obj], logs / "dbg-check.log",
                                check=False) == 0):
        env = dict(os.environ, VC6_EXTRA_FLAGS="/Z7")
        run([python, VC6 / "build_project.py", "--out", dbg_obj, "--jobs", args.jobs], logs / "dbg-build.log", env=env)

    # 2 links
    for objdir, link, extra in ((plain_obj, plain_link, []), (dbg_obj, dbg_link, ["--debug"])):
        if not (args.reuse and (link / "m1.exe").is_file()):
            shutil.rmtree(link, ignore_errors=True)
            run([python, VC6 / "link_m1.py", "--objdir", objdir, "--out", link] + M3_FLAGS + extra,
                logs / f"{link.name}.log")

    # 3 neutrality
    run([python, VC6 / "debug_neutral.py", "objects", plain_obj, dbg_obj, "--json", out / "neutral_objects.json"],
        logs / "neutral_objects.log", check=False)
    run([python, VC6 / "debug_neutral.py", "images", plain_link / "m1.exe", dbg_link / "m1.exe", "--json",
         out / "neutral_images.json"], logs / "neutral_images.log", check=False)
    objects = json.loads((out / "neutral_objects.json").read_text())
    images = json.loads((out / "neutral_images.json").read_text())
    summary["neutrality"] = {
        "objects_compared": objects["objects_compared"], "sections_compared": objects["sections_compared"],
        "objects_with_differences": objects["objects_with_differences"], "by_kind": objects["by_kind"],
        "image_section_tables_equal": images["tables_equal"],
        "image_differing_bytes": {k: v["differing_bytes"] for k, v in images["sections"].items()},
        "image_differing_ranges": {k: v["ranges"] for k, v in images["sections"].items() if v["ranges"]}}

    # 4 reccmp
    src = out / "src"
    run([py, VC6 / "reccmp_sanitize.py", ROOT / "match", src, out / "sanitize.json"], logs / "sanitize.log")
    summary["sanitize"] = json.loads((out / "sanitize.json").read_text())["changes"]
    paths = ["--paths", binary, dbg_link / "m1.exe", dbg_link / "m1.pdb", src]
    run(["reccmp-reccmp"] + paths + ["--json", out / "reccmp.json", "--json-diet", "--silent", "--no-color"],
        logs / "reccmp.log")
    summary["reccmp"] = reccmp_summary(logs / "reccmp.log")
    for tool, name, extra in (("reccmp-vtable", "vtable", ["--no-color"]), ("reccmp-datacmp", "datacmp", ["--no-color"]),
                              ("reccmp-roadmap", "roadmap", [])):
        with open(out / f"{name}.txt", "w") as stream, open(logs / f"{name}.log", "w") as err:
            subprocess.run([tool] + [str(p) for p in paths] + extra, stdout=stream, stderr=err, cwd=ROOT)
    summary["vtable"] = (out / "vtable.txt").read_text().strip().splitlines()[:3]
    summary["datacmp_lines"] = len((out / "datacmp.txt").read_text().splitlines())
    summary["roadmap_lines"] = len((out / "roadmap.txt").read_text().splitlines())

    # 5 audit
    manifest = ROOT / "scripts/data/match_manifest.json"
    base = [py, VC6 / "reccmp_audit.py", binary, dbg_link / "m1.exe", dbg_link / "m1.pdb"]
    tail = [manifest, ROOT / "match"]
    empty = out / "empty"
    empty.mkdir(exist_ok=True)
    run(base + [src] + tail + [out / "audit_annotations.json", "--placement", dbg_link / "placement.json"],
        logs / "audit_annotations.log")
    run(base + [empty] + tail + [out / "audit_paired.json", "--placement", dbg_link / "placement.json",
                                 "--pair-by-address"], logs / "audit_paired.log")
    for name in ("annotations", "paired"):
        audit = json.loads((out / f"audit_{name}.json").read_text())
        reverse = {}
        for e in audit["reccmp_exact_not_manifest_matched"]:
            key = f"{e['manifest']}/{e['origin']}"
            reverse[key] = reverse.get(key, 0) + 1
        summary[f"audit_{name}"] = {"counts": audit["counts"], "reccmp_exact_not_manifest_matched": reverse}

    # 6 stack
    if args.queue and not args.skip_stack:
        targets = stack_targets(args.queue, manifest, args.top)
        (out / "stack_targets.txt").write_text("\n".join(targets) + "\n")
        shutil.rmtree(out / "stack", ignore_errors=True)
        run([python, VC6 / "link_m1.py", "--objdir", dbg_obj, "--out", out / "stack", "--pin-data", "--order-tail",
             "--debug", "--promote", out / "stack_targets.txt"], logs / "stack-link.log")
        run([py, VC6 / "reccmp_stack.py", binary, out / "stack/m1.exe", out / "stack/m1.pdb", manifest,
             out / "stack_targets.txt", out / "stack.json", out / "stack.txt"], logs / "stack.log")
        stack = json.loads((out / "stack.json").read_text())
        verdicts = {}
        for r in stack.values():
            verdicts[r["verdict"]] = verdicts.get(r["verdict"], 0) + 1
        summary["stack"] = {"functions": len(stack), "verdicts": verdicts,
                            "moved": {a: r["moved"] for a, r in stack.items() if r.get("moved")}}
    (out / "summary.json").write_text(json.dumps(summary, indent=1) + "\n")
    print(json.dumps(summary, indent=1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
