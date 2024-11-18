/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:10:51 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/04 21:18:06 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_lstadd_back(t_env **lst, t_env *news)
{
	t_env	*last;

	if (!news)
		return (0);
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
	return (1);
}

t_env	*ft_lstnew(char *key, char *value)
{
	t_env	*ptr;

	if (!key || !value)
		return (NULL);
	ptr = (t_env *)ft_malloc((sizeof(t_env)), 1);
	if (!ptr)
		return (NULL);
	ptr->key = ft_strdup(key);
	if (!ptr->key)
	{
		return (NULL);
	}
	ptr->value = ft_strdup(value);
	if (!ptr->value)
	{
		return (NULL);
	}
	ptr->next = NULL;
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			if (s[i] == (char)c)
				return ((char *)&s[i]);
			i++;
		}
		if ((char)c == s[i])
			return ((char *)&s[i]);
	}
	return (NULL);
}
