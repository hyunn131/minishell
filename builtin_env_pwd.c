/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 18:00:30 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/03 00:45:37 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_info *info)
{
	int	i;

	if (info->argv[1])
	{
		ft_putstr_fd("bash: env: '", 2);
		ft_putstr_fd(info->argv[1], 2);
		ft_putstr_fd("' : Permission Denied\n", 2);
		return (1);
	}
	i = 0;
	while (info->envp[i])
	{
		ft_putstr_fd(info->envp[i], info->fd[1]);
		write(1, "\n", info->fd[1]);
		i++;
	}
	return (0);
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

char	*working_directory(void)
{
	char	*buf;
	int		n;

	n = 1;
	while (1)
	{
		buf = (char *)malloc(n * 100 * sizeof(char));
		if (buf == NULL)
			terminate(0);
		if (getcwd(buf, (n * 100)) == NULL)
		{
			n++;
			free(buf);
			if (errno == ERANGE)
				continue ;
			else
				terminate(0);
		}
		break ;
	}
	return (buf);
}

int	pwd(t_info *info)
{
	char	*buf;

	buf = working_directory();
	ft_putstr_fd(buf, info->fd[1]);
	write(1, "\n", 1);
	free(buf);
	return (0);
}