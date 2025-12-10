/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:40:02 by cbitca            #+#    #+#             */
/*   Updated: 2025/12/10 17:40:03 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "utils.h"

int	parse(t_game *game, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd <= 0)
		return (print_error(FILE_OPEN));
	return (EXIT_SUCCESS);
	(void)game;
}
