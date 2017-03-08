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

char	*g_flags;
char	*g_path;

static t_item	*parse_item(t_item *dir)
{
	struct stat		filestat;
    char            *minaor_dev;

	lstat(dir->path, &filestat);
	dir->name = get_name(dir, filestat);
    if (!ft_strchr(g_flags, 'a') && dir->name[0] == '.')
    {
        free(dir->name);
        free(dir);
        return NULL;
    }
    dir->time = get_modif_time(filestat);
	dir->type = get_file_type(filestat);
	dir->stat = filestat;
	dir->perm = get_permissions(filestat);
	dir->x_atr = get_x_atr(dir, filestat);
	dir->o_name = get_owner_name(filestat);
	dir->g_name = get_group_name(filestat);
	dir->size = (int)filestat.st_size;
    dir->m_s_m = ft_itoa(major(filestat.st_rdev));
    dir->m_s_m = ft_append(dir->m_s_m, " ", ft_strlen(dir->m_s_m), 1);
    minaor_dev = ft_itoa(minor(filestat.st_rdev));
    dir->m_s_m = ft_append(dir->m_s_m, minaor_dev
			, ft_strlen(dir->m_s_m), ft_strlen(minaor_dev));
	free(minaor_dev);
    return (dir);
}

t_list			*parse_folder(t_folder *folder_s)
{
	t_list			*item_list;
	t_item	        *diritem;

	item_list = NULL;
    while (1)
	{
		diritem = (t_item*)malloc(sizeof(t_item));
        if ((diritem->item = readdir(folder_s->folder)) == NULL)
        {
            free(diritem);
            break;
        }
        diritem->path = ft_strjoin(folder_s->path, "/");
		diritem->path = ft_append(diritem->path, diritem->item->d_name,
			ft_strlen(diritem->path), ft_strlen(diritem->item->d_name));
        diritem = parse_item(diritem);
        if (diritem != NULL)
        {
            ft_lstadd(&item_list, ft_lstnew(diritem, sizeof(*diritem)));
            free(diritem);
        }
    }
	item_list = sort_list(item_list);
    return (item_list);
}
