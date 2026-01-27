
# ARGUMENTS:
1. number_of_coders (also the number of dongles available)

2. time_to_burnout (ms)
 	if a coder doesn't start compiling in time_to_burnout 
 	they burnout and the simulation ends

3. time_to_compile (ms)
 	the time it takes to compile a code segment (holds 2 dongles)

4. time_to_debug (ms)
	the time it takes to debug a code segment (no dongles needed)

5. time_to_refactor (ms)
	the time it takes to refactor a code segment (no dongles needed)

6. number_of_compiles_required
	if all coders complete number_of_compiles_required
	the simulation ends successfully

7. dongle_cooldown 
	after release of dongles, a coder must wait dongle_cooldown
	before being able to acquire dongles again

8. scheduler
	- FIFO (first in first out) first come first served
	- EDF (earliest deadline first) = last_compile_start + time_to_burnout

## Reminder: 
All arguments are mandatory. Reject invalid inputs such as negative numbers, non-integers, or a scheduler other than FIFO or EDF.


# EXTERNAL FUNCTIONS
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


# RULES
- If there is only one coder, there should be only one dongle on the table.
  The coder will never be able to compile and will eventually burn out.

- Coders are seated around a circular table
- Coders are threads (pthread_create)
- Dongles are mutexes (pthread_mutex_t)
- Use pthread_cond_t for scheduler implementation
- When multiple coders request a dongle, the scheduler decides who gets it

- Each coder has a dongle on their left and right
- To compile, a coder must acquire both dongles

- Only one coder can hold a dongle at any given time

- Coders alternate between compiling, debugging, and refactoring

- After releasing dongles, coders must wait for dongle_cooldown before
  attempting to acquire dongles again

- There is a **monitor** thread that checks for burnout conditions
- Logging must be serialized so that two messages never interleave 
  on a single line (use a mutex to protect output).

- You must implement a priority queue (heap) for FIFO/EDF scheduling 
  manage coder access to dongles.


# LOGS 
- `[timestamp_in_ms] <coder_no> has taken dongle`
- `[timestamp_in_ms] <coder_no> is compiling`
- `[timestamp_in_ms] <coder_no> is debugging`
- `[timestamp_in_ms] <coder_no> is refactoring`
- `[timestamp_in_ms] <coder_no> burned out (display time <10ms after burnout)`
- `[timestamp_in_ms] number of compiles reached`
	
## Precision requirement:
Burnout logs must be displayed within 10 ms of the actual burnout time. 
Allow a minimal tolerance when testing, hardware and OS scheduling may slightly
affect measured timings

## Timing consideration: 
To reduce hardware impact on performance measurements, consider using CPU usage 
time instead of real-time clock when feasible. However, for this project, 
real-time measurements using gettimeofday() are acceptable and recommended for simplicity.

# ERRORS:
- Invalid number of arguments
- Invalid argument type
- Invalid argument value
- Thread creation failure
- Mutex initialization failure

# SIMULATION END CONDITIONS:
- A coder burns out
- All coders complete the required number of compiles

# CODER BEHAVIORS:
- Acquiring dongles (2 dongles needed)
- Compiling (holds 2 dongles)
- Releasing dongles
- Debugging (no dongles needed)
- Refactoring (no dongles needed)
- Cooling down after releasing dongles



