/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:05:38 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/09 13:57:18 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>

/*ft_gnl*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);

/*ft_is*/
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_iscount(int c, char *base);
int		ft_isdigit(int c);
int		ft_ishexdigit(int c);
int		ft_isin(int c, char *base);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_isspacenl(int c);
int		ft_iswhere(int c, char *base);

/*ft_lst*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

/*ft_math*/
int		ft_abs(long n);
int		ft_baselen(long n, int base);
int		ft_hexlen(unsigned	int num);
int		ft_nbrlen(long n);
int		ft_power(int nbr, int pow);

/*ft_mem*/
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memdel(void *ptr);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *str, int c, size_t len);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

/*ft_printf*/
int		ft_printf(const char *str, ...);
int		ft_printstr(char *str);
int		ft_printchar(int c);
int		ft_printptr(unsigned long long ptr);
int		ft_printnbr(int n);
int		ft_printunsigned(unsigned int n);
int		ft_printhex(unsigned int num, const char format);

/*ft_put*/
void	ft_putchar_fd(char c, int fd);
void	ft_putchar(char c);
void	ft_putendl_fd(char *s, int fd);
void	ft_putendl(char *s);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr(int n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr(char *s);

/*ft_skip*/
void	ft_skip_char(const char *str, int *i, char c);
void	ft_skip_chars(const char *str, int *i, char *base);
void	ft_skip_space(const char *str, int *i);
void	ft_skip_spacenl(const char *str, int *i);

/*ft_str*/
char	**ft_split(char const *s, char c);
char	*ft_strchr(char const *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *str);
int		ft_strisnum(const char *str);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(char *s, int c);
char	*ft_strtok(char *str, char delim);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

/*ft_to*/
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_tolower(int c);
int		ft_toupper(int c);

#endif
