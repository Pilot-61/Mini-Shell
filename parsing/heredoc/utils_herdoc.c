/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_herdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:23:02 by aennaqad          #+#    #+#             */
/*   Updated: 2024/09/27 21:21:52 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_herdoc	*ft_last_her(t_herdoc *lst)
{
	t_herdoc	*tmplst;

	if (!lst)
		return (NULL);
	tmplst = lst;
	while (tmplst->next != NULL)
	{
		tmplst = tmplst->next;
	}
	return (tmplst);
}

t_herdoc	*create_herdoc_node(char **_EOF)
{
	t_herdoc	*node;

	node = ft_malloc((sizeof(t_herdoc)), 1);
	if (node == NULL)
		return (NULL);
	node->_eofs = _EOF;
	node->next = NULL;
	return (node);
}

void	ft_her_add_back(t_herdoc **lst, t_herdoc *newa)
{
	t_herdoc	*last;

	if (!lst)
		return ;
	last = *lst;
	if (last == NULL)
		*lst = newa;
	else
	{
		last = ft_last_her(*lst);
		last->next = newa;
	}
}
