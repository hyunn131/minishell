/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 05:26:55 by docho             #+#    #+#             */
/*   Updated: 2022/09/19 06:51:19 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	counting(char *buffer, int *cnt)
{
	int 	i;
	int 	flag;
	char	c;
	
	i = -1;
	flag = 0;
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
			if (buffer[i] == '\"' || buffer[i] == '\'')
			{
				c = buffer[i++];
				while(buffer[i] != c)
					i++;
			}
		}
	}
}

static void	fills(char *buffer)
{
	int 	i;
	int 	flag;
	char	c;
	
	i = -1;
	flag = 0;
	while (buffer[++i])
	{
		if (buffer[i] == ' ')
		{
			if (len != 0)
			len = 0;
		}
		else
		{
			len++;
			if (buffer[i] == '\"' || buffer[i] == '\'')
			{
				c = buffer[i++];
				while(buffer[i] != c)
					i++;
			}
		}
	}
}	

void	splits(char *buffer)
{
	char	**argv;
	int 	cnt;
	int		i;

	cnt = 0;
	counting(buffer, &cnt);
	argv = ft_calloc(cnt + 1, sizeof(char *));
	if (!argv)
		terminate(0);
	i = -1;
	while (++i < cnt)
	{
		argv[i] = ft_strdup();
	}
	printf("cnt: %d\n", cnt);
}

void	quotes(char *buffer)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	ft_strlen(buffer) - $(len) + ft_strlen(getenv());
	while (buffer[++i])
	{
		if (buffer[i] != '\'')
			flag ^= 1;
		if (buffer[i] == '$' && !flag)
		{

		}
	}
}