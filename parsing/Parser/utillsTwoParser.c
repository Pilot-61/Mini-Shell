/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utillsTwoParser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaqad <aennaqad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:41:23 by aennaqad          #+#    #+#             */
/*   Updated: 2024/09/28 22:02:32 by aennaqad         ###   ########.fr       */
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

int	space_in_begin(char *str)
{
	if (str[0] == 32)
		return (1);
	return (0);
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

void	join_token(t_tokens **new_head, t_tokens **curr)
{
	char		*joined;
	t_tokens	*newa;
	int			is_sgl;

	is_sgl = 0;
	if (!ft_strcmp((*curr)->data, "\x03"))
		return ;
	joined = ft_strdup("");
	while (*curr)
	{
		if ((*curr)->flag == 3 || (*curr)->flag == 1 || (*curr)->flag == 2)
			break ;
		if ((*curr)->flag == 550 || !ft_strcmp((*curr)->data, ""))
			is_sgl = 1;
		joined = ft_strjoin(joined, (*curr)->data);
		(*curr) = (*curr)->next;
	}
	newa = createnode(joined, "JOINED", 0);
	if (is_sgl)
		newa->flag = 550;
	ft_tkn_add_back(new_head, newa);
}
