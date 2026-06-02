/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_by_time_short_all_data.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 00:54:32 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/29 01:16:54 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"


t_data	*ft_sort_by_time_long_all_data(t_data *data)
{
        t_long_format *prev;
        t_long_format *cur;
        t_long_format *tmp;

        if (!data || !data->lng_format)
                return (data);

        prev = NULL;
        cur = data->lng_format;
        while (cur && cur->next)
        {
		if (data->opt.op_r_flag && (!ft_cmp_time(data, cur, cur->next)))
                {
                        tmp = cur->next;

                        // unlink tmp
                        cur->next = tmp->next;
                        tmp->next = cur;

                        // 🔥 FIX 1: handle head correctly
                        if (prev == NULL)
                                data->lng_format = tmp;
                        else
                                prev->next = tmp;

                        // 🔥 FIX 2: update pointers correctly
                        //prev = tmp;
                        //cur = tmp->next;
                        cur = data->lng_format;
                        prev  = NULL;
                        continue;
                }
		if (data->opt.op_r_flag == 0 && (ft_cmp_time(data, cur, cur->next)))
                {
                        tmp = cur->next;

                        // unlink tmp
                        cur->next = tmp->next;
                        tmp->next = cur;

                        // 🔥 FIX 1: handle head correctly
                        if (prev == NULL)
                                data->lng_format = tmp;
                        else
                                prev->next = tmp;

                        // 🔥 FIX 2: update pointers correctly
                        //prev = tmp;
                        //cur = tmp->next;
                        cur = data->lng_format;
                        prev  = NULL;
                        continue;
                }
                else
                {
                        prev = cur;
                        cur = cur->next;
                }
        }
        return (data);
}


t_data	*ft_sort_by_time_short_all_data(t_data *data)
{
        t_short_format *prev;
        t_short_format *cur;
        t_short_format *tmp;

        if (!data || !data->shrt_format)
                return (data);

        prev = NULL;
        cur = data->shrt_format;

        while (cur && cur->next)
        {
		if (data->opt.op_r_flag && (!ft_cmp_time_short(data, cur, cur->next)))
		{
                        tmp = cur->next;
                        cur->next = tmp->next;
                        tmp->next = cur;
                        if (prev == NULL)
                                data->shrt_format = tmp;
                        else
                                prev->next = tmp;

                        cur = data->shrt_format;
                        prev  = NULL;
                        continue;
		}
                if (data->opt.op_r_flag == 0 && ft_cmp_time_short(data, cur, cur->next))
                {
                        tmp = cur->next;
                        cur->next = tmp->next;
                        tmp->next = cur;
                        if (prev == NULL)
                                data->shrt_format = tmp;
                        else
                                prev->next = tmp;

                        cur = data->shrt_format;
                        prev  = NULL;
                        continue;
                }
                else
                {
                        prev = cur;
                        cur = cur->next;
                }
        }
        return (data);
}


