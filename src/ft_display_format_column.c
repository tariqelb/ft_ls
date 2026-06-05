/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_format_column.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 21:08:29 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/04 20:43:00 by tel-bouh         ###   ########.fr       */
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
    {
        free(arr);
        return;
    }

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
