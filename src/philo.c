/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 18:53:09 by itopchu       #+#    #+#                 */
/*   Updated: 2023/05/17 18:53:09 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_starvation(t_phi *p)
{
	long	dinner;
	int		status;

	pthread_mutex_lock(&p->m_eat);
	dinner = dinner_time(p->e);
	status = 0;
	if (dinner - p->t_ate >= p->e->t_die)
	{
		status = 1;
		if (!add_cond(dinner, p, "died"))
			printf ("Malloc problem.\n");
	}
	pthread_mutex_unlock(&p->m_eat);
	return (status);
}

static int	unlock_mutexes(t_phi *p, int step, int vice)
{
	if (step)
		pthread_mutex_unlock(&p->e->fork[vice]);
	if (step == 2)
		pthread_mutex_unlock(&p->e->fork[p->id]);
	return (0);
}

static int	eat(t_phi *p)
{
	int	vice;

	vice = (p->id + 1) % p->e->n_phi;
	pthread_mutex_lock(&p->e->fork[vice]);
	if (!add_cond(dinner_time(p->e), p, "has taken left fork"))
		return (unlock_mutexes(p, 1, vice));
	pthread_mutex_lock(&p->e->fork[p->id]);
	if (!add_cond(dinner_time(p->e), p, "has taken own fork"))
		return (unlock_mutexes(p, 2, vice));
	p->t_ate = dinner_time(p->e);
	if (!add_cond(p->t_ate, p, "is eating"))
		return (unlock_mutexes(p, 2, vice));
	ft_better_sleep(p->e->t_eat);
	pthread_mutex_unlock(&p->e->fork[vice]);
	pthread_mutex_unlock(&p->e->fork[p->id]);
	return (1);
}

static int	end(t_phi *p)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&p->m_l);
	if (p->end)
		status = 1;
	pthread_mutex_unlock(&p->m_l);
	return (status);
}

void	*thread_philo(void *input)
{
	t_phi	*p;

	p = (t_phi *)input;
	p->t_ate = dinner_time(p->e);
	if (p->e->n_phi == 1)
	{
		printf("0 Philosopher 1 has taken left fork.\n");
		usleep(p->e->t_die * 1000);
		return (NULL);
	}
	pthread_mutex_lock(&p->e->m_print);
	pthread_mutex_unlock(&p->e->m_print);
	if (p->id % 2)
		ft_better_sleep(1);
	while (!end(p))
	{
		if (!eat(p))
			break ;
		if (!add_cond(dinner_time(p->e), p, "is sleeping"))
			break ;
		ft_better_sleep(p->e->t_sleep);
		if (!add_cond(dinner_time(p->e), p, "is thinking"))
			break ;
	}
	return (NULL);
}
