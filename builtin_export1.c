/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 18:00:49 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/04 15:34:59 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**new_added_envp(char *key_and_val, char **envp, int count)
{
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * (count + 2));
	if (!tmp)
		return (0);
	i = 0;
	while (i < count)
	{
		tmp[i] = ft_envp_copy(envp, i);
		if (!tmp[i])
			return (0);
		i++;
	}
	tmp[i] = ft_strdup(key_and_val);
	if (!tmp[i])
		return (0);
	tmp[i + 1] = NULL;
	return (tmp);
}

char	**change_env(char *key_and_val, char **envp)
{
	char	**new_envp;
	char	*tmp;
	int		len;
	int		i;
	int		envp_count;

	len = ft_strlen_key(key_and_val) + 1;
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp_equalsign(envp[i], key_and_val, len))
			continue ;
		tmp = ft_strdup(key_and_val);
		if (!tmp)
			terminate(0);
		free(envp[i]);
		envp[i] = tmp;
		return (envp);
	}
	envp_count = ft_count_matrix(envp);
	new_envp = new_added_envp(key_and_val, envp, envp_count);
	if (!new_envp)
		terminate(0);
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

void	ft_put_envp_with_qou_fd(char *arr, int fd)
{
	int	flag;
	int	i;
	int	len;

	i = -1;
	flag = 0;
	len = ft_strlen(arr);
	while (++i < len)
	{
		if (!flag && arr[i] == '=')
		{
			flag ^= 1;
			ft_putstr_fd("=\"", fd);
			continue ;
		}
		ft_putchar_fd(arr[i], fd);
	}
	ft_putstr_fd("\"\n", fd);
}

char	**ft_dup_matrix(char **arr)
{
	int		len;
	int		i;
	char	**res;

	len = 0;
	while (arr[len])
		len++;
	res = ft_calloc(len + 1, sizeof(char *));
	if (!res)
		terminate(0);
	i = -1;
	while (arr[++i])
	{
		res[i] = ft_strdup(arr[i]);
		if (!(res)[i])
			terminate(0);
	}
	return (res);
}

void	ft_sort_matrix(char **arr, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (++i < len)
	{
		j = i;
		while (++j < len)
		{
			if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[i])) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

void	sort_and_print(char **envp, int fd)
{
	int		i;
	int		len;
	char	**arr;

	len = ft_count_matrix(envp);
	arr = ft_dup_matrix(envp);
	ft_sort_matrix(arr, len);
	i = -1;
	while (arr[++i])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_put_envp_with_qou_fd(arr[i], fd);
	}
	free2d(arr);
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
		if (!ft_strchr(info->argv[i], '='))
			continue ;
		info->envp = change_env(info->argv[i], info->envp);
	}
	if (invalid_flag)
		return (1);
	if (count == 1)
		sort_and_print(info->envp, info->fd[1]);
	return (0);
}
