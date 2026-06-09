/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_long_short_format_folder_at.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 18:17:30 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/09 15:08:19 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_get_long_format_folder_at(t_data *data, t_fol_at *f)
{
	t_long_format	*new_file;
	t_new_node_dir	new_data;

	if (data->opt.op_a_flag == 0
		&& (ft_strcmp(f->entry->d_name, ".") == 0
			|| ft_strcmp(f->entry->d_name, "..") == 0
			|| f->entry->d_name[0] == '.'))
		return (0);
	new_data.entry_name = f->entry->d_name;
	new_data.st = f->st;
	new_data.prnt_dir = f->p_dir_path;
	new_data.total = f->total;
	new_file = ft_new_long_node_dir(data, new_data);
	if (new_file)
		ft_long_add_back_at(&data->lng_format, new_file, data->i);
	return (1);
}

int	ft_get_short_format_folder_at(t_data *data, t_fol_at *f)
{
	t_short_format	*new_file;

	if (data->opt.op_a_flag == 0
		&& (ft_strcmp(f->entry->d_name, ".") == 0
			|| ft_strcmp(f->entry->d_name, "..") == 0
			|| f->entry->d_name[0] == '.'))
		return (0);
	new_file = ft_add_new(f->entry->d_name,
			ft_strlen(f->entry->d_name),
			f->st, f->p_dir_path);
	if (new_file)
		ft_push_back_at(&data->shrt_format, new_file, data->i);
	return (1);
}
