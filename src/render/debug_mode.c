/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:25:37 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/11 15:25:38 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"
#include "parsing.h"

void	render_cell(t_game *game, int x, int y, int color)
{
	int	c_x;
	int	c_y;

	c_y = 0;
	while (c_y < TILE)
	{
		c_x = 0;
		while (c_x < TILE)
		{
			put_pixel(game->img, x + c_x, y + c_y, color);
			c_x++;
		}
		c_y++;
	}
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				render_cell(game, x * TILE, y * TILE, WHITE);
			else if (game->map[y][x] == '0')
				render_cell(game, x * TILE, y * TILE, BLACK);
			x++;
		}
		y++;
	}
}

void	render_player(t_game *game)
{
	int	px;
	int	py;
	int	end_x;
	int	end_y;
	t_line	*line;

	px = game->player->x * TILE;
	py = game->player->y * TILE;
	end_x = px + game->player->dir_x * 20;
	end_y = py + game->player->dir_y * 20;
	draw_player(game->img, game->player);
	line = init_line(game->player, end_x, end_y, RED);
	draw_line(game->img, line);
}

void	render_ray(t_game *game)
{
	int		i;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;

	i = 0;
	while (i < 64)
	{
		camera_x = 2 * i / 64.0 - 1;
		ray_dir_x = game->player->dir_x + game->player->plane_x * camera_x;
		ray_dir_y = game->player->dir_y + game->player->plane_y * camera_x;
	}
}

int	debug_mode(t_game *game)
{	
	render_map(game);
	render_player(game);
	// render_ray(game);
	return (EXIT_SUCCESS);
}
