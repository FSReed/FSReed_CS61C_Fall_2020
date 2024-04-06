from distutils.core import setup, Extension
import sysconfig

def main():
    CFLAGS = ['-g', '-Wall', '-std=c99', '-fopenmp', '-mavx', '-mfma', '-pthread', '-O3']
    LDFLAGS = ['-fopenmp']
    # Use the setup function we imported and set up the modules.
    # You may find this reference helpful: https://docs.python.org/3.6/extending/building.html
    # TODO: YOUR CODE HERE
    module = Extension('numc', sources=['numc.c', 'matrix.c'], extra_compile_args=CFLAGS.extend(LDFLAGS))

    setup(name='numc', version='1.0', ext_modules=[module]); 
if __name__ == "__main__":
    main()
