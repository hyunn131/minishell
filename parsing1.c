/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:25:15 by docho             #+#    #+#             */
/*   Updated: 2022/10/06 17:35:08 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	new_line(char **s)
{
	char	*new;
	char	*tmp;

	new = readline("> ");
	while (new && !*new)
	{
		free(new);
		new = readline("> ");
	}
	if (!new)
	{
		ft_putendl_fd("bash: syntax error: unexpected end of file", 2);
		return (false);
	}
	tmp = ft_strjoin(" ", new);
	if (!tmp)
		terminate(0);
	free(new);
	new = ft_strjoin(*s, tmp);
	free(*s);
	free(tmp);
	*s = new;
	return (true);
}

static void	pipe_check_2(bool *flag, int *start, int i)
{
	flag[2] = false;
	flag[3] = true;
	*start = i + 1;
}

static void	pipe_check_1(char **s, int i, bool *flag)
{
	if ((*s)[i] == '\'')
		flag[0] ^= 1;
	else if ((*s)[i] == '\"')
		flag[1] ^= 1;
	if ((*s)[i] > 32 && (*s)[i] < 127 && (*s)[i] != '|')
		flag[2] = true;
}

bool	pipe_check(char **s)
{
	int		i;
	bool	flag[4];
	int		start;

	ft_memset(flag, 0, sizeof(flag));
	i = -1;
	start = 0;
	while ((*s)[++i])
	{
		pipe_check_1(s, i, flag);
		if ((*s)[i] == '|' && !flag[0] && !flag[1])
		{
			if (!flag[2])
				return (syntex_false(&(*s)[i]));
			if (!redi_check(*s, start, i))
				return (false);
			pipe_check_2(flag, &start, i);
		}
	}
	if (!redi_check(*s, start, i) || (flag[3] && !flag[2] && !new_line(s)))
		return (false);
	return (true);
}
