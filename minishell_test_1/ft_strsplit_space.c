/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 15:59:07 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/08 13:42:09 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_nbr_mot(char const *buf)
{
	int		j;
	int		y;
	int		x;

	x = 0;
	j = 0;
	y = 0;
	while (buf[x] != '\0')
	{
		while ((buf[x] == ' ' || buf[x] == '\t') && buf[x] != '\0')
		{
			j = 0;
			x++;
		}
		if (buf[x] != ' ' && buf[x] != '\t' && buf[x] != '\0' && j == 0)
		{
			j = 1;
			y++;
		}
		x++;
	}
	return (y);
}

int		ft_while(char const *buf, char **tab)
{
	int		j;
	int		y;
	int		x;
	int		z;

	z = 0;
	x = 0;
	j = 0;
	y = 0;
	while (buf[x] != '\0')
	{
		while ((buf[x] == ' ' || buf[x] == '\t') && buf[x] != '\0')
		{
			j = 0;
			x++;
		}
		if (buf[x] != ' ' && buf[x] != '\t' && buf[x] != '\0' && j == 0)
		{
			j = 1;
			z = x;
			while (buf[z] != ' ' && buf[z] != '\t' && buf[z] != '\0')
				z++;
			if ((tab[y] = ft_memalloc(sizeof(**tab) * ((z - x) + 2))) == NULL)
				return (0);
			ft_memcpy(tab[y], buf + x, z);
			tab[y][z - x] = '\0';
			y++;
		}
		x++;
	}
	return (y);
}

char	**ft_strsplit_space(char const *buf)
{
	int		nbr_mot;
	char	**tab;

	tab = NULL;
	nbr_mot = ft_nbr_mot(buf);
	if ((tab = ft_memalloc(sizeof(*tab) * (nbr_mot + 1))) == NULL)
		return (NULL);
	ft_while(buf, tab);
	int	x=0;
	while (tab[x] != NULL)
	{
//		ft_printf("tab[x] = %s\n", tab[x]);
		x++;
	}
	return (tab);
}
