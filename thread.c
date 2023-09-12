/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:23:33 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/09/12 15:00:39 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_dead(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->last);
	if ((ft_get_time_of_ms() - philo->last_meal) > philo->time2die)
	{
		pthread_mutex_unlock(&philo->last);
		ft_philo_print(philo, "died", 1);
		pthread_mutex_lock(philo->death);
		*philo->check_dead = 1;
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->last);
	return (0);
}

int	ft_finish_serving(t_philo *philo, int *j, int *result)
{
	(void)result;
	(void)j;
	if (philo->must_eat != -1)
	{
		pthread_mutex_lock(&philo->total);
		if (philo->total_eaten == philo->must_eat)
		{
			pthread_mutex_unlock(&philo->total);
			return (1);
		}
		pthread_mutex_unlock(&philo->total);
	}
	return (0);
}

int	ft_check_de(t_philo *philo)
{
	int	i;
	int	j;
	int	result;

	//t_time	time;
	i = 0;
	j = 0;
	result = 0;

	while (i < philo->num_of_philo)
	{
		if (ft_dead(&philo[i]) || ft_finish_serving(&philo[i], &j, &result))
			return (1);
		i++;
	}
	return (0);
}

void	ft_create_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &ft_philo_loop, &philo[i]))
			return ;
		usleep(100);
		i++;
	}
	if (philo->num_of_philo > 1)
	{
		while (1)
		{
			if (ft_check_de(philo))
				break ;
		}
	}
	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

void	*ft_philo_loop(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->num_of_philo == 1)
	{
		if (pthread_mutex_lock(philo->left_fork))
			return (NULL);
		ft_philo_print(philo, " has taken a fork", 0);
		usleep(philo->time2die * 1000);
		ft_philo_print(philo, "died", 1);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		while (1)
		{
			pthread_mutex_lock(philo->death);
			if (*philo->check_dead)
			{
				pthread_mutex_unlock(philo->death);
				break ;
			}
			pthread_mutex_unlock(philo->death);
			ft_philo_eat(philo);
			pthread_mutex_lock(&philo->last);
			if (philo->total_eaten == philo->must_eat)
				break ;
			pthread_mutex_unlock(&philo->last);
			ft_philo_sleep(philo);
			ft_philo_print(philo, "is thinking", 0);
		}
		pthread_mutex_unlock(&philo->last);

	}
	return (NULL);
}

int	ft_check_death(t_philo *philo)
{
	if (*philo->check_dead)
	{
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	if (ft_get_time_of_ms() - philo->last_meal >
		philo->time2die)
	{
		ft_philo_print(philo, "died", 1);
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	return (0);
}
