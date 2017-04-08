/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 11:34:50 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/08 17:04:52 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exe_path(char **argv, char **envp, char **path)
{
	int		x;
	int		len_path;
	char	*tmp_join;
	char	*tmp_path;

	x = 0;
	while (path[x] != NULL)
	{
		len_path = ft_strlen(path[x]);
		if (!(tmp_path = ft_memalloc(sizeof(char) * (len_path + 2))))
			return ;
		ft_memcpy(tmp_path, path[x], len_path);
		ft_strcat(tmp_path, "/");
		if (access(tmp_join = ft_strjoin(tmp_path, argv[0]),
					F_OK | X_OK) == 0)
		{
			free(argv[0]);
			argv[0] = ft_strdup(tmp_join);
			execve(tmp_join, argv, envp);
			free(tmp_join);
			return ;
		}
		free(tmp_path);
		free(tmp_join);
		x++;
	}
	ft_printf("minishell: command not found: %s\n", argv[0]);
}

static void	no_exe_cmd(int argc, char **argv, char **envp)
{
	t_env	*tmp;
	t_env	*env;
	char	**path;

	if (argc == 0)
		return ;
	env = creat_t_env(envp);
	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, "PATH") == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		ft_printf("minishell: command not found: %s\n", argv[0]);
	else
	{
		path = ft_strsplit(tmp->data, ':');
		exe_path(argv, envp, path);
		free_tab(path);
	}
	free_env(env);
}

char		**exe_cmd(int argc, char **argv, char **envp)
{
	pid_t	father;

	if (ft_strcmp(argv[0], "env") == 0)
	{
		father = fork();
		if (father > 0)
		{
			wait(NULL);
			return (envp);
		}
		if (father == 0)
		{
			envp = ft_env(argv, envp);
			exit(0);
		}
	}
	else if (ft_strcmp(argv[0], "echo") == 0)
		echo(argv);
	else if (ft_strcmp(argv[0], "setenv") == 0)
	{
	}
	else if (ft_strcmp(argv[0], "unsetenv") == 0)
	{
	}
	else if (ft_strcmp(argv[0], "cd") == 0)
	{
		envp = cd(argv, envp);
	}
	else
	{
		father = fork();
		if (father > 0)
		{
			wait(NULL);
			return (envp);
		}
		if (father == 0)
		{
			if (access(argv[0], F_OK | X_OK) == 0)
				execve(argv[0], argv, envp);
			else
				no_exe_cmd(argc, argv, envp);
			exit(0);
		}
	}
	return (envp);
}

static int	len_tab(char **argv)
{
	int		x;

	x = 0;
	while (argv[x] != NULL)
		x++;
	return (x);
}

char		**exe(char *buf, char **envp)
{
	int		argc;
	char	**argv;

	argv = ft_strsplit_space(buf, " \t");
	argc = len_tab(argv);
	envp = exe_cmd(argc, argv, envp);
	free_tab(argv);
	return (envp);
}
