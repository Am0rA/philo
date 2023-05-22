/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 18:51:57 by itopchu       #+#    #+#                 */
/*   Updated: 2023/05/17 18:51:57 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	cur_time(void)
{
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	return (cur.tv_sec * 1000 + cur.tv_usec / 1000);
}

long	dinner_time(t_env *e)
{
	return (cur_time() - e->start);
}

void	ft_better_sleep(long time)
{
	long	start;

	start = cur_time();
	while (cur_time() - start < time)
		usleep(100);
}
