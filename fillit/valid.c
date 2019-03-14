#include "libft.h"
#include "fillit.h"
#include <stdio.h>

int		check_line(char *tmp)
{
	int	i;

	i = 0;
	if (!tmp || !*tmp)
		return (-1);
	if (ft_strlen(tmp) != 4)
		return (-1);
	while (tmp[i])
	{
		if ((tmp[i] != '#') && (tmp[i] != '.'))
			return (-1);
		i++;
	}
	return (1);
}

int		find_sharps(char **line, int i, int opt)
{
	static int	k;

	if (opt == 1)
		k = 0;
	while ((*line)[i] && ((*line)[i] != '#'))
		i++;
	if ((*line)[i] == '#')
	{
		k++;
		(*line)[i] = 'F';
		if (i < 15 && (*line)[i + 1] == '#')
			find_sharps(line, i + 1, 0);
		if (i > 0 && (*line)[i - 1] == '#')
			find_sharps(line, i - 1, 0);
		if (i < 12 && (*line)[i + 4] == '#')
			find_sharps(line, i + 4, 0);
		if (i > 3 && (*line)[i - 4] == '#')
			find_sharps(line, i - 4, 0);
	}
	return (k);
}

int		valid_line(char *line)
{
	char	*tmp;
	int		i;

	tmp = (char*)malloc(sizeof(char) * 17);
	tmp = ft_strcpy(tmp, line);
	if (ft_countchars(tmp, '#') != 4)
	{
		free(tmp);
		return (-1);
	}
	i = (int)ft_strchrpos(line, '#');
	if (find_sharps(&tmp, 0, 1) != 4)
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (1);
}

int		write_coord(int *x, int *y, char *line, int opt)
{
	static int i;
	static int start;

	if (opt == 1)
	{
		i = 0;
		i = ft_strchrpos(line, '#');
		start = i;
		i++;
	}
	while (line[i] && (line[i] != '#'))
		i++;
	if (line[i] == '#')
	{
		*x = (i % 4) - (start % 4);
		*y = (i / 4) - (start / 4);
		i++;
	}
	else
		return (-1);
	return (0);
}

int		get_figure(char *line, int n, t_figure **place)
{
	t_figure *figure;

	figure = (t_figure*)malloc(sizeof(t_figure));
	figure->order = 65 + n;
	figure->fig.first.x = 0;
	figure->fig.first.y = 0;
	if (write_coord(&(figure->fig.second.x),
				&(figure->fig.second.y), line, 1) != -1)
		if (write_coord(&(figure->fig.third.x),
					&(figure->fig.third.y), line, 0) != -1)
			if (write_coord(&(figure->fig.fourth.x),
						&(figure->fig.fourth.y), line, 0) != -1)
			{
				*place = figure;
				return (0);
			}
	free(figure);
	return (-1);
}

int			read_one_line(int fd, char **line)
{
	int		i;
	char	*tmp;
	int		r;

	i = -1;
	while (++i < 5)
	{
		printf("i is %d\n", i);
		r = get_next_line(fd, &tmp);
		if (i != 4)
		{
			if (r != 1)
				break ;
			if (check_line(tmp) == -1)
				break ;
			if (!(*line = ft_strrejoin(*line, tmp)))
				break ;
		}
		free(tmp);
	}
	if (i == 5)
		return (1);
	free(tmp);
	while (get_next_line(fd, &tmp) != 0)
		free(tmp);
	free(tmp);
	return (-1);
}

t_figure	*read_figure(int fd, int n)
{
	char		*line;
	t_figure	*figure;

	if (!(line = ft_strnew(0)))
		return (NULL);
	if (read_one_line(fd, &line) == -1)
	{
		free(line);
		return (NULL);
	}
	if (valid_line(line) == -1)
	{
		free(line);
		return (NULL);
	}
	if (get_figure(line, n, &figure) == -1)
	{
		free(line);
		return (NULL);
	}
	free(line);
	return (figure);
}
