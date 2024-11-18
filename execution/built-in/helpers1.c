/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 23:55:15 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/04 21:23:31 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	len;
	char	*new;

	new = (char *)s1;
	if (!s1 || !set)
		return (0);
	while (*s1 != '\0' && ft_strchr(set,*s1) != 0)
		s1++;
	len = ft_strlen(s1);
	if (len != 0)
		while (ft_strchr(set, s1[len]) != 0)
			len--;
	new = ft_substr((char *)s1, 0, len + 1);
	return (new);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	strlen;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	strlen = ft_strlen(s);
	if (start > strlen)
		start = strlen;
	if (len > strlen - start)
		len = strlen - start;
	sub = (char *)ft_malloc((len + 1), 1);
	if (!sub)
		return (NULL);
	while (start < strlen && len > i)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f');
}

int	ft_strcmp(char	*s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}
