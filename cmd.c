/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:24:49 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/07 16:04:15 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_filename(char *str, int *i, t_info *info)
{
	int		start;
	char	*filename;
	char	*tmp;

	while (str[*i] == '>' || str[*i] == '<')
		(*i)++;
	while (str[*i] == ' ')
		(*i)++;
	start = *i;
	while (str[(*i)] > 32 && str[(*i)] <= 126 && str[(*i)] != '<' \
			&& str[(*i)] != '>' && str[(*i)] != '|')
		(*i)++;
	if (start == *i)
	{
		syntex_err(&str[start]);
		return (0);
	}
	filename = ft_substr(str, start, (*i) - start);
	if (!filename)
		terminate(0);
	dollar(&filename, info);
	tmp = ft_substr2(filename, 0, ft_strlen(filename));
	free(filename);
	filename = tmp;
	return (filename);
}

bool	make_exec(char *str, int idx, t_info *info, char *buffer)
{
	int		i;
	int		flag[3];

	ft_memset(flag, 0, sizeof(flag));
	flag[2] = 1;
	i = info->lens[idx - 1];
	while (++i < info->lens[idx] && flag[2])
	{
		if (str[i] == '\'')
			flag[0] ^= 1;
		else if (str[i] == '\"')
			flag[1] ^= 1;
		if (!flag[0] && !flag[1] && str[i] == '>' && str[i + 1] == '>')
			flag[2] = append(make_filename(str, &i, info), &info->fd[1]);
		else if (!flag[0] && !flag[1] && str[i] == '>' && str[i + 1] != '>')
			flag[2] = output(make_filename(str, &i, info), &info->fd[1]);
		else if (!flag[0] && !flag[1] && str[i] == '<' && str[i + 1] == '<')
			flag[2] = here_doc(make_filename(str, &i, info), &info->inputfd);
		else if (!flag[0] && !flag[1] && str[i] == '<' && str[i + 1] != '<')
			flag[2] = input(make_filename(str, &i, info), &info->inputfd);
		else
			*buffer++ = str[i];
	}
	return (flag[2]);
}

void	pipecount(char *str, t_info *info)
{
	int		i;
	int		j;
	int		flag[2];

	flag[0] = 0;
	flag[1] = 0;
	info->lens = ft_calloc(ft_strlen(str) + 2, sizeof(int));
	if (!(info->lens))
		terminate(0);
	j = 0;
	info->lens[j++] = -1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '|' && !flag[0] && !flag[1])
			info->lens[j++] = i;
		if (str[i] == '\'')
			flag[0] ^= 1;
		if (str[i] == '\"')
			flag[1] ^= 1;
	}
	info->lens[j] = i;
	info->cnt = j;
}

bool	before_cmd(char *str, t_info *info)
{
	int		i;

	i = 0;
	pipecount(str, info);
	info->pids = ft_calloc(info->cnt, sizeof(pid_t));
	info->fd0 = ft_calloc(info->cnt, sizeof(int));
	info->fd1 = ft_calloc(info->cnt, sizeof(int));
	info->ifd = ft_calloc(info->cnt, sizeof(int));
	info->argvs = ft_calloc(info->cnt + 1, sizeof(char **));
	info->flag = ft_calloc(info->cnt, sizeof(int));
	if (!(info->pids) || !(info->fd0) || !(info->fd1) || \
			!(info->ifd) || !(info->argvs) || !(info->flag))
		terminate(0);
	info->inputfd = 0;
	iofd(str, info);
	return (true);
}

void	exec_cmd(t_info *info)
{
	int		i;

	i = 0;
	while (++i <= info->cnt)
	{
		if (!info->flag[i - 1] || !*(info->argvs[i - 1]))
			continue ;
		info->fd[0] = info->fd0[i - 1];
		info->fd[1] = info->fd1[i - 1];
		info->inputfd = info->ifd[i - 1];
		info->argv = info->argvs[i - 1];
		if (info->cnt == 1 && isbuiltin(info))
			;
		else
			process(info, i - 1);
	}
	info->exit_n = e_wait(info);
	returning(info);
}
