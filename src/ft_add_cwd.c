/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_cwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 18:01:13 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/04 16:10:51 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int  ft_is_an_option(char *arg)
{
    if (!arg)
        return (0);
    if (arg[0] == '-' && arg[1] != '\0')
        return (1);
    return (0);
}

int ft_all_args_are_options(char **args)
{
    int i;

    i = 0;
    while (args[i])
    {
        if (!ft_is_an_option(args[i]))
            return (0);
        i++;
    }
    return (1);
}

int ft_args_count(char **args)
{
    int i;

    i = 0;
    while (args[i])
        i++;
    return (i);
}

void ft_copy_args_cwd(char **dst, char **src, int count)
{
    int j;

    j = 0;
    while (j < count)
    {
        dst[j] = src[j];
        j++;
    }
}


int ft_append_dot(char **args, int index)
{
    args[index] = ft_strdup(".");
    if (!args[index])
        return (1);
    args[index + 1] = NULL;
    return (0);
}

int ft_add_cwd_if_needed(t_data *data)
{
    int     count;
    char    **new_args;

    if (!ft_all_args_are_options(data->args))
        return (0);

    count = ft_args_count(data->args);

    new_args = malloc(sizeof(char *) * (count + 2));
    if (!new_args)
    {
        free(data->args);
        data->args = NULL;
        return (1);
    }

    ft_copy_args_cwd(new_args, data->args, count);

    if (ft_append_dot(new_args, count))
    {
        free(new_args);
        return (1);
    }

    free(data->args);
    data->args = new_args;
    return (0);
}
