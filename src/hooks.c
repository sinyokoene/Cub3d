/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 18:38:14 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/12 18:34:13 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	mouse_move_hook(double xpos, double ypos, void *param)
{
	t_data			*data;
	static double	last_x = WINDOW_WIDTH / 2;
	double			xoffset;
	double			old_dir_x;
	double			old_plane_x;

	data = (t_data *)param;
	(void)ypos;
	xoffset = xpos - last_x;
	last_x = xpos;
	xoffset *= 0.002;
	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(xoffset) - data->player.dir_y
		* sin(xoffset);
	data->player.dir_y = old_dir_x * sin(xoffset) + data->player.dir_y
		* cos(xoffset);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(xoffset)
		- data->player.plane_y * sin(xoffset);
	data->player.plane_y = old_plane_x * sin(xoffset) + data->player.plane_y
		* cos(xoffset);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key < 0 || keydata.key >= TOTAL_KEYS)
		return ;
	if (keydata.action == MLX_PRESS)
		data->key_states[keydata.key] = 1;
	else if (keydata.action == MLX_RELEASE)
		data->key_states[keydata.key] = 0;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		terminate(data);
}

void	update(t_data *data)
{
	if (data->key_states[MLX_KEY_W])
		update_move_forward(data);
	if (data->key_states[MLX_KEY_S])
		update_move_backward(data);
	if (data->key_states[MLX_KEY_A])
		update_strafe_left(data);
	if (data->key_states[MLX_KEY_D])
		update_strafe_right(data);
	if (data->key_states[MLX_KEY_LEFT])
		update_rotate_left(data);
	if (data->key_states[MLX_KEY_RIGHT])
		update_rotate_right(data);
}

void	loop_hook(void *param)
{
	t_data	*data;
	double	current_time;
	double	elapsed_time;

	data = (t_data *)param;
	update(data);
	render(data);
	data->frame_count++;
	current_time = mlx_get_time();
	elapsed_time = current_time - data->last_time;
	if (elapsed_time >= 1.0)
	{
		data->fps = data->frame_count / elapsed_time;
		data->frame_count = 0;
		data->last_time = current_time;
		printf("Debug: FPS calculated as %.2f\n", data->fps);
		printf("Debug: Frame count reset to %d\n", data->frame_count);
		printf("Debug: Last time updated to %.2f\n", data->last_time);
	}
}

void	hook_functions(t_data *data)
{
	mlx_key_hook(data->mlx, &key_hook, data);
	mlx_loop_hook(data->mlx, &loop_hook, data);
	mlx_cursor_hook(data->mlx, &mouse_move_hook, data);
}
