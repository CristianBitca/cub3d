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

#define TILE 58
#define	COLLISION_BUF 0.1

//render

void	clear_img(t_game *game);
void	render_debug(t_game *game);
void	render_texture(t_game *game, t_ray *ray, int x);
void	render_3d(t_game *game);
int		render(t_game *game);

//debug_mode

void	debug_cell(t_game *game, int x, int y, int color);
void	debug_map(t_game *game);
void	debug_player(t_game *game);
void	debug_ray(t_game *game);

//draw

t_img	*texture_side(t_game *game, t_ray *ray);
void 	calc_texture_x(t_draw *draw, t_ray *ray, t_player *player, int tex_width);
void	draw_ceiling(t_game *game, t_draw *draw, int x, int color);
void	draw_wall(t_game *game, t_draw *draw, int x, t_img *img);
void	draw_floor(t_game *game, t_draw *draw, int x, int color);

//utility

void	draw_line(t_img *img, t_line *line);
void	draw_player(t_img *img, t_player *player);
void 	put_pixel(t_img *img, int x, int y, int color);
int		get_texture_color(t_img *tex, int x, int y);

//key

int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	handle_move(t_game *game);

//move

void	calc_move(t_game *game, double *new_x, double *new_y, t_key_code key);
void	move(t_game *game, t_key_code key);

//rotate

void 	rotate_left(t_game *game);
void 	rotate_right(t_game *game);

//raycasting

void	calculate_step_and_side_dist(t_ray *ray, t_player *player);
void	dda(t_ray *ray, char **map);
void 	calculate_perp_dist(t_ray *ray, t_player *player);

//time

double	get_time(void);
double	delta_time(t_game *game);

#endif
