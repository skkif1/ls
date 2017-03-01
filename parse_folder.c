/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_folder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omotyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 19:19:03 by omotyliu          #+#    #+#             */
/*   Updated: 2017/03/01 19:19:05 by omotyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char *g_flags;
char *g_path;

static t_item *parse_item(t_item *diritem, int flag_a)
{
    struct stat filestat;

    lstat(diritem->path, &filestat);
    diritem->name = get_name(diritem, filestat);
    if (flag_a && diritem->name[0] == '.')
        return NULL;
    diritem->type = get_file_type(filestat);
    if (!ft_strchr(g_flags, 'l'))
        return diritem;
    diritem->perm = get_permissions(filestat);
    diritem->x_atr = get_x_atr(diritem, filestat);
    diritem->n_link = filestat.st_nlink;
    diritem->o_name = get_owner_name(filestat);
    diritem->g_name = get_group_name(filestat);
    diritem->size =  (int)filestat.st_size;
    diritem->time =  get_modif_time(filestat);
    diritem->stat = filestat;
    if (!ft_strcmp(diritem->type, "b") || !ft_strcmp(diritem->type, "c"))
    {
        diritem->minor_s_major = ft_itoa(major(filestat.st_rdev));
        diritem->minor_s_major = ft_append(diritem->minor_s_major, " ", ft_strlen(diritem->minor_s_major), 1);
        diritem->minor_s_major = ft_append(diritem->minor_s_major, ft_itoa(minor(filestat.st_rdev)), ft_strlen(diritem->minor_s_major), ft_strlen(ft_itoa(minor(filestat.st_rdev))));
    }
    return diritem;
}


t_list *parse_folder(t_folder *folder_s)
{
    t_list *item_list;
    static t_item *diritem;

    item_list = NULL;
    while(1)
    {
        diritem = (t_item*)malloc(sizeof(t_item));
        if ((diritem->item = readdir(folder_s->folder)) == NULL)
            break;
        diritem->path = ft_strjoin(folder_s->path, "/");
        diritem->path = ft_append(diritem->path, diritem->item->d_name, ft_strlen(diritem->path), ft_strlen(diritem->item->d_name) );
        if (!ft_strchr(g_flags, 'a'))
            diritem = parse_item(diritem, 1);
        else
            diritem = parse_item(diritem, 0);
        if (diritem != NULL)
            ft_lstadd(&item_list, ft_lstnew(diritem, sizeof(*diritem)));
    }
    item_list = sort_list(item_list);
    return item_list;
}
