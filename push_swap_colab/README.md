# PUSH_SWAP

C program called `push_swap` which calculates and displays on the standard
output the minimum number of operations requiered to sort a list of integers 
given as arguments, made of Push swap language operations. 

**Operations**
- **sa**, 	(swap a): Swap the first two elements at the top of stack a. Do 
  			nothing if there is only one or no elements.

- **sb**	(swap b): Swap the first two elements at the top of stack b. Do 
			nothing if there is only one or no elements.

- **ss**:	sa and sb at the same time.

- **pa**	(push a): Take the first element at the top of b and put it at the 
			top of a. Do nothing if b is empty.

- **pb**	(push b): Take the first element at the top of a and put it at the 
			top of b. Do nothing if a is empty.

- **ra**	(rotate a): Shift up all elements of stack a by one. The first 
			element becomes the last one.

- **rb**	(rotate b): Shift up all elements of stack b by one. The first 
			element becomes the last one.

- **rr**:	ra and rb at the same time.

- **rra**	(reverse rotate a): Shift down all elements of stack a by one. The 
			last element becomes the first one.

- **rrb**	(reverse rotate b): Shift down all elements of stack b by one. The
			last element becomes the first one.

- **rrr**:	rra and rrb at the same time.

## NAME
> push_swap

## LIBRARY


## SYNOPSIS

```bash
$ ./push_swap [--bench] [SELECTOR] ARGS, ...
```

## DESCRIPTION

### SELECTOR
- `--simple`,	implements bubble sort, with $O(n^2)$ complexity

- `--medium`,	implements bucket sort, with $O(n\sqrt{n})$ complexity

- `--complex`,	implements merge sort, with $O(n\ \log(n))$ complexity

- `--daptive`,	implements adaptive sort based on the `disorder`. This is 
				the default behaviour if no selector is given


## EXAMPLE

Using an optional flag (ex: `--simple`)

```bash
$ ./push_swap --simple 3 2 1
ra
sa
```

## BENCHMARKING

Using the `--bench` flag. The output is sent to `stderr`

```bash
$ ./push_swap --bench --simple 3 2 1
[bench] disorder: 100.0%
[bench] strategy: Simple
[bench] total_ops: 2
[bench] sa: 1  sb: 0  ss: 0  pa: 0  pb: 0
[bench] ra: 1  rb: 0  rr: 0  rra: 0  rrb: 0  rrr: 0
```

