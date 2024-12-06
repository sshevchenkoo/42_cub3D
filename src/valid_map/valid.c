#include "../../include/cub3d.h"

int check_first_last_row(char *row)
{
    int i = 0;

	i = 0;
    while (row[i])
    {
        if (row[i] == '0')
            return (0);
        i++;
    }
    return (1);
}

int check_sides_and_spaces(char **map, int total_rows)
{
    int i;
	int row_len;
    int first_wall;
    int last_wall;
    int j;

	i = 1;
    while (i < total_rows - 1)
    {
        row_len = ft_strlen(map[i]);
        first_wall = -1;
        last_wall = -1;
        j = 0;

        while (j < row_len)
        {
            if (map[i][j] == '1' || map[i][j] == '0')
            {
                if (first_wall == -1)
                    first_wall = j;
                last_wall = j;
            }
            j++;
        }

        if (first_wall != -1)
        {
            if (map[i][first_wall] != '1' || map[i][last_wall] != '1')
                return (0);

            j = first_wall;
            while (j <= last_wall)
            {
                if (map[i][j] == ' ' && (map[i][j - 1] == '0' || map[i][j + 1] == '0'))
                    return (0);
                j++;
            }
        }
        i++;
    }
    return (1);
}

int is_map_closed(char **map)
{
    int total_rows;

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
