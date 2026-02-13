/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 21:56:03 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/12 21:56:04 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "render.h"
#include "utils.h"

t_line	*init_line(t_player *player, int x1, int y1, int color)
{
	t_line	*line;

	line = ft_calloc(sizeof(t_line), 1);
	if (!line)
		return (0);
	line->x0 = player->x * TILE;
	line->y0 = player->y * TILE;
	line->x1 = x1;
	line->y1 = y1;
	line->dx = abs(x1 - line->x0);
	line->dy = abs(y1 - line->y0);
	line->sx = (line->x0 < x1) ? 1 : -1;
	line->sy = (line->y0 < y1) ? 1 : -1;
	line->err = line->dx - line->dy;
	line->color = color;
	return (line);
}
