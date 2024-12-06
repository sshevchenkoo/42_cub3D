#include "../../include/cub3d.h"

static int	calc_raycast(t_data *d)
{
	d->view.x = 0;
	while (d->view.x < WIDTH)
	{
		setup_raycast_info(d->view.x, &d->ray, &d->player);
		calc_dda(&d->ray, &d->player);
		perform_dda(d, &d->ray);
		calculate_line_height(&d->ray, &d->player);
		update_text_pixels(d, &d->texture_det, &d->ray, d->view.x);
		d->view.x++;
	}
	return (SUCCESS);
}

static int	render_frame(t_data *d)
{
	d->view.y = 0;
	while (d->view.y < HEIGHT)
	{
		d->view.x = 0;
		while (d->view.x < WIDTH)
		{
			if (d->texture_pixels[d->view.y][d->view.x] > 0)
				d->view.color = d->texture_pixels[d->view.y][d->view.x];
			else if (d->view.y < HEIGHT / 2)
				d->view.color = d->texture_det.hex_ceiling;
			else if (d->view.y < HEIGHT - 1)
				d->view.color = d->texture_det.hex_floor;
			set_image_pixel(&d->view.screen, d->view.x, \
			d->view.y, d->view.color);
			d->view.x++;
		}
		d->view.y++;
	}
	return (SUCCESS);
}

int	render_images(t_data *data)
{
	init_texture_pixels(data);
	calc_raycast(data);
	render_frame(data);
	mlx_put_image_to_window(data->view.mlx, data->view.win, \
	data->view.screen.img, 0, 0);
	return (0);
}
