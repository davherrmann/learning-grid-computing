# learning-grid-computing

## Continuously running the files
`fswatch -o ./2-1.c | xargs -n1 sh -c "clear && gcc 2-1.c && ./a.out"`

## POSIX Threads
### API
- `pthread_exit(void *retval)` terminates the current thread, `*retval` points to the return value of the original thread function
- `pthread_join(pthread_t, void **retval)`
