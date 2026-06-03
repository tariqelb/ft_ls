/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 00:00:14 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/03 20:43:41 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

char	ft_check_is_hiden_file(char *path_file)
{
	int	len;

	len = ft_strlen(path_file);
	while (len > 0 && path_file[len - 1] != '/')
	{
		len--;	
	}
	if (path_file[len] == '.')
		return (1);
	return (0);
}

int	ft_get_long_format(t_data *data, int f_index, struct stat st)
{
	//printf("ft_get_long_format\n");
	//[permissions] [links] [user] [group] [size] [time] [filename]
	t_long_format	*new_file;
	char		*prnt_dir;
	//if (data->opt.op_a_flag == 0 && ft_check_is_hiden_file(data->files.file[f_index]))
	//	return (0);
	prnt_dir = ft_get_dir_path(data->files.file[f_index]);
	new_file = ft_new_long_node(data, f_index, st, prnt_dir, 0);//total 0 for list files as expected
	//printf("new %s \n", new_file->filename);
	ft_long_add_back(&data->lng_format, new_file);
	return (0);
}

int	ft_get_short_format(t_data *data, int f_index, struct stat st)
{
	//printf("ft_get_short_format\n");
	t_short_format	*new_file;
	char		*prnt_dir;

	//if (data->opt.op_a_flag == 0 && ft_check_is_hiden_file(data->files.file[f_index]))
	//	return (0);
	prnt_dir = ft_get_dir_path(data->files.file[f_index]);
	new_file = ft_add_new(data->files.file[f_index], ft_strlen(data->files.file[f_index]), st, prnt_dir);
	//printf("new %s \n", new_file->data);
	ft_push_back(&data->shrt_format, new_file);	
	return (0);
}

/*
** Handle one file:
** - get metadata using lstat
** - depending on options:
**      - fill long format
**      - or short format
** - handle errors properly
*/
int	ft_list_single_file(t_data *data, int f_index)
{
	//printf("ft_list_single_file:  \n");	
	struct stat st;

	/* Step 1: call lstat on the file path */
	/* lstat returns 0 on success, -1 on error */
	if (lstat(data->files.file[f_index], &st) == -1)
	{
	    /* Step 2: if error → print error message */
	    /* perror prints: "filename: reason" */
	    perror(data->files.file[f_index]);
	    return (1);
	}

	/* Step 3: check if -l option is enabled */
	if (data->opt.op_l_flag)
	{
	    /* Step 4: fill long format structure */
	    /* NOTE: this may overwrite or reuse existing data */
	    if (ft_get_long_format(data, f_index, st))
		return (1);
	}
	else
	{
	    /* Step 5: fill short format (just filename usually) */
	    if (ft_get_short_format(data, f_index, st))
		return (1);
	}

	/* Step 6: success */
	return (0);
}

int	ft_list_files(t_data *data)
{
	int	i;
	//printf("ft_list_files nbr of files = %d\n", data->files.nbr_of_files);
	if (data->files.nbr_of_files == 0)
		return (0);
	i = 0;
	while (i < data->files.nbr_of_files)
	{
		ft_list_single_file(data, i);	
		i++;
	}
	if (data->opt.op_t_flag)
	{
		if (data->opt.op_l_flag)
			data = ft_sort_by_time_long_n_elem(data, 0, 1);
		else
			data = ft_sort_by_time_short_n_elem(data, 0, 1);
	}
	else
	{
		if (data->opt.op_l_flag)
			data = ft_sort_format_data_from_elem_n_long(data, 0);
		else
			data = ft_sort_format_data_from_elem_n_short(data, 0);
	}
	if (data->opt.op_l_flag)
		ft_display_long_format(data);
	else
		ft_display_short_format_column(data);
	if (data->paths.nbr_of_paths)
		ft_putstr_std("\n", 1);
	return (0);
}
