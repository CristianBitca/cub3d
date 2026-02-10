/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:24:18 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/08 18:24:19 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"
#include "parsing.h"

void put_pixel(t_img *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

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
				render_cell(game, x * TILE, y * TILE, game->asset->F);
			else if (game->map[y][x] == '0')
				render_cell(game, x * TILE, y * TILE, game->asset->C);
			x++;
		}
		y++;
	}
}

void	render_player(t_game *game)
{
	int	c;
	int	px;
	int	py;
	int	x;
	int	y;
	char	**elem;

	px = game->player->x * TILE;
	py = game->player->y * TILE;
	elem = ft_calloc(2 + 1, sizeof(char *));
	elem[0] = NULL;
	elem[1] = "230,18,18";
	parse_rgb(&c, elem);
	y = -3;
	while(y <= 3)
	{
		x = -3;
		while (x <= 3)
		{
			put_pixel(game->img, px + x, py + y, c);
			x++;
		}
		y++;
	}
}

void	render_ray(t_game *game)
{
	int	i;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;

	i = 0;
	while (i < 64)
	{
		camera_x = 2 * i/64.0 - 1;
		ray_dir_x = game->player->dir_x + game->player->plane_x * camera_x;
		ray_dir_y = game->player->dir_y + game->player->plane_y * camera_x;
	}
}

int	render(t_game *game)
{
	// ft_memset(game->img->addr, 0, 1080 * game->img->line_len);
	render_map(game);
	render_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	// render_ray(game);
	return (EXIT_SUCCESS);
}