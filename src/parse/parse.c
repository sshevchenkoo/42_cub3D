/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:04:47 by itykhono          #+#    #+#             */
/*   Updated: 2025/03/12 16:56:40 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	open_and_validate_file(const char *file_path, t_data *data)
{
	data->map_det.lines_file = count_file_lines(file_path);
	if (data->map_det.lines_file < 0)
	{
		error_msg(ERR_MAP, 1);
		return (0);
	}
	data->map_det.fd = open(file_path, O_RDONLY);
	if (data->map_det.fd < 0)
	{
		error_msg(ERR_FL, 2);
		return (0);
	}
	data->map_det.path = ft_strdup(file_path);
	return (1);
}

int	initialize_map(t_data *data)
{
	data->map = init_map(data->map_det.fd);
	if (!data->map)
	{
		error_msg(ERR_MAP, 1);
		close(data->map_det.fd);
		return (0);
	}
	close(data->map_det.fd);
	data->map_det.height = calculate_map_height(data->map);
	data->map_det.width = calculate_map_width(data->map);
	data->map_det.start_i_map = data->map_det.lines_file - data->map_det.height;
	data->map_det.end_i_map = data->map_det.lines_file;
	return (1);
}

void	allocate_colors(t_data *data)
{
	data->texture_det.floor = malloc(sizeof(int));
	data->texture_det.ceiling = malloc(sizeof(int));
	*(data->texture_det.floor) = color_floor(data->texture_det.hex_floor);
	*(data->texture_det.ceiling) = color_ceiling(data->texture_det.hex_ceiling);
}

int	parse_file(const char *file_path, t_data *data)
{
	if (!open_and_validate_file(file_path, data))
		return (0);
	if (!parse_textures_and_colors(data->map_det.fd, &data->texture_det))
	{
		error_msg(ERR_MAP, 1);
		close(data->map_det.fd);
		return (0);
	}
	if (!initialize_map(data))
		return (0);
	allocate_colors(data);
	set_player_position(data);
	return (1);
}

int	parse_textures_and_colors(int fd_map, t_texture_det *texture_det)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd_map);
	while (line && i < 6)
	{
		if (ft_strcmp(line, "\n") == 0)
		{
			free(line);
			line = get_next_line(fd_map);
			continue ;
		}
		if (!process_texture_or_color(line, texture_det, i))
		{
			free(line);
			return (0);
		}
		free(line);
		i++;
		line = get_next_line(fd_map);
	}
	return (i == 6);
}
