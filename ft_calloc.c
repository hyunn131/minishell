/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:31:35 by docho             #+#    #+#             */
/*   Updated: 2022/09/18 17:41:42 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*mem;
	size_t			i;

	mem = b;
	i = 0;
	while (i < len)
	{
		mem[i] = (unsigned char)c;
		i++;
	}
	return (mem);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*m;

	m = malloc(size * count);
	if (m)
	{
		ft_bzero(m, size * count);
	}
	return (m);
}
