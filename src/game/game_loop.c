#include "../../include/cub3d.h"

// ffunction for MacOS
int	close_hook(t_data *d)
{
	mlx_destroy_image(d->view.mlx, d->view.screen.img);
	mlx_destroy_window(d->view.mlx, d->view.win);
	//mlx_destroy_display(d->view.mlx);
	free_data(d);
	free(d->view.mlx);
	exit(SUCCESS);
}

int key_hook(int key, t_data *d)
{
    if (key == ESCAPE_KEY)
        close_hook(d);
    if (key == W_KEY)
        move(d, d->player.dir_x, d->player.dir_y);
    if (key == S_KEY)
        move(d, -d->player.dir_x, -d->player.dir_y);
    if (key == A_KEY)
        move(d, -d->player.plane_x, -d->player.plane_y);
    if (key == D_KEY)
        move(d, d->player.plane_x, d->player.plane_y);
    if (key == LEFT_ARROW_KEY)
    {
        rotate(&d->player.dir_x, &d->player.dir_y, -ROTSPEED);
        rotate(&d->player.plane_x, &d->player.plane_y, -ROTSPEED);
    }
    if (key == RIGHT_ARROW_KEY)
    {
        rotate(&d->player.dir_x, &d->player.dir_y, ROTSPEED);
        rotate(&d->player.plane_x, &d->player.plane_y, ROTSPEED);
    }
    return (SUCCESS);
}

int	starting_game(t_data *d)
{
	// Используем 17 как код события закрытия окна и 2 для нажатия клавиш на macOS
	mlx_hook(d->view.win, 17, 0, close_hook, d);       // 17 — событие закрытия окна
	mlx_hook(d->view.win, 2, 0, key_hook, d);          // 2 — событие нажатия клавиши
	mlx_loop_hook(d->view.mlx, render_images, d);      // Цикл рендеринга изображения
	return (SUCCESS);
}
