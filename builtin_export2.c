/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:24:25 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/05 16:29:24 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_envp_copy(char **envp, int index)
{
	char	*tmp;
	int		len;

	len = ft_strlen(envp[index]);
	tmp = (char *)ft_calloc(sizeof(char), (len + 1));
	if (!tmp)
		return (0);
	ft_strlcpy(tmp, envp[index], len + 1);
	return (tmp);
}

int	ft_strlen_key(char *key_and_val)
{
	int	i;

	i = 0;
	while (key_and_val[i] && (key_and_val[i] != '='))
		i++;
	return (i);
}

int	ft_strncmp_equalsign(char *s1, char *s2, int len)
{
	if ((!ft_strncmp(s1, s2, len)) && (s1[len - 1] == s2[len - 1])
		&& (s1[len - 1] == '='))
		return (0);
	return (1);
}
