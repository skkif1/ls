/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omotyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 21:46:32 by omotyliu          #+#    #+#             */
/*   Updated: 2017/02/24 21:46:33 by omotyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

char *g_flags;
char *g_path;

static void print_item_info(t_item *item, int total)
{
    if (ft_strchr(g_flags, 'l'))
    {
        printf("%1s",  item->type);
        printf("%9s",   item->perm);
        printf("%1s\t", item->x_atr);
        printf("%s\t", item->n_link);
        printf("%s\t", item->o_name);
        printf("%s\t", item->g_name);
        if (!ft_strcmp(item->type, "b") || !ft_strcmp(item->type, "c"))
            printf("%d\t%d\t", item->minor_s_major[1], item->minor_s_major[0]);
        else
            printf("%s\t", item->size);
        printf("%s\t", item->time);
    }
        printf("%s", item->name);
        printf("\n");
}


void print_folder(t_folder *folder)
{
    t_item *item;
    t_list *ilist;

    ilist = folder->item_list;

    if (ft_strcmp(folder->path, g_path))
        printf("\n%s\n", folder->path);
    if (ft_strchr(g_flags, 'l'))
        printf("total %d\n", folder->total);
    if (ilist != NULL)
    {
        while (ilist)
        {
            item = ilist->content;
            print_item_info(item, folder->total);
            ilist = ilist->next;
        }
    }
}

