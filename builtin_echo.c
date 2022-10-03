/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 18:01:39 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/02 23:30:05 by junhkim          ###   ########.fr       */
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
			write(1, " ", 1);
		else
			break ;
	}
}

int	echo(t_info *info)
{
	if (!info->argv[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	if (ft_strcmp(info->argv[1], "-n"))
		print_echo(info->argv, 1, info->fd[1]);
	else
	{
		print_echo(info->argv, 1, info->fd[1]);
		write(1, "\n", 1);
	}
	return (0);
}