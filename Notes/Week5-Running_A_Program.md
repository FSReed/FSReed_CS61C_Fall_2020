# Running A Program

Topic of this lecture:

![Topic](/Image/Week5/week5-19.png)

Abstraction of this lecture:

![Layer](/Image/Week5/week5-20.png)

Here's one thing to notice: We are mainly focusing on **Compiler, Assembler and Linker**, not the Loader because the loader is mainly discussed in Operating Systems. Take the courses like CS162 to further understand how it works.  

The menu of the note:
[TOC]

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

What a linker does is to take in Object code files and finally produce the executable code!

- To combine several object files into a single executable.
- The great thing about linking is that **it enables separate compiling**, which means the change of one file won't require the recompilation of the whole program. We just need to recompile this new file and link it with other existing `.o` files!

![Linking](/Image/Week5/week5-30.png)  

The steps of linking:  

![Steps of linking](/Image/Week5/week5-31.png)  

There are four types of addresses. Except the PC-Relative addresses, other 3 types always need to be reallocated. They are **Absolute FUnction Addresses**, **External Function Reference** and **Static Data Reference**.

What would linkers do?

- Linker knows the length of the text and data segment, and the ordering of text and data segment.
- Linker resolve references. First search for the reference in all **user's symbol tables**, if there's no matching reference, then it will search in the **library files**. It's very similar to using `printf` in C, we need to `#include <stdio.h>` as an "external library".
  - Same label in two files may cause conflicting symbol type.
- Linker calculates the absolute address of each label to be jumped to and each piece of data being referenced. That's the process of fixing the
- For **RV32**, linker assumes that the **first** text segment starts at the absolute address **0x10000**, which is a **64KB** space from 0x0.

### Remember this kind of file: `*.dll`?

- What we are talking about above is called **Statically-Linked Approach**.
![Statically-Linked](/Image/Week5/week5-32.png)
- The problem of this approach is it could be really slow to download the executable as the library grows larger because the library is also one part of the executable. In this case, an alternative comes out, named **Dynamic Linked library(DLL)**.
- By using DLL, once the library gets updated, all programs using this library will benefit. The idea is we don't need to include the library into the executable, we refer to this library during run-time.
- Some issues about DLL:
![Issues](/Image/Week5/week5-33.png)
![Linking at Machine Code Level](/Image/Week5/week5-34.png)

## Loader

Just put the summary of what a loader does. We won't go into details.(Learn it from CS162!)  

![Loader](/Image/Week5/week5-35.png)

## In Conclusion

![Conclusion](/Image/Week5/week5-36.png)
