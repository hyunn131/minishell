/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:35:20 by junhkim           #+#    #+#             */
/*   Updated: 2022/01/14 01:49:29 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_l;
	size_t	src_l;

	dst_l = ft_strlen(dst);
	src_l = ft_strlen(src);
	i = 0;
	if (dst_l > dstsize)
		return (src_l + dstsize);
	else
	{
		while ((i + dst_l + 1 < dstsize) && src[i])
		{
			dst[dst_l + i] = src[i];
			i++;
		}
		dst[dst_l + i] = '\0';
	}
	return (dst_l + src_l);
}
