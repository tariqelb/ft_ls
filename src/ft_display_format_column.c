/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_format_column.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 21:08:29 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/09 16:35:27 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_prepare_layout(t_disp_ctx *ctx)
{
	t_cal_lay	lay;
	int			term_width;

	term_width = ft_get_term_width();
	ctx->col_widths = malloc(sizeof(int) * ctx->count);
	if (!ctx->col_widths)
		return (0);
	lay.arr = ctx->arr;
	lay.count = ctx->count;
	lay.term_width = term_width;
	lay.col_widths = ctx->col_widths;
	lay.out_rows = &ctx->rows;
	ctx->cols = ft_calculate_layout(&lay);
	return (1);
}

void	ft_print_cell(t_disp_ctx *ctx, int index, int col)
{
	char	*name;
	int		len;
	int		pad;

	name = (char *)ctx->arr[index]->data;
	len = ft_strlen(name);
	if (ctx->arr[index]->is_dir)
		write(1, "\033[94m", 5);
	else if (ctx->arr[index]->is_exe_or_link == 2)
		write(1, "\033[36m", 5);
	else if (ctx->arr[index]->is_exe_or_link == 1)
		write(1, "\033[32m", 5);
	else if (name[0] == '.')
		write(1, "\033[37m", 5);
	write(1, name, len);
	if (ctx->arr[index]->is_dir || name[0] == '.'
		|| ctx->arr[index]->is_exe_or_link)
		write(1, "\033[0m", 4);
	if (col < ctx->cols - 1)
	{
		pad = ctx->col_widths[col] - len;
		while (pad-- > 0)
			write(1, " ", 1);
	}
}

void	ft_print_grid(t_disp_ctx *ctx)
{
	int	row;
	int	col;
	int	index;

	row = 0;
	while (row < ctx->rows)
	{
		col = 0;
		while (col < ctx->cols)
		{
			index = col * ctx->rows + row;
			if (index < ctx->count)
				ft_print_cell(ctx, index, col);
			col++;
		}
		write(1, "\n", 1);
		row++;
	}
}

void	ft_display_short_format_n_data_column(t_data *data, int start)
{
	t_short_format	*tmp;
	t_disp_ctx		ctx;

	if (!data || !data->shrt_format)
		return ;
	tmp = data->shrt_format;
	while (tmp && start-- > 0)
		tmp = tmp->next;
	ctx.arr = ft_build_array(tmp, &ctx.count);
	if (!ctx.arr)
		return ;
	if (!ft_prepare_layout(&ctx))
		return (free(ctx.arr));
	ft_print_grid(&ctx);
	free(ctx.col_widths);
	free(ctx.arr);
}
