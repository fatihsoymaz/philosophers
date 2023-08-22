#include "philosophers.h"

unsigned long long get_timestamp_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned long long)(tv.tv_sec) * 1000 + (unsigned long long)(tv.tv_usec) / 1000;
}

void print_message(t_philo *philosopher, const char *message) {
    unsigned long long time = get_timestamp_ms();
    pthread_mutex_lock(&philosopher->print_mutex);
    if (philosopher->philosophers_alive) {
        printf("%llu %d %s\n", time, philosopher->id, message);
    }
    pthread_mutex_unlock(&philosopher->print_mutex);
}

void eat(t_philo *philosopher) {
    int left_fork = philosopher->id;
    int right_fork = (philosopher->id + 1) % philosopher->nop;

    pthread_mutex_lock(&philosopher->forks[left_fork]);
    print_message(philosopher, "has taken a fork");
    
    // Special case for philosopher_count = 1
    if (philosopher->nop == 1) {
        print_message(philosopher, "died");
        philosopher->philosophers_alive = false;
        exit(1);
    }
    
    pthread_mutex_lock(&philosopher->forks[right_fork]);
    print_message(philosopher, "has taken a fork");

    print_message(philosopher, "is eating");
    usleep(1000);
    philosopher->eat_count++;

    pthread_mutex_unlock(&philosopher->forks[right_fork]);
    pthread_mutex_unlock(&philosopher->forks[left_fork]);
}

void sleep_and_think(t_philo *philosopher) {
    print_message(philosopher, "is sleeping");
    usleep(philosopher->time_to_sleep * 1000);
    print_message(philosopher, "is thinking");
}

void *philosopher_thread(void *arg) {
    t_philo *philosopher = (t_philo *)arg;
    unsigned long long last_meal_time = get_timestamp_ms();
    
    while (1) {
        eat(philosopher);
        if (get_timestamp_ms() - last_meal_time >= (unsigned long long)philosopher->time_to_die)
        {
            print_message(philosopher, "died");
            philosopher->philosophers_alive = false;
            exit(1);
        }
        
        last_meal_time = get_timestamp_ms();
        sleep_and_think(philosopher);
        
        if (philosopher->max_eat_count != -1 && philosopher->eat_count >= philosopher->max_eat_count) {
            break;
        }
    }
    
    return NULL;
}


int main(int argc, char *argv[]) {
    if (argc < 5 || argc > 6) {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return 1;
    }

    t_philo philo;
    philo_control(argc, argv, &philo);
    
    philo.philosophers_alive = true;
    philo.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo.nop);

    if (philo.forks == NULL) {
        printf("Memory allocation error\n");
        return 1;
    }

    pthread_mutex_init(&philo.print_mutex, NULL);

    for (int i = 0; i < philo.nop; i++) {
        pthread_mutex_init(&philo.forks[i], NULL);
    }

    pthread_t threads[philo.nop];

    for (int i = 0; i < philo.nop; i++) {
        t_philo *philo_ptr = (t_philo *)malloc(sizeof(t_philo));
        if (philo_ptr == NULL)
            return 1;
        *philo_ptr = philo;
        philo_ptr->id = i + 1;
        philo_ptr->eat_count = 0;

        pthread_create(&threads[i], NULL, philosopher_thread, philo_ptr);
    }

    for (int i = 0; i < philo.nop; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < philo.nop; i++) {
        pthread_mutex_destroy(&philo.forks[i]);
    }
    pthread_mutex_destroy(&philo.print_mutex);

    free(philo.forks);
    
    return 0;
}