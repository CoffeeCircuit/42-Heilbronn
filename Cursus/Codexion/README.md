*This project has been created as part of the 42 curriculum by abalcu*

# Description

This project simulates a multi-threaded environment where coders (threads) 
compete for limited resources (dongles, represented by mutexes) to compile code 
segments. Coders are seated around a circular table, each requiring two dongles 
to compile. The simulation enforces strict timing and scheduling rules,
including burnout conditions if coders fail to start compiling within a 
specified time. The scheduler (FIFO or EDF) manages access to dongles, and a 
monitor thread oversees coder states to ensure proper synchronization and 
logging.

Key features:
- Coders alternate between compiling, debugging, and refactoring.
- Dongle acquisition is managed by a priority queue for FIFO/EDF scheduling.
- Burnout and completion conditions end the simulation.
- Logging is serialized to prevent message interleaving.
- Thread synchronization uses mutexes and condition variables.

The implementation is in the coders/ directory and follows the requirements.

# Instruction

## How to Run

1. Build the project:
	 - Navigate to the `coders/` directory and run `make`.
2. Execute the simulation:
	 - Run the compiled binary with the required arguments:
		```bash
		./codexion <number_of_coders> <time_to_burnout> <time_to_compile> 
		<time_to_debug> <time_to_refactor> <number_of_compiles_required> 
		<dongle_cooldown> <scheduler>
		```
	 - Example:
		 `./codexion 5 800 200 100 150 3 50 FIFO`
3. All arguments are mandatory. Invalid inputs will result in a usage message.

## Arguments

- number_of_coders: Number of coder threads and dongles.
- time_to_burnout: Max time (ms) before a coder must start compiling.
- time_to_compile: Time (ms) to compile (requires 2 dongles).
- time_to_debug: Time (ms) to debug (no dongles needed).
- time_to_refactor: Time (ms) to refactor (no dongles needed).
- number_of_compiles_required: Compiles needed for successful simulation end.
- dongle_cooldown: Cooldown (ms) after releasing dongles before reacquisition.
- scheduler: FIFO or EDF (Earliest Deadline First).

## External functions used

- pthread_create, 
- pthread_join, 
- pthread_mutex_init,
- pthread_mutex_lock,
- pthread_mutex_unlock, 
- pthread_mutex_destroy,
- pthread_cond_init,
- pthread_cond_wait, 
- pthread_cond_timedwait,
- pthread_cond_broadcast,
- pthread_cond_destroy, 
- gettimeofday, 
- usleep, 
- write,
- malloc, free,
- printf, 
- fprintf, 
- strcmp, strlen, atoi, memset

# Resources

- POSIX threads (pthreads) documentation.
- Man pages for: pthread_create, pthread_mutex, pthread_cond, gettimeofday,
- [HPC - POSIX Threads Programming](https://hpc-tutorials.llnl.gov/posix/) (archived)
- [YoLinux - POSIX thread (pthread) libraries](https://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html)
- Video reources: [Unix Threads in C](https://youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&si=Ap6CS8ZICSdDo5Hu)


# Blocking cases handled

- Only one coder and one dongle: Coder will never compile and will burn out.
- Invalid arguments: Negative values, non-integers, or unsupported scheduler 
  type are rejected.
- Thread creation or mutex initialization failure: Simulation aborts with error.
- Burnout: If a coder fails to start compiling within time_to_burnout, 
  simulation ends.
- All coders complete required compiles: Simulation ends successfully.

# Thread synchronization mechanisms

- Mutexes (`pthread_mutex_t`) are used to represent dongles and 
  serialize logging output.
- Condition variables (`pthread_cond_t`) are used for scheduler 
  coordination (FIFO/EDF).
- Each coder must acquire two dongles (mutexes) before compiling.
- Priority queue (heap) manages scheduling for dongle access.
- Monitor thread checks for burnout and simulation end conditions.
