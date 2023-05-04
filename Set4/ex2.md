### Question 2
How will the performance, measured as number of FP operations per second,
change if the above loop is modified as follows? And why?
```
for (i=0; i<N, i+=stride)
A[i] = s*B[i];
```

### Answer

To load the element B[i] from main memory, a whole cache line is required. If the stride is one, we then get the maximum utilization of these alocated elements in cache. However, if we have a stride larger thatn one, it means that some of these elements will simply not be accesed and taking space effectively making the cache line smaller. For large N, for example, a stride of 2 will mean that we will on avarage have to load cache lines twice as much. Therefore we can say that the cache utilization and therefore performance is impacted by approximately $1/stride$.


### Question 2
#### b)The dumb matmul code is 

```
void mat_mul(double **A, double **B, double **C){
    double temp;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < p; j++){
            temp = 0;
            for (int k = 0; k < m; k++)
            {
                temp += A[i][k] * B[k][j];
            }
            C[i][j] = temp;
        }
    }
};
```
If the matrices are tiny, and the *cache* comports all matrix elements ($n*p + m*p + m*n < M$), given that cache lines are of size $L_c$, we will have $n*p / L_c$ writes and $(n*m + m*p)/L_c$ loads.

But if the matrices are large, then the cache elements don't "last" one whole external loop, and so the number of loads for B increases significantly. Indeed, since it is not accessed in a row-major way, it will require $m*p*n$ loads. Notice that for A and C the situation does not change because they are accessed in a row-major fashion.

#### c)

Before using loop unrolling, it is important to understand where the bottleneck is so that we unroll the correct matrix. Unrolling arrays uneccesarily can create unwanted register pressure. We know in this case that the bottleneck is matrix B.

By unrolling it, we will be making sure to access it in a row-major form, and in this case the ammount of loads that will be done will still be $(m*p)/L_c$ or at least closer to it, instead of $m*n*p$.

Quoting the solution material, **"If element $B[k][j]$ is at the start of a cache line then $B[k][j+1], B[k][j+2], B[k][j+3] ... B[k][j+Lc-1]$ will be loaded with that element. To increase the cache hits we must use these values before they are flushed."**