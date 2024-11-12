/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 23:48:18 by skoene        #+#    #+#                 */
/*   Updated: 2024/11/12 20:57:06 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_fps(t_data *data)
{
	char				fps_text[100];
	static mlx_image_t	*fps = NULL;

	snprintf(fps_text, sizeof(fps_text), "FPS: %.2f", data->fps);
	if (fps)
		mlx_delete_image(data->mlx, fps);
	fps = mlx_put_string(data->mlx, fps_text, 40, 10);
}

uint32_t	rgb_to_hex(t_color color)
{
	return ((color.r << 24) | (color.g << 16) | (color.b << 8) | 0xFF);
}

uint32_t	get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
	int			pixel_index;
	uint8_t		*pixel;
	uint32_t	color;

	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
		return (0);
	pixel_index = (y * texture->width + x) * 4;
	pixel = &texture->pixels[pixel_index];
	color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
	return (color);
}

mlx_texture_t	*select_texture(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (data->texture_west);
		else
			return (data->texture_east);
	}
	else
	{
		if (ray->dir_y > 0)
			return (data->texture_north);
		else
			return (data->texture_south);
	}
}

void	calculate_texture_coordinates(t_data *data, t_ray *ray,
		mlx_texture_t *texture)
{
	if (ray->side == 0)
		ray->wall_x = data->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = data->player.x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)texture->width);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = texture->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = texture->width - ray->tex_x - 1;
	ray->step = 1.0 * texture->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2 + ray->line_height / 2)
		* ray->step;
}
