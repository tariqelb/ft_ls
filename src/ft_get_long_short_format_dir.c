/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_long_short_format_dir.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 23:30:33 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/06 23:36:09 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_get_short_format_dir(t_data *data, char *entry_name,
		int d_index, struct stat st)
{
	t_short_format	*new_file;

	if (data->opt.op_a_flag == 0 && (ft_strcmp(entry_name, ".") == 0
			|| ft_strcmp(entry_name, "..") == 0
			|| entry_name[0] == '.'))
		return (0);
	new_file = ft_add_new(entry_name, ft_strlen(entry_name),
			st, data->paths.path[d_index]);
	if (new_file)
		ft_push_back(&data->shrt_format, new_file);
	return (0);
}

int	ft_get_long_format_dir(t_data *data, char *entry_name,
		int d_index, struct stat st)
{
	t_long_format	*new_file;
	t_new_node_dir	new_data;

	if (data->opt.op_a_flag == 0 && (ft_strcmp(entry_name, ".") == 0
			|| ft_strcmp(entry_name, "..") == 0
			|| entry_name[0] == '.'))
		return (0);
	new_data.entry_name = entry_name;
	new_data.st = st;
	new_data.prnt_dir = data->paths.path[d_index];
	new_data.total = 0;
	new_file = ft_new_long_node_dir(data, new_data);
	if (new_file)
		ft_long_add_back(&data->lng_format, new_file);
	return (0);
}
