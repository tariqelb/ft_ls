/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_and_count_args_opt.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:44:47 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/05 23:38:11 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_count_args(t_data data)
{
	int	i;
	int	args;

	i = 0;
	args = 0;
	while (data.args && data.args[i] != NULL)
	{
		if (data.args[i][0] != '-')
			args++;
		i++;
	}
	return (args);
}

int	ft_its_only_options(t_data *data)
{
	int	i;
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
	int	res;

	res = ac - 1 - data->opt.nbr_of_opt;
	if (args == 0 && res > 0)
		return (1);
	return (0);
}
