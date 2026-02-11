# Minishell

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

## How My Minishell Works Internally

### Data Structures

#### `t_cmd`
Represents a single command in a pipeline.

```c
typedef struct s_cmd
{
    char            **cmd;
    char            *path;
    int             fd[2];
    pid_t           pid;
    int             nb_cmds;
    struct s_cmd    *next;
}   t_cmd;
```

Each node corresponds to one command between pipes. The linked list represents
the full pipeline.

---

#### `t_env`
Stores environment variables.

```c
typedef struct s_env
{
    char            **envp;
    struct s_env    *next;
}   t_env;
```

The `envp` array is used for variable expansion and passed directly to `execve()`.

---

### Global State

```c
extern int  g_ex_code;
```

Tracks the exit status of the last executed command and is used for `$?` expansion.

---

## Execution Flow

```
Read Input
 → Lexer
 → Syntax Check
 → Command List Creation
 → Expansion
 → Quote Removal
 → Pipes & Redirections
 → Execution
 → Cleanup
```

---

## Parser
The shell waits for user input using `readline()`.
If the input is non-empty, it is added to the command history.
An empty input or `Ctrl-D` causes the shell to exit.
The parser is split into two stages:

### Lexer
The lexer scans the raw input character by character and transforms it into a structured format.
It inserts internal separators only outside of quotes:
- `\3` to separate arguments
- `\4` to separate commands (pipes)

Redirection operators (`<`, `>`, `<<`, `>>`) are isolated so they can be processed independently later.

This allows clean splitting later without breaking quoted strings.

---

### Command Construction
- Input is split by `\4` into pipeline segments
- Each segment is split by `\3` into arguments
- A linked list of `t_cmd` is created

---

## Syntax Errors

Minishell validates syntax before execution, mainly focusing on pipes:
- Pipe at beginning
- Consecutive pipes
- Pipe at end of input

On error:
- An informative message is printed
- `g_ex_code` is set to `2`
- The command is not executed

---

## Expander

The expander processes:
- Environment variables (`$VAR`)
- Exit status (`$?`)

Rules:
- No expansion inside single quotes
- Expansion allowed in double quotes
- Empty expansions are removed from argument lists

---

## Here Document (Heredoc)

Heredocs (`<<`) allow inline input for commands.

Implementation:
- A pipe is created
- User input is read until the delimiter is reached
- Content is written to the pipe
- STDIN is redirected to the pipe read end

Signals are handled so `Ctrl-C` aborts the heredoc cleanly.

---

## Redirections

Supported redirections:
- `< file`
- `> file`
- `>> file`
- `<< limiter`

Redirections are applied in the child process before execution using `dup2()`.
Redirection tokens are removed before calling `execve()`.

---

## Pipes

Each pipe:
- Creates a connection between commands
- Redirects STDOUT of one command to STDIN of the next
- Forks processes accordingly

Builtins inside pipelines are executed in child processes.

---

## Signals

- `Ctrl-C` (SIGINT):
  - Clears current input
  - Interrupts running commands
  - Sets exit code to `130`
- `Ctrl-\` (SIGQUIT):
  - Ignored in interactive mode
  - Default behavior in child processes

---

## Built-in Commands

Builtins are handled internally:
- `cd`
- `echo`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

Stateful builtins (`cd`, `export`, `unset`, `exit`) execute in the parent process
to preserve shell state.

---

## Limitations

- No `&&`, `||`, or `;`
- No wildcard expansion (`*`)
- No job control
- No command substitution

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
