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

#define FILE_OPEN "Failed to open the file.\n"

// Function

// parse

int	parse(t_game *game, char *path);

#endif
