/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omotyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:11:27 by omotyliu          #+#    #+#             */
/*   Updated: 2017/02/25 20:11:28 by omotyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int if_dir_present(t_list *list)
{
    t_item *item;

    while (list)
    {
        item = list->content;
        if (ft_strcmp(item->type, "d"))
            return (1);
        list = list->next;
    }
    return (0);
}