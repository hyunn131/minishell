/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 18:00:39 by junhkim           #+#    #+#             */
/*   Updated: 2022/09/30 18:00:40 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	f_exit(char **argv)
{
	int	i;
	int	count;

	count = ft_count_matrix(argv);
	if (count >= 2 && !is_all_digit(argv[1]))
	{
		exit_error_message("numeric argument required", argv[1]);
		exit(255);
	}
	else if (count >= 3)
	{
		exit_error_message("too many arguments", 0);
		return (1);
	}
	else if (count == 2)
	{
		i = ft_atoi(argv[1]);
		exit(i);
	}
	else
		exit(0);
}

void	exit_error_message(char *message, char *non_numeric)
{
	ft_putstr_fd("exit\nbash: exit: ", 2);
	if (non_numeric)
	{
		ft_putstr_fd(non_numeric, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}
