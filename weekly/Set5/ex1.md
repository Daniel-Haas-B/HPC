## 1) Calculating code ballance of loops
A, B and y contain double precision (8 bytes). 
Code ballance is deffined as 

$$
B_c = \frac{\text{data traffic [words]}}{\text{Flops}}
$$

### a) Dense matrix multiplication 

```
for (j=0; j<N; j++)
    for (i=0; i<N; i++)
        y[j] += A[j][i]*B[i];
```

Here we have $2N^2$ flops. Assuming all arrays are loaded form memory, we then deal with a total traffic of $3* N^2 * 8$ bytes = $3* N^2$ words. Therefore

$$
B_c = \frac{3N^2}{2N^2} =  1.5 \text{Words/Flops}
$$

**Here I disagree with the solutions**. It is said that B will not fit in cache and therefore inccur in N elements loaded N times. On the other hand, y is said to stay in register the whole time, but they have the same size... 

### b) Vector Form

```
double s = 0.;
for (i=0; i<N; i++)
    s += A[i]*A[i];
```

$$
B_c = \frac{N}{2N} =  0.5 \text{Words/Flops}
$$

### c) Scalar product

```
double s = 0.;
for (i=0; i<N; i++)
    s += A[i]*B[i];
```

$$
B_c = \frac{2N}{2N} =  1 \text{Words/Flops}
$$

### d) Scalar product with indirect access

```
double s = 0.;
for (i=0; i<N; i++)
    s += A[i]*B[K[i]];
```


**If the elements of K[i] are sequential:**
$$
B_c = \frac{2.5N}{2N} =  1.25 \text{Words/Flops}
$$

Because every index of B will be a new one. However, suppose that K[i] elements are all the same. In this case, we have 0.5 words from the K[i] load, but they will always inccur in B fetching the same element, and therefore B access is negligible. 

So for the case where K[i] elements are randin, things also deppend if the next random index will point to an elements that was fetched from the last cache line load. In the worst case scenario, where every new random index will point to an element in a new line of memory, then for each element we need to bring actually all the other. The solutions here says that the code ballance is 

$$
B_c = \frac{N + N/2 + 8N}{2N} = 4.75
$$

But I have no idea where this 8 came from.