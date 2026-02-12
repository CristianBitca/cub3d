/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:21:12 by cbitca            #+#    #+#             */
/*   Updated: 2025/12/08 18:23:57 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"
#include "utils.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (check_arg(argc, argv))
		return (EXIT_FAILURE);
	game = ft_calloc(sizeof(t_game), 1);
	if (!game)
		return (EXIT_FAILURE);
	init_game(game, argv[1]);
	exit_game(game);
	return (EXIT_SUCCESS);
}
