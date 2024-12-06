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
