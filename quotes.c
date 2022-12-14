/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:25:50 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/07 13:49:33 by docho            ###   ########.fr       */
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
		i++;
		while (buffer[i] != c && buffer[i])
			i++;
	}
	if (buffer[i])
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

void	fills(char *buffer, t_info *info, int idx)
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
				info->argvs[idx][num++] = ft_substr2(buffer, start, i - start);
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
		info->argvs[idx][num++] = ft_substr2(buffer, start, i - start);
}

void	splits(char *buffer, t_info *info, int i)
{
	int	cnt;

	cnt = 0;
	counting(buffer, &cnt);
	info->argvs[i] = ft_calloc(cnt + 1, sizeof(char *));
	if (!info->argvs[i])
		terminate(0);
	fills(buffer, info, i);
}
