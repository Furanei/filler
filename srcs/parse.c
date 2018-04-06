/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 19:54:02 by mbriffau          #+#    #+#             */
/*   Updated: 2017/10/15 04:09:28 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	trim_piece(t_filler *f, int p[f->piece_dim.y][f->piece_dim.x])
{
	t_index		i;
	t_index		tmp;

	f->max_dim = (t_index) {.x = 0, .y = 0};
	i.y = -1;
	while (++i.y < f->piece_dim.y - f->min_dim.y && (i.x = -1))
	{
		tmp.x = 0;
		while (++i.x < f->piece_dim.x - f->min_dim.x)
		{
			p[i.y][i.x] = p[i.y + f->min_dim.y][i.x + f->min_dim.x];
			p[i.y + f->min_dim.y][i.x + f->min_dim.x] = 0;
			p[i.y][i.x] ? ++tmp.x : 0;
		}
		f->max_dim.x = (tmp.x > f->max_dim.x ? tmp.x : f->max_dim.x);
	}
	i.x = -1;
	while (++i.x < f->piece_dim.x - f->min_dim.x && (i.y = -1))
	{
		tmp.y = 0;
		while (++i.y < f->piece_dim.y - f->min_dim.y)
			p[i.y][i.x] ? ++tmp.y : 0;
		f->max_dim.y = (tmp.y > f->max_dim.y ? tmp.y : f->max_dim.y);
	}
}

t_index	ft_check_min_piece(t_filler *f, int p[f->piece_dim.y][f->piece_dim.x])
{
	t_index	i;
	t_index	min;

	i.y = -1;
	min.y = -1;
	while (++i.y < f->piece_dim.y && min.y == -1)
	{
		i.x = -1;
		while (++i.x < f->piece_dim.x && min.y == -1)
			if (p[i.y][i.x])
				min.y = i.y;
	}
	i.x = -1;
	min.x = -1;
	while (++i.x < f->piece_dim.x && min.x == -1)
	{
		i.y = -1;
		while (++i.y < f->piece_dim.y && min.x == -1)
			if (p[i.y][i.x])
				min.x = i.x;
	}
	return (min);
}

void	get_piece_dimension(t_filler *f, char *line, int b[f->max.y][f->max.x])
{
	int		p[f->piece_dim.y][f->piece_dim.x];
	t_index	i;

	i.y = -1;
	while (++i.y < f->piece_dim.y)
	{
		get_next_line(0, &line);
		i.x = -1;
		while (++i.x < f->piece_dim.x)
			p[i.y][i.x] = (int)((46 - line[i.x]) >> 2);
	}
	f->min_dim = (t_index) {0, 0};
	f->min_dim = ft_check_min_piece(f, p);
	if (f->min_dim.y || f->min_dim.x)
	{
		trim_piece(f, p);
		if (f->max_dim.y == f->max_dim.x)
			f->ver_hor = 0;
		else
			f->ver_hor = f->max_dim.y > f->max_dim.x ? 1 : -1;
	}
	solver(f, b, p);
}

void	filler_atoi(t_index *max, char *s)
{
	int		value;

	value = 0;
	while (*s >= '0' && *s <= '9')
		value = value * 10 + *s++ - '0';
	max->y = value;
	++s;
	value = 0;
	while (*s >= '0' && *s <= '9')
		value = value * 10 + *s++ - '0';
	max->x = value;
	if (max->x <= 0 || max->y <= 0)
		exit(1);
}

void	return_piece(int a, int b)
{
	char	*s;
	t_index	tmp;
	t_index	i;

	tmp.x = a;
	tmp.y = b;
	i.x = (a < 0) ? 2 : 1;
	i.y = (b < 0) ? 2 : 1;
	while ((tmp.x /= 10) >= 1)
		++i.x;
	while ((tmp.y /= 10) >= 1)
		++i.y;
	if (!(s = (char*)malloc(sizeof(char) * (i.x + i.y + 3))))
		return ;
	s[i.x] = ' ';
	s[i.x + i.y + 1] = '\n';
	s[i.x + i.y + 2] = '\0';
	while (i.y-- && (s[i.x + 1 + i.y] = b % 10 + '0'))
		b /= 10;
	while (i.x-- && (s[i.x] = a % 10 + '0'))
		a /= 10;
	ft_putstr(s);
	free(s);
}
