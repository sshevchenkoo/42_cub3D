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

char *trim_newline(char *str)
{
	size_t len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	return (str);
}

int parse_textures_and_colors(int fd_map, t_texture_det *texture_det)
{
	char	*line;
	int	i 

	i = 0;
	while ((line = get_next_line(fd_map)))
	{
		if (ft_strcmp(line, "\n") == 0)
		{
			free(line);
			continue;
		}
		trim_newline(line);
		if (i < 4)
		{
			if (ft_strncmp(line, "NO ", 3) == 0)
				texture_det->north = ft_strdup(line + 3);
			else if (ft_strncmp(line, "SO ", 3) == 0)
				texture_det->south = ft_strdup(line + 3);
			else if (ft_strncmp(line, "WE ", 3) == 0)
				texture_det->west = ft_strdup(line + 3);
			else if (ft_strncmp(line, "EA ", 3) == 0)
				texture_det->east = ft_strdup(line + 3);
			else {
				free(line);
				return (0);
			}
		}
		else if (i == 4)
		{
			if (ft_strncmp(line, "F ", 2) == 0)
				texture_det->hex_floor = parse_color(line + 2);
			else
			{
				free(line);
				return (0);
			}
		}
		else if (i == 5)
		{
			if (ft_strncmp(line, "C ", 2) == 0)
			{
				texture_det->hex_ceiling = parse_color(line + 2);
				free(line);
				return (1);
			}
			else
			{
				free(line);
				return (0);
			}
		}
		free(line);
		i++;
	}
	return (0);
}

char **init_map(int fd_map)
{
	char	*map_row;
	char	**map;
	int	i;
	int	map_capacity;
	int	j;
	size_t	len;
	int	new_capacity;
	char	**new_map;

	i = 0;
	map_capacity = 5;
	map = malloc(sizeof(char *) * map_capacity);
	if (!map)
		return NULL;
	while ((map_row = get_next_line(fd_map)))
	{
		if (ft_strcmp(map_row, "\n") == 0)
		{
			free(map_row);
			continue;
		}
		len = ft_strlen(map_row);
		if (map_row[len - 1] == '\n')
			map_row[len - 1] = '\0';
		if (ft_strchr(map_row, '1') || ft_strchr(map_row, '0'))
		{
			if (i >= map_capacity)
			{
				new_capacity = map_capacity * 2;
				**new_map = malloc(sizeof(char *) * new_capacity);
				if (!new_map)
				{
					while (i > 0)
						free(map[--i]);
					free(map);
					return NULL;
				}
				j = 0;
				while (j < map_capacity)
				{
					new_map[j] = map[j];
					j++;
				}
				free(map);
				map = new_map;
				map_capacity = new_capacity;
			}
			map[i++] = ft_strdup(map_row);
		}
		free(map_row);
	}
	map[i] = NULL;
	return map;
}

int calculate_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

int calculate_map_width(char **map)
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
	int	fd;
	int	lines;
	char	*line;

	lines = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		error_msg(ERR_FL, 2);
		return (-1);
	}
	while ((line = get_next_line(fd)))
	{
		lines++;
		free(line);
	}
	close(fd);
	return (lines);
}

int color_floor(unsigned long floor_color)
{
	return ((int)floor_color);
}

int color_ceiling(unsigned long ceiling_color)
{
	return ((int)ceiling_color);
}

void set_player_position(t_data *data)
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

int	parse_file(const char *file_path, t_data *data)
{
	int fd_map;

	data->map_det.lines_file = count_file_lines(file_path);
	if (data->map_det.lines_file < 0)
	{
		error_msg(ERR_MAP, 1);
		return (0);
	}
	fd_map = open(file_path, O_RDONLY);
	if (fd_map < 0)
	{
		error_msg(ERR_FL, 2);
		return (0);
	}
	data->map_det.fd = fd_map;
	data->map_det.path = ft_strdup(file_path);
	if (!parse_textures_and_colors(fd_map, &data->texture_det))
	{
		error_msg(ERR_MAP, 1);
		close(fd_map);
		return (0);
	}
	data->map = init_map(fd_map);
	if (!data->map)
	{
		error_msg(ERR_MAP, 1);
		close(fd_map);
		return (0);
	}
	close(fd_map);
	data->map_det.height = calculate_map_height(data->map);
	data->map_det.width = calculate_map_width(data->map);
	data->map_det.start_i_map = data->map_det.lines_file - data->map_det.height;
	data->map_det.end_i_map = data->map_det.lines_file;
	data->texture_det.floor = malloc(sizeof(int));
	data->texture_det.ceiling = malloc(sizeof(int));
	*(data->texture_det.floor) = color_floor(data->texture_det.hex_floor);
	*(data->texture_det.ceiling) = color_ceiling(data->texture_det.hex_ceiling);
	set_player_position(data);
	return (1);
}
