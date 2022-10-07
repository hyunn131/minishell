/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:24:15 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/07 13:38:02 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**new_added_envp(char *key_and_val, char **envp, int count)
{
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * (count + 2));
	if (!tmp)
		terminate(0);
	i = 0;
	while (i < count)
	{
		tmp[i] = ft_envp_copy(envp, i);
		if (!tmp[i])
			terminate(0);
		i++;
	}
	tmp[i] = ft_strdup(key_and_val);
	if (!tmp[i])
		terminate(0);
	tmp[i + 1] = NULL;
	return (tmp);
}

char	**change_env(char *key_val, char **envp)
{
	char	**new_envp;
	char	*tmp;
	int		len;
	int		i;
	int		envp_count;

	len = ft_strlen_key(key_val) + 1;
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp_equ(envp[i], key_val, len) == 1)
			continue ;
		if (ft_strncmp_equ(envp[i], key_val, len) == -1)
			return (envp);
		tmp = ft_strdup(key_val);
		if (!tmp)
			terminate(0);
		free(envp[i]);
		envp[i] = tmp;
		return (envp);
	}
	envp_count = ft_count_matrix(envp);
	new_envp = new_added_envp(key_val, envp, envp_count);
	free_argv(envp);
	return (new_envp);
}

int	check_export_valid(char *argv)
{
	if (ft_isdigit(*argv) || (*argv == '='))
		return (0);
	while ((*argv) && (*argv != '='))
	{
		if (!ft_isalnum(*argv) && (*argv != '_'))
			return (0);
		argv++;
	}
	return (1);
}

void	print_export_invalid(char *varname)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(varname, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	export(t_info *info)
{
	int	i;
	int	count;
	int	invalid_flag;

	i = 0;
	invalid_flag = 0;
	count = ft_count_matrix(info->argv);
	while (++i < count)
	{
		if (!check_export_valid(info->argv[i]))
		{
			print_export_invalid(info->argv[i]);
			invalid_flag = 1;
			continue ;
		}
		info->envp = change_env(info->argv[i], info->envp);
	}
	if (invalid_flag)
		return (1);
	if (count == 1)
		sort_and_print(info->envp, info->fd[1]);
	return (0);
}
