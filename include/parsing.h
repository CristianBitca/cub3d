/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:33:10 by cbitca            #+#    #+#             */
/*   Updated: 2025/12/10 14:33:11 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

// Include

#include "cub3d.h"

// Error message

#define FILE_OPEN	"Failed to open the file.\n"
#define	XPM_FILE	"Failed to open the file %s, to load %s\n"
#define	EXTRA_ELEM	"Unused element %s located in %s\n"

// Function

// parse

int	parse(t_game *game, char *path);

// parse_elem

int	check_elem(char	*line);
void	parse_rgb(int *p_elem, char **elem);
void	parse_elem(t_game *game, char *line);
void	parse_img(void *mlx, void **elem, char **path);

// parse_map
#endif
