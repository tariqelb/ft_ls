/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_over_options.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 23:58:18 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/06 22:41:34 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

void	ft_set_flag(short *flag, t_options *opt)
{
	if (!(*flag))
	{
		*flag = 1;
		opt->nbr_of_opt++;
	}
}

int	ft_set_option(char c, t_options *opt)
{
	if (c == 'l')
		ft_set_flag(&opt->op_l_flag, opt);
	else if (c == 'a')
		ft_set_flag(&opt->op_a_flag, opt);
	else if (c == 'r')
		ft_set_flag(&opt->op_r_flag, opt);
	else if (c == 't')
		ft_set_flag(&opt->op_t_flag, opt);
	else if (c == 'R')
		ft_set_flag(&opt->op_R_flag, opt);
	else
		return (1);
	return (0);
}

int	ft_parse_option_arg(char *arg, t_data *data)
{
	int	j;

	j = 1;
	while (arg[j])
	{
		if (ft_set_option(arg[j], &data->opt))
		{
			ft_putstr_std("ft_ls: invalid option -- ", 2);
			write(2, &arg[j], 1);
			ft_putstr_std("\nTry 'ls --help' for more information.\n", 2);
			return (1);
		}
		j++;
	}
	return (0);
}

int	ft_free_args(t_data *data)
{
	int	i;

	i = 0;
	while (data->args && data->args[i])
	{
		free(data->args[i]);
		i++;
	}
	if (data->args)
	{
		free(data->args);
		data->args = NULL;
	}
	return (0);
}

int	ft_loop_over_options(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	while (i < ac - 1)
	{
		if (av[i][0] == '-' && av[i][1] != '\0')
		{
			if (av[i][1] == '-')
			{
				ft_putstr_std("ft_ls: unrecognized option '", 2);
				ft_putstr_std(av[i], 2);
				ft_putstr_std("'\nTry 'ls --help' for more information.\n", 2);
				return (ft_free_args(data));
			}
			if (ft_parse_option_arg(av[i], data))
				return (1);
		}
		i++;
	}
	return (0);
}
