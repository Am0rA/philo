/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_input.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 18:52:40 by itopchu       #+#    #+#                 */
/*   Updated: 2023/05/17 18:52:40 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_signed(char *str)
{
	int		i;
	size_t	out;

	out = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			out = (out * 10) + str[i] - '0';
		else
			return (0);
		if (out > 2147483647)
			return (0);
		i++;
	}
	return (out);
}

int	set_input(t_env *e, int ac, char **av)
{
	e->n_phi = ft_signed(av[1]);
	if (!e->n_phi)
		return (printf("Use 0 < n_phi <= 2147483647\n"));
	e->t_die = ft_signed(av[2]);
	if (!e->t_die)
		return (printf("Use 0 < t_die <= 2147483647\n"));
	e->t_eat = ft_signed(av[3]);
	if (!e->t_eat)
		return (printf("Use 0 < t_eat <= 2147483647\n"));
	e->t_sleep = ft_signed(av[4]);
	if (!e->t_sleep)
		return (printf("Use 0 < t_sleep <= 2147483647\n"));
	e->n_meal = 0;
	if (ac == 6)
	{
		e->n_meal = ft_signed(av[5]);
		if (!e->n_meal)
			return (printf("Use 0 < n_meal <= 2147483647\n"));
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
