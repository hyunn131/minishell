/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:41:46 by docho             #+#    #+#             */
/*   Updated: 2022/09/30 13:23:51 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int sig)
{
	if (sig==SIGTERM)
		printf("ajielkej\n");
}

void	init_info(t_info *info, char **envp)
{
	int	i;

	i = 0;
	ft_memset(info, 0, sizeof(*info));
	while (envp[i])
		i++;
	info->envp = ft_calloc(i + 1, sizeof(char *));
	if (!(info->envp))
		terminate(0);
	i = -1;
	while (envp[++i])
	{
		(info->envp)[i] = ft_strdup(envp[i]);
		if (!(info->envp)[i])
			terminate(0);
	}
	info->exit_n = 1;
}

int	main(int argc, char **argv, char **envp)
{
	char 	*s;
	t_info	info;

	if (argv)
		;
	if (argc != 1)
		return (1);
	//signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, sig_handler);
	init_info(&info, envp);
	while (1)
	{
		s = readline(">");
		exec_cmd(s, &info);
	}
	free2d(info.envp);
	return (0);
}
