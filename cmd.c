/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:14:45 by docho             #+#    #+#             */
/*   Updated: 2022/09/28 21:11:43 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_filename(char **str)
{
	int		i;
	char	*s;
	char	*filename;

	s = *str;
	while (*s == '>' || *s == '<')
		s++;
	while (*s == ' ')
		s++;
	i = 0;
	while (s[i] > 32 && s[i] <= 126 && \
			s[i] != '<' && s[i] != '>' && s[i] != '|')
		i++;
	if (i == 0)
		terminate("syntax error near unexpected token '*s'");
	filename = ft_calloc(sizeof(char), i + 1);
	i = 0;
	while (*s > 32 && *s <= 126 && *s != '<' && *s != '>' && *s != '|')
		filename[i++] = *s++;
	if (!filename)
		terminate(0);
	*str = s;
	return (filename);
}

void	do_buffer(t_info *info, char *buffer)
{
	dollar(&buffer);
	splits(buffer, info);
	free(buffer);
}

void	make_exec(char *str, t_info *info, char *buffer)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (*str && (*str != '|' || flag))
	{
		if (!flag && *str == '>' && *(str + 1) == '>')
			append(make_filename(&str), &info->fd[1]);
		else if (!flag && *str == '>' && *(str + 1) != '>')
			output(make_filename(&str), &info->fd[1]);
		else if (!flag && *str == '<' && *(str + 1) == '<')
			here_doc(make_filename(&str), &info->inputfd);
		else if (!flag && *str == '<' && *(str + 1) != '<')
			input(make_filename(&str), &info->inputfd);
		else
		{
			if (*str == '\"' || *str == '\'')
				flag ^= 1;
			buffer[i++] = *str++;
		}
	}
	do_buffer(info, buffer);
}

void	iofd(char *str, t_info *info)
{
	int	flag;

	flag = 0;
	info->len = 0;
	while (str[info->len] && (str[info->len] != '|' || flag))
	{
		if (str[info->len] == '\"' || str[info->len] == '\'')
			flag ^= 1;
		info->len++;
	}
	if (!str[info->len])
	{
		info->fd[1] = 1;
		info->fd[0] = -1;
	}
	else
		e_pipe(info->fd);
}

void	exec_cmd(char *str, char **envp, int *n)
{
	t_info	info;
	char	*buffer;

	info.envp = envp;
	info.inputfd = 0;
	while (*str)
	{
		iofd(str, &info);
		buffer = ft_calloc(info.len + 1, sizeof(char));
		if (!buffer)
			terminate(0);
		make_exec(str, &info, buffer);
		if (!info.argv)
			terminate(0);
		if (!*(info.argv))
			terminate("syntax error near unexpected token '*s'");
		process(&info);
		if (!str[info.len])
			break ;
		free2d(info.argv);
		str = &str[++info.len];
	}
	*n = e_wait(info.pid);
}

int	main(int argc, char **argv, char **envp){
	int n;
	char *s;
	
	if (argc || argv)
		;
	while (1)
	{
		s = readline(">");
		exec_cmd(s, envp, &n);
	}
	return (0);
}
