# Legal scope (non-negotiable)

This is an independent preservation project with no EA or Westwood affiliation.
See [LICENSE](LICENSE) for the licence text.

What may be committed:

- decompiled C/C++ source, address-annotated;
- layouts, offsets, vtable and global addresses, expressed as code and
  constants;
- the reccmp config, build and verification scripts, CI, and census data
  derived from the binary.

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
