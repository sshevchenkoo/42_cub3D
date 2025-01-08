#include "../../include/cub3d.h"

int	check_first_last_row(char *row)
{
	int i;

	i = 0;
	while (row[i])
	{
		if (row[i] == '0')
			return (0);
		i++;
	}
	return (1);
}

int	find_walls_in_row(char *row, int row_len, int *first_wall, int *last_wall)
{
	int j;

	j = 0;
	*first_wall = -1;
	*last_wall = -1;
	while (j < row_len)
	{
		if (row[j] == '1' || row[j] == '0')
		{
			if (*first_wall == -1)
				*first_wall = j;
			*last_wall = j;
		}
		j++;
	}

	return (*first_wall != -1);
}

int	validate_spaces_between_walls(char *row, int first_wall, int last_wall)
{
	int	j;

	j = first_wall;
	while (j <= last_wall)
	{
		if (row[j] == ' ' && (row[j - 1] == '0' || row[j + 1] == '0'))
			return (0);
		j++;
	}
	return (1);
}

int	check_sides_and_spaces(char **map, int total_rows)
{
	int	i;
	int	row_len;
	int	first_wall;
	int	last_wall;

	i = 1;
	while (i < total_rows - 1)
	{
		row_len = ft_strlen(map[i]);
		if (find_walls_in_row(map[i], row_len, &first_wall, &last_wall))
		{
			if (map[i][first_wall] != '1' || map[i][last_wall] != '1')
				return (0);
			if (!validate_spaces_between_walls(map[i], first_wall, last_wall))
				return (0);
		}
		i++;
	}
	return (1);
}



int	is_map_closed(char **map)
{
	int	total_rows;

	total_rows = 0;
	while (map[total_rows])
		total_rows++;
	printf("%d\n", total_rows);
	if (!check_first_last_row(map[0]))
	{
		printf("first\n");
		return (0);
	}
	if (!check_first_last_row(map[total_rows - 1]))
	{
		printf("last\n");
		return (0);
	}
	if (!check_sides_and_spaces(map, total_rows))
	{
		printf("side, spaces\n");
		return (0);
	}
	return (1);
}
