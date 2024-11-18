/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utillsTwoParser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaqad <aennaqad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:41:23 by aennaqad          #+#    #+#             */
/*   Updated: 2024/10/05 12:59:09 by aennaqad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

void	free_dbl_char(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	space_at_end(char *str)
{
	int	len;

	if (!str[0])
		return (0);
	len = ft_strlen(str) - 1;
	if (str[len] == ' ')
		return (1);
	return (0);
}

int	is_not_spic(char *str)
{
	if (str[0] == '|' || str[0] == '>' || str[0] == '<')
		return (0);
	return (1);
}

void	add_flags(t_var *var)
{
	if (var->jnd && var->c > 1)
		var->newa->join_mode = 777;
	if (var->is_sgl)
		var->newa->flag = 550;
}

void	join_token(t_tokens **new_head, t_tokens **curr)
{
	t_var			var;

	var.is_sgl = 0;
	var.jnd = 0;
	var.c = 0;
	if (!ft_strcmp((*curr)->data, "\x03"))
		return ;
	var.joined = ft_strdup("");
	while (*curr)
	{
		if ((*curr)->flag == 3 || (*curr)->flag == 1 || (*curr)->flag == 2)
			break ;
		if ((*curr)->flag == 550 || !ft_strcmp((*curr)->data, ""))
			var.is_sgl = 1;
		if (!ft_strcmp((*curr)->data, "$"))
			var.jnd = 1;
		var.joined = ft_strjoin(var.joined, (*curr)->data);
		var.c++;
		(*curr) = (*curr)->next;
	}
	var.newa = createnode(var.joined, "JOINED", 0);
	add_flags(&var);
	ft_tkn_add_back(new_head, var.newa);
}
