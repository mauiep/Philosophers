/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:32:46 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/03 14:33:49 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	release(int f, t_philo *datas)
{
	pthread_mutex_unlock(&(datas->fork[f]));
}

void	release_2(t_philo *datas, int down, int up)
{
	pthread_mutex_unlock(&datas->fork[down]);
	pthread_mutex_unlock(&datas->fork[up]);
}

int	pick_a_fork(t_philo *datas, int f)
{
	if (should_die(datas->feedtime, datas->time_to_die) || dead_mate(datas))
		return (0);
	pthread_mutex_lock(&datas->fork[f]);
	if (should_die(datas->feedtime, datas->time_to_die) || dead_mate(datas))
		return (release(f, datas), 0);
	return (1);
}

int	up_fork(t_philo *datas)
{
	int	up;

	up = datas->id;
	if (datas->id == 0)
		up = datas->nb_philo - 1;
	if (datas->id % 2 == 1 && datas->nb_philo > 1)
		ft_usleep(15);
	return (up);
}

int	down_fork(t_philo *datas)
{
	int	down;

	down = datas->id - 1;
	if (datas->id == 0)
		down = datas->id;
	return (down);
}
