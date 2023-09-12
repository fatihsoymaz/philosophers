/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:22:49 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/09/12 15:27:03 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_arg_check(int ac, char **av)
{
	int	i;
	int	j;

	if (ac == 5 || ac == 6)
	{
		i = 1;
		while (av[i])
		{
			j = 0;
			while (av[i][j])
			{
				if (!(av[i][j] >= '0' && av[i][j] <= '9'))
					return (0);
				if (av[1][0] == '0')
					return (0);
				j++;
			}
			i++;
		}
	}
	else
		return (0);
	return (1);
}

long	ft_atol(const char *str)
{
	int		i;
	long	nb;
	int		sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb * sign);
}

void	ft_arg_init(t_philo *philo, int ac, char **av, int *check_dead)
{
	int	i;

	i = 0;
	while (i < ft_atol(av[1]))
	{
		philo[i].id = i + 1;
		philo[i].num_of_philo = ft_atol(av[1]);
		philo[i].time2die = ft_atol(av[2]);
		philo[i].time2eat = ft_atol(av[3]);
		philo[i].time2sleep = ft_atol(av[4]);
		if (ac == 6)
			philo[i].must_eat = ft_atol(av[5]);
		else
			philo[i].must_eat = -1;
		philo[i].last_meal = ft_get_time_of_ms();
		philo[i].start_time = ft_get_time_of_ms();
		philo[i].total_eaten = 0;
		philo[i].check_dead = check_dead;
		pthread_mutex_init(&philo[i].last, NULL);
		pthread_mutex_init(&philo[i].total, NULL);
		i++;
	}
}

t_time	ft_get_time_of_ms(void)
{
	struct timeval	tp;
	t_time			time;

	gettimeofday(&tp, NULL);
	time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (time);
}

void	ft_mutex_init(t_philo *philo, pthread_mutex_t *forks,
		pthread_mutex_t *death)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % philo->num_of_philo];
		i++;
	}
	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_mutex_init(philo[i].left_fork, NULL);
		pthread_mutex_init(philo[i].right_fork, NULL);
		philo[i].death = death;
		i++;
	}
	pthread_mutex_init(philo->death, NULL);
}
