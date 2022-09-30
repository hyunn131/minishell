/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:55:26 by docho             #+#    #+#             */
/*   Updated: 2022/09/30 18:05:31 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>
# include <stdlib.h>
# include <signal.h>
# include "./libft/libft.h"

typedef struct s_info{
	char	**argv;
	char	**envp;
	int		*lens;
	int		cnt;
	int		fd[2];
	int		inputfd;
	int		pid;
	int		exit_n;
}				t_info;


void    free2d(char **ss);
void    terminate(char *str);
void    e_close(int fd);
void    e_pipe(int *fd);
pid_t	e_fork();
bool    ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
char	*joinpath(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void    process(t_info *info);
int     e_wait(pid_t pid);
bool    input(char *filename, int *fd);
bool	output(char *filename, int *fd);
bool	append(char *filename, int *fd);
bool	here_doc(char *limiter, int *fd);
bool	isbuiltin(t_info *info);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
void	splits(char *buffer, t_info *info);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_substr2(char const *s, unsigned int start, size_t len);
char	*ft_strjoin2(char const *s1, char const *s2);
void	*ft_memset(void *b, int c, size_t len);
void	dollar(char **pbuffer, t_info *info);
void	exec_cmd(char *str, t_info *info);
void	syntex_err(char *str);

char	*working_directory(void);
char	**change_env(char *key_and_val, char **envp);
int	ft_count_matrix(char **envp);
int	ft_strncmp_equalsign(char *s1, char *s2, int len);

#endif
