/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:05:02 by itykhono          #+#    #+#             */
/*   Updated: 2025/03/13 13:05:47 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	error_msg(char *msg, int status_code)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	return (status_code);
}

// functio for MacOS
void	exit_and_free(t_data *data, int s_code)
{
	if (!data)
		exit(s_code);
	if (data->view.win && data->view.mlx)
		mlx_destroy_window(data->view.mlx, data->view.win);
	if (data->view.mlx)
		free(data->view.mlx);
	free_data(data);
	exit(s_code);
}

void	exit_cube(t_data *data, int exit_code)
{
	free_data(data);
	exit(exit_code);
}
