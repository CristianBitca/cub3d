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

#define FORMAT ".cub"

// Error message

#define ERR "Error\n"
#define ARG_1 "Missing the argument, PATH to the map.\n"
#define ARG_2 "The argumtent is not type .cub.\n"
#define ARG_3 "Moo many arguments.\n"

// Functions

// error
int	check_arg(int argc, char **argv);

// exit
int	print_error(char *err);

#endif