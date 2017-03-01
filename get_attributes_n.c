/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attributes_n.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omotyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 19:36:18 by omotyliu          #+#    #+#             */
/*   Updated: 2017/03/01 19:36:19 by omotyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char* get_modif_time(struct stat item_inf)
{
    char *time_s;
    char *temp;
    long long int perm;
    time_t current;

    current = time(&current);
    perm = current - item_inf.st_mtimespec.tv_sec;
    temp = ctime(&item_inf.st_mtimespec.tv_sec);
    if (perm < 15552000 || perm < 0)
        time_s = ft_strsub(temp, 4, 12);
    else
    {
        time_s = ft_strsub(temp, 4, 7);
        time_s = ft_append(time_s, ft_strsub(temp, 20, 24), ft_strlen(time_s), 5);
    }
    return time_s;
}

char *get_name(t_item *diritem, struct stat item_inf)
{
    char *symbol;
    char *name;

    if (S_ISLNK(item_inf.st_mode))
    {
        symbol = ft_strnew(1024);
        readlink(diritem->path, symbol, 10);
        name = ft_strdup(diritem->item->d_name);
        name = ft_append(name, " -> ", ft_strlen(name), 4);
        name = ft_append(name, symbol, ft_strlen(name), ft_strlen(symbol));
        free(symbol);
        return (name);
    }else
        return (ft_strdup(diritem->item->d_name));
}