/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omotyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:26:06 by omotyliu          #+#    #+#             */
/*   Updated: 2017/02/25 20:26:08 by omotyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "ft_ls.h"
#include <errno.h>


t_list *g_list;
char *g_flags;
char *g_path;

static int count_total(t_list *item_list)
{
    t_list *list;
    t_item *item;
    int count;

    count = 0;
    list = item_list;
    while (list)
    {
        item = list->content;
        int temp = (int)item->stat.st_blocks;
        count += (int)item->stat.st_blocks;
        list = list->next;
    }
    return count;
}
static t_folder *get_folder_info(char *path)
{
    t_folder *folder_s;
    DIR *folder;

    folder_s = (t_folder*)malloc(sizeof(t_folder));
    folder_s->path = path;
    folder = opendir(path);
    folder_s->folder = folder;
    if (folder == NULL)
        return folder_s;
    t_list *list = parse_folder(folder_s);
    folder_s->item_list = list;
    folder_s->total = count_total(folder_s->item_list);
    return folder_s;
}


static int not_system(char *str)
{
    if (!ft_strcmp(".", str))
        return (0);
    if (!ft_strcmp("..", str))
        return (0);
    return (1);
}

static void print_recurent(char *path)
{
    t_item *item;
    t_folder *folder_t;
    t_list *list;

    folder_t = get_folder_info(path);
    ft_lstadd_end(&g_list, ft_lstnew(folder_t, sizeof(*folder_t)));
    list = folder_t->item_list;
    while (list)
    {
        item = list->content;
        if (!ft_strcmp(item->type, "d") && not_system(item->name))
            print_recurent(item->path);
        list = list->next;
    }
    while (g_list)
    {
        folder_t = g_list->content;
        if (folder_t->folder == 0)
        {
            opendir(folder_t->path);
            printf("\n%s %s\n", ft_strjoin("cd: ", path), strerror(errno));
        }
        if (folder_t->item_list != NULL)
            print_folder(folder_t);
        g_list = g_list->next;
    }
}

int print_folder_info(char *path)
{
    t_folder *folder_s;


    if (ft_strchr(g_flags, 'R'))
    {
        print_recurent(path);
    }else
    {
        folder_s = get_folder_info(path);
        print_folder(folder_s);
    }
    return 0;
}
