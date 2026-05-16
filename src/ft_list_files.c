/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 00:00:14 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/17 00:44:10 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_get_long_format(t_data *data, int f_index, struct stat st)
{
	printf("ft_get_long_format\n");
	//[permissions] [links] [user] [group] [size] [time] [filename]
	t_long_format	*new_file;

	new_file = ft_new_long_node(data, f_index, st);
	ft_long_add_back(&data->lng_format, new_file);
	return (0);
}

int	ft_get_short_format(t_data *data, int f_index)
{
	printf("ft_get_short_format\n");
	t_short_format	*new_file;
	
	new_file = ft_add_new(data->files.file[f_index], ft_strlen(data->files.file[f_index]));
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
	printf("ft_list_single_file:  \n");	
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
	    if (ft_get_short_format(data, f_index))
		return (1);
	}

	/* Step 6: success */
	return (0);
}

int	ft_list_files(t_data *data)
{
	int	i;

	printf("ft_list_files nbr of files = %d\n", data->files.nbr_of_files);
	if (data->files.nbr_of_files == 0)
		return (0);
	i = 0;
	while (i < data->files.nbr_of_files)
	{
		ft_list_single_file(data, i);	
		i++;
	}
	return (0);
}
