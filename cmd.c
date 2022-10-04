/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:14:45 by docho             #+#    #+#             */
/*   Updated: 2022/10/04 14:40:36 by junhkim          ###   ########.fr       */
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
	info->lens = ft_calloc(ft_strlen(str) + 1, sizeof(int));
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

bool	iofd(char *str, int i, t_info *info)
{
	char	*buffer;

	if (i == info->cnt)
	{
		info->fd[1] = 1;
		info->fd[0] = 0;
	}
	else
		e_pipe(info->fd);
	buffer = ft_calloc(info->lens[i] - info->lens[i - 1], sizeof(char));
	if (!buffer)
		terminate(0);
	if (!make_exec(str, i, info, buffer))
	{
		free(buffer);
		returning(info);
		return (false);
	}
	dollar(&buffer, info);
	splits(buffer, info);
	free(buffer);
	return (true);
}

void	exec_cmd(char *str, t_info *info)
{
	int		i;

	if (!*str)
		return ;
	pipecount(str, info);
	i = 0;
	while (++i <= info->cnt)
	{
		if (!iofd(str, i, info) || !func(info, i, str))
			return ;
		if (info->cnt == 1 && isbuiltin(info))
			return ;
		else
		{
			printf("argv---------------------\n");
			for (int i = 0; info->argv[i]; ++i)
				printf("argv[%d]: %s\n", i, info->argv[i]);
			process(info);
		}
		free2d(info->argv);
	}
	returning(info);
	info->exit_n = e_wait(info);
}
