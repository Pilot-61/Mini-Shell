/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsParser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaqad <aennaqad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:33:05 by aennaqad          #+#    #+#             */
/*   Updated: 2024/09/29 01:44:51 by aennaqad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

void	joined(t_var **var, t_tokens *curr, char **env)
{
	char	*temp;

	if ((*var)->joined_data
		&& expand_dlr_args((*var)->joined_data, env)[0] == '\0')
		(*var)->joined_data = ft_strdup("");
	temp = NULL;
	if ((*var)->in_sngl_qts)
		(*var)->was_sgl = 1;
	temp = ft_strjoin((*var)->joined_data, curr->data);
	(*var)->joined_data = temp;
}

void	h_jnd(char **joined_data, int *was_sgl, t_tokens **new_head, char **env)
{
	t_tokens	*new_token;
	char		*expanded;

	new_token = NULL;
	if (*joined_data)
	{
		if (*was_sgl)
		{
			new_token = createnode(*joined_data, "WORD", 0);
			*was_sgl = 0;
			new_token->flag = 550;
			ft_tkn_add_back(new_head, new_token);
		}
		else
		{
			expanded = expand_dlr_args(*joined_data, env);
			if (expanded)
			{
				new_token = createnode(expanded, "WORD", 0);
				ft_tkn_add_back(new_head, new_token);
				new_token = NULL;
			}
		}
		*joined_data = NULL;
	}
}

void	intial_handle_env(t_var *var, t_tokens **new, t_tokens **spc)
{
	*spc = NULL;
	*new = NULL;
	(*var).dbl_char = NULL;
	(*var).i = 0;
}

void	create_add_likedlist(t_tokens **head, char *val, char *type, int flag)
{
	t_tokens	*node;

	node = createnode(val, type, flag);
	ft_tkn_add_back(head, node);
}

int	handle_ambguis(t_tokens *prev, char *to_exp, int c)
{
	if (prev->flag == 1)
	{
		if (!to_exp || c > 1 || !ft_strcmp(to_exp, "\x03"))
		{
			printf("abguis \n");
			return (0);
		}
	}
	return (1);
}
