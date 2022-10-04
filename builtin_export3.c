/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:22:08 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/04 16:22:11 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
