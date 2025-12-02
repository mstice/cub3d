/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:26:57 by mtice             #+#    #+#             */
/*   Updated: 2025/12/02 17:35:31 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_area t_area;
typedef struct s_data t_data;
typedef struct s_three t_three;
typedef struct s_two t_two;
typedef struct s_libx t_libx;

//------------------------------TYPE OF MAP AREAS------------------------------
typedef enum e_area
{
	UNDEFINED,
	WALL,
	OPEN,
}			t_area;

//--------------------------POINTER TO ALL TYPES OF DATA-----------------------
typedef struct s_data
{
	char	**raw_map;
	t_three	**map3d;
	t_two	**map2d;
	int		height;
	int		width;
	t_libx	*libx;
}				t_data;

//-------------------------INITIAL 3D COORDINATES------------------------------
//After parsing the map, x and y coordiates are collected
//z coordinates represent the height of the walls
//colour is the colour of the area the coordinate represents (floor, sky, wall)
typedef struct s_three
{
	int	x;
	int	y;
	int	z;
	int	colour;
}				t_three;

//-------------------------2D COORDINATES--------------------------------------
//after taking 3d coordinates and performing transformations
//gives the final x and y coordinates that are going to be used to render
typedef struct s_two
{
	float	x;
	float	y;
	int		colour;
}				t_two;

//----------------------------MINILIBX-----------------------------------------
//containes necessary informationi to render the window, images and plot pixels
typedef struct s_libx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img1;
	void	*img2;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_libx;


#endif
