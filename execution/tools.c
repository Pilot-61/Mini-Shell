/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 02:23:34 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/04 20:36:36 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup2(const char *s1)
{
	size_t	i;
	char	*arr;

	arr = (char *)malloc(ft_strlen(s1) + 1 * sizeof(char));
	i = 0;
	if (!arr)
		return (NULL);
	while (s1[i] != '\0')
	{
		*(arr + i) = s1[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

void	lstad(t_env **lst, t_env *news)
{
	t_env	*last;

	if (!news)
		return ;
	if (lst != NULL && news != NULL)
	{
		last = *lst;
		if (last == NULL)
			*lst = news;
		else
		{
			while (last->next != NULL)
				last = last->next;
			last->next = news;
		}
		news->next = NULL;
	}
}

t_env	*lstnew_env(char *key, char *value)
{
	t_env	*ptr;

	if (!key || !value)
		return (NULL);
	ptr = (t_env *)malloc(sizeof(t_env));
	if (!ptr)
		return (NULL);
	ptr->key = ft_strdup2(key);
	if (!ptr->key)
	{
		free(ptr);
		return (NULL);
	}
	ptr->value = ft_strdup2(value);
	if (!ptr->value)
	{
		free(ptr->key);
		free(ptr);
		return (NULL);
	}
	ptr->next = NULL;
	return (ptr);
}
