/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:02:12 by bboissen          #+#    #+#             */
/*   Updated: 2024/02/11 12:36:53 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

static int	init_words(t_list **cmd);
static int	init_words(t_list **cmd);

static int	parser(char const *s, t_list **cmd, int len, int i)
{
	int	j;
	int	flag;

	j = 0;
	flag = 0;
	if (i > 0 && s[i + j] == ' ')
	{
		while (s[i + j] && s[i + j] == ' ')
			i++;
	}
	while (s[i + j] && (s[i + j] != ' ' || (i == 0 && j == 0)
			|| i + j == len - 1) || flag == 1)
	{
		if ((s[i + j] == '\'' || s[i + j] == '"') && flag == 0)
			flag = 1;
		else if ((s[i + j] == '\'' || s[i + j] == '"') && flag == 1)
			flag = 0;
		j++;
	}
	((t_word *)((*cmd)->cont))->start = i;
	((t_word *)((*cmd)->cont))->len = j;
	return (i);
}

static int	index_words(char const *s, t_list **cmd)
{
	int		i;
	int		j;
	int		len;
	t_list	*current;

	len = ft_strlen(s);
	if (len == 0)
		return (-1);
	i = 0;
	current = *cmd;
	while (i < len)
	{
		i = parser(s, &current, len, i);
		j = ((t_word *)(current->cont))->len;
		if (s[i + j])
		{
			if (init_words(&current) < 0)
				return (-1);
			current = current->next;
			i += j + 1;
		}
		else
			i = i + j;
	}
	return (0);
}

static int	init_words(t_list **cmd)
{
	t_word	*words;
	t_list	*new;

	words = (t_word *)malloc(sizeof(t_word));
	if (!words)
		return (-1);
	words->start = -1;
	words->len = -1;
	words->err = 0;
	new = ft_lstnew(words);
	if (new)
		ft_lstadd_back(cmd, new);
	else
	{
		free(words);
		return (-1);
	}
	return (0);
}

static char	**malloc_error(char **args, t_list *current, t_list **cmd)
{
	free_array(args);
	if (((t_word *)(current->cont))->err == MALLOC_KO)
		((t_word *)((*cmd))->cont)->err = MALLOC_KO;
	return (NULL);
}

char	**parse_words(char const *s, t_list **cmd, char **argv, char **env)
{
	int		size;
	int		i;
	char	**args;
	t_list	*current;

	if (init_words(cmd) < 0 || index_words(s, cmd) < 0)
		return (NULL);
	current = *cmd;
	i = 0;
	size = ft_lstsize(*cmd);
	args = malloc((size + 1) * sizeof(char *));
	if (!args)
		return (clear_cmd(args, cmd, -1));
	args[size] = 0;
	while (current)
	{
		args[i] = fill_cmd(s, &current, argv, env);
		if (args[i++] == NULL)
			return (malloc_error(args, current, cmd));
		current = current->next;
	}
	return (args);
}
