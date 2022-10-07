/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:37:38 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/07 15:42:56 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	iofd1(t_info *info, int i, int *fd)
{
	if (i == info->cnt - 1)
	{
		info->fd1[i] = 1;
		info->fd0[i] = 0;
	}
	else
	{
		e_pipe(fd);
		info->fd1[i] = fd[1];
		info->fd0[i] = fd[0];
	}
}

static void	iofd2(char *buffer, t_info *info, int i, bool flag)
{
	dollar(&buffer, info);
	splits(buffer, info, i);
	free(buffer);
	info->flag[i] = flag;
}

void	iofd(char *str, t_info *info)
{
	char	*buffer;
	int		i;
	int		fd[2];
	bool	flag;

	i = -1;
	while (++i < info->cnt)
	{
		flag = true;
		iofd1(info, i, fd);
		buffer = ft_calloc(info->lens[i + 1] - info->lens[i], sizeof(char));
		if (!buffer)
			terminate(0);
		if (!make_exec(str, i + 1, info, buffer))
		{
			free(buffer);
			info->argvs[i] = 0;
			flag = false;
			continue ;
		}
		iofd2(buffer, info, i, flag);
	}
}
