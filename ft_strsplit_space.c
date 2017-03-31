/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 10:44:03 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/31 11:57:55 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	ft_mot(const char *s)
{
	int		x;
	int		y;
	char	*str;

	x = 0;
	y = 0;
	str = (char *)s;
	while (*str != '\0')
	{
		if (y == 1 && (*str == ' ' || *str == '\t'))
			y = 0;
		if (y == 0 && (*str != ' ' && *str != '\t'))
		{
			y = 1;
			x++;
		}
		str++;
	}
	return (x);
}

static int	ft_len_mot(const char *s)
{
	int		len;
	char	*str;

	len = 0;
	str = (char *)s;
	while ((*str != ' ' && *str != '\t') && *str != '\0')
	{
		len++;
		str++;
	}
	return (len);
}

static int	ft_while(char const *s, char **tab, int x, int y)
{
	int		len_mot;

	while ((s[y] == ' ' || s[y] == '\t') && s[y] != '\0')
		y++;
	len_mot = ft_len_mot(s + y);
	if ((tab[x] = (char *)malloc(sizeof(char) * len_mot + 1)) == NULL)
		return (-1);
	tab[x] = ft_memcpy(tab[x], (const char *)s + y, len_mot);
	tab[x][len_mot] = '\0';
	y += len_mot;
	return (y);
}

char		**ft_strsplit_space(char const *s)
{
	char	**tab;
	int		nbr_mot;
	int		y;
	int		x;

	x = 0;
	y = 0;
	if (s == NULL)
		return (NULL);
	nbr_mot = ft_mot(s);
	if ((tab = (char **)malloc(sizeof(char *) * nbr_mot + 1)) == NULL)
		return (NULL);
	tab[nbr_mot] = NULL;
	while (nbr_mot)
	{
		if ((y = ft_while(s, tab, x, y)) == -1)
			return (NULL);
		nbr_mot--;
		x++;
	}
	return (tab);
}
