CC = gcc
CFLAGS = -g -O0 -Wall -std=c99 -fopenmp -mavx -mfma -pthread
LDFLAGS = -fopenmp
CUNIT = -lcunit
PYTHON_VERSION = 3.11
PYTHON = -lpython$(PYTHON_VERSION)

install: install_dumbpy
	if [ ! -f numc_install.txt ]; then touch numc_install.txt; fi
	rm -rf build
	xargs rm -rf < numc_install.txt
	python3 setup.py install --record numc_install.txt
	echo .venv/lib/python$(PYTHON_VERSION)/site-packages/numc-* >> numc_install.txt

uninstall:
	if [ ! -f numc_install.txt ]; then touch numc_install.txt; fi
	rm -rf build
	xargs rm -rf < numc_install.txt

install_dumbpy:
	if [ ! -f dumbpy_install.txt ]; then touch dumbpy_install.txt; fi
	rm -rf build
	xargs rm -rf < dumbpy_install.txt
	python3 setup_dumbpy.py install --record dumbpy_install.txt
	echo .venv/lib/python$(PYTHON_VERSION)/site-packages/dumbpy-* >> dumbpy_install.txt

uninstall_dumbpy:
	if [ ! -f dumbpy_install.txt ]; then touch dumbpy_install.txt; fi
	rm -rf build
	xargs rm -rf < dumbpy_install.txt

clean:
	rm -f *.o
	rm -f test
	rm -rf build
	rm -rf __pycache__

test:
	rm -f test
	$(CC) $(CFLAGS) tests/mat_test.c src/matrix.c -o test $(LDFLAGS) $(CUNIT) $(PYTHON)
	valgrind -s --tool=memcheck --leak-check=yes ./test

.PHONY: test
