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

#include "ft_ls.h"

t_list	*g_list;
char	*g_flags;
char	*g_path;

static int			count_total(t_list *item_list)
{
	t_list	*list;
	t_item	*item;
	int		count;

	count = 0;
	list = item_list;
	while (list)
	{
		item = list->content;
		count += (int)item->stat.st_blocks;
		list = list->next;
	}
	return (count);
}

static t_folder		*get_folder_info(char *path)
{
	DIR			*folder;
	t_folder	*folder_s;
	t_list		*list;

	folder_s = (t_folder*)malloc(sizeof(t_folder));
	folder_s->path = ft_strdup(path);
	folder = opendir(path);
	folder_s->folder = folder;
	if (folder == NULL)
	{
		folder_s->item_list = NULL;
		return (folder_s);
	}
	list = parse_folder(folder_s);
	folder_s->item_list = list;
	folder_s->total = count_total(folder_s->item_list);
	return (folder_s);
}

static void			rec_print(t_list *list)
{
	t_list		*temp;
	t_folder	*folder_t;
	char		*error;

	temp = list;
	while (temp)
	{
		folder_t = temp->content;
		if (folder_t->folder == 0 && opendir(folder_t->path) == NULL)
		{
			error = ft_strjoin("ft_ls: ", get_folder_name(folder_t->path));
			ft_printf("\n%s:", folder_t->path);
			ft_printf("\n%s: ", error);
			ft_printf("%s\n", strerror(errno));
			free(error);
		}
		if (folder_t->folder != 0)
			print_folder(folder_t);
		temp = temp->next;
	}
}

static void			print_recurent(char *path)
{
	t_item		*item;
	t_folder	*folder_t;
	t_list		*list;

	folder_t = get_folder_info(path);
	list = (t_list*)malloc(sizeof(t_list));
	list->content = folder_t;
	list->next = NULL;
	list->content_size = sizeof(folder_t);
	ft_lstadd_end(&g_list, list);
	list = folder_t->item_list;
	while (list)
	{
		item = list->content;
		if (!ft_strcmp(item->type, "d") && not_system(item->name))
			print_recurent(item->path);
		list = list->next;
	}
	rec_print(g_list);
}

int					print_folder_info(char *path)
{
	t_folder	*folder_s;
	t_list		*temp;

	if (ft_strchr(g_flags, 'R'))
	{
		print_recurent(path);
		while (g_list)
		{
			folder_s = g_list->content;
			free_folder(folder_s);
			temp = g_list->next;
			free(g_list);
			g_list = temp;
		}
	}
	else
	{
		folder_s = get_folder_info(path);
		if (folder_s->folder != 0)
			print_folder(folder_s);
		free_folder(folder_s);
	}
	return (0);
}
