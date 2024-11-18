/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 00:49:05 by mes-salh          #+#    #+#             */
/*   Updated: 2024/11/18 19:20:14 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*trim_spaces(const char *str)
{
	const char	*end;
	size_t		len;
	char		*trimmed;

	while (ft_isspace((unsigned char)*str))
		str++;
	if (*str == '\0')
		return (ft_strdup2(""));
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace((unsigned char)*end))
		end--;
	len = end - str + 1;
	trimmed = (char *)ft_malloc((len + 1), 1);
	if (!trimmed)
		return (NULL);
	strncpy(trimmed, str, len);
	trimmed[len] = '\0';
	return (trimmed);
}

void	split_command(char *input, char **cmd, char **arg)
{
	char	*trim;
	char	*sp;

	trim = trim_spaces(input);
	sp = ft_strchr(trim, ' ');
	if (sp)
	{
		*sp = '\0';
		*cmd = ft_strdup2(trim);
		*arg = ft_strdup2(sp + 1);
	}
	else
	{
		*cmd = ft_strdup2(trim);
		*arg = NULL;
	}
}

void	ft_lstdelone(t_env *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del(lst->key);
		del(lst->value);
		free(lst);
	}
}
