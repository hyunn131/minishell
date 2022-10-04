/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:24:41 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/04 16:24:42 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env_name(char *name)
{
	if (ft_isdigit(*name))
		return (0);
	while (*name)
	{
		if (!ft_isalnum(*name) && (*name != '_'))
			return (0);
		name++;
	}
	return (1);
}

char	**remove_one_var(char **envp, int index)
{
	int		i;
	int		j;
	int		count;
	char	**new;

	i = -1;
	count = ft_count_matrix(envp);
	new = (char **)malloc(sizeof(char *) * count);
	if (!new)
		terminate(0);
	j = 0;
	while (++i < count)
	{
		if (i == index)
			continue ;
		new[j] = ft_strdup(envp[i]);
		if (!new[j])
			terminate(0);
		j++;
	}
	free_argv(envp);
	return (new);
}

char	**unset_var(char *varname, char **envp)
{
	int		i;
	int		len;
	char	**new_envp;

	i = -1;
	len = ft_strlen(varname);
	while (envp[++i])
	{
		if ((int)ft_strlen(envp[i]) <= len)
			continue ;
		if (!ft_strncmp(varname, envp[i], len) && envp[i][len] == '=')
			break ;
	}
	if (!envp[i])
		return (envp);
	new_envp = remove_one_var(envp, i);
	return (new_envp);
}

void	print_unset_invalid(char *varname)
{
	ft_putstr_fd("bash: unset: `", 2);
	ft_putstr_fd(varname, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	unset(t_info *info)
{
	int	i;
	int	invalid_flag;

	i = 1;
	invalid_flag = 0;
	while (info->argv[i])
	{
		if (!check_env_name(info->argv[i]))
		{
			print_unset_invalid(info->argv[i]);
			invalid_flag = 1;
			i++;
			continue ;
		}
		info->envp = unset_var(info->argv[i], info->envp);
		i++;
	}
	if (invalid_flag)
		return (1);
	return (0);
}
