/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:26:57 by mtice             #+#    #+#             */
/*   Updated: 2025/11/19 11:00:05 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_data t_data;
typedef struct s_three t_three;
typedef struct s_two t_two;
typedef struct s_libx t_libx;

typedef struct s_data
{
	t_three	**map3d;
	t_two	**map2d;
	t_libx	*libx;
}				t_data;

typedef struct s_three
{
	int	x;
	int	y;
	int	z;
	int	colour;
}				t_three;

typedef struct s_two
{
	float	x;
	float	y;
	int		colour;
}				t_two;

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
