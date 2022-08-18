/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:02:21 by admaupie          #+#    #+#             */
/*   Updated: 2022/08/18 20:33:51 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo.h"
#include <sys/time.h>

int	take_a_fork()
{
	return (0);
}

float time_diff(struct timeval *start, struct timeval *end)
{
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

void    *philo(void *param)
{
    t_philo 		*datas;
	struct timeval	now;
	int				err;

    datas = (t_philo*)param;
    if (datas->id % 2 == 0)
		usleep(10);
	gettimeofday(&now, NULL);
	while (time_diff(&(datas->feedtime), &now) < datas->time_to_die * 1e-3)
	{
		printf("Philo %d : time to die = %f et now = %f\n", datas->id, datas->time_to_die * 1e-3, time_diff(&(datas->feedtime), &now));
		if ((err = pthread_mutex_lock(&(datas->fork[0]))) == 0)
		{
			printf("Philo %d has taken a fork !\n", datas->id);
			usleep(datas->time_to_eat * 1000);
			pthread_mutex_unlock(&(datas->fork[0]));
		}
		else
			printf("Philo %d cant eat, err=%d\n", datas->id, err);
		gettimeofday(&now, NULL);
	}
	printf("Philo %d just die, time=%f\n", datas->id, time_diff(&(datas->feedtime), &now));
	return ((void*)datas);
}

t_philo init_thread_datas(int i, char **av, pthread_mutex_t *fork)
{
	t_philo 		new;

	gettimeofday(&(new.feedtime), NULL);
	new.id = i;
    new.nb_philo = atoi(av[1]);
    new.time_to_die = atoi(av[2]);
    new.time_to_eat = atoi(av[3]);
    new.time_to_sleep = atoi(av[4]);
    new.nb_feeding = 0;
    new.fork = fork;
    return (new);
}
int main(int ac, char **av)
{
    pthread_t   *pthread;
    int         nb_philo;
    int         i;
    t_philo     *datas;
    int         err;
    int         *r;
    pthread_mutex_t *fork;
	struct timeval	beg;
	struct timeval	end;

	gettimeofday(&beg, NULL);
    i = 0;
    if (ac >= 5)
    {
        nb_philo = atoi(av[1]);
        fork = malloc(sizeof(pthread_mutex_t) * nb_philo);
        if (!fork)
            return (printf("malloc error fork\n"));
        datas = malloc(sizeof(t_philo) * nb_philo);
        if (!datas)
            return (printf("malloc error philo data\n"));
        while (i < nb_philo)
        {
            pthread_mutex_init(&(fork[i]), NULL);
            i++;
        }
        if (!(pthread = (pthread_t *)malloc(sizeof(pthread_t) * nb_philo)))
            return (printf("malloc error pthreads\n"));
        write(1, "forks done \n", 13);
        i = 0;
        while (i < nb_philo)//init thread datas + create
        {
            datas[i] = init_thread_datas(i, av, fork);
            err = pthread_create(&(pthread[i]), NULL, &philo, (void *) &(datas[i]));
            i++;
        }
        i = 0;
        while(i < nb_philo)// boucle des JOIN
        {
            pthread_join(pthread[i], (void **)&r);
            printf("Le Philo numero %d est revenu avec la valeur %d\n", i, *r);
            i++;
        }
    }
	gettimeofday(&end, NULL);
    printf("TIME= %f\n", time_diff(&beg, &end));
	return (0);
}
