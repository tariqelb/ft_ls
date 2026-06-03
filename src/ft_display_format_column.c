/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_format_column.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 21:08:29 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/03 02:06:19 by tel-bouh         ###   ########.fr       */
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
    t_short_format *arr[10000]; // or malloc
    t_short_format *tmp = data->shrt_format;
    int count = 0;
    int i, j;

    // convert list �~F~R array
    while (tmp)
    {
        arr[count++] = tmp;
        tmp = tmp->next;
    }

    int term_width = ft_get_term_width();
    int max_len = ft_get_max_len(data->shrt_format);
    int col_width = max_len + 2;
    int cols = term_width / col_width;
    int rows;

    if (cols == 0)
        cols = 1;

    rows = (count + cols - 1) / cols;

    for (i = 0; i < rows; i++)
    {
        j = i;
        while (j < count)
        {
            char *name = (char *)arr[j]->data;

            // color logic (same as yours)
            if (arr[j]->is_dir)
                write(1, "\033[94m", 5);
            else if (name[0] == '.')
                write(1, "\033[37m", 5);

            write(1, name, ft_strlen(name));
            write(1, "\033[0m", 4);

            // padding
            int len = ft_strlen(name);
            int pad = col_width - len;

            while (pad-- > 0)
                write(1, " ", 1);

            j += rows;
        }
        write(1, "\n", 1);
    }
}

void    ft_print_name(t_short_format *node, int max_len, int is_last)
{
    char    *name;
    int     len;
    int     pad;

    name = (char *)node->data;
    len = ft_strlen(name);

    // color
    if (node->is_dir)
        write(1, "\033[94m", 5);
    else if (name[0] == '.')
        write(1, "\033[37m", 5);

    write(1, name, len);

    if (node->is_dir || name[0] == '.')
        write(1, "\033[0m", 4);

    // padding (only if not last column)
    if (!is_last)
    {
        pad = (max_len + 2) - len;
        while (pad-- > 0)
            write(1, "_", 1);
    }
}

/*
int ft_compute_cols(int count, int term_width, int col_width)
{
    int cols;
    int rows;

    cols = count;

    while (cols > 1)
    {
	
        rows = (count + cols - 1) / cols;
	printf("(count : [%d], cols - 1 [%d], : cols [%d])\n", count, cols - 1, cols);
	printf("row : [%d], term_width [%d], col_width [%d]\n", (count + cols - 1) / cols , term_width, col_width);
	printf("if %d\n", (cols * col_width));
        if ((cols * col_width) <= term_width + 2)
            break;

        cols--;
    }

    return cols;
}

void    ft_display_short_format_n_data_column(t_data *data, int start)
{
    t_short_format *tmp;
    t_short_format **arr;
    int count;
    int i, col, row;
    int term_width;
    int max_len;
    int col_width;
    int cols;
    int rows;

    if (!data || !data->shrt_format)
        return;

    //int bigger_max_len;//bigger some of consicutive filename + 2 less than window size
    //bigger_max_len = ft_get_bigger_max_line(data->shrt_format, ft_get_term_width()); 
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

    // layout
    term_width = ft_get_term_width();
    max_len = ft_get_max_len(save);

//ft_calculate
	ft_cal(term_width, max_len, count);

    col_width = max_len + 2;

    if (cols < 1)
        cols = 1;

    rows = (count + cols - 1) / cols;

    // print (COLUMN-FIRST like ls)
    row = 0;
    while (row < rows)
    {
        col = 0;
        while (col < cols)
        {
            int index = col * rows + row;

            if (index < count)
            {
                int is_last = ((col + 1) * rows + row >= count);
                ft_print_name(arr[index], max_len, is_last);
            }
            col++;
        }
        write(1, "\n", 1);
        row++;
    }

    free(arr);
}
*/

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
                else if (name[0] == '.')
                    write(1, "\033[37m", 5);

                write(1, name, len);

                if (arr[index]->is_dir || name[0] == '.')
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
