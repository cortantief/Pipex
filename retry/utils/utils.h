/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharboul <sharboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:15:42 by sharboul          #+#    #+#             */
/*   Updated: 2022/01/04 16:23:54 by sharboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "../pipex.h"

t_pipes	*ft_new_pipes(int size);
void	*ft_free_pipes(t_pipes *pipes);

#endif
