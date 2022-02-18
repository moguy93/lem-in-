/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 01:29:20 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/18 22:57:07 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_queue		*lm_lstnew(int room)
{
	t_queue	*new;

	if (!(new = (t_queue*)malloc(sizeof(t_queue))))
		return (NULL);
	new->index = (unsigned int)room;
	new->next = NULL;
	return (new);
}

int			lm_lst_pop(t_queue **lst)
{
	t_queue	*tmp;

	tmp = (*lst)->next;
	free(*lst);
	(*lst) = tmp;
	return (0);
}

int			lm_lst_push(t_queue **lst, int index)
{
	t_queue	*tmp;

	tmp = (*lst);
	if (!*lst)
	{
		if (!(*lst = lm_lstnew(index)))
			return (-1);
		(*lst)->next = NULL;
		return (0);
	}
	if (!(tmp = lm_lstnew(index)))
		return (-1);
	tmp->next = (*lst);
	(*lst) = tmp;
	return (0);
}

int			lm_lstdel(t_queue *queue)
{
	if (queue && queue->next)
		lm_lstdel(queue->next);
	free(queue);
	return (0);
}
