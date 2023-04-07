# Philosophers

This 42 school's project aims to simulate a problem known as the "Dining Philosophers" problem : A group of philosophers sit around a circular table, and there is a large plate of spaghetti in the center. The philosophers can either be eating, thinking, or sleeping.

## Overview

The program must adhere to the following rules:

* Global variables are not allowed.
* Each program must take the following arguments:

       * number_of_philosophers: the number of philosophers and forks on the table.
       * time_to_die (in milliseconds): if a philosopher has not started eating within time_to_die milliseconds after the beginning of their previous meal or since the start of the simulation, they die.
       * time_to_eat (in milliseconds): the time that a philosopher takes to eat. During this time, the philosopher must hold onto both forks.
       * time_to_sleep (in milliseconds): the time that a philosopher spends sleeping.
       * number_of_times_each_philosopher_must_eat (optional): if all the philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation ends. If this argument is not specified, then the simulation ends when a philosopher dies.
* Each philosopher is assigned a number between 1 and number_of_philosophers.
* Philosopher number 1 is sitting next to philosopher number number_of_philosophers. The other philosophers follow this logic: philosopher number N is sitting between philosopher number N - 1 and philosopher number N + 1.

In addition, the program must follow these rules:

* Any change of state for a philosopher must be formatted as follows:

        * timestamp_in_ms X has taken a fork
        * timestamp_in_ms X is eating
        * timestamp_in_ms X is sleeping
        * timestamp_in_ms X is thinking
        * timestamp_in_ms X died
* Replace timestamp_in_ms with the current timestamp in milliseconds, and X with the philosopher's number.
* No messages should be mixed with another message.
* There should be no more than 10 milliseconds between a philosopher's death and the message announcing their death.
* The philosophers must not die.
* The program must be written in C and must not have any data races or leaks.

## How to Run

To run the program, navigate to the project directory and run the following command:

```
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## Output

The program will output messages in the format specified above for each change in a philosopher's state. The program will run until a philosopher dies or until all philosophers have eaten the required number of times (if specified).

![Screenshot from 2023-04-07 19-35-09](https://user-images.githubusercontent.com/31923839/230652347-79a1016c-2ab4-4a3c-86bc-be30392576a3.png)
