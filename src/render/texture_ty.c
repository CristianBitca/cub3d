

#include "cub3d.h"
#include "render.h"
#include "parsing.h"

void	calculate_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0 && ray->dir_x > 0)
        ray->texture = game->asset->WE;
    else if (ray->side == 0 && ray->dir_x < 0)
        ray->texture = game->asset->EA;
    else if (ray->side == 1 && ray->dir_y > 0)
        ray->texture = game->asset->NO;
    else
        ray->texture = game->asset->SO;
    if (ray->side == 0)
        ray->wall_x = game->player->y + ray->perp_wall_dist * ray->dir_y;
    else
        ray->wall_x = game->player->x + ray->perp_wall_dist * ray->dir_x;
    ray->wall_x -= floor(ray->wall_x);
    ray->tex_x = (int)(ray->wall_x * (double)ray->texture->width);
    if (ray->side == 0 && ray->dir_x < 0)
        ray->tex_x = ray->texture->width - ray->tex_x - 1;
    if (ray->side == 1 && ray->dir_y > 0)
        ray->tex_x = ray->texture->width - ray->tex_x - 1;
    ray->step = (double)ray->texture->height / ray->line_height;
    ray->tex_pos = (ray->draw_start - game->screen_height / 2 + ray->line_height / 2) * ray->step;
}

void	draw_vertical_line(t_game *game, t_ray *ray, int x)
{
	int	y;
    int color;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
        ray->tex_y = (int)ray->tex_pos;
        if (ray->tex_y < 0)
            ray->tex_y = 0;
        if (ray->tex_y >= ray->texture->height)
            ray->tex_y = ray->texture->height - 1;
        ray->tex_pos += ray->step;
        color = *(int *)(ray->texture->addr + (ray->tex_y * ray->texture->line_len + ray->tex_x * (ray->texture->bpp / 8)));
        put_pixel(game->img, x, y, color);
        y++;
	}
}

void    draw_floor_and_ceiling(t_game *game)
{
    int x;
    int y;
    int half;

    half = game->screen_height / 2;
    y = -1;
    while (++y < game->screen_height)
    {
        x = -1;
        while (++x < game->screen_width)
        {
            if (y < half)
                put_pixel(game->img, x, y, game->asset->C);
            else
                put_pixel(game->img, x, y, game->asset->F);
        }
    }
}