/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omotyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 14:47:36 by omotyliu          #+#    #+#             */
/*   Updated: 2017/02/23 14:48:05 by omotyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <stdio.h>
#include <grp.h>
#include <time.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include "libft/libft.h"
#include <dirent.h>
#include "sys/stat.h"
#include "pwd.h"

typedef struct	s_item
{
    char *path;
    struct dirent *item;
    int *minor_s_major;
    char *type;
    char *perm;
    char *x_atr;
    char *n_link;
    char *o_name;
    char *g_name;
    char *size;
    char *time;
    char *name;
    struct stat stat;
    int paddings[5];
}				t_item;


typedef struct	s_folder
{
    char *path;
    t_list *item_list;
    DIR* folder;
    int total;
    char *name;
}				t_folder;

t_list *parse_folder(t_folder *folder_s);
t_list *sort_list(t_list *begin);
int if_dir_present(t_list *list);
int print_folder_info(char *path);
void print_folder(t_folder *folder);
t_list *concat(int argc, char **argv);
#endif
