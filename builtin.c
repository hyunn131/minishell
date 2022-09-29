/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhkim <junhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:13:45 by docho             #+#    #+#             */
/*   Updated: 2022/09/29 23:22:51 by junhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char *env_name)
{
	char	*envptr;

	envptr = getenv(env_name);
	if (envptr)
		ft_putstr_fd(envptr, 1);
}

void	print_echo_char(char *argv)
{
	while (*argv)
	{
		if (*argv == '$')
		{
			if (*(argv + 1) == '?')
			{
				// exit code 매개변수로 받아서 출력
				argv += 2;
				continue ;
			}	
		}
		ft_putchar_fd(*argv, 1);
		argv++;
	}
}

void	print_echo(char **argv, int start)
{
	while (argv[start])
	{
		print_echo_char(argv[start]);
		start++;
		if (argv[start])
			write(1, " ", 1);
		else
			break ;
	}
}

void	echo(char **argv)
{
	if (!argv[1])
	{
		write(1, "\n", 1);
		return ;
	}
	if (ft_strcmp(argv[1], "-n"))
		print_echo(argv, 1);
	else
	{
		print_echo(argv, 1);
		write(1, "\n", 1);
	}
}

char	*build_path(char **argv)
{
	char	*result;

	if (!ft_strncmp(argv[1], "./", 2) || !ft_strncmp(argv[1], "../", 3)
		|| !ft_strncmp(argv[1], "/", 1))
		result = argv[1];
	else
		result = NULL;
	return (result);
}

void	change_pwd(char ***envp, char *new_path)
{
	char	*new_env;

	new_env = ft_strjoin("PWD=", new_path);
	change_env(new_env, *envp);
	free(new_env);
}

void	change_old_pwd(char ***envp, char *old_path)
{
	char	*new_env;

	new_env = ft_strjoin("OLDPWD=", old_path);
	change_env(new_env, *envp);
	free(new_env);
}

void	cd(char **argv, char ***envp)
{
	char	*new_path;
	char	*old_path;

	if (!argv[1])
	{
		ft_putstr_fd("bash: cd: not a relative or absolute path\n", 2);
		return ;
	}
	old_path = working_directory();
	new_path = build_path(argv); // need to be modified
	if (!chdir(new_path))
	{
		change_pwd(envp, new_path);
		change_old_pwd(envp, old_path);
		free(old_path);
	}
	else
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd("No such file or directory: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("\n", 2);
	}
	free(old_path);
}

void	env(char **argv, char **envp)
{
	int	i;
	if (argv[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("' : Permission Denied\n", 2);
		return ;
	}
	i = 0;
	while(envp[i++])
	{
		if (!envp[i][0])
			break ;
		ft_putstr_fd(envp[i], 1);
		write(1, "\n", 1);
	}
}

char	*working_directory(void)
{
	char	*buf;
	int		n;

	n = 1;
	while (1)
	{
		buf = (char *)malloc(n * 100 * sizeof(char));
		if (buf == NULL)
			terminate(0);
		if (getcwd(buf, n++ * 100) == NULL)
		{
			free(buf);
			if (errno == ERANGE)
				continue ;
			else
				terminate(0);
		}
		break ;
	}
	return (buf);
}

void    pwd(void)
{
	char	*buf;

	buf = working_directory();
	ft_putstr_fd(buf, 1);
	write(1, "\n", 1);
	free(buf);
}

int	check_env_name(char *name)
{
	if (ft_isdigit(*name))
		return (0);
	while (*name)
	{
		if (!ft_isalnum(*name) && (*name != '_'))
			return (0);
		name++;
	}
	return (1);
}

void	print_unset_invalid(char *varname)
{
	ft_putstr_fd("bash: unset: `", 2);
	ft_putstr_fd(varname, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	matrix_free(char **matrix, int index)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (i < index)
		free(matrix[i]);
	free(matrix);
}

char	**remove_one_var(char **envp, int index)
{
	int	i;
	int	count;
	char	**new;

	i = 0;
	count = ft_count_matrix(envp);
	new = (char **)malloc(sizeof(char *) * count);
	if (!new)
		return (envp); 
	while (++i < count)
	{
		if (i == index)
			continue ;
		new[i] = ft_calloc(ft_strlen(envp[i]) + 1, sizeof(char));
		if (!new[i])
		{
			matrix_free(new, i);
			return (envp);
		}
		ft_strlcpy(new[i], envp[i], ft_strlen(envp[i]));
	}
	matrix_free(envp, count);
	return (new);
}

char	**unset_var(char *varname, char **envp)
{
	int		i;
	int		len;
	char	**new_envp;

	i = -1;
	len = ft_strlen(varname);
	while (envp[++i])
	{
		if ((int)ft_strlen(envp[i]) <= len)
			continue ;
		if (!ft_strncmp(varname, envp[i], len) && envp[i][len] == '=')
			break ;
	}
	if (!envp[i])
		return (envp);
	new_envp = remove_one_var(envp, i);
	return (new_envp);
}

void    unset(char **argv, char ***envp)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!check_env_name(argv[i]))
		{
			print_unset_invalid(argv[i]);
			continue ;
		}
		*envp = unset_var(argv[i], *envp);
		i++;
	}
}

void	exit_error_message(char *message, char *non_numeric)
{
	ft_putstr_fd("exit\nbash: exit: ", 2);
	if (non_numeric)
	{
		ft_putstr_fd(non_numeric, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

int	is_all_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	f_exit(char **argv)
{
	int	i;
	int	count;

	count = ft_count_matrix(argv);
	if (count >= 3)
		exit_error_message("too many arguments", 0);
	else if (count == 2 && !is_all_digit(argv[1]))
		exit_error_message("numeric argument required", argv[1]);
	else if (count == 2)
	{
		i = ft_atoi(argv[1]);
		free_argv(argv);
		exit(i);
	}
	else
	{
		free_argv(argv);
		exit(0);
	}
}

int	ft_strncmp_equalsign(char *s1, char *s2, int len)
{
	if ((!ft_strncmp(s1, s2, len)) && (s1[len - 1] == s2[len - 1]) 
		&& (s1[len - 1] == '='))
		return (0);
	return (1);
}

char	*ft_new_envp(char *key, char *new_val)
{
	int		key_len;
	int		val_len;
	int		total_len;
	char	*new_str;

	key_len = ft_strlen(key);
	val_len = ft_strlen(new_val);
	total_len = key_len + val_len + 2;
	new_str = (char *)malloc(sizeof(char) * total_len);
	if (!new_str)
		return (0);
	ft_strlcpy(new_str, key, key_len);
	new_str[key_len] = '=';
	ft_strlcpy(new_str + (key_len + 1), new_val, val_len);
	new_str[total_len - 1] = '\0';
	return (new_str);
}

int	ft_count_matrix(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	*ft_envp_copy(char **envp, int index)
{
	char	*tmp;
	int		len;

	len = ft_strlen(envp[index]);
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (0);
	ft_strlcpy(tmp, envp[index], len);
	return (tmp);
}

char	**new_added_envp(char *key_and_val, char **envp, int count)
{
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * count + 2);
	if (!tmp)
		return (0);
	i = 0;
	while (i < count)
	{
		tmp[i] = ft_envp_copy(envp, i);
		if (!tmp[i])
		{
			matrix_free(tmp, i);
			return (0);
		}
		i++;
	}
	tmp[i] = ft_strdup(key_and_val);
	if (!tmp[i])
	{
		matrix_free(tmp, i);
		return (0);
	}
	tmp[i + 1] = NULL;
	return (tmp);
}

int	ft_strlen_key(char *key_and_val)
{
	int	i;

	i = 0;
	while (key_and_val[i] && (key_and_val[i] != '='))
		i++;
	return (i);
}

char	**change_env(char *key_and_val, char **envp)
{
	char	**new_envp;
	char	*tmp;
	int		len;
	int		i;
	int		envp_count;

	len = ft_strlen_key(key_and_val) + 1;
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp_equalsign(envp[i], key_and_val, len))
			continue ;
		tmp = ft_strdup(key_and_val);
		if (!tmp)
			return (0);
		free(envp[i]);
		envp[i] = tmp;
		return (envp);
	}
	envp_count = ft_count_matrix(envp);
	new_envp = new_added_envp(key_and_val, envp, envp_count);
	if (!new_envp)
		return (0);
	free_argv(envp);
	return (new_envp);
}


void	print_export_invalid(char *varname)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(varname, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	check_export_valid(char *argv)
{
	if (ft_isdigit(*argv))
		return (0);
	while ((*argv) && (*argv != '='))
	{
		if (!ft_isalnum(*argv) && (*argv != '_'))
			return (0);
		argv++;
	}
	return (1);
}

void    export(char **argv, char ***envp)
{
	int	i;
	int	count;

	i = 0;
	count = ft_count_matrix(argv);
	while (++i < count)
	{
		if (!ft_strchr(argv[i], '='))
			continue ;
		if (!check_export_valid(argv[i]))
		{
			print_export_invalid(argv[i]);
			continue ;
		}
		*envp = change_env(argv[i], *envp);
		if (!(*envp))
			terminate(0);
	}
}

bool	isbuiltin(char **argv, char ***envp)
{
	if (ft_strcmp(argv[0], "echo"))
		echo(argv);
	else if (ft_strcmp(argv[0], "cd"))
		cd(argv, envp);
	else if (ft_strcmp(argv[0], "pwd"))
		pwd();
	else if (ft_strcmp(argv[0], "export"))
		export(argv, envp);
	else if (ft_strcmp(argv[0], "unset"))
		unset(argv, envp);
	else if (ft_strcmp(argv[0], "env"))
		env(argv, *envp);
	else if (ft_strcmp(argv[0], "exit"))
		f_exit(argv);
	else
		return (false);
	return (true);
}
