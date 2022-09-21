/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:12:14 by junhkim           #+#    #+#             */
/*   Updated: 2022/01/14 01:46:05 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp_s;
	unsigned char	temp_c;

	temp_s = (unsigned char *)s;
	temp_c = (unsigned char)c;
	while (n--)
	{
		if (*temp_s == temp_c)
			return ((void *)temp_s);
		temp_s++;
	}
	return (0);
}
