/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:23:46 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/07 13:37:04 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo_char(char *argv, int fd)
{
	while (*argv)
	{
		ft_putchar_fd(*argv, fd);
		argv++;
	}
}

void	print_echo(char **argv, int start, int fd)
{
	while (argv[start])
	{
		print_echo_char(argv[start], fd);
		start++;
		if (argv[start])
			write(fd, " ", 1);
		else
			break ;
	}
}

int	echo(t_info *info)
{
	int	i;

	i = 1;
	if (!info->argv[1])
	{
		write(info->fd[1], "\n", 1);
		return (0);
	}
	if (ft_strcmp(info->argv[1], "-n"))
	{
		while (info->argv[i] && ft_strcmp(info->argv[i], "-n"))
			i++;
		print_echo(info->argv, i, info->fd[1]);
	}
	else
	{
		print_echo(info->argv, 1, info->fd[1]);
		write(info->fd[1], "\n", 1);
	}
	return (0);
}
