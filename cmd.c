/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:14:45 by docho             #+#    #+#             */
/*   Updated: 2022/08/22 17:56:26 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmdlen(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

static char	**connect_io(char **cmd, int *fd)
{
	int		i;
	int		j;
	char	**argv;

	argv = (char **)malloc(sizeof(char *) * cmdlen(cmd) + 1);
	if (!argv)
		terminate();
	i = -1;
	j = -1;
	while (cmd[++i])
	{
		if (ft_strcmp(cmd[i], "<"))
			input(cmd[++i], fd);
		else if (ft_strcmp(cmd[i], "<<"))
			here_doc(cmd[++i], fd);
		else if (ft_strcmp(cmd[i], ">"))
			output(cmd[++i], fd);
		else if (ft_strcmp(cmd[i], ">>"))
			append(cmd[++i], fd);
		else
			argv[++j] = cmd[i];
	}
	argv[++j] = NULL;
}

void	exec_cmd(char ***arr, char **envp, int *n)
{
	int		i;
	int		len;
	int		fd[2];
	pid_t	*pids;
	char	**argv;

	len = 0;
	while (arr[len])
		len++;
	pids = (pid_t *)malloc(len * sizeof(pid_t));
	if (!pids)
		terminate();
	fd[0] = 0;
	i = -1;
	while (arr[++i])
	{
		fd[1] = -1;
		if (i == len - 1)
			fd[1] = 1;
		argv = connect_io(arr[i], fd);
		process(argv, envp, fd, &pids[i]);
		free(argv);
	}
	e_close(fd[0]);
	*n = e_wait(pids, len);
	free(pids);
}
