/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_rotation.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 23:58:54 by skoene        #+#    #+#                 */
/*   Updated: 2024/11/09 00:13:57 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_rotate_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(-data->player.rot_speed)
		- data->player.dir_y * sin(-data->player.rot_speed);
	data->player.dir_y = old_dir_x * sin(-data->player.rot_speed)
		+ data->player.dir_y * cos(-data->player.rot_speed);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(-data->player.rot_speed)
		- data->player.plane_y * sin(-data->player.rot_speed);
	data->player.plane_y = old_plane_x * sin(-data->player.rot_speed)
		+ data->player.plane_y * cos(-data->player.rot_speed);
}

void	update_rotate_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(data->player.rot_speed)
		- data->player.dir_y * sin(data->player.rot_speed);
	data->player.dir_y = old_dir_x * sin(data->player.rot_speed)
		+ data->player.dir_y * cos(data->player.rot_speed);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(data->player.rot_speed)
		- data->player.plane_y * sin(data->player.rot_speed);
	data->player.plane_y = old_plane_x * sin(data->player.rot_speed)
		+ data->player.plane_y * cos(data->player.rot_speed);
}
