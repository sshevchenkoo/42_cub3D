#include "../../include/cub3d.h"

void	calc_dda(t_ray *ray, t_player *p)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (p->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - p->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (p->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - p->pos_y) * ray->delta_dist_y;
	}
}

void	perform_dda(t_data *data, t_ray *ray)
{
	while (true)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->hit_side = false;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->hit_side = true;
		}
		if (ray->map_y < 0 || ray->map_x < 0 || !data->map[ray->map_y]
			|| !data->map[ray->map_y][ray->map_x])
			break ;
		if (data->map[ray->map_y][ray->map_x] == C_WALL)
			break ;
	}
}

void	calculate_line_height(t_ray *ray, t_player *player)
{
	if (ray->hit_side == false)
		ray->perp_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(HEIGHT / ray->perp_dist);
	ray->draw_start = -(ray->line_height) / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	if (ray->hit_side == false)
		ray->wall_x = player->pos_y + ray->perp_dist * ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->perp_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

void	setup_raycast_info(int x, t_ray *ray, t_player *player)
{
	ray->multiplier = 2 * x / (double)WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->multiplier;
	ray->dir_y = player->dir_y + player->plane_y * ray->multiplier;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
}
