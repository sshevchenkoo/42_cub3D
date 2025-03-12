/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:29:32 by itykhono          #+#    #+#             */
/*   Updated: 2025/03/12 16:57:39 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
