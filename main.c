/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:22:23 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/07 15:16:38 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	pid_t	pid;

	pid = waitpid(-1, 0, WNOHANG);
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		if (pid == -1)
			rl_redisplay();
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
	info->envp = change_env("OLDPWD", info->envp);
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
	sig_init();
	init_info(&info, envp);
	while (1)
	{
		echoctl_flag_off();
		s = readline("minishell$ ");
		if (!s)
			break ;
		if (*s && pipe_check(&s) && before_cmd(s, &info))
		{

			add_history(s);
			exec_cmd(&info);
		}
		if (*s)
			add_history(s);
		free(s);
	}
	ft_putstr_fd("\033[A\033[11Cexit\n", 1);
	free2d(info.envp);
	return (0);
}
