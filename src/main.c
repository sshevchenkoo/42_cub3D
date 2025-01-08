#include "../include/cub3d.h"

static void	starting_view(t_data *data)
{
	data->view.mlx = mlx_init();
	if (data->view.mlx == NULL)
	{
		error_msg(ERR_MLX_INIT, 5);
		exit(EXIT_FAILURE);
	}
	setup_textures(data);
	set_player_direction(&data->player);
	data->view.win = mlx_new_window(data->view.mlx, WIDTH, HEIGHT, TITLE);
	if (data->view.win == NULL)
	{
		error_msg(ERR_MLX_WIN, 5);
		exit(EXIT_FAILURE);
	}
	init_img(data, &data->view.screen, WIDTH, HEIGHT);
}

void print_texture_det(t_texture_det *texture) {
    printf("Texture Details:\n");
    printf("  North: %s\n", texture->north);
    printf("  South: %s\n", texture->south);
    printf("  West: %s\n", texture->west);
    printf("  East: %s\n", texture->east);
    printf("  Floor Color: %p\n", texture->floor);
    printf("  Ceiling Color: %p\n", texture->ceiling);
    printf("  Hex Floor: %lu\n", texture->hex_floor);
    printf("  Hex Ceiling: %lu\n", texture->hex_ceiling);
    printf("  Size: %d\n", texture->size);
    printf("  Index: %d\n", texture->index);
    printf("  Step: %f\n", texture->step);
    printf("  Pos: %f\n", texture->pos);
    printf("  X: %d, Y: %d\n", texture->x, texture->y);
}

void print_map_det(t_map_det *map) {
    printf("Map Details:\n");
    printf("  FD: %d\n", map->fd);
    printf("  Lines in File: %d\n", map->lines_file);
    printf("  Path: %s\n", map->path);
    printf("  Height: %d, Width: %d\n", map->height, map->width);
    printf("  Start of Map Index: %d\n", map->start_i_map);
    printf("  End of Map Index: %d\n", map->end_i_map);
}

void print_player(t_player *player) {
    printf("Player Details:\n");
    printf("  Direction: %c\n", player->dir);
    printf("  Position X: %f, Y: %f\n", player->pos_x, player->pos_y);
    printf("  Direction X: %f, Y: %f\n", player->dir_x, player->dir_y);
    printf("  Plane X: %f, Y: %f\n", player->plane_x, player->plane_y);
    printf("  Has Moved: %d\n", player->has_moved);
    printf("  Move X: %d, Move Y: %d\n", player->move_x, player->move_y);
    printf("  Rotate: %d\n", player->rotate);
}

void print_ray(t_ray *ray) {
    printf("Ray Details:\n");
    printf("  Multiplier: %f\n", ray->multiplier);
    printf("  Direction X: %f, Y: %f\n", ray->dir_x, ray->dir_y);
    printf("  Map X: %d, Y: %d\n", ray->map_x, ray->map_y);
    printf("  Step X: %d, Y: %d\n", ray->step_x, ray->step_y);
    printf("  Side Dist X: %f, Side Dist Y: %f\n", ray->side_dist_x, ray->side_dist_y);
    printf("  Delta Dist X: %f, Delta Dist Y: %f\n", ray->delta_dist_x, ray->delta_dist_y);
    printf("  Perp Dist: %f\n", ray->perp_dist);
    printf("  Wall X: %f\n", ray->wall_x);
    printf("  Hit Side: %d\n", ray->hit_side);
    printf("  Line Height: %d\n", ray->line_height);
    printf("  Draw Start: %d, Draw End: %d\n", ray->draw_start, ray->draw_end);
}

void print_img(t_img *img) {
    printf("Image Details:\n");
    printf("  Image Ptr: %p\n", img->img);
    printf("  Address: %p\n", img->addr);
    printf("  Pixel Bits: %d\n", img->pixel_bits);
    printf("  Size Line: %d\n", img->size_line);
    printf("  Endian: %d\n", img->endian);
}

void print_view(t_view *view) {
    printf("View Details:\n");
    printf("  X: %d, Y: %d\n", view->x, view->y);
    printf("  Color: %d\n", view->color);
    printf("  MLX Ptr: %p\n", view->mlx);
    printf("  Window Ptr: %p\n", view->win);
    print_img(&view->screen);
}

void print_data(t_data *data) {
    printf("Data Details:\n");
    print_view(&data->view);
    print_ray(&data->ray);
    print_map_det(&data->map_det);
    print_texture_det(&data->texture_det);
    print_player(&data->player);
    printf("Map:\n");
    for (int i = 0; data->map && data->map[i]; i++) {
        printf("  %s\n", data->map[i]);
    }
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (error_msg(ERR_ARGS, 1));
	ft_bzero(&data, sizeof(t_data));
	if (!parse_file(argv[1], &data))
	{
		error_msg(ERR_FL, 1);
		return EXIT_FAILURE;
	}
	print_data(&data);
	if (!is_map_closed(data.map))
        	return(error_msg(ERR_MAP, 1), 1);
	starting_view(&data);
	starting_game(&data);
	mlx_loop(data.view.mlx);
	return (EXIT_SUCCESS);
}
