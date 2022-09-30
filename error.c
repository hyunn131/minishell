/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:07:19 by docho             #+#    #+#             */
/*   Updated: 2022/09/30 19:08:19 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminate(char *str)
{
	if (str)
		printf("%s", str);
	else if (errno != 0)
		strerror(errno);
	exit(1);
}

void	e_close(int fd)
{
	if (close(fd) < 0)
		terminate(0);
}

void	e_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		terminate(0);
	}
}

pid_t	e_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		terminate(0);
	}
	return (pid);
}

void	syntex_err(char *str)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	if (!ft_strncmp(str, ">>", 2))
		ft_putstr_fd(">>", 2);
	else if (!ft_strncmp(str, ">", 1))
		ft_putstr_fd(">", 2);
	else if (!ft_strncmp(str, "<<", 2))
		ft_putstr_fd("<<", 2);
	else if (!ft_strncmp(str, "<", 1))
		ft_putstr_fd("<", 2);
	else if (!ft_strncmp(str, "|", 1))
		ft_putstr_fd("|", 2);
	else if (!ft_strncmp(str, "\0", 1))
		ft_putstr_fd("newline", 2);
	ft_putendl_fd("'", 2);
}