/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:41:50 by aennaqad          #+#    #+#             */
/*   Updated: 2024/10/03 21:11:54 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

void	handle_qu_par(t_tokens *curr, t_var *var, t_tokens *prev, char **env)
{
	if (!ft_strncmp(prev->type, "HEREDOC", 7))
		var->was_sgl = 1;
	if (!ft_strncmp(curr->data, "\"", 1) && !var->in_sngl_qts)
	{
		var->in_dbl_qts = !var->in_dbl_qts;
		if (curr->next && curr->flag == 7 && curr->next->flag == 7
			&& var->in_dbl_qts)
		{
			var->new_token = copy_node(curr);
			ft_tkn_add_back(&var->new_head, var->new_token);
		}
	}
	else if (!ft_strncmp(curr->data, "\'", 1) && !var->in_dbl_qts)
	{
		var->in_sngl_qts = !var->in_sngl_qts;
		if (curr->next && curr->flag == 8 && curr->next->flag == 8
			&& var->in_sngl_qts)
		{
			var->new_token = copy_node(curr);
			ft_tkn_add_back(&var->new_head, var->new_token);
		}
	}
	else if (var->in_sngl_qts || var->in_dbl_qts)
		joined(&var, curr, env);
}

int	handle_word_env(t_tokens *curr, t_var *var, char **env, t_tokens *prev)
{
	if (!ft_strncmp(curr->type, "ENV", 3)
		&& (prev && ft_strcmp(prev->type, "HEREDOC")))
	{
		if (!handle_env(curr, &var->new_head, prev, env))
			return (0);
	}
	else
		copy_and_add_to_list(curr, &var->new_head);
	return (1);
}

void	create_mini_line(t_parser *var)
{
	char	*val;
	char	*new_miniline;

	val = NULL;
	if (!ft_strncmp(var->curr->data, "", 1))
		val = ft_strdup("\x08");
	else if (var->curr->flag == 3)
		val = ft_strdup("\x1F");
	else
		val = ft_strdup(var->curr->data);
	new_miniline = ft_strjoin(var->miniline, val);
	if (!new_miniline)
		return ;
	var->miniline = new_miniline;
}

void	create_last_result(t_parser *var)
{
	int	j;

	var->splited_miniline = ft_split(var->miniline, '\x1F');
	j = 0;
	while (var->splited_miniline[j])
	{
		if (var->splited_miniline[j][0] == '\x08')
			var->splited_miniline[j][0] = '\0';
		j++;
	}
	var->node_cmd = new_cmd_node(var->splited_miniline, var->head_red);
	add_cmd_back(&var->head, var->node_cmd);
	var->head_red = NULL;
}
