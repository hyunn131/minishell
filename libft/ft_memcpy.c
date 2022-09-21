/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:03:56 by junhkim           #+#    #+#             */
/*   Updated: 2022/01/26 15:58:05 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		len;
	char		*temp_dst;
	const char	*temp_src;

	if (!dst && !src)
		return (0);
	temp_dst = (char *)dst;
	temp_src = (char *)src;
	len = 0;
	while (len < n)
	{
		temp_dst[len] = temp_src[len];
		len++;
	}
	return (dst);
}
