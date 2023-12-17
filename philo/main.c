/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:21:49 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/09/15 11:50:10 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] || s2[j])
	{
		if (s1[i] == s2[j])
		{
			i++;
			j++;
		}
		else
			return (1);
	}
	return (0);
}

void	ft_free(t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philo[i].last);
		pthread_mutex_destroy(&philo[i].total);
		i++;
	}
	pthread_mutex_destroy(philo->death);
	free(forks);
	free(philo);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death;
	int				check_dead;

	if (!ft_arg_check(ac, av))
		return (1);
	if (ft_atol(av[1]) == 0)
		return (1);
	check_dead = 0;
	philo = malloc(sizeof(t_philo) * ft_atol(av[1]));
	forks = malloc(sizeof(pthread_mutex_t));
	if (!philo || !forks)
		return (1);
	if (ft_arg_init(philo, ac, av, &check_dead))
		return (1);
	ft_mutex_init(philo, forks, &death);
	ft_create_thread(philo);
	ft_free(philo, forks);
	return (0);
}
