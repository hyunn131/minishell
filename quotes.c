/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 05:26:55 by docho             #+#    #+#             */
/*   Updated: 2022/09/24 22:44:19 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	counting(char *buffer, int *cnt)
{
	int 	i;
	int 	flag;
	char	c;
	
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
			if (buffer[i] == '\"' || buffer[i] == '\'')
			{
				c = buffer[i];
				while(buffer[++i] != c)
					;
			}
		}
	}
}

void	fills(char *buffer, t_info *info)
{
	int 	i;
	int 	flag;
	int		start;
	int		num;
	char	c;
	
	i = -1;
	flag = 0;
	start = 0;
	num = 0;
	while (buffer[++i])
	{
		while (buffer[i] == ' ')
			i++;
		start = i;
		while (buffer[i] != ' ' && buffer[i])
		{
			if (buffer[i] == '\"' || buffer[i] == '\'')
			{
				c = buffer[i];
				while(buffer[++i] != c)
					;
			}
			i++;
		}
		if (start == i)
			break ;
		info->argv[num++] = ft_substr2(buffer, start, i - start);
	}
}	

void	splits(char *buffer, t_info *info)
{
	int 	cnt;

	if (info || buffer) 
		;
	cnt = 0;   
	counting(buffer, &cnt);
	info->argv = ft_calloc(cnt + 1, sizeof(char *));
	if (!info->argv)
		terminate(0);
	fills(buffer, info);
	printf("argv-------------\n");
	for (int i = 0; info->argv[i]; ++i)
	{
		printf("argv[%d]: %s\n", i, info->argv[i]);
	}
	printf("\n");
}
