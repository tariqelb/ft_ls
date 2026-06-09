/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calcule_column_padding.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 20:35:04 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/09 16:05:56 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_get_col_max(t_cal_lay *lay, int col, int rows)
{
	int	row;
	int	index;
	int	max;
	int	len;

	max = 0;
	row = 0;
	while (row < rows)
	{
		index = col * rows + row;
		if (index < lay->count)
		{
			len = ft_strlen((char *)lay->arr[index]->data);
			if (len > max)
				max = len;
		}
		row++;
	}
	return (max);
}

int	ft_fill_col_widths(t_cal_lay *lay, int cols, int rows)
{
	int	col;
	int	total_width;
	int	max;

	total_width = 0;
	col = 0;
	while (col < cols)
	{
		max = ft_get_col_max(lay, col, rows);
		if (col == cols - 1)
			lay->col_widths[col] = max;
		else
			lay->col_widths[col] = max + 2;
		total_width += lay->col_widths[col];
		col++;
	}
	return (total_width);
}

int	ft_calculate_layout(t_cal_lay *lay)
{
	int	cols;
	int	rows;
	int	total_width;

	cols = lay->count;
	while (cols > 0)
	{
		rows = (lay->count + cols - 1) / cols;
		total_width = ft_fill_col_widths(lay, cols, rows);
		if (total_width <= lay->term_width)
		{
			*(lay->out_rows) = rows;
			return (cols);
		}
		cols--;
	}
	*(lay->out_rows) = lay->count;
	lay->col_widths[0] = lay->term_width;
	return (1);
}
