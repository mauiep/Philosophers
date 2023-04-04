/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:02:21 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/02 22:32:51 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <sys/time.h>

int	dead_mate(t_philo *datas)
{
	int	ret;

	pthread_mutex_lock(&datas->glo->die);
	ret = datas->glo->dead;
	pthread_mutex_unlock(&datas->glo->die);
	return (ret);
}

void	*philo_died(t_philo *datas)
{
	pthread_mutex_lock(&datas->glo->die);
	if (datas->glo->dead == 0)
	{
		datas->glo->dead = 1;
		pthread_mutex_unlock(&datas->glo->die);
		print_mess(datas, 5);
		return (NULL);
	}
	pthread_mutex_unlock(&datas->glo->die);
	return (NULL);
}

void	print_mess(t_philo *datas, int num)
{
	long int	time;

	pthread_mutex_lock(&datas->glo->wri);
	time = (time_now() - datas->start);
	if (num == 1 && !dead_mate(datas))
		printf("%ld %d has taken a fork\n", time, datas->id + 1);
	else if (num == 2 && !dead_mate(datas))
		printf("%ld %d is eating\n", time, datas->id + 1);
	else if (num == 3 && !dead_mate(datas))
		printf("%ld %d is sleeping\n", time, datas->id + 1);
	else if (num == 4 && !dead_mate(datas))
		printf("%ld %d is thinking\n", time, datas->id + 1);
	else if (num == 5)
		printf("%li %d died\n", time, datas->id + 1);
	pthread_mutex_unlock(&datas->glo->wri);
}

void	*philo(void *param)
{
	t_philo			*datas;
	int				up;
	int				down;
	long			ttd;

	datas = (t_philo *)param;
	ttd = datas->time_to_die;
	down = down_fork(datas);
	up = up_fork(datas);
	while (!should_die(datas->feedtime, ttd) && !dead_mate(datas))
	{
		if (!pick_a_fork(datas, up))
			return (philo_died(datas));
		print_mess(datas, 1);
		if ((up == down && ft_usleep(ttd)) || !pick_a_fork(datas, down))
			return (release(up, datas), philo_died(datas));
		print_mess(datas, 1);
		if (!philo_eats(datas))
			return (release_2(datas, up, down), philo_died(datas));
		release_2(datas, up, down);
		if (!philo_sleeps(datas))
			return ((void *)datas);
		print_mess(datas, 4);
	}
	return (philo_died(datas));
}

int	main(int ac, char **av)
{
	struct s_glo	*global;
	t_philo			*datas;
	int				nb_philo;

	if (ac >= 5 && ac < 7 && ft_verif(av))
	{
		nb_philo = spe_atoi(av[1]);
		global = NULL;
		datas = NULL;
		init_run(global, datas, av, nb_philo);
	}
	return (0);
}
