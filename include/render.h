/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:24:01 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/08 18:24:02 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
#define RENDER_H

#include "cub3d.h"

#define TILE 48

//render

int	render(t_game *game);
void put_pixel(t_img *img, int x, int y, int color);

//debug_mode

int	debug_mode(t_game *game);

//utility

void	draw_line(t_img *img, t_line *line);
void	draw_player(t_img *img, t_player *player);
double	delta_time(t_game *game);
double get_time(void);
void	dda(t_ray *ray, char **map);

//key

int	key_press(int keycode, t_game *game);
int	key_release(int keycode, t_game *game);
void	handle_move(t_game *game);

//move

void	move(t_game *game, t_key_code key);
void rotate_left(t_game *game);
void rotate_right(t_game *game);

#endif
