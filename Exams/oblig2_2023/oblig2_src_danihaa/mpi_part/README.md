### MPI Parallel part

Similarly to the first oblig, make sure to run from the terminal, in the same directory as the `makefile`

```
make compile_mpi_parallel
```

And to run the executable, run the command 

```
make run_parallel nprocs=<number of proccesses>
```

**OBS:** notice that the number of processes to be used is an argument passed at runtime under the variable `nprocs`.