/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_table.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 18:56:09 by itopchu       #+#    #+#                 */
/*   Updated: 2023/05/17 18:56:09 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_env_mutexes(t_env *e)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&e->m_print);
	while (i < e->n_phi)
		pthread_mutex_destroy(&e->fork[i++]);
}

static int	init_philo_mutexes(t_env *e, t_phi *p, int i)
{
	if (pthread_mutex_init(&(p->m_l), NULL))
	{
		clean_env_mutexes(e);
		while (--i >= 0)
		{
			pthread_mutex_destroy(&e->phi[i].m_l);
			pthread_mutex_destroy(&e->phi[i].m_eat);
		}
		return (printf("m_l failed.\n"));
	}
	if (pthread_mutex_init(&(p->m_eat), NULL))
	{
		clean_env_mutexes(e);
		pthread_mutex_destroy(&(p->m_l));
		while (--i >= 0)
		{
			pthread_mutex_destroy(&e->phi[i].m_l);
			pthread_mutex_destroy(&e->phi[i].m_eat);
		}
		return (printf("m_eat failed.\n"));
	}
	return (0);
}

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
		if (init_philo_mutexes(e, &e->phi[i], i))
		{
			printf("init_philo_mutexes failed on %d\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_env_mutexes(t_env *e)
{
	int	i;

	if (pthread_mutex_init(&e->m_print, NULL))
		return (printf("mutex m_print failed.\n"));
	i = -1;
	while (++i < e->n_phi)
	{
		if (pthread_mutex_init(&e->fork[i], NULL))
		{
			printf("mutex e->fork[%d] failed.\n", i);
			pthread_mutex_destroy(&e->m_print);
			while (--i >= 0)
				pthread_mutex_destroy(&e->fork[i]);
			return (0);
		}
	}
	return (1);
}

int	init_table(t_env *e)
{
	e->c_meal = 0;
	e->end = 0;
	e->phi = (t_phi *)malloc(sizeof(t_phi) * e->n_phi);
	if (!(e->phi))
		return (printf("malloc e->phi failed.\n"));
	e->fork = malloc(sizeof(pthread_mutex_t) * e->n_phi);
	if (!(e->fork))
		return (free(e->phi), printf("malloc e->fork failed.\n"));
	if (!init_env_mutexes(e))
		return (free(e->fork), free(e->phi), printf("init_env_mutexes failed.\n"));
	if (!init_philo(e))
		return (free(e->fork), free(e->phi), printf("init_philo failed.\n"));
	return (0);
}
