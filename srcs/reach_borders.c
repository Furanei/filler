/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reach_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 03:26:01 by mbriffau          #+#    #+#             */
/*   Updated: 2017/10/17 17:11:30 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	has_reached_borders(t_filler *f, int b[f->max.y][f->max.x])
{
	get_board_picture(f, b);
	if (f->min_ply.y.y == 0)
		f->goal &= ~1;
	else if (f->max_ply.y.y == f->max.y - 1)
		f->goal &= ~8;
	if (f->min_ply.x.x == 0)
		f->goal &= ~2;
	else if (f->max_ply.x.x == f->max.x - 1)
		f->goal &= ~4;
}

int		has_captured_center(t_filler *f, int b[f->max.y][f->max.x])
{
	t_index	i;
	int		check;

	i.y = f->min_area.y - 1;
	while (++i.y < f->max_area.y)
	{
		i.x = f->min_area.x - 1;
		check = 0;
		while (++i.x < f->max_area.x)
			check |= b[i.y][i.x];
		if ((check & 1) && (check & 2))
			return (1);
	}
	i.x = f->min_area.x - 1;
	while (++i.x < f->max_area.x)
	{
		i.y = f->min_area.y - 1;
		check = 0;
		while (++i.y < f->max_area.y)
			check |= b[i.y][i.x];
		if ((check & 1) && (check & 2))
			return (1);
	}
	return (0);
}
