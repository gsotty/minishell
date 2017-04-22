/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traite_signal_fork.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 19:42:06 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/12 19:43:48 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	traite_signal_fork(int s)
{
	signal(s, traite_signal);
	write(1, "\n", 1);
}

void	traite_signal(int s)
{
	signal(s, traite_signal);
	write(1, "\n", 1);
	print_prompt();
}
