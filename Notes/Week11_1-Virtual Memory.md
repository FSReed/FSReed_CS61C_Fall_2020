# Virtual Memory (Lecture 29-30)

## Virtual Memory Concepts

Multiple programs will run simultaneously on a machine, but the physical memory is finite. To let each program decide which piece of memory it will use on its own is impossible because there are tons of programs and tons of different computers with different memory hierarchy.  
**Virtual Memory** provides a **map** from the virtual address one program acquired to the physical address in the hardware.

- It provides the program an illusion of a very large memory
- It provides the ability to run programs **larger than the primary memory**!
- It hides differences between different computer configurations.
- Nowadays, it's more important for protection (for accidentally or maliciously overwritten cases).
  ![Hierarchy](./Image/Week11/Week11-1.png)
- Library Analogy:
  - In a library, the title of the book is a *virtual address*.
  - The call number of a book is the *physical address*.
  - Card catalogue is *page table*, mapping virtual address to physical address.
  - On each card, there's a valid bit showing whether this book is in the "main memory" or "on the disk".
  - On each card, there will be an *access right*.

## Physical Memory and Storage

Introduce what memory and disks look like and their difference. Check the [course video](https://www.youtube.com/watch?v=MJwBmN8L2Lo&list=PLnvUoC1Ghb7zlukNrB3PYYnoRbedKV2_-&index=2).

![Memory](./Image/Week11/Week11-2.png)
![SSD&HDD](./Image/Week11/Week11-3.png)

- Memory is **volatile**, which means when its power is turned off, the memory will lose the data in it.
- Disks are **non-volatile** because the data can stay in them forever even the power is turned off. Note that *SSD*s use transistors to store the data, so they are less reliable than mechanical hard drives.

![SSD](./Image/Week11/Week11-4.png)

## Memory Manager

- In a *"bare metal"* machine, `lw` and `sw` instructions are directly accessing the physical address. This may cause corrupting the OS data structure.
- We should "translate" these addresses by passing them into a mechanism controlled by the OS to the physical memory on the DRAM.
- The **Memory manager** should manage the mapping from the virtual address to the physical address. COnceptually the memory manager would allocate a portion of the physical memory for a program, and this subset of memory don't have to be contiguous.
- As we are running more and more programs, the DRAM will finally run out of space. In this case, the memory manager will **swap the memory to the disk**, and the DRAM performs like a **cache** for the disk!
