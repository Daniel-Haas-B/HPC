### Question 2
The dot-product between two arrays can be computed by a for-loop:
```
double s = 0.;
for (i=0; i<N; i++)
    s = s + A[i]*B[i];
```

Suppose an imaginary 1GHz CPU, which can do one load (or store), one multiplication and one addition per clock cycle. We assume that loop counting and branching come at no cost. The memory bus can transfer 3.2GBytes/sec. Assume that the latency to load one cache line from main memory is 100 clock cycles, and that four double precision numbers fit into one cache line.
(a) What is the expected performance for this loop kernel without data prefetching?
(b) Assuming that the CPU is capable of prefetching (loading cache lines from memory in advance so that they are present when needed), what is the required number of outstanding prefetches the CPU has to sustain in order to make this code bandwidth-limited, instead of latencylimited
(c) How would this number change if the cache line were twice or four times as long?
(d) What is the expected performance of the dot-product calculation if we can assume that prefetching hides all the latency?

### Answers

(a) Here we should notice that given there are two arrays, two cache lines need to be fetched for each loop entry. This already implies a 200 clock cycle latency. This is 200 ns because the CPU is a 1Ghz one, meaning 1 billion cycles per second, or one nano second per cycle.

Furthemore, each cache line fits 4 doubles, meaning 8*4 = 32 bytes.

So the time for one loop due to memory would be this number devided by bandwith, time two, which is

$$
\frac{2 * 32 Bytes}{3.2GBytes/sec} = 20 ns
$$

So memory-wise this code already takes 220 nanoseconds. However, to measure perfomance we nees to divide this by the number of flops. The solutions says that  after loading the cache lines, there will be data in the cache to complete four multiplications, and four additions, for a total of 8 flops, but i don't understand how.

(b) 

(c) if the cache line was bigger, than the  time for grabing all the memory would be larger, but in the formula for the prefetches necessary
$$
P = 1 + \frac{T_\ell}{L_c/B}
$$

the second term would than be smaller, so we would need a smaller number of prefetches. 



