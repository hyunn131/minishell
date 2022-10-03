/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 20:50:54 by docho             #+#    #+#             */
/*   Updated: 2022/10/03 21:17:03 by docho            ###   ########.fr       */
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
