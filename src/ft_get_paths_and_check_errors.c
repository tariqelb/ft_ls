/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_paths_and_check_errors.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:32:02 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/26 00:59:31 by tel-bouh         ###   ########.fr       */
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

int 	ft_check_if_its_a_dir(char *av, t_data *data, int i)
{
	//printf("ft_check_if_its_a_dir\n");
	struct stat st;

	if (stat(av, &st) != 0)
	{
		return (ft_display_error(1, av, data, i));
	}

	if (S_ISDIR(st.st_mode))
	{
		if (ft_strlen(av) < 4097)
			return (0);
		else
			return (ft_display_error(3, av, data, i));
	}
	else 
		return (-1);
	return (0);
}


int	ft_check_this_arg_is_valid_path(t_data *data, char *av, int index)
{
	//printf("ft_check_this_arg_is_valid_path\n");
	char    **new_paths;
	int     i;

	i = ft_check_if_its_a_dir(av, data, index);
	if (i == -1)
		return (0);
	else if (i == 1)
		return (1);
	if (access(av, F_OK) != 0)
		return (ft_display_error(1, av, data, index));
	new_paths = malloc(sizeof(char *) * (data->paths.nbr_of_paths + 1));
	if (!new_paths)
		return (ft_display_error(2, av, data, index));
	i = 0;
	while (i < data->paths.nbr_of_paths)
	{
		new_paths[i] = data->paths.path[i];
		i++;
	}
	new_paths[i] = ft_strdup(av);
	if (!new_paths[i])
	{
		free(new_paths);
		return (ft_display_error(2, av, data, index));
	}
	free(data->paths.path);
	data->paths.path = new_paths;
	data->paths.nbr_of_paths++;
	return (0);
}

int	ft_get_paths_and_check_errors(char **av, t_data *data)
{
	//printf("ft_get_paths_and_check_errors\n");
	int i;

	i = 0;
	while (av && av[i] != NULL)
	{
		if (av[i][0] != '-')
		{
			i -= ft_check_this_arg_is_valid_path(data, av[i], i);
				
		}
		i++;
	}
	return (0);	
}
