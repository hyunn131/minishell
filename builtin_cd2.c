/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:58:47 by junhkim           #+#    #+#             */
/*   Updated: 2022/10/04 17:58:48 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_path(char **argv, int *flag)
{
	char	*result;

	if (!ft_strncmp(argv[1], "./", 2) || !ft_strncmp(argv[1], "../", 3)
		|| !ft_strncmp(argv[1], "/", 1))
	{
		result = argv[1];
		*flag = 0;
	}
	else
	{
		result = ft_strjoin("./", argv[1]);
		if (!result)
			terminate(0);
		*flag = 1;
	}
	return (result);
}
