/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:26:06 by bboissen          #+#    #+#             */
/*   Updated: 2024/03/19 14:04:45 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//cc -o clear src/clear.c -lreadline -ltermcap

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

char	*ft_strtok(char *str, char delim)
{
	static char	*token;
	char		*start;

	if (str)
		token = str;
	if (!token)
		return (NULL);
	while (*token == delim)
		token++;
	if (!*token)
	{
		token = NULL;
		return (NULL);
	}
	start = token;
	while (*token && *token != delim)
		token++;
	if (*token)
	{
		*token = '\0';
		token++;
	}
	return (start);
}

int main(void)
{
	char *rl;

	while (1)
	{
		rl = readline("Prompt > ");
		if (rl == NULL && errno == ENOMEM) 
		{
			fprintf(stderr, "Insufficient memory for readline\n");
			rl_clear_history();
			return (errno);
		}
		if (rl == NULL && errno == 0 || rl[0] == 'e') 
		{
			printf("exit\n");
 			break;
		}
		add_history(rl);
		if (rl[0] == 'c')
			write(STDOUT_FILENO, "\033[H\033[J", 7);
	}
	rl_clear_history();
	return (0);
}

