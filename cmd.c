/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:14:45 by docho             #+#    #+#             */
/*   Updated: 2022/09/30 14:11:45 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_filename(char *str, int *idx)
{
	int		i;
	int		j;
	int		len;
	char	*filename;

	i = *idx;
	while (str[i] == '>' || str[i] == '<')
		i++;
	while (str[i] == ' ')
		i++;
	len = 0;
	while (str[i + len] > 32 && str[i + len] <= 126 && str[i + len] != '<' \
			&& str[i + len] != '>' && str[i + len] != '|')
		len++;
	if (len == 0)
		terminate("syntax error near unexpected token 'str[i]'");
	filename = ft_calloc(sizeof(char), len + 1);
	if (!filename)
		terminate(0);
	j = 0;
	while (j < len)
		filename[j++] = str[i++];
	*idx = i;
	return (filename);
}

void	make_exec(char *str, int idx, t_info *info, char *buffer)
{
	int		i;
	int		j;
	int		flag[2];

	j = 0;
	flag[0] = 0;
	flag[1] = 1;
	i = info->lens[idx - 1];
	while (++i < info->lens[idx])
	{
		if (str[i] == '\'')
			flag[0] ^= 1;
		else if (str[i] == '\"')
			flag[1] ^= 1;
		if (!flag[0] && !flag[1] && str[i] == '>' && str[i + 1] == '>')
			append(make_filename(str, &i), &info->fd[1]);
		else if (!flag[0] && !flag[1] && str[i] == '>' && str[i + 1] != '>')
			output(make_filename(str, &i), &info->fd[1]);
		else if (!flag[0] && !flag[1] && str[i] == '<' && str[i + 1] == '<')
			here_doc(make_filename(str, &i), &info->inputfd);
		else if (!flag[0] && !flag[1] && str[i] == '<' && str[i + 1] != '<')
			input(make_filename(str, &i), &info->inputfd);
		else
			buffer[j++] = str[i];
	}
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

void	iofd(char *str, int i, t_info *info)// > (공백 나오는 경우)
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
	make_exec(str, i, info, buffer);
	dollar(&buffer, info);
	splits(buffer, info);
	free(buffer);
}

void	print_info(t_info *info)
{
	printf("print info---------------------\n");
	for (int i = 0; info->envp[i]; ++i)
		printf("%s\n", info->envp[i]);
	for (int i = 0; i <= info->cnt; ++i)
		printf("%d\n", info->lens[i]);
	printf("%d\n", info->cnt);
	printf("%d\n", info->fd[0]);
	printf("%d\n", info->fd[1]);
	printf("%d\n", info->inputfd);
	printf("%d\n", info->pid);
	printf("%d\n", info->exit_n);
}

void	exec_cmd(char *str, t_info *info)
{
	int		i;
	char	*ss;

	pipecount(str, info);
	i = 0;
	while (++i <= info->cnt)
	{
		iofd(str, i, info);
		if (!*(info->argv) && i != info->cnt)
		{
			ft_putstr_fd("syntax error near unexpected token '", 2);
			ft_putstr_fd(check_token(&str[info->lens[i]]), 2);
			ft_putendl_fd("'", 2);
			return ;
		}
		else if (!*(info->argv) && i == info->cnt)
		{
			ss = readline(">");
			exec_cmd(ss, info);
			free(ss);
			return ;
		}
		else if (info->cnt == 1 && isbuiltin(info))
			return ;
		else
		{
			process(info);
			free2d(info->argv);
		}
	}
	info->exit_n = e_wait(info->pid);
}