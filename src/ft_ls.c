/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 00:35:15 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/05 01:48:32 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"


t_data	ft_initialize_data_struct(t_data data)
{
	memset(&data, 0, sizeof(t_data));
	data.paths.nbr_of_paths = 0;
	data.files.nbr_of_files = 0;
	data.opt.nbr_of_opt = 0;
	data.first_dir = 0;
	data.args = NULL;
	data.lng_format = NULL;
	data.shrt_format = NULL;
	data.paths.path = NULL;
	data.files.file = NULL;

	return (data);
}

int	main(int ac, char **av)
{
	t_data	data;
	int	i;
	int	args;

	data = ft_initialize_data_struct(data);
	//printf("-------------------------------------\n");
	if (ft_copy_args(ac, av, &data))
	{
		ft_putstr_std("ft_ls.c : error allocate memory\n", 2);
		return (1);
	}
	/*i = 0;
	while (data.args[i])
	{
		printf("args path %s ,i :%d \n", data.args[i], i);
		i++;
	}
	printf("-------------------------------------\n");
	*/
	if (ft_get_options_and_check_errors(ac, data.args, &data))
		return (1);
	//printf("-------------------------------------\n");
	i = ft_count_args(data);
	//printf("-------------------------------------\n");
	if (i)
	{
		if (ft_get_files_and_check_errors(data.args, &data))
		{
			//ft_free(data);
			return (1);
		}
	}
	//printf("-------------------------------------\n");
	if (ft_get_paths_and_check_errors(data.args, &data))
		return (1);

	//printf("oo%d-------------------------------------\n", data.paths.nbr_of_paths);
	//printf("s-------------------------------------\n");
	i = 0;
	args = ft_count_args(data);
	if ((args == 0 && ac > 1) || ((ac > 1 && ft_its_only_options(&data)) && ft_count_opt_and_args(&data, ac, args)))
	{
		ft_putstr_std("ft_ls.c : error, no valid arg or oprion\n", 1);
		return (1);
	}
	//exit(0);
	ft_start_listing(&data);
	//printf("-------------------------------------\n");
	ft_free_data(&data);
	return (0);
}
