#ifndef PHILO_H
# define PHILO_H

typedef struct  s_philo
{
    int id;
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_feeding;
}               t_philo;

#endif