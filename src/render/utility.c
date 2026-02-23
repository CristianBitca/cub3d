/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 21:36:11 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/12 21:36:12 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"
#include "parsing.h"
#include <sys/wait.h>

void	draw_line(t_img *img, t_line *line)
{
	put_pixel(img, line->x0, line->y0, line->color);
	if (line->x0 == line->x1 && line->y0 == line->y1)
		return ;
	line->err2 = line->err * 2;
	if (line->err2 > -line->dy)
	{
		line->err -= line->dy;
		line->x0 += line->sx;
	}
	if (line->err2 < line->dx)
	{
		line->err += line->dx;
		line->y0 += line->sy;
	}
	draw_line(img, line);
}

void	draw_player(t_img *img, t_player *player)
{
	int	x;
	int	y;
	int	cx;
	int	cy;

	cx = player->x * TILE;
	cy = player->y * TILE;
	y = -5;
	while (y <= 5)
	{
		x = -5;
		while (x <= 5)
		{
			if (x * x + y * y <= 25)
				put_pixel(img, cx + x, cy + y, RED);
			x++;
		}
		y++;
	}
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_texture_color(t_img *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(int *)pixel);
}
