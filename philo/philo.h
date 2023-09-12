/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:23:18 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/09/12 15:59:37 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef unsigned long long	t_time;

typedef struct s_philo
{
	int				id;
	int				must_eat;
	int				num_of_philo;
	int				total_eaten;
	int				*check_dead;
	t_time			time2die;
	t_time			time2eat;
	t_time			time2sleep;
	t_time			start_time;
	t_time			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*death;
	pthread_mutex_t	last;
	pthread_mutex_t	total;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

int		ft_arg_check(int ac, char **av);
int		ft_check_death(t_philo *philo);
int		ft_philo_wait(t_philo *philo, t_time wait_time);
long	ft_atol(const char *str);
t_time	ft_get_time_of_ms(void);
void	ft_mutex_init(t_philo *philo, pthread_mutex_t *forks, \
			pthread_mutex_t *death);
void	ft_arg_init(t_philo *philo, int ac, char **av, int *a);
void	ft_create_thread(t_philo *philo);
void	*ft_philo_loop(void *args);
int		ft_philo_eat(t_philo *philo);
void	ft_philo_sleep(t_philo *philo);
void	ft_philo_think(t_philo *philo);
void	ft_philo_print(t_philo *philo, char *status, int kill);
int		ft_check_de(t_philo *philo);

#endif