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

char *g_flags;
char *g_path;


static void check_param(void)
{
    char *temp;

    temp = g_flags;
    while(*temp)
    {
        if (*temp != 'l' && *temp != 'R' && *temp != 'a'
            && *temp != 'r' && *temp != 't' && *temp != '-')
        {
            printf("ls: illigal option -- %c\n", *temp);
            printf("usage: ls [-lRartU] [file...]\n");
            exit(1);
        }
        temp++;
    }
}

t_list *concat(int argc, char **argv)
{
    int i;
    i = 1;
    t_list *arg_list;

    arg_list = NULL;
    g_flags = ft_strdup("\0");
    if (argc > 1)
     while (i < argc)
    {
        if (argv[i][0] != '-')
        {
            ft_lstadd(&arg_list, ft_lstnew(argv[i], sizeof(argv[0])));
        }else
            g_flags = ft_append(g_flags, argv[i], ft_strlen(g_flags), ft_strlen(argv[i]));
        i++;
    }
    check_param();
    return arg_list;
}
