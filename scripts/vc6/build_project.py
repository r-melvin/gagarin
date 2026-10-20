#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Compile tracked project C++ into persistent, path-preserving VC6 objects.

This is an object build, not an engine link or proof of executable identity.
The local object index records the input set for subsequent link analysis.
"""

import argparse
import concurrent.futures
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

from source_inventory import InventoryError, build_inventory, git_tracked_paths


ROOT = Path(__file__).resolve().parents[2]


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def input_hashes(root):
    inputs = {}
    for name in git_tracked_paths(root, "match"):
        if Path(name).suffix not in (".cpp", ".h"):
            continue
        path = root / name
        if path.is_symlink():
            raise InventoryError(f"refusing tracked symlink input: {name}")
        inputs[name] = sha256(path)
    return inputs


def check_index(root, out):
    """Reject stale objects before a downstream diagnostic uses this index."""
    index = json.loads((out / "objects.json").read_text(encoding="utf-8"))
    if not index.get("success"):
        raise InventoryError("object index records an unsuccessful build")
    if index.get("input_sha256") != input_hashes(root):
        raise InventoryError("tracked source/header inputs changed; rebuild project objects")
    for name, field in [("scripts/vc6/vc6cl.sh", "wrapper_sha256"),
                        ("scripts/data/match_manifest.json", "manifest_sha256")]:
        if sha256(root / name) != index.get(field):
            raise InventoryError(f"{name} changed; rebuild project objects")
    for item in index["objects"]:
        path = out / item["object"]
        if not path.resolve().is_relative_to(out.resolve()):
            raise InventoryError("object index path escapes output directory")
        if not item.get("success") or sha256(path) != item.get("object_sha256"):
            raise InventoryError(f"object missing or changed: {item['object']}")
    print(f"Object index is current: {len(index['objects'])} objects; no link performed")
    return 0


def compile_unit(root, out, unit, flags_override=None):
    relative = Path(unit["path"])
    source = root / relative
    obj = out / relative.with_suffix(".obj")
    log = out / relative.with_suffix(".log")
    obj.parent.mkdir(parents=True, exist_ok=True)
    obj.unlink(missing_ok=True)
    result = {
        "source": relative.as_posix(),
        "source_sha256": sha256(source),
        "object": obj.relative_to(out).as_posix(),
        "log": log.relative_to(out).as_posix(),
        "flags": flags_override or unit["vc6_flags"],
        "flags_source": "VC6_FLAGS environment" if flags_override else unit["vc6_flags_source"],
        "manifest_rows": unit["row_count"],
    }
    with log.open("w", encoding="utf-8") as stream:
        try:
            process = subprocess.run(
                ["bash", str(root / "scripts/vc6/vc6cl.sh"), "/Fo" + str(obj), source.name],
                cwd=source.parent, stdout=stream, stderr=subprocess.STDOUT,
            )
            code = process.returncode
        except OSError as exc:
            stream.write(f"could not start compiler: {exc}\n")
            code = 127
    result["compiler_exit_code"] = code
    result["success"] = code == 0 and obj.is_file()
    if result["success"]:
        result["object_sha256"] = sha256(obj)
    else:
        obj.unlink(missing_ok=True)
    return result


def build(root, out, jobs):
    root, out = root.resolve(), out.resolve()
    inventory, status = build_inventory(root)
    if status:
        raise InventoryError("source inventory has missing or symlink inputs; run source_inventory.py")
    units = [unit for group in inventory["subsystems"] for unit in group["translation_units"]]
    inputs = input_hashes(root)
    override = os.environ.get("VC6_FLAGS") or None
    out.mkdir(parents=True, exist_ok=True)
    # Remove a previous successful index before starting a new build. Failed
    # builds still write a new index with explicit per-object failure state.
    index_path = out / "objects.json"
    index_path.unlink(missing_ok=True)
    results = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=jobs) as executor:
        futures = {executor.submit(compile_unit, root, out, unit, override): unit for unit in units}
        for future in concurrent.futures.as_completed(futures):
            result = future.result()
            results.append(result)
            if not result["success"]:
                print(f"FAIL {result['source']} (see {out / result['log']})", file=sys.stderr)
    results.sort(key=lambda result: result["source"])
    successful = sum(result["success"] for result in results)
    inputs_unchanged = inputs == input_hashes(root)
    index = {
        "schema_version": 1,
        "scope": "tracked C++ object build; no integrated engine link",
        "success": successful == len(units) and inputs_unchanged,
        "source_count": len(units),
        "successful_objects": successful,
        "wrapper_sha256": sha256(root / "scripts/vc6/vc6cl.sh"),
        "manifest_sha256": sha256(root / "scripts/data/match_manifest.json"),
        "inventory_warnings": inventory["warnings"],
        "input_sha256": inputs,
        "inputs_unchanged_during_build": inputs_unchanged,
        "input_scope": "tracked match/*.cpp and *.h; external toolchain headers are not fingerprinted",
        "objects": results,
    }
    temporary = out / "objects.json.tmp"
    temporary.write_text(json.dumps(index, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    temporary.replace(index_path)
    print(f"{successful}/{len(units)} tracked translation units compiled; index: {index_path}")
    if not inputs_unchanged:
        print("Inputs changed during compilation; rebuild before using these objects", file=sys.stderr)
    return 0 if index["success"] else 1


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--out", type=Path, default=ROOT / "build-vc6/project")
    parser.add_argument("--jobs", type=int, default=4)
    parser.add_argument("--check", action="store_true", help="check saved object and tracked input hashes without compiling")
    args = parser.parse_args(argv)
    if args.jobs < 1:
        parser.error("--jobs must be positive")
    try:
        if args.check:
            return check_index(ROOT, args.out.resolve())
        return build(ROOT, args.out, args.jobs)
    except (InventoryError, OSError, ValueError, KeyError, subprocess.CalledProcessError) as exc:
        print(f"build_project: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
