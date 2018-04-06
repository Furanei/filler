/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 19:02:51 by mbriffau          #+#    #+#             */
/*   Updated: 2017/10/15 06:41:22 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

static void		check_max_area(t_filler *f, int map[f->max.y][f->max.x])
{
	t_index	i;

	i.y = f->max.y;
	f->max_area.y = -1;
	while (--i.y >= 0 && f->max_area.y == -1)
	{
		i.x = f->max.x;
		while (--i.x >= 0 && f->max_area.y == -1)
		{
			if (map[i.y][i.x])
				f->max_area.y = i.y;
		}
	}
	f->max_area.x = -1;
	i.x = f->max.x;
	while (--i.x >= 0 && f->max_area.x == -1)
	{
		i.y = f->max.y;
		while (--i.y >= 0 && f->max_area.x == -1)
		{
			if (map[i.y][i.x])
				f->max_area.x = i.x;
		}
	}
}

static t_index	check_min_area(t_filler *f, int map[f->max.y][f->max.x])
{
	t_index	i;
	t_index	min;

	i.y = -1;
	min.y = -1;
	while (++i.y < f->max.y && min.y == -1)
	{
		i.x = -1;
		while (++i.x < f->max.x && min.y == -1)
			if (map[i.y][i.x])
				min.y = i.y;
	}
	i.x = -1;
	min.x = -1;
	while (++i.x < f->max.x && min.x == -1)
	{
		i.y = -1;
		while (++i.y < f->max.y && min.x == -1)
			if (map[i.y][i.x])
				min.x = i.x;
	}
	return (min);
}

static void		map_atoi(t_filler *f, char *s, int y,
	int map[f->max.y][f->max.x])
{
	int	x;

	x = -1;
	while (s[++x])
		if (s[x] == 'O')
			map[y][x] = PLY;
		else if (s[x] == 'X')
			map[y][x] = (PLY & 2) >> 1 | (PLY & 1) << 1;
		else
			map[y][x] = 0;
}

/*
** boucle principale
*/

static void		filler_loop(t_filler *f)
{
	t_index	i;
	char	*line;
	int		map[f->max.y][f->max.x];

	NEXT_LINE;
	i.y = -1;
	while (++i.y < f->max.y)
	{
		if (get_next_line(0, &line) == -1)
			ft_error("GNL error");
		map_atoi(f, line + 4, i.y, map);
	}
	f->min_area = check_min_area(f, map);
	check_max_area(f, map);
	NEXT_LINE;
	f->piece_dim = (t_index) {.y = 0, .x = 0};
	filler_atoi(&f->piece_dim, line + 6);
	get_piece_dimension(f, line, map);
	NEXT_LINE;
	++f->turn;
}

/*
** f->cpu = (f->player >> 1) equivalent to f->cpu = (f->player == 2)
** 50 = 11 0010 --> >> 1 --> (1 1001 & 1)
** first get_next_line is for //$$$ exec p[1-2]
** second one is for //Plateau 14 17:
*/

int				main(void)
{
	t_filler	f;
	char		*line;

	get_next_line(0, &line);
	if (!line[10] || (line[10] != '1' && line[10] != '2'))
		ft_error("error about player position");
	f.player = line[10] - '0';
	f.ply_name = &line[14];
	f.cpu = (f.player & 2) >> 1 | (f.player & 1) << 1;
	get_next_line(0, &line);
	f.max = (t_index) {.y = 0, .x = 0};
	filler_atoi(&f.max, line + 8);
	f.turn = 0;
	f.goal = 0;
	f.ply_score = 0;
	f.cpu_score = 0;
	while (1)
		filler_loop(&f);
	return (0);
}
