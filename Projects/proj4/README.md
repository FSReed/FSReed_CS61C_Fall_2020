# numc

As I can't use the HIVE machine, I need to configure the environment on my own machine.  

- I use a Virtual Machine on Digital Ocean using image Ubuntu20.04.
- Do `apt install python3.6` first.
- `apt install python3.6-dev` to get `Python.h`.
- `apt install libcunit1 libcunit1-doc libcunit1-dev`

It seems to be fine if you don't modify `Makefile`, but I don't know why. `make` works anyway, that's enough.

