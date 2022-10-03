/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 18:00:58 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/03 21:42:25 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sorting(char **envp)
{
	int		i;
	int		j;
	int		len;
	char	**arr;
	char	*tmp;

	len = 0;
	while (envp[len])
		len++;
	arr = ft_calloc(len + 1, sizeof(char *));
	if (!(arr))
		terminate(0);
	i = -1;
	while (envp[++i])
	{
		arr[i] = ft_strdup(envp[i]);
		if (!(arr)[i])
			terminate(0);
	}
	//여기까지 복복사사부부분분
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
	//여기까지sorting
	i = -1;
	while(arr[++i])
	{
		//출력
	}
	free2d(arr);
}

char	*ft_envp_copy(char **envp, int index)
{
	char	*tmp;
	int		len;

	len = ft_strlen(envp[index]);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (0);
	ft_strlcpy(tmp, envp[index], len + 1);
	return (tmp);
}

int	ft_strlen_key(char *key_and_val)
{
	int	i;

	i = 0;
	while (key_and_val[i] && (key_and_val[i] != '='))
		i++;
	return (i);
}

int	ft_strncmp_equalsign(char *s1, char *s2, int len)
{
	if ((!ft_strncmp(s1, s2, len)) && (s1[len - 1] == s2[len - 1])
		&& (s1[len - 1] == '='))
		return (0);
	return (1);
}
