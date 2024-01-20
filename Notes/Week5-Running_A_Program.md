# Running A Program

Topic of this lecture:
![Topic](/Image/Week5/week5-19.png)
Abstraction of this lecture:
![Layer](/Image/Week5/week5-20.png)

## Interpretation and Translation

![All in one](/Image/Week5/week5-21.png)
![All in one](/Image/Week5/week5-22.png)

But sometimes, we need to interpret machine language because there will be different versions of ISA that programs are using.

- One way is to translate all the programs into the new machine code, but this is inconvenient.
- Another way is to keep the old version of executables and interpret them into the new version of machine code.

Translated/compiled code is almost always more efficient and has better performance. And what's important is that **translation helps to hide the program source from the user**.

## Compile

The overall picture about the steps of compiling and running a program:
![Overall](/Image/Week5/week5-23.png)
When we are using `gcc` in the past, if we don't add `-S` label, we will get an a.out file directly. With this label, we can get the `.s` file i.e. the assembly program.  
**Note:** the output may contain **pseudo instructions** like `mv x1, x2` and `ret`. And we won't further discuss how to compile in CS61C, take CS164 if you are interested.

## Assembler

The input is the assembly code file, and the output is **Object code** which contains **information tables**. Other things assemblers will do are:
![Assembler](/Image/Week5/week5-24.png)

- Assembler Directives:
  ![Directives](/Image/Week5/week5-25.png)
- Some Pseudo-Instruction-Replacement examples:
  - `mv t0, t1` to `addi t0, t1, 0`
  - `neg t0, t1` to `sub t0, zero, t1`
  - `not t0, t1` to **`xori t0, t1, -1`**, remember to sign-extend the immediates.
  - `la t0, str` to **`lui t0, str[31:12]` and `addi t0, t0, str[11:0]`**

Now here are some problems we need to handle:

- If we are branching to a label which occurs later than the current instruction, we can't tell the gap between the label and the instruction.
  ![Problem 1](/Image/Week5/week5-26.png)
  And the solution is:
  ![Solution 1](/Image/Week5/week5-27.png)
- If we are doing PC-Relative jumps and branches, it doesn't matter where we are moving this piece of code to because the offset between the current instruction and the label won't change.
- **If we are making references to the static data**, things will be different because these codes are no longer PC-Relative, we need the **32-bit absolute address** of the data.

In this case, we will build two tables:

- **Symbol Table**:
  ![Symbol Table](/Image/Week5/week5-28.png)
- **Relocation Table**: List of items whose address this file needs. This is like a to-do list for us, which stores what we need to fill in later when we finally **link** all files together. And this is exactly what **linkers** would do: to fix these items, like giving the absolute address of the static data.

Then here's the object file format:
![Object file format](/Image/Week5/week5-29.png)

## Linker
