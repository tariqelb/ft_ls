/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 00:35:15 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/30 00:03:02 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_count_args(t_data data)
{
	//printf("ft_count_args\n");
	int	i;
	int	args;

	i = 0;
	args = 0;
	while (data.args && data.args[i] != NULL)
	{
	//	printf("Arg i %d is %s \n", i, data.args[i]);
		if (data.args[i][0] != '-')
			args++;
		i++;
	}
	//printf("args %d\n", args);
	return (args);
}

int	ft_its_only_options(t_data *data)
{
	int 	i;
	int	flag;

	flag = 0;
	i = 0;
	while (data->args && data->args[i])
	{
		if (data->args[i][0] != '-')
			flag = 1;
		i++;
	}
	return (flag);
}

int	ft_count_opt_and_args(t_data *data, int ac, int args)
{
	int res;

	res = ac - 1 - data->opt.nbr_of_opt;
	if (args == 0 && res > 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int	i;
	int	args;

	memset(&data, 0, sizeof(t_data));
	data.paths.nbr_of_paths = 0;
	data.files.nbr_of_files = 0;
	data.opt.nbr_of_opt = 0;
	data.first_dir = 0;
	data.args = NULL;
	ft_copy_args(ac, av, &data);
	if (ft_get_options_and_check_errors(ac, data.args, &data))
		return (1);
	//printf("end check opt\n");
	//printf("check file\n");
	
	i = ft_count_args(data);
	if (i)
		ft_get_files_and_check_errors(data.args, &data);
	//printf("check opt\n");
	//printf("end check file\n");
	//printf("check dir\n");
	ft_get_paths_and_check_errors(data.args, &data);

	
	//printf("check opt\n");
	//printf("end of check dir\n");
	(void) i;
	/*
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
	}*/
	data.lng_format = NULL;
	data.shrt_format = NULL;
	i = 0;
	args = ft_count_args(data);
	//printf("counter path : %d , file : %d opt: %d args-opt: %d\n", data.paths.nbr_of_paths, data.files.nbr_of_files, data.opt.nbr_of_opt, args);
	if ((args == 0 && ac > 1) || ((ac > 1 && ft_its_only_options(&data)) && ft_count_opt_and_args(&data, ac, args)))
	{
		printf("outside\n");
		return (1);
	}
	//printf("_______________________________________________________________________\n");
	//printf("\n\n\n\n\n\n\n\n\n\n");
	ft_start_listing(&data);
	/*printf("_______________________________________________________________________\n");
	
	if (data.opt.op_l_flag)
		ft_display_long_format(&data);
	else
		ft_display_short_format(&data);
	*/
	return (0);
}
