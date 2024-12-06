#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		ft_isalpha(int argument);
int		ft_isdigit(int argument);
int		ft_isalnum(int argument);
int		ft_isascii(int argument);
int		ft_isprint(int argument);
size_t	ft_strlen(const char *arg);
int		ft_toupper(int argument);
int		ft_tolower(int argument);
char	*ft_strchr(const char *str, int argument);
char	*ft_strrchr(char *str, int argument);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
void	ft_bzero(void *str, size_t len);
void	*ft_memset(void *str, int val, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *s1, const void *s2, size_t n);
size_t	ft_strlcpy(char *des, const char *src, size_t len);
size_t	ft_strlcat(char *des, const char *src, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	*ft_memchr(const void *str, int val, size_t len);
int		ft_memcmp(const void *str1, const void *str2, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t nitems, size_t len);
char	*ft_itoa(int n);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *str, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_isspace(int c);
int		ft_ato_long(const char *str, bool *error);
int		ft_strcmp(const char *s1, const char *s2);
void	free_ptr(void *ptr);
void	free_array_str(char **arr_str);
char	*get_next_line(int fd);
char	*ft_realloc(char *str, size_t size);

#endif
