/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:23:39 by mtice             #+#    #+#             */
/*   Updated: 2026/01/12 17:29:32 by mtice            ###   ########.fr       */
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
# include <X11/keysym.h>
# include <X11/X.h>

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
void			record_map_attributes(t_data *all, int fd, char *map_start);
int				map_checks(t_data *all, char *map_name);

//map_reformats.c
void			create_map(t_data *all, char *map_name);
int				reformat_map(t_data *all);

//---------------------------FUNCTIONS: EXECUTION------------------------------
//draw_scene.c
void			draw_scene(t_room *game);

//hooks.c
int				on_key_down(int keycode, t_room *game);
int				close_game(t_room *game);

//player.c
void			set_direction_south_north(t_spawn direction, t_player *player);
void			set_direction_east_west(t_spawn direction, t_player *player);
void			set_player_pos(t_data *all, t_player *player);

//textures.c
unsigned int	*get_txt_address(t_room *game, char *txt_path);
void			draw_walls(t_room *game, t_raycast *ray, t_txt *txt, int x);

//--------------------------FUNCTIONS: UTILS-----------------------------------
//init_t_data.c
void			init_t_data(t_data *all);

//init_game.c
void			init_game(t_data *all, t_room *game);

//parsing_utils.c
bool			accepted(char c);
bool			is_wall(char c);
bool			is_open(char c);
int				safe_j(t_data *all, int *j, int i);

//file_checks_utils.c
bool			record_col(t_data *all, char *line, int fd);
bool			record_txt(t_data *all, char *line, int fd);
int				invalid_txt(t_data *all, char *file_name, int fd);
int				invalid_col(t_data *all, int fd);

//colour.c
int				get_colour_values(char *colour);

//math_utils.c
int				get_max(int a, int b);

//free_utils.c
void			free_all(t_data *all);
void			free_double_char(char **arr);

//ft_exit.c
void			ft_exit(t_data *all, char *err_msg, int fd);

//scene_util.c
void			put_pixel(t_img *img, int x, int y, int color);
void			draw_all(t_room *game, t_raycast *ray, int x);

//movements.c
void			update_new_pos(t_player new, t_player *player, char **map);
void			move_forward(t_player *player, char **map);
void			move_back(t_player *player, char **map);
void			move_right(t_player *player, char **map);
void			move_left(t_player *player, char **map);

//rotation.c
void			rotate_right(t_player *player);
void			rotate_left(t_player *player);
#endif
