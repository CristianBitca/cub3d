/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 18:51:42 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/23 18:51:43 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"
#include "parsing.h"

t_img	*texture_side(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (game->asset->EA);
		else
			return (game->asset->WE);
	}
	else
	{
		if (ray->dir_y > 0)
			return (game->asset->SO);
		else
			return (game->asset->NO);
	}
}

void	calculate_texture_x(t_draw_info *draw, t_ray *ray, t_player *player, int tex_width)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = player->y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = player->x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	draw->tex_x = (int)(wall_x * (double)tex_width);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
		draw->tex_x = tex_width - draw->tex_x - 1;
}

void	draw_ceiling(t_game *game, t_draw_info *draw, int x, int color)
{
	int	y;

	y = 0;
	while (y < draw->draw_start)
	{
		put_pixel(game->img, x, y, color);
		y++;
	}
}

void	draw_wall(t_game *game, t_draw_info *draw, int x, t_img *img)
{
	int	y;
	int	tex_y;
	int	color;
	int	d;

	y = draw->draw_start;
	while (y < draw->draw_end)
	{
		d = y * 256 - game->screen_height * 128 + draw->line_height * 128;
		tex_y = ((d * img->height) / draw->line_height) / 256;
		color = get_texture_color(img, draw->tex_x, tex_y);
		put_pixel(game->img, x, y, color);
		y++;
	}
}

void	draw_floor(t_game *game, t_draw_info *draw, int x, int color)
{
	int	y;

	y = draw->draw_end;
	while (y < game->screen_height)
	{
		put_pixel(game->img, x, y, color);
		y++;
	}
}
