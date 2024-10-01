/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaqad <aennaqad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:54:49 by aennaqad          #+#    #+#             */
/*   Updated: 2024/09/28 22:02:59 by aennaqad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

static char	*hand_env_linked_list(t_tokens **head, char *start)
{
	int		c;
	char	*end;
	char	*val;

	end = start;
	c = 0;
	while (*end && !is_space(*end) && *end != '|' && *end != '>'
		&& *end != '<' && *end != '\"' && *end != '\'')
	{
		end++;
		c++;
	}
	val = ft_strndup(start, end - start);
	add_back(head, val, "ENV", 55);
	return (start += c);
}

static char	*hand_cmd_linked_list(t_tokens **head, char *start)
{
	char	*end;
	char	*val;

	end = start;
	while (*end && !is_space(*end)
		&& *end != '$'
		&& *end != '|'
		&& *end != '>' && *end != '<'
		&& *end != '\"' && *end != '\'')
		end++;
	if (end > start)
	{
		val = ft_strndup(start, end - start);
		add_back(head, val, "CMD", 0);
		start = end;
	}
	return (start);
}

static char	*spc_named_add_linkd_list(t_tokens **head, char *start)
{
	if (*start == '>')
	{
		if (*(start + 1) == '>')
		{
			add_back(head, ">>", "APPEND", 1);
			start += 2;
		}
		else
			start = to_linkd_list(head, ">", "OUTPUT", start);
	}
	else if (*start == '<')
	{
		if (*(start + 1) == '<')
		{
			add_back(head, "<<", "HEREDOC", 1);
			start += 2;
		}
		else
			start = to_linkd_list(head, "<", "INPUT", start);
	}
	return (start);
}

static char	*space_named_add_linkd_list(t_tokens **head, char *start)
{
	char	*spaces_arr;

	spaces_arr = NULL;
	while (is_space(*start))
	{
		spaces_arr = ft_strjoin(spaces_arr, " ");
		start++;
	}
	add_back(head, spaces_arr, "SPACE", 3);
	return (start);
}

t_tokens	*tokenize(char *start)
{
	t_var	x;

	intial_data(&x);
	while (*start)
	{
		if (is_space(*start))
			start = space_named_add_linkd_list(&x.new_head, start);
		if (*start == '|' || *start == '>' || *start == '<'
			|| *start == '\"' || *start == '\'')
		{
			if (*start == '>' || *start == '<' )
			{
				start = spc_named_add_linkd_list(&x.new_head, start);
				continue ;
			}
			else if (*start == '|')
				start = to_linkd_list(&x.new_head, "|", "PIPE", start);
			else if (*start == '\'' || *start == '\"')
				start = qtkn(&x.new_head, start, &x.in_dbl_qts, &x.in_sngl_qts);
		}
		if (*start == '$')
			start = hand_env_linked_list(&x.new_head, start);
		start = hand_cmd_linked_list(&x.new_head, start);
	}
	return (x.new_head);
}
