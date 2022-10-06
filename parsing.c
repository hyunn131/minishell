/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:25:15 by docho             #+#    #+#             */
/*   Updated: 2022/10/06 16:37:34 by docho            ###   ########.fr       */
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

int	syntex_tok(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (2);
	else if (!ft_strncmp(str, ">", 1))
		return (1);
	else if (!ft_strncmp(str, "<<", 2))
		return (2);
	else if (!ft_strncmp(str, "<", 1))
		return (1);
	// else if (!ft_strncmp(str, "||", 2))
	// 	return (2);
	else if (!ft_strncmp(str, "|", 1))
		return (1);
	else if (!ft_strncmp(str, "", 1))
		return (1);
	return (0);
}

bool	syntex_false(char *str)
{
	syntex_err(str);
	return (false);
}

bool	redi_check(char *s, int start, int end)
{
	int		i;
	bool	flag;

	if (start == end)
		return (true);
	i = start;
	flag = false;
	while (i <= end)
	{
		if (syntex_tok(&s[i]))
		{
			if (flag)
				return (syntex_false(&s[i]));
			flag = true;
			i += syntex_tok(&s[i]) - 1;
		}
		else if (s[i] != ' ')
			flag = false;
		i++;
	}
	return (true);
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
		if ((*s)[i] == '\'')
			flag[0] ^= 1;
		else if ((*s)[i] == '\"')
			flag[1] ^= 1;
		if ((*s)[i] > 32 && (*s)[i] < 127)
			flag[2] = true;
		if ((*s)[i] == '|' && !flag[0] && !flag[1])
		{
			if (!flag[2])
				return (syntex_false(&(*s)[i]));
			if (!redi_check(*s, start, i))
				return (false);
			flag[2] = false;
			flag[3] = true;
			start = i + 1;
		}
	}
	if (!redi_check(*s, start, i))
		return (false);
	if (flag[3] && !flag[2] && !new_line(s))
		return (false);
	return (true);
}