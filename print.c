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

void			size_padding(t_item *item, int *paddings)
{
	int		temp;
	char	*temp_num;

	if ((temp = item->n_link) > paddings[0])
	{
		temp_num = ft_itoa(temp);
		paddings[0] = (int)ft_strlen(temp_num);
		free(temp_num);
	}
	if ((temp = (int)ft_strlen(item->o_name)) > paddings[1])
		paddings[1] = temp;
	if ((temp = (int)ft_strlen(item->g_name)) > paddings[2])
		paddings[2] = temp;
	temp_num = ft_itoa(item->size);
	if (!ft_strcmp(item->type, "b") || !ft_strcmp(item->type, "c"))
	{
		temp = (int)(ft_strlen(item->m_s_m));
		if (temp > paddings[3])
			paddings[3] = temp;
	}
	else if ((temp = (int)ft_strlen(temp_num)) > paddings[3])
		paddings[3] = temp;
	free(temp_num);
}

static int		*get_paddings(t_list *item_list)
{
	t_list		*list;
	t_item		*item;
	static int	paddings[5];

	list = item_list;
	if (ft_strchr(g_flags, 'l'))
	{
		while (list)
		{
			item = list->content;
			size_padding(item, paddings);
			list = list->next;
		}
	}
	return (paddings);
}

static void		print_item_info(t_item *item, int *paddings)
{
	int o_pad;
	int g_pad;

	o_pad = paddings[1] - ft_strlen(item->o_name) + 1;
	g_pad = paddings[2] - ft_strlen(item->g_name) + 1;
	if (ft_strchr(g_flags, 'l'))
	{
		ft_printf("%1s", item->type);
		ft_printf("%9s", item->perm);
		ft_printf("%1s ", item->x_atr);
		ft_printf("%*d ", paddings[0], item->n_link);
		ft_printf("%s ", item->o_name);
		while (o_pad-- > 0)
			ft_printf(" ");
		ft_printf("%s ", item->g_name);
		while (g_pad-- > 0)
			ft_printf(" ");
		if (!ft_strcmp(item->type, "b") || !ft_strcmp(item->type, "c"))
			ft_printf("%*s ", paddings[3], item->m_s_m);
		else
			ft_printf("%*d ", paddings[3], item->size);
		ft_printf("%-12s ", item->time);
	}
	ft_printf("%s\n", item->name);
}

int				print_folder(t_folder *folder)
{
	t_item	*item;
	t_list	*ilist;
	int		*paddings;

	ilist = folder->item_list;
	paddings = get_paddings(ilist);
	if (ft_strcmp(folder->path, g_path))
		ft_printf("\n%s%s:\n", g_root, get_folder_name(folder->path));
	if (folder->item_list == NULL)
		return (1);
	if (ft_strchr(g_flags, 'l'))
		ft_printf("total %d\n", folder->total);
	while (ilist)
	{
		item = ilist->content;
		if (!ft_strchr(g_flags, 'a') && item->name[0] == '.')
		{
			ilist = ilist->next;
			continue ;
		}
		print_item_info(item, paddings);
		ilist = ilist->next;
	}
	return (1);
}
