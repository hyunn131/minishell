/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:49:56 by docho             #+#    #+#             */
/*   Updated: 2022/09/21 15:40:50 by docho            ###   ########.fr       */
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
		if(s[j] != '\'' && s[j] != '\"')
			sub[i++] = s[j];
		j++;
	}
	return (sub);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;
	size_t	slen;

	if (!s)
		terminate(0);
	i = 0;
	slen = ft_strlen(s);
	if (slen < len)
		len = slen;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		terminate(0);
	while (i < len && start + i < slen)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}


void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}
