# Single-Cycle CPU Control Design

## CPU Structure Recap

We've already completed the design of datapath. Do you remember the other component of CPU? **Control**!

![Recap](./Image/Week8/Week8-1.png)

In fact, we've already included the Control Unit into the structure of datapath. Here they are:

![Control Unit](./Image/Week8/Week8-2.png)

So the control unit will set up the multiplexers and other configuration options in the datapath to execute different instructions. Let's go through some instructions to see how it works.

## Instruction Timing

**One important thing to know**: The decoding of an instruction and getting the output of $PC + 4$ will almost happen simultaneously. Not the same time, but the time cost is comparable.  
The time cost is marked in green in the picture below. But why is that? Isn't accessing memory much lower than doing combinational logics?  
This will be explained in module `Cache`.

![Add](./Image/Week8/Week8-3.png)

Another instruction: `lw`:

![lw](./Image/Week8/Week8-4.png)

Design Clock Frequency:

![Clk Frequency](./Image/Week8/Week8-5.png)

## Control Logic Design

![Control](./Image/Week8/Week8-6.png)

### ROM (Read Only Memory)

It's like copying a whole truth table down to the ROM. For each unit in ROM, it will only represent one instruction.

![ROM](./Image/Week8/Week8-7.png)

*In my opinion, this approach may cause a huge waste of space.* 

### Logic Design

Considering each output of the Control Logic, and design the logic of each output instead of each instruction.

![Logic](./Image/Week8/Week8-8.png)

## Conclusion

We've made Hardware and Software contact!

![Accomplishment](./Image/Week8/Week8-9.png)
![So far](./Image/Week8/Week8-10.png)
