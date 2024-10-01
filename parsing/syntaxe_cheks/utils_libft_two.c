/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaqad <aennaqad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:19:54 by aennaqad          #+#    #+#             */
/*   Updated: 2024/09/28 22:25:48 by aennaqad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	size_t	len;
	char	*arr;

	len = ft_strlen(s1);
	arr = (char *)ft_malloc(((len + 1) * sizeof(char)), 1);
	i = 0;
	if (!arr)
		return (NULL);
	if (len < n)
		n = len;
	while (i < n)
	{
		arr[i] = s1[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char	*ft_strjoin(char const *s1, char const *s2)
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
	joined = ft_malloc((((ft_strlen(s1) + ft_strlen(s2)) + 1)
				* sizeof(char)), 1);
	if (!joined)
		return (NULL);
	while (s1[++i])
		joined[i] = s1[i];
	while (s2[++j])
		joined[i + j] = s2[j];
	joined[i + j] = '\0';
	return (joined);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] && i < n - 1)
	{
		if ((unsigned char)s1[i] == (unsigned char)s2[i])
			i++;
		else
			break ;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	countnum(int n)
{
	int	c;

	c = 0;
	if (n == 0)
		c = 1;
	while (n != 0)
	{
		n = n / 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	int			sizen;
	char		*ptr;
	int			t;
	long long	newn;

	t = 0;
	newn = n;
	if (newn < 0)
	{
		t = 1;
		newn = -newn;
	}
	sizen = countnum(n) + t;
	ptr = ft_malloc((sizen * sizeof(char) + 1), 1);
	if (!ptr)
		return (NULL);
	ptr[sizen] = '\0';
	if (t == 1)
		ptr[0] = '-';
	while (--sizen >= t)
	{
		ptr[sizen] = (newn % 10) + '0';
		newn = newn / 10;
	}
	return (ptr);
}
