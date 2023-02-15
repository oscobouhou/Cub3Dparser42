/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3dparser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:45:47 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/15 15:50:31 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3DPARSER_H
# define CUB3DPARSER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "mlx.h"

// # STRUCT
typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_color;

typedef	struct	s_parse
{
	int			check;
}				t_parse;

typedef struct	s_extract
{
	int			map_width;
	int			map_height;
	t_color		rgb_c;
	t_color		rgb_f;
	t_parse		*parser;
	char		**map;
	int			init_pos[3];
	char		*textures[4];
}				t_extract;

typedef struct	s_cub
{
	t_extract	*extract;
}				t_cub;

// # ENUM
typedef	enum	e_cardinal
{
	NO,
	SO,
	WE,
	EA
}				t_cardinal;

typedef	enum	e_return
{
	FAIL,
	SUCCESS
}				t_return;

typedef	enum	e_rgb_params
{
	F,
	C
}				t_rgb_params;

#endif