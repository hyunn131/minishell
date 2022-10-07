/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:24:06 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/07 13:37:15 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_digit(char *str)
{
	while (*str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	f_exit(char **argv, t_info *info)
{
	int	i;
	int	count;

	count = ft_count_matrix(argv);
	if (count >= 2 && !is_all_digit(argv[1]))
	{
		exit_error_message("numeric argument required", argv[1], info);
		exit(255);
	}
	else if (count >= 3)
	{
		exit_error_message("too many arguments", 0, info);
		return (1);
	}
	else if (count == 2)
		i = ft_atoi(argv[1]);
	else
		i = 0;
	if (info->cnt == 1)
		ft_putstr_fd("exit\n", 2);
	exit(i);
}

void	exit_error_message(char *message, char *non_numeric, t_info *info)
{
	if (info->cnt == 1)
		ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("bash: exit: ", 2);
	if (non_numeric)
	{
		ft_putstr_fd(non_numeric, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}
