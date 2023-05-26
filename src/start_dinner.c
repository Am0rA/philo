/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_dinner.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 18:52:15 by itopchu       #+#    #+#                 */
/*   Updated: 2023/05/17 18:52:15 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_philo(t_env *e)
{
	int	i;

	i = -1;
	while (++i < e->n_phi)
	{
		if (pthread_create(&(e->phi[i].philo), NULL, \
			thread_philo, &(e->phi[i])))
		{
			e->end = 1;
			pthread_mutex_unlock(&e->m_print);
			break ;
		}
	}
	if (i < e->n_phi)
	{
		printf("Failed on %d.\n", i);
		while (i >= 0)
			pthread_join(e->phi[i--].philo, NULL);
		pthread_join(e->printer, NULL);
		return (1);
	}
	return (0);
}

static int	start_printer(t_env *e)
{
	if (pthread_create(&e->printer, NULL, thread_printer, e))
	{
		e->end = 1;
		pthread_mutex_unlock(&e->m_print);
		return (1);
	}
	return (0);
}

int	start_dinner(t_env *e)
{
	pthread_mutex_lock(&e->m_print);
	if (start_printer(e))
		return (printf("start_printer failed.\n"));
	if (start_philo(e))
		return (printf("start_philo failed.\n"));
	e->start = cur_time();
	pthread_mutex_unlock(&e->m_print);
	return (0);
}
