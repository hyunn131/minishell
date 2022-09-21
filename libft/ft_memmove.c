/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:57:19 by junhkim           #+#    #+#             */
/*   Updated: 2022/01/26 15:56:17 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*temp_d;
	const char	*temp_s;
	size_t		i;

	if (dst == src || len == 0)
		return (dst);
	temp_d = dst;
	temp_s = src;
	i = 0;
	if (dst <= src)
	{
		while (i++ < len)
			*temp_d++ = *temp_s++;
	}
	else
	{
		while (len)
		{
			temp_d[len - 1] = temp_s[len - 1];
			len--;
		}
	}
	return (dst);
}
