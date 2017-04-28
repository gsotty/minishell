/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traite_signal_fork.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 19:42:06 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/27 16:46:46 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	traite_signal_fork(int s)
{
	write(1, "\n", 1);
	signal(s, traite_signal);
}

void	traite_signal(int s)
{
	write(1, "\n", 1);
	print_prompt();
	signal(s, traite_signal);
}
