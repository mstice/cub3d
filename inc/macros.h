/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:25:59 by mtice             #+#    #+#             */
/*   Updated: 2025/11/18 09:26:51 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000
# define WIN_NAME "cub3D"

# define BLACK 0x000000
# define WHITE 0xFFFFFF

# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6
# define ON_EXPOSE 12
# define ON_DESTROY 17

# define NO_EVENT_MASK "0L"
# define KEY_PRESS_MASK "1L<<0"
# define KEY_RELEASE_MASK "1L<<1"
# define BUTTON_PRESS_MASK "1L<<2"
# define BUTTON_RELEASE_MASK "1L<<3"
# define ENTER_WINDOW_MASK "1L<<4"
# define LEAVE_WINDOW_MASK "1L<<5"

# define ESC 65307

# define ERR_USAGE "Usage: ./cub3D <map.cub>"
# define ERR_FILE "Invalid file"
# define ERR_WALLS "Map is not covered by walls"
# define ERR_POS "Starting position on map not specified"

#endif
