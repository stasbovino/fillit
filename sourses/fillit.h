/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:17:29 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/03/23 22:31:59 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"

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

int					get_solution(t_figure **a, int count, int size);
void				del_figure(t_square *dst, t_figure *figure, t_coord *pos);
void				place_figure(t_square *dst, t_figure *figure, t_coord *pos);
t_coord				*find_pos(t_square *src, t_figure *figure);
t_square			*create_map(int count);
void				print_map(t_square *map);
int					clean_map(t_square *map);
t_square			*copy_map(t_square *src);
t_figure			*read_figure(int fd, int n);
int					check_line(char *tmp);
int					valid_line(char *line);
int					get_figure(char *line, int n, t_figure **place);

#endif
