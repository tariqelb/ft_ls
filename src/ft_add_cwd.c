/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_cwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 18:01:13 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/29 18:01:35 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static int  is_option(char *arg)
{
    if (!arg)
        return (0);
    if (arg[0] == '-' && arg[1] != '\0')
        return (1);
    return (0);
}

void    ft_add_cwd_if_needed(t_data *data)
{
    int     i;
    int     all_options;
    char    **new_args;

    i = 0;
    all_options = 1;

    // check if all args are options
    while (data->args[i])
    {
        if (!is_option(data->args[i]))
        {
            all_options = 0;
            break;
        }
        i++;
    }

    if (!all_options)
        return;

    // allocate new array (old count + "." + NULL)
    new_args = malloc(sizeof(char *) * (i + 2));
    if (!new_args)
        return;

    // copy old args
    int j = 0;
    while (j < i)
    {
        new_args[j] = data->args[j]; // reuse pointers
        j++;
    }

    // append "."
    new_args[j] = ft_strdup(".");
    if (!new_args[j])
        return;
    j++;

    new_args[j] = NULL;

    // free only old array (not strings)
    free(data->args);

    data->args = new_args;
}
