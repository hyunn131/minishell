/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:41:46 by docho             #+#    #+#             */
/*   Updated: 2022/10/04 14:38:46 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	pid_t	pid;

	pid = waitpid(-1, 0, WNOHANG);
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		if (pid == -1)
			printf("minishell$ ");
	}
	if (sig == SIGQUIT)
	{
		if (pid != -1)
			ft_putendl_fd("Quit: 3", 2);
		else
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
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
	info->exit_n = 0;
}

void	echoctl_flag_off(void)
{
	struct termios	attr;

	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &attr);
		attr.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &attr);
	}
	else if (isatty(STDOUT_FILENO))
	{
		tcgetattr(STDOUT_FILENO, &attr);
		attr.c_lflag &= ~ECHOCTL;
		tcsetattr(STDOUT_FILENO, TCSANOW, &attr);
	}
	else if (isatty(STDERR_FILENO))
	{
		tcgetattr(STDERR_FILENO, &attr);
		attr.c_lflag &= ~ECHOCTL;
		tcsetattr(STDERR_FILENO, TCSANOW, &attr);
	}
}

void	echoctl_flag_on(void)
{
	struct termios	attr;

	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &attr);
		attr.c_lflag |= ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &attr);
	}
	else if (isatty(STDOUT_FILENO))
	{
		tcgetattr(STDOUT_FILENO, &attr);
		attr.c_lflag |= ECHOCTL;
		tcsetattr(STDOUT_FILENO, TCSANOW, &attr);
	}
	else if (isatty(STDERR_FILENO))
	{
		tcgetattr(STDERR_FILENO, &attr);
		attr.c_lflag |= ECHOCTL;
		tcsetattr(STDERR_FILENO, TCSANOW, &attr);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*s;
	t_info	info;

	if (argc != 1 || !argv)
		return (1);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	init_info(&info, envp);
	while (1)
	{
		echoctl_flag_off();
		s = readline("minishell$ ");
		if (!s)
		{
			ft_putstr_fd("\033[A\033[11Cexit\n", 1);
			exit (0);
		}
		add_history(s);
		exec_cmd(s, &info);
		free(s);
	}
	free2d(info.envp);
	return (0);
}
