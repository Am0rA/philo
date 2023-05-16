#include "philo.h"

static int	init_philo(t_env *e)
{
	int	i;

	i = 0;
	while (i < e->n_phi)
	{
		e->phi[i].e = e;
		e->phi[i].id = i;
		e->phi[i].end = 0;
		e->phi[i].c_meal = 0;
		e->phi[i].l = NULL;
		if (pthread_mutex_init(&(e->phi[i].m_l), NULL))
		{
			while (i != 0 && --i)
				pthread_mutex_destroy(&(e->phi[i].m_l));
			pthread_mutex_destroy(&e->m_print);
			free(e->phi);
			return (printf("mutex_init e->phi[%d].m_l failed.\n", i));
		}
		i++;
	}
	return (0);
}

static int	init_mutexes(t_env *e)
{
	int	i;

	if (pthread_mutex_init(&e->m_print, NULL))
		return (printf("mutex m_print failed.\n"));
	e->fork = malloc(sizeof(pthread_mutex_t) * e->n_phi);
	if (!(e->fork))
	{
		pthread_mutex_destroy(&e->m_print);
		free(e->phi);
		return (printf("malloc e->fork failed.\n"));
	}
	i = -1;
	while (++i < e->n_phi)
		if (pthread_mutex_init(&e->fork[i], NULL))
		{
			printf("mutex e->fork[%d] failed.\n", i);
			while (i >= 0)
				pthread_mutex_destroy(&e->fork[i--]);
			return (1);
		}
	return (0);
}

int	init_table(t_env *e)
{
	e->c_meal = 0;
	e->end = 0;
	e->phi = (t_phi *)malloc(sizeof(t_phi) * e->n_phi);
	if (!(e->phi))
		return (printf("malloc phi * failed.\n"));
	if (init_mutexes(e))
		return (printf("init_mutexes failed.\n"));
	if (init_philo(e))
		return (printf("init_philo failed.\n"));
	return (0);
}