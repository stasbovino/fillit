/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:17:29 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/03/18 21:38:17 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

#include "libft.h"
#include <stdio.h>

typedef struct		s_typeof_figure
{
	t_coord			first;
	t_coord			second;
	t_coord			third;
	t_coord			fourth;
}					t_typeof_figure;

typedef struct		s_figure
{
	char			order;
	t_typeof_figure	fig;
}					t_figure;

typedef struct		s_square
{
	char	**map;
	int		size;
}					t_square;

int					test(t_figure **a, int count);

void				place_figure(t_square *dst, t_figure *figure, t_coord *pos);
t_coord				*find_pos(t_square *src, t_figure *figure);
t_coord				*first_diag(t_square *src, t_figure *figure, int k, int worth);
t_coord				*second_diag(t_square *src, t_figure *figure, int k, int worth);

int					is_figure_fit(t_square *src, t_figure *figure, int x, int y);
int					check_borders(int size, int x, int y);

t_square			*create_map(int count);
void				print_map(t_square *map);
int					clean_map(t_square *map);
t_square			*copy_map(t_square *src);

int					count_figures(int fd);/*fillit.c*/
int					clean_them_all(t_figure **a, int count);

int					end_reading(int fd);/*read_figure.c*/
int					read_one_line(int fd, char **line);
t_figure			*read_figure(int fd, int n);

int					check_line(char *tmp);/*check_valid.c*/
int					find_sharps(char **line, int i, int opt);
int					valid_line(char *line);

int					write_coord(int *x, int *y, char *line, int opt);/*get_figure.c*/
int					get_figure(char *line, int n, t_figure **place);

#endif
