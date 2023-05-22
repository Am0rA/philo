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
	new->i = p->id + 1;
	new->ms = ms;
	pthread_mutex_lock(&p->m_l);
	add_to_end(&(p->l), new);
	pthread_mutex_unlock(&p->m_l);
	return (1);
}

static int	count_meal(t_phi *p, t_list *l)
{
	int	check;

	if (!p->e->n_meal)
		return (0);
	check = 0;
	if (!ft_strcmp(l->s, "is eating"))
	{
		if (p->c_meal < p->e->n_meal)
		{
			p->c_meal++;
			if (p->c_meal == p->e->n_meal)
				p->e->c_meal++;
			if (p->e->c_meal == p->e->n_phi)
				check = 1;
		}
	}
	free(l);
	return (check);
}

static int	print_cond(t_phi *p)
{
	t_list	*tmp;
	int		check;

	check = 1;
	pthread_mutex_lock(&p->m_l);
	tmp = p->l;
	if (tmp)
		p->l = p->l->next;
	pthread_mutex_unlock(&p->m_l);
	pthread_mutex_lock(&p->e->m_print);
	if (p->e->end)
		check = 0;
	if (check && tmp)
	{
		printf("%ld Philosopher %d %s\n", tmp->ms, tmp->i, tmp->s);
		if (!ft_strcmp(tmp->s, "died") || count_meal(p, tmp))
			p->e->end = 1;
		if (p->e->end)
			check = 0;
	}
	pthread_mutex_unlock(&p->e->m_print);
	return (check);
}

void	*thread_print(void *input)
{
	t_phi	*p;

	p = (t_phi *)input;
	pthread_mutex_lock(&p->e->m_print);
	pthread_mutex_unlock(&p->e->m_print);
	while (print_cond(p))
		;
	pthread_mutex_lock(&p->m_l);
	p->end = 1;
	pthread_mutex_unlock(&p->m_l);
	return (NULL);
}
