/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:42:51 by itykhono          #+#    #+#             */
/*   Updated: 2025/03/12 16:58:31 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*trim_newline(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	return (str);
}

int	parse_color(const char *color_str)
{
	int	r;
	int	g;
	int	b;

	if (sscanf(color_str, "%d,%d,%d", &r, &g, &b) != 3)
	{
		error_msg(ERR_RGB_VAL, 1);
		return (-1);
	}
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
	{
		error_msg(ERR_RGB_VAL, 1);
		return (-1);
	}
	return ((r << 16) | (g << 8) | b);
}

int	color_floor(unsigned long floor_color)
{
	return ((int)floor_color);
}

int	color_ceiling(unsigned long ceiling_color)
{
	return ((int)ceiling_color);
}
