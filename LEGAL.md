# Legal scope (non-negotiable)

This is an independent preservation project with no EA or Westwood affiliation.
See [LICENSE](LICENSE) for the licence text.

What may be committed:

- decompiled C/C++ source, address-annotated;
- layouts, offsets, vtable and global addresses, expressed as code and
  constants;
- the reccmp config, build and verification scripts, CI, and census data
  derived from the binary;
- Phobos's own material when the review below permits the specific import.

What must never be committed (all `.gitignore`d):

- the retail binary, the game's MIX assets, or any EA byte;
- any PDB, `.obj`, `.exe` or other build output;
- the Microsoft VC6 toolchain, which is fetched at build time;
- verbatim text from sources without a compatible licence (YRpp ships none, so
  it is consult-only: reconfirm every fact against the binary and never copy its
  headers);
- material from private or unpublished projects.

Licence: GPLv3 with EA's Section 7 additional terms (no EA trademarks,
modifications marked, no claim of EA affiliation). EA's released RA1/TD source
is a naming and structure reference only, never a transcription source; RA1 was
built with Watcom and is two engine generations back. Clean-room
reimplementations (OpenRA-ra2, ra2yrcpp and others) are black-box behaviour
references only, never a code or layout source.

Every source and header file carries a provenance header naming where its facts
came from (see [CONTRIBUTING.md](CONTRIBUTING.md) for the tags).

## Phobos and its YRpp submodule

Reviewed on 2026-10-21: Phobos commit
[`89fcc44`](https://github.com/Phobos-developers/Phobos/tree/89fcc44fbafca9f04e6db8729a68f5d1811254a1)
contains a [GPLv3 licence](https://github.com/Phobos-developers/Phobos/blob/89fcc44fbafca9f04e6db8729a68f5d1811254a1/LICENSE.md).
Its [YRpp dependency is a separate submodule](https://github.com/Phobos-developers/Phobos/blob/89fcc44fbafca9f04e6db8729a68f5d1811254a1/.gitmodules),
pinned there to
[`1d5d17d`](https://github.com/Phobos-developers/YRpp/tree/1d5d17d141554987d86f181bba749efbd2ff6488).
No project-wide reuse licence was identified in that YRpp revision. Phobos's
parent licence does not establish permission to copy the submodule. YRpp
remains consult-only, including YRpp-derived material moved outside that folder.

Phobos's own GPLv3-covered code is a candidate for reuse. Before importing any
material, verify its authorship, origin and applicable terms at the exact file
and commit. Preserve copyright, attribution and licence notices, include the
applicable licence text, mark modifications, and record a `Phobos-GPL3`
provenance tag with the upstream path and commit. Preserve the actual version
grant; do not relabel GPLv3-only material as GPLv3-or-later.

The reviewed [Phobos README](https://github.com/Phobos-developers/Phobos/blob/89fcc44fbafca9f04e6db8729a68f5d1811254a1/README.md#legal-and-license)
also says EA's modding guidelines take precedence over its licence and mentions
non-commercial use. Those stated additional terms need clarification before
an import; this policy does not declare unconditional licence compatibility.

Phobos extends the engine through injected code. Its names, layouts and
behaviour claims remain hypotheses to confirm against retail `gamemd.exe`.
Licence eligibility alone does not establish that its code reproduces retail
functions or is recovered Westwood source.
