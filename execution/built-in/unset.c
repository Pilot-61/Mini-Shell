/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 05:21:15 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/04 23:46:55 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	search_and_delet(t_env *curr, t_env *prev, t_env **envp, char *word)
{
	while (curr)
	{
		if (ft_strcmp(curr->key, word) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*envp = curr->next;
			ft_lstdelone(curr, free);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	is_valid_identifier(char *arg)
{
	int	i;

	i = 0;
	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	unset(t_env **envp, char **args)
{
	t_env	*curr;
	t_env	*prev;
	char	**words;
	int		i;

	if (!envp || !*envp)
		return ;
	i = 0;
	words = args;
	while (words[i])
	{
		if (!is_valid_identifier(words[i]))
		{
			printf("unset: `%s': not a valid identifier\n", words[i]);
			i++;
			continue ;
		}
		curr = *envp;
		prev = NULL;
		search_and_delet(curr, prev, envp, words[i]);
		i++;
	}
	ft_exit_status(0, 1);
}
