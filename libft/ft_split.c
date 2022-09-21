/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:06:39 by junhkim           #+#    #+#             */
/*   Updated: 2022/01/28 04:55:46 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else if (s[i])
		{
			count++;
			i++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

static char	*ft_substr_tmp(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = 0;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (0);
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

static void	mem_free(char **result, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(result[n]);
		i++;
	}
	free(result);
	return ;
}

static void	do_split(char const *s, char c, char **result)
{
	size_t	i;
	size_t	n;
	size_t	start;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] != c && s[i])
			i++;
		result[n] = ft_substr_tmp(s, start, i - start);
		if (!result[n])
			mem_free(result, n);
		n++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	n;

	if (!s)
		return (0);
	n = ft_count(s, c);
	result = (char **)malloc((n + 1) * sizeof(char *));
	if (!result)
		return (0);
	result[n] = 0;
	if (n == 0)
		return (result);
	do_split(s, c, result);
	return (result);
}
