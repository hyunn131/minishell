/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:25:15 by docho             #+#    #+#             */
/*   Updated: 2022/10/06 03:27:47 by docho            ###   ########.fr       */
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
	if (!new)
		terminate(0);
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
	else if (!ft_strncmp(str, "||", 2))
		return (2);
	else if (!ft_strncmp(str, "|", 1))
		return (1);
	return (0);
}

bool	redi_check(char *s, int i, t_info *info, bool *f_pipe)
{
	int		j;
	bool	f_redi;

	j = info->lens[i - 1];
	f_redi = false;
	while (++j <= info->lens[i] && s[j])
	{
		counting2(s, &j);
		if (syntex_tok(&s[j]))
		{
			if (f_redi)
			{
				syntex_err(&s[j]);
				return (false);
			}
			f_redi = true;
			j += syntex_tok(&s[j]);
		}
		else if (s[j] != ' ')
		{
			*f_pipe = false;
			f_redi = false;
		}
	}
	return (true);
}

bool	rt_f(char *s)
{
	add_history(s);
	return (false);
}

bool	line_check(char **s, t_info *info)
{
	int		i;
	bool	f_pipe;

	pipecount(*s, info);
	i = 0;
	while (++i <= info->cnt)
	{
		f_pipe = true;
		if (!redi_check(*s, i, info, &f_pipe))
			return (rt_f(*s));
		if (f_pipe && i != info->cnt)
		{
			syntex_err(&(*s)[info->lens[i]]);
			return (rt_f(*s));
		}
	}
	if (f_pipe && !new_line(s))
		return (rt_f(*s));
	return (true);
}
