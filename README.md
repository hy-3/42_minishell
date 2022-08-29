# Minishell

Create a simple shell.
<br>

## Overview
### Allowed external fucntions to use for the project
```
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, kill, exit, getcwd, chdir, stat,
lstat, fstat, unlink, execve, dup, dup2, pipe,
opendir, readdir, closedir, strerror, perror,
isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr,
tcgetattr, tgetent, tgetflag, tgetnum, tgetstr,
tgoto, tputs
```
### Requirements
- Not interpret unclosed quotes or unspecified special characters like \ or ;.
- Not use more than one global variable.
- Show a prompt when waiting for a new command.
- Have a working History.
- Search and launch the right executable (based on the PATH variable or by using relative or absolute path)
- It must implement the builtins:
  - echo with option -n
  - cd with only a relative or absolute path
  - pwd with no options
  - export with no options
  - unset with no options
  - env with no options or arguments
  - exit with no options
- ’ inhibit all interpretation of a sequence of characters.
- " inhibit all interpretation of a sequence of characters except for $.
- Redirections:
  - < should redirect input.
  - \> should redirect output.
  - “<<” read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history.
  - “>>” should redirect output with append mode.
- Pipes | The output of each command in the pipeline is connected via a pipe to the input of the next command.
- Environment variables ($ followed by characters) should expand to their values.
- $? should expand to the exit status of the most recently executed foreground pipeline.
- ctrl-C ctrl-D ctrl-\ should work like in bash.
  - ctrl-C print a new prompt on a newline.
  - ctrl-D exit the shell.
  - ctrl-\ do nothing.
<br>

## Usage
```
$ make 
$ ./minishell
```
