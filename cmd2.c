/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 20:50:54 by docho             #+#    #+#             */
/*   Updated: 2022/09/30 21:37:27 by docho            ###   ########.fr       */
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

bool    func(t_info *info, int i, char *str)
{
	char    *ss;
	if (!*(info->argv) && i != info->cnt)
	{
		returning(info);
		syntex_err(&str[info->lens[i]]);
		free2d(info->argv);
		return (false);
	}
	else if (!*(info->argv) && i == info->cnt)
	{
		ss = readline(">");
		exec_cmd(ss, info);
		free2d(info->argv);
		free(ss);
		return (false);
	}
	return (true);
}

void	cmd_err(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	exit(1);
}
