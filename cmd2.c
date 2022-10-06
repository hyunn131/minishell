/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:24:59 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/06 17:18:24 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	returning(t_info *info)
{
	free(info->lens);
	free(info->pids);
	if (info->fd[1] != 1)
		close(info->fd[1]);
	if (info->fd[0] != 0)
		close(info->fd[0]);
}

bool	func(t_info *info)
{
	if (!*(info->argv))
	{
		returning(info);
		free2d(info->argv);
		return (false);
	}
	return (true);
}

void	cmd_err(char *cmd, t_info *info)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	if (ft_getenv("PATH", info))
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
