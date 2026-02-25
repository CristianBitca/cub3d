/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamano <tyamano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:24:18 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/19 20:06:17 by tyamano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"
#include "parsing.h"

void	clear_img(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			put_pixel(game->img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	render_debug(t_game *game)
{
	debug_map(game);
	debug_ray(game);
	debug_player(game);
}

void	render_texture(t_game *game, t_ray *ray, int x)
{
	t_draw	draw;

	init_draw(&draw, ray, game);
	calc_texture_x(&draw, ray, game->player, draw.img->width);
	draw_ceiling(game, &draw, x, game->asset->C);
	draw_wall(game, &draw, x, draw.img);
	draw_floor(game, &draw, x, game->asset->F);
}

void	render_3d(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < game->screen_width)
	{
		init_ray(&ray, game, game->player, x);
		render_texture(game, &ray, x);
		x++;
	}
}

int	render(t_game *game)
{
	game->old_time = game->time;
	game->time = get_time();
	handle_move(game);
	clear_img(game);
	if (game->debug_mode)
		render_debug(game);
	else
		render_3d(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	return (EXIT_SUCCESS);
}
