/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libms.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjimpei <yjimpei@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:17:56 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/03/02 17:38:20 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMS_H
# define LIBMS_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*prev;
	struct s_list	*next;
}				t_list;

void	*ms_memset(void *b, int c, size_t len);
void	ms_bzero(void *s, size_t n);
void	*ms_memcpy(void *dst, const void *src, size_t n);
void	*ms_memccpy(void *dst, const void *src, int c, size_t n);
void	*ms_memmove(void *dst, const void *src, size_t len);
void	*ms_memchr(const void *s, int c, size_t n);
int		ms_memcmp(const void *s1, const void *s2, size_t n);
size_t	ms_strlen(const char *s);
size_t	ms_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ms_strlcat(char *dst, const char *src, size_t dstsize);
char	*ms_strchr(const char *s, int c);
char	*ms_strrchr(const char *s, int c);
char	*ms_strnstr(const char *haystack, const char *needle, size_t len);
int		ms_strncmp(const char *s1, const char *s2, size_t n);
int		ms_strcmp(const char *s1, const char *s2);
int		ms_atoi(const char *str);
int		ms_isalpha(int c);
int		ms_isdigit(int c);
int		ms_isalnum(int c);
int		ms_isascii(int c);
int		ms_isprint(int c);
int		ms_isspace(int c);
int		ms_toupper(int c);
int		ms_tolower(int c);
int		ms_int_check(unsigned int input, unsigned int num, int minus);
void	*ms_calloc(size_t count, size_t size);
char	*ms_strdup(const char *s1);
char	*ms_strndup(const char *s1, size_t n);
char	*ms_substr(char const *s, unsigned int start, size_t len);
char	*ms_strjoin(char const *s1, char const *s2);
char	*ms_strtrim(char const *s1, char const *set);
char	**ms_split(char const *s, char c);
char	*ms_itoa(int n);
char	*ms_strmapi(char const *s, char (*f)(unsigned int, char));
void	ms_striteri(char *s, void (*f)(unsigned int, char *));
void	ms_putchar_fd(char c, int fd);
void	ms_putstr_fd(char *s, int fd);
void	ms_putendl_fd(char *s, int fd);
void	ms_putnbr_fd(int n, int fd);
t_list	*ms_lstnew(void *content);
void	ms_lstadd_front(t_list **lst, t_list *new);
int		ms_lstsize(t_list *lst);
t_list	*ms_lstlast(t_list *lst);
void	ms_lstadd_back(t_list **lst, t_list *new);
void	ms_lstdelone(t_list *lst, void (*del)(void *));
void	ms_lstclear(t_list **lst, void (*del)(void *));
void	ms_lstiter(t_list *lst, void (*f)(void *));
t_list	*ms_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ms_error(char *msg);
void	*ms_xmalloc(size_t size);
char	*ms_strcpy(char *dst, const char *src);
char	*ms_strcat(char *dst, const char *src);
char	*ms_strappend(char *body, char *add);
void	ms_split_free(char **split);
int		ms_isnum_string(char *str);
char	*ms_char_replace(char *str, char old, char new);

#endif
