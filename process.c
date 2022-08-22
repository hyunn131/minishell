/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:54:58 by docho             #+#    #+#             */
/*   Updated: 2022/08/22 16:29:49 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	connectpath(char **argv0, char *ss)
{
	DIR				*dptr;
	struct dirent	*dir;
	int				i;

	i = -1;
	while (ss[++i])
	{
		dptr = opendir(ss[i]);
		if (!dptr)
			terminate();
		dir = readdir(dir);
		while (dir != NULL)
		{
			if (ft_strcmp(*argv0, dir->dname))
			{
				*argv0 = joinpath(ss[i], *argv0);
				if (!(*argv0))
					terminate();
			}
		}
		if (errno != 0)
			terminate();
		if (!closedir(dir))
			terminate();
	}
}

void	cmdpath(char **argv0)
{
	char	*s;
	char	*ss;

	s = getenv("PATH");
	if (!s)
		terminate();
	ss = ft_split(s, ':');
	if (!ss)
		terminate();
	connectpath(argv0, ss);
	free2d(ss);
}

void	in_child_do_cmd(char **argv, char **envp)
{
	if (!isbuiltin(argv, envp))
	{
		if (execve(cmdpath(&argv[0]), argv, envp) == -1)
			cmd_err(argv[0]);//에러처리
	}
}

void    process(char **argv, char **envp, int *iofd, pid_t *p_pid)
{
	int		fd[2];
	pid_t	pid;

	e_pipe(fd);
	pid = e_fork();
	if (iofd[1] != -1)
	{
		e_close(fd[1]);
		fd[1] = iofd[1];
	}
	if (pid == 0)
	{
		e_close(fd[0]);
		dup2(iofd[0], 0);
		dup2(fd[1], 1);
		in_child_do_cmd(argv, envp);
	}
	else
	{
		*p_pid = pid;
		e_close(fd[1]);
		if (iofd[0] != 0)
			e_close(iofd[0]);
		iofd[0] = fd[0];
	}
}

int	e_wait(pid_t *pids, int len)
{
	int		i;
	int		status;

	pid_t	w_pid;

	i = 0;
	while (i < len)
	{
		w_pid = waitpid(pids[i], &status, 0);
		if (w_pid == -1)
			terminate();
		i++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));//정상종료 안될 시 리턴 값 없는데 어떻게 할 건지 malloc 처리하거나, 8비트 이상의 값을 리턴하거나(257)
	//if (WIFSIGNALED(status))
	//	WTERMSIG(status);
	return (1 << 8);
}