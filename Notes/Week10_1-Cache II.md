# Cache II (Lecture 26-27)

## Multi-Word Block Cache

![Multi-Word Block](./Image/Week10/Week10-1.png)

We are mainly taking advantage of the **spatial locality** because multiple words would be loaded to cache when accessing one address. But actually we are also taking advantage of the **temporal locality** because the latest access would always be stored in the cache.  

## How to Write with Cache?

We know how to access memory through the cache, but how to write to memory? Assume that we keep **loading then saving** all the time, do we really need to go to memory every time we want to save the data?  
The answer is no. The idea is **to update the word in cache block** without writing back to memory. If the content of this block is going to be changed again, we will write the data in this block into the memory.  

![Write](./Image/Week10/Week10-2.png)

- The content in memory and cache could be different!
- Another **dirty bit** is needed to indicate this block in cache should be written back to memory when necessary.

## Block Size Trade-offs

Larger block size works well for **sequential** array access. But there are drawbacks for larger block size:

- Larger block size means larger **miss penalty**.
- Larger block size means less block, which leads to a higher **miss rate**.

Consider an extreme example: only one huge block! We are likely to continuously load data into cache and discard data before using it again.

![Tradeoff](./Image/Week10/Week10-3.png)

## Three types of miss

- **Compulsory misses**: When program begins, the cache doesn't contain any data of the program so the misses are bound to occur. Every block **in the memory** will have one compulsory miss.
- **Conflict misses**: Big problem in Direct Mapped Caches. Two pieces of data in the memory (which happen to map to the same block in the cache) may keep overwriting each other. How to solve this?
  - Using larger cache. (Fails at some point)
  - Let multiple memory blocks fit in the same cache index? Using **Full Associative Cache**.
- **Capacity misses**: misses that occur because cache has limited size.

### Full Associative Cache

The idea is: sometimes different block in memory may map to the same block in cache. So in FAC, all blocks in memory can go anywhere in the cache. The index of the cache would be discarded. Now only **tag** and **offset** exists.  
But every time searching the cache would be expensive because we need to compare the target address to **all tags** in the cache at the same time. Assume the block size of the cache is 16KB, then 16KB comparators are needed. That's infeasible!  

![FAC](./Image/Week10/Week10-4.png)

- There's **no conflict misses** in FAC, but it's too expensive.
- **Capacity miss** is the primary type of miss in FAC.

### How to category them?

![Category](./Image/Week10/Week10-5.png)

- From infinity-size to finite-size, the differences are **capacity misses**.
- From **full associative** to **finite associative**(**between** full associative and direct mapped), the differences are **conflict misses**.
