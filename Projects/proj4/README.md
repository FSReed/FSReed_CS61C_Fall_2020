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

### Conceptual check for Task 3

When implementing slice in Task3, I found the implementation of `allocate` and `deallocate` is totally wrong!  
When creating a slice, this slice should share the same data with its parent matrix. This means **DO NOT allocate another space and copy the data from the parent!**. Instead, only create a `double**` pointer and allocate the space of `rows` pointers of the type `double`. Then manage the pointers to let them point to the right location of the original data.

## Task 2: Setup Numc

Only need to modify the `setup.py` using 2 function calls. If it's done properly:

- Enter the Virtual Environment
- Type `python3.6` to enter python
- Type `import numc as nc`

The output of python should be `CS61C Fall2020 Project 4: numc imported!`  

## Task 3

### Number Methods

The [documentation](https://docs.python.org/3.6/c-api/index.html) can be really helpful. I use it to parse the Python args into Integer in C.

- Python Number Methods:
  - We need a PyNumberMethods struct to specify the function we use. The format is `.nb_{python_method} = {function_name}`. **Remember**: use `,` at the end of each line.
  - Use `get_shape` function provided in numc.c to write the shape of the result.
  - Throw exception when something went wrong. 

*Something weird*: When I launch python, and type:

```Python
import numc as nc

A = nc.Matrix(2, 3, 4);
B = nc.Matrix(3, 4, 2);
A + B
```

And run these codes **without other operations**, **NO EXCEPTION WILL BE THROWN**. But run another `A + B`, the exception occurs.  
If I put these codes in a python file and execute it, the exception will be thrown during the first wrong addition. Huh?

### Instance Methods

Read the documentation!

- If the number of the arguments is wrong or the type of any argument if wrong, throw a `TypeError` exception. This can be handled by `PyArg_ParseTuple` automatically.
- The return value is not a datatype in C. It should be a datatype in Python. `Py_BuildValue` is needed.

