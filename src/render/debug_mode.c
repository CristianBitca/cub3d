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

// FUNCTION: debug_cell
// ----------------------------
// Draws a single map cell as a filled square on the screen for debugging purposes.
// Fills a TILE-sized area at the given screen coordinates with the specified color.
//
// PARAMETERS
// game  : Pointer to the game structure containing the image buffer.
// x     : Horizontal screen coordinate where the cell starts.
// y     : Vertical screen coordinate where the cell starts.
// color : Color value to fill the cell.
//
// RETURN VALUE
// None.
void	debug_cell(t_game *game, int x, int y, int color)
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

// FUNCTION: debug_map
// ----------------------------
// Renders a 2D representation of the map for debugging purposes. Draws each map
// cell with a color based on its type to visualize walls and empty spaces.
//
// PARAMETERS
// game : Pointer to the game structure containing the map array and image buffer.
//
// RETURN VALUE
// None.
void	debug_map(t_game *game)
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
				debug_cell(game, x * TILE, y * TILE, WHITE);
			else if (game->map[y][x] == '0')
				debug_cell(game, x * TILE, y * TILE, BLACK);
			x++;
		}
		y++;
	}
}

// FUNCTION: debug_player
// ----------------------------
// Draws the player position and facing direction on the screen for debugging purposes.
// Renders a player marker and a short line indicating the direction the player is facing.
//
// PARAMETERS
// game : Pointer to the game structure containing the player structure and image buffer.
//
// RETURN VALUE
// None.
void	debug_player(t_game *game)
{
	t_line	line;

	line.x0 = game->player->x * TILE;
	line.y0 = game->player->y * TILE;
	line.x1 = line.x0 + game->player->dir_x * 5;
	line.y1 = line.y0 + game->player->dir_y * 5;
	draw_player(game->img, game->player);
	init_line(&line, RED);
	draw_line(game->img, &line);
}

// FUNCTION: debug_ray
// ----------------------------
// Draws raycasting lines on the screen for debugging purposes. Casts rays at
// regular intervals across the screen and renders their paths to visualize
// ray directions and wall intersections.
//
// PARAMETERS
// game : Pointer to the game structure containing player position, screen dimensions, and image buffer.
//
// RETURN VALUE
// None.
void	debug_ray(t_game *game)
{
	t_ray	ray;
	t_line	line;
	int		x;

	x = 0;
	while (x < game->screen_width)
	{
		init_ray(&ray, game, game->player, x);
		init_ray_line(&line, &ray, game->player);
		draw_line(game->img, &line);
		x += 30;
	}
}
