# Minishell (DrunkShell)

A small, from-scratch Unix-like shell written in C.
This shell parses user input, handles pipes, redirections, environment expansion,
and executes both builtin and external commands.

Prompt used by the shell:
```
DrunkShell>
```

---

## Features

### Command Execution
- Executes external programs using `execve()`
- Resolves commands using the `PATH` environment variable
- Supports absolute and relative paths

### Builtin Commands
- `echo` (with `-n`)
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

### Pipes
- Supports single and multiple pipes (`cmd1 | cmd2 | cmd3`)

### Redirections
- Input redirection: `< file`
- Output redirection (truncate): `> file`
- Output redirection (append): `>> file`
- Heredoc: `<< LIMITER`

### Expansions
- Environment variables (`$USER`, `$PATH`, etc.)
- Exit status expansion (`$?`)

### Quotes
- Single quotes `'...'` (no expansion)
- Double quotes `"..."` (expansion allowed)

### Signals
- Handles `Ctrl-C` and `Ctrl-\`
- Proper signal behavior in parent, child, and heredoc contexts

---

## Build & Run

### Requirements
- GCC or Clang
- GNU Make
- Readline library

### Build
```bash
make
```

### Run
```bash
./minishell
```

Exit the shell with:
- `exit`
- `Ctrl-D` on an empty prompt

---

## How to Use

### Basic Commands
```bash
ls -la
whoami
/bin/echo hello
./program arg1 arg2
```

### Pipes
```bash
ls -la | grep minishell | wc -l
```

### Redirections
```bash
echo hello > out.txt
echo again >> out.txt
cat < out.txt
```

### Heredoc
```bash
cat << EOF
line one
line two
EOF
```

### Variable Expansion
```bash
echo $HOME
echo $?
```

---

## Builtin Commands

### echo
Prints arguments to stdout.
Option `-n` disables the trailing newline.

### cd
Changes the current working directory.

### pwd
Prints the current working directory.

### env
Prints the current environment variables.

### export
Sets or updates environment variables.

### unset
Removes environment variables.

### exit
Exits the shell with an optional numeric status.

---

## Command Difficulty Levels

### Easy commands
- Simple external commands (`ls`, `cat`, `wc`)
- Builtins without pipes
- Single redirections
- Basic variable expansion

### Medium commands
- Multiple pipes
- Pipes with redirections
- Builtins inside pipelines (non-stateful)

### Hard commands
- Heredoc combined with pipes
- Complex quoting and expansions
- Syntax edge cases
- Stateful builtins inside pipelines (`cd`, `export`, `unset`)

---

## Code structure file by file

### minishell.c
Main loop:
- Reads input with `readline`
- Tokenizes input
- Expands variables
- Removes quotes
- Executes commands
- Frees memory

### parsing.c
- Lexer implementation
- Handles quotes and separators
- Splits input into tokens and pipes

### init.c
- Builds command linked list
- Syntax validation
- Path resolution

### expander.c / expander2.c
- Handles `$VAR` and `$?` expansion

### pipes.c
- Pipe setup and execution
- Forking logic
- Parent vs child builtin handling

### redirect.c / redirect_aux.c
- Input/output redirections
- Heredoc implementation

### exec.c
- Builtin dispatcher
- External command execution via `execve`

---

## Limitations imposed in the subject

- No logical operators (`&&`, `||`, `;`)
- No wildcard expansion (`*`)
- No job control (`fg`, `bg`, `jobs`)
- No command substitution (`$(...)`)

---

## Testing Checklist

```bash
pwd
echo hello
export TEST=42
echo $TEST
unset TEST
ls | wc -l
echo hi > file.txt
cat << EOF
test
EOF
false
echo $?
```
