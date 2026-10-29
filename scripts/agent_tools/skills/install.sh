#!/bin/bash
# Link the delivery skills into the user's Claude Code skills dir (user level; nothing in the repo).
set -e
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DST="${1:-$HOME/.claude/skills}"
mkdir -p "$DST"
ADST="${2:-$HOME/.claude/agents}"
mkdir -p "$ADST"
for a in gagarin-worker gagarin-lander gagarin-orchestrator; do
  src="$(dirname "$HERE")/agent_defs/$a.md"
  if [ -e "$ADST/$a.md" ] && [ ! -L "$ADST/$a.md" ]; then echo "exists and is not a link, skipped: $ADST/$a.md"; else ln -sfn "$src" "$ADST/$a.md"; echo "linked $ADST/$a.md"; fi
done
for s in gagarin-packet-worker gagarin-lander gagarin-orchestrator; do
  if [ -e "$DST/$s" ] && [ ! -L "$DST/$s" ]; then echo "exists and is not a link, skipped: $DST/$s"; continue; fi
  ln -sfn "$HERE/$s" "$DST/$s"; echo "linked $DST/$s -> $HERE/$s"
done
