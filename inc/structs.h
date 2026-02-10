/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:26:57 by mtice             #+#    #+#             */
/*   Updated: 2026/01/12 17:30:40 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_area			t_area;
typedef enum e_spawn		t_spawn;
typedef struct s_data		t_data;
typedef struct s_img		t_img;
typedef struct s_player		t_player;
typedef struct s_room		t_room;
typedef struct s_raycast	t_raycast;
typedef struct s_txt		t_txt;

//------------------------------TYPE OF MAP AREAS------------------------------
typedef enum e_area
{
	UNDEFINED,
	WALL,
	OPEN,
}			t_area;

//------------------------------PLAYER SPAWN POSITIONS-------------------------
typedef enum e_spawn
{
	NOPLAYER = 0,
	NORTH = 78,
	EAST = 69,
	SOUTH = 83,
	WEST = 87
}			t_spawn;

//-----------------------------TEXTURES----------------------------------------
typedef struct s_txt
{
	unsigned int	**txt_address;
	double			step;
	double			pos;
	int				x;
	int				y;
	t_spawn			index;
}				t_txt;

//--------------------------POINTER TO ALL TYPES OF DATA-----------------------
typedef struct s_data
{
	char		**map;
	int			height;
	int			width;
	int			map_start;
	t_spawn		player;
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	int			floor;
	int			ceiling;
	t_room		*game;
	t_txt		*txt;
}				t_data;

//-------------------------------STRUCTURE FOR IMAGE---------------------------
typedef struct s_img
{
	void		*img;
	void		*img_tmp;
	char		*addr;
	char		*addr_tmp;
	int			bpp;
	int			len;
	int			endian;
}				t_img;

//----------------------------PLAYER MOVEMENT----------------------------------
typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			rotate;
}				t_player;

//--------------------------GAME STRUCTURE-------------------------------------
typedef struct s_room
{
	void		*mlx;
	void		*win;
	char		**map;
	int			render_in_progress;
	t_img		img;
	t_player	player;
	t_data		*all;
}				t_room;

//---------------------------STRUCTURE FOR RAYCASTING--------------------------
typedef struct s_raycast
{
	double		camera_x;
	double		raydir_x;
	double		raydir_y;
	double		delta_x;
	double		delta_y;
	double		side_x;
	double		side_y;
	double		dist;
	double		wall_x;
	int			map_x;
	int			map_y;
	int			hit;
	int			side;
	int			line_h;
	int			draw_start;
	int			draw_end;
	int			step_x;
	int			step_y;
}				t_raycast;

#endif
