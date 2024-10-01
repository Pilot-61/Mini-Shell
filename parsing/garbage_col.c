/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_col.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:27:22 by aennaqad          #+#    #+#             */
/*   Updated: 2024/09/27 21:21:35 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_gcol	*ft_last_garbage(t_gcol *lst)
{
	t_gcol	*tmplst;

	if (!lst)
		return (NULL);
	tmplst = lst;
	while (tmplst->next != NULL)
		tmplst = tmplst->next;
	return (tmplst);
}

t_gcol	*create_node(size_t size)
{
	t_gcol	*node;

	node = malloc(sizeof(t_gcol));
	if (node == NULL)
		return (NULL);
	node->var = malloc(size);
	if (!node->var)
		return (NULL);
	node->next = NULL;
	return (node);
}

void	ft_node_add_back(t_gcol **lst, t_gcol *newa)
{
	t_gcol	*last;

	if (!lst)
		return ;
	last = *lst;
	if (last == NULL)
		*lst = newa;
	else
	{
		last = ft_last_garbage(*lst);
		last->next = newa;
	}
}

void	ft_free_all(t_gcol **lst)
{
	t_gcol	*tmp;
	t_gcol	*next;

	tmp = *lst;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp->var);
		free(tmp);
		tmp = next;
	}
	*lst = NULL;
}

void	*ft_malloc(size_t size, int type)
{
	t_gcol			*ptr;
	static t_gcol	*head;

	ptr = NULL;
	if (type == 1)
	{
		ptr = create_node(size);
		ft_node_add_back(&head, ptr);
		return (ptr->var);
	}
	else if (type == 2)
	{
		ft_free_all(&head);
		return (NULL);
	}
	return (NULL);
}
