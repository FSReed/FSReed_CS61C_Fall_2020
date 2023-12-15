# Week2: C Intro

## C memory pools(Lecture 8)

[Video Link Here](https://www.youtube.com/watch?v=Keducx5bp-g&list=PLnvUoC1Ghb7zmY1Hi_SC3xPXjwGxNafmn&index=4)

C has 3 different pools of memory:

- Static storage: Global variable storage.
- The Stack: Local variables.
- The Heap: (Dynamic malloc storage): data lives until de-allocated by programmer. **Not the heap data structure!!!**

## Normal C Memory Management(Lecture 8)

A program's address space contains 4 regions. From the top to the bottom, they are: **stack, heap, static data and code**. Stack grows from top to bottom and heap grows from bottom to top, which means the data in stack and heap seem to reach towards each other.
Notes:

- *The code block is loaded when the program starts. Never change.*
- *The OS will prevent stack and heap over-crossing each other. See in CS162.*

## The Heap(Dynamic Memory)

The memory allocation in the heap is tricky.
**Important:** Each block of memory is preceded by a header that has 2 fields:

- size of the block
- a **pointer to the next block**

All **free** blocks are kept in a circular linked list, the pointer field is unused in an allocated block.
Then consider malloc() function. It might be really slow to search over all the free blocks. So how does malloc() really works?
There are three wys to find free space when given a request:

- First fit: find first one that's free
- Next fit: same as first fit, but remembers where left off.
- Best fit: finds most "snug" free space

Need to do some trade-offs, but remember: **malloc() handles free spaces as lists!**

Heap data is **biggest** source of bugs in C codes.
