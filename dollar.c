/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:25:07 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/06 04:16:16 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_buffer(char **pbuffer, int start, int i, t_info *info)
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*tmp;
	char	*env;

	tmp = ft_substr(*pbuffer, start + 1, i - start - 1);
	if (!ft_strncmp(tmp, "?", 1))
	{
		env = ft_itoa(info->exit_n);
		i = start + 2;
	}
	else
		env = ft_getenv(tmp, info);
	free(tmp);
	s1 = ft_substr(*pbuffer, 0, start);
	s2 = ft_strjoin2(s1, env);
	free(s1);
	s1 = ft_substr(*pbuffer, i, ft_strlen(*pbuffer));
	s3 = ft_strjoin2(s2, s1);
	free(s1);
	free(s2);
	free(*pbuffer);
	*pbuffer = s3;
}

void	init_(int *flag, int *i)
{
	*flag = 0;
	*i = -1;
}

void	counting3(char *buffer, int *pi)
{
	int		i;
	char	c;

	i = *pi;
	if (buffer[i] == '\'')
	{
		c = buffer[i];
		i++;
		while (buffer[i] != c && buffer[i])
			i++;
	}
	if (buffer[i])
		*pi = i;
	else
		*pi += 1;
}

void	dollar(char **pbuffer, t_info *info)
{
	int		flag;
	int		i;
	int		start;

	while (1)
	{
		init_(&flag, &i);
		while ((*pbuffer)[++i])
		{
			if ((*pbuffer)[i] == '\'')
				counting3(*pbuffer, &i);
			if ((*pbuffer)[i] == '$')
			{
				flag = 1;
				start = i;
				while (!ft_strchr("><| :\"\'", (*pbuffer)[++i]))
					;
				new_buffer(pbuffer, start, i, info);
				break ;
			}
		}
		if (flag)
			continue ;
		break ;
	}
}
