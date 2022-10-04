/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:24:59 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/04 16:25:00 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	returning(t_info *info)
{
	free(info->lens);
	if (info->fd[1] != 1)
		close(info->fd[1]);
	if (info->fd[0] != 0)
		close(info->fd[0]);
}

bool	func(t_info *info, int i, char *str)
{
	char	*ss;

	if (!*(info->argv) && i != info->cnt)
	{
		returning(info);
		syntex_err(&str[info->lens[i]]);
		free2d(info->argv);
		return (false);
	}
	else if (!*(info->argv) && i == info->cnt)
	{
		returning(info);
		free2d(info->argv);
		ss = readline("> ");
		exec_cmd(ss, info);
		free(ss);
		return (false);
	}
	return (true);
}

void	cmd_err(char *cmd, t_info *info)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	info->exit_n = 127;
	exit(127);
}
