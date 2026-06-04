/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_format_column.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 21:08:29 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/04 02:17:48 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int ft_get_term_width(void)
{
    struct winsize w;

    if (ioctl(1, TIOCGWINSZ, &w) == -1)
        return (80); // fallback

    return (w.ws_col);
}

int ft_get_max_len(t_short_format *list)
{
    int max = 0;
    int len;

    while (list)
    {
        len = ft_strlen((char *)list->data);
        if (len > max)
            max = len;
        list = list->next;
    }
    return (max);
}

int ft_list_size(t_short_format *list)
{
    int count = 0;

    while (list)
    {
        count++;
        list = list->next;
    }
    return (count);
}

void ft_display_short_format_column(t_data *data)
{
	ft_display_short_format_n_data_column(data, 0);
}

void    ft_print_name(t_short_format *node, int max_len, int is_last)
{
    char    *name;
    int     len;
    int     pad;

    name = (char *)node->data;
    len = ft_strlen(name);

	char *color = NULL;

	if (node->is_dir)
	    color = "\033[94m";
	else if (node->is_exe_or_link == 2)
	    color = "\033[31m";
	else if (node->is_exe_or_link == 1)
	    color = "\033[32m";
	else if (name[0] == '.')
	    color = "\033[37m";

	if (color)
	    write(1, color, 5);

	write(1, name, ft_strlen(name));

	if (color)
	    write(1, "\033[0m", 4);

    // padding (only if not last column)
    if (!is_last)
    {
        pad = (max_len + 2) - len;
        while (pad-- > 0)
            write(1, "_", 1);
    }
}


int ft_calculate_layout(
    t_short_format **arr,
    int count,
    int term_width,
    int *col_widths,
    int *out_rows)
{
    int cols = count;
    int rows;
    int col, row, index;
    int total_width;
    int max;

    while (cols > 0)
    {
        rows = (count + cols - 1) / cols;
        total_width = 0;

        col = 0;
        while (col < cols)
        {
            max = 0;
            row = 0;

            while (row < rows)
            {
                index = col * rows + row;
                if (index < count)
                {
                    int len = ft_strlen((char *)arr[index]->data);
                    if (len > max)
                        max = len;
                }
                row++;
            }

            // 🔥 KEY FIX HERE
            if (col == cols - 1)
                col_widths[col] = max;        // NO padding
            else
                col_widths[col] = max + 2;    // padding

            total_width += col_widths[col];
            col++;
        }

        if (total_width <= term_width)
        {
            *out_rows = rows;
            return cols;
        }

        cols--;
    }

    *out_rows = count;
    col_widths[0] = term_width;
    return 1;
}

void ft_display_short_format_n_data_column(t_data *data, int start)
{
    t_short_format *tmp;
    t_short_format **arr;
    int *col_widths;

    int count;
    int i, row, col;
    int term_width;
    int cols, rows;
    int index;

    if (!data || !data->shrt_format)
        return;

    // skip start
    tmp = data->shrt_format;
    i = 0;
    while (tmp && i++ < start)
        tmp = tmp->next;

    // count
    count = 0;
    t_short_format *save = tmp;
    while (tmp && ++count)
        tmp = tmp->next;

    if (count == 0)
        return;

    // array
    arr = malloc(sizeof(t_short_format *) * count);
    if (!arr)
        return;

    tmp = save;
    i = 0;
    while (tmp)
    {
        arr[i++] = tmp;
        tmp = tmp->next;
    }

    // terminal
    term_width = ft_get_term_width();

    // allocate col widths
    col_widths = malloc(sizeof(int) * count);
    if (!col_widths)
        return;

    // compute layout
    cols = ft_calculate_layout(arr, count, term_width, col_widths, &rows);

    // PRINT (column-first)
    row = 0;
    while (row < rows)
    {
        col = 0;
        while (col < cols)
        {
            index = col * rows + row;

            if (index < count)
            {
                char *name = (char *)arr[index]->data;
                int len = ft_strlen(name);
                int pad;

                // color
                if (arr[index]->is_dir)
                    write(1, "\033[94m", 5);
		else if (arr[index]->is_exe_or_link == 2)
                    write(1, "\033[36m", 5);
		else if (arr[index]->is_exe_or_link == 1)
                    write(1, "\033[32m", 5);
                else if (name[0] == '.')
                    write(1, "\033[37m", 5);

                write(1, name, len);

                if (arr[index]->is_dir || name[0] == '.' || arr[index]->is_exe_or_link)
                    write(1, "\033[0m", 4);

                // padding ONLY if not last column
                if (col < cols - 1)
                {
                    pad = col_widths[col] - len;
                    while (pad-- > 0)
                        write(1, " ", 1);
                }
            }
            col++;
        }
        write(1, "\n", 1);
        row++;
    }

    free(col_widths);
    free(arr);
}
