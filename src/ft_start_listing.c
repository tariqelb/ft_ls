/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_listing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 23:30:34 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/01 01:09:18 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

t_long_format	*ft_iter_till_new_data_long(t_data *data, int we_reach)
{
	int i = 0;
	t_long_format *tmp;

	tmp = data->lng_format;
	while (i < we_reach && tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

t_short_format	*ft_iter_till_new_data_short(t_data *data, int we_reach)
{
	int i = 0;
	t_short_format *tmp;

	tmp = data->shrt_format;
	while (i < we_reach && tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}


int	ft_iterate_recursion_long_format(t_data *data, int we_reach)
{
	//printf("ft_iterate_recursion_long_format\n");
	int	i;
	int	len;
	t_long_format *temp;

	//temp = data->lng_format;
	temp = ft_iter_till_new_data_long(data, we_reach);
	len = ft_count_struct_elem_long(data); 
	i = 0;
	i = we_reach;
	while (i < len)
	{
		//printf("Is dir %d, i %d, len %d  file %s\n", temp->is_dir, i, len, temp->filename);
		int	nbr_of_elem = 0;
		if (temp->is_dir == 1  && (ft_strcmp(temp->filename, ".") != 0 && ft_strcmp(temp->filename, "..") != 0))
		{
			//nbr_of_elem = ft_list_folder_long_format(data, temp->filename, temp->prnt_dir);
			len = ft_count_struct_elem_long(data);
			nbr_of_elem = ft_list_folder_long_format_at(data, temp->filename, temp->prnt_dir, i);
			//len = ft_count_struct_elem_long(data);
			//printf("____before %d [%d]******************************************************\n", len , nbr_of_elem);
			//ft_display_long_format(data);
			//printf("____before %d [%d]******************************************************\n", len , nbr_of_elem);
			data = ft_sort_format_data_from_elem_n_to_m_long(data, i + 1, nbr_of_elem);
			ft_display_long_format_n_to_m_data(data, i + 1 , nbr_of_elem);
			//exit(1);
			//printf("____after******************************************************\n");
			len = ft_count_struct_elem_long(data); 

			//printf("inside Is dir %d, i %d, len %d  file %s\n", temp->is_dir, i, len, temp->filename);
		}
		//printf("after temp iter recr -------------------[%s]\n", temp->filename);
		temp = temp->next;
		i++;
	}
	return (0);
}

int	ft_iterate_recursion_short_format(t_data *data, int we_reach)
{
	//printf("ft_iterate_recursion_short_format\n");
	int	i;
	int	len;
	t_short_format *temp;

	//temp = data->shrt_format;
	temp = ft_iter_till_new_data_short(data, we_reach);
	len = ft_count_struct_elem_short(data); 
	i = 0;
	i = we_reach;
	while (i < len)
	{
		//printf("Is dir %d, i %d, len %d  file %s\n", temp->is_dir, i, len, temp->data);
		int	nbr_of_elem = 0;
		if (temp->is_dir == 1 && (ft_strcmp(temp->data, ".") != 0 && ft_strcmp(temp->data, "..") != 0))
		{
			len = ft_count_struct_elem_short(data);
			nbr_of_elem = ft_list_folder_short_format_at(data, temp->data, temp->prnt_dir, i);
			//len = ft_count_struct_elem_short(data);
			//printf("____before %d [%d]******************************************************\n", len , nbr_of_elem);
			//ft_display_short_format(data);
			//printf("____before %d [%d]******************************************************\n", len , nbr_of_elem);
			if (data->opt.op_t_flag && data->opt.op_l_flag)
				data = ft_sort_by_time_long_n_to_m_elem(data, i + 1, nbr_of_elem);
			else if (data->opt.op_t_flag && data->opt.op_l_flag == 0)
				data = ft_sort_by_time_short_n_to_m_elem(data, i + 1, nbr_of_elem);
			else
				data = ft_sort_format_data_from_elem_n_to_m_short(data, i + 1, nbr_of_elem);
			ft_display_short_format_n_to_m_data(data, i + 1, nbr_of_elem);
		//	printf("____after******************************************************\n");
			len = ft_count_struct_elem_short(data); 
		//printf("inside Is dir %d, i %d, len %d  file %s\n", temp->is_dir, i, len, temp->data);
		}
		//printf("after temp iter recr -------------------[%s]\n", temp->filename);
		temp = temp->next;
		i++;
	}
	return (0);
}

int	ft_start_listing(t_data *data)
{
	//printf("ft_start_listing\n");
	//ls start listing file the dirs
	//printf("Start file listing       #-------------------------\n");
	ft_list_files(data);
	//printf("End file listing         #---------------------------\n");
	//printf("Start listing to dirs     ---------------------------\n");
	ft_list_directories(data);
	//printf("End start listing to dirs ---------------------------\n");
	//printf("Start recursion listing to dirs     ---------------------------\n");
	/*	
	if (data->opt.op_l_flag)
		data = ft_sort_long_format_all_data(data);
	else
		data = ft_sort_short_format_all_data(data);
	if (data->opt.op_R_flag)
	{
		if (data->opt.op_l_flag)
			ft_iterate_recursion_long_format(data);
		else
			ft_iterate_recursion_short_format(data);	
	}
	*/
	//printf("End recursion listing to dirs     ---------------------------\n");
	return (0);
}
