/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_this_arg_is_valid_path.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 22:45:17 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/06 23:00:58 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static int	ft_display_error(int err, char *av, t_data *data, int i)
{
	if (err == 1)
	{
		ft_putstr_std("ft_ls: cannot access '", 2);
		ft_putstr_std(av, 2);
		ft_putstr_std("': No such file or directory\n", 2);
	}
	else if (err == 2)
		ft_putstr_std("ft_ls: error allocation memory\n", 2);
	else if (err == 3)
	{
		ft_putstr_std("ls: cannot access '", 2);
		ft_putstr_std(av, 2);
		ft_putstr_std("': File name too long\n", 2);
	}
	ft_remove_arg(data, i);
	return (1);
}

static int	ft_handle_pre_checks(t_data *data, char *av, int index)
{
	int	i;

	i = ft_check_if_its_a_dir(av, data, index);
	if (i == -1)
		return (0);
	else if (i == 1)
		return (1);
	if (access(av, F_OK) != 0)
		return (ft_display_error(1, av, data, index));
	return (2);
}

static char	*ft_safe_strdup_path(t_data *data, char *av,
			int index, int *malloc_err)
{
	char	*temp;

	temp = ft_strdup(av);
	if (!temp)
	{
		*malloc_err = 1;
		ft_free_paths(data);
		ft_display_error(2, av, data, index);
		return (NULL);
	}
	return (temp);
}

static char	**ft_copy_old_paths(t_data *data, char *av,
			int index, int *malloc_err)
{
	char	**new_paths;

	new_paths = malloc(sizeof(char *) * (data->paths.nbr_of_paths + 2));
	if (!new_paths)
		return (*malloc_err = 1, ft_free_paths(data),
			ft_display_error(2, av, data, index), NULL);
	data->i = 0;
	while (data->i < data->paths.nbr_of_paths)
	{
		new_paths[data->i] = malloc(ft_strlen(data->paths.path[data->i]) + 1);
		if (!new_paths[data->i])
			return (ft_free_until(new_paths, data->i), ft_free_paths(data),
				*malloc_err = 1,
				ft_display_error(2, av, data, index), NULL);
		data->j = 0;
		while (data->paths.path[data->i][data->j])
		{
			new_paths[data->i][data->j] = data->paths.path[data->i][data->j];
			data->j++;
		}
		new_paths[data->i][data->j] = 0;
		data->i++;
	}
	return (new_paths);
}

int	ft_check_this_arg_is_valid_path(t_data *data, char *av,
		int index, int *malloc_err)
{
	char	**new_paths;
	char	*temp;
	int		status;

	status = ft_handle_pre_checks(data, av, index);
	if (status != 2)
		return (status);
	temp = ft_safe_strdup_path(data, av, index, malloc_err);
	if (!temp)
		return (0);
	new_paths = ft_copy_old_paths(data, av, index, malloc_err);
	if (!new_paths)
		return (0);
	new_paths[data->paths.nbr_of_paths] = temp;
	new_paths[data->paths.nbr_of_paths + 1] = NULL;
	ft_free_paths(data);
	data->paths.path = new_paths;
	data->paths.nbr_of_paths++;
	return (0);
}
