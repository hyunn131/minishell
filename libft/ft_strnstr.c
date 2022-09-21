/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:32:16 by junhkim           #+#    #+#             */
/*   Updated: 2022/01/27 03:45:38 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	search_lim;

	i = 0;
	search_lim = len - ft_strlen(needle) + 1;
	if (!needle[0])
		return ((char *)haystack);
	while (len-- && *haystack && search_lim--)
	{
		while (needle[i])
		{
			if (haystack[i] != needle[i])
				break ;
			i++;
		}
		if (!(needle[i]))
			return ((char *)haystack);
		haystack++;
		i = 0;
	}
	return (0);
}
