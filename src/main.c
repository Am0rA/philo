#include "philo.h"

static void	join_threads(t_env *e)
{
	int	i;

	i = -1;
	while (++i < e->n_phi)
	{
		pthread_join(e->phi[i].printer, NULL);
		pthread_join(e->phi[i].philo, NULL);
	}
}

static void	clean_table(t_env *e)
{
	t_list	*tmp;
	t_list	*cur;
	int		i;

	pthread_mutex_destroy(&e->m_print);
	i = -1;
	while (++i < e->n_phi)
		pthread_mutex_destroy(&(e->fork[i]));
	free(e->fork);
	i = -1;
	while (++i < e->n_phi)
	{
		cur = e->phi[i].l;
		while (cur)
		{
			tmp = cur;
			cur = cur->next;
			free(tmp);
		}
		pthread_mutex_destroy(&(e->phi[i].m_l));
	}
	free(e->phi);
}

int	main(int ac, char **av)
{
	t_env	e;

	if (ac != 5 && ac != 6)
		return (printf("Input must be 4 or 5 intigers.\n"));
	if (set_input(&e, ac, av))
		return (printf("set_input failed.\n"));
	if (e.n_phi == 1)
	{
		printf("1 Philosopher 1 has taken left fork.\n");
		printf("%d Philosopher 1 died.\n", e.t_die);
		return (0);
	}
	if (init_table(&e))
		return (printf("init_table failed.\n"));
	if (start_dinner(&e))
	{
		clean_table(&e);
		return (printf("start_dinner failed.\n"));
	}
	join_threads(&e);
	clean_table(&e);
	return (0);
}