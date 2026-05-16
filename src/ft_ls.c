/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 00:35:15 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/17 00:58:17 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_count_args(t_data data)
{
	int	i;

	i = 0;
	while (data.args && data.args[i])
	{
		printf("Arg i %d is %s \n", i, data.args[i]);
		i++;
	}
	return (i);
}


int	main(int ac, char **av)
{
	t_data	data;
	int	i;

	data.paths.nbr_of_paths = 0;
	data.files.nbr_of_files = 0;
	data.opt.nbr_of_opt = 0;
	printf("check opt\n");
	if (ac > 1)
		ft_copy_args(ac, av, &data);
	if (ft_get_options_and_check_errors(ac, data.args, &data))
		return (1);
	printf("check file\n");
	ft_get_files_and_check_errors(data.args, &data);
	printf("check dir\n");
	ft_get_paths_and_check_errors(data.args, &data);
	printf("end of check dir\n");
	i = 0;

	if ((ft_count_args(data) == 0 && ac > 1) || (ac > 1 && data.opt.nbr_of_opt == ft_count_args(data)))
	{
		printf("Ls with args but all give error\n");
		return (1);
	}
	printf("counter %d %d %d\n", data.paths.nbr_of_paths, data.files.nbr_of_files, data.opt.nbr_of_opt);
	i = 0;
	while (i < data.paths.nbr_of_paths)
	{
		printf("Path data :[%d] {%s} \n", i, data.paths.path[i]);
		i++;
	}
	i = 0;
	while (i < data.files.nbr_of_files)
	{
		printf("Filename data :[%d] {%s} \n", i, data.files.file[i]);
		i++;
	}
	i = 0;
	{
		printf("options data l :[%d]\n",  data.opt.op_l_flag);
		printf("options data R :[%d]\n",  data.opt.op_R_flag);
		printf("options data a :[%d]\n",  data.opt.op_a_flag);
		printf("options data r :[%d]\n",  data.opt.op_r_flag);
		printf("options data t :[%d]\n",  data.opt.op_t_flag);
		printf("options total  :[%d]\n",  data.opt.nbr_of_opt);
		i++;
	}
	ft_start_listing(&data);
	ft_display_short_format(&data);
	return (0);
}
