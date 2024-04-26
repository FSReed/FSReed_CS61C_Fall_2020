# numc

As I can't use the HIVE machine, I need to configure the environment on my own machine.  

- I use a Virtual Machine on Digital Ocean using image Ubuntu20.04.
- Do `apt install python3.6` first.
- `apt install python3.6-dev` to get `Python.h`.
- `apt install libcunit1 libcunit1-doc libcunit1-dev`

It seems to be fine if you don't modify `Makefile`, but I don't know why. `make` works anyway, that's enough.

- Addition: I switch to Ubuntu23.10 after that. The version of Python doesn't really matter because the library `dumbpy` can only be accessed on HIVE machines.

## Task 1

- At first, I didn't assume the `result` matrix is valid. What I did is `allocate_matrix(&result, ...)` which **really cause me big trouble**. Because I'm allocating memory for the *local variable* `*result`! Then I treat the `result` as a valid matrix.
- In `mul_matrix`, I forget to initialize the `result` matrix's entries to all 0.
- Use a "stupid" way to copy the previous `result` into `tmp` in `pow_matrix`. Is there any clever way to implement `pow_matrix`?

## Task 2: Setup Numc

Only need to modify the `setup.py` using 2 function calls. If it's done properly:

- Enter the Virtual Environment
- Type `python3.6` to enter python
- Type `import numc as nc`

The output of python should be `CS61C Fall2020 Project 4: numc imported!`  

## Task 3

The [document](https://docs.python.org/3.6/c-api/index.html) can be really helpful. I use it to parse the Python args into Integer in C.

- Python Number Methods:
  - We need a PyNumberMethods struct to specify the function we use. The format is `.nb_{python_method} = {function_name}`. **Remember**: use `,` at the end of each line.
  - Use `get_shape` function provided in numc.c to write the shape of the result.
  - Throw exception when something went wrong. This is included in `Python.h` so I think the exceptions can only be thrown in `numc.c`, not in `matrix.c` if importing `Python.h` is not allowed.

