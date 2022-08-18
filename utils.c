/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:49:14 by docho             #+#    #+#             */
/*   Updated: 2022/08/18 20:52:24 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	while(s1[++i])
	{
		if(s1[i] != s2[i])
			break ;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (true);
	return (false);
}