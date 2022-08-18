/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:36:46 by docho             #+#    #+#             */
/*   Updated: 2022/08/18 20:22:17 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    input(char *filename, int *fd)
{
	if (fd[0] != 0)
		e_close(fd[0]);
	fd[0] = open(filename, O_RDONLY);
	if (fd[0] < 0)
		terminate();
}

void	output(char *filename, int *fd)
{
	if (fd[1] != -1)
		e_close(fd[1]);
	fd[1] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] < 0)
		terminate();
}

void	append(char *filename, int *fd)
{
	if (fd[1] != -1)
		e_close(fd[1]);
	fd[1] = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd[1] < 0)
		terminate();
}

void	here_doc(char *limiter, int *fd)
{
	int		tmp[2];
	char	*str;
	
	if (fd[0] != 0)
		e_close(fd[0]);
	e_pipe(tmp);
	while(1)
	{
		str = readline(">");
		if (!str)
			continue ;
		if (ft_strcmp(str, limiter))
			break ;
		else
			ft_putstr_fd(str, tmp[1]);
		free(str);
	}
	free(str);
	e_close(tmp[1]);
	fd[0] = tmp[0];
}