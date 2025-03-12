/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:13:12 by itykhono          #+#    #+#             */
/*   Updated: 2025/03/12 16:58:04 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_texture(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0);
}

int	is_color(char *line)
{
	return (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

int	parse_texture(char *line, t_texture_det *texture_det)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		texture_det->north = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		texture_det->south = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		texture_det->west = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		texture_det->east = ft_strdup(line + 3);
	else
		return (0);
	return (1);
}

int	handle_color_assignment(char *line, t_texture_det *texture_det, int index)
{
	if (index == 4 && ft_strncmp(line, "F ", 2) == 0)
		texture_det->hex_floor = parse_color(line + 2);
	else if (index == 5 && ft_strncmp(line, "C ", 2) == 0)
	{
		texture_det->hex_ceiling = parse_color(line + 2);
		return (1);
	}
	else
		return (0);
	return (1);
}

int	process_texture_or_color(char *line, t_texture_det *texture_det, int i)
{
	trim_newline(line);
	if (i < 4)
		return (parse_texture(line, texture_det));
	return (handle_color_assignment(line, texture_det, i));
}
