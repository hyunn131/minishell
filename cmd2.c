/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:24:59 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/07 16:55:47 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	returning(t_info *info)
{
	int	i;

	free(info->lens);
	free(info->pids);
	free(info->flag);
	if (info->fd[1] != 1 && info->fd[1] > 0)
		close(info->fd[1]);
	if (info->fd[0] != 0 && info->fd[1] > 0)
		close(info->fd[0]);
	free(info->fd0);
	free(info->fd1);
	free(info->ifd);
	i = -1;
	while (++i < info->cnt)
		free2d(info->argvs[i]);
	free(info->argvs);
}

static int	ft_strcmp_path(char *s1)
{
	if (!ft_strncmp(s1, "./", 2) || !ft_strncmp(s1, "../", 3)
		|| !ft_strncmp(s1, "/", 1))
		return (1);
	return (0);
}

void	cmd_err(char *cmd, t_info *info)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	if (ft_getenv("PATH", info) && !ft_strcmp_path(cmd))
		ft_putendl_fd(": command not found", 2);
	else
		ft_putendl_fd(": No such file or directory", 2);
	info->exit_n = 127;
	exit(127);
}

void	sig_init(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}
