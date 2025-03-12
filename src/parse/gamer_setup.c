/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamer_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:50:08 by itykhono          #+#    #+#             */
/*   Updated: 2025/03/12 16:51:10 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	count_file_lines(const char *file_path)
{
	int		fd;
	int		lines;
	char	*line;

	lines = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		error_msg(ERR_FL, 2);
		return (-1);
	}
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

void	set_player_position(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_det.height)
	{
		j = 0;
		while (j < data->map_det.width)
		{
			if (data->map[i][j] == 'W' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'N')
			{
				data->player.pos_x = j + 0.5;
				data->player.pos_y = i + 0.5;
				data->player.dir = data->map[i][j];
				return ;
			}
			j++;
		}
		i++;
	}
}
