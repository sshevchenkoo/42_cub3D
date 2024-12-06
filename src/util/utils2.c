#include "../../include/cub3d.h"

static void	free_map(t_data *data);
static void	free_textures(t_texture_det *text_det);

void	free_ptr(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_array_gen(void **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			if (arr[i])
			{
				free_ptr(arr[i]);
				arr[i] = NULL;
			}
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

int	free_data(t_data *data)
{
	if (data)
	{
		if (data->textures)
			free_array_gen((void **)data->textures);
		if (data->texture_pixels)
			free_array_gen((void **)data->texture_pixels);
		free_textures(&data->texture_det);
		free_map(data);
	}
	return (EXIT_FAILURE);
}

static void	free_map(t_data *data)
{
	if (data->map_det.fd > 0)
		close(data->map_det.fd);
	if (data->map_det.file)
		free_array_str(data->map_det.file);
	if (data->map)
		free_array_str(data->map);
}

static void	free_textures(t_texture_det *text_det)
{
	if (text_det->north)
		free_ptr(text_det->north);
	if (text_det->south)
		free_ptr(text_det->south);
	if (text_det->west)
		free_ptr(text_det->west);
	if (text_det->east)
		free_ptr(text_det->east);
	if (text_det->floor)
		free_ptr(text_det->floor);
	if (text_det->ceiling)
		free_ptr(text_det->ceiling);
}
