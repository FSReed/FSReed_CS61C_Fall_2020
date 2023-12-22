# RISC-V Instruction Representation

## Some Great Ideas

1. After the first program-stored computer, everything has a memory, since all instructions and data are stored in memory, everything has a memory address. Both **branches** and **jumps** use these.
   - C pointers are just memory addresses, they can point to anything in memory because of this.
   - One register keeps address of instruction being executed: **Program Counter(PC)**. This is basically a pointer to memory
   - Intel calls PC *instruction pointer(IP)*
2. Binary Compatibility.
   - Programs are distributed in binary form. **Programs are bound to specific instruction set!** Different ISAs are dominant in different domains, e.g. almost all PCs use x86 while most phones use ARM architecture.
   - New machines want to run old programs as well as programs compiled to new instructions, e.g., when we are updating our phones, we don't want to get all new applications and developers won't like this too.
   - This leads to **backward-compatible" instruction set evolving over time. Here's the example:
    ![Intel 8088](Image/Week5/week5-1.png)
3. Instructions as Numbers
   - Computers don't understand the string of assembly instructions. We need to translate them to binary.
   - RISC-V seeks simplicity: since data is in words, so make instructions 32 bits also.
   - One word is 32 bits, so we need to divide the instructions into some **fields**. Each field tells processor something about the instruction.
4. **Six Basic Types of Instruction Formats in RISC-V**
![6 Types](Image/Week5/week5-2.png)
In registers, we have 32 bits, and we need to use 5 bits to store which register it is(because there are 32 registers in total). How to arrange the other 27 bits?

## 1. R-format: Register-register arithmetic operations

First give the layout of R-format instructions:
![R-format Layout](Image/Week5/week5-3.png)

- **opcode** partially specifies what instruction it is. For R-format instructions, **opcode** is equal to **$0110011_{two}$**.
- **funct7 + funct3**: combined with **opcode**, these two fields describe what operation to perform. There are two questions:
  - We are using so many bits to specify a instruction, this seems to be redundant?
  - Why not put these 3 fields in a 17-bit space?
  They will be answered later.
- **rs1** & **rs2**: (**S**ource **R**egister)specifies the 1st/2nd register operand
- **rd**: (**D**estination **R**egister):specifies register which will receive the result of computation
- Recall we've mentioned before, there will be a 5-bit space in each register to specify which register it is, and **rs1, rs2, rd** will correspond to a specific register in this way.
- All instructions in R-format:
![R-format instructions](Image/Week5/week5-4.png)
- New instructions: **`slt` and  `sltu`**, it compares the values of registers **rs1** and **rs2**, and if the value in **rs1** is less than **rs2**, it sets the destination register to 1. Useful for comparisons, **`sltu`** is the unsigned version of it.
- Notice the `add` and `sub` instruction, they are using the same hardware, but the difference is we need to perform a signed version in `sub`, that what the `1` in **funct7** specifies. We can find that `sra` also need the signed extension. We've started the use of **signed version of operands** here.
