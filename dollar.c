/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:38:48 by docho             #+#    #+#             */
/*   Updated: 2022/09/29 13:52:56 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_buffer(char **pbuffer, int start, int i)
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*tmp;
	char	*env;

	tmp = ft_substr(*pbuffer, start + 1, i - start - 1);
	env = getenv(tmp);
	free(tmp);
	s1 = ft_substr(*pbuffer, 0, start);
	s2 = ft_strjoin(s1, env);
	free(s1);
	s1 = ft_substr(*pbuffer, i, ft_strlen(*pbuffer));
	s3 = ft_strjoin(s2, s1);
	free(s1);
	free(s2);
	free(*pbuffer);
	*pbuffer = s3;
}

void	init_(int *flag, int *i)
{
	flag[0] = 0;
	flag[1] = 0;
	*i = -1;
}

void	dollar(char **pbuffer)
{
	int		flag[2];
	int		i;
	int		start;

	while (1)
	{
		init_(flag, &i);
		while ((*pbuffer)[++i])
		{
			if ((*pbuffer)[i] == '\'')
				flag[0] ^= 1;
			if ((*pbuffer)[i] == '$' && !flag[0])
			{
				flag[1] = 1;
				start = i;
				while (!ft_strchr("><| \"\'", (*pbuffer)[++i]))
					;
				new_buffer(pbuffer, start, i);
				break ;
			}
		}
		if (flag[1])
			continue ;
		break ;
	}
}
