/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:31:48 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/06 17:32:02 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
