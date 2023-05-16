#include "philo.h"

long	cur_time(void)
{
	struct timeval	cur;

	if (gettimeofday(&cur, NULL) == -1)
		return (-1);
	return (cur.tv_sec * 1000 + cur.tv_usec / 1000);
}

long	dinner_time(t_env *e)
{
	return (cur_time() - e->start);
}

void	ft_better_sleep(long time)
{
	long	start;
	long	cur;

	start = cur_time();
	cur = 0;
	while (cur < time)
	{
		usleep(time * 100);
		cur = cur_time() - start;
	}
}