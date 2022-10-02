/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:59:53 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/03 00:44:44 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_path(char **argv)
{
	char	*result;

	if (!ft_strncmp(argv[1], "./", 2) || !ft_strncmp(argv[1], "../", 3)
		|| !ft_strncmp(argv[1], "/", 1))
		result = argv[1];
	else
	{
		result = ft_strjoin("./", argv[1]);
		if (!result)
			terminate(0);
	}
	return (result);
}

void	change_pwd(t_info *info, char *new_path)
{
	char	*new_env;

	new_env = ft_strjoin("PWD=", new_path);
	if (!new_env)
		terminate(0);
	free(new_path);
	info->envp = change_env(new_env, info->envp);
	if (!(info->envp))
		terminate(0);
	free(new_env);
}

void	change_old_pwd(t_info *info, char *old_path)
{
	char	*new_env;

	new_env = ft_strjoin("OLDPWD=", old_path);
	if (!new_env)
		terminate(0);
	free(old_path);
	info->envp = change_env(new_env, info->envp);
	if (!(info->envp))
		terminate(0);
	free(new_env);
}

int	cd(t_info *info)
{
	char	*new_path;
	char	*old_path;

	if (!info->argv[1])
	{
		ft_putstr_fd("bash: cd: not a relative or absolute path\n", 2);
		return (1);
	}
	old_path = working_directory();
	new_path = build_path(info->argv);
	if (!chdir(new_path))
	{
		free(new_path);
		new_path = working_directory();
		change_pwd(info, new_path);
		change_old_pwd(info, old_path);
	}
	else
	{
		ft_putstr_fd("bash: cd: No such file or directory: ", 2);
		ft_putstr_fd(info->argv[1], 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}
