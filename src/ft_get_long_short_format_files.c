/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_long_short_format_files.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 17:34:10 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/07 17:48:17 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_get_long_format(t_data *data, int f_index, struct stat st)
{
	t_long_format	*new_file;
	char			*prnt_dir;

	prnt_dir = ft_get_dir_path(data->files.file[f_index]);
	new_file = ft_new_long_node(data, f_index, st, prnt_dir);
	if (new_file)
		ft_long_add_back(&data->lng_format, new_file);
	free(prnt_dir);
	return (0);
}

int	ft_get_short_format(t_data *data, int f_index, struct stat st)
{
	t_short_format	*new_file;
	char			*prnt_dir;

	prnt_dir = ft_get_dir_path(data->files.file[f_index]);
	new_file = ft_add_new(data->files.file[f_index],
			ft_strlen(data->files.file[f_index]), st, prnt_dir);
	if (new_file)
		ft_push_back(&data->shrt_format, new_file);
	free(prnt_dir);
	return (0);
}
