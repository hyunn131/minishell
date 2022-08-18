/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:14:45 by docho             #+#    #+#             */
/*   Updated: 2022/08/18 20:52:23 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_err(char *cmd, int )
{
}

void	connect_io(char **cmd, int *fd)
{
	int	i;
	int	n;

	i = -1;
	while (cmd[++i])
	{
		if (ft_strcmp(cmd[i], "<"))
			input(cmd[i + 1], fd);
		else if (ft_strcmp(cmd[i], "<<"))
			here_doc(cmd[i + 1], fd);
		else if (ft_strcmp(cmd[i], ">"))
			output(cmd[i + 1], fd);
		else if (ft_strcmp(cmd[i], ">>"))
			append(cmd[i + 1], fd);
	}
}

void    process(char **cmd, char **envp, int *iofd)
{
	int		fd[2];
	pid_t	pid;

	e_pipe(fd);
	pid = e_fork();
	if (pid == 0)
	{
		if (iofd[1] != -1)
		{
			e_close(fd[1]);
			fd[1] = iofd[1];
		}
		e_close(fd[0]);
		dup2(iofd[0], 0);
		dup2(fd[1], 1);
		if (execve(argv[0], argv, envp) == -1)
			cmd_err(argv[0]);
	}
	else
	{
		e_close(fd[1]);
		e_close(iofd[0]);
		if (iofd[1] != -1)
			e_close(iofd[1]);
		iofd[0] = fd[0];
	}
}

void	exec_cmd(char ***arr, char **envp)
{
	int		i;
	int		len;
	int		fd[2];
	pid_t	*pids;

	len = 0;
	while (arr[len])
		len++;
	pids = (pid_t *)malloc()
	fd[0] = -1;
	fd[1] = -1;
	i = -1;
	while (arr[++i])
	{
		process(arr[i], envp, fd);
	}
	e_close(fd[0]);
}