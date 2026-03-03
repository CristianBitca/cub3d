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

// FUNCTION: clear_img
// ----------------------------
// Clears the image buffer by filling the entire screen with a black color.
// This is typically called before rendering a new frame.
//
// PARAMETERS
// game : Pointer to the game structure containing the image buffer and screen dimensions.
//
// RETURN VALUE
// None.
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

// FUNCTION: render_debug
// ----------------------------
// Renders the debug view of the game. Displays the map layout, raycasting lines,
// and player position to help visualize and debug the internal state.
//
// PARAMETERS
// game : Pointer to the game structure containing the map, player, and raycasting data.
//
// RETURN VALUE
// None.
void	render_debug(t_game *game)
{
	debug_map(game);
	debug_ray(game);
	debug_player(game);
}

// FUNCTION: render_texture
// ----------------------------
// Renders a vertical stripe of the screen using the raycasting result. Initializes
// drawing parameters, computes the texture X coordinate, and draws the ceiling,
// wall texture, and floor for the given screen column.
//
// PARAMETERS
// game : Pointer to the game structure containing image buffer, assets, and player data.
// ray  : Pointer to the ray structure containing direction, hit side, and distance info.
// x    : Horizontal screen coordinate (column) being drawn.
//
// RETURN VALUE
// None.
void	render_texture(t_game *game, t_ray *ray, int x)
{
	t_draw	draw;

	init_draw(&draw, ray, game);
	calc_texture_x(&draw, ray, game->player, draw.img->width);
	draw_ceiling(game, &draw, x, game->asset->C);
	draw_wall(game, &draw, x, draw.img);
	draw_floor(game, &draw, x, game->asset->F);
}

// FUNCTION: render_3d
// ----------------------------
// Renders the 3D scene using raycasting. Casts a ray for each vertical stripe of
// the screen, initializes ray parameters, and draws the corresponding textured wall.
//
// RETURN VALUE
//	None.
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

// FUNCTION: render_3d
// ----------------------------
// Renders the 3D scene using raycasting. Casts a ray for each vertical stripe of
// the screen, initializes ray parameters, and draws the corresponding textured wall.
//
// PARAMETERS
// game : Pointer to the game structure containing screen dimensions, assets, player, and image buffer.
//
// RETURN VALUE
// None.
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
