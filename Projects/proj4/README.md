# numc

As I can't use the HIVE machine, I need to configure the environment on my own machine.  

- I use a Virtual Machine on Digital Ocean using image Ubuntu20.04.
- Do `apt install python3.6` first.
- `apt install python3.6-dev` to get `Python.h`.
- `apt install libcunit1 libcunit1-doc libcunit1-dev`

It seems to be fine if you don't modify `Makefile`, but I don't know why. `make` works anyway, that's enough.

## Task 1

- At first, I didn't assume the `result` matrix is valid. What I did is `allocate_matrix(&result, ...)` which **really cause me big trouble**. Because I'm allocating memory for the *local variable* `*result`! Then I treat the `result` as a valid matrix.
- In `mul_matrix`, I forget to initialize the `result` matrix's entries to all 0.
- Use a "stupid" way to copy the previous `result` into `tmp` in `pow_matrix`. Is there any clever way to implement `pow_matrix`?

## Task 2: Setup Numc

Only need to modify the `setup.py` using 2 function calls. If it's done properly:

- Enter the Virtual Environment
- Type `python3.6` to enter python

The output of python should be `CS61C Fall2020 Project 4: numc imported!`  

## Task 3

