/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:23:12 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/06 17:06:06 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	matrix_free(char **matrix, int index)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (i < index)
		free(matrix[i]);
	free(matrix);
}

int	ft_count_matrix(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

bool	isbuiltin(t_info *info)
{
	if (ft_strcmp(info->argv[0], "echo"))
		info->exit_n = echo(info);
	else if (ft_strcmp(info->argv[0], "cd"))
		info->exit_n = cd(info);
	else if (ft_strcmp(info->argv[0], "pwd"))
		info->exit_n = pwd(info);
	else if (ft_strcmp(info->argv[0], "export"))
		info->exit_n = export(info);
	else if (ft_strcmp(info->argv[0], "unset"))
		info->exit_n = unset(info);
	else if (ft_strcmp(info->argv[0], "env"))
		info->exit_n = env(info);
	else if (ft_strcmp(info->argv[0], "exit"))
		info->exit_n = f_exit(info->argv, info);
	else
		return (false);
	return (true);
}
