/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:24:59 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/06 10:53:41 by junhkim          ###   ########.fr       */
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
	ft_putendl_fd(": command not found", 2);
	info->exit_n = 127;
	exit(127);
}

bool	space_check(char *s)
{
	int	i;
	
	i = 0;
	while (s[i] == ' ')
		i++;
	if (!s[i])
		return (false);
	else
		return (true);
}