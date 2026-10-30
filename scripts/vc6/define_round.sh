#!/usr/bin/env bash
# One define_globals round: snapshot the build, apply, rebuild, prune. usage: define_round.sh REGION
# Needs GAMEMD_BINARY and an up-to-date build-vc6/gate. A round leaves the pruned sources for the next build.
set -e
cd "$(git rev-parse --show-toplevel)"
rm -rf build-vc6/gate-base3 && cp -r build-vc6/gate build-vc6/gate-base3
python3 scripts/vc6/define_globals.py apply --objdir build-vc6/gate --region "$1"
python3 scripts/vc6/build_project.py --out build-vc6/gate --jobs 8 2>&1 | tail -2
python3 scripts/vc6/define_globals.py prune --objdir build-vc6/gate --base build-vc6/gate-base3
