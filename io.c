/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:36:46 by docho             #+#    #+#             */
/*   Updated: 2022/09/28 20:16:50 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input(char *filename, int *fd)
{
	if (*fd != 0)
		e_close(*fd);
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
		terminate(0);
	free(filename);
}

void	output(char *filename, int *fd)
{
	if (*fd != 1)
		e_close(*fd);
	*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd < 0)
		terminate(0);
	free(filename);
}

void	append(char *filename, int *fd)
{
	if (*fd != 1)
		e_close(*fd);
	*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd < 0)
		terminate(0);
	free(filename);
}

void	here_doc(char *limiter, int *fd)
{
	int		tmp[2];
	char	*str;

	if (*fd != 0)
		e_close(*fd);
	e_pipe(tmp);
	while (1)
	{
		str = readline(">");
		if (!str)
			continue ;
		if (ft_strcmp(str, limiter))
			break ;
		else
		{
			ft_putstr_fd(str, tmp[1]);
			ft_putstr_fd("\n", tmp[1]);
		}
		free(str);
	}
	free(str);
	e_close(tmp[1]);
	*fd = tmp[0];
	free(limiter);
}
