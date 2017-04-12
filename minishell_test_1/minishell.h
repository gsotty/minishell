/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 11:19:04 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/12 19:43:30 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include <unistd.h>
# include <signal.h>

typedef struct		s_flag_env
{
	unsigned int	i_min : 1;
	unsigned int	u_min;
	char			*name;
}					t_flag_env;

typedef struct		s_split
{
	int				j;
	int				x;
}					t_split;

typedef struct		s_intflag
{
	int				x;
	int				y;
}					t_intflag;

int					echo(char **argv);
int					check_flag_env(char **cmd, t_flag_env *flag, char **envp);
char				**creat_envp(char **envp);
char				**exe(char *buf, char **envp);
char				**cd(char **argv, char **envp);
char				**ft_env(char **cmd, char **env);
char				**add_env(char **envp, char *data);
char				**ft_setenv(char **envp, char **cmd);
char				**remove_env(char **envp, char *name);
char				*find_var_env(char **env, char *name);
char				**ft_unsetenv(char **envp, char **cmd);
char				**exe_cmd_no_fork(char **argv, char **envp);
char				**ft_strsplit_space(char const *s, char *c);
char				**exe_cmd(int argc, char **argv, char **envp);
char				**exe_fork(int argc, char **argv, char **envp);
char				**remalloc_envp(char **envp, int after_size, int new_size);
void				print_prompt(void);
void				free_tab(char **tab);
void				traite_signal(int s);
void				traite_signal_fork(int s);

#endif
