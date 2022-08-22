/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:13:45 by docho             #+#    #+#             */
/*   Updated: 2022/08/22 17:45:08 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	isbuiltin(char **argv, char **envp)
{
	if (ft_strcmp(argv[0], "echo"))
	{
		if ft_strcmp(argv[1], "-n")
			echo(argv+2, true);
		else
			echo(argv+1, false);
	}
	else if
}

void    echo(char **argv, bool f)
{
	if (f)
		printf("%s", s);
	else
		printf("%s\n", s);
}

void    cd()
{
	if (chdir(s) == -1)
		terminate();
}

void    pwd()
{
	char	*buf;
	int		n;

	n = 1;
	while (1)
	{
		buf = (char *)malloc(n * 100 * sizeof(char));
		if (buf == NULL)
			terminate();
		if (getcwd(buf, n++ * 100) == NULL)
		{
			if (errno == ERANGE)
				continue ;
			else
				terminate();
		}
		break;
	}
	printf("%s\n", buf);
}

void    export()
{
	while (*envp)
		printf("%s\n", *envp++);
}

void    unset()
{
	
}