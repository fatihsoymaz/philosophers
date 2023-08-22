#include "philosophers.h"

void	philo_control(int argc, char **argv, t_philo *philo)
{
	philo->nop = ft_atoi2(argv[1]);
	philo->time_to_die = ft_atoi2(argv[2]);
	philo->time_to_eat = ft_atoi2(argv[3]);
	philo->time_to_sleep = ft_atoi2(argv[4]);
	if (argc == 6)
		philo->max_eat_count = ft_atoi2(argv[5]);
	else
		philo->max_eat_count = -1;

	if (philo->nop < 1 || philo->nop > 200 || philo->time_to_die <= 0
		|| philo->time_to_eat <= 0 || philo->time_to_sleep <= 0)
	{
		printf("Invalid arguments\n");
		return ;
	}
}