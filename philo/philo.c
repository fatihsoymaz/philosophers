/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:23:09 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/09/12 18:59:16 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
int	ft_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_philo_print(philo, "has taken a left fork");
	if (philo->num_of_philo == 1)
	{
		ft_philo_wait(philo, philo->time2die);
		ft_philo_print(philo, "died");
		return (1);
	}
	pthread_mutex_lock(philo->right_fork);
	ft_philo_print(philo, "has taken a right fork ");
	ft_philo_print(philo, "is eating");
	pthread_mutex_lock(&philo->last);
	philo->last_meal = ft_get_time_of_ms();
	pthread_mutex_unlock(&philo->last);
	ft_philo_wait(philo, philo->time2eat);
	pthread_mutex_lock(&philo->total);
	philo->total_eaten++;
	pthread_mutex_unlock(&philo->total);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	ft_philo_sleep(t_philo *philo)
{
	ft_philo_print(philo, "is sleeping");
	ft_philo_wait(philo, philo->time2sleep);
}

void	ft_philo_print(t_philo *philo, char *status)
{
	pthread_mutex_lock(philo->death);
	if (!*philo->check_dead)
	{
		printf("%llu %d %s\n", (ft_get_time_of_ms() - philo->start_time),
			philo->id, status);
		if (!strcmp(status, "died"))
			*philo->check_dead = 1;
	}
	pthread_mutex_unlock(philo->death);
}

int	ft_philo_wait(t_philo *philo, t_time wait_time)
{
	t_time	time;

	time = ft_get_time_of_ms();
	while (ft_get_time_of_ms() - time < wait_time)
	{
		(void)philo;
		usleep(100);
	}
	return (0);
}
