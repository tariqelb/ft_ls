/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_options_and_check_errors.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:50:00 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/15 20:15:04 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_get_options_and_check_errors(int ac, char **av, t_data *data)
{
	if (ac == 1)
	{
		data->paths.path = NULL;
		data->files.file = NULL;
		data->paths.nbr_of_paths = 0;
		data->files.nbr_of_files = 0;
		data->opt.nbr_of_opt = 0;			
		return (0);
	}
	if (ft_loop_over_options(ac, av, data) == 1)
		return (1);
	return (0);
}
