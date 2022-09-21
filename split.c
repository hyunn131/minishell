/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:06:34 by docho             #+#    #+#             */
/*   Updated: 2022/09/21 14:32:59 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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