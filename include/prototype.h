#ifndef PROTOTYPE_H
# define PROTOTYPE_H

int parse_file(const char *file_path, t_data *data);
void	exit_cube(t_data *data, int exit_code);
void	exit_and_free(t_data *data, int s_code);
int	error_msg(char *msg, int status_code);
void	free_ptr(void *ptr);
void	free_array_gen(void **arr);
int	free_data(t_data *data);
bool	is_white_space(char c);
void	init_img(t_data *data, t_img *i, int width, int height);
void	set_image_pixel(t_img *image, int x, int y, int color);
void	init_texture_img(t_data *data, t_img *image, char *path);
void	spaces_to_wall(t_data *data);
void	init_texture_pixels(t_data *data);
void	update_text_pixels(t_data *data, t_texture_det *tex, t_ray *r, int x);
void	setup_textures(t_data *data);
int	set_player_direction(t_player *p);
int	rotate(double *x, double *y, double angle);
int	move(t_data *d, double dx, double dy);
int	render_images(t_data *data);
void	calc_dda(t_ray *ray, t_player *p);
void	perform_dda(t_data *data, t_ray *ray);
void	calculate_line_height(t_ray *ray, t_player *player);
void	setup_raycast_info(int x, t_ray *ray, t_player *player);
int	close_hook(t_data *d);
int key_hook(int key, t_data *d);
int	starting_game(t_data *d);
int is_map_closed(char **map);

#endif
