/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 22:49:02 by mes-salh          #+#    #+#             */
/*   Updated: 2024/09/27 01:22:35 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_strcpy(char *dst, char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

void	ft_strcat(char *dst, const char *src)
{
	while (*dst)
		dst++;
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

int	command_count(t_cmd *cmd_list)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmd_list;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

bool	is_delimiter(char c, const char *delim)
{
	int	i;

	i = 0;
	while (delim[i] != '\0')
	{
		if (c == delim[i])
			return (true);
		i++;
	}
	return (false);
}

char	*my_split(char *str, const char *delim)
{
	static char	*input = NULL;
	char		*token_start;

	if (str != NULL)
		input = str;
	if (input == NULL)
		return (NULL);
	while (*input != '\0' && is_delimiter(*input, delim))
		input++;
	if (*input == '\0')
		return (NULL);
	token_start = input;
	while (*input != '\0' && !is_delimiter(*input, delim))
		input++;
	if (*input != '\0')
	{
		*input = '\0';
		input++;
	}
	return (token_start);
}
