/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omotyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 14:46:47 by omotyliu          #+#    #+#             */
/*   Updated: 2017/02/23 14:46:48 by omotyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*g_flags;
char	*g_path;
char	*g_root;

int				main(int argc, char **argv)
{
	DIR			*folder;
	t_list		*arg_list;

	arg_list = concat(argc, argv);
	while (arg_list)
	{
		g_path = (char*)arg_list->content;
		g_root = get_root(g_path);
		if (g_path == NULL)
			g_path = ft_strdup(".");
		if ((folder = opendir(g_path)) == NULL)
		{
			perror(ft_strjoin("ft_ls: ", g_path));
			exit(1);
		}
		closedir(folder);
		print_folder_info(g_path);
		free(arg_list->content);
		free(arg_list);
		arg_list = arg_list->next;
	}
	free(g_flags);
}
