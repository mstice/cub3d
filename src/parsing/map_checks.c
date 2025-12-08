/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:26:22 by mtice             #+#    #+#             */
/*   Updated: 2025/12/08 15:50:23 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//TODO: free_all() is not well equipped to deal with exiting this function
static int	create_raw_map(t_data *all, char *map_name)
{
	int		fd;
	int		j;
	char	*line;

	fd = file_no_exist(all, map_name);
	all->raw_map = ft_calloc(sizeof(char *), all->height + 1);
	if (!all->raw_map)
		close(fd), ft_exit(all, ERR_MALLOC);
	while (all->map_start-- > 0)
		line = get_next_line(fd), free(line);
	j = -1;
	while (++j < all->height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		all->raw_map[j] = ft_strtrim(line, "\n");
		if (!(all->raw_map[j])|| !(*all->raw_map[j]))
		{
			free(all->raw_map[j]), free(line);
			break ;
		}
		all->width = get_max(all->width, ft_strlen(all->raw_map[j]));
		free(line);
	}
	all->raw_map[j] = NULL;
	close(fd);
	return (SUCCESS);
}
//-----------------------------------------------------------------------------
//checks if any elements are out of order
//e.g. no player, too many players, and non-accepted elements
static int	map_err_elements(t_data *all)
{
	int		j;
	int		i;

	j = 0;
	while (all->raw_map[j] != NULL)
	{
		i = 0;
		while (all->raw_map[j][i] != '\0')
		{
			if (all->raw_map[j][i] == 'N' || all->raw_map[j][i] == 'E'
				|| all->raw_map[j][i] == 'S' || all->raw_map[j][i] == 'W')
			{
				if (all->player != NOPLAYER)
					ft_exit(all, ERR_POS_DUP);
				all->player = all->raw_map[j][i];
			}
			if (!accepted(all->raw_map[j][i]))
				ft_exit(all, ERR_INV_EL);
			i++;
		}
		j++;
	}
	if (all->player == NOPLAYER)
		ft_exit(all, ERR_NO_POS);
	return (SUCCESS);
}

//-----------------------------------------------------------------------------
//checks if open areas are surrounded by walls from a horizontal pov
static int	map_err_walls_horizontal(t_data *all)
{
	t_area	area;
	int		j;
	int		i;

	area = UNDEFINED;
	j = 0;
	while (all->raw_map[j] != NULL)
	{
		i = 0;
		area = UNDEFINED;
		while (all->raw_map[j][i] != '\0')
		{
			if (is_wall(all->raw_map[j][i]))
				area = WALL;
			else if (is_open(all->raw_map[j][i]) && area != UNDEFINED)
				area = OPEN;
			else if (is_open(all->raw_map[j][i]) && area == UNDEFINED)
				ft_exit(all, ERR_MAP_WAL);
			i++;
		}
		if (area != WALL && printf("horizontal \n"))
			ft_exit(all, ERR_MAP_WAL);
		j++;
	}
	if (area != WALL && printf("horizontal out \n"))
		ft_exit(all, ERR_MAP_WAL);
	return (SUCCESS);
}

//-----------------------------------------------------------------------------
//checks if open areas are surrounded by walls from a vertical pov
static int	map_err_walls_vertical(t_data *all)
{
	t_area	area;
	int		j;
	int		i;

	area = UNDEFINED;
	j = 0;
	i = 0;
	printf("all->height: %d\n", all->height);
	while (all->raw_map[j] != NULL)
	{
		area = UNDEFINED;
		while (all->raw_map[j] != NULL && all->raw_map[j][i] != '\0')
		{
			if (is_wall(all->raw_map[j][i]))
				area = WALL;
			else if (is_open(all->raw_map[j][i]) && area != UNDEFINED)
				area = OPEN;
			else if (is_open(all->raw_map[j][i]) && area == UNDEFINED)
				ft_exit(all, ERR_MAP_WAL);
			safe_j(all, &j, i);
		}
		if (area != WALL && printf("area: %d\n", area))
			ft_exit(all, ERR_MAP_WAL);
		i++;
		safe_j(all, &j, i);
	}
	if (area != WALL)
		ft_exit(all, ERR_MAP_WAL);
	return (SUCCESS);
}

//-----------------------------------------------------------------------------
//parses map and performs necessary error checking before rendering images
//TODO: empty line in map SHOULD be a problem. HANDLE THIS!
int	map_checks(t_data *all, char *map_name)
{
	if (create_raw_map(all, map_name))
		return (FAILURE);
	printf("-----------RAW_MAP------------\n");
	int j = -1;
	while (++j < all->height)
		printf("line[%d]: %s\n", j, all->raw_map[j]);
	if (map_err_elements(all))
		return (FAILURE);
	if (map_err_walls_horizontal(all))
		return (FAILURE);
	else if (map_err_walls_vertical(all))
		return (FAILURE);
	return (SUCCESS);
}
