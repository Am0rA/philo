#include "philo.h"

int	check_end(t_env *e)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&e->m_print);
	if (e->end)
		status = 1;
	pthread_mutex_unlock(&e->m_print);
	return (status);
}

static int	print(t_phi *p, t_list *l)
{
	int	status;

	status = 1;
	pthread_mutex_lock(&p->e->m_print);
	if (p->e->end)
	{
		pthread_mutex_unlock(&p->e->m_print);
		return (free(l), 0);
	}
	printf("%ld Philosopher %d %s\n", l->ms, l->i + 1, l->s);
	if (!ft_strcmp(l->s, "died") || count_meal(p, l))
		status = 0;
	if (!status)
		p->e->end = 1;
	free(l);
	pthread_mutex_unlock(&p->e->m_print);
	return (status);
}

static t_list	*find_a_node(t_env *e)
{
	int		i;
	t_list	*tmp;
	while (1)
	{
		i = -1;
		while (++i < e->n_phi)
		{
			pthread_mutex_lock(&e->phi[i].m_l);
			tmp = e->phi[i].l;
			pthread_mutex_unlock(&e->phi[i].m_l);
			if (tmp)
				return (tmp);
		}
	}
}

static int	print_loop(t_env *e)
{
	int		i;
	t_list *tmp;

	tmp = find_a_node(e);
	i = -1;
	while (++i < e->n_phi)
	{
		pthread_mutex_lock(&e->phi[i].m_l);
		if (e->phi[i].l && e->phi[i].l->ms < tmp->ms)
			tmp = e->phi[i].l;
		pthread_mutex_unlock(&e->phi[i].m_l);
	}
	pthread_mutex_lock(&e->phi[tmp->i].m_l);
	e->phi[tmp->i].l = e->phi[tmp->i].l->next;
	pthread_mutex_unlock(&e->phi[tmp->i].m_l);
	return (print(&e->phi[tmp->i], tmp));
}

void	*thread_printer(void *input)
{
	t_env *e;
	int		i;

	e = (t_env *)input;
	pthread_mutex_lock(&e->m_print);
	pthread_mutex_unlock(&e->m_print);
	while (!check_end(e))
		if (!print_loop(e))
			break ;
	i = -1;
	while (++i < e->n_phi)
	{
		pthread_mutex_lock(&e->phi[i].m_l);
		e->phi[i].end = 1;
		pthread_mutex_unlock(&e->phi[i].m_l);
	}
	return (NULL);
}