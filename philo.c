#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void    *philo(void *param)
{
    int *p;

    p = (int *)param;
    printf("Bonjour tlm je suis le philo nb %d ! \n", *p);
    return ((void *)p);
}
int main(int ac, char **av)
{
    pthread_t   *pthread;
    int         nb_philo;
    int         i;
    int         *arg;
    int         err;
    int         *r;

    i = 0;
    if (ac >= 5)
    {
        nb_philo = atoi(av[1]);
        pthread = malloc(sizeof(pthread_t) * nb_philo);
        if (!pthread)
            return (0);
        arg = malloc(sizeof(int) * nb_philo);
        if (!arg)
            return (0);
        while(i < nb_philo)
        {
            arg[i] = i;
            err = pthread_create(&(pthread[i]), NULL, &philo, (void *) &(arg[i]));
            i++;
        }
        i = 0;
        while(i < nb_philo)
        {
            pthread_join(pthread[i], (void **)&r);
            printf("Le Philo numero %d est revenu avec la valeur %d\n", i, *r);
            i++;
        }
    }
    return (0);
}