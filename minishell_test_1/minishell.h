/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 11:19:04 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/09 18:22:23 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include <unistd.h>

typedef struct		s_flag_env
{
	unsigned int	i_min : 1;
	unsigned int	u_min : 1;
	char			*name;
}					t_flag_env;

typedef struct		s_split
{
	int				j;
	int				x;
}					t_split;

int					echo(char **argv);
char				**creat_envp(char **envp);
char				**exe(char *buf, char **envp);
char				**cd(char **argv, char **envp);
char				**ft_env(char **cmd, char **env);
char				**add_env(char **envp, char *data);
char				**ft_setenv(char **envp, char **cmd);
char				**remove_env(char **envp, char *name);
char				*find_var_env(char **env, char *name);
char				**ft_unsetenv(char **envp, char **cmd);
char				**ft_strsplit_space(char const *s, char *c);
char				**exe_cmd(int argc, char **argv, char **envp);
char				**remalloc_envp(char **envp, int after_size, int new_size);
void				free_tab(char **tab);

#endif
