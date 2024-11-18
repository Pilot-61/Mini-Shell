/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:21:45 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/04 22:07:43 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoin2(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*joined;

	i = -1;
	j = -1;
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	joined = malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	while (s1[++i])
		joined[i] = s1[i];
	while (s2[++j])
		joined[i + j] = s2[j];
	joined[i + j] = '\0';
	return (joined);
}

void	ex_var(t_env *existing, char *k, char *v, int apnd)
{
	char	*temp;

	if (apnd)
	{
		temp = existing->value;
		if (temp)
		{
			existing->value = ft_strjoin2(temp, v);
			free(temp);
		}
		else
			existing->value = v;
		free(v);
	}
	else
	{
		free(existing->value);
		existing->value = v;
	}
	free(k);
}

void	parse_arg(char *arg, char **k, char **v, int *apnd)
{
	char	*equals_pos;

	*apnd = 0;
	equals_pos = ft_strchr(arg, '=');
	if (equals_pos == NULL)
		return ;
	if (equals_pos > arg && *(equals_pos - 1) == '+')
	{
		*apnd = 1;
		*(equals_pos - 1) = '\0';
		*k = ft_strdup2(arg);
		*(equals_pos - 1) = '+';
		*v = ft_strdup2(equals_pos + 1);
	}
	else
	{
		*equals_pos = '\0';
		*k = ft_strdup2(arg);
		*equals_pos = '=';
		*v = ft_strdup2(equals_pos + 1);
	}
}
