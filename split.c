/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:06:34 by docho             #+#    #+#             */
/*   Updated: 2022/08/22 16:08:04 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;
	size_t	slen;

	if (!s)
		return (0);
	i = 0;
	slen = ft_strlen(s);
	if (slen < len)
		len = slen;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (0);
	while (i < len && start + i < slen)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}


static size_t	counting(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i++] == c)
			continue ;
		i--;
		count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static void	freestrs(char **strs, size_t index)
{
	while (index > 0)
		free(strs[index - 1]);
	free(strs);
}

static void	fillstrs(char const *s, char c, char **strs)
{
	size_t	i;
	size_t	index;
	size_t	start;
	size_t	len;

	i = 0;
	index = 0;
	while (s[i])
	{
		if (s[i++] == c)
			continue ;
		i--;
		start = i;
		len = 0;
		while (s[i] && s[i] != c)
		{
			len++;
			i++;
		}
		strs[index] = ft_substr(s, start, len);
		if (!strs[index])
			freestrs(strs, index);
		index++;
	}
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**strs;

	if (!s)
		return (0);
	count = counting(s, c);
	strs = (char **)malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (0);
	fillstrs(s, c, strs);
	strs[count] = 0;
	return (strs);
}