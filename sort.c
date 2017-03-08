/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omotyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 20:40:47 by omotyliu          #+#    #+#             */
/*   Updated: 2017/02/24 20:40:48 by omotyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char *g_flags;

static void	order(t_list *elem, t_list *next)
{
	t_item *item;

	if (ft_strcmp(((t_item*)elem->content)->name,
		((t_item*)next->content)->name) > 0)
	{
		item = elem->content;
		elem->content = next->content;
		next->content = item;
	}
}

static void	time_order(t_list *elem, t_list *next)
{
	t_item *item;

	if (((t_item*)elem->content)->stat.st_mtimespec.tv_sec <=
			((t_item*)next->content)->stat.st_mtimespec.tv_sec)
	{
		if (((t_item*)elem->content)->stat.st_mtimespec.tv_sec ==
			((t_item*)next->content)->stat.st_mtimespec.tv_sec)
			if (((t_item*)elem->content)->stat.st_mtimespec.tv_nsec >
				((t_item*)next->content)->stat.st_mtimespec.tv_nsec)
				return ;
		item = elem->content;
		elem->content = next->content;
		next->content = item;
	}
}

static void	time_creation_order(t_list *elem, t_list *next)
{
	t_item *item;

	if (((t_item*)elem->content)->stat.st_birthtimespec.tv_sec <=
		((t_item*)next->content)->stat.st_birthtimespec.tv_sec)
	{
		if (((t_item*)elem->content)->stat.st_birthtimespec.tv_sec ==
			((t_item*)next->content)->stat.st_birthtimespec.tv_sec)
			if (((t_item*)elem->content)->stat.st_birthtimespec.tv_nsec >
				((t_item*)next->content)->stat.st_birthtimespec.tv_nsec)
				return ;
		item = elem->content;
		elem->content = next->content;
		next->content = item;
	}
}

static void	reverse(t_list **head_ref)
{
	t_list *prev;
	t_list *current;
	t_list *next;

	current = *head_ref;
	prev = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head_ref = prev;
}

t_list		*sort_list(t_list *begin)
{
	if (begin != NULL)
	{
		if (ft_strchr(g_flags, 't'))
			ft_lstsort(begin, time_order);
		else if (ft_strchr(g_flags, 'z'))
			ft_lstsort(begin, time_creation_order);
		else
			ft_lstsort(begin, order);
		if (ft_strchr(g_flags, 'r'))
			reverse(&begin);
	}
	return (begin);
}
