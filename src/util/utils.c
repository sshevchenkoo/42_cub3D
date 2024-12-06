#include "../../include/cub3d.h"

int	error_msg(char *msg, int status_code)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	return (status_code);
}

//functio for MacOS
void	exit_and_free(t_data *data, int s_code)
{
	if (!data)
		exit(s_code);
		
	// Уничтожаем окно, если оно создано
	if (data->view.win && data->view.mlx)
		mlx_destroy_window(data->view.mlx, data->view.win);

	// Освобождаем указатель на mlx, если он был создан
	if (data->view.mlx)
		free(data->view.mlx);

	// Освобождаем другие данные структуры
	free_data(data);
	exit(s_code);
}

void	exit_cube(t_data *data, int exit_code)
{
	free_data(data);
	exit(exit_code);
}
