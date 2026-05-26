/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:00:01 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/25 02:24:18 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"


t_data *ft_sort_long_format_all_data(t_data *data)
{
	t_long_format *prev;
	t_long_format *cur;
	t_long_format *tmp;

	if (!data || !data->lng_format)
		return (data);

	prev = NULL;
	cur = data->lng_format;
	/*{
		printf("all iter ---\n");
		t_long_format *t = data->lng_format;
		while (t)
		{
			printf("----- all iter : %s\n", t->filename);
			t = t->next;
		}
	}*/

	while (cur && cur->next)
	{
		if (ft_strcmp(cur->filename, cur->next->filename) > 0)
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
	/*{
		printf("all iter ---\n");
		t_long_format *t = data->lng_format;
		while (t)
		{
			printf("----- all iter : %s\n", t->filename);
			t = t->next;
		}
	}*/
	return (data);
}


t_data *ft_sort_short_format_all_data(t_data *data)
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
		if (ft_strcmp(cur->data, cur->next->data) > 0)
		{
			tmp = cur->next;

			// unlink tmp
			cur->next = tmp->next;
			tmp->next = cur;

			// 🔥 FIX 1: handle head correctly
			if (prev == NULL)
				data->shrt_format = tmp;
			else
				prev->next = tmp;

			// 🔥 FIX 2: update pointers correctly
			//prev = tmp;
			//cur = tmp->next;
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


t_long_format	*ft_loop_over(t_data *data, int long_len)
{
	t_long_format *start;
	size_t		i;

	i = 0;
	start = data->lng_format;
	while (start && i < long_len)
	{
		start = start->next;
		i++;
	}
	return (start);
}

t_data *ft_sort_long_format(t_data *data, int long_len)
{
	int		i;
	t_long_format	*start;
	t_long_format	*prev;
	t_long_format	*cur;
	t_long_format	*tmp;

	if (!data || !data->lng_format)
		return (data);

	prev = data->lng_format;
	start = data->lng_format;
	/*{
		printf("iter ---\n");
		t_long_format *t = data->lng_format;
		while (t)
		{
			printf("iter : %s\n", t->filename);
			t = t->next;
		}
		printf("before sort %s %d\n", start->filename, long_len);
	}*/
	
	i = 0;
	while (start && i < long_len)
	{
		//printf("Move [%s]\n ", start->filename);
		prev = start;
		start = start->next;
		i++;
	}
	if (!start)
		return (data);
	cur = start;
	while (cur && cur->next)
	{
		if (prev->next != cur)
			prev = prev->next;
		if (i == 0)
			prev = cur;
		if (ft_strcmp(cur->filename, cur->next->filename) > 0 && i == 0)
		{
			//printf("sort prob\n");
			//printf("else c[%s] n{%s} p[%s]\n ", cur->filename, cur->next->filename, prev->filename);
			tmp = cur->next;
			cur->next = tmp->next;
			tmp->next = cur;
			data->lng_format = tmp;
			//printf("else c[%s] n{%s} p[%s]\n ", cur->filename, tmp->filename, prev->filename);
		}
		else if (ft_strcmp(cur->filename, cur->next->filename) > 0)
		{
			//printf("else c[%s] n{%s} p[%s]\n ", cur->filename, cur->next->filename, prev->filename);
			//[prev][tmp][curr][next][]
			tmp = cur->next;
			prev->next = tmp;
			cur->next = tmp->next;
			tmp->next = cur;
			//printf("after n[%s] c{%s} p[%s] pn[%s]\n ", cur->filename, tmp->filename, prev->filename, prev->next->filename);
			cur = prev->next;
			prev->next = cur;
			//cur = ft_loop_over(data, long_len);
			//prev =  cur;
			//printf("after c[%s] n{%s} p[%s] pn[%s]\n ", cur->filename, cur->next->filename, prev->filename, prev->next->filename);
		}
		else
		{
			cur = cur->next;
		}
		
	}
	{
		printf("iter ---\n");
		t_long_format *t = data->lng_format;
		while (t)
		{
			printf("iter : %s\n", t->filename);
			t = t->next;
		}
		printf("before sort %s %d\n", start->filename, long_len);
	}
	return (data);
}


t_data	*ft_sort_short_format(t_data *data, int short_len)
{
	int		i;
	t_short_format	*start;
	t_short_format	*prev;
	t_short_format	*cur;
	t_short_format	*tmp;

	if (!data || !data->shrt_format)
		return (data);

	prev = data->shrt_format;
	start = data->shrt_format;
	/*{
		printf("iter short-----\n");
		t_long_format *t = data->shrt_format;
		while (t)
		{
			printf("iter  short : %s\n", t->data);
			t = t->next;
		}
	}*/
	
	i = 0;
	while (start && i < short_len)
	{
		//printf("Move [%s]\n ", start->filename);
		prev = start;
		start = start->next;
		i++;
	}
	if (!start)
		return (data);
	cur = start;
	while (cur && cur->next)
	{
		if (prev->next != cur)
			prev = prev->next;
		if (i == 0)
			prev = cur;
		if (ft_strcmp(cur->data, cur->next->data) > 0 && i == 0)
		{
			//printf("sort prob\n");
			//printf("else c[%s] n{%s} p[%s]\n ", cur->filename, cur->next->filename, prev->filename);
			tmp = cur->next;
			cur->next = tmp->next;
			tmp->next = cur;
			data->shrt_format = tmp;
			//printf("else c[%s] n{%s} p[%s]\n ", cur->filename, tmp->filename, prev->filename);
		}
		else if (ft_strcmp(cur->data, cur->next->data) > 0)
		{
			//printf("else c[%s] n{%s} p[%s]\n ", cur->filename, cur->next->filename, prev->filename);
			//[prev][tmp][curr][next][]
			tmp = cur->next;
			prev->next = tmp;
			cur->next = tmp->next;
			tmp->next = cur;
			cur = prev->next;
			prev->next = cur;
		}
		else
		{
			cur = cur->next;
		}
	}
	{
		/*printf("iter  short---\n");
		t_short_format *t = data->shrt_format;
		while (t)
		{
			printf("iter short: %s\n", t->data);
			t = t->next;
		}*/
	}
	return (data);
}
