#include "philo.h"

static int	check_starvation(t_phi *p)
{
	if (dinner_time(p->e) - p->t_ate >= p->e->t_die)
	{
		if (!add_cond(dinner_time(p->e), p, "died"))
			return (1);
		return (1);
	}
	return (0);
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
	// if (check_starvation(p))
	// 	return (unlock_mutexes(p, 1, vice));
	if (!add_cond(dinner_time(p->e), p, "has taken left fork"))
		return (unlock_mutexes(p, 1, vice));
	pthread_mutex_lock(&p->e->fork[p->id]);
	// if (check_starvation(p))
	// 	return (unlock_mutexes(p, 2, vice));
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
	pthread_mutex_lock(&p->e->m_print);
	pthread_mutex_unlock(&p->e->m_print);
	p->t_ate = dinner_time(p->e);
	if (p->id % 2)
		ft_better_sleep(p->e->t_die / 2);
	while (!end(p))
	{
		if (!eat(p))
			break ;
		if (!add_cond(dinner_time(p->e), p, "is sleeping"))
			break ;
		ft_better_sleep(p->e->t_sleep);
		if (check_starvation(p))
			break ;
		if (!add_cond(dinner_time(p->e), p, "is thinking"))
			break ;
	}
	return (NULL);
}