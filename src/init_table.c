#include "philo.h"

static int	destroy_mutexes(t_env *e, int i, int j)
{
	int x;
	int	y;

	x = 0;
	y = 0;
	pthread_mutex_destroy(&e->m_print);
	while (e->c_meal < e->n_phi)
		pthread_mutex_destroy(&e->fork[e->c_meal++]);
	while (x <= i)
		pthread_mutex_destroy(&(e->phi[x++].m_l));
	while (y <= j)
		pthread_mutex_destroy(&(e->phi[y++].m_eat));
	free(e->phi);
	free(e->fork);
	return (printf("On e->phi i %d j %d failed.\n", i, j));
}

static int	init_philo(t_env *e)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < e->n_phi)
	{
		e->phi[i].e = e;
		e->phi[i].id = i;
		e->phi[i].end = 0;
		e->phi[i].c_meal = 0;
		e->phi[i].l = NULL;
		if (pthread_mutex_init(&(e->phi[j].m_eat), NULL))
			return (destroy_mutexes(e, i, j - 1));
		j++;
		if (pthread_mutex_init(&(e->phi[i].m_l), NULL))
			return (destroy_mutexes(e, i - 1, j));
		i++;
	}
	return (0);
}

static int	init_mutexes(t_env *e)
{
	int	i;

	if (pthread_mutex_init(&e->m_print, NULL))
		return (printf("mutex m_print failed.\n"));
	i = -1;
	while (++i < e->n_phi)
	{
		if (pthread_mutex_init(&e->fork[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&e->fork[i]);
			pthread_mutex_destroy(&e->m_print);
			return (printf("mutex e->fork[i] failed.\n"));
		}
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
	e->fork = malloc(sizeof(pthread_mutex_t) * e->n_phi);
	if (!e->fork)
		return (free(e->phi), printf("malloc e->fork failed.\n"));
	if (init_mutexes(e))
	{
		free(e->phi);
		free(e->fork);
		return (printf("init_mutexes failed.\n"));
	}
	if (init_philo(e))
		return (printf("init_philo failed.\n"));
	return (0);
}
