/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 11:19:04 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/08 12:16:11 by gsotty           ###   ########.fr       */
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

int					echo(char **argv);
char				**creat_char_envp(t_env *env);
char				**exe(char *buf, char **envp);
char				**cd(char **argv, char **envp);
char				**ft_env(char **cmd, char **env);
char				**ft_strsplit_space(char const *s);
char				**exe_cmd(int argc, char **argv, char **envp);
t_env				*creat_new(char *envp);
t_env				*creat_t_env(char **envp);
t_env				*find_var_env(t_env *env, char *name);
t_env				*add_env(t_env *begin_env, char *envp);
t_env				*remove_env(t_env *begin_env, char *name);
void				free_env(t_env *env);
void				free_tab(char **tab);

/*
**
** int					len_argc(char **cmd);
** int					ft_setenv(t_env *begin_env, char **cmd);
** t_env				*ft_unsetenv(t_env *begin_env, char **cmd);
**
*/

#endif
