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

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

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

int	render(t_game *game)
{
	game->old_time = game->time;
	game->time = get_time();
	clear_img(game);
	handle_move(game);
	if (game->debug_mode)
		debug_mode(game);
	else
		clear_img(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	return (EXIT_SUCCESS);
}
