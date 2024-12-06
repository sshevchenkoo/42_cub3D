#include "../../include/cub3d.h"

bool	is_white_space(char c)
{
	if (c == C_WHITE_S || c == '\t' || c == '\n')
		return (true);
	return (false);
}

void	init_img(t_data *data, t_img *i, int width, int height)
{
	i->img = mlx_new_image(data->view.mlx, width, height);
	if (i->img == NULL)
		exit_and_free(data, error_msg(ERR_MLX_IMG, 20));
	i->addr = (int *)mlx_get_data_addr(i->img, &i->pixel_bits,
			&i->size_line, &i->endian);
	return ;
}

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

void	init_texture_img(t_data *data, t_img *image, char *path)
{
	image->img = mlx_xpm_file_to_image(data->view.mlx, path,
			&data->texture_det.size, &data->texture_det.size);
	if (image->img == NULL)
		exit_and_free(data, error_msg(ERR_MLX_IMG, 21));
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
	return ;
}
