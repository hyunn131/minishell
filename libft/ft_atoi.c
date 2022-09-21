/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:47:34 by junhkim           #+#    #+#             */
/*   Updated: 2022/02/07 18:17:32 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	convert_int(const char *str)
{
	int			len;
	long long	result;
	const char	*temp;

	temp = str;
	len = 0;
	result = 0;
	while (ft_isdigit(*temp++))
		len++;
	while (len--)
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;

	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	if (ft_isdigit(*str))
		result = convert_int(str);
	else
		result = 0;
	result *= sign;
	return ((int)result);
}
