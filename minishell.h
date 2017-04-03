/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 11:19:04 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/03 17:33:07 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include <unistd.h>

typedef struct		s_env
{
	char			*name;
	char			*data;
	struct s_env	*next;
}					t_env;

typedef struct		s_flag_env
{
	unsigned int	i_min : 1;
	unsigned int	u_min : 1;
	char			*name;
}					t_flag_env;

int		len_argc(char **cmd);
char	**ft_strsplit_space(char const *s);
int		echo(char **argv);
t_env	*cd(t_env *env, char **argv);
int		ft_env(char **cmd, t_env *env);
int		ft_setenv(t_env *begin_env, char **cmd);
t_env	*ft_unsetenv(t_env *begin_env, char **cmd);
int		exe_cmd(char **cmd, char **envp);
t_env	*creat_t_env(char **envp);
char	**creat_char_envp(t_env *env);
t_env	*creat_new(char *envp);
t_env	*add_env(t_env *begin_env, char *envp);
t_env	*remove_env(t_env *begin_env, char *name);

#endif
