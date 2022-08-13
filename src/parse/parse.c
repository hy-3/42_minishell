#include "../minishell.h"

void	parse(char *original_imput, t_imput *parsed_imput)
{
	cust_split(original_imput, ' ', parsed_imput);
	//	- if contains odd num of "			-> dquote>
	//	- if contains odd num of '			-> quote>

	//	- if end is pipe
	//		ex) a |							-> pipe>
	//		ex) la | a |					-> pipe pipe>
	//		ex) la | a | a |				-> pipe pipe pipe>
	//	- if begin is >/>> & one arg: > a	-> no prompt but wait imput from user
	//	- if begin is < & one arg & file exists: < a(if file named a exists)
	//										-> cat file & show (END)
	//	- if contains << anywhere			-> heredoc>
}
