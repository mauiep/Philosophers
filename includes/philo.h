/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:50:06 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/02 22:33:37 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_glo
{
	int				dead;
	pthread_mutex_t	die;
	pthread_mutex_t	wri;
	pthread_mutex_t	*fork;
	pthread_mutex_t	end;
	int				count;
}				t_glo;

typedef struct s_philo
{
	int				id;
	int				nb_philo;
	long			start;
	long			feedtime;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				ft;
	int				nb;
	struct s_glo	*glo;
	pthread_mutex_t	*fork;
}				t_philo;

int				ft_verif(char **av);
void			eat_enough(t_philo *datas);
int				dead_mate(t_philo *datas);
void			*philo_died(t_philo *datas);
int				philo_eats(t_philo *datas);
int				philo_sleeps(t_philo *datas);
long			time_diff(struct timeval *start, struct timeval end);
long			time_diff2(struct timeval *start, struct timeval end);
long			time_now(void);
int				should_die(long feed, long time_to_die);
void			print_mess(t_philo *datas, int num);
t_philo			init_thread_datas(int i, char **av, pthread_mutex_t *fork,
					t_glo *global);
void			release(int f, t_philo *datas);
void			release_2(t_philo *datas, int down, int up);
int				pick_a_fork(t_philo *datas, int f);
int				up_fork(t_philo *datas);
int				down_fork(t_philo *datas);
struct s_glo	*init_global(int nb_philo);
pthread_mutex_t	*init_fork(int nb_philo);
int				spe_atoi(char *nb);
int				ft_verif(char **av);
void			ft_free(t_philo *datas, pthread_t *pthread);
void			*philo(void *param);
void			init_run(t_glo *global, t_philo *datas, char **av, int nb);
int				ft_usleep(long time);
void			ft_launch_pthread(pthread_t *pthread, t_philo *datas, int i);

#endif
