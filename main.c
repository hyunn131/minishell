/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docho <docho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:41:46 by docho             #+#    #+#             */
/*   Updated: 2022/09/29 16:45:00 by docho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp){
	int n;
	char *s;
	
	if (argc || argv)
		;
	while (1)
	{
		s = readline(">");
		exec_cmd(s, envp, &n);
	}
	return (0);
}
