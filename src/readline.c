/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:54:40 by bboissen          #+#    #+#             */
/*   Updated: 2024/03/11 13:48:16 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The readline() function reads a line from the terminal and returns it, using prompt as a prompt.
If no prompt is given as parameter, no prompt will be shown in the terminal.
The line returned is allocated with malloc and we have to free it ourselves.*/


/*
The add_history() function saves the line passed as parameter in the history so it can be retrieved later in the terminal (like pressing the up arrow in bash).
*/

/*
The rl_clear_history() function clears the history list by deleting all of the entries.
The rl_clear_history() function frees data that the readline library saves in the histroy list.
*/

/*
The rl_on_new_line() function tells the update routine that we have moved onto a new empty line, usually used after outputting a line.
*/

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

//cc -o readline src/readline.c -lreadline

int main(void)
{
	char *rl;
	char *pwd;
	
	while (rl[0] != 'b')
	{
		rl = readline("Prompt > ");
		add_history(rl);
		if (rl[0] == 'c')
			rl_clear_history();
		if (rl[0] == 'p')
		{
			pwd = getcwd(NULL, 0);
			printf("%s\n", pwd);
		}
		rl_on_new_line();
	}
	return (0);
}
