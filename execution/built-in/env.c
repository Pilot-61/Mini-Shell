/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 00:27:38 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/03 21:23:00 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*envinit(char **env)
{
	t_env	*head;
	int		i;
	char	**splited;

	i = 0;
	head = NULL;
	if (!*env)
	{
		lstaddb_env(&head, lstnew_env("PWD", "/"));
		lstaddb_env(&head, lstnew_env("SHLVL", "1"));
		lstaddb_env(&head, lstnew_env("_", "usr/bin/env"));
		lstaddb_env(&head,
			lstnew_env("PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
		return (head);
	}
	while (env[i])
	{
		splited = ft_split2(env[i], '=');
		if (!splited)
			return (NULL);
		lstaddb_env(&head, lstnew_env(splited[0], splited[1]));
		ft_free(splited);
		i++;
	}
	return (head);
}

char	*ft_strndup2(const char *s1, size_t n)
{
	size_t		i;
	char		*r;

	r = (char *)malloc(n + 1);
	if (!r)
		return (NULL);
	i = 0;
	while (s1[i] && i < n)
	{
		r[i] = s1[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

char	**ft_split2(char *s, char c)
{
	char	**result;
	char	*pos;

	if (!s)
		return (NULL);
	pos = ft_strchr(s, c);
	if (!pos)
		return (NULL);
	result = (char **)malloc(3 * sizeof(char *));
	if (!result)
		return (NULL);
	result[0] = ft_strndup2(s, pos - s);
	result[1] = ft_strdup2(pos + 1);
	result[2] = NULL;
	return (result);
}

void	printenv(t_env *envp)
{
	t_env	*temp;

	temp = envp;
	while (temp)
	{
		if (ft_strcmp(temp->value, "") != 0)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
	ft_exit_status(0, 1);
}
