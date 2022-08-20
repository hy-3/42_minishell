[Hiro] Not interpret unclosed quotes or unspecified special characters like \ or ;.
-> throw error when pipe is unclosed as well because it is not asked.

[Check_at_the_end] Not use more than one global variable, think about it and be ready to explain why you do it.

[Hiro] Show a prompt when waiting for a new command.
- Done.

[Edu] Have a working History.
- Change to allowed methods.

[Hiro] Search and launch the right executable (based on the PATH variable or by using relative or absolute path)
- Done.

[Hiro] It must implement the builtins:
    [Hiro] echo with option -n
    - Done
    [Hiro] cd with only a relative or absolute path
    [Hiro] pwd with no options
    - Done
    [Hiro] export with no options
    [Hiro] unset with no options
    [Hiro] env with no options or arguments
    - Done
    [Hiro] exit with no options

[Hiro] ’ inhibit all interpretation of a sequence of characters.

[Hiro] " inhibit all interpretation of a sequence of characters except for $.

[Hiro] Redirections:
    [Hiro] < should redirect input.
    [Hiro] > should redirect output.
    [Hiro] “<<” read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history!
    [Hiro] “>>” should redirect output with append mode.
- Implement methods when arrows included after the parse.
- Implement heredoc.
- Make sure << doesn't update history.

[Hiro] Pipes | The output of each command in the pipeline is connected via a pipe to the input of the next command.
- Done.

[Hiro] Environment variables ($ followed by characters) should expand to their values.

[Check_at_the_end] $? should expand to the exit status of the most recently executed foreground pipeline.
- Make sure exit status code whenever we handles error.

[Edu] ctrl-C ctrl-D ctrl-\ should work like in bash.∫
    When interactive:
      [Edu] ctrl-C print a new prompt on a newline.
      [Edu] ctrl-D exit the shell.
      [Edu] ctrl-\ do nothing.




# Possible imputs (to think how we parse from readline imput)
    $ cmd
    $ cmd option
    $ cmd file
    $ cmd | cmd
    $ > file    -> [Override] you can write to mentioned file without prompt (you can end imput with ctl+C)
    $ >> file   -> [Add] you can write to mentioned file without prompt (you can end imput with ctl+C)
    $ < input_file | cmd > output_file h
        - if begin is < & one arg & file exists: < a(if file named a exists)    -> cat file & show (END)
    $ << TERMINATE_WORD
        ex) << TERMINATE_WORD    -> heredoc>
                                    (Work as 'echo' with new line after putting TERMINATE_WORD)
    $ cmd << TERMINATE_WORD | cmd
        ex) cat << | wc -l       -> pipe heredoc>
    $ $<ENV>
     $ "consider as one command" or 'consider as one command'
        ex) [echo "\n" or echo '\n'] and [echo \n]    -> different output
        ex) [" ls" or ' ls']    -> error(command not found)

# Possible flows (After parse)
- [cmd]
- [>] or [>>]
- [<]
- [<<]
- [$<ENV>]
- ["]
- [']

# Things to be careful with quote
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