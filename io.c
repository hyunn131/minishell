/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:25:30 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/06 18:55:34 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	input(char *filename, int *fd)
{
	if (!filename)
		return (false);
	if (*fd != 0 && *fd > 0)
		e_close(*fd); 
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
	{
		perror("bash: ");
		free(filename);
		return (false);
	}
	free(filename);
	return (true);
}

bool	output(char *filename, int *fd)
{
	if (!filename)
		return (false);
	if (*fd != 1  && *fd > 0)
		e_close(*fd);
	*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd < 0)
	{
		perror("bash: ");
		free(filename);
		return (false);
	}
	free(filename);
	return (true);
}

bool	append(char *filename, int *fd)
{
	if (!filename)
		return (false);
	if (*fd != 1 && *fd > 0)
		e_close(*fd);
	*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd < 0)
	{
		perror("bash: ");
		free(filename);
		return (false);
	}
	free(filename);
	return (true);
}

void	here_doc2(char *str, char *limiter, int *tmp, int *fd)
{
	free(str);
	free(limiter);
	e_close(tmp[1]);
	*fd = tmp[0];
}

bool	here_doc(char *limiter, int *fd)
{
	int		tmp[2];
	char	*str;
	bool	flag;

	if (!limiter)
		return (false);
	if (*fd != 0  && *fd > 0)
		e_close(*fd);
	e_pipe(tmp);
	flag = true;
	while (1)
	{
		str = readline("> ");
		if (!str || ft_strcmp(str, limiter))
		{
			if (!str)
				flag = false;
			break ;
		}
		ft_putendl_fd(str, tmp[1]);
		free(str);
	}
	here_doc2(str, limiter, tmp, fd);
	return (flag);
}
