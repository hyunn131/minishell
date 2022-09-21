/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:38:48 by docho             #+#    #+#             */
/*   Updated: 2022/09/21 16:41:23 by docho            ###   ########.fr       */
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

void    dollar(char **pbuffer)
{
	int		flag;
	int		flag2;
	int		i;
	int		start;

	while (1)
	{
		i = -1;
		flag = 0;
		flag2 = 0;
		while ((*pbuffer)[++i])
		{
			if ((*pbuffer)[i] == '\'')
				flag ^= 1;
			if ((*pbuffer)[i] == '$' && !flag)
			{
				flag2 = 1;
				start = i;
				while (!ft_strchr("><| \"\'", (*pbuffer)[++i]))
					;
				new_buffer(pbuffer, start, i);
				break;
			}
		}
		if (flag2)
			continue;
		break;
	}
}