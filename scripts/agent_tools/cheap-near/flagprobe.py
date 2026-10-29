#!/usr/bin/env python3
"""flagprobe.py: score every manifest row of a TU under compiler-flag variants.

usage: flagprobe.py --tree WT --tu match/x.cpp [--tu ...] --out OUT.jsonl
Variants: the TU's current flags, then Ob none/Ob1/Ob2 and /Op toggled.
Rows whose COMDAT section (bytes+relocs) equals the current build keep the
current score; changed rows are scored with raw_match then diff_retail.
"""
import argparse, json, os, re, subprocess, sys, tempfile, shutil
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "land"))
from sectioncmp import coff

DEFAULT = "/nologo /c /O2 /Gr /GR /DNDEBUG /Gy /MT /Ob2"

def tuflags(path):
    for l in open(path, errors="replace"):
        m = re.match(r"\s*//\s*VC6FLAGS:(.*)", l)
        if m: return m.group(1).split()
    return DEFAULT.split()

def variants(cur):
    base = [f for f in cur if f not in ("/Ob0", "/Ob1", "/Ob2")]
    out = {}
    for ob in ("", "/Ob1", "/Ob2"):
        out["ob=" + (ob or "none")] = base + ([ob] if ob else [])
    op = [f for f in cur if f != "/Op"] if "/Op" in cur else cur + ["/Op"]
    out["op-toggle"] = op
    return out

def compile_(tree, tu, flags, obj):
    env = dict(os.environ, VC6_FLAGS=" ".join(flags))
    r = subprocess.run(["bash", f"{tree}/scripts/vc6/vc6cl.sh", f"/Fo{obj}", os.path.basename(tu)],
                       cwd=os.path.join(tree, os.path.dirname(tu)), env=env,
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    return r.returncode == 0 and os.path.exists(obj)

def score(tree, obj, e):
    for tool in ("raw_match.py", "diff_retail.py"):
        r = subprocess.run(["python3", f"{tree}/scripts/vc6/{tool}", "--obj", obj, "--sym", e["sym"],
                            "--addr", e["addr"], "--len", e["len"]], capture_output=True, text=True)
        if r.returncode == 0 and "100.0%" in r.stdout: return 100.0
        last = r.stdout
    for l in last.splitlines():
        if l.startswith("match:"):
            try: return float(l.split()[-1].rstrip("%"))
            except ValueError: pass
    return None

def secs(obj):
    c = coff(obj); d = {}
    for k, v in c.items():
        if "|" in k: d.setdefault(k.split("|", 1)[1].split("#")[0], []).append(v)
    return d

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--tree", required=True); ap.add_argument("--tu", action="append", default=[])
    ap.add_argument("--out", required=True)
    a = ap.parse_args()
    man = json.load(open(f"{a.tree}/scripts/data/match_manifest.json"))
    tmp = tempfile.mkdtemp(prefix="flagprobe_")
    with open(a.out, "a") as out:
        for tu in a.tu:
            rows = [e for e in man if e["tu"] == tu]
            cur = tuflags(os.path.join(a.tree, tu))
            bobj = os.path.join(tmp, "base.obj")
            if not compile_(a.tree, tu, cur, bobj):
                out.write(json.dumps({"tu": tu, "error": "base compile"}) + "\n"); out.flush(); continue
            bs = secs(bobj); base = {}
            vres = {}
            for vn, fl in variants(cur).items():
                if sorted(fl) == sorted(cur): continue
                vobj = os.path.join(tmp, "v.obj")
                if os.path.exists(vobj): os.remove(vobj)
                if not compile_(a.tree, tu, fl, vobj):
                    vres[vn] = {"flags": " ".join(fl), "error": "compile"}; continue
                vs = secs(vobj); ch = {}
                for e in rows:
                    if bs.get(e["sym"]) == vs.get(e["sym"]): continue
                    if e["addr"] not in base: base[e["addr"]] = score(a.tree, bobj, e)
                    ch[e["addr"]] = score(a.tree, vobj, e)
                up = {k: (base[k], v) for k, v in ch.items() if (v or 0) > (base[k] or 0)}
                down = {k: (base[k], v) for k, v in ch.items() if (v or 0) < (base[k] or 0)}
                vres[vn] = {"flags": " ".join(fl), "changed": len(ch), "up": up, "down": down}
            out.write(json.dumps({"tu": tu, "cur": " ".join(cur), "nrows": len(rows),
                                  "partials": sum(e["status"] != "matched" for e in rows),
                                  "variants": vres}) + "\n"); out.flush()
    shutil.rmtree(tmp, True)

if __name__ == "__main__":
    main()
