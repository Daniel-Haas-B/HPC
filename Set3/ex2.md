### Question 2
The dot-product between two arrays can be computed by a for-loop:
```
double s = 0.;
for (i=0; i<N; i++)
    s = s + A[i]*B[i];
```

Suppose an imaginary 1GHz CPU, which can do one load (or store), one multiplication and one addition per clock cycle. We assume that loop counting and branching come at no cost. The memory bus can transfer 3.2GBytes/sec. Assume that the latency to load one cache line from main memory is 100 clock cycles, and that four double precision numbers fit into one cache line.
(a) What is the expected performance for this loop kernel without data prefetching?
(b) Assuming that the CPU is capable of prefetching (loading cache lines from memory in advance so that they are present when needed), what is the required number of outstanding prefetches the CPU has to sustain in order to make this code bandwidth-limited, instead of latencylimited?
(c) How would this number change if the cache line were twice or four times as long?
(d) What is the expected performance of the dot-product calculation if we can assume that prefetching hides all the latency?

### Answers

(a) Each entry of the loop does two operations, two loads, and a store. This cpu can make one load, one multiplication and one addition per clock cycle. This means each loop entry takes $5/4$ of a clock cycle. Consequently, this loop has performance of $(5/4) \frac{flops}{cycle* loop} * 1 GHz$  

