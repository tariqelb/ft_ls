/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diplay_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:49:04 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/25 02:48:53 by tel-bouh         ###   ########.fr       */
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
        write(1, tmp->prnt_dir, ft_strlen(tmp->prnt_dir));
        write(1, " ", 1);

        write(1, tmp->permission, 10);
        write(1, " ", 1);

        ft_put_size_t(tmp->links, 1);
        write(1, " ", 1);

        write(1, tmp->user, ft_strlen(tmp->user));
        write(1, " ", 1);

        write(1, tmp->grop, ft_strlen(tmp->grop));
        write(1, " ", 1);

        ft_put_size_t(tmp->size, 1);
        write(1, " ", 1);

        write(1, tmp->time, ft_strlen(tmp->time));
        write(1, " ", 1);

        write(1, tmp->filename, ft_strlen(tmp->filename));
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

	//write(1, tmp->prnt_dir, ft_strlen(tmp->prnt_dir));
        //write(1, " ", 1);
        write(1, name, ft_strlen(name));

        if (tmp->next)
            write(1, "  ", 2);

        tmp = tmp->next;
    }

    write(1, "\n", 1);
}

void ft_display_long_format_n_data(t_data *data, int len)
{
	t_long_format	*tmp;
	int		i;

	if (!data || !data->lng_format)
	    return;

	tmp = data->lng_format;
	i = 0;
	while (tmp && i < len)
	{
	    i++;
	    tmp = tmp->next;
	}

	while (tmp)
	{
	    //write(1, tmp->prnt_dir, ft_strlen(tmp->prnt_dir));
	    //write(1, " ", 1);

	    write(1, tmp->permission, 10);
	    write(1, " ", 1);

	    ft_put_size_t(tmp->links, 1);
	    write(1, " ", 1);

	    write(1, tmp->user, ft_strlen(tmp->user));
	    write(1, " ", 1);

	    write(1, tmp->grop, ft_strlen(tmp->grop));
	    write(1, " ", 1);

	    ft_put_size_t(tmp->size, 1);
	    write(1, " ", 1);

	    write(1, tmp->time, ft_strlen(tmp->time));
	    write(1, " ", 1);

	    write(1, tmp->filename, ft_strlen(tmp->filename));
	    write(1, "\n", 1);

	    tmp = tmp->next;
	}
}
/*
** Display linked list in short format like ls
*/
void	ft_display_short_format_n_data(t_data *data, int len)
{
	t_short_format *tmp;
	char            *name;
	int		i;

	if (!data || !data->shrt_format)
	    return;

	tmp = data->shrt_format;
	i = 0;
	while (tmp && i < len)
	{
		i++;
		tmp = tmp->next;
	}
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
