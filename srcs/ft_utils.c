/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:31:34 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/01 19:39:10 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <limits.h>

void	ft_launch_pthread(pthread_t *pthread, t_philo *datas, int i)
{
	if (pthread_create(&(pthread[i]), NULL, &philo, (void *) &(datas[i])) != 0)
	{
		pthread_mutex_lock(&datas->glo->die);
		datas->glo->dead = 1;
		pthread_mutex_unlock(&datas->glo->die);
	}
}

void	ft_free(t_philo *datas, pthread_t *pthread)
{
	int	i;

	i = -1;
	while (++i < datas->nb_philo)
		pthread_mutex_destroy(&datas->glo->fork[i]);
	pthread_mutex_destroy(&datas->glo->wri);
	pthread_mutex_destroy(&datas->glo->die);
	pthread_mutex_destroy(&datas->glo->end);
	free(datas->glo->fork);
	free(datas->glo);
	free(pthread);
	free(datas);
}

int	spe_atoi(char *str)
{
	int	nb;

	nb = 0;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + *str - 48;
		str++;
	}
	if (*str != 0)
		return (0);
	return (nb);
}

int	ft_verif(char **av)
{
	int	i;

	i = 1;
	while (av[i] != NULL)
	{
		if (spe_atoi(av[i]) > INT_MAX || spe_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}
