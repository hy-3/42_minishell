[Check] Not interpret unclosed quotes or unspecified special characters like \ or ;.

[Check] Not use more than one global variable, think about it and be ready to explain why you do it.

[x] Show a prompt when waiting for a new command.
- Done by Edu

[x] Have a working History.
- Done by Edu.

[x] Search and launch the right executable (based on the PATH variable or by using relative or absolute path)
- Done by Hiro

[Both] It must implement the builtins:
    [Hiro] echo with option -n
    [Edu] cd with only a relative or absolute path
    [x] pwd with no options
    [Hiro] export with no options
    [Hiro] unset with no options
    [Edu] env with no options or arguments
    [Edu] exit with no options

[] ’ inhibit all interpretation of a sequence of characters.
- ask Pable

[] " inhibit all interpretation of a sequence of characters except for $.
- ask Pable

[Hiro] Redirections:
    [x] < should redirect input.
    [x] > should redirect output.
    [Hiro] “<<” read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history!
    [x] “>>” should redirect output with append mode.
- Make sure << doesn't update history.

[x] Pipes | The output of each command in the pipeline is connected via a pipe to the input of the next command.
- Done with Hiro .

[Hiro] Environment variables ($ followed by characters) should expand to their values.
- 

[Check] $? should expand to the exit status of the most recently executed foreground pipeline.
- Make sure exit status code whenever we handles error.

[Edu] ctrl-C ctrl-D ctrl-\ should work like in bash.∫
    When interactive:
      [Edu] ctrl-C print a new prompt on a newline.
      [Edu] ctrl-D exit the shell.
      [Edu] ctrl-\ do nothing.

hiroki