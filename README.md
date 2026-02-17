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

![shell_procces](https://github.com/user-attachments/assets/50bdb5f7-af15-4dd9-875a-f44e12e2287a)

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
  
<img width="569" height="453" alt="expansion" src="https://github.com/user-attachments/assets/0b0a44ad-907d-4bab-884f-b0340b7fff88" />

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
cat /dev/random | head
< Makefile < main.c cat > out > out2
<< hello << world << see << final cat
<< EOF cat
cat << EOF
cd  | cd
ls  | cd
cd  | ls
pwd | cat
cat | exit | cat | wc
cat >
exit 300
export | grep hello
export new (variavel nova) ;
export new=a (variavel nova) ;
export HELLO=world GOODBYE=world
unset HELLO GOODBYE
export "HELLO =hello"
echo ""''
echo test > file test1
export a=c b=a c=t e dps $a$b$c main.c
----
echo hello ; |
echo hello | |
|
echo hello |;
echo hello ; ls
echo hello > test\ 1
cd $HOME/Documents
echo "\s" & echo "\s"
echo >
echo -n -n -nnnn -nnnnm
cat /dev/random | head -n 1 | cat -e
unset var1 # with undefined var1
export "" et unset ""
echo test > file test1
$
not_cmd bonjour > salut
env puis export puis env # vars aren't sorted
cat Makefile | grep pr | head -n 5 | cd test (mybin)
cat Makefile | grep pr | head -n 5 | cat test (bin)
cat Makefile | grep pr | head -n 5 | hello (NA)
echo hello >>> test
echo hello > > out
echo 2 >> out1 > out2
echo 2 > out1 >> out2
cat < test 
export var; export var=test
echo bonjour > $test
file_name_in_current_dir
cd ../../../../../.. ; pwd
ctrl-C . 130 sur bin(ex : sleep 10)&line vide
ctrl-\ .131 sur bin
echo "bip | bip ; coyotte > < " "
cat | cat | cat | ls # check outputs order
$bla # with bla not defined
export var ="cat Makefile | grep >"
export "test=ici"=coucou
c$var Makefile # with var=at
$LESS$VAR
/bin/echo bonjour
not_cmd
sleep 5 | exit
echo bonjour > $test w/ t
"exit retour a la ligne"
minishell # binary not in path without "./" before
cat diufosgid # check exit code
exit # should return the last exit code value
exit -10
exit +10
;
echo "$HOME"
echo '$HOME'
export ; env # display is different for both commands
echo $HOME
> log echo coucou
echo hudifg d | | hugdfihd
echo
echo simple
echo -n simple
echo ''
echo ""
echo "\"
echo "\n \n \n"
echo "\n \n \\n"
echo ;;
echo hi";" hihi
echo hi " ; " hihi
cd
cd .
cd ~
cd /
cd no_file
cd a b c d
pwd a
pwd a b c d
export LOL=lala ROR=rara
unset LOL ROR
export "HI= hi"
export "HI =hi"
/bin/ls
#write something the press ctrl+c
#write something then press ctrl+d
#write something then press ctrl+\
echo $?
l^Ds
echo |
| echo
sort | ls # check output order
cat < >
cat < <
cat > >
> a ls > b < Makefile
echo > a Hello World!
> a echo Hello World!
cat < Makefile | grep gcc > output
exit 0 | exit 1
exit 1 | exit 0
```
