/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:23:39 by mtice             #+#    #+#             */
/*   Updated: 2025/12/02 13:21:07 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//--------------------------------INCLUDED LIBRARIES---------------------------
# include <fcntl.h> //open
# include <unistd.h> //close //read //write //exit
# include <stdio.h> //printf //perror
# include <stdlib.h> //malloc //free
# include <string.h> //strerror
# include <sys/time.h> //gettimeofday
# include <math.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>

# include "macros.h"
# include "structs.h"
# include "../minilibx-linux/mlx.h"
# include "../my_libft/libft/inc/libft.h"
# include "../my_libft/ft_printf/inc/ft_printf_bonus.h"
# include "../my_libft/gnl/inc/get_next_line_bonus.h"


//---------------------------FUNCTIONS: PARSING--------------------------------

//parsing.c
int	parsing(t_data *all, char *map_name);

//map_checks.c
int	map_checks(t_data *all, char *map_name);

//---------------------------FUNCTIONS: EXECUTION------------------------------
//render.c
void	render(t_libx *libx);

//--------------------------FUNCTIONS: UTILS-----------------------------------
//init_utils.c
void	init_t_data(t_data *all);

//ft_exit.c
void	ft_exit(char *err_msg, int exit_code);

#endif
