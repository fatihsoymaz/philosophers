#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include "./libft/libft.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				max_eat_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nop;
	pthread_t		thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	bool			philosophers_alive;
}					t_philo;

//typedef struct s_args
//{
//	int						n_philo;
//	t_philo					**philo;
//}							t_args;


int					ft_atoi2(char *str);
void				philo_control(int argc, char **argv, t_philo *philo);
#endif