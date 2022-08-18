#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

typedef struct  s_philo
{
    int id;
    int nb_philo;
	struct timeval feedtime;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_feeding;
    pthread_mutex_t *fork;
}               t_philo;

#endif
