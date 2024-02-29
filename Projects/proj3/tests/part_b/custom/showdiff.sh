#!/bin/bash

file=$1
python binary_to_hex_cpu.py reference_output/cpu-$file-ref.out > ref.out
python binary_to_hex_cpu.py student_output/cpu-$file-student.out > stu.out
echo "ref.out" > diff.out
diff ref.out stu.out >> diff.out

