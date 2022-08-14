#include "../minishell.h"

t_imput	*parse(char *original_imput)
{
	return (cust_split(original_imput, ' '));
	// When below cases happen, add lists based on user input.
	//	- if end is pipe
	//		ex) a |							-> pipe>
	//		ex) la | a |					-> pipe pipe>
	//		ex) la | a | a |				-> pipe pipe pipe>
	//	- if begin is >/>> & one arg: > a	-> no prompt but wait imput from user
	//	- if begin is < & one arg & file exists: < a(if file named a exists)
	//										-> cat file & show (END)
	//	- if contains << anywhere			-> heredoc>
}
