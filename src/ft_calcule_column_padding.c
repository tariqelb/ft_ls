/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calcule_column_padding.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 20:35:04 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/04 20:40:51 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_get_col_max(t_short_format **arr, int count, int col, int rows)
{
    int row;
    int index;
    int max;
    int len;

    max = 0;
    row = 0;
    while (row < rows)
    {
        index = col * rows + row;
        if (index < count)
        {
            len = ft_strlen((char *)arr[index]->data);
            if (len > max)
                max = len;
        }
        row++;
    }
    return (max);
}

int	ft_fill_col_widths(t_short_format **arr, int count, int cols, int rows, int *col_widths)
{
    int col;
    int total_width;
    int max;

    total_width = 0;
    col = 0;
    while (col < cols)
    {
        max = ft_get_col_max(arr, count, col, rows);

        if (col == cols - 1)
            col_widths[col] = max;
        else
            col_widths[col] = max + 2;

        total_width += col_widths[col];
        col++;
    }
    return (total_width);
}

int	ft_calculate_layout(t_short_format **arr, int count, int term_width, int *col_widths, int *out_rows)
{
    int cols;
    int rows;
    int total_width;

    cols = count;
    while (cols > 0)
    {
        rows = (count + cols - 1) / cols;

        total_width = ft_fill_col_widths(arr, count,
                                        cols, rows, col_widths);

        if (total_width <= term_width)
        {
            *out_rows = rows;
            return (cols);
        }
        cols--;
    }
    *out_rows = count;
    col_widths[0] = term_width;
    return (1);
}
