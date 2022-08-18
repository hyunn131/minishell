/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:54:58 by docho             #+#    #+#             */
/*   Updated: 2022/08/18 20:52:24 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	cmd_err(char *cmd, int )
{
}

void    process(char **argv, char **envp, int *iofd)
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