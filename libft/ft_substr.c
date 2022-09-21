/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:54:37 by junhkim           #+#    #+#             */
/*   Updated: 2022/08/30 07:11:08 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	length;
	size_t	l;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	length = ft_strlen(s);
	if (length <= start)
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		l = ft_strlen(s);
	else
		l = len;
	substr = (char *)malloc((l + 1) * sizeof(char));
	if (!substr)
		return (0);
	while (i < len && start + i < length)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
