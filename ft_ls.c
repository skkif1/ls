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

static char* get_file_type(struct stat item_inf) {

    char *type;
    char *result;

    type = ft_strnew(2);
    type[0] = (char) ((S_ISDIR(item_inf.st_mode)) ? 'd' : '-');
    type[0] = (char) ((S_ISBLK(item_inf.st_mode)) ? 'b' : type[0]);
    type[0] = (char) ((S_ISCHR(item_inf.st_mode)) ? 'c' : type[0]);
    type[0] = (char) ((S_ISFIFO(item_inf.st_mode)) ? 'p' : type[0]);
    type[0] = (char) ((S_ISSOCK(item_inf.st_mode)) ? 's' : type[0]);
    type[0] = (char) ((S_ISLNK(item_inf.st_mode)) ? 'l' : type[0]);
    result = ft_strdup(type);
    return (result);
}

static char *get_permissions(struct stat item_inf)
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
static char *get_x_atr(t_item *diritem, struct stat item_inf)
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

static char* get_owner_name(struct stat item_inf)
{
    struct passwd *pw;
    char *name;

    pw = getpwuid(item_inf.st_uid);
    if (pw == NULL)
        return ft_itoa(item_inf.st_uid);
    name = ft_strdup(pw->pw_name);
    return (name);
}

static char* get_group_name(struct stat item_inf)
{
    struct group *gpw;
    char *gname;

    gpw = getgrgid(item_inf.st_gid);
    if (gpw == NULL)
        return ft_itoa(item_inf.st_uid);
    gname = ft_strdup(gpw->gr_name);
    return (gname);
}

static char* get_modif_time(struct stat item_inf)
{
    char *time_s;
    char *temp;
    long long int perm;
    time_t current;

    current = time(&current);
    perm = current - item_inf.st_mtimespec.tv_sec;
    temp = ctime(&item_inf.st_mtimespec.tv_sec);
    if (perm < 15552000 || perm < -15552000)
        time_s = ft_strsub(temp, 4, 12);
    else
    {
        time_s = ft_strsub(temp, 4, 7);
        time_s = ft_append(time_s, ft_strsub(temp, 20, 24), ft_strlen(time_s), 5);
    }
        return time_s;
}

static char *get_name(t_item *diritem, struct stat item_inf)
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

static t_item *parse_item(t_item *diritem, int flag_a)
{
    struct stat filestat;

    lstat(diritem->path, &filestat);
    diritem->name = get_name(diritem, filestat);
    if (flag_a && diritem->name[0] == '.')
        return NULL;
    diritem->type = get_file_type(filestat);
    if (!ft_strchr(g_flags, 'l'))
        return diritem;
    diritem->perm = get_permissions(filestat);
    diritem->x_atr = get_x_atr(diritem, filestat);
    diritem->n_link = ft_itoa(filestat.st_nlink);
    diritem->o_name = get_owner_name(filestat);
    diritem->g_name = get_group_name(filestat);
    diritem->size = ft_itoa((int)filestat.st_size);
    diritem->time = get_modif_time(filestat);
    diritem->stat = filestat;
    if (!ft_strcmp(diritem->type, "b") || !ft_strcmp(diritem->type, "c"))
    {
        diritem->minor_s_major = (int *) malloc(sizeof(int) * 2);
        diritem->minor_s_major[0] = minor(filestat.st_rdev);
        diritem->minor_s_major[1] = major(filestat.st_rdev);
    }
    return diritem;
}

t_list *parse_folder(t_folder *folder_s)
{
    t_list *item_list;
    static t_item *diritem;

    item_list = NULL;
    while(1)
    {
        diritem = (t_item*)malloc(sizeof(t_item));
        if ((diritem->item = readdir(folder_s->folder)) == NULL)
            break;
        diritem->path = ft_strjoin(folder_s->path, "/");
        diritem->path = ft_append(diritem->path, diritem->item->d_name, ft_strlen(diritem->path), ft_strlen(diritem->item->d_name) );
        if (!ft_strchr(g_flags, 'a'))
            diritem = parse_item(diritem, 1);
        else
            diritem = parse_item(diritem, 0);
        if (diritem != NULL)
        ft_lstadd(&item_list, ft_lstnew(diritem, sizeof(*diritem)));
    }
    item_list = sort_list(item_list);
    return item_list;
}

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

