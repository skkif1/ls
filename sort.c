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

static void order(t_list *elem)
{
    t_item *item;
    t_item *next;

    item = elem->content;
    if (elem->next)
    next = elem->next->content;
    else
        return ;
    if (ft_strcmp(item->name, next->name) > 0)
    {
        elem->content = next;
        elem->next->content = item;
    }
}

static void rev_order(t_list *elem)
{
    t_item *item;
    t_item *next;

    item = elem->content;
    if (elem->next)
    next = elem->next->content;
    else
        return ;
    if (ft_strcmp(item->name, next->name) < 0)
    {
        elem->content = next;
        elem->next->content = item;
    }
}

static void time_order(t_list *elem)
{
    t_item *item;
    t_item *next;

    item = elem->content;
    if (elem->next)
    next = elem->next->content;
    else
        return ;
    if (item->stat.st_mtimespec.tv_sec < next->stat.st_mtimespec.tv_sec)
    {
        elem->content = next;
        elem->next->content = item;
    }
}

static void time_creation_order(t_list *elem)
{
    t_item *item;
    t_item *next;

    item = elem->content;
    if (elem->next)
    next = elem->next->content;
    else
        return ;
    if (item->stat.st_birthtimespec.tv_sec < next->stat.st_birthtimespec.tv_sec)
    {
        elem->content = next;
        elem->next->content = item;
    }
}

t_list *sort_list(t_list *begin)
{
    void (*f)(t_list *elem);
    t_list *temp;

    if (ft_strchr(g_flags, 't'))
        f = time_order;
    if (ft_strchr(g_flags, 'r'))
        f = rev_order;
    if (ft_strchr(g_flags, 'U'))
        f = time_creation_order;
    else
        f = order;
    temp = begin;
    if (temp != NULL)
    while (temp->next != NULL)
    {
        ft_lstiter(begin, f);
        temp = temp->next;
    }
    return begin;
}