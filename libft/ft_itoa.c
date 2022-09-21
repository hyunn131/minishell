/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 22:43:00 by junhkim           #+#    #+#             */
/*   Updated: 2022/01/26 19:52:07 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(size_t n)
{
	int	count;

	count = 1;
	n /= 10;
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static void	ft_putnbr(char *s, size_t n, int len)
{
	s[len] = '\0';
	while (len--)
	{
		s[len] = n % 10 + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	size_t	temp;
	int		len;
	char	*result;

	if (n >= 0)
	{
		len = ft_len(n);
		result = (char *)malloc((len + 1) * sizeof(char));
		if (!result)
			return (0);
		ft_putnbr(result, (size_t)n, len);
	}
	else
	{
		temp = (size_t)n * -1;
		len = ft_len(temp);
		result = (char *)malloc((len + 2) * sizeof(char));
		if (!result)
			return (0);
		result[0] = '-';
		ft_putnbr(result + 1, temp, len);
	}
	return (result);
}
