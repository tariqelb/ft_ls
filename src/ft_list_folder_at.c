/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_folder_at.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 02:08:59 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/30 23:41:53 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int     ft_get_short_format_folder_at(t_data *data, char *entry_name, struct stat st, char *p_dir, int at);
int     ft_get_long_format_folder_at(t_data *data, char *entry_name, struct stat st, char *p_dir, size_t total, int at);
int	ft_list_folder_long_format_at(t_data *data, char *filename, char *prnt_dir, int i);
int	ft_list_folder_short_format_at(t_data *data, char *filename, char *prnt_dir, int i);

int     ft_get_short_format_folder_at(t_data *data, char *entry_name, struct stat st, char *p_dir, int at)
{
        //printf("ft_get_short_format_folder\n");
        t_short_format  *new_file;

        if (data->opt.op_a_flag == 0
                && (ft_strcmp(entry_name, ".") == 0 || ft_strcmp(entry_name, "..") == 0 || entry_name[0] == '.' ))
                return (0);
        new_file = ft_add_new(entry_name, ft_strlen(entry_name), st, p_dir);
        ft_push_back_at(&data->shrt_format, new_file, at);
        return (1);
}

int     ft_get_long_format_folder_at(t_data *data, char *entry_name, struct stat st, char *p_dir, size_t total, int at)
{
        //[permissions] [links] [user] [group] [size] [time] [filename]
        //printf("ft_get_long_format_folder\n");
        t_long_format   *new_file;

        if (data->opt.op_a_flag == 0
                && (ft_strcmp(entry_name, ".") == 0 || ft_strcmp(entry_name, "..") == 0 || entry_name[0] == '.'))
                return (0);
        new_file = ft_new_long_node_dir(data, entry_name, st, p_dir, total);
        ft_long_add_back_at(&data->lng_format, new_file, at);
        return (1);
}

int	ft_list_folder_long_format_at(t_data *data, char *filename, char *prnt_dir, int i)
{
	//printf("ft_list_folder_long_format\n");
	DIR             *dir;
	struct dirent   *entry;
	struct stat     st;
	char            *path;
	char		*p_dir_path;
	size_t		long_len;
	int		nbr_of_elem;
	size_t		total;
	
	p_dir_path = ft_join_parrent_dir(filename, prnt_dir);
	//printf("Data : %s %s %s \n", filename, prnt_dir, p_dir_path);
	dir = opendir(p_dir_path);
	if (!dir)
	{
		free(p_dir_path);
		return (1);
	}

	nbr_of_elem = 0;
	long_len = ft_count_struct_elem_long(data);
	ft_print_folder_path(data, p_dir_path);
	if (data->opt.op_l_flag)
		total = ft_get_total(data, p_dir_path);
	
	while ((entry = readdir(dir)) != NULL)
	{
		path = ft_path_join(p_dir_path, entry->d_name);
		//printf("lstat path check : {%s} {%s} {%s}{%d}\n", p_dir_path, entry->d_name, path , i);
		if (!path)
			return (1);
		if (lstat(path, &st) == -1)
		{
			free(path);
			continue;
		}
		//if (data->opt.op_l_flag)
			nbr_of_elem += ft_get_long_format_folder_at(data, entry->d_name, st, p_dir_path, total, i);
		//else
		//	nbr_of_elem += ft_get_short_format_folder(data, entry->d_name, st, p_dir_path, total);
		free(path);
	}
	closedir(dir);
	ft_display_total(data, total);
	/*int new_long_len = ft_count_struct_elem_long(data);
	if (data->opt.op_t_flag)
		data = ft_sort_by_time_long_n_elem(data, long_len);
	else
		data = ft_sort_format_data_from_elem_n_to_m_long(data, long_len + 1, new_long_len);*/
	return (nbr_of_elem);
}

int	ft_list_folder_short_format_at(t_data *data, char *filename, char *prnt_dir, int i)
{
	//printf("ft_list_folder_short_format\n");

	DIR             *dir;
	struct dirent   *entry;
	struct stat     st;
	char            *path;
	char		*p_dir_path;
	(void) st;	
	(void) data;
	short		put_path;
	size_t		short_len;
	int		nbr_of_elem;

	put_path = 1;	
	p_dir_path = ft_join_parrent_dir(filename, prnt_dir);
	//printf("Data : %s %s %s \n", filename, prnt_dir, p_dir_path);
	dir = opendir(p_dir_path);
	if (!dir)
	{
		free(p_dir_path);
		return (1);
	}
	nbr_of_elem = 0;
	short_len = ft_count_struct_elem_short(data);
	ft_print_folder_path(data, p_dir_path);
	while ((entry = readdir(dir)) != NULL)
	{
		path = ft_path_join(p_dir_path, entry->d_name);
		//printf("lstat path check : {%s} {%s} {%s}\n", p_dir_path, entry->d_name, path );
		if (!path)
			return (1);
		if (lstat(path, &st) == -1)
		{
			free(path);
			continue;
		}
		nbr_of_elem += ft_get_short_format_folder_at(data, entry->d_name, st, p_dir_path, i);
		free(path);
	}
	closedir(dir);
	/*int new_short_len = ft_count_struct_elem_short(data);
	if (data->opt.op_t_flag)
		data = ft_sort_by_time_short_n_elem(data, short_len);
	else
		data = ft_sort_format_data_from_elem_n_to_m_short(data, short_len, new_short_len);
	*/
	return (nbr_of_elem);
}
