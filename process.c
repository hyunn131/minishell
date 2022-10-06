/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:25:43 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/06 18:52:57 by docho            ###   ########.fr       */
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
			continue ;
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

void	in_child_do_cmd(t_info *info)
{
	char	*path;
	char	**ss;

	if (!isbuiltin(info))
	{
		path = ft_getenv("PATH", info);
		if (path)
		{
			ss = ft_split(path, ':');
			if (!ss)
				terminate(0);
			connectpath(&info->argv[0], ss);
			free2d(ss);
		}
		if (execve(info->argv[0], info->argv, info->envp) == -1)
			cmd_err(info->argv[0], info);
	}
	exit(info->exit_n);
}

void	process(t_info *info, int i)
{
	info->pids[i] = e_fork();
	if (info->pids[i] == 0)
	{
		echoctl_flag_on();
		if (info->fd[0] != 0 && info->fd[0] > 0)
			e_close(info->fd[0]);
		if (info->inputfd > 0)
			dup2(info->inputfd, 0);
		if (info->fd[1] > 0)
			dup2(info->fd[1], 1);
		in_child_do_cmd(info);
	}
	else
	{
		if (info->fd[1] != 1 && info->fd[1] > 0)
			e_close(info->fd[1]);
		if (info->inputfd != 0 && info->inputfd > 0)
			e_close(info->inputfd);
		info->inputfd = info->fd[0];
	}
}
