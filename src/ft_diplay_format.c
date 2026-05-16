/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diplay_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:49:04 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/17 00:54:45 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

/*
** Display linked list in long format like ls -l
*/
void ft_display_long_format(t_data *data)
{
    t_long_format *tmp;

    if (!data || !data->lng_format)
        return;

    tmp = data->lng_format;

    while (tmp)
    {
        // permissions
        write(1, tmp->permission, 10);
        write(1, " ", 1);

        // links
        printf("%zu ", tmp->links);

        // user
        write(1, tmp->user, ft_strlen(tmp->user));
        write(1, " ", 1);

        // group
        write(1, tmp->grop, ft_strlen(tmp->grop));
        write(1, " ", 1);

        // size
        printf("%zu ", tmp->size);

        // time
        write(1, tmp->time, ft_strlen(tmp->time));
        write(1, " ", 1);

        // filename
        write(1, tmp->filename, ft_strlen(tmp->filename));

        // newline
        write(1, "\n", 1);

        tmp = tmp->next;
    }
}

/*
** Display linked list in short format like ls
*/
void	ft_display_short_format(t_data *data)
{
    t_short_format *tmp;
    char            *name;

    if (!data || !data->shrt_format)
        return;

    tmp = data->shrt_format;

    while (tmp)
    {
        name = (char *)tmp->data;

        write(1, name, ft_strlen(name));

        if (tmp->next)
            write(1, "  ", 2);

        tmp = tmp->next;
    }

    write(1, "\n", 1);
}
