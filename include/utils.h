/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:32:40 by cbitca            #+#    #+#             */
/*   Updated: 2025/12/10 14:32:41 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

// Include

#include "cub3d.h"

#define MAP_FORMAT	".cub"
#define IMG_FORMAT	".xpm"

// Error message

#define ERR			"Error\n"
#define ARG_1		"Missing the argument, PATH to the map.\n"
#define ARG_2		"The argumtent is not type .cub.\n"
#define ARG_3		"Moo many arguments.\n"
#define MLX			"Unable to initialize MLX\n"
#define MAP			"Unable to allocate memory for map\n"
#define IMG_EXT		"Image %s has from incompatible format(expeced .xpm)\n"
#define RGB			"Element %s has wrong RGB value(%s)\n"
#define MAP_ENTRY	"Too many starting points in the map\n"
#define MAP_CHAR	"Unexpected character in the map\n"

// Functions

// error
int	check_arg(int argc, char **argv);
int	check_assets(t_map *map);

// exit
void	error();
int	exit_error(char *err);
void	free_content(char **content);
void	parse_error(t_game *game, char *line, int fd);

#endif