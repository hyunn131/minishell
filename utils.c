/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:25:58 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/07 15:28:02 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *str, t_info *info)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(str);
	while (info->envp[++i])
	{
		if (!ft_strncmp(info->envp[i], str, len) && info->envp[i][len] == '=')
			return (&(info->envp[i])[len + 1]);
	}
	return (0);
}

void	free2d(char **ss)
{
	int	i;

	if (!ss)
		return ;
	i = -1;
	while (ss[++i])
		free(ss[i]);
	free(ss);
}

bool	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s1[++i])
	{
		if (s1[i] != s2[i])
			break ;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (true);
	return (false);
}

char	*joinpath(char *s1, char *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*str;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		s1len = 0;
	else
		s1len = ft_strlen(s1);
	if (!s2)
		s2len = 0;
	else
		s2len = ft_strlen(s2);
	str = (char *)malloc((s1len + s2len + 2) * sizeof(char));
	if (!str)
		return (0);
	ft_memmove(str, s1, s1len * sizeof(char));
	ft_memmove(str + s1len + 1, s2, s2len * sizeof(char));
	str[s1len] = '/';
	str[s1len + s2len + 1] = '\0';
	free(s2);
	return (str);
}

int	e_wait(t_info *info)
{
	int		status;
	pid_t	w_pid;
	int		i;
	int		res;

	i = -1;
	while (++i < info->cnt)
	{
		res = 0;
		if (info->pids[i] == 0)
			continue ;
		w_pid = waitpid(info->pids[i], &status, 0);
		if (WIFEXITED(status))
				res = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			res = 128 + WTERMSIG(status);
	}
	return (res);
}
