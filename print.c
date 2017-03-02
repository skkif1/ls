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


char *g_flags;
char *g_path;
char *g_root;

void size_padding(t_item *item, int *paddings)
{
    int temp;

    if (!ft_strcmp(item->type, "b") || !ft_strcmp(item->type, "c"))
    {
        temp = (int) (ft_strlen(item->minor_s_major));
        if (temp > paddings[3])
            paddings[3] = temp;
    }
    else
    if ((temp = (int) ft_strlen(ft_itoa(item->size))) > paddings[3])
        paddings[3] = temp;


}

static int *get_paddings(t_list *item_list)
{
    t_list *list;
    t_item *item;
    static int paddings[5];
    int temp;

        list = item_list;
    if (ft_strchr(g_flags, 'l'))
    {
        while (list) {
            item = list->content;
            if (item->n_link > paddings[0])
                paddings[0] = item->n_link;
            if ((temp = (int) ft_strlen(item->o_name)) > paddings[1])
                paddings[1] = temp;
            if ((temp = (int) ft_strlen(item->g_name)) > paddings[2])
                paddings[2] = temp;
            size_padding(item, paddings);
            list = list->next;
        }
        paddings[0] = (int) ft_strlen(ft_itoa(paddings[0]));
    }
    return paddings;
}

static void print_item_info(t_item *item, int *paddings)
{
    if (ft_strchr(g_flags, 'l'))
    {
        printf("%1s",  item->type);
        printf("%9s",   item->perm);
        printf("%1s ", item->x_atr);
        printf("%*d ", paddings[0], item->n_link);
        printf("%*s  ", paddings[1], item->o_name);
        printf("%*s  ", paddings[2], item->g_name);
        if (!ft_strcmp(item->type, "b") || !ft_strcmp(item->type, "c"))
            printf("%*s ", paddings[3], item->minor_s_major);
        else
            printf("%*d ", paddings[3], item->size);
        printf("%-12s ", item->time);
    }
        printf("%s", item->name);
        printf("\n");
}


void print_folder(t_folder *folder)
{
    t_item *item;
    t_list *ilist;
    int *paddings;
    ilist = folder->item_list;

    paddings = get_paddings(ilist);
    if (folder->folder == 0)
        return ;
    if (ft_strcmp(folder->path, g_path))
        printf("\n%s%s\n", g_root, get_folder_name(folder->path));
    if (folder->item_list == NULL)
        return ;
    if (ft_strchr(g_flags, 'l'))
        printf("total %d\n", folder->total);
    while (ilist)
    {
            item = ilist->content;
            print_item_info(item, paddings);
            ilist = ilist->next;
    }
}
