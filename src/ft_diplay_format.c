/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diplay_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:49:04 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/09 15:11:34 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"
/*
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
		ft_print_padded_size(tmp->size, max_size_width);
		write(1, " ", 1);
		write(1, tmp->time, ft_strlen(tmp->time));
		write(1, " ", 1);
		if (tmp->is_dir)
		{
			write(1, "\033[94m", 5);
			write(1, tmp->filename, strlen(tmp->filename));
			write(1, "\033[0m", 4);
		}
		else
		{
			if (tmp->is_exe_or_link == 2)
			{
				write(1, "\033[36m", 5);
				write(1, tmp->filename, strlen(tmp->filename));
				write(1, "\033[0m", 4);
			}
			else if (tmp->is_exe_or_link == 1)
			{
				write(1, "\033[32m", 5);
				write(1, tmp->filename, strlen(tmp->filename));
				write(1, "\033[0m", 4);
			}
			else if (tmp->filename[0] == '.')
			{
				write(1, "\033[37m", 5);
				write(1, tmp->filename, strlen(tmp->filename));
				write(1, "\033[0m", 4);
			}
			else
				write(1, tmp->filename, ft_strlen(tmp->filename));
		}
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}*/
/*
void	ft_display_short_format(t_data *data)
{
	t_short_format	*tmp;
	char			*name;
	int				i;

	if (!data || !data->shrt_format)
		return ;
	tmp = data->shrt_format;
	i = 0;
	while (tmp)
	{
		i++;
		name = (char *)tmp->data;
		if (tmp->is_dir)
		{
			write(1, "\033[94m", 5);
			write(1, name, strlen(name));
			write(1, "\033[0m", 4);
		}
		else
		{
			if (tmp->is_exe_or_link == 2)
			{
				write(1, "\033[36m", 5);
				write(1, name, strlen(name));
				write(1, "\033[0m", 4);
			}
			else if (tmp->is_exe_or_link == 1)
			{
				write(1, "\033[32m", 5);
				write(1, name, strlen(name));
				write(1, "\033[0m", 4);
			}
			else if (name[0] == '.')
			{
				write(1, "\033[37m", 5);
				write(1, name, strlen(name));
				write(1, "\033[0m", 4);
			}
			else
				write(1, name, ft_strlen(name));
		}
		if (tmp->next)
			write(1, "  ", 2);
		tmp = tmp->next;
	}
	if (i)
		write(1, "\n", 1);
}*/
/*
void	ft_display_long_format_n_data(t_data *data, int len)
{
	t_long_format	*tmp;
	int				i;
	int				max_size_width;

	if (!data || !data->lng_format)
		return ;
	tmp = data->lng_format;
	i = 0;
	while (tmp && i < len)
	{
		i++;
		tmp = tmp->next;
	}
	max_size_width = ft_get_max_size_width(tmp);
	while (tmp)
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
		if (tmp->is_dir)
		{
			write(1, "\033[94m", 5);
			write(1, tmp->filename, strlen(tmp->filename));
			write(1, "\033[0m", 4);
		}
		else
		{
			if (tmp->is_exe_or_link == 2)
			{
				write(1, "\033[36m", 5);
				write(1, tmp->filename, strlen(tmp->filename));
				write(1, "\033[0m", 4);
			}
			else if (tmp->is_exe_or_link == 1)
			{
				write(1, "\033[32m", 5);
				write(1, tmp->filename, strlen(tmp->filename));
				write(1, "\033[0m", 4);
			}
			else if (tmp->filename[0] == '.')
			{
				write(1, "\033[37m", 5);
				write(1, tmp->filename, strlen(tmp->filename));
				write(1, "\033[0m", 4);
			}
			else
				write(1, tmp->filename, ft_strlen(tmp->filename));
		}
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}
*/
/*
void	ft_display_short_format_n_data(t_data *data, int len)
{
	t_short_format	*tmp;
	char			*name;
	int				i;
	int				k;

	if (!data || !data->shrt_format)
		return ;
	tmp = data->shrt_format;
	i = 0;
	while (tmp && i < len)
	{
		i++;
		tmp = tmp->next;
	}
	k = i;
	while (tmp)
	{
		name = (char *)tmp->data;
		if (tmp->is_dir)
		{
			write(1, "\033[94m", 5);
			write(1, name, strlen(name));
			write(1, "\033[0m", 4);
		}
		else
		{
			if (tmp->is_exe_or_link == 2)
			{
				write(1, "\033[36m", 5);
				write(1, name, strlen(name));
				write(1, "\033[0m", 4);
			}
			else if (tmp->is_exe_or_link == 1)
			{
				write(1, "\033[32m", 5);
				write(1, name, strlen(name));
				write(1, "\033[0m", 4);
			}
			else if (name[0] == '.')
			{
				write(1, "\033[37m", 5);
				write(1, name, strlen(name));
				write(1, "\033[0m", 4);
			}
			else
				write(1, name, ft_strlen(name));
		}
		if (tmp->next)
			write(1, "  ", 2);
		tmp = tmp->next;
		i++;
	}
	if (i != k)
		write(1, "\n", 1);
}
*/
/*
void	ft_display_long_format_n_to_m_data(t_data *data, int start, int end)
{
	t_long_format	*tmp;
	int				i;
	int				max_size_width;

	if (!data || !data->lng_format)
		return ;
	tmp = data->lng_format;
	i = 0;
	while (tmp && i < start)
	{
		i++;
		tmp = tmp->next;
	}
	max_size_width = ft_get_max_size_width(tmp);
	while (tmp && i < start + end)
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
		if (tmp->is_dir)
		{
			write(1, "\033[94m", 5);
			write(1, tmp->filename, strlen(tmp->filename));
			write(1, "\033[0m", 4);
		}
		else
		{
			if (tmp->is_exe_or_link == 2)
			{
				write(1, "\033[36m", 5);
				write(1, tmp->filename, strlen(tmp->filename));
				write(1, "\033[0m", 4);
			}
			else if (tmp->is_exe_or_link == 1)
			{
				write(1, "\033[32m", 5);
				write(1, tmp->filename, strlen(tmp->filename));
				write(1, "\033[0m", 4);
			}
			else if (tmp->filename[0] == '.')
			{
				write(1, "\033[37m", 5);
				write(1, tmp->filename, strlen(tmp->filename));
				write(1, "\033[0m", 4);
			}
			else
				write(1, tmp->filename, ft_strlen(tmp->filename));
		}
		write(1, "\n", 1);
		tmp = tmp->next;
		i++;
	}
}*/

