[Hiro] Not interpret unclosed quotes or unspecified special characters like \ or ;.
- when quote is not closed: change from error to giving back prompt

[] Not use more than one global variable, think about it and be ready to explain why you do it.

x [Hiro] Show a prompt when waiting for a new command.

x [Edu] Have a working History.

x [Hiro] Search and launch the right executable (based on the PATH variable or by using relative or absolute path)

x [Hiro] It must implement the builtins:
    x [Hiro] echo with option -n
    x [Hiro] cd with only a relative or absolute path
    x [Hiro] pwd with no options
    x [Hiro] export with no options
    x [Hiro] unset with no options
    x [Hiro] env with no options or arguments
    x [Hiro] exit with no options

x [Hiro] ’ inhibit all interpretation of a sequence of characters.

x [Hiro] " inhibit all interpretation of a sequence of characters except for $.

x [Hiro] Redirections:
    x [Hiro] < should redirect input.
    x [Hiro] > should redirect output.
    x [Hiro] “<<” read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history!
    x [Hiro] “>>” should redirect output with append mode.

x [Hiro] Pipes | The output of each command in the pipeline is connected via a pipe to the input of the next command.

x [Hiro] Environment variables ($ followed by characters) should expand to their values.

x [Hiro] $? should expand to the exit status of the most recently executed foreground pipeline.

[Hiro] ctrl-C ctrl-D ctrl-\ should work like in bash.
    When interactive:
      [Hiro] ctrl-C print a new prompt on a newline.
      [Hiro] ctrl-D exit the shell.
      [Hiro] ctrl-\ do nothing.

# quotes
$ echo "$USER"
hiyamamo
$ echo '$USER'
$USER
$ echo "'$USER'"
'hiyamamo'
$ echo '"$USER"'
"$USER"
$ echo "'"$USER"'"
'hiyamamo'
$ echo '"'"$USER"'"'
"hiyamamo"
$ echo "$HOME"s
/Users/hiyamamos
$ echo "   $HOME "s 
   /Users/hiyamamo s
-> DONE

# TODO
- signal
- add signal to heredoc
- fix
> ls
Makefile        README.md       lib             minishell       src             todo.md         wc
> ls | wc
command not found