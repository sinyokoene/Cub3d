/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 23:58:17 by skoene        #+#    #+#                 */
/*   Updated: 2024/11/08 23:59:41 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_move_forward(t_data *data)
{
	if (data->map[(int)(data->player.y)][(int)(data->player.x
			+ data->player.dir_x * data->player.move_speed)] == '0')
		data->player.x += data->player.dir_x * data->player.move_speed;
	if (data->map[(int)(data->player.y + data->player.dir_y
			* data->player.move_speed)][(int)(data->player.x)] == '0')
		data->player.y += data->player.dir_y * data->player.move_speed;
}

void	update_move_backward(t_data *data)
{
	if (data->map[(int)(data->player.y)][(int)(data->player.x
			- data->player.dir_x * data->player.move_speed)] == '0')
		data->player.x -= data->player.dir_x * data->player.move_speed;
	if (data->map[(int)(data->player.y - data->player.dir_y
			* data->player.move_speed)][(int)(data->player.x)] == '0')
		data->player.y -= data->player.dir_y * data->player.move_speed;
}

void	update_strafe_left(t_data *data)
{
	double	perp_dir_x;
	double	perp_dir_y;

	perp_dir_x = data->player.dir_y;
	perp_dir_y = -data->player.dir_x;
	if (data->map[(int)(data->player.y)][(int)(data->player.x + perp_dir_x
			* data->player.move_speed)] == '0')
		data->player.x += perp_dir_x * data->player.move_speed;
	if (data->map[(int)(data->player.y + perp_dir_y
			* data->player.move_speed)][(int)(data->player.x)] == '0')
		data->player.y += perp_dir_y * data->player.move_speed;
}

void	update_strafe_right(t_data *data)
{
	double	perp_dir_x;
	double	perp_dir_y;

	perp_dir_x = -data->player.dir_y;
	perp_dir_y = data->player.dir_x;
	if (data->map[(int)(data->player.y)][(int)(data->player.x + perp_dir_x
			* data->player.move_speed)] == '0')
		data->player.x += perp_dir_x * data->player.move_speed;
	if (data->map[(int)(data->player.y + perp_dir_y
			* data->player.move_speed)][(int)(data->player.x)] == '0')
		data->player.y += perp_dir_y * data->player.move_speed;
}
