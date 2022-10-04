/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:23:32 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/04 17:57:03 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	if_dir_changed(t_info *info, char *new_path, char *old_path, int flag)
{
	if (flag)
		free(new_path);
	new_path = working_directory();
	change_pwd(info, new_path);
	change_old_pwd(info, old_path);
}

void	if_not_changed(t_info *info, char *new_path, char *old_path, int flag)
{
	free(old_path);
	if (flag)
		free(new_path);
	ft_putstr_fd("bash: cd: No such file or directory: ", 2);
	ft_putstr_fd(info->argv[1], 2);
	ft_putstr_fd("\n", 2);
}

int	cd(t_info *info)
{
	char	*new_path;
	char	*old_path;
	int		flag;

	if (!info->argv[1])
	{
		ft_putstr_fd("bash: cd: not a relative or absolute path\n", 2);
		return (1);
	}
	old_path = working_directory();
	new_path = build_path(info->argv, &flag);
	if (!chdir(new_path))
		if_dir_changed(info, new_path, old_path, flag);
	else
	{
		if_not_changed(info, new_path, old_path, flag);
		return (1);
	}
	return (0);
}
