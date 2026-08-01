#include "./ft_ls.h"

int     ft_cmp_case_short(t_data *data, t_short_format *a, t_short_format *b)
{
        int ascii;

        if (a->tv.tv_usec > b->tv.tv_usec)
                return (0);
        if (a->tv.tv_usec < b->tv.tv_usec)
                return (1);
        else
        {
                ascii = ft_strcmp(a->data, b->data);
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


int     ft_cmp_case_short_r_flag(t_data *data, t_short_format *a, t_short_format *b)
{
        int ascii;

        if (a->tv.tv_usec > b->tv.tv_usec)
                return (1);
        if (a->tv.tv_usec < b->tv.tv_usec)
                return (0);
        else
        {
                ascii = ft_strcmp(a->data, b->data);
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


int     ft_cmp_time_short_tv(t_data *data, t_short_format *a, t_short_format *b)
{
	int ascii;

	if (a->tv.tv_sec == b->tv.tv_sec)
		return (ft_cmp_case_short(data, a, b));
	if (a->tv.tv_sec < b->tv.tv_sec)
		return (1);
	if (a->tv.tv_sec > b->tv.tv_sec)
		return (0);
	if (a->tv.tv_usec < b->tv.tv_usec)
		return (1);
	if (a->tv.tv_usec > b->tv.tv_usec)
		return (0);
	ascii = ft_strcmp(a->data, b->data);
	if (data->opt.op_r_flag == 0 && ascii < 0)
		return (1);
	else if (data->opt.op_r_flag == 0 && ascii > 0)
		return (0);
	if (data->opt.op_r_flag == 1 && ascii > 0)
		return (0);
	else if (data->opt.op_r_flag == 1 && ascii < 0)
		return (1);
	else
		return (-1);
}

int     ft_cmp_time_short_upper_r_flag_tv(t_data *data,
                t_short_format *a, t_short_format *b)
{
	int ascii;

	if (a->tv.tv_sec == b->tv.tv_sec)
		return (ft_cmp_case_short(data, a, b));
	if (a->tv.tv_sec < b->tv.tv_sec)
		return (1);
	if (a->tv.tv_sec > b->tv.tv_sec)
		return (0);
	if (a->tv.tv_usec < b->tv.tv_usec)
		return (1);
	if (a->tv.tv_usec > b->tv.tv_usec)
		return (0);
	ascii = ft_strcmp(a->data, b->data);
	if (data->opt.op_r_flag == 0 && ascii < 0)
		return (0);
	else if (data->opt.op_r_flag == 0 && ascii > 0)
		return (1);
	if (data->opt.op_r_flag == 1 && ascii > 0)
		return (1);
	else if (data->opt.op_r_flag == 1 && ascii < 0)
		return (0);
	else
		return (-1);
}
