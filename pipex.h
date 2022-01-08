/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharboul <sharboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:17:53 by sharboul          #+#    #+#             */
/*   Updated: 2022/01/05 05:23:42 by sharboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct pipe {
	int				ip;
	int				op;
}	t_pipe;

/*
 * arr -> arrays of pipe struct
 * size -> number of elements in array
 */

typedef struct pipes {
	t_pipe	**arr;
	size_t	size;
}	t_pipes;

#endif
