# Minishell

Create a bash-like simple shell.
<br>

## Overview
You can check the subject [here](https://github.com/hy-3/minishell/blob/main/subject.pdf)

## Usage
```
$ make 
$ ./minishell
```

If 'make' fails, please check if below path for readline in Makefile is aligned with the path in your computer.<br>
You can check the path in your computer with a command below, for example.<br>
> $ brew info readline

LDFLAGS = -L ~/brew/opt/readline/lib/<br>
CPPFLAGS = -I ~/brew/opt/readline/include/
