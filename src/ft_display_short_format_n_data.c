/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_short_format_n_data.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:59:14 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/06 19:09:11 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static t_short_format	*ft_skip_short_n(t_short_format *tmp,
				int len, int *i)
{
	while (tmp && *i < len)
	{
		(*i)++;
		tmp = tmp->next;
	}
	return (tmp);
}

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

static void	ft_print_short_list(t_short_format *tmp, int *i, int *k)
{
	char	*name;

	while (tmp)
	{
		name = (char *)tmp->data;
		ft_print_short_name(tmp, name);
		if (tmp->next)
			write(1, "  ", 2);
		tmp = tmp->next;
		(*i)++;
	}
	if (*i != *k)
		write(1, "\n", 1);
}

void	ft_display_short_format_n_data(t_data *data, int len)
{
	t_short_format	*tmp;
	int				i;
	int				k;

	if (!data || !data->shrt_format)
		return ;
	tmp = data->shrt_format;
	i = 0;
	tmp = ft_skip_short_n(tmp, len, &i);
	k = i;
	ft_print_short_list(tmp, &i, &k);
}
