/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omotyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:28:40 by omotyliu          #+#    #+#             */
/*   Updated: 2017/02/27 16:28:42 by omotyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*g_flags;
char	*g_path;

static void	check_param(void)
{
	char	*temp;

	temp = g_flags;
	while (*temp)
	{
		if (*temp != 'l' && *temp != 'R' && *temp != 'a'
			&& *temp != 'r' && *temp != 't' && *temp != '-' && *temp != 'z')
		{
			ft_printf("ft_ls: illigal option -- %c\n", *temp);
			ft_printf("usage: ft_ls [-lRartz] [file...]\n");
			exit(1);
		}
		temp++;
	}
}

t_list		*concat(int argc, char **argv)
{
	int		i;
	t_list	*arg_list;

	i = 1;
	arg_list = NULL;
	g_flags = ft_strdup("\0");
	if (argc > 1)
		while (i < argc)
		{
			if (argv[i][0] != '-')
				ft_lstadd(&arg_list, ft_lstnew(argv[i], sizeof(char) *
					ft_strlen(argv[i]) + 1));
			else
				g_flags = ft_append(g_flags, argv[i], ft_strlen(g_flags),
					ft_strlen(argv[i]));
			i++;
		}
	if (g_path == NULL && arg_list == NULL)
	{
		g_path = ft_strdup(".");
		ft_lstadd(&arg_list, ft_lstnew(g_path, ft_strlen(g_path)));
	}
	check_param();
	return (arg_list);
}
