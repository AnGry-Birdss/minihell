# Phase 4: Built-in Commands

## Summary
- All required built-in command files are present in `src/builtins/` (echo, cd, pwd, export, unset, env, exit).
- `ft_echo` is implemented and norm-compliant, handling `-n` and argument spacing.
- Other built-ins are present but not all are fully implemented or tested.

## Assessment
- `echo` is functional and matches bash behavior for basic cases.
- Other built-ins may need further implementation and edge case handling.
- Exit status and error handling for built-ins should be reviewed for bash compatibility.

## Recommendations
- Complete and test all built-in commands for full bash compatibility.
- Ensure all built-ins are norm-compliant (function/line/param/var limits).
- Add robust error handling and exit status management for each built-in.
- Test edge cases (e.g., `cd` with/without args, invalid `export`, etc.).
