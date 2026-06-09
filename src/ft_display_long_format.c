/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_long_format.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:07:35 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/09 23:24:21 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static void	ft_print_long_name_two(t_long_format *tmp)
{
	if (tmp->filename[0] == '.')
	{
		write(1, "\033[37m", 5);
		write(1, tmp->filename, ft_strlen(tmp->filename));
		write(1, "\033[0m", 4);
	}
	else
		write(1, tmp->filename, ft_strlen(tmp->filename));
}

static void	ft_print_long_name(t_long_format *tmp)
{
	if (tmp->is_dir)
	{
		write(1, "\033[94m", 5);
		write(1, tmp->filename, ft_strlen(tmp->filename));
		write(1, "\033[0m", 4);
	}
	else if (tmp->is_exe_or_link == 2)
	{
		write(1, "\033[36m", 5);
		write(1, tmp->filename, ft_strlen(tmp->filename));
		write(1, " -> ", 4);
		write(1, tmp->link_file, ft_strlen(tmp->link_file));
		write(1, "\033[0m", 4);
	}
	else if (tmp->is_exe_or_link == 1)
	{
		write(1, "\033[32m", 5);
		write(1, tmp->filename, ft_strlen(tmp->filename));
		write(1, "\033[0m", 4);
	}
	else
		ft_print_long_name_two(tmp);
}

static void	ft_print_long_line(t_long_format *tmp, int max_size_width)
{
	write(1, tmp->permission, 10);
	write(1, " ", 1);
	ft_put_size_t(tmp->links, 1);
	write(1, " ", 1);
	write(1, tmp->user, ft_strlen(tmp->user));
	write(1, " ", 1);
	write(1, tmp->grop, ft_strlen(tmp->grop));
	write(1, " ", 1);
	ft_print_padded_size(tmp->size, max_size_width);
	write(1, " ", 1);
	write(1, tmp->time, ft_strlen(tmp->time));
	write(1, " ", 1);
	ft_print_long_name(tmp);
	write(1, "\n", 1);
}

void	ft_display_long_format(t_data *data)
{
	t_long_format	*tmp;
	int				max_size_width;

	if (!data || !data->lng_format)
		return ;
	tmp = data->lng_format;
	max_size_width = ft_get_max_size_width(data->lng_format);
	while (tmp)
	{
		ft_print_long_line(tmp, max_size_width);
		tmp = tmp->next;
	}
}
