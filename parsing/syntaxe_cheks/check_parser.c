/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:28:52 by aennaqad          #+#    #+#             */
/*   Updated: 2024/10/03 21:13:03 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_close_quote(char *line)
{
	t_var		var;

	var.single_counter = 0;
	var.double_counter = 0;
	var.i = 0;
	while (line[var.i])
	{
		if (line[var.i] == '\'' && var.double_counter % 2 == 0)
			var.single_counter++;
		if (line[var.i] == '\"' && var.single_counter % 2 == 0)
			var.double_counter++;
		var.i++;
	}
	if (var.double_counter % 2 != 0 || var.single_counter % 2 != 0)
	{
		ft_putstr_fd("syntax error\n", 2);
		return (0);
	}
	return (1);
}

int	handl_pipes(t_tokens *curr)
{
	if (curr && !ft_strncmp((curr)->type, "PIPE", 4))
	{
		(curr) = (curr)->next;
		while ((curr) && (curr)->flag == 3)
			(curr) = (curr)->next;
		if (!(curr) || !ft_strncmp((curr)->type, "PIPE", 4))
			return (0);
	}
	return (1);
}

int	syntaxe_error(t_tokens *tokens)
{
	t_tokens	*curr;

	curr = tokens;
	if (curr && !ft_strncmp(curr->type, "PIPE", 4))
		return (0);
	while (curr)
	{
		if (curr->flag == 1)
		{
			curr = curr->next;
			while (curr && curr->flag == 3)
				curr = curr->next;
			if (!curr || curr->flag == 2 || curr->flag == 1)
				return (0);
		}
		if (!handl_pipes(curr))
			return (0);
		curr = curr->next;
	}
	return (1);
}

int	is_empty_line(char *line)
{
	t_var	var;

	var.i = 0;
	var.j = 0;
	while (line[var.j])
		var.j++;
	while (is_space(line[var.i]))
		var.i++;
	if (var.i == var.j)
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
