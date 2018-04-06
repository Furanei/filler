/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_positions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 02:15:20 by mbriffau          #+#    #+#             */
/*   Updated: 2017/10/13 17:46:58 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

t_point	*new_point(t_index i, int score)
{
	t_point	*point;

	if (!(point = (t_point *)malloc(sizeof(t_point))))
		return (NULL);
	point->i = i;
	point->score = score;
	point->next = NULL;
	return (point);
}

void	add_point(t_point **points, t_index i, int score)
{
	t_point	*lst;

	if ((lst = *points))
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new_point(i, score);
	}
	else
		*points = new_point(i, score);
}

int		is_valid_position(t_filler *f, BOARD, PIECE, t_index i)
{
	t_index	pad;
	int		connected;
	int		score;

	score = 0;
	connected = 0;
	pad.y = -1;
	while (++pad.y < f->piece_dim.y)
	{
		pad.x = -1;
		while (++pad.x < f->piece_dim.x)
		{
			if (p[pad.y][pad.x])
			{
				if (pad.y + i.y < f->min_dim.y || pad.x + i.x < f->min_dim.x
				|| pad.y + i.y >= f->max.y || pad.x + i.x >= f->max.x
				|| (b[pad.y + i.y][pad.x + i.x] >> 1)
				|| (b[i.y + pad.y][i.x + pad.x] && ++connected > 1))
					return (0);
				if (!b[i.y + pad.y][i.x + pad.x])
					score += scoring(f, b, pad.y + i.y, pad.x + i.x);
			}
		}
	}
	return (connected ? score : 0);
}

int		put_piece(t_filler *f, BOARD, PIECE, t_point **points)
{
	t_index	i;
	int		score;

	score = 0;
	i.y = 0;
	while (i.y < f->max.y)
	{
		i.x = 0;
		while (i.x < f->max.x)
		{
			if ((score = is_valid_position(f, b, p, i)))
				add_point(points, i, score);
			++i.x;
		}
		++i.y;
	}
	return (1);
}

void	free_saved_positions(t_point **points)
{
	t_point	*lst;
	t_point	*tmp;

	lst = *points;
	while (lst)
	{
		tmp = lst;
		free(tmp);
		lst = lst->next;
	}
}
