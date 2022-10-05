/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:59:31 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/06 08:20:16 by docho            ###   ########.fr       */
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
# include <termios.h>

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

void	free2d(char **ss);
void	terminate(char *str);
void	e_close(int fd);
void	e_pipe(int *fd);
pid_t	e_fork(void);
bool	ft_strcmp(char *s1, char *s2);
char	*joinpath(char *s1, char *s2);
void	process(t_info *info);
int		e_wait(t_info *info);
bool	input(char *filename, int *fd);
bool	output(char *filename, int *fd);
bool	append(char *filename, int *fd);
bool	here_doc(char *limiter, int *fd);
bool	isbuiltin(t_info *info);
void	splits(char *buffer, t_info *info);
char	*ft_substr2(char *s, unsigned int start, size_t len);
char	*ft_strjoin2(char const *s1, char const *s2);
void	dollar(char **pbuffer, t_info *info);
void	exec_cmd(char *str, t_info *info);
void	syntex_err(char *str);
void	returning(t_info *info);
bool	func(t_info *info);
void	cmd_err(char *cmd, t_info *info);
void	free_argv(char **argv);
void	print_echo_char(char *argv, int fd);
void	print_echo(char **argv, int start, int fd);
int		echo(t_info *info);
char	*build_path(char **argv, int *flag);
void	change_pwd(t_info *info, char *new_path);
void	change_old_pwd(t_info *info, char *old_path);
int		cd(t_info *info);
int		env(t_info *info);
char	*working_directory(void);
int		pwd(t_info *info);
int		check_env_name(char *name);
void	print_unset_invalid(char *varname);
void	matrix_free(char **matrix, int index);
char	**remove_one_var(char **envp, int index);
char	**unset_var(char *varname, char **envp);
int		unset(t_info *info);
void	exit_error_message(char *message, char *non_numeric);
int		is_all_digit(char *str);
int		f_exit(char **argv);
int		ft_strncmp_equalsign(char *s1, char *s2, int len);
int		ft_count_matrix(char **envp);
char	*ft_envp_copy(char **envp, int index);
char	**new_added_envp(char *key_and_val, char **envp, int count);
int		ft_strlen_key(char *key_and_val);
char	**change_env(char *key_and_val, char **envp);
int		ft_count_matrix(char **envp);
int		ft_strncmp_equalsign(char *s1, char *s2, int len);
void	print_export_invalid(char *varname);
int		check_export_valid(char *argv);
int		export(t_info *info);
bool	isbuiltin(t_info *info);
char	*ft_getenv(char *str, t_info *info);
void	echoctl_flag_off(void);
void	echoctl_flag_on(void);
void	sig_handler(int sig);
void	ft_sort_matrix(char **arr, int len);
void	sort_and_print(char **envp, int fd);
void	ft_put_envp_with_qou_fd(char *arr, int fd);
char	**ft_dup_matrix(char **arr);
void	if_not_changed(t_info *info, char *new_path, char *old_path, int flag);
void	if_dir_changed(t_info *info, char *new_path, char *old_path, int flag);
bool	line_check(char **s, t_info *info);
void	counting2(char *buffer, int *pi);
void	pipecount(char *str, t_info *info);

#endif
