/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:38:34 by junhkim           #+#    #+#             */
/*   Updated: 2022/08/30 07:19:42 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_first(char const *s1, char const *set, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (ft_strchr(set, s1[i]))
			i++;
		else
			break ;
	}
	return (i);
}

static size_t	ft_last(char const *s1, char const *set, size_t len)
{
	size_t	i;

	if (!len)
		return (0);
	i = len - 1;
	while (len-- && i)
	{
		if (ft_strchr(set, s1[i]))
			i--;
		else
			break ;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	first;
	size_t	last;
	char	*result;

	if (!set)
		return ((char *)s1);
	if (!s1)
		return (0);
	s1_len = ft_strlen(s1);
	first = ft_first(s1, set, s1_len);
	last = ft_last(s1, set, s1_len);
	if (first > last)
		return (ft_strdup(""));
	result = ft_substr(s1, first, last - first + 1);
	return (result);
}
