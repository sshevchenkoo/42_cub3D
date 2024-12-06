#include "../../include/cub3d.h"

void	spaces_to_wall(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (is_white_space(data->map[i][j]) == true)
			j++;
		while (data->map[i][j])
		{
			if (data->map[i][j] == C_WHITE_S)
				data->map[i][j] = C_WALL;
			j++;
		}
		i++;
	}
}
