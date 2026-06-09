/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_short_format.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:04:28 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/06 19:10:47 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static void	ft_print_short_name_two(t_short_format *tmp, char *name)
{
	(void) tmp;
	if (name[0] == '.')
	{
		write(1, "\033[37m", 5);
		write(1, name, ft_strlen(name));
		write(1, "\033[0m", 4);
	}
	else
		write(1, name, ft_strlen(name));
}

static void	ft_print_short_name(t_short_format *tmp, char *name)
{
	if (tmp->is_dir)
	{
		write(1, "\033[94m", 5);
		write(1, name, ft_strlen(name));
		write(1, "\033[0m", 4);
	}
	else if (tmp->is_exe_or_link == 2)
	{
		write(1, "\033[36m", 5);
		write(1, name, ft_strlen(name));
		write(1, "\033[0m", 4);
	}
	else if (tmp->is_exe_or_link == 1)
	{
		write(1, "\033[32m", 5);
		write(1, name, ft_strlen(name));
		write(1, "\033[0m", 4);
	}
	else
		ft_print_short_name_two(tmp, name);
}

static void	ft_display_short_loop(t_short_format *tmp, int *i)
{
	char	*name;

	while (tmp)
	{
		(*i)++;
		name = (char *)tmp->data;
		ft_print_short_name(tmp, name);
		if (tmp->next)
			write(1, "  ", 2);
		tmp = tmp->next;
	}
}

void	ft_display_short_format(t_data *data)
{
	t_short_format	*tmp;
	int				i;

	if (!data || !data->shrt_format)
		return ;
	tmp = data->shrt_format;
	i = 0;
	ft_display_short_loop(tmp, &i);
	if (i)
		write(1, "\n", 1);
}
