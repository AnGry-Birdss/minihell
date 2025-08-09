# Phase 1: Project Structure & Headers

## Summary
- Project is organized into `src/`, `include/`, and `obj/` directories.
- Main header file `minishell.h` exists and includes system headers, structure forward declarations, function prototypes, macro definitions, and a global variable for signal handling.
- Data structures for tokens, commands, environment, and shell state are defined using 42 Norm conventions.
- Makefile is present, compiles all sources, and links with readline.

## Assessment
- Structure and headers are compliant with 42 Norm and project requirements.
- All critical elements (guards, naming, modularity) are present.
- No major refinements needed for this phase.

## Recommendations
- Double-check all header guards for correct format (`FT_FILENAME_H`).
- Ensure all prototypes are grouped by module in `minishell.h`.
- Confirm only one global variable is used for signal handling.
