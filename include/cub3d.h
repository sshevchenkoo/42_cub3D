#ifndef CUB3D_H
# define CUB3D_H

# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>

# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>

# include "../lib/libft/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include "./enum.h"
# include "./define.h"
# include "./struct.h"
# include "./prototype.h"

// === PARSE FUNCTIONS (parse.c) ===
int		parse_textures_and_colors(int fd_map, t_texture_det *texture_det);
int		parse_file(const char *file_path, t_data *data);
int		open_and_validate_file(const char *file_path, t_data *data);
int		initialize_map(t_data *data);
void	allocate_colors(t_data *data);

// === TEXTURE PARSING (parse_textures.c) ===
int		is_texture(char *line);
int		is_color(char *line);
int		parse_texture(char *line, t_texture_det *texture_det);
int		handle_color_assignment(char *line, t_texture_det *texture_det,
			int index);
int		process_texture_or_color(char *line, t_texture_det *texture_det, int i);

// === MAP INITIALIZATION (init_map.c) ===
char	**init_map(int fd_map);
char	**expand_map_capacity(char **map, int *capacity, int size);
int		add_map_row(char *row, char ***map, int *i, int *capacity);
int		calculate_map_height(char **map);
int		calculate_map_width(char **map);

// === UTILITY FUNCTIONS (parse_helpers.c) ===
int		ft_strcmp(const char *s1, const char *s2);
char	*trim_newline(char *str);
int		parse_color(const char *color_str);
int		color_floor(unsigned long floor_color);
int		color_ceiling(unsigned long ceiling_color);

// === GAME SETUP (game_setup.c) ===
void	set_player_position(t_data *data);
int		count_file_lines(const char *file_path);

#endif
