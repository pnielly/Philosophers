# Philosophers

The basics of multi-threading, mutex and semaphores, through <a href="https://en.wikipedia.org/wiki/Dining_philosophers_problem">the dining philosophers problem</a>.</br>
N philosophers are around a table with N forks. They need two forks to eat.</br>
If they don't eat before <time_to_die>, they die. </br>
Once they ate for <time_to_eat>, they sleep for <time_to_sleep> </br>
If you want, you can stop the simulation once each philosophers ate a certain number of times (last arg, optionnal)

Each philosopher is a thread.

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)

## Installation

In the root of the repo, type:

```bash
#Solving with mutex
cd philo && make
```
or
```bash
#Solving with semaphores
cd philo_bonus && make
```

## Usage

Once the binary is compiled, type:
```python
./[binary] #_of_philosophers time_to_die time_to_eat time_to_sleep [#_times_each_philosopher_must_eat]
```

## Additional feature
For more logs during the execution of the binary, use this command to compile:
```bash
make more
```

