/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:12:59 by itykhono          #+#    #+#             */
/*   Updated: 2025/03/13 13:13:01 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *str, size_t size)
{
	char	*temp;

	if (!str)
		return (NULL);
	else
	{
		temp = (char *)malloc(sizeof(char) * (size));
		ft_strlcpy(temp, str, size + 1);
		free(str);
	}
	if (!temp)
		return (NULL);
	return (temp);
}
