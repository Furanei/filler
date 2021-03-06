/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 18:30:45 by mbriffau          #+#    #+#             */
/*   Updated: 2017/09/30 14:08:38 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int			ft_count_word(const char *s, char c)
{
	int		i;
	int		nword;

	i = 0;
	nword = 0;
	while (s[i++])
		if ((s[i - 1] == c || nword == 0) && s[i] != c && s[i] != '\0')
			nword++;
	return (nword);
}
