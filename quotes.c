/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 05:26:55 by docho             #+#    #+#             */
/*   Updated: 2022/09/30 15:29:19 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	counting2(char *buffer, int *pi)
{
	int		i;
	char	c;

	i = *pi;
	if (buffer[i] == '\"' || buffer[i] == '\'')
	{
		c = buffer[i];
		while (buffer[++i] != c)
			;
	}
	*pi = i;
}

void	counting(char *buffer, int *cnt)
{
	int		i;
	int		flag;

	i = -1;
	flag = 0;
	*cnt = 0;
	while (buffer[++i])
	{
		if (buffer[i] == ' ')
			flag = 0;
		else
		{
			if (flag == 0)
			{
				flag = 1;
				(*cnt)++;
			}
			counting2(buffer, &i);
		}
	}
}

void	fills(char *buffer, t_info *info)
{
	int		i;
	int		start;
	int		num;

	start = -1;
	i = -1;
	num = 0;
	while (buffer[++i])
	{
		if (buffer[i] == ' ')
		{
			if (start != -1)
				info->argv[num++] = ft_substr2(buffer, start, i - start);
			start = -1;
		}
		else
		{
			if (start == -1)
				start = i;
			counting2(buffer, &i);
		}
	}
	if (start != -1)
		info->argv[num++] = ft_substr2(buffer, start, i - start);
}

void	splits(char *buffer, t_info *info)
{
	int	cnt;

	cnt = 0;
	counting(buffer, &cnt);
	info->argv = ft_calloc(cnt + 1, sizeof(char *));
	if (!info->argv)
		terminate(0);
	fills(buffer, info);
}
