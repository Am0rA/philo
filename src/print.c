/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 18:52:51 by itopchu       #+#    #+#                 */
/*   Updated: 2023/05/17 18:52:51 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	add_to_end(t_list **l, t_list *new)
{
	t_list	*tmp;

	tmp = *l;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*l = new;
}

int	add_cond(long ms, t_phi *p, char s[20])
{
	t_list	*new;
	int		i;

	new = malloc(sizeof(t_list));
	if (!new)
	{
		pthread_mutex_lock(&p->e->m_print);
		printf("Philosopher %d has messedup with list.\n", p->id);
		p->e->end = 1;
		pthread_mutex_unlock(&p->e->m_print);
		return (0);
	}
	i = -1;
	while (s[++i])
		new->s[i] = s[i];
	new->s[i] = '\0';
	new->next = NULL;
	new->i = p->id;
	new->ms = ms;
	pthread_mutex_lock(&p->m_l);
	add_to_end(&(p->l), new);
	pthread_mutex_unlock(&p->m_l);
	return (1);
}

int	count_meal(t_phi *p, t_list *l)
{
	int	check;

	check = 0;
	if (p->e->n_meal && !ft_strcmp(l->s, "is eating"))
		if (p->c_meal < p->e->n_meal)
			if (++p->c_meal == p->e->n_meal)
				if (++p->e->c_meal == p->e->n_phi)
					check = 1;
	return (check);
}
