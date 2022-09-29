/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:54:58 by docho             #+#    #+#             */
/*   Updated: 2022/09/29 19:35:25 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	connectpath2(DIR *dptr)
{
	if (errno != 0)
		terminate(0);
	if (closedir(dptr) == -1)
		terminate(0);
}

static void	connectpath(char **argv0, char **ss)
{
	DIR				*dptr;
	struct dirent	*dir;
	int				i;

	i = -1;
	while (ss[++i])
	{
		dptr = opendir(ss[i]);
		if (!dptr)
			terminate(0);
		errno = 0;
		dir = readdir(dptr);
		while (dir != NULL)
		{
			if (ft_strcmp(*argv0, dir->d_name))
			{
				*argv0 = joinpath(ss[i], *argv0);
				if (!(*argv0))
					terminate(0);
				break ;
			}
			dir = readdir(dptr);
		}
		connectpath2(dptr);
	}
}

void	in_child_do_cmd(char **argv, char ***envp)
{
	char	*path;
	char	**ss;

	if (!isbuiltin(argv, envp))
	{
		path = getenv("PATH");
		if (!path)
			terminate(0);
		ss = ft_split(path, ':');
		if (!ss)
			terminate(0);
		connectpath(&argv[0], ss);
		free2d(ss);
		if (execve(argv[0], argv, *envp) == -1)
			;//cmd_err(argv[0]);//에러처리
	}
}

void	process(t_info *info)
{
	info->pid = e_fork();
	if (info->pid == 0)
	{
		if (info->fd[0] != -1)
			e_close(info->fd[0]);//pipe 안열때? pipe 없을땐?
		dup2(info->inputfd, 0);
		dup2(info->fd[1], 1);
		in_child_do_cmd(info->argv, &info->envp);
	}
	else
	{
		if (info->fd[1] != 1)
			e_close(info->fd[1]);
		if (info->inputfd != 0)
			e_close(info->inputfd);
		info->inputfd = info->fd[0];
	}
}

int	e_wait(pid_t pid)
{
	int		status;
	pid_t	w_pid;

	if (pid == 0)
		return (1);
	w_pid = waitpid(pid, &status, 0);
	if (w_pid == -1)
		terminate(0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));//정상종료 안될 시 리턴 값 없는데 어떻게 할 건지 malloc 처리하거나, 8비트 이상의 값을 리턴하거나(257)
	//if (WIFSIGNALED(status))
	//	WTERMSIG(status);
	return (1 << 8);
}
