/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_short_format_n_to_m_data.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:31:55 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/06 18:56:47 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static t_short_format	*ft_skip_to_start(t_short_format *tmp,
				int start, int *i)
{
	while (tmp && *i < start)
	{
		(*i)++;
		tmp = tmp->next;
	}
	return (tmp);
}

static void	ft_print_colored_name_two(t_short_format *tmp, char *name)
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

static void	ft_print_colored_name(t_short_format *tmp, char *name)
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
		ft_print_colored_name_two(tmp, name);
}

static int	ft_display_range(t_short_format *tmp, int start, int end, int i)
{
	int		k;
	char	*name;

	k = i;
	while (tmp && i < start + end)
	{
		name = (char *)tmp->data;
		ft_print_colored_name(tmp, name);
		if (tmp->next)
			write(1, "  ", 2);
		tmp = tmp->next;
		i++;
	}
	if (i != k)
		write(1, "\n", 1);
	return (0);
}

void	ft_display_short_format_n_to_m_data(t_data *data, int start, int end)
{
	t_short_format	*tmp;
	int				i;

	if (!data || !data->shrt_format)
		return ;
	tmp = data->shrt_format;
	i = 0;
	tmp = ft_skip_to_start(tmp, start, &i);
	ft_display_range(tmp, start, end, i);
}
