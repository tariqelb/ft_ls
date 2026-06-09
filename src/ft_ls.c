/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 00:35:15 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/07 22:28:13 by tel-bouh         ###   ########.fr       */
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

int	ft_initialize_data_and_copy_args(t_data *data, int ac, char **av)
{
	*data = ft_initialize_data_struct(*data);
	if (ft_copy_args(ac, av, data))
	{
		ft_putstr_std("ft_ls.c : error allocate memory\n", 2);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;
	int		args;

	if (ft_initialize_data_and_copy_args(&data, ac, av))
		return (1);
	if (ft_get_options_and_check_errors(ac, data.args, &data))
		return (1);
	i = ft_count_args(data);
	if (i)
		if (ft_get_files_and_check_errors(data.args, &data))
			return (1);
	if (ft_get_paths_and_check_errors(data.args, &data))
		return (1);
	args = ft_count_args(data);
	if ((args == 0 && ac > 1) || ((ac > 1 && ft_its_only_options(&data))
			&& ft_count_opt_and_args(&data, ac, args)))
	{
		ft_putstr_std("ft_ls.c : error, no valid arg or oprion\n", 1);
		return (1);
	}
	ft_start_listing(&data);
	ft_free_data(&data);
	return (0);
}
