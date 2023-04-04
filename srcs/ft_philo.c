/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:37:44 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/02 20:13:06 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <sys/time.h>

void	eat_enough(t_philo *datas)
{
	pthread_mutex_lock(&datas->glo->end);
	datas->glo->count++;
	if (datas->glo->count == datas->nb_philo)
	{
		pthread_mutex_lock(&datas->glo->die);
		datas->glo->dead = 1;
		pthread_mutex_unlock(&datas->glo->die);
	}
	pthread_mutex_unlock(&datas->glo->end);
}

int	philo_eats(t_philo *datas)
{
	long	tte;
	long	ttd;

	tte = datas->time_to_eat;
	ttd = datas->time_to_die;
	if (should_die(datas->feedtime, ttd) || dead_mate(datas))
		return (0);
	print_mess(datas, 2);
	if (time_now() - datas->feedtime + tte > ttd)
	{
		ft_usleep((ttd - (time_now() - datas->feedtime)));
		return (0);
	}
	datas->nb++;
	if (datas->ft != 0 && datas->ft == datas->nb)
		eat_enough(datas);
	ft_usleep(tte);
	datas->feedtime = time_now();
	if (should_die(datas->feedtime, ttd) || dead_mate(datas))
		return (0);
	return (1);
}

int	philo_sleeps(t_philo *datas)
{
	if (datas->time_to_sleep > datas->time_to_die || dead_mate(datas))
		return (0);
	print_mess(datas, 3);
	ft_usleep(datas->time_to_sleep);
	if (dead_mate(datas))
		return (0);
	return (1);
}