/*
void	ft_display_short_format_n_to_m_data(t_data *data, int start, int end)
{
	t_short_format	*tmp;
	char			*name;
	int				i;
	int				k;

	if (!data || !data->shrt_format)
		return ;
	tmp = data->shrt_format;
	i = 0;
	while (tmp && i < start)
	{
		i++;
		tmp = tmp->next;
	}
	k = i;
	while (tmp && i < start + end)
	{
		name = (char *)tmp->data;
		if (tmp->is_dir)
		{
			write(1, "\033[94m", 5);
			write(1, name, strlen(name));
			write(1, "\033[0m", 4);
		}
		else
		{
			if (tmp->is_exe_or_link == 2)
			{
				write(1, "\033[36m", 5);
				write(1, name, strlen(name));
				write(1, "\033[0m", 4);
			}
			else if (tmp->is_exe_or_link == 1)
			{
				write(1, "\033[32m", 5);
				write(1, name, strlen(name));
				write(1, "\033[0m", 4);
			}
			else if (name[0] == '.')
			{
				write(1, "\033[37m", 5);
				write(1, name, strlen(name));
				write(1, "\033[0m", 4);
			}
			else
				write(1, name, ft_strlen(name));
		}
		if (tmp->next)
			write(1, "  ", 2);
		tmp = tmp->next;
		i++;
	}
	if (i != k)
		write(1, "\n", 1);
}*/
