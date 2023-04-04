/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:35:56 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/02 22:46:40 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	init_thread_datas(int i, char **av, pthread_mutex_t *fork, t_glo *glo)
{
	t_philo	new;

	new.nb_philo = spe_atoi(av[1]);
	new.nb = 0;
	new.start = time_now();
	new.feedtime = time_now();
	new.id = i;
	new.time_to_die = spe_atoi(av[2]);
	new.time_to_eat = spe_atoi(av[3]);
	new.time_to_sleep = spe_atoi(av[4]);
	new.ft = 0;
	if (av[5] != NULL)
		new.ft = spe_atoi(av[5]);
	new.fork = fork;
	new.glo = glo;
	return (new);
}

struct s_glo	*init_global(int nb_philo)
{
	struct s_glo	*new;

	new = malloc(sizeof(struct s_glo));
	if (!new)
		return (NULL);
	new->dead = 0;
	pthread_mutex_init(&new->wri, NULL);
	pthread_mutex_init(&new->die, NULL);
	pthread_mutex_init(&new->end, NULL);
	new->count = 0;
	new->fork = init_fork(nb_philo);
	if (!new->fork)
		return (free(new), NULL);
	return (new);
}

pthread_mutex_t	*init_fork(int nb_philo)
{
	pthread_mutex_t	*fork;
	int				i;

	i = -1;
	fork = malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!fork)
		return (NULL);
	while (++i < nb_philo)
		pthread_mutex_init(&(fork[i]), NULL);
	return (fork);
}

void	init_run(t_glo *glo, t_philo *datas, char **av, int nb_philo)
{
	pthread_t		*pthread;
	int				i;

	glo = init_global(nb_philo);
	if (!glo)
		return ;
	datas = malloc(sizeof(t_philo) * nb_philo);
	if (!datas)
		return ;
	pthread = (pthread_t *)malloc(sizeof(pthread_t) * nb_philo);
	if (!pthread)
		return ;
	i = -1;
	while (++i < nb_philo)
		datas[i] = init_thread_datas(i, av, glo->fork, glo);
	i = -1;
	while (++i < nb_philo)
		ft_launch_pthread(pthread, datas, i);
	i = -1;
	while (++i < nb_philo)
		pthread_join(pthread[i], (void **) NULL);
	ft_free(datas, pthread);
}
