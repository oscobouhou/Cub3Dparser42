/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:44:28 by pgros             #+#    #+#             */
/*   Updated: 2023/02/15 15:51:07 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dparser.h"

t_cub	*init_game(void)
{
	t_cub	*init;

	init->extract = malloc(sizeof(t_extract));
	if (!init->extract)
		return (NULL);
	init->extract->map_width = 0; 
	init->extract->map_height = 0;
	init->extract->map = NULL;
	init->extract->textures[0] = NULL;
	init->extract->textures[1] = NULL;
	init->extract->textures[2] = NULL;
	init->extract->textures[3] = NULL;
	return (init);
}
int	file_extractor(t_cub *cub, char **av)
{
	(void)av;
	(void)cub;
	return (SUCCESS);
}

int main(int ac, char **av)
{
	t_cub	*cub;

	cub = init_game();
	file_extractor(cub, av);
	return (0);
}
