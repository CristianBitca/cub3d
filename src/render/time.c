/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 21:51:57 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/23 21:51:58 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"
#include "parsing.h"
#include <sys/wait.h>

// FUNCTION: get_time
// ----------------------------
// Retrieves the current system time in seconds with microsecond precision.
//
// PARAMETERS
// None.
//
// RETURN VALUE
// Returns the current time as a double (seconds + microseconds fraction).
double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

// FUNCTION: delta_time
// ----------------------------
// Calculates the time difference between the current frame and the previous frame.
// Useful for frame-independent movement and rotation scaling.
//
// PARAMETERS
// game : Pointer to the game structure containing the current and previous frame times.
//
// RETURN VALUE
// Returns the time difference (delta) in seconds as a double.
double	delta_time(t_game *game)
{
	return (game->time - game->old_time);
}
