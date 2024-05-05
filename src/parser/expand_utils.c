
#include "minishell.h"

void	token_join(t_mini **mini)
{
	(*mini)->token = (*mini)->h_token;
	while ((*mini)->token)
	{
		if ((*mini)->token->join)
		{
			if ((*mini)->token == (*mini)->h_token)
				(*mini)->h_token = (*mini)->token->next;
			(*mini)->token = list_join((*mini)->token);
			if (!(*mini)->token)
				error_manager((*mini), MALLOC, NULL, NULL);
		}
		else
			(*mini)->token = (*mini)->token->next;
	}
}

void	token_refacto(t_mini **mini)
{
	t_token	*tmp_token;

	if ((*mini)->token == (*mini)->h_token && !(*mini)->token->next)
		free_token(&(*mini)->h_token);
	else
	{
		tmp_token = (*mini)->token;
		if ((*mini)->token->prev)
		{
			(*mini)->token->prev->next = (*mini)->token->next;
			(*mini)->token = (*mini)->token->prev;
		}
		else
		{
			(*mini)->h_token = (*mini)->token->next;
			(*mini)->token = (*mini)->h_token;
		}
		if ((*mini)->token->next)
			(*mini)->token->next->prev = (*mini)->token->prev;
		free(tmp_token->str);
		free(tmp_token);
	}
}
