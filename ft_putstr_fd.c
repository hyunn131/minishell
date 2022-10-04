/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:25:23 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/04 16:25:24 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr2(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub;
	size_t	slen;

	if (!s)
		terminate(0);
	i = 0;
	j = start;
	slen = ft_strlen(s);
	if (slen < len)
		len = slen;
	sub = (char *)ft_calloc(sizeof(char), (len + 1));
	if (!sub)
		terminate(0);
	while (j - start < len && j < slen)
	{
		if (s[j] != '\'' && s[j] != '\"')
			sub[i++] = s[j];
		j++;
	}
	return (sub);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*str;

	if (!s1 && !s2)
		terminate(0);
	if (!s1)
		s1len = 0;
	else
		s1len = ft_strlen(s1);
	if (!s2)
		s2len = 0;
	else
		s2len = ft_strlen(s2);
	str = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	if (!str)
		terminate(0);
	ft_memmove(str, s1, s1len * sizeof(char));
	ft_memmove(str + s1len, s2, s2len * sizeof(char));
	str[s1len + s2len] = '\0';
	return (str);
}
