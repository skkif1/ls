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
    char *minor_s_major;
    char *type;
    char *perm;
    char *x_atr;
    int   n_link;
    char *o_name;
    char *g_name;
    int   size;
    char *time;
    char *name;
    struct stat stat;
}				t_item;


typedef struct	s_folder
{
    char *path;
    t_list *item_list;
    DIR* folder;
    int total;
}				t_folder;

t_list *parse_folder(t_folder *folder_s);
t_list *sort_list(t_list *begin);
int if_dir_present(t_list *list);
int print_folder_info(char *path);
void print_folder(t_folder *folder);
t_list *concat(int argc, char **argv);
char* get_file_type(struct stat item_inf);
char *get_permissions(struct stat item_inf);
char *get_x_atr(t_item *diritem, struct stat item_inf);
char* get_owner_name(struct stat item_inf);
char* get_group_name(struct stat item_inf);
char *get_name(t_item *diritem, struct stat item_inf);
char* get_modif_time(struct stat item_inf);
char *get_folder_name(char *str);
char *get_root(char *str);
void free_folder(void* f_folder, size_t size);
void get_header(t_list *g_list);



#endif
