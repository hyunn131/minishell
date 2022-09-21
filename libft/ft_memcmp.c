/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:50:01 by junhkim           #+#    #+#             */
/*   Updated: 2022/01/14 01:47:59 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*temp_s1;
	const unsigned char	*temp_s2;

	temp_s1 = s1;
	temp_s2 = s2;
	while (n--)
	{
		if (*temp_s1 != *temp_s2)
			return ((int)(*temp_s1 - *temp_s2));
		temp_s1++;
		temp_s2++;
	}
	return (0);
}
