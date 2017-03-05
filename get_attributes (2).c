/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attributes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omotyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 19:33:03 by omotyliu          #+#    #+#             */
/*   Updated: 2017/03/01 19:33:04 by omotyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char* get_file_type(struct stat item_inf) {

    char *type;
    char *result;

    type = ft_strnew(2);
    type[0] = (char) ((S_ISDIR(item_inf.st_mode)) ? 'd' : '-');
    type[0] = (char) ((S_ISBLK(item_inf.st_mode)) ? 'b' : type[0]);
    type[0] = (char) ((S_ISCHR(item_inf.st_mode)) ? 'c' : type[0]);
    type[0] = (char) ((S_ISFIFO(item_inf.st_mode)) ? 'p' : type[0]);
    type[0] = (char) ((S_ISSOCK(item_inf.st_mode)) ? 's' : type[0]);
    type[0] = (char) ((S_ISLNK(item_inf.st_mode)) ? 'l' : type[0]);
    return (type);
}

char *get_permissions(struct stat item_inf)
{
    char  *permissions;
    int atr;

    permissions = ft_strnew(10);
    permissions[0] = (char) ((item_inf.st_mode & S_IRUSR) ? 'r' : '-');
    permissions[1] = (char) ((item_inf.st_mode & S_IWUSR) ? 'w' : '-');
    permissions[2] = (char) ((item_inf.st_mode & S_IXUSR) ? 'x' : '-');
    permissions[3] = (char) ((item_inf.st_mode & S_IRGRP) ? 'r' : '-');
    permissions[4] = (char) ((item_inf.st_mode & S_IWGRP) ? 'w' : '-');
    permissions[5] = (char) ((item_inf.st_mode & S_IXGRP) ? 'x' : '-');
    permissions[6] = (char) ((item_inf.st_mode & S_IROTH) ? 'r' : '-');
    permissions[7] = (char) ((item_inf.st_mode & S_IWOTH) ? 'w' : '-');
    permissions[8] = (char) ((item_inf.st_mode & S_IXOTH) ? 'x' : '-');

    return  permissions;
}

char *get_x_atr(t_item *diritem, struct stat item_inf)
{
    ssize_t atr;
    char *path;

    path = ft_strnew(100);
    atr = listxattr(diritem->path, path, sizeof(path), 0);
    free(path);
    if (atr > 0 || !ft_strcmp(diritem->item->d_name, ".DS_Store"))
        return ft_strdup("@");
    else
        return ft_strdup(" ");
}

char* get_owner_name(struct stat item_inf)
{
    struct passwd *pw;
    char *name;

    pw = getpwuid(item_inf.st_uid);
    if (pw == NULL)
        return ft_itoa(item_inf.st_uid);
    name = ft_strdup(pw->pw_name);
    return (name);
}

char* get_group_name(struct stat item_inf)
{
    struct group *gpw;
    char *gname;

    gpw = getgrgid(item_inf.st_gid);
    if (gpw == NULL)
        return ft_itoa(item_inf.st_uid);
    gname = ft_strdup(gpw->gr_name);
    return (gname);
}
