/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 18:55:59 by itopchu       #+#    #+#                 */
/*   Updated: 2023/05/17 18:55:59 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// Threads
# include <pthread.h>
// Printf
# include <stdio.h>
// Malloc
# include <stdlib.h>
// Usleep
# include <unistd.h>
// Time
# include <sys/time.h>
// Memset
# include <string.h>

typedef struct s_list
{
	long			ms;
	int				i;
	char			s[20];
	struct s_list	*next;
}	t_list;

typedef struct s_env
{
	int				c_meal;
	int				end;
	long			start;
	struct s_phi	*phi;
	pthread_mutex_t	*fork;
	pthread_mutex_t	m_print;
	pthread_t		printer;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_phi;
	int				n_meal;
}	t_env;

typedef struct s_phi
{
	int				id;
	int				end;
	int				c_meal;
	long			t_ate;
	t_env			*e;
	t_list			*l;
	pthread_t		philo;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_l;
}	t_phi;

//init_table.c
int		init_table(t_env *e);

//main.c
int		main(int ac, char **av);

//philo.c
int		check_starvation(t_phi *p);
void	*thread_philo(void *input);
int		count_meal(t_phi *p, t_list *l);


//print.c
int		add_cond(long ms, t_phi *p, char s[20]);

//printer.c
void	*thread_printer(void *input);

//set_input.c
int		set_input(t_env *e, int ac, char **av);
int		ft_strcmp(char *s1, char *s2);

//start_dinner.c
int		start_dinner(t_env *e);

//time.c
long	cur_time(void);
long	dinner_time(t_env *e);
void	ft_better_sleep(long time);

#endif