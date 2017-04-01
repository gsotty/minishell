/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 11:19:04 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/01 12:47:03 by gsotty           ###   ########.fr       */
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
	unsigned int	p_maj : 1;
	unsigned int	s_maj : 1;
	unsigned int	u_min : 1;
	unsigned int	v_min : 1;
}					t_flag_env;

int		len_argc(char **cmd);
char	**ft_strsplit_space(char const *s);
int		echo(char **argv);
int		cd(char **argv);
int		env(char **cmd, t_env *env);
int		exe_cmd(char **cmd, char **envp);
t_env	*creat_t_env(char **envp);
char	**creat_char_envp(t_env *env);

#endif
