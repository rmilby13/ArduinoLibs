Repository layout

- Mono-repo of Arduino libraries located at libraries/<LibraryName>/.
- Each library follows Arduino layout: src/ (implementation + public headers at src/<header>.h), optional examples/, and optional tests or *_test.cpp files.

Per-library documentation

- Expect a library-level markdown file at libraries/<LibraryName>/<LibraryName>.md describing:
  - Purpose and public API
  - Hardware targets and constraints (memory, special IO like RP2040 PIO)
  - How to build and run the library's examples/tests
  - Any included protocol docs (PDFs) and external references
- Existing library docs to consult now:
  - libraries/LocoNet/LocoNet.md — packet-oriented LocoNet implementation; ln_*-prefixed files are packet handlers; loconet class manages open/close/read/write; RP2040 PIO support and included protocol PDFs live in this folder.
  - libraries/TCPLocoNet/TCPLocoNet.md — TCP client adapter for JMRI LocoNet-over-TCP.

Build, test, and lint commands

- No repo-level CI detected. Recommended per-library commands:
  - Arduino CLI (compile a single example):
    arduino-cli compile --fqbn <fqbn> ./libraries/<LibraryName>/examples/<Sketch>
  - PlatformIO (create/run project):
    platformio init --board <board_id> -d <project_dir>
    platformio run -d <project_dir>
  - Run a single PlatformIO unit test (after adding tests using Unity):
    platformio test -d <project_dir> -e <env> --filter <test_name>
  - Lint/format:
    clang-format -i <file>
    cpplint <file>

High-level architecture

- Libraries are independent Arduino libraries; build and test per-library or per-example using Arduino CLI or PlatformIO.
- LocoNet library is packet-oriented. Packet types inherit from a common LNPacket base; files named ln_* are packet/message handlers. loconet.cpp/.h expose the main API.
- TCPLocoNet provides a TCP-based transport that can call into LocoNet library logic.

Key conventions

- Public headers must live at src/<header>.h so Arduino tooling finds them when installing the library.
- Tests use *_test.cpp naming but are not wired to a unified runner by default; add PlatformIO + Unity per-library to run tests.
- Keep library changes scoped to a single library (libraries/<LibraryName>/). Avoid adding non-Arduino runtime dependencies.
- For hardware-specific code, document constraints and preferred approach in the library's markdown file (e.g., RP2040 PIO usage in LocoNet.md).

AI / Copilot guidance

- Always consult libraries/<LibraryName>/<LibraryName>.md first for library-specific goals and constraints.
- Reference files using full paths like libraries/<LibraryName>/src/ in suggestions.
- When adding CI or PlatformIO configs, place them at the library root or .github/workflows/ so sessions can reuse them.

Where to look quickly

- libraries/<LibraryName>/<LibraryName>.md (library overview and build/run instructions)
- libraries/<LibraryName>/src/ (implementation)
- libraries/<LibraryName>/examples/ (compile targets)
- libraries/<LibraryName>/ (protocol PDFs and other reference files, e.g., libraries/LocoNet/*.pdf)
- Top-level LICENSE

Branch and commit guidance

- Avoid committing directly to main. Create a short-lived feature branch for changes (e.g., copilot/update-copilot-instructions).

