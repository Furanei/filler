/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 19:54:16 by mbriffau          #+#    #+#             */
/*   Updated: 2017/10/17 17:11:28 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		next_to_cpu(t_filler *f, int b[f->max.y][f->max.x], t_index i)
{
	return (b[i.y][i.x] >> 1 &&
	((i.y > 0 && i.y < f->max.y - 1
		&& (!b[i.y + 1][i.x] || !b[i.y - 1][i.x]))
	|| (i.x > 0 && i.x < f->max.x - 1
		&& (!b[i.y][i.x + 1] || !b[i.y][i.x - 1]))
	|| (!i.y && !b[i.y + 1][i.x]) || (!i.x && !b[i.y][i.x + 1])
	|| (i.y == f->max.y - 1 && !b[i.y - 1][i.x])
	|| (i.x == f->max.x - 1 && !b[i.y][i.x - 1])));
}

int		get_dst(t_filler *f, int b[f->max.y][f->max.x], t_index p)
{
	t_index		i;
	int			distance;
	int			tmp;

	distance = f->max.y * f->max.y + f->max.x * f->max.x;
	i.y = -1;
	while (++i.y < f->max.y)
	{
		i.x = -1;
		while (++i.x < f->max.x)
		{
			tmp = (i.y - p.y) * (i.y - p.y) + (i.x - p.x) * (i.x - p.x);
			if (next_to_cpu(f, b, i) && tmp < distance)
				if ((distance = tmp) == 2)
					return (distance);
		}
	}
	return (distance);
}

void	surround(t_filler *f, int b[f->max.y][f->max.x], t_point *points)
{
	LAST = points->i;
	while (points)
	{
		if (get_dst(f, b, points->i) < get_dst(f, b, LAST))
			LAST = points->i;
		else if (get_dst(f, b, points->i) == get_dst(f, b, LAST) && f->goal)
		{
			if (f->ver_hor > 0)
			{
				if ((f->goal & 1) ? points->i.y < LAST.y : points->i.y > LAST.y)
					LAST = points->i;
			}
			else if (f->ver_hor < 0)
				if ((f->goal & 2) ? points->i.x < LAST.x : points->i.x > LAST.x)
					LAST = points->i;
		}
		points = points->next;
	}
}

void	solver(t_filler *f, int b[f->max.y][f->max.x],
		int p[f->piece_dim.y][f->piece_dim.x])
{
	t_point		*points;
	t_index		ply_area;

	points = NULL;
	ply_area = (t_index) {.x = 0, .y = 0};
	LAST.y = f->min_dim.y - 42;
	LAST.x = f->min_dim.x - 42;
	init_min(f);
	check_min(f, b);
	check_max(f, b);
	put_piece(f, b, p, &points);
	if (points)
	{
		has_reached_borders(f, b);
		if (!has_captured_center(f, b) || f->goal)
			break_through(f, b, points);
		else
			surround(f, b, points);
		free_saved_positions(&points);
	}
	return_piece(LAST.y - f->min_dim.y, LAST.x - f->min_dim.x);
}
