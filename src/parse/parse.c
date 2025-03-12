/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:04:47 by itykhono          #+#    #+#             */
/*   Updated: 2025/03/12 14:26:46 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	parse_color(const char *color_str)
{
	int	r;
	int	g;
	int	b;

	if (sscanf(color_str, "%d,%d,%d", &r, &g, &b) != 3)
	{
		error_msg(ERR_RGB_VAL, 1);
		return (-1);
	}
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
	{
		error_msg(ERR_RGB_VAL, 1);
		return (-1);
	}
	return ((r << 16) | (g << 8) | b);
}

char	*trim_newline(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	return (str);
}

int	is_texture(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0);
}

int	is_color(char *line)
{
	return (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

int	parse_texture(char *line, t_texture_det *texture_det)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		texture_det->north = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		texture_det->south = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		texture_det->west = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		texture_det->east = ft_strdup(line + 3);
	else
		return (0);
	return (1);
}

int	handle_color_assignment(char *line, t_texture_det *texture_det, int index)
{
	if (index == 4 && ft_strncmp(line, "F ", 2) == 0)
		texture_det->hex_floor = parse_color(line + 2);
	else if (index == 5 && ft_strncmp(line, "C ", 2) == 0)
	{
		texture_det->hex_ceiling = parse_color(line + 2);
		return (1);
	}
	else
		return (0);
	return (1);
}

int	process_texture_or_color(char *line, t_texture_det *texture_det, int i)
{
	trim_newline(line);
	if (i < 4)
		return (parse_texture(line, texture_det));
	return (handle_color_assignment(line, texture_det, i));
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

char	**expand_map_capacity(char **map, int *capacity, int size)
{
	char	**new_map;
	int		j;
	int		new_capacity;

	new_capacity = (*capacity) * 2;
	new_map = malloc(sizeof(char *) * new_capacity);
	if (!new_map)
	{
		while (size > 0)
			free(map[--size]);
		free(map);
		return (NULL);
	}
	j = 0;
	while (j < *capacity)
	{
		new_map[j] = map[j];
		j++;
	}
	free(map);
	*capacity = new_capacity;
	return (new_map);
}

int	add_map_row(char *row, char ***map, int *i, int *capacity)
{
	size_t	len;

	len = ft_strlen(row);
	if (len > 0 && row[len - 1] == '\n')
		row[len - 1] = '\0';
	if (ft_strchr(row, '1') || ft_strchr(row, '0'))
	{
		if (*i >= *capacity)
		{
			*map = expand_map_capacity(*map, capacity, *i);
			if (!(*map))
				return (0);
		}
		(*map)[(*i)++] = ft_strdup(row);
	}
	return (1);
}

char	**init_map(int fd_map)
{
	char	*map_row;
	char	**map;
	int		i;
	int		map_capacity;

	i = 0;
	map_capacity = 5;
	map = malloc(sizeof(char *) * map_capacity);
	if (!map)
		return (NULL);
	map_row = get_next_line(fd_map);
	while (map_row)
	{
		if (ft_strcmp(map_row, "\n") != 0)
		{
			if (!add_map_row(map_row, &map, &i, &map_capacity))
				return (NULL);
		}
		free(map_row);
		map_row = get_next_line(fd_map);
	}
	map[i] = NULL;
	return (map);
}

int	calculate_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

int	calculate_map_width(char **map)
{
	int	max_width;
	int	i;
	int	width;

	i = 0;
	max_width = 0;
	while (map[i])
	{
		width = ft_strlen(map[i]);
		if (map[i][width - 1] != '\n')
			width++;
		if (width > max_width)
			max_width = width;
		i++;
	}
	return (max_width);
}

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

int	color_floor(unsigned long floor_color)
{
	return ((int)floor_color);
}

int	color_ceiling(unsigned long ceiling_color)
{
	return ((int)ceiling_color);
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
