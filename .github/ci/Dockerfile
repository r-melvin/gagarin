# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original build-environment configuration.
# Only open-source runtime dependencies belong in this cached image. The VC6
# toolchain is fetched separately into the mounted, ignored toolchain directory.
FROM ubuntu:24.04

RUN dpkg --add-architecture i386 \
    && apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        ca-certificates git wine wine32:i386 wine64 \
    && rm -rf /var/lib/apt/lists/* \
    && git config --system --add safe.directory /workspace

ENV WINEDEBUG=-all \
    MESA_LOADER_DRIVER_OVERRIDE=swrast \
    LIBGL_ALWAYS_SOFTWARE=1

WORKDIR /workspace
