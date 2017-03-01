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

char *g_flags;
char *g_path;

int main (int argc, char **argv)
{
    t_folder *folder_s;
    DIR* folder;
    t_list *arg_list;
    arg_list = concat(argc, argv);
    while(arg_list)
    {
        g_path = (char*)arg_list->content;
        if (g_path == NULL)
            g_path = ft_strdup(".");

        folder = opendir(g_path);
        if (folder == NULL) {
            perror(ft_strjoin("ls: ", g_path));
            exit(1);
        }
        closedir(folder);
        print_folder_info(g_path);
        arg_list = arg_list->next;
    }
}

