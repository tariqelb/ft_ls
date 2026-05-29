/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_directories.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 23:57:34 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/30 00:41:37 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_get_short_format_dir(t_data *data, char *entry_name, int d_index, struct stat st)
{
	//printf("ft_get_short_format_dir\n");
	t_short_format  *new_file;

	if (data->opt.op_a_flag == 0 
		&& (ft_strcmp(entry_name, ".") == 0 || ft_strcmp(entry_name, "..") == 0 || entry_name[0] == '.'))
		return (0);
	new_file = ft_add_new(entry_name, ft_strlen(entry_name), st, data->paths.path[d_index]);
	ft_push_back(&data->shrt_format, new_file);
	return (0);
}

int	ft_get_long_format_dir(t_data *data, char *entry_name, int d_index, struct stat st)
{
	//printf("ft_get_long_format\n");
	//[permissions] [links] [user] [group] [size] [time] [filename]
	t_long_format   *new_file;

	if (data->opt.op_a_flag == 0 
		&& (ft_strcmp(entry_name, ".") == 0 || ft_strcmp(entry_name, "..") == 0 || entry_name[0] == '.'))
		return (0);
	new_file = ft_new_long_node_dir(data, entry_name, st, data->paths.path[d_index], 0);//total
	ft_long_add_back(&data->lng_format, new_file);
	return (0);	
}

int	ft_list_dir(t_data *data, int d_index)
{
	DIR             *dir;
	struct dirent   *entry;
	struct stat     st;
	char            *path;
	size_t		total;

	total = 0;
	dir = opendir(data->paths.path[d_index]);
	if (!dir)
		return (1);
	if (data->paths.nbr_of_paths > 1)
		ft_print_folder_path(data, data->paths.path[d_index]);
	total = ft_get_total(data, data->paths.path[d_index] );
	while ((entry = readdir(dir)) != NULL)
	{
		path = ft_path_join(data->paths.path[d_index], entry->d_name);
		if (!path)
			return (1);
		if (lstat(path, &st) == -1)
		{
			free(path);
			continue;
		}
		if (data->opt.op_l_flag)
			ft_get_long_format_dir(data, entry->d_name, d_index, st);
		else
			ft_get_short_format_dir(data, entry->d_name, d_index, st);
		free(path);
	}
	closedir(dir);
	ft_display_total(data, total);
	return (0);
}

int	ft_list_directories(t_data *data)
{
	int	i;
	int	short_len;
	int	long_len;

	long_len = 0;
	short_len = 0;
	i = 0;
	int	we_reach = 0;
	while (i < data->paths.nbr_of_paths)
	{
		if (data->opt.op_l_flag)
			long_len = ft_count_struct_elem_long(data);
		else
			short_len = ft_count_struct_elem_short(data);
		ft_list_dir(data, i);
		if (data->opt.op_t_flag)
		{
			if (data->opt.op_l_flag)
				data = ft_sort_by_time_long_n_elem(data, long_len);
			else
				data = ft_sort_by_time_short_n_elem(data, short_len);
		}
		else
		{
			if (data->opt.op_l_flag)
				data = ft_sort_format_data_from_elem_n_long(data, long_len);
			else
		 		data = ft_sort_format_data_from_elem_n_short(data, short_len);
		}
		if (data->opt.op_l_flag)
			ft_display_long_format_n_data(data, long_len);
		else
			ft_display_short_format_n_data(data, short_len);
	//	printf("//---------------------------------------------------------{%d}\n", we_reach);
         //if (data->opt.op_l_flag)
         //        data = ft_sort_long_format_all_data(data);
         //else
         //        data = ft_sort_short_format_all_data(data);
         if (data->opt.op_R_flag)
         {
                 if (data->opt.op_l_flag)
                         ft_iterate_recursion_long_format(data, we_reach);
                 else
                         ft_iterate_recursion_short_format(data);
         }

		we_reach = ft_count_struct_elem_long(data);
	//	printf("//---------------------------------------------------------\n");
		//---------------------------------------------------------
		i++;
	}
	return (0); 
}
