/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 21:37:38 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/03/28 19:37:51 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

static int		clean_and_ret(t_square *tmp, int ret)
{
	clean_map(tmp);
	return (ret);
}

static int		place_it(t_square *tmp, t_figure **figures, int count, int i)
{
	t_coord	*pos;
	int		ret;

//	printf("\n\nFIGIRE IS %c\n\n", i + 65);
	while ((pos = find_pos(tmp, figures[i])))
	{
		place_figure(tmp, figures[i], pos);
//		printf("\n\x1b[33mAFTER PLACING %c:\x1b[0m\n", i + 65);
//		print_map(tmp);
		map_restore(tmp, "save", i);
		if ((ret = fill_it(&tmp, figures, count, i + 1)) < 0)
		{
			if (ret == -2)
				return (clean_and_ret(tmp, -2));
			del_figure(tmp, figures[i], pos);
			map_restore(tmp, "save", i);
//			printf("\n\x1b[31mAFTER REST %c:\x1b[0m\n", i + 65);
//			print_map(tmp);
			free(pos);
		}
		else
		{
			free(pos);
			if (ret == 0)
			{
//				printf("\nSOLUTION IS:\n");
				map_restore(tmp, "finish", 0);
//				print_map(tmp);
			}
			return (clean_and_ret(tmp, 1));
		}
	}
//	printf("\n\x1b[36mNO POS FOR %c:\x1b[0m\n", i + 65);
//	print_map(tmp);
	return (3);
}

int		fill_it(t_square **map, t_figure **figures, int count, int i)
{
	t_square	*tmp;
	int			ret;

	if (i >= count)
		return (0);
	if (!(tmp = copy_map(*map, 1)))
		return (-2);
/*	ft_putchar('\n');
	ft_putstr("Hello! figure is ");
	ft_putchar(i + 65);
	ft_putchar('\n');
	ft_putchar('\n');
	print_map(tmp);
	ft_putchar('\n');*/
	map_restore(tmp, "rest", i);
/*	ft_putchar('\n');
	ft_putchar(i + 65);
	ft_putstr(" after restoring");
	ft_putchar('\n');
	ft_putchar('\n');
	print_map(tmp);
	ft_putchar('\n');*/
	if ((ret = place_it(tmp, figures, count, i)) != 3)
		return (ret);
//	printf("\n\x1b[32mSAVED %c:\x1b[0m\n", i + 65);
//	print_map(tmp);
	clean_map(tmp);
	return (-1);
}

int				get_solution(t_figure **a, int count, int size)
{
	t_square	*map;
	int			ret;
	char		*equal_fig;

	equal_fig = find_same_figures(a, count);
//	ft_putstr(equal_fig);
//	ft_putchar('\n');
	if (map_restore(NULL, equal_fig, count) == -1)
		return (-1);
	free(equal_fig);
	if (!(map = create_map(size)))
		return (-1);
	while ((ret = fill_it(&map, a, count, 0)) != 1)
	{
		clean_map(map);
		if (ret == -2)
			return (-1);
		if (!(map = create_map(size++)))
			return (-1);
	}
	map_restore(NULL, "clean", count);
	clean_map(map);
	return (0);
}
