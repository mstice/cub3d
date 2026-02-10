/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:55:53 by mtice             #+#    #+#             */
/*   Updated: 2026/01/30 15:49:06 by ombatkam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
//-----------------------------------------------------------------------------
//adjusts the pixel colour calculation depending on Linux or macOS
//Linux: BGRA, endian 0
//MacOS: ARGB, endian 1
static unsigned int	get_pixel_colour(t_img *tmp, int x, int y)
{
	unsigned char	*pixel;
	unsigned int	colour;

	pixel = (unsigned char *)tmp->addr + y * tmp->len + x * (tmp->bpp / 8);
	if (tmp->endian == 0)
		colour = (pixel[2] << 16) | (pixel[1] << 8) | (pixel[0]);
	else
		colour = (pixel[1] << 16) | (pixel[2] << 8) | (pixel[3]);
	return (colour);
}

//-----------------------------------------------------------------------------
unsigned int	*get_txt_address(t_room *game, char *txt_path)
{
	t_img			tmp;
	unsigned int	*buffer;
	int				x;
	int				y;
	int				size;

	size = 64;
	tmp.img = mlx_xpm_file_to_image(game->mlx, txt_path, &size, &size);
	if (!tmp.img)
		ft_exit(game->all, ERR_MALLOC, 0);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.len, &tmp.endian);
	buffer = ft_calloc(1, sizeof * buffer * TXT_SIZE * TXT_SIZE);
	if (!buffer)
		ft_exit(game->all, ERR_MALLOC, 0);
	y = -1;
	while (++y < TXT_SIZE)
	{
		x = -1;
		while (++x < TXT_SIZE)
			buffer[y * TXT_SIZE + x] = get_pixel_colour(&tmp, x, y);
	}
	mlx_destroy_image(game->mlx, tmp.img);
	return (buffer);
}

//-----------------------------------------------------------------------------
static void	find_texture(t_raycast *ray, t_txt *txt)
{
	const int	north = 0;
	const int	east = 1;
	const int	south = 2;
	const int	west = 3;

	if (ray->side == 0)
	{
		if (ray->raydir_x < 0)
			txt->index = west;
		else
			txt->index = east;
	}
	else
	{
		if (ray->raydir_y > 0)
			txt->index = south;
		else
			txt->index = north;
	}
}

//-----------------------------------------------------------------------------
void	draw_walls(t_room *game, t_raycast *ray, t_txt *txt, int x)
{
	int		y;
	int		colour;

	find_texture(ray, txt);
	txt->x = (int)(ray->wall_x * TXT_SIZE);
	if ((ray->side == 0 && ray->raydir_x < 0)
		|| (ray->side == 1 && ray->raydir_y > 0))
		txt->x = TXT_SIZE - txt->x - 1;
	txt->step = 1.0 * TXT_SIZE / ray->line_h;
	txt->pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_h / 2) * txt->step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		txt->y = (int)txt->pos & (TXT_SIZE - 1);
		txt->pos += txt->step;
		colour = txt->txt_address[txt->index][TXT_SIZE * txt->y + txt->x];
		if (ray->side == 0)
			colour = (colour >> 1) & 0x7F7F7F;
		put_pixel(&game->img, x, y, colour);
		y++;
	}
}
