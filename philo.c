#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo.h"

void    *philo(void *param)
{
    t_philo *datas;

    usleep(1000);
    printf("aaaa");
    datas = (t_philo*)param;
    printf("Bonjour tlm je suis le philo nb %d ! \n", datas->id);
    return ((void*)datas);
}

t_philo init_thread_datas(int i, char **av, pthread_mutex_t *fork)
{
    t_philo new;

    new.id = i;
    new.nb_philo = atoi(av[1]);
    new.feedtime = 1;//timestamp
    new.time_to_die = 1;
    new.time_to_eat = 1;
    new.time_to_sleep= 1;
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

    printf("bienvenue dans PHILOSOPHERS\n");
    i = 0;
    if (ac >= 5)
    {
        nb_philo = atoi(av[1]);
        printf("on va prep les fourchettes il y a %d philos\n", nb_philo);
        fork = malloc(sizeof(pthread_mutex_t) * nb_philo);
        if (!fork)
            return (printf("malloc error fork\n"));
        datas = malloc(sizeof(t_philo) * nb_philo);
        if (!datas)
            return (printf("malloc error philo data\n"));
        while (i < nb_philo)
        {
            printf("%d fork\n", i);
            pthread_mutex_init(fork[i], NULL);
            i++;
        }
        write(1, "Bonjour init ok\n", 17);
        printf("gonna malloc : %d\n", sizeof(pthread_t) * nb_philo);
        ;
        if (!(pthread = (pthread_t *)malloc(sizeof(pthread_t) * nb_philo)))
        {
            printf("malloc error pthreads\n");
            return (printf("malloc error pthreads\n"));
        }
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
    return (0);
}