/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:15:00 by aennaqad          #+#    #+#             */
/*   Updated: 2024/10/01 19:30:20 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

void	intial_data(t_var *var)
{
	var->exp.final_arg = ft_strdup("");
	var->exp.var_name = NULL;
	var->exp.var_val = NULL;
	var->j = 0;
	var->temp = NULL;
	var->in_dbl_qts = 0;
	var->dbl_char = NULL;
	var->was_sgl = 0;
	var->new_head = NULL;
	var->joined_data = NULL;
	var->len = 0;
	var->new_token = NULL;
	var->spc = NULL;
	var->i = 0;
	var->ex = -1;
	var->c = 0;
	var->result = NULL;
	var->in_sngl_qts = 0;
}

int	handle_herdoc_del(t_tokens **curr, char **env, int fd, char *file_name)
{
	char	*l;
	// char	*exapned_l;

	// exapned_l = NULL;
	l = NULL;
	if ((*curr) && ((*curr)->flag == 0 || (*curr)->flag == 550))
	{
		while ('x')
		{
			l = readline("> ");
			if (!ttyname(0))
				return (open(ttyname(2), O_RDWR), 0);
			if (!ft_strcmp(l, (*curr)->data))
				break ;
			if (is_not_dlr((*curr)->data) && (*curr)->flag != 550)
				expand_her(l, env, fd);
			else
				write(fd, l, ft_strlen(l));
			write(fd, "\n", 1);
			free(l);
		}
		free(l);
		(*curr)->data = ft_strdup(file_name);
	}
	return (1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isalnum(int c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= 48 && c <= 57));
}

void	next_skip_spaces(t_tokens **curr)
{
	(*curr) = (*curr)->next;
	while ((*curr) && (*curr)->flag == 3)
		(*curr) = (*curr)->next;
}
