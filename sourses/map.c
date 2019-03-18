/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 21:07:36 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/03/18 21:58:37 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

void			place_figure(t_square *dst, t_figure *figure, t_coord *pos)
{
	int			i;
	char		s;
	char		***map;

	map = &(dst->map);
	s = figure->order;
	i = 0;
	(*map)[pos->y][pos->x] = s;
	(*map)[pos->y + figure->fig.second.y][pos->x + figure->fig.second.x] = s;
	(*map)[pos->y + figure->fig.third.y][pos->x + figure->fig.third.x] = s;
	(*map)[pos->y + figure->fig.fourth.y][pos->x + figure->fig.fourth.x] = s;
}

t_square		*create_map(int count)
{
	char		**a;
	int			size;
	int			i;
	int			j;
	t_square	*map;

	if (!(map = (t_square*)malloc(sizeof(t_square))))
		return (NULL);
	i = 0;
	size = (int)ft_sqrt(count, 1);
	if (!(a = (char**)malloc(sizeof(char*) * size)))
		return (NULL);
	while (i < size)
	{
		if (!(a[i] = (char*)malloc(sizeof(char) * (size + 1))))
			return (NULL);
		j = -1;
		while (++j < size)
			a[i][j] = i + j + 97;
		a[i++][size] = '\0';
	}
	map->map = a;
	map->size = size;
	return (map);
}

void			print_map(t_square *map)
{
	int			i;
	int			j;
	int			n;
	char		**tab;

	if (!map)
		return ;
	n = map->size;
	tab = map->map;
	i = -1;
	while (++i < n)
	{
		j = 0;
		printf(" %d ", i);
		//ft_putnbr(i);
		while (tab[i][j])
		{
			if (!(ft_isupper(tab[i][j])))
				ft_putstr(" . ");
			else
			{
				ft_putchar('[');
				ft_putchar(tab[i][j]);
				ft_putchar(']');
			}
			j++;
		}
		ft_putchar(' ');
		ft_putnbr(i);
		ft_putchar('\n');
	}
	return ;
}

int				clean_map(t_square *map)
{
	int			i;
	int			n;

	n = map->size;
	i = 0;
	while (i < n)
	{
		printf("%d", i);
		free((map->map)[i]);
		i++;
	}
	free(map->map);
	map->map = NULL;
	free(map);
	map = NULL;
	return (-1);
}

t_square		*copy_map(t_square *src)
{
	int			i;
	char		**map;
	t_square	*a;
	int			n;

	n = src->size;
	if (!(a = (t_square*)malloc(sizeof(t_square))))
		return (NULL);
	if (!(map = (char**)malloc(sizeof(char*) * n)))
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (!(map[i] = (char*)malloc(sizeof(char) * (n + 1))))
			return (NULL);
		map[i] = ft_strcpy(map[i], (src->map)[i]);
		i++;
	}
	a->map = map;
	a->size = n;
	return (a);
}
