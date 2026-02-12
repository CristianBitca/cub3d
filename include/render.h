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

#define TILE 32

//render

int	render(t_game *game);
void put_pixel(t_img *img, int x, int y, int color);

//debug_mode

int	debug_mode(t_game *game);

#endif
