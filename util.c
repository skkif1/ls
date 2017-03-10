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

char		*g_path;

char		*get_folder_name(char *str)
{
	char	*temp;

	temp = g_path;
	while (temp && str)
	{
		if (*temp != *str)
			return (str);
		str++;
		temp++;
	}
	return (0);
}

char		*get_root(char *str)
{
	char	*temp;
	int		i;

	temp = str;
	i = 0;
	while (*temp)
	{
		i++;
		temp++;
	}
	while (*temp != '/' && i > 0)
	{
		temp--;
		i--;
	}
	return (temp);
}

void		free_folder(t_folder *folder)
{
	t_list	*ilist;
	t_item	*item;

	ilist = folder->item_list;
	while (ilist)
	{
		item = ilist->content;
		free(item->path);
		free(item->g_name);
		free(item->name);
		free(item->o_name);
		free(item->perm);
		free(item->time);
		free(item->type);
		free(item->x_atr);
		free(item->m_s_m);
		free(ilist->content);
		free(ilist);
		ilist = ilist->next;
	}
	free(folder->path);
	if (folder->folder != NULL)
		closedir(folder->folder);
	free(folder);
}

int			not_system(char *str)
{
	if (!ft_strcmp(".", str))
		return (0);
	if (!ft_strcmp("..", str))
		return (0);
	return (1);
}
