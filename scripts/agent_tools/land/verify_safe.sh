#!/usr/bin/env bash
# verify_safe.sh [verify_safe.py options] : verify_all with per-run temp objects (see verify_safe.py --help)
exec python3 "$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")/verify_safe.py" "$@"
