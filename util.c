/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omotyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:11:27 by omotyliu          #+#    #+#             */
/*   Updated: 2017/02/25 20:11:28 by omotyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char *g_path;
static int flag;
t_list *g_temp;

char *get_folder_name(char *str)
{
    char *temp;

    temp = g_path;

    while(temp && str)
    {
        if(*temp != *str)
        {
            return str;
        }
        str++;
        temp++;
    }
    return 0;
}

char *get_root(char *str)
{
    char *temp;
    int i;

    temp = str;
    i = 0;
    while(*temp)
    {
        i++;
        temp++;
    }
    while(*temp != '/' && i > 0)
    {
        temp--;
        i--;
    }
    return temp;
}

static void del_item(t_item* item)
{
    free(item->g_name);
    free(item->o_name);
    free(item->name);
    free(item->perm);
    free(item->time);
    free(item->type);
    free(item->path);
    free(item->x_atr);
    free(item);
}

void free_folder(void* f_folder, size_t size)
{
    t_folder *folder;
    t_list *item_l;

    folder = f_folder;
    item_l = folder->item_list;
    free(folder->folder);
    free(folder->path);
    while(item_l)
    {
        del_item(item_l->content);
        item_l = item_l->next;
    }
      free(folder);
}

void get_header(t_list *g_list)
{
    if (!flag)
        g_temp = g_list;
    flag = 1;
}
