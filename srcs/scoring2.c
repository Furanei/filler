/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scoring2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 02:47:54 by mbriffau          #+#    #+#             */
/*   Updated: 2017/10/12 03:50:00 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		score_top_left(t_filler *f, int b[f->max.y][f->max.x], t_index p)
{
	t_index		i;
	int			range_i;
	int			range;

	range = 1;
	i.y = p.y;
	while (--i.y >= 0)
	{
		i.x = p.x;
		if (range + p.x >= f->max.x - 1)
			return (1);
		++range;
		range_i = 0;
		while (i.x >= 0 && range_i < range)
		{
			if (b[i.y][i.x] >> 1)
				return (i.x == p.x ? 0 : range);
			--i.x;
			++range_i;
		}
	}
	return (range);
}

int		score_top_right(t_filler *f, int b[f->max.y][f->max.x], t_index p)
{
	t_index		i;
	int			range_i;
	int			range;

	range = 1;
	i.y = p.y;
	while (--i.y >= 0)
	{
		i.x = p.x;
		if (range + p.x >= f->max.x - 1)
			return (1);
		++range;
		range_i = 0;
		while (i.x < f->max.x && range_i < range)
		{
			if (b[i.y][i.x] >> 1)
				return (i.x == p.x ? 0 : range);
			++i.x;
			++range_i;
		}
	}
	return (range);
}
