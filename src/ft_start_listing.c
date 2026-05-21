/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_listing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 23:30:34 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/21 03:37:04 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"


int	ft_iterate_recursion_long_format(t_data *data)
{
	//printf("ft_iterate_recursion_long_format\n");
	int	i;
	int	len;
	t_long_format *temp;

	temp = data->lng_format;
	len = ft_count_struct_elem_long(data); 
	i = 0;
	while (i < len)
	{
		//printf("Is dir %d, i %d, len %d  file %s\n", temp->is_dir, i, len, temp->filename);
		if (data->lng_format->is_dir == 0)
		//if (temp->is_dir == 0)
			ft_list_folder_long_format(data, temp->filename, temp->prnt_dir);
		len = ft_count_struct_elem_long(data);
		temp = temp->next;
		i++;
	}
	return (0);
}

int	ft_iterate_recursion_short_format(t_data *data)
{
	//printf("ft_iterate_recursion_short_format\n");
	int	i;
	int	len;
	t_short_format *temp;

	temp = data->shrt_format;
	len = ft_count_struct_elem_short(data); 
	i = 0;
	while (i < len)
	{
		//printf("Is dir %d, i %d, len %d  file %s\n", temp->is_dir, i, len, temp->filename);
		if (data->shrt_format->is_dir == 0)
		//if (temp->is_dir == 0)
			ft_list_folder_short_format(data, temp->data, temp->prnt_dir);
		len = ft_count_struct_elem_short(data);
		temp = temp->next;
		i++;
	}
	return (0);
}

int	ft_start_listing(t_data *data)
{
	//printf("ft_start_listing\n");
	//ls start listing file the dirs
	printf("Start file listing       #-------------------------\n");
	ft_list_files(data);
	printf("End file listing         #---------------------------\n");
	printf("Start listing to dirs     ---------------------------\n");
	ft_list_directories(data);
	printf("End start listing to dirs ---------------------------\n");
	printf("Start recursion listing to dirs     ---------------------------\n");
	if (data->opt.op_R_flag)
	{
		if (data->opt.op_l_flag)
			ft_iterate_recursion_long_format(data);
		else
			ft_iterate_recursion_short_format(data);	
	}
	printf("End recursion listing to dirs     ---------------------------\n");
	return (0);
}
