# OS and VM intro

## What are we going to learn?

![Hierarchy](./Image/Week10/Week10-19.png)
![TODO](./Image/Week10/Week10-20.png)

## Operating System Basics

What does the core of the OS do?

- Provide **isolation**: each program would run in a little space, and won't know about other programs.
- Provide **interaction** with the outside world: each program would be able to interact with other devices like disks, network etc.
- **Memory translation**: Each program would try to access a virtual memory, and OS would give different maps of *virtual -> physical* memory to each program.
- **Privilege and protection**: The *running mode* of a processor should be split into at least two modes: *Supervisor* and *User*. And less privilege **cannot** change its **memory mapping**, but *supervisor* can change the memory mapping for any given program!
  - Changing mode could be done by saving different bits in some specific registers.
  - RISC-V also has another mode called *Machine* under supervisor but above user.
- **Trap and Interrupts**: We need a trap handler and something will be called by the supervisor mode to perform this function. We don't have to do this by an internal/external trigger, we can call the supervisor to do this for us.

## What happens at Boot?

- First, the CPU would execute the code starting from a preset memory address. The code would be read from the **Flash ROM** and be written into the memory pointed by the program counter.
  ![boot](./Image/Week10/Week10-21.png)
- Then:
  1. **BIOS**(Basic Input Output System): Find a storage device and load the first *sector* block of data. The data contains some important information called **BootLoader**.
  2. **BootLoader**: Load the *OS Kernel* into the memory and jump into it.
  3. **OS Boot**: Initialize services.
  4. **Init**: Launch an application that waits for input. That's an infinite loop!
  ![Boot](./Image/Week10/Week10-22.png)

## Operating System Functions (Better re-watch [this video](https://www.youtube.com/watch?v=NeGAhZzmCVg&list=PLnvUoC1Ghb7ziIlgNnQ24Gb6HBmLQO4T4&index=3) after going through VM and IO)

### Launching Applications

- Applications are processes for a CPU. Multiple processes would run simultaneously on a single core of CPU so OS needs to implement this.
- Applications are started by *another process* -> **Shell** calling an OS routine.
  - Loads executable file from the disk
  - Set **argc** and **argv**, jump into main.
  - Shell will wait for main to return.

### Supervisor Mode

- If an application goes wrong, the whole system may crash down. How to prevent this?
- OS needs to constrain the resource one application can access (like devices and memory).
- Out of supervisor mode, the process can only access *a subset of instructions and memory*.
- The error in supervisor mode is often catastrophic.

...Too many terminologies. Check the video in the title and learn them slowly in the following lectures.
