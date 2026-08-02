/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmp_time_with_timeval.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tariq <tariqelbouhali039@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 21:37:32 by tariq             #+#    #+#             */
/*   Updated: 2026/08/02 21:47:00 by tariq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_cmp_case(t_data *data, t_long_format *a, t_long_format *b)
{
	int	ascii;

	if (a->tv.tv_usec > b->tv.tv_usec)
		return (0);
	if (a->tv.tv_usec < b->tv.tv_usec)
		return (1);
	else
	{
		ascii = ft_strcmp(a->filename, b->filename);
		if (data->opt.op_r_flag == 0 && ascii < 0)
			return (0);
		else if (data->opt.op_r_flag == 0 && ascii > 0)
			return (1);
		else if (data->opt.op_r_flag == 1 && ascii > 0)
			return (1);
		else if (data->opt.op_r_flag == 1 && ascii < 0)
			return (0);
		else
			return (-1);
	}
}

int	ft_cmp_case_r_flag(t_data *data, t_long_format *a, t_long_format *b)
{
	int	ascii;

	if (a->tv.tv_usec > b->tv.tv_usec)
		return (1);
	if (a->tv.tv_usec < b->tv.tv_usec)
		return (0);
	else
	{
		ascii = ft_strcmp(a->filename, b->filename);
		if (data->opt.op_r_flag == 0 && ascii < 0)
			return (1);
		else if (data->opt.op_r_flag == 0 && ascii > 0)
			return (0);
		else if (data->opt.op_r_flag == 1 && ascii > 0)
			return (0);
		else if (data->opt.op_r_flag == 1 && ascii < 0)
			return (1);
		else
			return (-1);
	}
}

int	ft_cmp_time_tv(t_data *data, t_long_format *a, t_long_format *b)
{
	int	ascii;

	if (a->tv.tv_sec == b->tv.tv_sec)
		return (ft_cmp_case(data, a, b));
	if (a->tv.tv_sec < b->tv.tv_sec)
		return (1);
	if (a->tv.tv_sec > b->tv.tv_sec)
		return (0);
	if (a->tv.tv_usec < b->tv.tv_usec)
		return (1);
	if (a->tv.tv_usec > b->tv.tv_usec)
		return (0);
	ascii = ft_strcmp(a->filename, b->filename);
	if (data->opt.op_r_flag == 0 && ascii < 0)
		return (1);
	else if (data->opt.op_r_flag == 0 && ascii > 0)
		return (0);
	else if (data->opt.op_r_flag == 1 && ascii > 0)
		return (0);
	else if (data->opt.op_r_flag == 1 && ascii < 0)
		return (1);
	else
		return (-1);
}

int	ft_cmp_time_upper_r_flag_tv(t_data *data,
		t_long_format *a, t_long_format *b)
{
	int	ascii;

	if (a->tv.tv_sec == b->tv.tv_sec)
		return (ft_cmp_case(data, a, b));
	if (a->tv.tv_sec < b->tv.tv_sec)
		return (1);
	if (a->tv.tv_sec > b->tv.tv_sec)
		return (0);
	if (a->tv.tv_usec < b->tv.tv_usec)
		return (1);
	if (a->tv.tv_usec > b->tv.tv_usec)
		return (0);
	ascii = ft_strcmp(a->filename, b->filename);
	if (data->opt.op_r_flag == 0 && ascii < 0)
		return (0);
	else if (data->opt.op_r_flag == 0 && ascii > 0)
		return (1);
	else if (data->opt.op_r_flag == 1 && ascii > 0)
		return (1);
	else if (data->opt.op_r_flag == 1 && ascii < 0)
		return (0);
	else
		return (-1);
}
