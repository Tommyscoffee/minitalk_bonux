/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:00:32 by akihito           #+#    #+#             */
/*   Updated: 2021/12/05 21:38:41 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# define BUFFSIZE 1024

# ifndef TURE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# include <stdlib.h>
# include "libft.h"
# include <stdio.h>
# include <unistd.h>

typedef struct s_stack
{
	size_t		bit;
	pid_t		sipid;
	size_t		top_byte;
}		t_stack;

static t_stack		g_bit = {0, 0, 0};
//構造体t_stackを初期化する。
void	error(char *str_error);

#endif