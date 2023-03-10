/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3dparser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:45:47 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/16 16:07:50 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3DPARSER_H
# define CUB3DPARSER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
#include <sys/types.h>
#include <errno.h>  
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

// # STRUCT
typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_color;

typedef	struct	s_parse
{
	int			check_prm;
	char		*charfile;
	char		*game_infos[6];
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

typedef	enum	e_return
{
	FAIL,
	SUCCESS
}				t_return;

typedef enum	e_params
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
}				t_params;

#endif