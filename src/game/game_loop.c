#include "../../include/cub3d.h"

int	close_hook(t_data *d)
{
	mlx_destroy_image(d->view.mlx, d->view.screen.img);
	mlx_destroy_window(d->view.mlx, d->view.win);
	mlx_destroy_display(d->view.mlx);
	free_data(d);
	free(d->view.mlx);
	exit(SUCCESS);
}

int	key_hook(int key, t_data *d)
{
	if (key == XK_Escape)
		close_hook(d);
	if (key == XK_w)
		move(d, d->player.dir_x, d->player.dir_y);
	if (key == XK_s)
		move(d, -d->player.dir_x, -d->player.dir_y);
	if (key == XK_a)
		move(d, -d->player.plane_x, -d->player.plane_y);
	if (key == XK_d)
		move(d, d->player.plane_x, d->player.plane_y);
	if (key == XK_Left)
	{
		rotate(&d->player.dir_x, &d->player.dir_y, -ROTSPEED);
		rotate(&d->player.plane_x, &d->player.plane_y, -ROTSPEED);
	}
	if (key == XK_Right)
	{
		rotate(&d->player.dir_x, &d->player.dir_y, ROTSPEED);
		rotate(&d->player.plane_x, &d->player.plane_y, ROTSPEED);
	}
	return (SUCCESS);
}

int	starting_game(t_data *d)
{
	mlx_hook(d->view.win, DestroyNotify, StructureNotifyMask, close_hook, d);
	mlx_hook(d->view.win, KeyPress, KeyPressMask, key_hook, d);
	mlx_loop_hook(d->view.mlx, render_images, d);
	return (SUCCESS);
}
