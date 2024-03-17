# Virtual Memory II(Lecture 30)

- There are too few examples in this lecture so [wikipedia](https://en.wikipedia.org/wiki/Page_table) might helps a lot when learning this.  
- What's more, here's [a great answer about table walk](https://cs.stackexchange.com/questions/102834/what-is-happening-during-table-walk).
- Check the [PDF](./CS356Unit9_VM.pdf) for more detailed explanation.

## Hierarchical Page Tables

- If a page table has $2^{20}$ entries which contains 4 bytes, the size of a single page table will be 4 MiB. What if there are like **256 processes** running simultaneously? The total size of the page tables will be **1GiB**!
- That's just too big. How can we make the size of the page tables reasonable?

1. Increase the **page size**. If a single page size doubles, the entries in the page tables will reduce by half. But the waste of the memory will become worse.
2. Use **hierarchical page tables**. The idea is to add two (or more) layers of page tables between the virtual address and the physical address. For example, we use 20 bits as the page table entries, but now we split them into 2 parts with each has 10 bits. Then use the first (higher) 10 bits to find the position in the **first** page table, then use the other 10 bits and the offset to locate the physical memory.
   ![HPT](./Image/Week11/Week11-11.png)

## Translation Lookaside Buffers(转译后备缓冲器/TLB)

With the hierarchical page table, we can save a lot of space. But each layer in the HPT means another trip to the memory, which is very slow. If the address is of 64 bits, there will be 4 layers which causes 5 access to the memory for each instruction. No way!  
So we will use something same with *cache* (conceptually) to solve the problem, which is called a **TLB**.  

![TLB](./Image/Week11/Week11-12.png)

- TLB acts just like a cache.
- A typical TLB has 32-128 entries and usually **full-associative**.
  ![TLB](./Image/Week11/Week11-13.png)
- Split the Virtual Page Number into 2 parts, just like what we did in *cache*. Use the index to locate the TLB, and compare the TLB tag and the tag in the VPN.
  ![TLB](./Image/Week11/Week11-14.png)
- We use TLB to get the Physical Address, so TLB should come before the cache in the datapath.
  ![TLB & cache](./Image/Week11/Week11-15.png)

## TLB in Datapath

![TLB in Datapath](./Image/Week11/Week11-16.png)
![Translation](./Image/Week11/Week11-17.png)
![COntext Switching](./Image/Week11/Week11-18.png)

## *Intel i7 Page System*

What's the TLB and the hierarchical page table looks like in 64-bit system? Here's the summary of the **i7 address translation**.

![i7](./Image/Week11/Week11-19.png)

## Virtual Memory Performance

### Comparison between Cache and TLB

![Comp](./Image/Week11/Week11-20.png)

- In TLB, the whole page would be stored in each line. In cache, each line contains $block size$ bytes.
- In virtual memory, the **penalty of writing through to the disk** is too high. So in virtual memory,  we only write back.

In general, we just add another level called virtual memory *under the main memory*. We can access the **AMAT of the virtual memory** by adding up *the AMAT to the main memory* and *the penalty of accessing the disk*.  
But accessing the disk can be much slower than accessing the memory:

![diskAccess](./Image/Week11/Week11-21.png)

I thought increasing the hit rate to the main memory can easily handle this problem. But I was too naive. It turns out that even we increase the hit rate to $99.9%$, the AMAT can still be about **80 times slower** than the AMAT without paging! To get the similar performance, we need to cut down the miss rate to under 0.001%!
You can check the last 2 slides of [the lecture PDF](https://inst.eecs.berkeley.edu/~cs61c/fa20/pdfs/lectures/lec30.pdf).
