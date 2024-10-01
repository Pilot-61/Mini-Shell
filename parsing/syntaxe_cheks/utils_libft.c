/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:16:44 by aennaqad          #+#    #+#             */
/*   Updated: 2024/09/27 21:24:54 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**free_it(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static char	*allocsingleword(char const *s, size_t *start, char c)
{
	char		*oneword;
	size_t		end;
	size_t		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[*start] == c && s[*start] != '\0')
		(*start)++;
	end = *start;
	while (s[end] != c && s[end] != '\0')
		end++;
	oneword = ft_malloc((sizeof(char) * (end - *start) + 1), 1);
	if (!oneword)
		return (NULL);
	while (*start < end)
		oneword[i++] = s[(*start)++];
	oneword[i] = '\0';
	return (oneword);
}

static size_t	countword(char const *s, char c)
{
	size_t	counter;
	int		k;

	counter = 0;
	k = 0;
	while (*s)
	{
		if (*s != c && k == 0)
		{
			k = 1;
			counter++;
		}
		else if (*s == c)
			k = 0;
		s++;
	}
	return (counter);
}

char	**ft_split(char const *s, char c)
{
	char	**all;
	size_t	i;
	size_t	start;
	size_t	countw;

	i = 0;
	start = 0;
	if (!s)
		return (NULL);
	countw = countword(s, c);
	all = ft_malloc((sizeof(char *) * (countw + 1)), 1);
	if (!all)
		return (NULL);
	while (i < countw)
	{
		all[i] = allocsingleword(s, &start, c);
		if (!(all[i]))
			return (free_it(all));
		i++;
	}
	all[countw] = NULL;
	return (all);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*arr;

	arr = (char *)ft_malloc((ft_strlen(s1) + 1 * sizeof(char)), 1);
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
