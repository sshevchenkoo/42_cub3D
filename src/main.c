/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:06:57 by itykhono          #+#    #+#             */
/*   Updated: 2025/03/13 13:07:41 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	starting_view(t_data *data)
{
	data->view.mlx = mlx_init();
	if (data->view.mlx == NULL)
	{
		error_msg(ERR_MLX_INIT, 5);
		exit(EXIT_FAILURE);
	}
	setup_textures(data);
	set_player_direction(&data->player);
	data->view.win = mlx_new_window(data->view.mlx, WIDTH, HEIGHT, TITLE);
	if (data->view.win == NULL)
	{
		error_msg(ERR_MLX_WIN, 5);
		exit(EXIT_FAILURE);
	}
	init_img(data, &data->view.screen, WIDTH, HEIGHT);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (error_msg(ERR_ARGS, 1));
	ft_bzero(&data, sizeof(t_data));
	if (!parse_file(argv[1], &data))
	{
		error_msg(ERR_FL, 1);
		return (EXIT_FAILURE);
	}
	if (!is_map_closed(data.map))
		return (error_msg(ERR_MAP, 1), 1);
	starting_view(&data);
	starting_game(&data);
	mlx_loop(data.view.mlx);
	return (EXIT_SUCCESS);
}
