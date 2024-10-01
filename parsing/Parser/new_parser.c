/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaqad <aennaqad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:50:06 by aennaqad          #+#    #+#             */
/*   Updated: 2024/09/29 01:00:59 by aennaqad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_tokens	*parser_commands(t_tokens *curr, char **env)
{
	t_var		var;
	t_tokens	*prev;

	intial_data(&var);
	prev = curr;
	while (curr)
	{
		if (curr->flag == 7 || curr->flag == 8
			|| var.in_dbl_qts || var.in_sngl_qts)
			handle_qu_par(curr, &var, prev, env);
		else
		{
			h_jnd(&var.joined_data, &var.was_sgl, &var.new_head, env);
			if (!handle_word_env(curr, &var, env, prev))
				return (0);
		}
		if (curr->flag != 3 && curr->flag != 0
			&& curr->flag != 7 && curr->flag != 8)
			prev = curr;
		curr = curr->next;
	}
	h_jnd(&var.joined_data, &var.was_sgl, &var.new_head, env);
	return (var.new_head);
}

void	itialize_parser_var(t_parser *var)
{
	var->curr = NULL;
	var->prev = NULL;
	var->new_head = NULL;
	var->node_before = NULL;
	var->node_after = NULL;
	var->node_redirection = NULL;
	var->node_cmd = NULL;
	var->head_red = NULL;
	var->node_redirection = NULL;
	var->miniline = NULL;
	var->head = NULL;
	var->splited_miniline = NULL;
	var->red = NULL;
	var->j = 0;
}

t_tokens	*parser(t_tokens *tokens)
{
	t_parser	var;

	(1) && (itialize_parser_var(&var), var.curr = tokens, 0);
	while (var.curr)
	{
		if (var.curr->flag == 0 && var.curr->data[0] == '$'
			&& var.curr->data[1] == '\0')
			var.curr = var.curr->next;
		if (var.curr && var.curr->flag != 1
			&& var.curr->flag != 3 && var.curr->flag != 2)
			join_token(&var.new_head, &var.curr);
		if (var.curr && var.curr->flag == 1)
		{
			var.node_before = createnode(" ", "SPACE", 3);
			var.node_after = createnode(" ", "SPACE", 3);
			ft_tkn_add_back(&var.new_head, var.node_before);
			copy_and_add_to_list(var.curr, &var.new_head);
			ft_tkn_add_back(&var.new_head, var.node_after);
		}
		if (var.curr && var.curr->flag != 1)
			copy_and_add_to_list(var.curr, &var.new_head);
		if (var.curr)
			var.curr = var.curr->next;
	}
	return (var.new_head);
}

void	reintial_data(t_parser *var)
{
	var->splited_miniline = NULL;
	var->miniline = NULL;
	var->node_cmd = NULL;
	var->node_redirection = NULL;
}

t_cmd	*parse_commands(t_tokens *tokens)
{
	t_parser	var;

	itialize_parser_var(&var);
	var.curr = tokens;
	while (var.curr)
	{
		reintial_data(&var);
		while (var.curr && var.curr->flag != 2)
		{
			if (var.curr->flag == 1)
				create_linkd_list_red(&var);
			else if (var.curr->flag != 1)
				create_mini_line(&var);
			if (var.curr)
				var.curr = var.curr->next;
		}
		create_last_result(&var);
		if (var.curr && var.curr->flag == 2)
			var.curr = var.curr->next;
	}
	return (var.head);
}
