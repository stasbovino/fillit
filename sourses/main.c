/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:01:55 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/03/26 15:39:35 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"
#include <fcntl.h>

int		count_figures(int fd)
{
	int		r;
	char	*line;
	size_t	count;
	size_t	n;

	count = 0;
	while ((r = get_next_line(fd, &line)) > 0)
	{
		free(line);
		count++;
	}
	free(line);
	if (((count + 1) % 5) != 0)
		return (-1);
	n = (count + 1) / 5;
	if ((n == 0) || (n > 26))
		return (-1);
	return (n);
}

void	clean_them_all(t_figure **a, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		free(a[i]);
		i++;
	}
	free(a);
	a = NULL;
}

int		main(int argc, char **argv)
{
	int			fd;
	t_figure	**a;
	int			i;
	int			count;

	if (argc != 2)
		print_usage();
	else
	{
		i = -1;
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			print_error(-2, NULL, 0);
		if ((count = (int)count_figures(fd)) == -1)
			print_error(fd, NULL, 0);
		close(fd);
		fd = open(argv[1], O_RDONLY);
		if (!(a = (t_figure**)malloc(sizeof(t_figure*) * count)))
			print_error(fd, NULL, 0);
		while (++i < count)
			if (!(a[i] = read_figure(fd, i)))
				print_error(-1, a, count);
		if (get_solution(a, count, (int)ft_sqrt((count * 4), 1)) == -1)
			print_error(-1, a, count);
		clean_them_all(a, count);
	}
	return (0);
}
