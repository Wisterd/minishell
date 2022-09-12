/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 18:57:46 by mvue              #+#    #+#             */
/*   Updated: 2022/09/12 19:29:17 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stddef.h>

# define MALLOC 0
# define FREE 1
# define END 2
# define INIT 3

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_garbage
{
	void				*pointer;
	struct s_garbage	*next;
	struct s_garbage	*prev;
}	t_garbage;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strdup_perm(const char *s1);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
size_t	ft_strlen(const char *str);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **alst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	free_all(t_garbage **l_garbage);
void	add_front(t_garbage **l_garbage, void *pointer);
void	rm_ele(t_garbage **l_garbage, void *pointer);
void	ft_garbage_collector(int mode, void *pointer);
void	ft_garbage_collector_perm(int mode, void *pointer);
void	*ft_malloc(int size);
void	*ft_malloc_perm(int size);
void	ft_free(void *pointer);
void	ft_free_perm(void *pointer);

// Nouvelle fct ajouter lors de minishell

char	*ft_strldup(const char *s1, size_t size);
char	*ft_strjoin_2free(char *s1, char *s2);
char	*ft_strjoin_1free(char *s1, char *s2);
char	*ft_strjoin_1free_perm(char *s1, char *s2);
char	*ft_str_deldeb(char *str, int len);

#endif