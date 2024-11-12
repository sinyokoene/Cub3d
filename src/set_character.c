/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_character.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/09 00:12:24 by skoene        #+#    #+#                 */
/*   Updated: 2024/11/09 00:19:19 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_player_direction(t_data *data, char dir)
{
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	if (dir == 'N')
	{
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
	else if (dir == 'S')
	{
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
	}
	else if (dir == 'E')
	{
		data->player.dir_x = 1;
		data->player.plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		data->player.dir_x = -1;
		data->player.plane_y = -0.66;
	}
}

/* Function to initialize the player position and update the map */
void	set_player(t_data *data, int x, int y, char dir)
{
	data->player.x = x + 0.5;
	data->player.y = y + 0.5;
	set_player_direction(data, dir);
	data->map[y][x] = '0';
}

/* Function to validate each character in the map */
void	validate_map_character(t_data *data, size_t x, size_t y,
		int *player_count)
{
	char	c;

	c = data->map[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		set_player(data, x, y, c);
		(*player_count)++;
	}
	else if (c != '0' && c != '1' && c != ' ')
	{
		fprintf(stderr, "Error\nInvalid character '%c' in map.\n", c);
		terminate(data);
	}
}
