/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:23:39 by mtice             #+#    #+#             */
/*   Updated: 2025/11/19 11:00:06 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h> //open
# include <unistd.h> //close //read //write //exit
# include <stdio.h> //printf //perror
# include <stdlib.h> //malloc //free
# include <string.h> //strerror
# include <sys/time.h> //gettimeofday
# include <math.h>
# include <errno.h>
# include <limits.h>

# include "macros.h"
# include "structs.h"
# include "../minilibx-linux/mlx.h"
# include "../my_libft/libft/inc/libft.h"
# include "../my_libft/ft_printf/inc/ft_printf_bonus.h"
# include "../my_libft/gnl/inc/get_next_line_bonus.h"


//main

//render.c
void	render(t_libx *libx);

#endif
