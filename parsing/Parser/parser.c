/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:44:55 by aennaqad          #+#    #+#             */
/*   Updated: 2024/09/30 00:19:14 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_space_env(t_tokens **new_head, t_var *var, int *c)
{
	while (var->dbl_char[var->i] != NULL)
	{
		if (var->to_exp[0] == ' ')
			create_add_likedlist(new_head, " ", "SPACE", 3);
		var->new_token = createnode(var->dbl_char[var->i], "WORD", 0);
		ft_tkn_add_back(new_head, var->new_token);
		if (var->to_exp[ft_strlen(var->to_exp) - 1] == ' ')
			create_add_likedlist(new_head, " ", "SPACE", 3);
		if (is_space(var->to_exp[0]))
			var->new_token->join_mode = 888;
		else
			var->new_token->join_mode = 1;
		var->new_token = NULL;
		if (var->dbl_char[var->i + 1])
			create_add_likedlist(new_head, " ", "SPACE", 3);
		(*c)++;
		var->i++;
	}
}

int	handle_env(t_tokens *curr, t_tokens **new_head, t_tokens *prev, char **env)
{
	t_var	var;
	int		c;

	c = 0;
	var.to_exp = expand_dlr_args(curr->data, env);
	intial_data(&var);
	if (!var.to_exp)
		create_add_likedlist(new_head, "", "EMPTY", 777);
	if (!handle_ambguis(prev, var.to_exp, c))
		return (0);
	else if (var.to_exp)
	{
		var.dbl_char = ft_split(var.to_exp, ' ');
		handle_space_env(new_head, &var, &c);
	}
	return (1);
}

int	handle_num(t_var *var, char *arg)
{
	char	*temp;

	temp = ft_strdup(arg);
	temp += 2;
	if (is_numeric(temp))
	{
		var->exp.final_arg = ft_strdup(temp);
		return (1);
	}
	return (0);
}
