/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:34:12 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/03 14:43:46 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <sys/time.h>

long	time_diff(struct timeval *s, struct timeval e)
{
	long	ret;

	ret = (e.tv_sec - s->tv_sec) * 1000 + (e.tv_usec - s->tv_usec) / 1000;
	return (ret);
}

long	time_diff2(struct timeval *s, struct timeval e)
{
	long	ret;

	ret = (e.tv_sec - s->tv_sec) * 1000 + (e.tv_usec - s->tv_usec) / 1000;
	return (ret);
}

long	time_now(void)
{
	struct timeval	now;
	long			time;

	time = 0;
	gettimeofday(&now, NULL);
	time = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (time);
}

int	ft_usleep(long time)
{
	long	start;

	start = time_now();
	while ((time_now() - start) < time)
		usleep(50);
	return (1);
}

int	should_die(long feed, long time_to_die)
{
	if (time_now() - feed > time_to_die)
		return (1);
	return (0);
}
