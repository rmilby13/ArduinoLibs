Repository layout

- This repo is a mono-repo of Arduino libraries. Each library lives under
  libraries/<LibraryName>/ and follows the Arduino library layout: a src/ folder
  (implementation and public headers), optional examples/ sketches, and any tests
  that the library author included.

Build, test, and lint commands

- No CI/build scripts were detected in the repository. Use these recommended commands locally:

  - Compile an example/sketch that uses a library with Arduino CLI:
    arduino-cli compile --fqbn <fqbn> ./libraries/<LibraryName>/examples/<Sketch>
    (replace <fqbn> with your board fully-qualified board name and <Sketch> with an example sketch filename or folder)

  - Create a PlatformIO project to run unit tests or to compile for multiple environments:
    platformio init --board <board_id> -d <project_dir>
    platformio run -d <project_dir>

  - Run a single PlatformIO unit test (after adding tests using PlatformIO's Unity runner):
    platformio test -d <project_dir> -e <env> --filter <test_name>

  - C/C++ linting/formatting (no config present in repo):
    clang-format -i <file>
    cpplint <file>

High-level architecture (big picture)

- Mono-repo of independently-versioned Arduino libraries located at:
  ArduinoLibs/libraries/<LibraryName>/

- Each library typically contains:
  - src/: core .cpp/.h implementation files (public headers should live at src/ top level)
  - examples/: sketches that demonstrate usage and are useful for compile-checks
  - tests: sparse, often single-file *_test.cpp unit tests placed next to sources

- Example: libraries/LocoNet/src/ holds a small, packet-oriented implementation for the LocoNet protocol. Files are split by message-handlers (ln_ prefix) and a central loconet.cpp/loconet.h pair exposes the API.

Key conventions (repo-specific)

- File naming
  - Per-library source files are in src/. Files with ln_ prefix in the LocoNet library correspond to specific packet/message types.
  - Unit-test files are named *_test.cpp and currently are not wired to a unified test runner.

- Build and tooling
  - There is no single repository-level build system. Assume Arduino CLI or PlatformIO per-library or per-example.
  - Keep public headers at src/<header>.h so Arduino tooling picks them up when the library is installed.

- Changes and coding style hints for Copilot sessions
  - Keep modifications limited to a single library and update its examples/tests together.
  - Avoid introducing non-Arduino runtime dependencies; prefer standard C++ and Arduino-compatible APIs.
  - When adding tests, prefer PlatformIO's Unity runner or add a clear README describing how to run them.

AI assistant / Copilot guidance

- No existing Copilot/AI assistant configuration files were found in the repository; this file is intended to centralize repository-specific guidance.
- When suggesting code changes, reference the library path (libraries/<LibraryName>/src/) and keep edits local to that library.
- If creating new build/test automation (PlatformIO, CI), add configuration at the library root or a repository-level CI workflow in .github/workflows/ so future sessions can reuse it.

Where to look quickly

- Source: libraries/<LibraryName>/src/
- Examples (compile targets): libraries/<LibraryName>/examples/
- Top-level license: LICENSE

Branch and commit guidance

- Current repository branch policy: avoid committing directly to main. Create a short-lived feature branch for Copilot-generated changes (e.g., copilot/add-copilot-instructions).

If more details are wanted

- If you want, add one example sketch per library (examples/) and a small PlatformIO test project; Copilot can then be given commands to generate CI workflows or unit-test scaffolding.
