#!/usr/bin/env bash
# land_bundle.sh [options] <READY packet dir>... : see land_bundle.py --help
exec python3 "$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")/land_bundle.py" "$@"
