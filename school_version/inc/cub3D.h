/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:23:39 by mtice             #+#    #+#             */
/*   Updated: 2025/12/13 14:03:38 by mtice            ###   ########.fr       */
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
int				parsing(t_data *all, char *map_name);

//file_checks.c
int				file_checks(t_data *all, char *map_name);
int				file_invalid_name(char *file_name, char *req_extension);
int				file_no_exist(char *file_name);

//map_checks.c
int				map_checks(t_data *all, char *map_name);

//map_reformats.c
int				map_reformats(t_data *all);
int				reformat_raw_map(t_data *all);

//---------------------------FUNCTIONS: EXECUTION------------------------------
//render.c
void			render(t_data *all);

//sky_and_floor.c
void			draw_sky(t_data *all);
void			draw_floor(t_data *all);

//transform.c
void			transform_map2d(t_data *all);

//position.c
void	position_image(t_data *all);

//hooks.c
int	on_key_down(int keycode, t_data *all);

//--------------------------FUNCTIONS: UTILS-----------------------------------
//init_utils.c
void			init_t_data(t_data *all);

//parsing_utils.c
bool			accepted(char c);
bool			is_wall(char c);
bool			is_open(char c);
void			safe_j(t_data *all, int *j, int i);

//file_checks_utils.c
bool			record_col(t_data *all, char *line, char *p_line, int fd);
bool			record_text(t_data *all, char *line, char *p_line, int fd);
int				invalid_txt(char *file_name);
int				invalid_col(t_data *all);

//draw.c
void			draw(t_data *all);
void			my_mlx_pixel_put(t_data *all, int x, int y, int colour);

//render_utils.c
char			ft_itoh(int n);
unsigned int	rgb_to_hex(unsigned char r, unsigned char g, unsigned char b);
unsigned int	ft_atoh(const char *nptr);
//
//math_utils.c
int				get_max(int a, int b);

//free_utils.c
void			free_all(t_data *all);
void			free_double_char(char **arr);

//ft_exit.c
void			ft_exit(t_data *all, char *err_msg);

#endif
